#include "memory.hpp"
#include "lazy_importer.hpp"
#include "../game/sdk.hpp"
#include <stdlib.h>
#include <limits.h>
#include <cctype>
#include <climits>

#define in_range( x,a,b ) ( x >=a&&x<=b ) 
#define get_bits( x ) ( in_range( ( x&( ~0x20 ) ),'A','F' )?( ( x&( ~0x20 ) )-'A'+0xa ):( in_range( x,'0','9' )?x-'0':0 ) )
#define get_byte( x ) ( get_bits( x[ 0 ] )<< 4|get_bits( x[ 1 ] ) )


#ifndef ULONG_MAX
#define        ULONG_MAX        ( ( unsigned long )( ~0L ) )                /* 0xFFFFFFFF */
#endif
/*
 * Convert a string to an unsigned long integer.
 *
 * Ignores `locale' stuff.  Assumes that the upper and lower case
 * alphabets and digits are each contiguous.
 */

uintptr_t memory::sigscan( const char* scanmodule, const char* pattern, int jump )
{
    uintptr_t moduleAdress = 0;
    const auto mod = scanmodule;
    //moduleAdress = LI_MODULE( mod ).get< uintptr_t >( );

    static auto patternToByte = [ ]( const char* pattern )
    {
        auto       bytes = std::vector< int >{ };
        const auto start = const_cast< char* >( pattern );
        const auto end = const_cast< char* >( pattern ) + strlen( pattern );

        for( auto current = start; current < end; ++current )
        {
            if( *current == '?' )
            {
                ++current;
                if( *current == '?' )
                    ++current;
                bytes.push_back( -1 );
            }
            else { bytes.push_back( strtoul( current, &current, 16 ) ); }
        }
        return bytes;
    };

    const auto dosHeader = ( PIMAGE_DOS_HEADER )moduleAdress;
    if( !dosHeader )
        return NULL;

    const auto ntHeaders = ( PIMAGE_NT_HEADERS )( ( std::uint8_t* )moduleAdress + dosHeader->e_lfanew );

    const auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
    auto       patternBytes = patternToByte( pattern );
    const auto scanBytes = reinterpret_cast< std::uint8_t* >( moduleAdress );

    const auto s = patternBytes.size( );
    const auto d = patternBytes.data( );

    for( auto i = 0ul; i < sizeOfImage - s; ++i )
    {
        bool found = true;
        for( auto j = 0ul; j < s; ++j )
        {
            if( scanBytes[ i + j ] != d[ j ] && d[ j ] != -1 )
            {
                found = false;
                break;
            }
        }
        if( found )
        {
            if( !jump )
                return reinterpret_cast< uintptr_t >( &scanBytes[ i ] );
            else
            {
                uintptr_t patterScanResult = ( reinterpret_cast< uintptr_t >( &scanBytes[ i ] ) + jump );
                int relative = read< int >( patterScanResult + 3 );
                return ( patterScanResult + 7 + relative );
            }
        }
    }
    return NULL;
}

uintptr_t memory::find( uintptr_t range_start, uintptr_t range_end, const char* pattern ) {
    const char* pattern_bytes = pattern;

    uintptr_t first_match = 0;

    for( uintptr_t cur_byte = range_start; cur_byte < range_end; cur_byte++ ) {
        if( !*pattern_bytes )
            return first_match;

        if( *( uint8_t* )pattern_bytes == '\?' || *( uint8_t* )cur_byte == static_cast< uint8_t >( get_byte( pattern_bytes ) ) ) {
            if( !first_match )
                first_match = cur_byte;

            if( !pattern_bytes[ 2 ] )
                return first_match;

            if( *( uint16_t* )pattern_bytes == '\?\?' || *( uint8_t* )pattern_bytes != '\?' )
                pattern_bytes += 3;
            else
                pattern_bytes += 2;
        }
        else {
            pattern_bytes = pattern;
            first_match = 0;
        }
    }

    return 0;
}

uintptr_t memory::find( const char* mod, const char* pattern ) {
    const char* pattern_bytes = pattern;

    uintptr_t range_start = LI_MODULE_SAFE_( "GameAssembly.dll" );
    uintptr_t range_size = LI_MODULESIZE_SAFE_( "GameAssembly.dll" );
    uintptr_t range_end = range_start + range_size;

    return find( range_start, range_end, pattern );
}

uintptr_t memory::find_rel( const char* mod, const char* pattern, ptrdiff_t position, ptrdiff_t jmp_size, ptrdiff_t instruction_size ) {
    auto result = find( mod, pattern );

    if( !result )
        return 0;

    result += position;

    auto rel_addr = *reinterpret_cast< int32_t* >( result + jmp_size );
    auto abs_addr = result + instruction_size + rel_addr;

    return abs_addr;
}
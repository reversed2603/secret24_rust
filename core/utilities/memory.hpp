#pragma once
#include "../includes/includes.hpp"

namespace memory
{
    uintptr_t sigscan( const char* module, const char* pattern, int jump = 0 );
    uintptr_t find( uintptr_t range_start, uintptr_t range_end, const char* pattern );
    uintptr_t find( const char* mod, const char* pattern );

    uintptr_t find_rel( const char* mod, const char* pattern, ptrdiff_t position = 0, ptrdiff_t jmp_size = 3, ptrdiff_t instruction_size = 7 );

    template< typename t = uintptr_t >
    t read( uintptr_t address )
    {
        if( !address )
        {
            return t( );
        }
        else if( address < 0xffffff )
        {
            return t( );
        }
        else if( address > 0x7fffffff0000 )
        {
            return t( );
        }
        else
        {
            return *reinterpret_cast< t* >( address );
        }
    }

    template< typename t >
    t read_chain( uintptr_t address, std::vector< uintptr_t > chain )
    {
        uintptr_t cur_read = address;

        for( int i = 0; i < chain.size( ) - 1; ++i )
            cur_read = read< uintptr_t >( cur_read + chain[ i ] );

        return read< t >( cur_read + chain[ chain.size( ) - 1 ] );
    }
}
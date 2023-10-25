#include <Windows.h>
#include "core/includes/includes.hpp"
#include "core/game/hooks.hpp"
#include "core/game/offsets.hpp"
#include "core/game/sdk.hpp"

unsigned long main( void* ) {

    il2mgr::init( ); // would look pretty dope if i'd space it out
    {
        hooks::init( );
    }
    return 0;
}

bool DllMain( void* arg1, unsigned long reason, void* r ) {
    if( reason != 1 )
        return false;

    const auto handle = CreateThread( nullptr, 0, &main, nullptr, 0, nullptr );
    if( handle ) // make sure handle has a valid pointer.
        CloseHandle( handle );

    return true;
}
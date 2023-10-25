#pragma once
#include <type_traits>

template < typename result, typename... arguments >
__forceinline static result spoof_ret( result( *fn )( arguments... ), arguments... args )
{
	return fn( args... );
}

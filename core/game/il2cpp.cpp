#include "il2cpp.hpp"
#include <map>

std::map< const char*, uintptr_t > this_classes;
std::map< const char*, uintptr_t > method_list;
std::map< const char*, uintptr_t > field_list;

namespace il2mgr {
	void init( )
	{
		game_assembly = LI_MODULE( ( "GameAssembly.dll" ) ).get< uintptr_t >( );
		unity_player = LI_MODULE( ( "UnityPlayer.dll" ) ).get< uintptr_t >( );

		using il2cpp_domain_get = uintptr_t( * )( );
		methods::domain_get = LI_FIND_DEF( il2cpp_domain_get );

		using il2cpp_class_get_methods = uintptr_t( * )( uintptr_t, uintptr_t* );
		methods::class_get_methods = LI_FIND_DEF( il2cpp_class_get_methods );

		using il2cpp_method_get_param = uintptr_t( * )( uintptr_t, int );
		methods::method_get_param = LI_FIND_DEF( il2cpp_method_get_param );

		using il2cpp_method_get_param_count = int ( * )( uintptr_t );
		methods::method_get_param_count = LI_FIND_DEF( il2cpp_method_get_param_count );

		using il2cpp_assembly_get_image = uintptr_t( * )( uintptr_t );
		methods::assembly_get_image = LI_FIND_DEF( il2cpp_assembly_get_image );

		using il2cpp_domain_get_assemblies = uintptr_t * ( * )( void*, uintptr_t* );
		methods::domain_get_assemblies = LI_FIND_DEF( il2cpp_domain_get_assemblies );

		using il2cpp_class_from_name = uintptr_t( * )( uintptr_t, const char*, const char* );
		methods::class_from_name = LI_FIND_DEF( il2cpp_class_from_name );

		using il2cpp_resolve_icall = uintptr_t( * )( const char* );
		methods::resolve_icall = LI_FIND_DEF( il2cpp_resolve_icall );

		using il2cpp_class_get_field_from_name = uintptr_t( * )( uintptr_t, const char* );
		methods::class_get_field_from_name = LI_FIND_DEF( il2cpp_class_get_field_from_name );

		using il2cpp_field_static_get_value = uintptr_t( * )( uintptr_t, uintptr_t* );
		methods::field_static_get_value = LI_FIND_DEF( il2cpp_field_static_get_value );

		using il2cpp_class_get_fields = uintptr_t( * )( uintptr_t, uintptr_t* );
		methods::class_get_fields = LI_FIND_DEF( il2cpp_class_get_fields );

		using il2cpp_field_get_offset = uintptr_t( * )( uintptr_t );
		methods::field_get_offset = LI_FIND_DEF( il2cpp_field_get_offset );

		using il2cpp_object_new = uintptr_t( * )( uintptr_t );
		methods::object_new = LI_FIND_DEF( il2cpp_object_new );

		using il2cpp_type_get_object = uintptr_t( * )( uintptr_t );
		methods::type_get_object = LI_FIND_DEF( il2cpp_type_get_object );

		using il2cpp_class_get_type = uintptr_t( * )( uintptr_t );
		methods::class_get_type = LI_FIND_DEF( il2cpp_class_get_type );

		using il2cpp_runtime_class_init = uintptr_t( * )( uintptr_t );
		methods::runtime_class_init = LI_FIND_DEF( il2cpp_runtime_class_init );

		using il2cpp_string_new_wrapper = il2cppstring * ( * )( const char* );
		methods::new_string = LI_FIND_DEF( il2cpp_string_new_wrapper );
	}

	uintptr_t init_class( const char* name, const char* name_space )
	{
		uintptr_t domain = methods::domain_get( );

		if( !domain )
			return NULL;

		uintptr_t nrofassemblies;
		uintptr_t* assemblies = methods::domain_get_assemblies( ( void* )domain, &nrofassemblies );

		for( int i = 0; i < nrofassemblies; i++ )
		{
			uintptr_t img = methods::assembly_get_image( assemblies[ i ] );

			uintptr_t kl = methods::class_from_name( img, name_space, name );
			if( !kl )
				continue;

			return kl;
		}

		return NULL;
	}

	uintptr_t type_object( const char* name_space, const char* name )
	{
		uintptr_t this_class = init_class( name, name_space );
		return methods::type_get_object( methods::class_get_type( this_class ) );
	}

	uintptr_t method( std::string kl, std::string name, int param_count, const char* name_space, bool param_check, int param_idx, std::string param_name )
	{
		uintptr_t this_class = init_class( kl.c_str( ), name_space );
		if( !this_class )
			return NULL;

		if( !param_check )
			return methods::class_get_method_from_name( this_class, name.c_str( ), param_count );
		else
		{
			uintptr_t nrofmethods;
			uintptr_t methods;
			methods = methods::class_get_methods( this_class, &nrofmethods );
			while( methods = methods::class_get_methods( this_class, &nrofmethods ) )
			{
				char* method_name = *reinterpret_cast< char** >( methods + 0x10 );
				if( std::string( method_name ) == name )
				{
					uintptr_t args = *reinterpret_cast< uintptr_t* >( methods + 0x28 );
					char* arg_name = *reinterpret_cast< char** >( args + 1 * 0x18 );
				}
			}
		}

		return NULL;
	}

	uintptr_t hook( void* our_func, std::string kl, std::string name, int arg, const char* name_space )
	{
		uintptr_t il2mgr_method = method( kl.c_str( ), name.c_str( ), arg, name_space );
		*reinterpret_cast< void** >( il2mgr_method ) = our_func;

		void* written = *reinterpret_cast< void** >( il2mgr_method );
		if( !written )
			return NULL;

		return il2mgr_method;
	}

	uintptr_t hook_virt( const char* classname, const char* function_to_hook, void* our_func, int param_count, const char* name_space )
	{
		uintptr_t this_method = method( classname, function_to_hook, param_count, name_space );
		if( !this_method )
			return NULL;

		uintptr_t search = *reinterpret_cast< uintptr_t* >( this_method );
		uintptr_t table = init_class( classname, name_space );

		if( search == reinterpret_cast< uintptr_t >( our_func ) )
			return reinterpret_cast< uintptr_t >( our_func );

		for( uintptr_t i = table; i <= table + 0x10000; i += 0x1 ) {
			uintptr_t addr = *reinterpret_cast< uintptr_t* >( i );
			if( addr == search )
			{
				*reinterpret_cast< uintptr_t* >( i ) = reinterpret_cast< uintptr_t >( our_func );
				return addr;
			}
		}

		return NULL;
	}

	uintptr_t field( uintptr_t this_class, const char* name )
	{
		return methods::class_get_field_from_name( this_class, name );
	}

	uintptr_t value( const char* kl, const char* name, bool get_offset, const char* name_space )
	{
		uintptr_t this_class = init_class( kl, name_space );

		if( !this_class )
			return NULL;

		uintptr_t this_field = field( this_class, name );
		if( get_offset )
		{
			uintptr_t out = 0;
			uintptr_t il2cpp_field = NULL;
			uintptr_t field_offset = NULL;

			while( il2cpp_field = methods::class_get_fields( this_class, &out ) )
			{
				char* char_name = ( char* )*reinterpret_cast< uintptr_t* >( il2cpp_field );
				if( !char_name )
					continue;

				uintptr_t offset = methods::field_get_offset( il2cpp_field );
				std::string field_name = std::string( char_name );
				if( name == field_name )
				{
					field_offset = offset;
					break;
				}
			}
			return field_offset;
		}

		uintptr_t static_value;
		methods::field_static_get_value( this_field, &static_value );
		if( static_value )
			return static_value;

		return NULL;
	}
}
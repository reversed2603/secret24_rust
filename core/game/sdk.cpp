#include "sdk.hpp"
#include <cmath>
#include "il2cpp.hpp"
#include "offsets.hpp"
#include "../utilities/memory.hpp"
#include "../utilities/returnspoofer.hpp"
#include "enums.hpp"
#include "../features/options.h"

il2mgr::il2cppstring* il2mgr::il2cppstring::New( const char* str )
{
	return spoof_ret( il2mgr::methods::new_string, str );
}

typedef struct str_ing
{
	char stub[ 0x10 ];
	int len;
	wchar_t str[ 1 ];
} *str;

// create global definition for sdk class.
c_sdk g_sdk;

// create global definition for cheat class.
c_cheat g_cheat;

// create global definition for game class.
c_game g_game;

void camera::set_aspect_ratio( float value ) {
	uintptr_t entity = reinterpret_cast< uintptr_t >( this );
	if( !entity )
		return;

	uintptr_t method = offsets::set_aspect;
	if( !method )
		return;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return;

	auto set_aspect = reinterpret_cast< void( * )( uintptr_t, float ) >( method_ptr );
	spoof_ret( set_aspect, entity, value );
}

matrix_4x4 camera::get_view_matrix( )
{
	if( !g_cheat.camera_ptr )
		return matrix_4x4( );

	uintptr_t camera = *reinterpret_cast< uintptr_t* >( ( uintptr_t )g_cheat.camera_ptr + 0x10 );
	if( !camera )
		return matrix_4x4( );

	matrix_4x4 matrix = *reinterpret_cast< matrix_4x4* >( camera + 0x2E4 );
	if( !matrix.base( ) )
		return matrix_4x4( );

	return matrix;
}

static bool has_drew_once = true;

vec2_t c_sdk::world_to_screen( vec3_t ent_pos )
{
	camera* camera = get_main_camera( );
	if( !camera )
		return vec2_t( );

	matrix_4x4 matrix = camera->get_view_matrix( ).transpose( );

	if( !matrix.m )
		return vec2_t( );

	auto trans = vec3_t( matrix[ 3 ][ 0 ], matrix[ 3 ][ 1 ], matrix[ 3 ][ 2 ] );
	auto up = vec3_t( matrix[ 1 ][ 0 ], matrix[ 1 ][ 1 ], matrix[ 1 ][ 2 ] );
	auto right = vec3_t( matrix[ 0 ][ 0 ], matrix[ 0 ][ 1 ], matrix[ 0 ][ 2 ] );

	float w = trans.dot( ent_pos ) + matrix[ 3 ][ 3 ];

	float x = right.dot( ent_pos ) + matrix[ 0 ][ 3 ];
	float y = up.dot( ent_pos ) + matrix[ 1 ][ 3 ];

	vec2_t this_out = vec2_t( );
	this_out.x = static_cast< int >( ( g_cheat.screen_size.x ) / 2 * ( 1 + x / w ) );
	this_out.y = static_cast< int >( ( g_cheat.screen_size.y ) / 2 * ( 1 - y / w ) );

	if( this_out.is_zero( ) )
		return vec2_t( );

	return w > 0.1 ? this_out : vec2_t( );
}

void c_sdk::set_gl_color( color_t color )
{
	uintptr_t method = offsets::set_gl_color;
	if( !method )
		return;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return;

	auto set_color = reinterpret_cast< void( * )( color_t ) >( method_ptr );

	spoof_ret( set_color, color );
}

bool c_game::water_level_test( vec3_t pos, bool value1, bool value2, core::base_entity* entity ) {
	uintptr_t method = offsets::waterlevel_test;
	if( !method )
		return false;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return false;

	auto water_level_test = reinterpret_cast< bool( * )( vec3_t, bool, bool, core::base_entity* ) >( method_ptr );

	return spoof_ret( water_level_test, pos, value1, value2, entity );
}

void c_game::set_flash_duration( float value ) {
	static uintptr_t this_class = offsets::flashbang_overlay_instance;
	if( !this_class )
		return;

	static uintptr_t static_fields = *reinterpret_cast< uintptr_t* >( this_class + 0xB8 ); //LOL
	if( !static_fields )
		return;

	*reinterpret_cast< float* >( static_fields + 0x40 ) = value;
}

void c_game::set_graphics_fov( float value ) {
	static uintptr_t this_class = offsets::graphics_convar;
	if( !this_class )
		return;

	static uintptr_t static_fields = *reinterpret_cast< uintptr_t* >( this_class + 0xB8 ); //LOL
	if( !static_fields )
		return;

	*reinterpret_cast< float* >( static_fields + 0x18 ) = value;
}

void c_game::set_admin_time( float value ) {
	static uintptr_t this_class = offsets::admin_convar;
	if( !this_class )
		return;

	static uintptr_t static_fields = *reinterpret_cast< uintptr_t* >( this_class + 0xB8 ); //LOL
	if( !static_fields )
		return;

	*reinterpret_cast< float* >( static_fields + 0x0 ) = value;
}

void c_game::set_underwater_blur( bool value ) {
	static uintptr_t this_class = offsets::admin_convar;
	if( !this_class )
		return;

	static uintptr_t static_fields = *reinterpret_cast< uintptr_t* >( this_class + 0xB8 ); //LOL
	if( !static_fields )
		return;

	*reinterpret_cast< bool* >( static_fields + 0x11 ) = value;
}

void c_game::set_admin_ref_mp( float value ) {
	static uintptr_t this_class = offsets::admin_convar;
	if( !this_class )
		return;

	static uintptr_t static_fields = *reinterpret_cast< uintptr_t* >( this_class + 0xB8 ); //LOL
	if( !static_fields )
		return;

	*reinterpret_cast< float* >( static_fields + 0x8 ) = value;
}

void c_game::set_admin_ambient_mp( float value ) {
	static uintptr_t this_class = offsets::admin_convar;
	if( !this_class )
		return;

	static uintptr_t static_fields = *reinterpret_cast< uintptr_t* >( this_class + 0xB8 ); //LOL
	if( !static_fields )
		return;

	*reinterpret_cast< float* >( static_fields + 0xC ) = value;
}

void c_game::set_rain( float value )
{
	uintptr_t method = offsets::set_rain;
	if( !method )
		return;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return;

	auto set_rain = reinterpret_cast< void( * )( float ) >( method_ptr );
	spoof_ret( set_rain, value );
}

void c_game::set_rayleigh( float value )
{
	uintptr_t method = offsets::set_atmosphere_rayleigh;
	if( !method )
		return;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return;

	auto set_rayleigh = reinterpret_cast< void( * )( float ) >( method_ptr );
	spoof_ret( set_rayleigh, value );
}

void c_game::set_mie( float value )
{
	uintptr_t method = offsets::set_atmosphere_mie;
	if( !method )
		return;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return;

	auto set_mie = reinterpret_cast< void( * )( float ) >( method_ptr );
	spoof_ret( set_mie, value );
}

void c_game::set_is_sprinting( bool value )
{
	uintptr_t method = offsets::input_convar;
	if( !method )
		return;
		
	static uintptr_t static_fields = *reinterpret_cast< uintptr_t* >( method + 0xB8 ); //LOL
	if( !static_fields )
		return;

	*reinterpret_cast< bool* >( static_fields + 0x12 ) = value;
}

void c_game::set_brightness( float value )
{
	uintptr_t method = offsets::set_atmosphere_brightness;
	if( !method )
		return;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return;

	auto set_brightness = reinterpret_cast< void( * )( float ) >( method_ptr );
	spoof_ret( set_brightness, value );
}

char* c_sdk::memstr( char* haystack, const char* needle, int size )
{
	char* p;
	char needlesize = strlen( needle );
	for( p = haystack; p <= ( haystack - needlesize + size ); p++ ) {
		if( memcmp( p, needle, needlesize ) == 0 )
		{
			return p;
		}
	}
	return NULL;
}

std::string c_sdk::ws2s( const std::wstring& wstr )
{
	std::string str( wstr.begin( ), wstr.end( ) );
	return str;
}

std::wstring c_sdk::s2ws( const std::string& str )
{
	int size_needed = MultiByteToWideChar( CP_UTF8, 0, &str[ 0 ], ( int )str.size( ), NULL, 0 );
	std::wstring wstrTo( size_needed, 0 );
	MultiByteToWideChar( CP_UTF8, 0, &str[ 0 ], ( int )str.size( ), &wstrTo[ 0 ], size_needed );
	return wstrTo;
}

std::wstring c_sdk::read_unicode( uint64_t address, std::size_t size )
{
	const auto buffer = std::make_unique< wchar_t[ ] >( size );
	memcpy( buffer.get( ), reinterpret_cast< const void* >( address ), size * 2 );
	return std::wstring( buffer.get( ) );
}

std::string c_sdk::read_ascii( uint64_t address, std::size_t size )
{
	return std::string( reinterpret_cast< const char* >( address ) );
}

laddy_list< uintptr_t >* c_sdk::get2renderers( uintptr_t multimesh )
{
	uintptr_t method = offsets::get_Renderers;
	if( !method )
		return NULL;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return NULL;

	auto get_renderers = reinterpret_cast< laddy_list< uintptr_t >*( * )( uintptr_t ) >( method_ptr );
	return spoof_ret( get_renderers, multimesh );
}

uintptr_t c_sdk::get_material( uintptr_t renderer )
{
	uintptr_t method = offsets::get_material;
	if( !method )
		return NULL;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return NULL;

	auto get_material = reinterpret_cast< uintptr_t( * )( uintptr_t ) >( method_ptr );
	return spoof_ret( get_material, renderer );
}

uintptr_t c_sdk::get_texture( uintptr_t sprite )
{
	uintptr_t method = offsets::get_texture;
	if( !method )
		return NULL;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return NULL;

	auto get_texture = reinterpret_cast< uintptr_t( * )( uintptr_t ) >( method_ptr );
	if( !get_texture )
		return NULL;

	return spoof_ret( get_texture, sprite );
}

uintptr_t c_sdk::get_shader( uintptr_t material )
{
	uintptr_t method = offsets::get_shader;
	if( !method )
		return NULL;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return NULL;

	auto get_shader = reinterpret_cast< uintptr_t( * )( uintptr_t ) >( method_ptr );
	return spoof_ret( get_shader, material );
}

uintptr_t c_sdk::load_asset( uintptr_t assetbundle, std::string shader, uintptr_t typeobject )
{
	uintptr_t method = offsets::LoadAsset_Internal;
	if( !method )
		return NULL;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return NULL;

	auto load_asset = reinterpret_cast< uintptr_t( * )( uintptr_t, il2mgr::il2cppstring*, uintptr_t ) >( method_ptr );
	return spoof_ret( load_asset, assetbundle, il2mgr::il2cppstring::New( shader.c_str( ) ), typeobject );
}

uintptr_t c_sdk::load_bundle_file( std::string data )
{
	uintptr_t method = offsets::LoadFromFile_Internal;
	if( !method )
		return NULL;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return NULL;

	auto bundle = reinterpret_cast< uintptr_t( * )( il2mgr::il2cppstring*, uint32_t, std::uint64_t ) >( method_ptr );
	return spoof_ret( bundle, il2mgr::il2cppstring::New( data.c_str( ) ), uint32_t( 0 ), std::uint64_t( 0 ) );
}

uintptr_t c_sdk::find( const char* shader )
{
	uintptr_t method = offsets::find;
	if( !method )
		return NULL;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return NULL;

	auto get_shader = reinterpret_cast< uintptr_t( * )( il2mgr::il2cppstring * shader ) >( method_ptr );
	return spoof_ret( get_shader, il2mgr::il2cppstring::New( shader ) );
}

void c_sdk::create_shader( uintptr_t self, uintptr_t shader )
{
	uintptr_t method = offsets::CreateWithShader;
	if( !method )
		return;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return;

	auto set_color = reinterpret_cast< void( * )( uintptr_t, uintptr_t ) >( method_ptr );
	spoof_ret( set_color, self, shader );
}

void c_sdk::set_shader( uintptr_t material, uintptr_t shader )
{
	uintptr_t method = offsets::set_shader;
	if( !method )
		return;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return;

	auto set_color = reinterpret_cast< void( * )( uintptr_t material, uintptr_t shader ) >( method_ptr );
	spoof_ret( set_color, material, shader );
}

void set_gl_color( color_t color )
{
	uintptr_t method = offsets::set_gl_color;
	if( !method )
		return;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return;

	auto set_color = reinterpret_cast< void( * )( color_t ) >( method_ptr );

	spoof_ret( set_color, color );
}

void c_sdk::set_color( uintptr_t material, const char* name, color_t color )
{
	uintptr_t method = offsets::set_color;
	if( !method )
		return;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return;

	auto set_color = reinterpret_cast< void( * )( uintptr_t material, il2mgr::il2cppstring * name, color_t color ) >( method_ptr );

	spoof_ret( set_color, material, il2mgr::il2cppstring::New( name ), color );
}

void c_sdk::push_matrix( )
{
	uintptr_t method = offsets::push_matrix;
	if( !method )
		return;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return;

	auto push_matrix = reinterpret_cast< void( * )( ) >( method_ptr );

	spoof_ret( push_matrix );
}

void c_sdk::begin( int mode )
{
	uintptr_t method = offsets::begin;
	if( !method )
		return;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return;

	auto push_matrix = reinterpret_cast< void( * )( int ) >( method_ptr );

	spoof_ret( push_matrix, mode );
}

void c_sdk::end( )
{
	uintptr_t method = offsets::end;
	if( !method )
		return;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return;

	auto push_matrix = reinterpret_cast< void( * )( ) >( method_ptr );

	spoof_ret( push_matrix );
}

void c_sdk::pop_matrix( )
{
	uintptr_t method = offsets::pop_matrix;
	if( !method )
		return;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return;

	auto push_matrix = reinterpret_cast< void( * )( ) >( method_ptr );

	spoof_ret( push_matrix );
}

void c_sdk::vertex( vec3_t vertex )
{
	uintptr_t method = offsets::vertex;
	if( !method )
		return;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return;

	auto _vertex = reinterpret_cast< void( * )( vec3_t ) >( method_ptr );

	spoof_ret( _vertex, vertex );
}

void c_sdk::set_pass( uintptr_t material, int value )
{
	uintptr_t method = offsets::set_pass;
	if( !method )
		return;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return;

	auto set_pass = reinterpret_cast< void( * )( uintptr_t material, int value ) >( method_ptr );

	spoof_ret( set_pass, material, value );
}
	
void c_sdk::set_material_float( uintptr_t material, const char* name, float value )
{
	uintptr_t method = offsets::set_float;
	if( !method )
		return;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return;

	auto set_color = reinterpret_cast< void( * )( uintptr_t material, il2mgr::il2cppstring * name, float value ) >( method_ptr );

	spoof_ret( set_color, material, il2mgr::il2cppstring::New( name ), value );
}

void c_sdk::set_material_int( uintptr_t material, const char* name, int value )
{
	uintptr_t method = offsets::set_int;
	if( !method )
		return;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return;

	auto set_color = reinterpret_cast< void( * )( uintptr_t material, il2mgr::il2cppstring * name, int value ) >( method_ptr );

	spoof_ret( set_color, material, il2mgr::il2cppstring::New( name ), value );
}

uintptr_t c_sdk::scan_for_camera_list( )
{
	uintptr_t unity_player = il2mgr::unity_player;
	if( !unity_player )
		return NULL;

	const auto dos_header = reinterpret_cast< IMAGE_DOS_HEADER* >( unity_player );
	const auto nt_header = reinterpret_cast< IMAGE_NT_HEADERS64* >( unity_player + dos_header->e_lfanew );

	uint64_t data_base;
	uint64_t data_size;

	for( int i = 0;; )
	{
		const auto section = reinterpret_cast< IMAGE_SECTION_HEADER* >( 
			unity_player + dos_header->e_lfanew + // nt_header base
			sizeof( IMAGE_NT_HEADERS64 ) +  // start of section headers
			( i * sizeof( IMAGE_SECTION_HEADER ) ) ); // section header at our index

		if( strcmp( ( char* )section->Name, xs( ".data" ) ) == 0 )
		{
			data_base = section->VirtualAddress + unity_player;
			data_size = section->SizeOfRawData;
			break;
		}

		i++;

		if( i >= nt_header->FileHeader.NumberOfSections )
			return NULL;
	}

	uint64_t camera_table = 0;

	const auto camera_string = memstr( ( char* )data_base, xs( "AllCameras" ), data_size );

	for( auto walker = ( uint64_t* )camera_string; walker > ( uint64_t* )0; walker -= 1 )
	{
		if( *walker > 0x100000
			&& *walker < 0xF00000000000000 )
		{
			camera_table = *walker;
			break;
		}
	}

	if( camera_table )
		return camera_table;

	return NULL;
}

vec3_t c_sdk::get_camera_pos( )
{
	uintptr_t camera_list = scan_for_camera_list( );
	if( !camera_list )
		return vec3_t( );

	uintptr_t camera_table = *reinterpret_cast< uintptr_t* >( camera_list );
	if( !camera_table )
		return vec3_t( );

	uintptr_t camera = *reinterpret_cast< uintptr_t* >( camera_table );
	if( !camera )
		return vec3_t( );

	vec3_t position = *reinterpret_cast< vec3_t* >( camera + 0x42C );
	if( position.is_zero( ) )
		return vec3_t( );

	return position;
}

uintptr_t c_sdk::get_component( uintptr_t game_object, const char* name_str )
{
	if( !game_object )
		return NULL;

	uintptr_t list = *reinterpret_cast< uintptr_t* >( game_object + 0x30 );
	for( int i = 0; i < 20; i++ )
	{
		uintptr_t component = *reinterpret_cast< uintptr_t* >( list + ( 0x10 * i + sizeof( uint64_t ) ) );

		if( !component )
			continue;

		uintptr_t unk1 = *reinterpret_cast< uintptr_t* >( component + 0x28 );
		if( !unk1 )
			continue;

		uintptr_t name_ptr = *reinterpret_cast< uintptr_t* >( unk1 );
		if( !name_ptr )
			continue;

		std::string name = g_sdk.read_ascii( *reinterpret_cast< uintptr_t* >( name_ptr + 0x10 ), 18 );

		if( !strcmp( name.c_str( ), name_str ) )
			return unk1;
	}

	return NULL;
}

vec3_t c_sdk::get_mouse_pos( )
{
	uintptr_t method = offsets::get_mousePosition;
	if( !method )
		return vec3_t( );

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return vec3_t( );

	auto get_mousePosition = reinterpret_cast< vec3_t( * )( ) >( method_ptr );
	return get_mousePosition( );
}

int c_sdk::get_screen_width( )
{
	uintptr_t method = offsets::screen_get_width;
	if( !method )
		return 0;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return 0;

	auto get_screen_position = reinterpret_cast< int( * )( ) >( method_ptr );
	return spoof_ret( get_screen_position );
}

int c_sdk::get_screen_height( )
{
	uintptr_t method = offsets::screen_get_height;
	if( !method )
		return 0;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return 0;

	auto get_screen_position = reinterpret_cast< int( * )( ) >( method_ptr );
	return spoof_ret( get_screen_position );
}

float c_sdk::realtimeSinceStartup( ) {
	uintptr_t method = offsets::real_time_since_startup;
	if( !method )
		return 0.f;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return 0.f;

	auto real_time_since_startup = reinterpret_cast< float( * )( ) >( method_ptr );
	return spoof_ret( real_time_since_startup );
}

float c_sdk::get_fixedTime( ) {
	uintptr_t method = offsets::get_fixed_time;
	if( !method )
		return 0.f;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return 0.f;

	auto get_fixed_time = reinterpret_cast< float( * )( ) >( method_ptr );
	return spoof_ret( get_fixed_time );
}

void c_sdk::ignore_layer_collision( layer the_layer, layer ignore_layer, bool should_collide )
{
	uintptr_t method = offsets::ignore_layer_collision;
	if( !method )
		return;

	auto ignore_layer_func = reinterpret_cast< void( * )( layer, layer, bool ) >( method );
	spoof_ret( ignore_layer_func, the_layer, ignore_layer, should_collide );
}

bool c_sdk::get_key_down( key_code key )
{
	uintptr_t method = offsets::input_get_key_down;
	if( !method )
		return false;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return false;

	auto get_keydown = reinterpret_cast< bool( * )( key_code ) >( method_ptr );
	return spoof_ret( get_keydown, key );
}

bool c_sdk::get_key_up( key_code key )
{
	uintptr_t method = offsets::input_get_key_up; //il2mgr::method( xs( "Input" ), xs( "GetKeyUp" ), 1, xs( "UnityEngine" ) );
	if( !method )
		return false;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return false;

	auto get_keydown = reinterpret_cast< bool( * )( key_code ) >( method_ptr );
	return spoof_ret( get_keydown, key );
}

bool c_sdk::get_key( int key )
{
	uintptr_t method = offsets::input_get_key;
	if( !method )
		return false;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return false;

	auto get_keydown = reinterpret_cast< bool( * )( key_code ) >( method_ptr );
	return spoof_ret( get_keydown, static_cast< key_code >( key ) );
}

bool c_sdk::get_key( key_code key )
{
	uintptr_t method = offsets::input_get_key;
	if( !method )
		return false;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return false;

	auto get_keydown = reinterpret_cast< bool( * )( key_code ) >( method_ptr );
	return spoof_ret( get_keydown, key );
}

bool c_sdk::line_of_sight( vec3_t start, vec3_t end, int layer_mask, float padding )
{
	uintptr_t method = offsets::gamephysics_line_of_site; //il2mgr::method( xs( "game_physics" ), xs( "LineOfSight" ), 4 );
	if( !method )
		return false;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return false;

	auto get_line_of_sight = reinterpret_cast< bool( * )( vec3_t, vec3_t, int, float ) >( method_ptr );
	return spoof_ret( get_line_of_sight, start, end, layer_mask, padding );
}

bool c_sdk::is_visible( vec3_t start, vec3_t end )
{
	auto layer = ( ( int )Layers::ProjectileLineOfSightCheckTerrain | ( int )Layers::BuildLineOfSightCheck | ( int )Layers::Construction );

	return line_of_sight( start, end, layer, 0 );
}

uintptr_t c_sdk::get_current( )
{
	uintptr_t method = offsets::event_get_current;
	if( !method )
		return NULL;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return NULL;

	auto get_current = reinterpret_cast< uintptr_t( * )( ) >( method_ptr );
	return spoof_ret( get_current );
}

event_type c_sdk::get_event_type( uintptr_t current )
{
	uintptr_t method = offsets::event_get_type;
	if( !method )
		return event_type::Ignore;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return event_type::Ignore;

	auto get_type = reinterpret_cast< event_type( * )( uintptr_t ) >( method_ptr );
	return spoof_ret( get_type, current );
}

uintptr_t c_sdk::get_draw_skin( )
{
	uintptr_t method = offsets::gui_get_skin;
	if( !method )
		return false;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return false;

	auto get_skin = reinterpret_cast< uintptr_t( * )( ) >( method_ptr );
	return spoof_ret( get_skin );
}

uintptr_t c_sdk::get_white_texture( )
{
	uintptr_t method = offsets::texture2d_get_whitetexture;
	if( !method )
		return NULL;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return NULL;

	auto get_whiteTexture = reinterpret_cast< uintptr_t( * )( ) >( method_ptr );
	return spoof_ret( get_whiteTexture );
}

uintptr_t c_sdk::get_guicontent_temp( il2mgr::il2cppstring* content )
{
	uintptr_t method = offsets::guicontent_temp;
	if( !method )
		return NULL;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return NULL;

	auto temp = reinterpret_cast< uintptr_t( * )( il2mgr::il2cppstring * content ) >( method_ptr );
	return spoof_ret( temp, content );
}

void c_sdk::set_draw_font_size( uintptr_t label, int size )
{
	uintptr_t method = offsets::guistyle_set_fontsize;
	if( !method )
		return;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return;

	auto set_fontSize = reinterpret_cast< void( * )( uintptr_t label, int size ) >( method_ptr );
	spoof_ret( set_fontSize, label, size );
}

void c_sdk::set_draw_color( color_t color )
{
	uintptr_t method = offsets::gui_set_color;
	if( !method )
		return;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return;

	auto set_color = reinterpret_cast< void( * )( color_t color ) >( method_ptr );
	spoof_ret( set_color, color );
}

void c_sdk::set_draw_alignment( uintptr_t label, uintptr_t value )
{
	uintptr_t method = offsets::guistyle_set_alignment;
	if( !method )
		return;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return;

	auto set_alignment = reinterpret_cast< void( * )( uintptr_t label, uintptr_t value ) >( method_ptr );
	spoof_ret( set_alignment, label, value );
}

void c_sdk::set_cursor_lockstate( int value )
{
	uintptr_t method = offsets::cursor_set_lockState;
	if( !method )
		return;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return;

	auto set_lockState = reinterpret_cast< void( * )( int ) >( method_ptr );
	spoof_ret( set_lockState, value );
}

void c_sdk::draw_texture( vec4_t position, uintptr_t texture )
{
	uintptr_t method = offsets::gui_drawtexture;
	if( !method )
		return;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return;

	auto draw_texture = reinterpret_cast< void( * )( vec4_t position, uintptr_t texture ) >( method_ptr );
	spoof_ret( draw_texture, position, texture );
}

void c_sdk::create( uintptr_t self, const char* shader )
{
	uintptr_t method = offsets::create;
	if( !method )
		return;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return;

	auto create = reinterpret_cast< void( * )( uintptr_t self, il2mgr::il2cppstring * shader ) >( method_ptr );
	spoof_ret( create, self, il2mgr::il2cppstring::New( shader ) );
}

void c_sdk::add_component( uintptr_t self, uintptr_t componentType )
{
	uintptr_t method = offsets::add_component;
	if( !method )
		return;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return;

	auto add_component = reinterpret_cast< void( * )( uintptr_t self, uintptr_t componentType ) >( method_ptr );
	spoof_ret( add_component, self, componentType );
}

void c_sdk::dont_destroy_on_load( uintptr_t target )
{
	uintptr_t method = offsets::dont_destroy_on_load;
	if( !method )
		return;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return;

	auto dont_destroy_on_load = reinterpret_cast< void( * )( uintptr_t target ) >( method_ptr );
	spoof_ret( dont_destroy_on_load, target );
}

uintptr_t c_sdk::CreatePrefab( const char* prefab, bool active )
{
	uintptr_t method = offsets::gamemanager_createprefab;
	if( !method )
	{
		return NULL;
	}

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
	{
		return NULL;
	}

	auto create_prefab = reinterpret_cast< uintptr_t( * )( il2mgr::il2cppstring*, bool ) >( method_ptr );
	return spoof_ret( create_prefab, il2mgr::il2cppstring::New( prefab ), active );
}

void c_sdk::Destroy( uintptr_t object )
{
	uintptr_t method = offsets::gamemanager_destroy;
	if( !method )
	{
		return;
	}

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
	{
		return;
	}

	auto create_prefab = reinterpret_cast< void( * )( uintptr_t ) >( method_ptr );
	return spoof_ret( create_prefab, object );
}

void c_sdk::set_timescale( float value )
{
	uintptr_t method = offsets::Settime;
	if( !method )
		return;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return;

	auto get_time = reinterpret_cast< void( * )( float ) >( method_ptr );
	spoof_ret( get_time, value );
}

float c_sdk::system_time( ) {
	return ( float )( clock( ) / ( float )1000.f );
}

float c_sdk::get_time( )
{
	uintptr_t method = offsets::time_get_time;
	if( !method )
		return 0.f;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return 0.f;

	auto get_time = reinterpret_cast< float( * )( ) >( method_ptr );
	return spoof_ret( get_time );
}

float c_sdk::get_deltaTime( )
{
	uintptr_t method = offsets::time_get_deltaTime;
	if( !method )
		return 0.f;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return 0.f;

	auto get_deltaTime = reinterpret_cast< float( * )( ) >( method_ptr );
	return spoof_ret( get_deltaTime );
}

float c_sdk::random_range( float min, float max )
{
	uintptr_t method = offsets::randomrange;
	if( !method )
	{
		return min + ( max - min );
	}

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
	{
		return min + ( max - min );
	}

	auto range = reinterpret_cast< float( * )( float min, float max ) >( method_ptr );
	return spoof_ret( range, min, max );
}

bool c_sdk::physics_checkcapsule( vec3_t start, vec3_t end, float radius, int layer_mask, QueryTriggerInteraction querytriggerinteraction )
{
	uintptr_t method = offsets::physics_checkcapsule;
	if( !method )
		return false;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return false;

	auto checkcapsule = reinterpret_cast< bool( * )( vec3_t, vec3_t, float, int, QueryTriggerInteraction ) >( method_ptr );
	return spoof_ret( checkcapsule, start, end, radius, layer_mask, querytriggerinteraction );
}

namespace core
{
	vec3_t transform::get_position( )
	{
		if( !g_cheat.local
			|| !g_cheat.camera_ptr )
			return vec3_t( );

		uintptr_t transform = reinterpret_cast< uintptr_t >( this );
		if( !transform )
			return vec3_t( );

		uintptr_t method = offsets::transform_get_position;
		if( !method )
			return vec3_t( );

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
			return vec3_t( );

		auto get_transform_position = reinterpret_cast< vec3_t( * )( uintptr_t ) >( method_ptr );

		return spoof_ret( get_transform_position, transform );
	}

	void transform::set_position( vec3_t value )
	{
		if( !g_cheat.local
			|| !g_cheat.camera_ptr 
			|| g_cheat.player_list.empty( ) )
			return;

		uintptr_t transform = reinterpret_cast< uintptr_t >( this );
		if( !transform )
			return;

		uintptr_t method = offsets::transform_set_position;
		if( !method )
			return;

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
			return;

		auto set_transform_position = reinterpret_cast< void( * )( uintptr_t transform, vec3_t value ) >( method_ptr );
		spoof_ret( set_transform_position, transform, value );
	}

	uintptr_t get_texture( uintptr_t sprite )
	{
		uintptr_t method = offsets::get_texture;
		if( !method )
			return NULL;

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
			return NULL;

		auto get_texture = reinterpret_cast< uintptr_t( * )( uintptr_t ) >( method_ptr );
		return spoof_ret( get_texture, sprite );
	}

	vec3_t transform::inverse_tranform_point( vec3_t point )
	{
		uintptr_t transform = reinterpret_cast< uintptr_t >( this );
		if( !transform )
			return vec3_t( );

		uintptr_t method = offsets::transform_inverse_transform_point; //il2mgr::method( xs( "transform" ), xs( "InverseTransformPoint" ), 1, xs( "UnityEngine" ) );
		if( !method )
		{
			return vec3_t( );
		}

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
		{
			return vec3_t( );
		}

		auto inverse_tranform_point = reinterpret_cast< vec3_t( * )( uintptr_t transform, vec3_t position ) >( method_ptr );
		return inverse_tranform_point( transform, point );
	}

	vec3_t transform::transform_direction( vec3_t direction )
	{
		uintptr_t transform = reinterpret_cast< uintptr_t >( this );
		if( !transform )
			return vec3_t( );

		uintptr_t method = offsets::transform_transform_direction; //il2mgr::method( xs( "transform" ), xs( "InverseTransformPoint" ), 1, xs( "UnityEngine" ) );
		if( !method )
			return vec3_t( );

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
			return vec3_t( );

		auto inverse_tranform_point = reinterpret_cast< vec3_t( * )( uintptr_t transform, vec3_t position ) >( method_ptr );
		return inverse_tranform_point( transform, direction );
	}

	vec3_t transform::up( ) {
		uintptr_t transform = reinterpret_cast< uintptr_t >( this );
		if( !transform )
			return vec3_t( );

		uintptr_t method = offsets::get_transform_up;
		if( !method )
			return vec3_t( );

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
			return vec3_t( );

		auto get_up = reinterpret_cast< vec3_t( * )( uintptr_t ) >( method_ptr );
		return spoof_ret( get_up, transform );
	}

	bool item::is_deployed( ) {
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return false;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held )
			return false;

		uintptr_t address = offsets::heldentity_isdeployed;
		if( !address )
			return false;

		return *reinterpret_cast< bool* >( held + address );
	}
	
	void item::set_was_aiming( bool value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held )
			return;

		uintptr_t method = offsets::bowweapon_wasAiming;
		if( !method )
			return;

		std::wstring item_name = get_short_name( );
		if( item_name.find( xs( L"bow.compound" ) ) != std::string::npos
			|| item_name.find( xs( L"cross" ) ) != std::string::npos )
			return;

		*reinterpret_cast< bool* >( held + method ) = value; // attack ready
	}

	//int item::get_projectile_velocity_scale( bool get_max )
	//{
	//	uintptr_t entity = reinterpret_cast< uintptr_t >( this );
	//	if( !entity )
	//		return 69;

	//	uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
	//	if( !held )
	//		return 69;

	//	base_projectile* base_proj = reinterpret_cast< base_projectile* >( held );
	//	if( !base_proj )
	//		return 69;

	//	uintptr_t method = offsets::get_projectile_velocity_scale;
	//	if( !method )
	//		return 69;

	//	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	//	if( !method_ptr )
	//		return 69;

	//	auto get_projectile_velocity_scale = reinterpret_cast< int( * )( base_projectile*, bool ) >( method_ptr );
	//	return spoof_ret( get_projectile_velocity_scale, base_proj, get_max );
	//}

	void item::set_aiming_while_cycling( bool value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held )
			return;

		base_projectile* base_proj = reinterpret_cast< base_projectile* >( held );
		if( !base_proj )
			return;

		uintptr_t method = offsets::noAimingWhileCycling;
		if( !method )
			return;

		*reinterpret_cast< bool* >( reinterpret_cast< uintptr_t >( base_proj ) + method ) = value;
	}

	void item::set_projectile_velocity_scale( float value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held )
			return;

		base_projectile* base_proj = reinterpret_cast< base_projectile* >( held );
		if( !base_proj )
			return;

		uintptr_t method = offsets::projectile_velocity_scale;
		if( !method )
			return;

		*reinterpret_cast< float* >( reinterpret_cast< uintptr_t >( base_proj ) + method ) = value;
	}

	void item::set_projectile_distance_scale( float value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held )
			return;

		base_projectile* base_proj = reinterpret_cast< base_projectile* >( held );
		if( !base_proj )
			return;

		uintptr_t method = offsets::projectile_distance_scale;
		if( !method )
			return;

		*reinterpret_cast< float* >( reinterpret_cast< uintptr_t >( base_proj ) + method ) = value;
	}

	float item::get_projectile_velocity_scale( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return 0.f;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held )
			return 0.f;

		base_projectile* base_proj = reinterpret_cast< base_projectile* >( held );
		if( !base_proj )
			return 0.f;

		uintptr_t method = offsets::projectile_velocity_scale;
		if( !method )
			return 0.f;

		return *reinterpret_cast< float* >( reinterpret_cast< uintptr_t >( base_proj ) + method );
	}

	void item::set_attack_ready( bool value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held )
			return;

		uintptr_t method = offsets::bowweapon_attackReady;
		if( !method )
			return;

		std::wstring item_name = get_short_name( );
		if( item_name.find( xs( L"bow.compound" ) ) != std::string::npos
			|| item_name.find( xs( L"cross" ) ) != std::string::npos )
			return;

		*reinterpret_cast< bool* >( held + method ) = value; // attack ready
	}

	void item::set_did_spark_this_frame( bool value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held )
			return;

		uintptr_t method = offsets::flintstrikeweapon_didSparkThisFrame;
		if( !method )
			return;

		auto item_name = get_short_name( );

		if( item_name.find( xs( L"eoka" ) ) != std::string::npos )
			*reinterpret_cast< bool* >( held + method ) = value;
	}

	float item::get_attack_max_distance( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return 0.f;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held )
			return 0.f;

		uintptr_t method = offsets::basemelee_maxDistance;
		if( !method )
			return 0.f;

		return *reinterpret_cast< float* >( held + method ); // attack radius
	}

	void item::set_attack_max_distance( float value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held )
			return;

		uintptr_t method = offsets::basemelee_maxDistance;
		if( !method )
			return;

		uintptr_t address_second = offsets::basemelee_attack_radius;
		if( !method )
			return;

		*reinterpret_cast< float* >( held + method ) = value; // attack radius
		*reinterpret_cast< float* >( held + address_second ) = value;
	}

	std::wstring item::get_weapon_name( ) {
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return std::wstring( );

		uintptr_t item_def = *reinterpret_cast< uintptr_t* >( entity + offsets::item_info );
		if( !item_def )
			return std::wstring( );

		uintptr_t display_name = *reinterpret_cast< uintptr_t* >( item_def + offsets::itemdefinition_displayName );
		if( !display_name )
			return std::wstring( );

		str_ing* weapon_name = *reinterpret_cast< str_ing** >( display_name + 0x18 );
		if( !weapon_name )
			return std::wstring( );

		return weapon_name->str;
	}

	std::string player_name_id::get_user_name( ) {
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return std::string( );

		uintptr_t address = offsets::player_name_id_username;
		if( !address )
			return std::string( );

		uintptr_t text = *reinterpret_cast< uintptr_t* >( entity + address );
		if( !text )
			return std::string( );

		return g_sdk.read_ascii( text );
	}

	void item::send_broadcast_projectile( Signal signal, const char* text )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held )
			return;

		base_projectile* base_proj = reinterpret_cast< base_projectile* >( held );
		if( !base_proj )
			return;

		base_proj->send_signal_broadcast( signal, text );
	}

	std::wstring base_entity::get_name( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return std::wstring( );

		uintptr_t address = offsets::item_info;
		if( !address )
			return std::wstring( );

		uintptr_t info = *reinterpret_cast< uintptr_t* >( entity + address );
		if( !info )
			return std::wstring( );

		uintptr_t second_address = offsets::itemdefinition_displayName;
		if( !second_address )
			return std::wstring( );

		il2mgr::il2cppstring* entity_name = *reinterpret_cast< il2mgr::il2cppstring** >( info + second_address );
		if( !entity_name )
			return std::wstring( );

		return entity_name->buffer;
	}

	item* base_entity::get_world_item( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return NULL;
		
		uintptr_t method = offsets::worldItem_item;
		if( !method )
			return NULL;

		return *reinterpret_cast< item** >( entity + method );
	}

	std::wstring base_entity::get_item_name( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return std::wstring( );

		uintptr_t address = offsets::item_info;
		if( !address )
			return std::wstring( );

		uintptr_t info = *reinterpret_cast< uintptr_t* >( entity + address );
		if( !info )
			return std::wstring( );

		uintptr_t second_address = offsets::itemdefinition_shortname;
		if( !second_address )
			return std::wstring( );

		uintptr_t entity_name = *reinterpret_cast< uintptr_t* >( info + second_address );
		if( !entity_name )
			return std::wstring( );

		auto item_name = g_sdk.read_unicode( entity_name + 0x14, 64 );
		if( item_name.empty( ) )
			return std::wstring( );

		return item_name;
	}

	float base_entity::get_protected_minutes( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return 0.f;

		uintptr_t address = offsets::building_privlidge_cachedProtectedMinutes;
		if( !address )
			return 0.f;

		return *reinterpret_cast< float* >( entity + address );
	}

	std::string base_entity::get_prefab_name( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return std::string( );

		uintptr_t class_name_ptr = *reinterpret_cast< uintptr_t* >( entity + 0x60 );
		if( !class_name_ptr )
			return std::string( );

		return g_sdk.read_ascii( class_name_ptr, 128 );
	}

	std::string base_entity::get_prefab_namehash( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return std::string( );

		auto object_name_ptr = *reinterpret_cast< uintptr_t* >( entity + offsets::prefab );

		if( !object_name_ptr )
			return std::string( );

		if( g_sdk.read_ascii( object_name_ptr ).empty( ) )
			return std::string( );

		return reinterpret_cast< const char* >( object_name_ptr );
	}

	std::string base_entity::get_class_name( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return std::string( );

		uintptr_t object_unk = *reinterpret_cast< uintptr_t* >( entity );
		if( !object_unk )
			return std::string( );

		uintptr_t class_name_ptr = *reinterpret_cast< uintptr_t* >( object_unk + 0x10 );
		if( !class_name_ptr )
			return std::string( );

		return g_sdk.read_ascii( class_name_ptr );
	}

	vec3_t base_entity::get_visual_position( uintptr_t object_class )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return vec3_t( );

		uintptr_t player_visual = *reinterpret_cast< uintptr_t* >( object_class + sizeof( uint64_t ) );
		if( !player_visual )
			return vec3_t( );

		uintptr_t visual_state = *reinterpret_cast< uintptr_t* >( player_visual + 0x38 );
		if( !visual_state )
			return vec3_t( );

		return *reinterpret_cast< vec3_t* >( visual_state + 0x90 );
	}

	vec3_t base_entity::get_closest_point( vec3_t position )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return vec3_t( );

		uintptr_t method = offsets::baseentity_closest_point;
		if( !method )
			return vec3_t( );

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
			return vec3_t( );

		auto get_ClosestPoint = reinterpret_cast< vec3_t( * )( uintptr_t entity, vec3_t position ) >( method_ptr );
		return get_ClosestPoint( entity, position );
	}

	transform* base_entity::get_transform( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return nullptr;

		uintptr_t method = offsets::component_get_transform;
		if( !method )
			return nullptr;

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
			return nullptr;

		auto get_transform = reinterpret_cast< transform * ( * )( uintptr_t entity ) >( method_ptr );
		return spoof_ret( get_transform, entity );
	}

	float base_entity::get_max_speed( ) {
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return 0.0;

		uintptr_t method = offsets::get_max_speed;
		if( !method )
			return 0.0;

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
			return 0.0;

		auto max_speed = reinterpret_cast< float( * )( uintptr_t ) >( method_ptr );
		return spoof_ret( max_speed, entity );
	}

	void base_entity::set_hit_direction( vec3_t value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t address = offsets::treeentity_hit_direction;
		if( !address )
			return;

		*reinterpret_cast< vec3_t* >( entity + address ) = value;
	}

	float base_combat_entity::get_health( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return 0.f;

		uintptr_t address = offsets::basecombatentity__health;
		if( !address )
			return 0.f;

		return *reinterpret_cast< float* >( entity + address );
	}

	float stash_container::get_burried_offset( ) {
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return 0.f;

		uintptr_t address = offsets::stashcontainer_burriedOffset;
		if( !address )
			return 0.f;

		return *reinterpret_cast< float* >( entity + address );
	}

	void base_entity::server_rpc( const char* rpc )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t method = offsets::baseentity_serverrpc_1arg;
		if( !method )
			return;

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
			return;

		auto ServerRPC = reinterpret_cast< void ( * )( uintptr_t, il2mgr::il2cppstring* ) >( method_ptr );
		spoof_ret( ServerRPC, entity, il2mgr::il2cppstring::New( rpc ) );
	}

	void base_entity::server_rpc( uintptr_t entity, const char* rpc, const char* string, bool value )
	{
		uintptr_t method = offsets::baseentity_serverrpc_4arg;
		if( !method )
			return;

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
			return;

		auto ServerRPC = reinterpret_cast< void ( * )( uintptr_t, il2mgr::il2cppstring*, il2mgr::il2cppstring*, bool ) >( method_ptr );
		spoof_ret( ServerRPC, entity, il2mgr::il2cppstring::New( rpc ), il2mgr::il2cppstring::New( string ), value );
	}

	void base_entity::server_rpc( uintptr_t entity, const char* rpc )
	{
		uintptr_t method = offsets::baseentity_serverrpc_1arg;
		if( !method )
			return;

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
			return;

		auto ServerRPC = reinterpret_cast< void ( * )( uintptr_t, il2mgr::il2cppstring* ) >( method_ptr );
		spoof_ret( ServerRPC, entity, il2mgr::il2cppstring::New( rpc ) );
	}

	void base_entity::send_signal_broadcast( Signal signal, const char* arg )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t method = offsets::baseentity_sendsignalbroadcast;
		if( !method )
			return;

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
			return;

		auto ServerRPC = reinterpret_cast< void ( * )( uintptr_t, Signal, il2mgr::il2cppstring* ) >( method_ptr );
		spoof_ret( ServerRPC, entity, signal, il2mgr::il2cppstring::New( arg ) );
	}

	float base_combat_entity::get_max_health( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return 0.f;

		uintptr_t address = offsets::basecombatentity__maxHealth;
		if( !address )
			return 0.f;

		return *reinterpret_cast< float* >( entity + address );
	}

	void item::set_bullet_thickness( float value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;
		
		uintptr_t address = offsets::projectile_thickness;
		if( !address )
			return;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held )
			return;

		base_projectile* base_proj = reinterpret_cast< base_projectile* >( held );
		if( !base_proj )
			return;

		uintptr_t created_projectiles = *reinterpret_cast< uintptr_t* >( ( uintptr_t )base_proj + offsets::baseprojectile_createdProjectiles );
		if( !created_projectiles )
			return;

		int size = *reinterpret_cast< int* >( created_projectiles + 0x18 );
		for( int i = 0; i < size; i++ ) {
			uintptr_t projectile = *reinterpret_cast< uintptr_t* >( static_cast< uintptr_t >( created_projectiles + 0x10 ) 
				+ 0x20 + ( i * sizeof( uint64_t ) ) );
			if( !projectile )
				continue;

			*reinterpret_cast< float* >( projectile + address ) = value;
		}
	}

	int base_combat_entity::get_life_state( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return 1;

		uintptr_t address = offsets::basecombatentity_lifestate;
		if( !address )
			return 1;

		return *reinterpret_cast< int* >( entity + address );
	}

	void player_walk_movement::set_was_falling( bool value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t address = offsets::playerwalkmovement_wasFalling;
		if( !address )
			return;

		*reinterpret_cast< bool* >( entity + address ) = value;
	}
	
	void player_walk_movement::teleport_to( vec3_t value )
	{
		if( !g_cheat.local )
			return;

		if( g_cheat.local->get_life_state( ) )
			return;

		uintptr_t transform = reinterpret_cast< uintptr_t >( this );
		if( !transform )
			return;

		uintptr_t method = offsets::playerwalkmovement_TeleportTo;
		if( !method )
			return;

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
			return;

		auto set_teleport_to = reinterpret_cast< void( * )( player_walk_movement*, vec3_t, base_player* ) >( method_ptr );
		spoof_ret( set_teleport_to, this, value, g_cheat.local );
	}

	void player_walk_movement::set_previous_velocity( vec3_t value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t address = offsets::playerwalkmovement_previousVelocity;
		if( !address )
			return;

		*reinterpret_cast< vec3_t* >( entity + address ) = value;
	}

	bool player_walk_movement::swimming( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return 1;

		uintptr_t address = offsets::playerwalkmovement_swimming;
		if( !address )
			return 1;

		return *reinterpret_cast< bool* >( entity + address );
	}

	void player_walk_movement::set_grounded( bool value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t address = offsets::playerwalkmovement_grounded;
		if( !address )
			return;

		*reinterpret_cast< bool* >( entity + address ) = value;
	}
		
	void player_walk_movement::set_flying( bool value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t address = offsets::playerwalkmovement_flying;
		if( !address )
			return;

		*reinterpret_cast< bool* >( entity + address ) = value;
	}

	bool player_walk_movement::flying( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return 1;

		uintptr_t address = offsets::playerwalkmovement_flying;
		if( !address )
			return 1;

		return *reinterpret_cast< bool* >( entity + address );
	}

	bool player_walk_movement::ducking( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return 1;

		uintptr_t address = offsets::playerwalkmovement_ducking;
		if( !address )
			return 1;

		return *reinterpret_cast< bool* >( entity + address );
	}

	void player_walk_movement::set_speed( float value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		*reinterpret_cast< float* >( entity + 0x40 ) = value;
	}

	void player_walk_movement::set_ground_angle( float angle )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t address = offsets::playerwalkmovement_groundAngle;
		if( !address )
			return;

		*reinterpret_cast< float* >( entity + address ) = angle;
	}

	float player_walk_movement::get_ground_time( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return 1.f;

		uintptr_t address = offsets::playerwalkmovement_groundTime;
		if( !address )
			return 1.f;

		return *reinterpret_cast< float* >( entity + address );
	}

	void player_walk_movement::set_gravity_test_radius( float angle )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t address = offsets::playerwalkmovement_gravityTestRadius;
		if( !address )
			return;

		*reinterpret_cast< float* >( entity + address ) = angle;
	}

	void player_walk_movement::set_ground_angle_new( float angle )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t address = offsets::playerwalkmovement_groundAngleNew;
		if( !address )
			return;

		*reinterpret_cast< float* >( entity + address ) = angle;
	}

	float player_walk_movement::get_ground_angle_new( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return 0.f;

		uintptr_t address = offsets::playerwalkmovement_groundAngleNew;
		if( !address )
			return 0.f;

		return *reinterpret_cast< float* >( entity + address );
	}

	float player_walk_movement::get_capsule_height( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return 0.f;

		uintptr_t address = offsets::playerwalkmovement_capsuleHeight;
		if( !address )
			return 0.f;

		return *reinterpret_cast< float* >( entity + address );
	}

	void player_walk_movement::set_capsule_height( float angle )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t address = offsets::playerwalkmovement_capsuleHeight;
		if( !address )
			return;

		*reinterpret_cast< float* >( entity + address ) = angle;
	}

	void player_walk_movement::set_capsule_center( float angle )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t address = offsets::playerwalkmovement_capsuleCenter;
		if( !address )
			return;

		*reinterpret_cast< float* >( entity + address ) = angle;
	}

	float player_walk_movement::get_capsule_center( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return 0.f;

		uintptr_t address = offsets::playerwalkmovement_capsuleCenter;
		if( !address )
			return 0.f;

		return *reinterpret_cast< float* >( entity + address );
	}

	void player_walk_movement::set_capsule_radius( float angle )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t address = offsets::playerwalkmovement_capsule_radius;
		if( !address )
			return;

		*reinterpret_cast< float* >( entity + address ) = angle;
	}

	void player_walk_movement::set_is_grounded( float value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		*reinterpret_cast< bool* >( entity + 0x140 ) = value; // grounded

		*reinterpret_cast< float* >( entity + 0x4C ) = value;
	}

	void player_walk_movement::set_is_running( float value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t address = offsets::playerwalkmovement_running;
		if( !address )
			return;

		*reinterpret_cast< float* >( entity + address ) = value;
	}

	void player_walk_movement::set_max_angle_walking( float angle )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t address = offsets::playerwalkmovement_maxAngleWalking;
		if( !address )
			return;

		*reinterpret_cast< float* >( entity + address ) = angle;
	}

	void player_walk_movement::set_max_angle_climbing( float angle )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t address = offsets::playerwalkmovement_maxAngleClimbing;
		if( !address )
			return;

		*reinterpret_cast< float* >( entity + address ) = angle;
	}

	void player_walk_movement::set_ground_time( float time )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t address = offsets::playerwalkmovement_groundTime;
		if( !address )
			return;

		*reinterpret_cast< float* >( entity + address ) = time;
	}

	void player_walk_movement::set_gravity_multiplier( float multiplier )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t address = offsets::playerwalkmovement_gravityMultiplier;
		if( !address )
			return;

		*reinterpret_cast< float* >( entity + address ) = multiplier;
	}

	void player_walk_movement::set_jump_time( float time )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t address = offsets::playerwalkmovement_jumpTime;
		if( !address )
			return;

		*reinterpret_cast< float* >( entity + address ) = time;
	}

	void player_walk_movement::set_land_time( float time )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t address = offsets::playerwalkmovement_landTime;
		if( !address )
			return;

		*reinterpret_cast< float* >( entity + address ) = time;
	}

	vec3_t player_walk_movement::get_targetmovement( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return vec3_t( );

		return *reinterpret_cast< vec3_t* >( entity + 0x34 );
	}

	void player_walk_movement::set_targetmovement( vec3_t new_val )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		*reinterpret_cast< vec3_t* >( entity + 0x34 ) = new_val;
	}

	void rigid_body::set_velocity( vec3_t val )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t method = offsets::rigidbody_setVelocity;
		if( !method )
			return;

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
			return;

		auto set_velocity = reinterpret_cast< void( * )( uintptr_t, vec3_t ) >( method_ptr );
		return spoof_ret( set_velocity, entity, val );
	}

	rigid_body* player_walk_movement::get_body( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return nullptr;

		return *reinterpret_cast< rigid_body** >( entity + 0xA0 );
	}

	vec2_t player_input::get_view_angles( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return vec2_t( );

		uintptr_t address = offsets::playerinput_bodyAngles;
		if( !address )
			return vec2_t( );

		return *reinterpret_cast< vec2_t* >( entity + address );
	}

	vec2_t player_input::get_recoil_angles( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return vec2_t( );

		uintptr_t address = il2mgr::value( xs( "PlayerInput" ), xs( "recoilAngles" ) );
		if( !address )
			return vec2_t( );

		return *reinterpret_cast< vec2_t* >( entity + address );
	}

	void player_input::set_view_angles( vec2_t angle )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t address = offsets::playerinput_bodyAngles;
		if( !address )
			return;

		*reinterpret_cast< vec2_t* >( entity + address ) = angle;
	}

	void player_input::set_head_rotation( vec4_t angle )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t address = offsets::playerinput_headRotation;
		if( !address )
			return;

		*reinterpret_cast< vec4_t* >( entity + address ) = angle;
	}

	void player_input::set_recoil_angles( vec2_t angle )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t address = il2mgr::value( xs( "PlayerInput" ), xs( "recoilAngles" ) );
		if( !address )
			return;

		*reinterpret_cast< vec2_t* >( entity + address ) = angle;
	}

	input_state* player_input::get_input_state( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return NULL;

		uintptr_t address = il2mgr::value( xs( "PlayerInput" ), xs( "state" ) );
		if( !address )
			return NULL;

		return *reinterpret_cast< input_state** >( entity + address );
	}

	input_message* input_state::get_input_message( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return NULL;

		uintptr_t address = il2mgr::value( xs( "InputState" ), xs( "current" ) );
		if( !address )
			return NULL;

		return *reinterpret_cast< input_message** >( entity + address );
	}

	void input_message::set_aim_angles( vec3_t value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t address = il2mgr::value( xs( "InputMessage" ), xs( "aimAngles" ) );
		if( !address )
			return;

		*reinterpret_cast< vec3_t* >( entity + address ) = value;
	}

	int item_definition::get_itemid( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return 0;

		return *reinterpret_cast< int* >( entity + offsets::itemdefinition_itemid );
	}

	std::wstring item_definition::get_shortname( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return std::wstring( );

		il2mgr::il2cppstring* entity_name = *reinterpret_cast< il2mgr::il2cppstring** >( entity + offsets::itemdefinition_displayName );
		if( !entity_name )
			return std::wstring( );

		return entity_name->buffer;
	}

	void item::set_can_attack( float value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held )
			return;

		*reinterpret_cast< bool* >( entity + offsets::CanAttack ) = value;
	}

	void item::set_is_automatic( bool value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held )
			return;

		uintptr_t method = offsets::baseprojectile_automatic;
		if( !method )
			return;

		*reinterpret_cast< bool* >( held + method ) = value;
	}

	void item::set_is_burst( bool value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held )
			return;

		uintptr_t method = offsets::baseprojectile_is_burst;
		if( !method )
			return;

		*reinterpret_cast< bool* >( held + method ) = value;
	}

	base_entity* item::get_held_entity( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return nullptr;

		return *reinterpret_cast< base_entity** >( entity + offsets::item_heldEntity );
	}

	int base_projectile::Magazine::get_ammotype( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return 1;

		uintptr_t method = offsets::magazine_ammoType;
		if( !method )
			return 1;

		return *reinterpret_cast< int* >( entity + method );
	}

	int& base_projectile::Magazine::contents( )
	{
		return *reinterpret_cast< int* >( ( uintptr_t )this + offsets::magazine_contents );
	}

	base_projectile::Magazine* base_projectile::get_primaryMagazine( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return NULL;

		return *reinterpret_cast< base_projectile::Magazine** >( entity + offsets::baseprojectile_primaryMagazine );
	}

	void base_projectile::update_ammo_display( ) {
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;
		
		uintptr_t method = offsets::baseprojectile_UpdateAmmoDisplay;
		if( !method )
			return;

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
			return;

		auto shot_fired = reinterpret_cast< void( * )( uintptr_t ) >( method_ptr );
		spoof_ret( shot_fired, entity );
	}

	void base_projectile::did_attack_clientside( ) {
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;
		
		uintptr_t method = offsets::baseprojectile_DidAttackClientside;
		if( !method )
			return;

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
			return;

		auto shot_fired = reinterpret_cast< void( * )( uintptr_t ) >( method_ptr );
		spoof_ret( shot_fired, entity );
	}

	void base_projectile::begin_cycle( ) {
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;
		
		uintptr_t method = offsets::baseprojectile_BeginCycle;
		if( !method )
			return;

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
			return;

		auto shot_fired = reinterpret_cast< void( * )( uintptr_t ) >( method_ptr );
		spoof_ret( shot_fired, entity );
	}

	void base_projectile::launch_projectile( ) {
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;
		
		uintptr_t method = offsets::baseprojectile_LaunchProjectile;
		if( !method )
			return;

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
			return;

		auto shot_fired = reinterpret_cast< void( * )( uintptr_t ) >( method_ptr );
		spoof_ret( shot_fired, entity );
	}

	void base_projectile::shot_fired( ) {
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;
		
		uintptr_t method = offsets::baseprojectile_ShotFired;
		if( !method )
			return;

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
			return;

		auto shot_fired = reinterpret_cast< void( * )( uintptr_t ) >( method_ptr );
		spoof_ret( shot_fired, entity );
	}

	float item::get_bullet_velocity( )
	{		
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return 0.f;
		
		if( is_melee( ) )
			return 0.f;

		auto weapon_name = g_sdk.ws2s( this->get_short_name( ) );
		auto bullet_name = this->get_bullet_name( );

		/* rifle ammo */

		if( weapon_name == xs( "rifle.ak" )
			|| weapon_name == xs( "rifle.lr300" ) )
		{

			if( bullet_name == xs( "ammo.rifle" ) )
			{
				return 375.f;
			}
			if( bullet_name == xs( "ammo.rifle.hv" ) )
			{
				return 450.f;
			}
			if( bullet_name == xs( "ammo.rifle.explosive" ) )
			{
				return 225.f;
			}
			if( bullet_name == xs( "ammo.rifle.incendiary" ) )
			{
				return 225.f;
			}
		}

		if( weapon_name == xs( "rifle.bolt" ) )
		{
			if( bullet_name == xs( "ammo.rifle" ) )
			{
				return 656.f;
			}
			if( bullet_name == xs( "ammo.rifle.hv" ) )
			{
				return 788.f;
			}
			if( bullet_name == xs( "ammo.rifle.incendiary" )
				|| bullet_name == xs( "ammo.rifle.explosive" ) )
			{
				return 394.f;
			}
		}

		if( weapon_name == xs( "rifle.l96" ) )
		{
			if( bullet_name == xs( "ammo.rifle" ) )
			{
				return 1125.f;
			}
			if( bullet_name == xs( "ammo.rifle.hv" ) )
			{
				return 1350.f;
			}
			if( bullet_name == xs( "ammo.rifle.explosive" )
				|| bullet_name == xs( "ammo.rifle.incendiary" ) )
			{
				return 675.f;
			}
		}

		if( weapon_name == xs( "rifle.m39" ) )
		{
			if( bullet_name == xs( "ammo.rifle" ) )
			{
				return 469.f;
			}
			if( bullet_name == xs( "ammo.rifle.hv" ) )
			{
				return 563.f;
			}
			if( bullet_name == xs( "ammo.rifle.explosive" )
				|| bullet_name == xs( "ammo.rifle.incendiary" ) )
			{
				return 281.f;
			}
		}

		if( weapon_name == xs( "rifle.semiauto" ) )
		{
			if( bullet_name == xs( "ammo.rifle" ) )
			{
				return 375.f;
			}
			if( bullet_name == xs( "ammo.rifle.hv" ) )
			{
				return 450.f;
			}
			if( bullet_name == xs( "ammo.rifle.incendiary" )
				|| bullet_name == xs( "ammo.rifle.explosive" ) )
			{
				return 225.f;
			}
		}

		if( weapon_name == xs( "lmg.m249" ) )
		{
			if( bullet_name == xs( "ammo.rifle" ) )
			{
				return 487.5f;
			}
			if( bullet_name == xs( "ammo.rifle.hv" ) )
			{
				return 585.f;
			}
			if( bullet_name == xs( "ammo.rifle.explosive" )
				|| bullet_name == xs( "ammo.rifle.incendiary" ) )
			{
				return 293.f;
			}
		}

		if( weapon_name == xs( "hmlmg" ) )
		{
			if( bullet_name == xs( "ammo.rifle" ) )
			{
				return 487.5f;
			}
			if( bullet_name == xs( "ammo.rifle.hv" ) )
			{
				return 585.f;
			}
			if( bullet_name == xs( "ammo.rifle.explosive" )
				|| bullet_name == xs( "ammo.rifle.incendiary" ) )
			{
				return 293.f;
			}
		}

		/* pistol ammo */

		if( weapon_name == xs( "smg.2" )
			|| weapon_name == xs( "smg.mp5" ) )
		{

			if( bullet_name == xs( "ammo.pistol" ) )
			{
				return 240.f;
			}
			if( bullet_name == xs( "ammo.pistol.hv" ) )
			{
				return 320.f;
			}
			if( bullet_name == xs( "ammo.pistol.incendiary" ) )
			{
				return 180.f;
			}
		}

		if( weapon_name == xs( "pistol.m92" )
			|| weapon_name == xs( "pistol.python" )
			|| weapon_name == xs( "pistol.revolver" )
			|| weapon_name == xs( "pistol.semiauto" ) 
			|| weapon_name == xs( "smg.thompson" ) )
		{

			if( bullet_name == xs( "ammo.pistol" ) )
			{
				return 300.f;
			}
			if( bullet_name == xs( "ammo.pistol.hv" ) )
			{
				return 400.f;
			}
			if( bullet_name == xs( "ammo.pistol.incendiary" ) )
			{
				return 225.f;
			}
		}

		/* shotgun ammo */

		if( weapon_name == xs( "shotgun.double" )
			|| weapon_name == xs( "shotgun.pump" )
			|| weapon_name == xs( "shotgun.waterpipe" )
			|| weapon_name == xs( "shotgun.spas12" )
			|| weapon_name == xs( "pistol.eoka" ) )
		{
			if( bullet_name == xs( "ammo.shotgun.slug" ) )
			{
				return 225.f;
			}
			if( bullet_name == xs( "ammo.shotgun.fire" )
				|| bullet_name == xs( "ammo.handmade.shell" ) )
			{
				return 100.f;
			}
		}

		/* monkey arrows and monkey guns */

		if( weapon_name == xs( "bow.hunting" ) )
		{
			if( bullet_name == xs( "arrow.hv" ) )
			{
				return 80.f;
			}
			if( bullet_name == xs( "arrow.bone" ) )
			{
				return 45.f;
			}
			if( bullet_name == xs( "arrow.wooden" ) )
			{
				return 50.f;
			}
			if( bullet_name == xs( "arrow.fire" ) )
			{
				return 40.f;
			}
		}

		if( weapon_name == xs( "bow.compound" ) )
		{
			if( bullet_name == xs( "arrow.hv" ) )
			{
				return 160.f;
			}
			if( bullet_name == xs( "arrow.bone" ) )
			{
				return 90.f;
			}
			if( bullet_name == xs( "arrow.wooden" ) )
			{
				return 50.f;
			}
			if( bullet_name == xs( "arrow.fire" ) )
			{
				return 80.f;
			}
		}

		if( weapon_name == xs( "crossbow" ) )
		{
			if( bullet_name == xs( "arrow.hv" ) )
			{
				return 120.f;
			}
			if( bullet_name == xs( "arrow.bone" ) )
			{
				return 68.f;
			}
			if( bullet_name == xs( "arrow.wooden" ) )
			{
				return 75.f;
			}
			if( bullet_name == xs( "arrow.fire" ) )
			{
				return 60.f;
			}
		}

		if( weapon_name == xs( "pistol.nailgun" ) )
		{
			return 50.f;
		}

		return 1337.f;
	}

	weapon_information item::get_weapon_information( )
	{
		if( !this )
			return weapon_information( );

		weapon_information info_return{ this->bullet_gravity( ), this->get_bullet_velocity( ), this->get_bullet_drag( ) };

		//auto bullet_name = this->get_bullet_name( );

		//if( bullet_name.find( xs( "explosive" ) ) != std::string::npos
  //          || bullet_name.find( xs( "incendiary" ) ) != std::string::npos )
		//	return info_return;

		//uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		//if( !entity )
		//	return info_return;

		//uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		//if( !held )
		//	return info_return;

		//uintptr_t address = offsets::baseprojectile_primaryMagazine;
		//if( !address )
		//	return info_return;

		//uintptr_t address_third = offsets::itemmodprojectile_projectileVelocity;
		//if( !address_third )
		//	return info_return;

		//uintptr_t magazine = *reinterpret_cast< uintptr_t* >( held + address );
		//if( !magazine )
		//	return info_return;

		//uintptr_t unity_class = memory::read_chain< uintptr_t >( magazine, { 0x20, 0x10, 0x30 } );
		//if( !unity_class )
		//	return info_return;

		//uintptr_t item_mod = g_sdk.get_component( unity_class, xs( "ItemModProjectile" ) );
		//if( !item_mod )
		//	return info_return;

		//uintptr_t projectile_class = memory::read_chain< uintptr_t >( item_mod, { 0x18, 0x18, 0x10 } );
		//if( !projectile_class )
		//	return info_return;

		//projectile* proj = *reinterpret_cast< projectile** >( g_sdk.get_component( projectile_class, xs( "Projectile" ) ) );
		//if( !proj )
		//	return info_return;

		//float gravity = proj->get_gravity_modifier( );
		//if( !gravity )
		//	return info_return;

		//info_return.drag = proj->get_drag( );
		//info_return.bullet_gravity = *reinterpret_cast< float* >( item_mod + address_third );

		return info_return;
	}

	vec3_t player_model::get_position( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return vec3_t( );

		return *reinterpret_cast< vec3_t* >( entity + offsets::playermodel_position );
	}

	void player_model::set_position( vec3_t new_pos )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return;

		*reinterpret_cast< vec3_t* >( entity + offsets::playermodel_position ) = new_pos;
	}

	vec3_t player_model::get_velocity( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return vec3_t( );

		return *reinterpret_cast< vec3_t* >( entity + offsets::playermodel_newVelocity );
	}

	uintptr_t player_model::get_multimesh( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return NULL;

		uintptr_t multi_mesh = *reinterpret_cast< uintptr_t* >( entity + offsets::playermodel_multimesh );

		if( !multi_mesh )
			return NULL;

		return multi_mesh;
	}

	void player_model::disable_hands( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return;

		*reinterpret_cast< bool* >( entity + offsets::Nohands ) = true;
	}

	void player_model::set_velocity( vec3_t new_velo )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return;

		*reinterpret_cast< vec3_t* >( entity + offsets::playermodel_newVelocity ) = new_velo;
	}
	
	void model_state::set_sprinting( bool value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t method = offsets::modelstate_set_sprinting;
		if( !method )
			return;

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
			return;

		auto onLadder = reinterpret_cast< void( * )( uintptr_t, bool ) >( method_ptr );
		spoof_ret( onLadder, entity, value );
	}

	void model_state::set_onLadder( bool value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t method = offsets::modelstate_set_onLadder;
		if( !method )
			return;

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
			return;

		auto onLadder = reinterpret_cast< void( * )( uintptr_t, bool ) >( method_ptr );
		return spoof_ret( onLadder, entity, value );
	}

	bool model_state::get_ducked( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return false;

		uintptr_t method = offsets::get_ducked;
		if( !method )
			return false;

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
			return false;

		auto get_ducked = reinterpret_cast< bool( * )( uintptr_t ) >( method_ptr );
		return spoof_ret( get_ducked, entity );
	}

	void model_state::set_water_level( int value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t method = offsets::waterLevel;
		if( !method )
			return;

		*reinterpret_cast< int* >( entity + method ) = value;
	}

	void model_state::Setfly( bool value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t method = offsets::SetFlying;
		if( !method )
		{
			return;
		}

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
		{
			return;
		}
		auto onLadder = reinterpret_cast< void( * )( uintptr_t, bool ) >( method_ptr );
		spoof_ret( onLadder, entity, value );
	}

	void model_state::InteractiveDebug( bool value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t method = offsets::SetMounted;
		if( !method )
			return;

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
			return;

		auto onLadder = reinterpret_cast< void( * )( uintptr_t, bool ) >( method_ptr );
		spoof_ret( onLadder, entity, value );
	}

	void model_state::remove_flag( int flag )
	{
		int flags = *reinterpret_cast< int* >( ( uintptr_t )this + 0x24 );

		flags &= ~flag;

		*reinterpret_cast< int* >( ( uintptr_t )this + 0x24 ) = flags;
	}

	void model_state::add_flag( int flag )
	{
		int flags = *reinterpret_cast< int* >( ( uintptr_t )this + 0x24 );

		*reinterpret_cast< int* >( ( uintptr_t )this + 0x24 ) = flags |= ( int )flag;
	}

	bool model_state::has_flag( int flag )
	{
		int flags = *reinterpret_cast< int* >( ( uintptr_t )this + 0x24 );
		return ( flags & flag );
	}

	bool base_entity::mounted( ) {
		uintptr_t method = offsets::mounted;

		if( !method )
			return false;

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
			return false;

		auto mounted = reinterpret_cast< bool( * )( ) >( method_ptr );
		return spoof_ret( mounted );
	}

	float base_entity::max_velocity( ) {
		if( !this )
			return 0.f;

		if( this->mounted( ) )
			return this->get_max_speed( ) * 4;

		return this->get_max_speed( );
	}

	vec3_t player_eyes::get_position( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return vec3_t( );

		uintptr_t method = offsets::playereyes_get_position;
		if( !method )
			return vec3_t( );

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
			return vec3_t( );

		auto get_up = reinterpret_cast< vec3_t( * )( uintptr_t ) >( method_ptr );
		return spoof_ret( get_up, entity );
	}

	vec3_t player_eyes::get_viewoffset( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return vec3_t( );

		uintptr_t address = offsets::view_offset;
		if( !address )
			return vec3_t( );

		return *reinterpret_cast< vec3_t* >( entity + address );
	}

	vec3_t player_eyes::get_eyeOffset( ) {
		static auto this_class = il2mgr::init_class( xs( "PlayerEyes" ) );
		if( !this_class )
			return vec3_t( );

		return *reinterpret_cast< vec3_t* >( this_class + 0xB8 ); // never write to this value, its a static feild
	}

	vec3_t player_eyes::get_movementforward( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return vec3_t( );

		uintptr_t method = offsets::playereyes_movementforward;
		if( !method )
			return vec3_t( );

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
			return vec3_t( );

		auto movementforward = reinterpret_cast< vec3_t( * )( uintptr_t ) >( method_ptr );
		return spoof_ret( movementforward, entity );
	}

	vec3_t player_eyes::get_movementright( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return vec3_t( );

		uintptr_t method = offsets::playereyes_movementright;
		if( !method )
			return vec3_t( );

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
			return vec3_t( );

		auto movementright = reinterpret_cast< vec3_t( * )( uintptr_t ) >( method_ptr );
		return spoof_ret( movementright, entity );
	}

	vec3_t player_eyes::get_bodyforward( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return vec3_t( );

		uintptr_t method = offsets::playereyes_bodyforward;
		if( !method )
			return vec3_t( );

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
			return vec3_t( );

		auto bodyforward = reinterpret_cast< vec3_t( * )( uintptr_t ) >( method_ptr );
		return spoof_ret( bodyforward, entity );
	}

	vec3_t player_eyes::get_bodyright( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return vec3_t( );

		uintptr_t method = offsets::playereyes_bodyright;
		if( !method )
			return vec3_t( );

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
			return vec3_t( );

		auto bodyright = reinterpret_cast< vec3_t( * )( uintptr_t ) >( method_ptr );
		return spoof_ret( bodyright, entity );
	}

	vec4_t player_eyes::get_rotation( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return vec4_t( );

		uintptr_t method = offsets::playereyes_eye_rotation;
		if( !method )
			return vec4_t( );

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
			return vec4_t( );

		auto bodyright = reinterpret_cast< vec4_t( * )( uintptr_t ) >( method_ptr );
		return spoof_ret( bodyright, entity );
	}

	vec4_t player_eyes::get_body_rotation( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return vec4_t( );

		uintptr_t address = offsets::body_rotation;
		if( !address )
			return vec4_t( );

		return *reinterpret_cast< vec4_t* >( entity + address );
	}

	void player_eyes::set_body_rotation( vec4_t value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t address = offsets::body_rotation;
		if( !address )
			return;

		*reinterpret_cast< vec4_t* >( entity + address ) = value;
	}

	void player_eyes::set_view_offset( vec3_t value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;
		
		uintptr_t address = offsets::view_offset;
		if( !address )
			return;

		*reinterpret_cast< vec3_t* >( entity + address ) = value;
	}

	float item::bullet_gravity( )
	{		
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return 0.f;
		
		if( is_melee( ) )
			return 1.f;

		auto bullet_name = this->get_bullet_name( );

		if( bullet_name == xs( "ammo.rifle.explosive" ) )
		{
			return 1.25f;
		}

		if( bullet_name == xs( "arrow.hv" ) )
		{
			return 0.5f;
		}

		if( bullet_name == xs( "arrow.bone" )
			|| bullet_name == xs( "arrow.wooden" ) )
		{
			return 0.75f;
		}

		if( bullet_name == xs( "ammo.handmade.shell" )
			|| bullet_name == xs( "arrow.fire" )
			|| bullet_name == xs( "ammo.shotgun" )
			|| bullet_name == xs( "ammo.shotgun.fire" )
			|| bullet_name == xs( "ammo.shotgun.slug" )
			|| bullet_name == xs( "ammo.rifle" )
			|| bullet_name == xs( "ammo.rifle.hv" )
			|| bullet_name == xs( "ammo.pistol" )
			|| bullet_name == xs( "ammo.pistol.hv" )
			|| bullet_name == xs( "ammo.pistol.incendiary" )
			|| bullet_name == xs( "ammo.rifle.incendiary" ) )
		{
			return 1.f;
		}

		if( bullet_name == xs( "ammo.nailgun.nails" ) )
		{
			return 0.75f;
		}

		return 1.f;
	}

	float item::get_bullet_drag( )
	{		
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return 0.f;
		
		if( is_melee( ) )
			return 1.f;

		auto bullet_name = this->get_bullet_name( );

		if( bullet_name == xs( "ammo.rifle.incendiary" )
			|| bullet_name == xs( "ammo.rifle" )
			|| bullet_name == xs( "ammo.rifle.explosive" )
			|| bullet_name == xs( "ammo.shotgun.slug" ) )
		{
			return 0.6f;
		}
		if( bullet_name == xs( "ammo.pistol" )
			|| bullet_name == xs( "ammo.pistol.incendiary" ) )
		{
			return 0.7f;
		}
		if( bullet_name == xs( "arrow.hv" )
			|| bullet_name == xs( "arrow.wooden" ) )
		{
			return 0.005f;
		}
		if( bullet_name == xs( "arrow.fire" )
			|| bullet_name == xs( "arrow.bone" ) )
		{
			return 0.01f;
		}
		if( bullet_name == xs( "ammo.handmade.shell" )
			|| bullet_name == xs( "ammo.shotgun" )
			|| bullet_name == xs( "ammo.shotgun.fire" )
			|| bullet_name == xs( "ammo.pistol.hv" )
			|| bullet_name == xs( "ammo.rifle.hv" ) )
		{
			return 1.f;
		}
		if( bullet_name == xs( "ammo.nailgun.nails" ) )
		{
			return 0.005f;
		}

		return 1.f;
	}

	std::string item::get_bullet_name( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return std::string( );

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held )
			return std::string( );

		uintptr_t magazine = *reinterpret_cast< uintptr_t* >( held + offsets::baseprojectile_primaryMagazine );
		if( !magazine )
			return std::string( );

		uintptr_t ammo_type = *reinterpret_cast< uintptr_t* >( magazine + 0x20 );
		if( !ammo_type )
			return std::string( );

		uintptr_t shortname = *reinterpret_cast< uintptr_t* >( ammo_type + 0x20 ); // shortname
		if( !shortname )
			return std::string( );

		std::string ammo_name = g_sdk.ws2s( g_sdk.read_unicode( shortname + 0x14, 32 ) );
		if( ammo_name.empty( ) )
			return std::string( );

		return ammo_name;
	}

	int item::get_amount( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return 0;

		uintptr_t address = offsets::item_amount;
		if( !address )
			return 0;

		return *reinterpret_cast< int* >( entity + address );
	}

	int32_t item::get_definition_id( )
	{
		const auto item_definition = *reinterpret_cast< uintptr_t* >( ( uintptr_t )this + offsets::item_info );
		if( !item_definition )
			return 0;

		return *reinterpret_cast< int32_t* >( item_definition + 0x18 );
	}

	int item::get_uid( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return 0;

		uintptr_t address = offsets::item_uid;
		if( !address )
			return 0;

		return *reinterpret_cast< int* >( entity + address );
	}

	uintptr_t item::get_sprite( )
	{
		uintptr_t method = offsets::get_iconSprite;
		if( !method )
			return NULL;

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
			return NULL;

		auto get_sprite = reinterpret_cast< uintptr_t( * )( uintptr_t ) >( method_ptr );
		if( !get_sprite )
			return NULL;

		return spoof_ret( get_sprite, reinterpret_cast< uintptr_t >( this ) );
	}

	std::wstring item::get_short_name( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return std::wstring( );

		uintptr_t address = offsets::item_info;
		if( !address )
			return std::wstring( );

		uintptr_t info = *reinterpret_cast< uintptr_t* >( entity + address );
		if( !info )
			return std::wstring( );

		uintptr_t second_address = offsets::itemdefinition_shortname;
		if( !second_address )
			return std::wstring( );

		il2mgr::il2cppstring* entity_name = *reinterpret_cast< il2mgr::il2cppstring** >( info + second_address );
		if( !entity_name )
			return std::wstring( );

		return entity_name->buffer;
	}

	vec3_t item::get_visual_position( uintptr_t object_class )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return vec3_t( );

		uintptr_t player_visual = *reinterpret_cast< uintptr_t* >( object_class + sizeof( uint64_t ) );
		if( !player_visual )
			return vec3_t( );

		uintptr_t visual_state = *reinterpret_cast< uintptr_t* >( player_visual + 0x38 );
		if( !visual_state )
			return vec3_t( );

		return *reinterpret_cast< vec3_t* >( visual_state + 0x90 );
	}

	bool item::get_recoil_min_max( vec2_t& pitch_bounds, vec2_t& yaw_bounds )
	{
		// TO-DO; REPEAT AFTER UPDATE.
		// WE GET YAW_BOUNDS.X AS RECOIL_YAW_MIN
		// AND OPPOSITE FOR MAX.
		// SAME GOES TO PITCH
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return false;

		auto item_definition = *reinterpret_cast< uintptr_t* >( entity + offsets::item_info );
		if( !item_definition )
			return false;

		if( !is_gun( )
			|| is_melee( ) )
			return false;

		unsigned int weapon_id = *reinterpret_cast< unsigned int* >( item_definition + 0x18 );
		switch( weapon_id )
		{
			case 0x5c22b98e/*Assault Rifle*/: { //Updated.
				pitch_bounds.x = -2.5;
				pitch_bounds.y = -3.5;
				yaw_bounds.x = 1.5;
				yaw_bounds.y = 2.5;
				return true;
			}
			case 0xb065ec45/*Assault Rifle ( ICE )*/: { //Updated.
				pitch_bounds.x = -2.5;
				pitch_bounds.y = -3.5;
				yaw_bounds.x = 1.5;
				yaw_bounds.y = 2.5;
				return true;
			}
			case 0x5eab82c3/*Bolt Action Rifle*/: { //Updated.
				pitch_bounds.x = -2;
				pitch_bounds.y = -3;
				yaw_bounds.x = -4;
				yaw_bounds.y = 4;
				return true;
			}
			case 0x34b73d71/*Compound Bow*/: { //Updated.
				pitch_bounds.x = -3;
				pitch_bounds.y = -6;
				yaw_bounds.x = -3;
				yaw_bounds.y = 3;
				return true;
			}
			case 0x7523110a/*Crossbow*/: { //Updated.
				pitch_bounds.x = -3;
				pitch_bounds.y = -6;
				yaw_bounds.x = -3;
				yaw_bounds.y = 3;
				return true;
			}
			case 0x6b1731e1/*Custom SMG*/: { //Updated.
				pitch_bounds.x = -1.5;
				pitch_bounds.y = -2;
				yaw_bounds.x = -1;
				yaw_bounds.y = 1;
				return true;
			}
			case 0xd264397f/*Double Barrel Shotgun*/: { //Updated.
				pitch_bounds.x = -10;
				pitch_bounds.y = -15;
				yaw_bounds.x = 8;
				yaw_bounds.y = 15;
				return true;
			}
			case 0x560b474f/*Hunting Bow*/: { //Updated.
				pitch_bounds.x = -3;
				pitch_bounds.y = -6;
				yaw_bounds.x = -3;
				yaw_bounds.y = 3;
				return true;
			}
			case 0xd19b0ec1/*L96 Rifle*/: { //Updated.
				pitch_bounds.x = -1;
				pitch_bounds.y = -1.5;
				yaw_bounds.x = -2;
				yaw_bounds.y = 2;
				return true;
			}
			case 0x93f69a57/*LR-300 Assault Rifle*/: { //Updated.
				pitch_bounds.x = -2;
				pitch_bounds.y = -3;
				yaw_bounds.x = -1;
				yaw_bounds.y = 1;
				return true;
			}
			case 0x84a4bb78/*M249*/: { //Updated.
				pitch_bounds.x = -3;
				pitch_bounds.y = -3;
				yaw_bounds.x = -1;
				yaw_bounds.y = 1;
				return true;
			}
			case 0x1ae5371/*M39 Rifle*/: { //Updated.
				pitch_bounds.x = -5;
				pitch_bounds.y = -7;
				yaw_bounds.x = -1.5;
				yaw_bounds.y = 1.5;
				return true;
			}
			case 0xcd2eebb5/*M92 Pistol*/: {
				pitch_bounds.x = -7;
				pitch_bounds.y = -8;
				yaw_bounds.x = -1;
				yaw_bounds.y = 1;
				return true;
			}
			case 0x4e979c37/*MP5A4*/: { //Updated
				pitch_bounds.x = -1;
				pitch_bounds.y = -3;
				yaw_bounds.x = -1;
				yaw_bounds.y = 1;
				return true;
			}
			case 0xbd092660/*Multiple Grenade Launcher*/: {
				pitch_bounds.x = -15.f;
				pitch_bounds.y = -20.f;
				yaw_bounds.x = 5.f;
				yaw_bounds.y = 10.f;
				return true;
			}
			case 0x74763261/*Nailgun*/: {
				pitch_bounds.x = -3;
				pitch_bounds.y = -6;
				yaw_bounds.x = -1;
				yaw_bounds.y = 1;
				return true;
			}
			case 0x2f686650/*Pump Shotgun*/: {
				pitch_bounds.x = -10.f;
				pitch_bounds.y = -14.f;
				yaw_bounds.x = 4.f;
				yaw_bounds.y = 8.f;
				return true;
			}
			case 0x51e52593/*Python Revolver*/: {
				pitch_bounds.x = -15.f;
				pitch_bounds.y = -16.f;
				yaw_bounds.x = -2.f;
				yaw_bounds.y = 2.f;
				return true;
			}
			case 0x26bce126/*Revolver*/: {
				pitch_bounds.x = -3.f;
				pitch_bounds.y = -6.f;
				yaw_bounds.x = -1.f;
				yaw_bounds.y = 1.f;
				return true;
			}
			case 0x1a65e87c/*Rocket Launcher*/: {
				pitch_bounds.x = -15.f;
				pitch_bounds.y = -20.f;
				yaw_bounds.x = 5.f;
				yaw_bounds.y = 10.f;
				return true;
			}
			case 0x30cf142c/*Semi-Automatic Pistol*/: {
				pitch_bounds.x = -6.f;
				pitch_bounds.y = -8.f;
				yaw_bounds.x = -2.f;
				yaw_bounds.y = 2.f;
				return true;
			}
			case 0xca10e257/*Semi-Automatic Rifle*/: {
				pitch_bounds.x = -5.f;
				pitch_bounds.y = -6.f;
				yaw_bounds.x = -1.f;
				yaw_bounds.y = 1.f;
				return true;
			}
			case 0xfd87ab32/*Spas-12 Shotgun*/: {
				pitch_bounds.x = -10.f;
				pitch_bounds.y = -14.f;
				yaw_bounds.x = 4.f;
				yaw_bounds.y = 8.f;
				return true;
			}
			case 0x97315c8b/*Thompson*/: { //Updated
				pitch_bounds.x = -1.5;
				pitch_bounds.y = -2;
				yaw_bounds.x = -1;
				yaw_bounds.y = 1;
				return true;
			}
			case 0xae80eeeb/*Waterpipe Shotgun*/: {
				pitch_bounds.x = -10.f;
				pitch_bounds.y = -14.f;
				yaw_bounds.x = 4.f;
				yaw_bounds.y = 8.f;
				return true;
			}
			case 0xb79b8d5f/*HMLMG*/: { //Updated.
				pitch_bounds.x = -3;
				pitch_bounds.y = -4;
				yaw_bounds.x = -1;
				yaw_bounds.y = -1.5;
				return true;
			}
			default: {
				return false;
			}
		}

		return false;
	}

	int item::ammocount( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return 1;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held )
			return 1;

		auto primemag = *reinterpret_cast< uintptr_t* >( held + offsets::baseprojectile_primaryMagazine );
		if( !primemag )
			return 1;

		auto contants = *reinterpret_cast< int* >( primemag + 0x14 );

		if( !contants )
			return 1;

		return contants;
	}

	int item::ammotype( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return 666;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held )
			return 666;

		auto primemag = *reinterpret_cast< uintptr_t* >( held + offsets::baseprojectile_primaryMagazine );
		if( !primemag )
			return 666;

		auto ammotype = *reinterpret_cast< int* >( primemag + 0x20 );
		if( !ammotype )
			return 666;

		return ammotype;
	}

	base_projectile* item::get_base_projectile( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return NULL;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held )
			return NULL;

		return *reinterpret_cast< base_projectile** >( held + offsets::baseprojectile_baseProjectile );
	}

	int item::get_max_ammo( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return 1;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held )
			return 1;

		auto primemag = *reinterpret_cast< uintptr_t* >( held + offsets::baseprojectile_primaryMagazine );
		if( !primemag )
			return 1;

		auto mag_contents = *reinterpret_cast< int* >( primemag + 0x10 );

		if( !mag_contents )
			return 1;

		return mag_contents;
	}

	void item::set_always_eoka( float value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held )
			return;

		auto item_name = get_short_name( );

		if( item_name.find( xs( L"eoka" ) ) != std::string::npos )
			*reinterpret_cast< float* >( held + offsets::flintstrikeweapon_successFraction ) = value;
	}

	void item::set_aim_sway( float value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held
			|| !is_gun( )
			|| is_melee( ) )
			return;

		*reinterpret_cast< float* >( held + offsets::baseprojectile_aimSway ) = value;
	}

	void item::do_attack( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held
			|| !is_gun( )
			|| is_melee( ) )
			return;

		uintptr_t method = offsets::baseprojectile_DoAttack;
		if( !method )
			return;

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
			return;

		auto DoAttack = reinterpret_cast< void ( * )( ) >( method_ptr );
		return spoof_ret( DoAttack );
	}

	void item::set_recoil_min_max( float value )
	{
		vec2_t pitch_bounds = vec2_t( ), yaw_bounds = vec2_t( );

		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t held_entity = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held_entity )
			return;

		uintptr_t recoil = *reinterpret_cast< uintptr_t* >( held_entity + offsets::baseprojectile_recoil );
		if( !recoil )
			return;

		uintptr_t new_recoil = *reinterpret_cast< uintptr_t* >( recoil + offsets::recoilproperties_newRecoilOverride ); // get our new recoil override
		if( !new_recoil )
			return;

		item* held_item = g_cheat.local->get_held_item( );
		if( !held_item )
			return;

		if( held_item->get_recoil_min_max( pitch_bounds, yaw_bounds ) )
		{
			*reinterpret_cast< float* >( recoil + offsets::recoilproperties_recoilYawMin ) = yaw_bounds.x * value;
			*reinterpret_cast< float* >( recoil + offsets::recoilproperties_recoilYawMax ) = yaw_bounds.y * value;
			*reinterpret_cast< float* >( recoil + offsets::recoilproperties_recoilPitchMin ) = pitch_bounds.x * value;
			*reinterpret_cast< float* >( recoil + offsets::recoilproperties_recoilPitchMax ) = pitch_bounds.y * value;

			/* new recoil */
			*reinterpret_cast< float* >( new_recoil + offsets::recoilproperties_recoilYawMin ) = yaw_bounds.x * value;
			*reinterpret_cast< float* >( new_recoil + offsets::recoilproperties_recoilYawMax ) = yaw_bounds.y * value;
			*reinterpret_cast< float* >( new_recoil + offsets::recoilproperties_recoilPitchMin ) = pitch_bounds.x * value;
			*reinterpret_cast< float* >( new_recoil + offsets::recoilproperties_recoilPitchMax ) = pitch_bounds.y * value;
		}
	}

	void item::set_aim_sway_speed( float value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held
			|| !is_gun( )
			|| is_melee( ) )
			return;

		*reinterpret_cast< float* >( held + offsets::baseprojectile_aimSwaySpeed ) *= value;
	}

	void item::set_aim_cone( float value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held
			|| !is_gun( )
			|| is_melee( ) )
			return;

		*reinterpret_cast< float* >( held + offsets::baseprojectile_aimCone ) *= value;
	}

	void item::set_aim_penalty_recover_delay( float value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held
			|| !is_gun( )
			|| is_melee( ) )
			return;

		*reinterpret_cast< float* >( held + offsets::baseprojectile_aimconePenaltyRecoverDelay ) *= value;
	}

	void item::set_aim_penalty_recover_time( float value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held
			|| !is_gun( )
			|| is_melee( ) )
			return;

		*reinterpret_cast< float* >( held + offsets::baseprojectile_aimconePenaltyRecoverTime ) *= value;
	}

	void item::set_aim_sight_aim_cone_scale( float value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held
			|| !is_gun( )
			|| is_melee( ) )
			return;

		*reinterpret_cast< float* >( held + offsets::baseprojectile_sightAimConeScale ) *= value;
	}

	void item::set_aim_sight_aim_cone_offset( float value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held
			|| !is_gun( )
			|| is_melee( ) )
			return;

		*reinterpret_cast< float* >( held + offsets::baseprojectile_sightAimConeOffset ) *= value;
	}

	void item::set_stance_penalty( float value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held
			|| !is_gun( )
			|| is_melee( ) )
			return;

		*reinterpret_cast< float* >( held + offsets::baseprojectile_stancePenalty ) *= value;
	}

	void item::set_aim_cone_curve_scale( float value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held
			|| !is_gun( )
			|| is_melee( ) )
			return;

		*reinterpret_cast< float* >( held + offsets::baseprojectile_aimCone ) *= value;
	}

	void item::set_aim_cone_penalty_max( float value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held
			|| !is_gun( )
			|| is_melee( ) )
			return;

		*reinterpret_cast< float* >( held + offsets::baseprojectile_aimConePenaltyMax ) *= value;
	}

	void item::set_aim_cone_penalty_per_shot( float value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held
			|| !is_gun( )
			|| is_melee( ) )
			return;

		*reinterpret_cast< float* >( held + offsets::baseprojectile_aimconePenaltyPerShot ) *= value;
	}

	void item::set_stance_penalty_scale( float value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held
			|| !is_gun( )
			|| is_melee( ) )
			return;

		*reinterpret_cast< float* >( held + offsets::baseprojectile_stancePenaltyScale ) *= value;
	}

	void item::set_hip_aim_cone( float value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held
			|| !is_gun( )
			|| is_melee( ) )
			return;

		*reinterpret_cast< float* >( held + offsets::baseprojectile_hipAimCone ) *= value;
	}

	void item::set_aim_cone_penalty( float value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held
			|| !is_gun( )
			|| is_melee( ) )
			return;

		*reinterpret_cast< float* >( held + offsets::baseprojectile_aimconePenalty ) *= value;
	}

	void item::set_hip_aim_cone_scale( float value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held
			|| !is_gun( )
			|| is_melee( ) )
			return;

		*reinterpret_cast< float* >( held + offsets::baseprojectile_hipAimConeScale ) *= value;
	}

	void item::set_hip_aim_cone_offset( float value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held
			|| !is_gun( )
			|| is_melee( ) )
			return;

		*reinterpret_cast< float* >( held + offsets::baseprojectile_hipAimConeOffset ) *= value;
	}

	float item::get_aim_sway_speed( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return 0.f;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held
			|| !is_gun( )
			|| is_melee( ) )
			return 0.f;

		return *reinterpret_cast< float* >( held + offsets::baseprojectile_aimSwaySpeed );
	}

	float item::get_aim_cone( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return 0.f;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held
			|| !is_gun( )
			|| is_melee( ) )
			return 0.f;

		return *reinterpret_cast< float* >( held + offsets::baseprojectile_aimCone );
	}

	float item::get_aim_penalty_recover_delay( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return 0.f;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held
			|| !is_gun( )
			|| is_melee( ) )
			return 0.f;

		return *reinterpret_cast< float* >( held + offsets::baseprojectile_aimconePenaltyRecoverDelay );
	}

	float item::get_aim_penalty_recover_time( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
		{
			return 0.f;
		}

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held
			|| !is_gun( )
			|| is_melee( ) )
			return 0.f;

		return *reinterpret_cast< float* >( held + offsets::baseprojectile_aimconePenaltyRecoverTime );
	}

	float item::get_aim_sight_aim_cone_scale( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
		{
			return 0.f;
		}

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held
			|| !is_gun( )
			|| is_melee( ) )
			return 0.f;

		return *reinterpret_cast< float* >( held + offsets::baseprojectile_sightAimConeScale );
	}

	float item::get_aim_sight_aim_cone_offset( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
		{
			return 0.f;
		}

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held
			|| !is_gun( )
			|| is_melee( ) )
			return 0.f;

		return *reinterpret_cast< float* >( held + offsets::baseprojectile_sightAimConeOffset );
	}

	float item::get_stance_penalty( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
		{
			return 0.f;
		}

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held
			|| !is_gun( )
			|| is_melee( ) )
			return 0.f;

		return *reinterpret_cast< float* >( held + offsets::baseprojectile_stancePenalty );
	}

	float item::get_aim_cone_curve_scale( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
		{
			return 0.f;
		}

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held
			|| !is_gun( )
			|| is_melee( ) )
		{
			return 0.f;
		}

		return *reinterpret_cast< float* >( held + offsets::baseprojectile_aimCone );
	}

	float item::get_aim_cone_penalty_max( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
		{
			return 0.f;
		}

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held
			|| !is_gun( )
			|| is_melee( ) )
		{
			return 0.f;
		}

		return *reinterpret_cast< float* >( held + offsets::baseprojectile_aimConePenaltyMax );
	}

	float item::get_aim_cone_penalty_per_shot( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return 0.f;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held
			|| !is_gun( )
			|| is_melee( ) )
			return 0.f;

		return *reinterpret_cast< float* >( held + offsets::baseprojectile_aimconePenaltyPerShot );
	}

	float item::get_stance_penalty_scale( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return 0.f;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held
			|| !is_gun( )
			|| is_melee( ) )
			return 0.f;

		return *reinterpret_cast< float* >( held + offsets::baseprojectile_stancePenaltyScale );
	}

	float item::get_hip_aim_cone( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return 0.f;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held
			|| !is_gun( )
			|| is_melee( ) )
			return 0.f;

		return *reinterpret_cast< float* >( held + offsets::baseprojectile_hipAimCone );
	}

	float item::get_aim_cone_penalty( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return 0.f;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held
			|| !is_gun( )
			|| is_melee( ) )
			return 0.f;

		return *reinterpret_cast< float* >( held + offsets::baseprojectile_aimconePenalty );
	}

	float item::get_hip_aim_cone_scale( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return 0.f;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held
			|| !is_gun( )
			|| is_melee( ) )
			return 0.f;

		return *reinterpret_cast< float* >( held + offsets::baseprojectile_hipAimConeScale );
	}

	float item::get_hip_aim_cone_offset( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return 0.f;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held
			|| !is_gun( )
			|| is_melee( ) )
			return 0.f;

		return *reinterpret_cast< float* >( held + offsets::baseprojectile_hipAimConeOffset );
	}

	uintptr_t item::get_damage_properties( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return NULL;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held )
			return NULL;

		return *reinterpret_cast< uintptr_t* >( held + offsets::basemelee_damageproperties );
	}

	void item::set_block_sprint( bool value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held )
			return;

		*reinterpret_cast< bool* >( held + offsets::basemelee_blockSprintOnAttack ) = value;
	}

	void item::set_reload_start_time( float value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held )
			return;

		*reinterpret_cast< float* >( held + offsets::reloadStartDuration ) = value;
	}

	void item::set_reload_time( float value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held )
			return;

		*reinterpret_cast< float* >( held + offsets::reloadTime ) = value;
	}

	float item::get_reload_time( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return 0.f;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held )
			return 0.f;

		return *reinterpret_cast< float* >( held + offsets::reloadTime );
	}

	float item::get_next_reload_time( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return 0.f;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held )
			return 0.f;

		return *reinterpret_cast< float* >( held + offsets::nextReloadTime );
	}

	bool item::has_reload_cooldown( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return 0.f;

		return this->get_next_reload_time( ) > g_cheat.global_time;
	}

	float item::calculate_cooldown_time( float next_time, float cool_down ) {
		float num = g_cheat.global_time;

		float ret = next_time;

		if( ret < 0.f )
			ret = max( 0.f, num + cool_down );
		else if ( ( num - ret ) <= 0.f )
			ret = min( ret + cool_down, num + cool_down );
		else
			ret = max( ret + cool_down, num + cool_down );

		return ret;
	}

	float item::get_static_repeat_delay( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return 0.f;

		auto weapon_name = g_sdk.ws2s( this->get_short_name( ) );
		auto item_definition = *reinterpret_cast< uintptr_t* >( entity + offsets::item_info );
		if( !item_definition )
			return 0.f;

		if( !is_gun( )
			|| is_melee( ) )
			return 0.f;

		unsigned int weapon_id = *reinterpret_cast< unsigned int* >( item_definition + 0x18 );
		
		if( weapon_name == xs( "rifle.ak" )
			|| weapon_id == 0xb065ec45 )
		{
			return 0.1333f;
		}
		else if( weapon_name == xs( "smg.2" )
			|| weapon_name == xs( "smg.mp5" ) )
		{
			return 0.1f;
		}
		else if( weapon_name == xs( "rifle.lr300" )
			|| weapon_name == xs( "lmg.m249" ) )
		{
			return 0.12f;
		}
		else if( weapon_name == xs( "rifle.m39" ) )
		{
			return 0.2f;
		}
		else if( weapon_name == xs( "pistol.nailgun" ) 
			|| weapon_name == xs( "pistol.python" )
			|| weapon_name == xs( "pistol.m92" )
			|| weapon_name == xs( "pistol.semiauto" ) )
		{
			return 0.15f;
		}
		else if( weapon_name == xs( "pistol.revolver" )
			|| weapon_name == xs( "rifle.semiauto" ) )
		{
			return 0.175f;
		}
		else if( weapon_name == xs( "hmlmg" )
			|| weapon_name == xs( "smg.thompson" ) )
		{
			return 0.13f;
		}
		else if( weapon_name == xs( "pistol.prototype17" ) )
		{
			return 0.09f;
		}

		return 1.f;
	}

	float item::get_repeat_delay( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return 0.f;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held )
			return 0.f;

		return *reinterpret_cast< float* >( held + offsets::attackentity_repeatDelay );
	}

	void item::set_repeat_delay( float value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held )
			return;

		*reinterpret_cast< float* >( held + offsets::attackentity_repeatDelay ) = value;
	}

	void item::set_deploy_delay( float value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held )
			return;

		*reinterpret_cast< float* >( held + offsets::attackentity_deployDelay ) = value;
	}

	float item::get_time_since_deploy( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return 0.f;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held )
			return 0.f;

		auto method = offsets::attackentity_timesincedeploy;
		if( !method )
			return 0.f;

		return *reinterpret_cast< float* >( held + method );
	}

	float item::get_deploy_delay( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return 0.f;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held )
			return 0.f;

		auto method = offsets::attackentity_deployDelay;
		if( !method )
			return 0.f;

		return *reinterpret_cast< float* >( held + method );
	}

	float item::get_next_attack_time( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return 0.f;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held )
			return 0.f;

		auto method = offsets::attackentity_nextattacktime;
		if( !method )
			return 0.f;

		return *reinterpret_cast< float* >( held + method );
	}

	void item::set_current_hold_progress( float value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held )
			return;

		auto weapon_name = g_sdk.ws2s( get_short_name( ) );

		if( weapon_name != xs( "bow.compound" ) )
			return;

		*reinterpret_cast< float* >( held + offsets::compoundbow_currentHoldProgress ) = value;
	}

	void item::set_string_bonus_damage( float value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held )
			return;

		auto weapon_name = g_sdk.ws2s( get_short_name( ) );

		if( weapon_name != xs( "bow.compound" ) )
			return;

		*reinterpret_cast< float* >( held + offsets::compoundbow_stringBonusDamage ) = value;
	}
	
	void item::set_movement_penalty_ramp_up_time( float value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held )
			return;

		auto weapon_name = g_sdk.ws2s( get_short_name( ) );

		if( weapon_name != xs( "bow.compound" ) )
			return;

		*reinterpret_cast< float* >( held + offsets::compoundbow_movementPenaltyRampUpTime ) = value;
	}

	void item::process_attack( hit_test* hit_test )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t method = offsets::basemelee_processattack;
		if( !method )
			return;

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
			return;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held )
			return;

		auto startcooldown = reinterpret_cast< void( * )( uintptr_t, core::hit_test* ) >( method_ptr );
		spoof_ret( startcooldown, held, hit_test );
	}

	void item::do_throw( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t method = offsets::basemelee_dothrow;
		if( !method )
			return;

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
			return;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held )
			return;

		auto dothrow = reinterpret_cast< void( * )( uintptr_t ) >( method_ptr );
		spoof_ret( dothrow, held );
	}

	bool item::can_throw_as_projectile( ) {
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return false;

		uintptr_t method = offsets::basemelee_can_throw_as_projectile;
		if( !method )
			return false;

		return *reinterpret_cast< bool* >( entity + method );
	}

	void item::start_attack_cooldown( float value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t method = offsets::attackentity_startattackcooldown;
		if( !method )
			return;

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
			return;

		uintptr_t held = *reinterpret_cast< uintptr_t* >( entity + offsets::item_heldEntity );
		if( !held )
			return;

		auto startcooldown = reinterpret_cast< void( * )( uintptr_t, float ) >( method_ptr );
		spoof_ret( startcooldown, held, value );
	}

	bool item::is_heal( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return false;

		int32_t item_id = this->get_definition_id( );

		if( item_id == 1079279582 // syringe
			|| item_id == -2072273936 // bandage
		) 
			return true;
		else
			return false;

		return false;
	}

	bool item::is_melee( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return false;

		if( this->is_heal( ) )
			return false;

		int32_t item_id = get_definition_id( );

		if( item_id == -1104520648 || // chainsaw
			item_id == -1137865085 || // machete
			item_id == -1252059217 || // hatchet
			item_id == -1302129395 || // pickaxe
			item_id == -262590403  || // axe.salvaged
			item_id == -1506397857 || // hammer.salvaged
			item_id == -1780802565 || // icepick.salvaged
			item_id == -1583967946 || // stonehatchet
			item_id == 171931394   || // stone.pickaxe
			item_id == 795236088   || // torch
			item_id == 1711033574  || // bone.club
			item_id == 1814288539  || // knife.bone
			item_id == -194509282  || // knife.butcher
			item_id == 1789825282  || // candycaneclub
			item_id == -1252059217 || // hatchet
			item_id == 2040726127  || // knife.combat
			item_id == -1469578201 || // longsword
			item_id == -1966748496 || // mace
			item_id == -1137865085 || // paddle
			item_id == 1491189398  || // paddle
			item_id == 1090916276  || // pitchfork
			item_id == 1602646136  || // spear.stone
			item_id == -1978999529 || // salvaged.cleaver
			item_id == 1326180354  || // salvaged.sword
			item_id == 1491189398  || // paddle
			item_id == 1540934679  || // spear.wooden
			item_id == -196667575  || // flashlight
			item_id == 963906841   || // rock
			item_id == 200773292   || // hammer tool
			item_id == 1803831286  )  // garry's mod tool gun
			return true;
		else
			return false;

		return false;
	}

	bool item::is_gun( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return false;

		std::wstring item_name = get_short_name( );

		if( item_name.find( xs( L"ammo." ) ) == std::string::npos ) {
			if( ( item_name.find( xs( L"rifle." ) ) != std::string::npos
				|| item_name.find( xs( L"pistol." ) ) != std::string::npos
				|| item_name.find( xs( L"bow." ) ) != std::string::npos
				|| item_name.find( xs( L"cross" ) ) != std::string::npos
				|| item_name.find( xs( L"lmg." ) ) != std::string::npos
				|| item_name.find( xs( L"hmlmg" ) ) != std::string::npos
				|| item_name.find( xs( L"shotgun." ) ) != std::string::npos
				|| item_name.find( xs( L"smg." ) ) != std::string::npos ) )
				return true;
			else
				return false;
		}
		else
			return false;

		return false;
	}

	int item_container::get_size( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return 0;

		uintptr_t address = offsets::itemcontainer_itemList;
		if( !address )
			return 0;

		uintptr_t item_list = *reinterpret_cast< uintptr_t* >( entity + address );
		if( !item_list )
			return 0;

		return *reinterpret_cast< uintptr_t* >( item_list + 0x18 );
	}

	item* item_container::get_item( int id )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return nullptr;

		uintptr_t address = offsets::itemcontainer_itemList;
		if( !address )
			return nullptr;

		uintptr_t item_list = *reinterpret_cast< uintptr_t* >( entity + address );
		if( !item_list )
			return nullptr;

		uintptr_t items = *reinterpret_cast< uintptr_t* >( item_list + 0x10 );
		if( !items )
			return nullptr;

		return *reinterpret_cast< item** >( items + 0x20 + ( id * sizeof( uint64_t ) ) );
	}

	item_container* player_inventory::get_wear( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return nullptr;

		uintptr_t address = offsets::playerinventory_containerWear; //il2mgr::value( xs( "player_inventory" ), xs( "containerBelt" ) );
		if( !address )
			return nullptr;

		return *reinterpret_cast< item_container** >( entity + address );
	}

	item_container* player_inventory::get_belt( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return nullptr;

		uintptr_t address = offsets::playerinventory_containerBelt; //il2mgr::value( xs( "player_inventory" ), xs( "containerBelt" ) );
		if( !address )
			return nullptr;

		return *reinterpret_cast< item_container** >( entity + address );
	}

	long team_member::get_uid( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return long( );

		return *reinterpret_cast< long*>( entity + 0x20 );
	}

	std::vector< long > player_team::get_members( )
	{
		std::vector< long > member_vector = std::vector< long >( );
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return std::vector< long >( );

		uintptr_t member_list = *reinterpret_cast< uintptr_t* >( entity + 0x30 );
		if( !member_list )
			return std::vector< long >( );

		uintptr_t members = *reinterpret_cast< uintptr_t* >( member_list + 0x10 );
		if( !members )
			return std::vector< long >( );

		int members_size = *reinterpret_cast< int* >( member_list + 0x18 );
		if( !members_size )
			return std::vector< long >( );

		for( auto i = 0; i < members_size; i++ )
		{
			team_member* member = *reinterpret_cast< team_member** >( members + ( 0x20 + ( i * sizeof( uint64_t ) ) ) );
			if( !member )
				continue;

			long member_uid = member->get_uid( );
			if( member_uid )
				member_vector.push_back( member_uid );
		}

		return member_vector;
	}

	long player_team::get_team_id( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return long( );

		uintptr_t method = offsets::teamID;
		if( !method )
			return long( );

		return *reinterpret_cast< long* >( entity + method );
	}

	vec3_t player_ticks::get_position( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return vec3_t( );
		
		uintptr_t method = offsets::playertick_position;
		if( !method )
			return vec3_t( );

		return *reinterpret_cast< vec3_t* >( entity + method );
	}

	void player_ticks::SetTicks( float ticks )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return;

		*reinterpret_cast< float* >( entity + offsets::player_lastSentTick ) = ticks;
	}

	float player_ticks::TicksPerSec( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return 0.f;

		uintptr_t address = offsets::player_lastSentTick;
		if( !address )
			return 0.f;

		return *reinterpret_cast< float* >( entity + address );
	}

	float base_player::lastSentTickTime( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return 0.f;

		uintptr_t address = offsets::player_lastSentTickTime;
		if( !address )
			return 0.f;

		return *reinterpret_cast< float* >( entity + address );
	}

	void base_player::on_land( float velocity )
	{
		base_player* entity = *reinterpret_cast< base_player** >( this );
		if( !entity )
			return;

		uintptr_t method = offsets::OnLand;
		if( !method )
			return;

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
			return;

		auto on_land = reinterpret_cast< void( * )( base_player*, float ) >( method_ptr );
		return spoof_ret( on_land, entity, velocity );
	}

	player_ticks* base_player::get_lastSentTick( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return nullptr;

		uintptr_t method = offsets::player_lastSentTick;
		if( !method )
			return nullptr;

		return *reinterpret_cast< player_ticks** >( entity + method );
	}

	float base_player::get_height( bool ducked )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return 0.f;

		uintptr_t method = offsets::baseplayer_get_height;
		if( !method )
			return 0.f;

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
			return 0.f;
		
		auto func = reinterpret_cast< float( * )( uintptr_t, bool ) >( method_ptr );
		return spoof_ret( func, entity, ducked );
	}

	void base_player::set_clothing_speed_reduce( float value ) {
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t method = offsets::clothingMoveSpeedReduction;
		if( !method )
			return;
		
		*reinterpret_cast< float* >( entity + method ) = value;
	}

	void base_player::set_clothing_blocks_aiming( bool value ) {
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t method = offsets::clothingBlocksAiming;
		if( !method )
			return;
		
		*reinterpret_cast< bool* >( entity + method ) = value;
	}

	void base_player::set_is_frozen( bool value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t method = offsets::Frozen;
		if( !method )
			return;
		
		*reinterpret_cast< bool* >( entity + method ) = value;
	}

	bool base_player::get_on_ladder( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return 0.f;

		uintptr_t method = offsets::baseplayer_onladder;
		if( !method )
			return 0.f;

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
			return 0.f;

		auto func = reinterpret_cast< bool( * )( uintptr_t ) >( method_ptr );
		return spoof_ret( func, entity );
	}

	float base_player::get_radius( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return 0.f;

		uintptr_t method = offsets::baseplayer_get_radius;
		if( !method )
			return 0.f;

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
			return 0.f;

		auto func = reinterpret_cast< float( * )( uintptr_t ) >( method_ptr );
		return spoof_ret( func, entity );
	}

	float base_player::get_jumpheight( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return 0.f;

		uintptr_t method = offsets::baseplayer_get_jumpheight;
		if( !method )
			return 0.f;

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
			return 0.f;

		auto func = reinterpret_cast< float( * )( uintptr_t ) >( method_ptr );
		return spoof_ret( func, entity );
	}

	std::wstring base_player::get_username( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return std::wstring( );

		uintptr_t address = offsets::_displayName;

		il2mgr::il2cppstring* player_name = *reinterpret_cast< il2mgr::il2cppstring** >( entity + address );
		if( !player_name )
			return std::wstring( );

		return player_name->buffer;
	}

	unsigned long base_player::get_uid( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return unsigned long( );

		uintptr_t address = offsets::userID;
		if( !address )
			return unsigned long( );

		return *reinterpret_cast< unsigned long* >( entity + address );
	}

	int base_player::get_active_weapon_id( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return 0;

		return *reinterpret_cast< int* >( entity + offsets::clActiveItem );
	}

	player_walk_movement* base_player::get_movement( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return nullptr;

		return *reinterpret_cast< player_walk_movement** >( entity + offsets::movement );
	}

	player_input* base_player::get_input( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return nullptr;

		uintptr_t address = offsets::input;
		if( !address )
			return nullptr;

		return *reinterpret_cast< player_input** >( entity + address );
	}

	player_inventory* base_player::get_inventory( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return nullptr;

		uintptr_t address = offsets::inventory;
		if( !address )
			return nullptr;

		return *reinterpret_cast< player_inventory** >( entity + address );
	}

	bool base_player::has_flag( player_flags flag )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return false;

		uintptr_t address = offsets::playerFlags;
		if( !address )
			return false;

		int flags = *reinterpret_cast< int* >( entity + address );

		return flags & flag;
	}

	player_team* base_player::get_team( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return nullptr;

		uintptr_t address = offsets::clientTeam;
		if( !address )
			return nullptr;

		return *reinterpret_cast< player_team** >( entity + address );
	}

	bool base_player::is_same_team( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return false;

		base_player* local = g_cheat.local;
		if( !local )
			return false;

		player_team* team = local->get_team( );
		if( !team )
			return false;

		auto team_members = team->get_members( );
		for( auto& team : team_members ) {
			if( team == this->get_uid( ) )
				return true;
		}
		return false;
	}

	model_state* base_player::get_modelstate( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return nullptr;

		uintptr_t address = offsets::modelstate;
		if( !address )
			return nullptr;

		return *reinterpret_cast< model_state** >( entity + address );
	}

	player_model* base_player::get_model( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return nullptr;

		uintptr_t address = offsets::player_model;
		if( !address )
			return nullptr;

		return *reinterpret_cast< player_model** >( entity + address );
	}

	player_eyes* base_player::get_eyes( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return nullptr;

		uintptr_t address = offsets::player_eyes;
		if( !address )
			return nullptr;

		return *reinterpret_cast< player_eyes** >( entity + address );
	}

	item* base_player::get_held_item( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return nullptr;

		int active_item_id = get_active_weapon_id( );
		if( !active_item_id )
			return nullptr;

		player_inventory* inventory = get_inventory( );
		if( !inventory )
			return nullptr;

		item_container* belt = inventory->get_belt( );
		if( !belt )
			return nullptr;

		for( int i = 0; i < belt->get_size( ); i++ )
		{
			item* weapon = belt->get_item( i );
			if( !weapon )
				continue;

			if( active_item_id == weapon->get_uid( ) )
				return weapon;
		}

		return nullptr;
	}

	void viewmodel_bob::set_bob_speed_walk( float value ) {
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t method = offsets::bob_speed_walk;
		if( !method )
			return;
		
		*reinterpret_cast< float* >( entity + method ) = value;
	}

	void viewmodel_bob::set_bob_speed_run( float value ) {
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t method = offsets::bob_speed_run;
		if( !method )
			return;
		
		*reinterpret_cast< float* >( entity + method ) = value;
	}

	void viewmodel_bob::set_bob_amount_walk( float value ) {
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t method = offsets::bob_amount_walk;
		if( !method )
			return;
		
		*reinterpret_cast< float* >( entity + method ) = value;
	}

	void viewmodel_bob::set_bob_amount_run( float value ) {
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t method = offsets::bob_amount_run;
		if( !method )
			return;
		
		*reinterpret_cast< float* >( entity + method ) = value;
	}

	void viewmodel_lower::set_should_lower( bool value ) {
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t method = offsets::should_lower;
		if( !method )
			return;
		
		*reinterpret_cast< bool* >( entity + method ) = value;
	}

	viewmodel_bob* base_view_model::get_bob( ) {
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return nullptr;

		uintptr_t method = offsets::bob;
		if( !method )
			return nullptr;
		
		return *reinterpret_cast< viewmodel_bob** >( entity + method );
	}
	
	base_view_model* base_view_model::get_view( ) {
		uintptr_t method = offsets::view;
		if( !method )
			return NULL;

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
			return NULL;

		auto get_view = reinterpret_cast< base_view_model*( * )( ) >( method_ptr );

		return spoof_ret( get_view );
	}

	viewmodel_lower* base_view_model::get_lower( ) {
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return nullptr;

		uintptr_t method = offsets::lower;
		if( !method )
			return nullptr;
		
		return *reinterpret_cast< viewmodel_lower** >( entity + method );
	}
	
	std::vector< item* > base_player::get_wear_items( )
	{
		std::vector< item* > temp = std::vector< item* >( { nullptr } );

		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return temp;

		player_inventory* inventory = get_inventory( );
		if( !inventory )
			return temp;

		item_container* wear = inventory->get_wear( );
		if( !wear )
			return temp;

		for( int i = 0; i < wear->get_size( ); i++ )
		{
			item* weapon = wear->get_item( i );
			if( !weapon )
				continue;

			temp.push_back( weapon );
		}

		return temp;
	}

	std::vector< item* > base_player::get_hotbar_items( )
	{
		std::vector< item* > temp = std::vector< item* >( { nullptr } );

		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return temp;

		player_inventory* inventory = get_inventory( );
		if( !inventory )
			return temp;

		item_container* belt = inventory->get_belt( );
		if( !belt )
			return temp;

		for( int i = 0; i < belt->get_size( ); i++ )
		{
			item* weapon = belt->get_item( i );
			if( !weapon )
				continue;

			temp.push_back( weapon );
		}

		return temp;
	}

	bool base_player::is_knocked( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return false;

		uintptr_t address1 = offsets::playerFlags;
		if( !address1 )
			return false;

		int flags = *reinterpret_cast< int* >( entity + address1 );

		return flags & player_flags::is_wounded;
	}

	base_mountable* base_player::get_mountable( ) {
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return nullptr;

		return *reinterpret_cast< base_mountable** >( entity + offsets::mounted );
	}

	void base_player::set_clientTickInterval( float value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t address = offsets::clientTickInterval;
		if( !address )
			return;

		*reinterpret_cast< float* >( entity + address ) = value;
	}

	float base_player::get_clientTickInterval( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return 0.f;

		uintptr_t address = offsets::clientTickInterval;
		if( !address )
			return 0.f;

		return *reinterpret_cast< float* >( entity + address );
	}

	void base_mountable::set_ignore_vehicle_parent( bool value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t address = offsets::basemountable_ignoreVehicleParent;
		if( !address )
			return;

		*reinterpret_cast< bool* >( entity + address ) = value;
	}

	void base_mountable::set_can_wield_item( bool value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t address = offsets::basemountable_canwielditems;
		if( !address )
			return;

		*reinterpret_cast< bool* >( entity + address ) = value;
	}

	bool player_model::is_npc( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return false;

		uintptr_t address = offsets::playermodel_get_IsNpc;
		if( !address )
			return false;

		return *reinterpret_cast< bool* >( entity + address );
	}

	bool base_player::is_sleeping( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return false;

		uintptr_t address1 = offsets::playerFlags;

		return *reinterpret_cast< int* >( entity + address1 ) & player_flags::is_sleeping;
	}

	bool base_player::is_visible( vec3_t end )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return false;
		
		player_eyes* eyes = g_cheat.local_eyes;
		if( !eyes )
			return false;

		return g_sdk.is_visible( eyes->get_position( ), end );
	}

	bool base_player::is_visible( vec3_t start, vec3_t end )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return false;

		return g_sdk.is_visible( start, end );
	}

	vec3_t base_player::get_bone_position( int bone )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return vec3_t( );

		transform* transform = get_bone_transform( bone );
		if( !transform )
			return vec3_t( );

		return transform->get_position( );
	}

	transform* base_player::get_bone_transform( int bone )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return nullptr;

		uintptr_t address1 = offsets::model;
		if( !address1 )
			return nullptr;

		uintptr_t player_model = *reinterpret_cast< uintptr_t* >( entity + address1 );
		if( !player_model )
			return nullptr;

		uintptr_t second_address = offsets::boneTransforms;
		if( !second_address )
			return nullptr;

		uintptr_t bone_transforms = *reinterpret_cast< uintptr_t* >( player_model + second_address );
		if( !bone_transforms )
			return nullptr;

		transform* entity_bone = *reinterpret_cast< transform** >( bone_transforms + ( 0x20 + ( bone * sizeof( uint64_t ) ) ) );
		if( !entity_bone )
			return nullptr;

		return entity_bone;
	}

	int	base_player::get_mpv_bone( ) {
		if( !this ) 
			return 0;

		auto eyes = g_cheat.local->get_eyes( );

		if( !eyes )
			return 0;

		else if( g_sdk.is_visible( g_cheat.local_pos, this->get_bone_position( bone_list::head ) ) )
			return bone_list::head;
		else if( g_sdk.is_visible( g_cheat.local_pos, this->get_bone_position( bone_list::spine3 ) ) )
			return bone_list::spine3;
		else if( g_sdk.is_visible( g_cheat.local_pos, this->get_bone_position( bone_list::pelvis ) ) )
			return bone_list::pelvis;
		else if( g_sdk.is_visible( g_cheat.local_pos, this->get_bone_position( bone_list::l_hand ) ) )
			return bone_list::l_hand;
		else if( g_sdk.is_visible( g_cheat.local_pos, this->get_bone_position( bone_list::r_hand ) ) )
			return bone_list::r_hand;
		else if( g_sdk.is_visible( g_cheat.local_pos, this->get_bone_position( bone_list::l_foot ) ) )
			return bone_list::l_foot;
		else if( g_sdk.is_visible( g_cheat.local_pos, this->get_bone_position( bone_list::r_foot ) ) )
			return bone_list::r_foot;
		else
			return bone_list::head;
	}

	uintptr_t base_player::visiblePlayerList( )
	{
		static auto this_class = il2mgr::init_class( xs( "BasePlayer" ) );
		if( !this_class )
			return NULL;

		uintptr_t static_fields = *reinterpret_cast< uintptr_t* >( this_class + 0xB8 );
		if( !static_fields )
			return NULL;

		return *reinterpret_cast< uintptr_t* >( static_fields + sizeof( uint64_t ) );
	}

	void base_player::set_can_attack( bool value ) {
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		*reinterpret_cast< bool* >( entity + offsets::CanAttack ) = value;
	}

	void base_player::add_flag( int flag )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		auto address = offsets::playerFlags;

		*reinterpret_cast< int* >( entity + address ) |= flag;
	}

	void base_player::remove_flag( int flag )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		auto address = offsets::playerFlags;

		*reinterpret_cast< int* >( entity + address ) &= flag;
	}

	void base_player::invite_to_team( base_player* player )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t method = offsets::invitetoteam;
		if( !method )
			return;

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
			return;

		auto InviteToTeam = reinterpret_cast< void( * )( uintptr_t, base_player* ) >( method_ptr );
		spoof_ret( InviteToTeam, entity, player );
	}

	base_player* local_player::Entity( )
	{
		static auto this_class = il2mgr::init_class( xs( "LocalPlayer" ) );
		if( !this_class )
			return nullptr;

		uintptr_t static_fields = *reinterpret_cast< uintptr_t* >( this_class + 0xB8 );
		if( !static_fields )
			return nullptr;

		return *reinterpret_cast< base_player** >( static_fields );
	}

	void local_player::ConsoleMessage( const char* message )
	{
		uintptr_t method = offsets::baseplayer_consolemessage;
		if( !method )
			return;

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
			return;

		auto consoleMessage = reinterpret_cast< void( * )( uintptr_t, il2mgr::il2cppstring* ) >( method_ptr );
		uintptr_t blank = NULL;
		spoof_ret( consoleMessage, blank, il2mgr::il2cppstring::New( message ) );
	}

	void item_mod_projectile::set_projectile_spread( float value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return;

		*reinterpret_cast< float* >( entity + offsets::itemmodprojectile_projectileSpread ) = value;
	}

	void item_mod_projectile::set_projectile_velocity_spread( float value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return;

		*reinterpret_cast< float* >( entity + offsets::itemmodprojectile_projectileVelocitySpread ) = value;
	}

	float projectile::get_thickness( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return false;

		return *reinterpret_cast< float* >( entity + offsets::projectile_thickness );
	}

	float projectile::get_integrity( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return false;

		return *reinterpret_cast< float* >( entity + offsets::projectile_integrity );
	}

	float projectile::get_traveled_distance( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return false;

		return *reinterpret_cast< float* >( entity + offsets::projectile_traveledDistance );
	}

	float projectile::get_max_distance( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return false;

		return *reinterpret_cast< float* >( entity + offsets::projectile_maxDistance );
	}

	float projectile::get_move_delta_time( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return false;

		return *reinterpret_cast< float* >( entity + il2mgr::value( xs( "Projectile" ), xs( "moveDeltaTime" ) ) );
	}

	float projectile::get_drag( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return false;

		return *reinterpret_cast< float* >( entity + il2mgr::value( xs( "Projectile" ), xs( "drag" ) ) );
	}

	bool projectile::is_authoritative( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return false;

		return *reinterpret_cast< bool* >( entity + il2mgr::value( xs( "Projectile" ), xs( "get_isAuthoritative" ) ) );
	}

	vec3_t projectile::get_current_position( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return vec3_t( );

		return *reinterpret_cast< vec3_t* >( entity + il2mgr::value( "Projectile", "currentPosition" ) );
	}

	vec3_t projectile::get_current_velocity( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return vec3_t( );

		return *reinterpret_cast< vec3_t* >( entity + il2mgr::value( xs( "Projectile" ), xs( "currentVelocity" ) ) );
	}

	float projectile::get_traveled_time( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return false;

		return *reinterpret_cast< float* >( entity + offsets::projectile_traveledTime );
	}

	bool projectile::is_alive( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return false;

		return ( this->get_integrity( ) > 0.001f && this->get_traveled_distance( ) < this->get_max_distance( ) && this->get_traveled_time( ) < 8 );
	}

	void projectile::set_thickness( float value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return;

		uintptr_t address = offsets::projectile_thickness;
		if( !address )
			return;

		*reinterpret_cast< float* >( entity + address ) = value;
	}

	base_player* projectile::get_owner( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return nullptr;

		return *reinterpret_cast< base_player** >( entity + offsets::projectile_owner ); //*Rust_Offsets::hit_test::HitEntity );
	}

	item_mod_projectile* projectile::get_item_mod_projectile( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return nullptr;

		return *reinterpret_cast< item_mod_projectile** >( entity + offsets::projectile_mod ); //*Rust_Offsets::hit_test::HitEntity );
	}

	vec3_t projectile::get_initial_velocity( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return vec3_t( );

		return *reinterpret_cast< vec3_t* >( entity + offsets::projectile_initialVelocity );
	}

	float projectile::get_gravity_modifier( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return 0.f;

		return *reinterpret_cast< float* >( entity + offsets::projectile_gravityModifier );
	}

	void projectile::set_current_velocity( vec3_t value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return;

		*reinterpret_cast< vec3_t* >( entity + offsets::projectile_currentVelocity ) = value;
	}

	base_entity* hit_test::get_hit_entity( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return nullptr;

		return *reinterpret_cast< base_entity** >( entity + offsets::hittest_hitEntity );
	}

	hit_test* hit_test::New( )
	{
		return ( hit_test* )il2mgr::methods::object_new( il2mgr::init_class( xs( "HitTest" ) ) );
	}

	vec3_t hit_test::get_hit_normal( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return vec3_t( );

		return *reinterpret_cast< vec3_t* >( entity + offsets::hittest_hitNormal );
	}

	void hit_test::set_hit_entity( base_entity* new_entity )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return;

		*reinterpret_cast< base_entity** >( entity + offsets::hittest_hitEntity ) = new_entity;
	}

	void hit_test::set_hit_transform( transform* new_transform )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return;

		*reinterpret_cast< transform** >( entity + offsets::hittest_hitTransform ) = new_transform;
	}

	void hit_test::set_hit_hitpoint( vec3_t new_hitpoint )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return;

		*reinterpret_cast< vec3_t* >( entity + offsets::hittest_hitPoint ) = new_hitpoint;
	}

	void hit_test::set_hit_distance( float distance )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return;

		*reinterpret_cast< float* >( entity + offsets::hittest_hitDistance ) = distance;
	}

	void hit_test::set_did_hit( bool value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return;

		*reinterpret_cast< bool* >( entity + offsets::hittest_didHit ) = value;
	}

	void hit_test::set_attack_ray( Ray value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return;

		*reinterpret_cast< Ray* >( entity + offsets::hittest_attackray ) = value;
	}

	void hit_test::set_max_distance( float value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return;

		*reinterpret_cast< bool* >( entity + offsets::hittest_maxDistance ) = value;
	}

	void hit_test::set_damage_properties( uintptr_t value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return;

		*reinterpret_cast< uintptr_t* >( entity + offsets::hittest_damageProperties ) = value;
	}

	void hit_test::set_hit_normal( vec3_t value )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return;

		*reinterpret_cast< vec3_t* >( entity + offsets::hittest_hitNormal ) = value;
	}

	base_entity* hit_info::get_initiator( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return nullptr;

		return *reinterpret_cast< base_entity** >( entity + il2mgr::value( xs( "HitInfo" ), xs( "Initiator" ) ) );
	}

	base_entity* hit_info::get_hit_entity( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return nullptr;

		return *reinterpret_cast< base_entity** >( entity + il2mgr::value( xs( "HitInfo" ), xs( "HitEntity" ) ) );
	}

	int hit_info::get_hit_bone( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return NULL;

		return *reinterpret_cast< int* >( entity + il2mgr::value( xs( "HitInfo" ), xs( "HitBone" ) ) );
	}

	vec3_t hit_info::get_hit_start( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return vec3_t( );

		return *reinterpret_cast< vec3_t* >( entity + il2mgr::value( xs( "HitInfo" ), xs( "PointStart" ) ) );
	}

	vec3_t hit_info::get_hit_end( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return vec3_t( );

		return *reinterpret_cast< vec3_t* >( entity + il2mgr::value( xs( "HitInfo" ), xs( "PointEnd" ) ) );
	}

	vec3_t hit_info::get_hit_position_world( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return vec3_t( );

		return *reinterpret_cast< vec3_t* >( entity + il2mgr::value( xs( "HitInfo" ), xs( "HitPositionWorld" ) ) );
	}

	vec3_t hit_info::get_hit_position_local( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return vec3_t( );

		return *reinterpret_cast< vec3_t* >( entity + il2mgr::value( xs( "HitInfo" ), xs( "HitPositionLocal" ) ) );
	}

	vec3_t hit_info::get_hit_velocity( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return vec3_t( );

		return *reinterpret_cast< vec3_t* >( entity + il2mgr::value( xs( "HitInfo" ), xs( "ProjectileVelocity" ) ) );
	}

	float hit_info::get_hit_distance( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );

		if( !entity )
			return 0.f;

		return *reinterpret_cast< float* >( entity + il2mgr::value( xs( "HitInfo" ), xs( "ProjectileDistance" ) ) );
	}

	bool building_block::can_afford( int grade, int skin, base_player* player )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return false;

		uintptr_t method = offsets::buildingblock_canaffordupgrade;
		if( !method )
			return false;

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
			return false;

		auto CanAffordUpgrade = reinterpret_cast< bool( * )( uintptr_t, int, int, uintptr_t ) >( method_ptr );
		return spoof_ret( CanAffordUpgrade, entity, grade, skin, ( uintptr_t )player );
	}

	bool building_block::can_upgrade( int grade, int skin, base_player* player )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return false;

		uintptr_t method = offsets::buildingblock_canchangetograde;
		if( !method )
			return false;

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
			return false;

		auto CanChangeToGrade = reinterpret_cast< bool( * )( uintptr_t, int, int, uintptr_t ) >( method_ptr );
		return spoof_ret( CanChangeToGrade, entity, grade, skin, ( uintptr_t )player );
	}

	void building_block::upgrade( int grade, int skin, base_player* player )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t method = offsets::buildingblock_upgradetograde;
		if( !method )
			return;

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
			return;

		auto UpgradeToGrade = reinterpret_cast< void( * )( uintptr_t, int, int, uintptr_t ) >( method_ptr );
		spoof_ret( UpgradeToGrade, entity, grade, skin, ( uintptr_t )player );
	}

	bool item_icon::queued_for_looting( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return false;

		uintptr_t method = offsets::item_icon_queued_for_looting;
		if( !method )
			return false;

		return *reinterpret_cast< bool* >( entity + method );
	}

	void item_icon::run_timed_action( )
	{
		uintptr_t entity = reinterpret_cast< uintptr_t >( this );
		if( !entity )
			return;

		uintptr_t method = offsets::item_icon_run_timed_action;
		if( !method )
			return;

		uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
		if( !method_ptr )
			return;

		auto run_timed_action = reinterpret_cast< void( * )( uintptr_t ) >( method_ptr );
		spoof_ret( run_timed_action, entity );
	}
}
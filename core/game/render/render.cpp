#include "../../includes/hinclude.h"
#include "../offsets.hpp"

// create global definition of render class.
c_renderer g_render;

static uintptr_t draw_shader = NULL;
static bool has_drew_once = true;

void c_renderer::get_draw_shader( ) {
	draw_shader = il2mgr::methods::object_new( il2mgr::init_class( xs( "Material" ), xs( "UnityEngine" ) ) );
}

void c_renderer::set_up_draw_shader( ) {
	if( !draw_shader )
		return get_draw_shader( );

	static uintptr_t shader = g_sdk.find( "Hidden/Internal-Colored" );
	if( !shader
		|| !has_drew_once )
		return;

	g_sdk.create_shader( draw_shader, shader );
	g_sdk.set_material_int( draw_shader, "_SrcBlend", 5 );
	g_sdk.set_material_int( draw_shader, "_DstBlend", 10 );
	g_sdk.set_material_int( draw_shader, "_Cull", 0 );
	g_sdk.set_material_int( draw_shader, "_ZWrite", 0 );
	g_sdk.dont_destroy_on_load( draw_shader );
	has_drew_once = false;
}

void c_renderer::begin_gl_draw( begin_mode mode ) {
	if( !draw_shader )
		return get_draw_shader( );

	g_sdk.push_matrix( );
	g_sdk.set_pass( draw_shader, 0 );
	g_sdk.begin( mode );
}

void c_renderer::draw_circle( vec2_t pos, float radius, color_t color ) {
	if( !draw_shader )
		return get_draw_shader( );

	begin_gl_draw( begin_mode::line_strip );
	g_sdk.set_gl_color( color );
	for( float num = 0.f; num < PIX2 * 2.f; num += 0.05f ) {
		g_sdk.vertex( vec3_t( cos( num ) * radius + pos.x, sin( num ) * radius + pos.y, 0 ) );
		g_sdk.vertex( vec3_t( cos( num + 0.05f ) * radius + pos.x, sin( num + 0.05f ) * radius + pos.y, 0 ) );
	}
	g_sdk.end( );
	g_sdk.pop_matrix( );
}

void c_renderer::gl_triangle( vec2_t pos, vec2_t pos1, vec2_t pos2, color_t col )
{
	if( !draw_shader )
		return get_draw_shader( );

	begin_gl_draw( begin_mode::triangles );
	g_sdk.set_gl_color( col );
	g_sdk.vertex( vec3_t( pos.x, pos.y, 0 ) );
	g_sdk.vertex( vec3_t( pos1.x, pos1.y, 0 ) );
	g_sdk.vertex( vec3_t( pos2.x, pos2.y, 0 ) );

	g_sdk.end( );
	g_sdk.pop_matrix( );
}

void c_renderer::draw_line( vec2_t start, vec2_t end, color_t color ) {
	if( !draw_shader )
		return get_draw_shader( );

	begin_gl_draw( begin_mode::lines );
	g_sdk.set_gl_color( color );
	g_sdk.vertex( vec3_t( start.x, start.y, 0 ) );
	g_sdk.vertex( vec3_t( end.x, end.y, 0 ) );

	g_sdk.end( );
	g_sdk.pop_matrix( );
}

void c_renderer::get_n_white_texture( ) {
	g_cheat.white_texture = g_sdk.get_white_texture( );
}

void c_renderer::horizontal_line( vec2_t pos, float size, color_t clr )
{
	if( !g_cheat.white_texture )
		return get_n_white_texture( );

	g_sdk.set_draw_color( clr );

	g_sdk.draw_texture( vec4_t( pos.x, pos.y, size, 1 ), g_cheat.white_texture );
}

void c_renderer::vertical_line( vec2_t pos, float size, color_t clr )
{
	if( !g_cheat.white_texture )
		return get_n_white_texture( );

	g_sdk.set_draw_color( clr );

	g_sdk.draw_texture( vec4_t( pos.x, pos.y, 1, size ), g_cheat.white_texture );
}

void c_renderer::outline_box( vec2_t position, vec2_t size, color_t color, float girth )
{
	if( !g_cheat.white_texture )
		return get_n_white_texture( );

	g_sdk.set_draw_color( color );

	g_sdk.draw_texture( vec4_t( position.x, position.y, girth, size.y ), g_cheat.white_texture );
	g_sdk.draw_texture( vec4_t( position.x + size.x, position.y, girth, size.y + 1 ), g_cheat.white_texture );
	g_sdk.draw_texture( vec4_t( position.x, position.y, size.x, girth ), g_cheat.white_texture );
	g_sdk.draw_texture( vec4_t( position.x, position.y + size.y, size.x, girth ), g_cheat.white_texture );
}

void c_renderer::draw_filled_rect( vec2_t position, vec2_t size, color_t color )
{
	if( !g_cheat.white_texture )
		return get_n_white_texture( );

	g_sdk.set_draw_color( color );
	g_sdk.draw_texture( vec4_t( position.x, position.y, size.x, size.y ), g_cheat.white_texture );
}

void c_renderer::draw_filled_rect( float x, float y, float width, float height, color_t color )
{
	if( !g_cheat.white_texture )
		return get_n_white_texture( );

	g_sdk.set_draw_color( color );
	g_sdk.draw_texture( vec4_t( x, y, width, height ), g_cheat.white_texture );
}

void c_renderer::draw_filled_rect( vec4_t position, color_t color )
{
	if( !g_cheat.white_texture )
		return get_n_white_texture( );

	g_sdk.set_draw_color( color );
	g_sdk.draw_texture( position, g_cheat.white_texture );
}

void c_renderer::line( vec2_t point1, vec2_t point2, color_t color )
{
	if( !g_cheat.white_texture )
		return get_n_white_texture( );

	g_sdk.set_draw_color( color );
	if( ( point1.x - point2.x ) < 1.f )
		g_sdk.draw_texture( vec4_t( point1.x, point1.y, point1.x - point2.x, 1.f ), g_cheat.white_texture );
	else
		g_sdk.draw_texture( vec4_t( point1.x, point1.y, 1.f, point1.y - point2.y ), g_cheat.white_texture );
}

void c_renderer::label( vec4_t position, std::string text, color_t color, bool centered, int font_size )
{
	if( !g_cheat.draw_label )
		return;

	g_sdk.set_draw_font_size( g_cheat.draw_label, font_size );

	g_sdk.set_draw_alignment( g_cheat.draw_label, centered ? 0x4 : 0x0 );

	//if( centered )
	//	position.x -= .5 * ( text.length( ) * font_size );

	uintptr_t method = offsets::gui_label;
	if( !method )
		return;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return;

	auto label = reinterpret_cast< void( * )( vec4_t, il2mgr::il2cppstring*, uintptr_t ) >( method_ptr );

	auto contents = il2mgr::il2cppstring::New( text.c_str( ) );

	g_sdk.set_draw_color( color );
	spoof_ret( label, position, contents, g_cheat.draw_label );
}

void c_renderer::draw_text( vec4_t position, std::string text, color_t color, bool centered, int font_size, font_flags_t flags, color_t outline_color ) {
	// measure.
	outline_color.a *= color.a;

	if( flags & outline ) {
		label( vec4_t( position.x, position.y - 1, position.z, position.w ), text, outline_color, centered, font_size ); //up
		label( vec4_t( position.x, position.y + 1, position.z, position.w ), text, outline_color, centered, font_size ); //down
		label( vec4_t( position.x + 1, position.y, position.z, position.w ), text, outline_color, centered, font_size ); //right
		label( vec4_t( position.x - 1, position.y, position.z, position.w ), text, outline_color, centered, font_size ); //left
		label( vec4_t( position.x + 1, position.y + 1, position.z, position.w ), text, outline_color, centered, font_size ); //down-right
		label( vec4_t( position.x - 1, position.y + 1, position.z, position.w ), text, outline_color, centered, font_size ); //down-left
		label( vec4_t( position.x + 1, position.y - 1, position.z, position.w ), text, outline_color, centered, font_size ); //up-right
		label( vec4_t( position.x - 1, position.y - 1, position.z, position.w ), text, outline_color, centered, font_size ); //up-left
	}
	if( flags & dropshadow ) {
		label( vec4_t( position.x + 1, position.y + 1, position.z, position.w ), text, outline_color, centered, font_size );
	}

	label( position, text, color, centered, font_size );
}

void c_renderer::ddraw_line( vec3_t start, vec3_t end, color_t color, float duration, bool distanceFade, bool ztest )
{
	uintptr_t method = offsets::ddraw_line;
	if( !method )
		return;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return;

	auto line = reinterpret_cast< void( * )( vec3_t, vec3_t, color_t, float, bool, bool ) >( method_ptr );
	spoof_ret( line, start, end, color, duration, distanceFade, ztest );
}

void c_renderer::ddraw_sphere( vec3_t start, vec3_t end, color_t color, float duration, bool distanceFade )
{
	uintptr_t method = offsets::ddraw_sphere;
	if( !method )
		return;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return;

	auto sphere = reinterpret_cast< void( * )( vec3_t, vec3_t, color_t, float, bool ) >( method_ptr );
	spoof_ret( sphere, start, end, color, duration, distanceFade );
}

void c_renderer::ddraw_arrow( vec3_t start, vec3_t end, float size, color_t color, float duration )
{
	uintptr_t method = offsets::ddraw_arrow;
	if( !method )
		return;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return;

	auto arrow = reinterpret_cast< void( * )( vec3_t, vec3_t, float, color_t, float ) >( method_ptr );
	spoof_ret( arrow, start, end, size, color, duration );
}

void c_renderer::ddraw_text( const char* text, vec3_t pos, color_t color, float duration )
{
	uintptr_t method = offsets::ddraw_text;
	if( !method )
		return;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return;

	auto drawtext = reinterpret_cast< void( * )( il2mgr::il2cppstring*, vec3_t, color_t, float ) >( method_ptr );
	spoof_ret( drawtext, il2mgr::il2cppstring::New( text ), pos, color, duration );
}

void c_renderer::ddraw_get( )
{
	uintptr_t method = offsets::ddraw_get;
	if( !method )
		return;

	uintptr_t method_ptr = *reinterpret_cast< uintptr_t* >( method );
	if( !method_ptr )
		return;

	auto Get = reinterpret_cast< void( * )( ) >( method_ptr );
	spoof_ret( Get );
}
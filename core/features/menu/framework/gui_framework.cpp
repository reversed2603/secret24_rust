#include "gui_framework.h"
#include "../../../game/sdk.hpp"
#include "../../options.h"
#include "../../aimbot/aimbot.h"

// create global definition of framework class.
c_framework g_framework;

bool c_framework::get_lmb( )
{
	static int delay = 0;

	if( g_sdk.get_key_down( key_code::Mouse0 ) 
		&& delay < 1 )
	{
		delay = 10;
		return true;
	}

	delay--;

	return false;
}

vec2_t c_framework::get_cursor( int child ) {
	switch( child ) {
	case 1:
		return cursor1;
		break;
	case 2:
		return cursor2;
		break;
	default:
		return cursor1;
		break;
	}

	// as default return cursor1
	return cursor1;
}

bool c_framework::get_rmb( )
{
	static int delay = 0;

	if( g_sdk.get_key_down( key_code::Mouse1 )
		&& delay < 1 )
	{
		delay = 10;
		return true;
	}

	delay--;

	return false;
}

bool c_framework::get_ins( )
{
	static int delay = 0;

	if( g_sdk.get_key_down( key_code::Insert )
		&& delay < 1 )
	{
		delay = 10;
		return true;
	}

	delay--;

	return false;
}

bool c_framework::is_hovering( vec2_t position, vec2_t size )
{
	vec3_t cursor = g_cheat.mouse_pos;
	cursor.y = ( g_cheat.screen_size.y - cursor.y );

	return ( cursor.x > position.x 
		&& cursor.x < ( position.x + size.x )
		&& cursor.y > position.y 
		&& cursor.y < ( position.y + size.y ) );
}

void c_framework::create_tab( std::string name, int index, int offset )
{
	auto hovering = is_hovering( vec2_t( position.x + 12, position.y + 33 + ( 45 * index ) ), vec2_t( 100, 35 ) );

	g_render.draw_filled_rect( vec4_t( position.x + 12, position.y + 33 + ( 45 * index ), 100, 35 ),
		selected_tab == index || hovering ? color_t( 25, 25, 25, alpha ) : color_t( 20, 20, 20, alpha ) );

	g_render.outline_box( vec2_t( position.x + 11, position.y + 32 + ( 45 * index ) ), vec2_t( 101, 36 ),
		elements_outline_color.alpha( alpha, true ) );

	g_render.draw_filled_rect( vec4_t( position.x + 11, position.y + 32 + ( 45 * index ), 2, 37 ),
		selected_tab == index ? options::accent_color.alpha( alpha, true ) :
		hovering ? color_t( 132, 142, 156, alpha ) : color_t( 25, 25, 25, alpha ) );

	if( hovering 
		&& lmb )
		selected_tab = index;

	g_render.draw_text( vec4_t( position.x + 12, position.y + 33 + ( 45 * index ), 100, 35 ), name, text_color.alpha( alpha, true ), true, 11, dropshadow );
}

void c_framework::create_label( std::string text, int child, bool centered )
{
	vec2_t cursor = get_cursor( child );

	g_render.draw_text( vec4_t( cursor.x, cursor.y - 2, 150, 20 ), text, text_color.alpha( alpha, true ), centered, 12, dropshadow );

	switch( child )
	{
	case 1:
		cursor1.y += 22;
		break;
	case 2:
		cursor2.y += 22;
		break;
	default:
		break;
	}
}
	
void c_framework::create_combo_box( std::vector< std::string > list, int* selected, int child )
{
	vec2_t cursor = get_cursor( child );

	const bool left_hovered = is_hovering( vec2_t( cursor.x, cursor.y - 3 ), vec2_t( 14, 20 ) );
	const bool right_hovered = is_hovering( vec2_t( cursor.x + 141, cursor.y - 2 ), vec2_t( 14, 20 ) );

	g_render.draw_text( vec4_t( cursor.x, cursor.y - 3, 150, 20 ), xs( "<" ),
		left_hovered ? color_t( 255, 245, 245 ) : text_color.alpha( alpha, true ), false, 11, dropshadow );

	g_render.draw_text( vec4_t( cursor.x, cursor.y - 2, 150, 20 ), list[ *selected ],
		text_color.alpha( alpha, true ), true, 11, dropshadow );

	g_render.draw_text( vec4_t( cursor.x + 141, cursor.y - 2, 150, 20 ), xs( ">" ),
		right_hovered ? color_t( 249, 255, 245 ) : text_color.alpha( alpha, true ), false, 11, dropshadow );

	int list_size = list.size( ) - 1;

	if( *selected < 1 
		&& left_hovered
		&& lmb )
	{	
		*selected = list_size;
	}
	else if( *selected > 0 
		&& left_hovered
		&& lmb )
	{	
		--* selected;
	}
	else if( *selected >= list_size
		&& right_hovered 
		&& lmb )
	{
		*selected = 0;
	}
	else if( *selected < list_size
		&& right_hovered 
		&& lmb )
	{
		++* selected;
	}
	else if( left_hovered
		&& rmb )
	{
		*selected = 0;
	}

	switch( child )
	{
	case 1:
		cursor1.y += 22;
		break;
	case 2:
		cursor2.y += 22;
		break;
	default:
		break;
	}
}

void c_framework::create_check_box( std::string name, bool* value, int child )
{
	vec2_t cursor = get_cursor( child );
			
	const bool hovered = is_hovering( vec2_t( cursor.x - 3, cursor.y - 2 ), vec2_t( 80, 16 ) );

	g_render.draw_filled_rect( vec4_t( cursor.x, cursor.y, 14, 14 ), color_t( 20, 20, 20, alpha ) );
	g_render.outline_box( vec2_t( cursor.x, cursor.y ), vec2_t( 14, 14 ), elements_outline_color.alpha( alpha, true ) );

	if( *value
		|| hovered )
		g_render.draw_filled_rect( vec4_t( cursor.x + 3, cursor.y + 3, 9, 9 ), *value ? options::accent_color.alpha( alpha, true ) : color_t( 132, 142, 156, alpha ) );

	g_render.draw_text( vec4_t( cursor.x + 19, cursor.y - 2, 150, 20 ), name, text_color.alpha( alpha, true ), false, 11 );

	if( hovered 
		&& lmb )
		*value = !*value;

	switch( child )
	{
	case 1:
		cursor1.y += 22;
		break;
	case 2:
		cursor2.y += 22;
		break;
	default:
		break;
	}
}

void c_framework::slider_float( std::string name, float* value, float min, float max, int child )
{
	vec2_t cursor = get_cursor( child );

	const float mouse_x = g_sdk.get_mouse_pos( ).x;

	const bool hovered = is_hovering( vec2_t( cursor.x - 1, cursor.y + 17 ), vec2_t( max_width + 2, 10 ) );

	g_render.draw_filled_rect( vec4_t( cursor.x, cursor.y + 15, max_width, 4 ), background_color.alpha( alpha, true ) );
	g_render.outline_box( vec2_t( cursor.x, cursor.y + 15 ), vec2_t( max_width, 4 ), elements_outline_color.alpha( alpha, true ) );

	float to_set = ( ( mouse_x - cursor.x ) / max_width * max );

	*value = std::clamp( *value, min, max );

	if( hovered 
		&& g_sdk.get_key( key_code::Mouse0 ) )
		*value = to_set;

	if( *value > 0.f ) {
		g_render.draw_filled_rect( vec4_t( cursor.x + 2, cursor.y + 17, ( ( ( hovered ? to_set : *value ) * max_width ) / max ) - 2, 2 ),
			hovered ? color_t( 132, 142, 156 ).alpha( alpha, true ) : options::accent_color.alpha( alpha, true ) );
	}

	std::string normal_value = g_math.remove_trailing_zeros( hovered ? to_set : *value );

	g_render.draw_text( vec4_t( cursor.x, cursor.y - 4, 150, 20 ), name, text_color.alpha( alpha, true ), false, 11, dropshadow );
	g_render.draw_text( vec4_t( cursor.x + max_width - 15, cursor.y - 4, 150, 20 ), 
		normal_value.c_str( ),
		text_color.alpha( alpha, true ), false, 11, dropshadow );
		
	switch( child )
	{
	case 1:
		cursor1.y += 23;
		break;
	case 2:
		cursor2.y += 23;
		break;
	default:
		break;
	}
}

void c_framework::slider_int( std::string name, int* value, int min, int max, int child )
{
	vec2_t cursor = get_cursor( child );

	const float mouse_x = g_sdk.get_mouse_pos( ).x;

	const bool hovered = is_hovering( vec2_t( cursor.x - 1, cursor.y + 17 ), vec2_t( max_width + 2, 10 ) );

	g_render.draw_filled_rect( vec4_t( cursor.x, cursor.y + 15, max_width, 4 ), background_color.alpha( alpha, true ) );
	g_render.outline_box( vec2_t( cursor.x, cursor.y + 15 ), vec2_t( max_width, 4 ), elements_outline_color.alpha( alpha, true ) );

	int to_set = static_cast< int >( ( mouse_x - cursor.x ) / max_width * max );

	static int delay = 0;
	if( delay > 1 )
		--delay;

	*value = std::clamp( *value, min, max );

	if( hovered 
		&& g_sdk.get_key( key_code::Mouse0 ) )
		*value = to_set;

	if( *value > 0 ) {
		g_render.draw_filled_rect( vec4_t( cursor.x + 2, cursor.y + 17, ( ( ( hovered ? to_set : *value ) * max_width ) / max ) - 2, 2 ),
			hovered ? color_t( 132, 142, 156, alpha ) : options::accent_color.alpha( alpha, true ) );
	}

	std::string normal_value = std::to_string( hovered ? to_set : *value );

	g_render.draw_text( vec4_t( cursor.x, cursor.y - 4, 150, 20 ), name, text_color.alpha( alpha, true ), false, 11, dropshadow );
	g_render.draw_text( vec4_t( cursor.x + max_width - 15, cursor.y - 4, 150, 20 ), 
		normal_value.c_str( ),
		text_color.alpha( alpha, true ), false, 11, dropshadow );
		
	switch( child )
	{
	case 1:
		cursor1.y += 23;
		break;
	case 2:
		cursor2.y += 23;
		break;
	default:
		break;
	}
}

void c_framework::create_hotkey( std::string name, int* key, int child )
{
	elements_count++;

	vec2_t size = vec2_t( 50.f, 23.f );

	vec2_t cursor = get_cursor( child );

	vec2_t pos = cursor;

	const bool hovered = is_hovering( pos, size );
	const bool pressed_lmb = lmb;

	std::string text = name + ": " + "[" + g_aimbot.get_key_from_combo( *key ) + "]";

	if( active_hotkey == elements_count )
	{
		text = name + ": " + "[~]";

		if( !g_sdk.get_key( key_code::Mouse0	) )
			pressed_key = false;

		if( !pressed_key )
		{
			for( int code = 0; code < ( int )key_code::Mouse6; code++ ) {
				if( g_sdk.get_key( code ) ) { 
					*key = code;
					active_hotkey = -1;
				}
			}
		}
	}
	else
	{
		if( pressed_lmb ) {
			if( hovered )
			{
				pressed_key = true;
				active_hotkey = elements_count;
			}
		}
	}
	g_render.draw_text( vec4_t( pos.x + 3.f, pos.y, 150, 20 ), text, text_color.alpha( alpha, true ), false, 11 );

	switch( child )
	{
	case 1:
		cursor1.y += 23;
		break;
	case 2:
		cursor2.y += 23;
		break;
	default:
		break;
	}
}

void c_framework::color_pixel( vec2_t pos, vec2_t size, color_t* original, color_t color )
{		
	g_render.draw_filled_rect( pos, size, color );

	const bool hovered = is_hovering( pos, size );

	if( original->r == color.r && original->g == color.g && original->b == color.b )
		g_render.outline_box( pos, size, color_t( 0.f, 0.f, 0.f, alpha ) );

	if( hovered ) {
		g_render.outline_box( pos, size, color_t( 45, 45, 45, alpha ) );

		if( g_sdk.get_key( key_code::Mouse0 ) )
			*original = color;
	}
}

void c_framework::color_picker( std::string name, color_t* color, int child )
{
	++elements_count;

	// set this to full alpha.
	color->a = 255.f;

	vec2_t size = vec2_t( 11, 11 );

	vec2_t cursor = get_cursor( child );

	vec2_t pos = cursor;

	const bool hovered = is_hovering( pos, size );
		
	g_render.draw_filled_rect( vec4_t( pos.x, pos.y, 14, 14 ), hovered ? color_t( 40, 40, 40, alpha ) : background_color.alpha( alpha, true ) );

	color_t render_color = *color;
	g_render.draw_filled_rect( vec4_t( pos.x + 3, pos.y + 3, 9, 9 ), render_color.alpha( alpha, true ) );

	g_render.outline_box( vec2_t( pos.x, pos.y ), vec2_t( 14, 14 ), hovered ? color_t( 25, 25, 25, alpha ) : elements_outline_color.alpha( alpha, true ) );

	g_render.draw_text( vec4_t( pos.x + size.x + 8.f, pos.y - 2.f, 150, 20 ), name, text_color.alpha( alpha, true ), false, 11 );

	if( active_picker == elements_count )
	{
		vec2_t color_size = vec2_t( 125, 125 );

		bool hover_picker = is_hovering( pos, vec2_t( color_size.x, color_size.y - 60 ) );

		vec2_t pixel_size = vec2_t( color_size.x / 12, color_size.y / 12 );
		pos.x += 90;

		g_render.draw_filled_rect( vec4_t( pos.x + pixel_size.x, pos.y + pixel_size.y, pixel_size.x * 9, pixel_size.y * 9 ), color_t( 40, 40, 40, alpha ) );

		g_render.outline_box( vec2_t( pos.x + pixel_size.x, pos.y + pixel_size.y ), vec2_t( pixel_size.x * 9, pixel_size.y * 9 ), elements_outline_color.alpha( alpha, true ) );

		//0
		{
			color_pixel( vec2_t( pos.x + pixel_size.x, pos.y + pixel_size.y ), pixel_size, color, color_t( 174, 235, 253, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x, pos.y + pixel_size.y * 2 ), pixel_size, color, color_t( 136, 225, 251, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x, pos.y + pixel_size.y * 3 ), pixel_size, color, color_t( 108, 213, 250, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x, pos.y + pixel_size.y * 4 ), pixel_size, color, color_t( 89, 175, 213, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x, pos.y + pixel_size.y * 5 ), pixel_size, color, color_t( 76, 151, 177, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x, pos.y + pixel_size.y * 6 ), pixel_size, color, color_t( 60, 118, 140, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x, pos.y + pixel_size.y * 7 ), pixel_size, color, color_t( 43, 85, 100, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x, pos.y + pixel_size.y * 8 ), pixel_size, color, color_t( 32, 62, 74, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x, pos.y + pixel_size.y * 9 ), pixel_size, color, color_t( 255, 255, 255, alpha ) );
		}
		//1
		{
			color_pixel( vec2_t( pos.x + pixel_size.x * 1, pos.y + pixel_size.y ), pixel_size, color, color_t( 175, 205, 252, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 1, pos.y + pixel_size.y * 2 ), pixel_size, color, color_t( 132, 179, 252, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 1, pos.y + pixel_size.y * 3 ), pixel_size, color, color_t( 90, 152, 250, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 1, pos.y + pixel_size.y * 4 ), pixel_size, color, color_t( 55, 120, 250, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 1, pos.y + pixel_size.y * 5 ), pixel_size, color, color_t( 49, 105, 209, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 1, pos.y + pixel_size.y * 6 ), pixel_size, color, color_t( 38, 83, 165, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 1, pos.y + pixel_size.y * 7 ), pixel_size, color, color_t( 28, 61, 120, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 1, pos.y + pixel_size.y * 8 ), pixel_size, color, color_t( 20, 43, 86, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 1, pos.y + pixel_size.y * 9 ), pixel_size, color, color_t( 247, 247, 247, alpha ) );
		}
		//2
		{
			color_pixel( vec2_t( pos.x + pixel_size.x * 2, pos.y + pixel_size.y ), pixel_size, color, color_t( 153, 139, 250, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 2, pos.y + pixel_size.y * 2 ), pixel_size, color, color_t( 101, 79, 249, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 2, pos.y + pixel_size.y * 3 ), pixel_size, color, color_t( 64, 50, 230, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 2, pos.y + pixel_size.y * 4 ), pixel_size, color, color_t( 54, 38, 175, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 2, pos.y + pixel_size.y * 5 ), pixel_size, color, color_t( 39, 31, 144, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 2, pos.y + pixel_size.y * 6 ), pixel_size, color, color_t( 32, 25, 116, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 2, pos.y + pixel_size.y * 7 ), pixel_size, color, color_t( 21, 18, 82, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 2, pos.y + pixel_size.y * 8 ), pixel_size, color, color_t( 16, 13, 61, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 2, pos.y + pixel_size.y * 9 ), pixel_size, color, color_t( 228, 228, 228, alpha ) );
		}
		//3
		{
			color_pixel( vec2_t( pos.x + pixel_size.x * 3, pos.y + pixel_size.y ), pixel_size, color, color_t( 194, 144, 251, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 3, pos.y + pixel_size.y * 2 ), pixel_size, color, color_t( 165, 87, 249, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 3, pos.y + pixel_size.y * 3 ), pixel_size, color, color_t( 142, 57, 239, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 3, pos.y + pixel_size.y * 4 ), pixel_size, color, color_t( 116, 45, 184, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 3, pos.y + pixel_size.y * 5 ), pixel_size, color, color_t( 92, 37, 154, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 3, pos.y + pixel_size.y * 6 ), pixel_size, color, color_t( 73, 29, 121, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 3, pos.y + pixel_size.y * 7 ), pixel_size, color, color_t( 53, 21, 88, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 3, pos.y + pixel_size.y * 8 ), pixel_size, color, color_t( 37, 15, 63, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 3, pos.y + pixel_size.y * 9 ), pixel_size, color, color_t( 203, 203, 203, alpha ) );
		}
		//4
		{
			color_pixel( vec2_t( pos.x + pixel_size.x * 4, pos.y + pixel_size.y ), pixel_size, color, color_t( 224, 162, 197, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 4, pos.y + pixel_size.y * 2 ), pixel_size, color, color_t( 210, 112, 166, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 4, pos.y + pixel_size.y * 3 ), pixel_size, color, color_t( 199, 62, 135, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 4, pos.y + pixel_size.y * 4 ), pixel_size, color, color_t( 159, 49, 105, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 4, pos.y + pixel_size.y * 5 ), pixel_size, color, color_t( 132, 41, 89, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 4, pos.y + pixel_size.y * 6 ), pixel_size, color, color_t( 104, 32, 71, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 4, pos.y + pixel_size.y * 7 ), pixel_size, color, color_t( 75, 24, 51, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 4, pos.y + pixel_size.y * 8 ), pixel_size, color, color_t( 54, 14, 36, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 4, pos.y + pixel_size.y * 9 ), pixel_size, color, color_t( 175, 175, 175, alpha ) );
		}
		//5
		{
			color_pixel( vec2_t( pos.x + pixel_size.x * 5, pos.y + pixel_size.y ), pixel_size, color, color_t( 235, 175, 176, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 5, pos.y + pixel_size.y * 2 ), pixel_size, color, color_t( 227, 133, 135, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 5, pos.y + pixel_size.y * 3 ), pixel_size, color, color_t( 219, 87, 88, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 5, pos.y + pixel_size.y * 4 ), pixel_size, color, color_t( 215, 50, 36, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 5, pos.y + pixel_size.y * 5 ), pixel_size, color, color_t( 187, 25, 7, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 5, pos.y + pixel_size.y * 6 ), pixel_size, color, color_t( 149, 20, 6, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 5, pos.y + pixel_size.y * 7 ), pixel_size, color, color_t( 107, 14, 4, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 5, pos.y + pixel_size.y * 8 ), pixel_size, color, color_t( 77, 9, 3, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 5, pos.y + pixel_size.y * 9 ), pixel_size, color, color_t( 144, 144, 144, alpha ) );
		}
		//6
		{
			color_pixel( vec2_t( pos.x + pixel_size.x * 6, pos.y + pixel_size.y ), pixel_size, color, color_t( 241, 187, 171, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 6, pos.y + pixel_size.y * 2 ), pixel_size, color, color_t( 234, 151, 126, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 6, pos.y + pixel_size.y * 3 ), pixel_size, color, color_t( 229, 115, 76, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 6, pos.y + pixel_size.y * 4 ), pixel_size, color, color_t( 227, 82, 24, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 6, pos.y + pixel_size.y * 5 ), pixel_size, color, color_t( 190, 61, 15, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 6, pos.y + pixel_size.y * 6 ), pixel_size, color, color_t( 150, 48, 12, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 6, pos.y + pixel_size.y * 7 ), pixel_size, color, color_t( 107, 34, 8, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 6, pos.y + pixel_size.y * 8 ), pixel_size, color, color_t( 79, 25, 6, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 6, pos.y + pixel_size.y * 9 ), pixel_size, color, color_t( 113, 113, 113, alpha ) );
		}
		//7
		{
			color_pixel( vec2_t( pos.x + pixel_size.x * 7, pos.y + pixel_size.y ), pixel_size, color, color_t( 245, 207, 169, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 7, pos.y + pixel_size.y * 2 ), pixel_size, color, color_t( 240, 183, 122, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 7, pos.y + pixel_size.y * 3 ), pixel_size, color, color_t( 236, 159, 74, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 7, pos.y + pixel_size.y * 4 ), pixel_size, color, color_t( 234, 146, 37, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 7, pos.y + pixel_size.y * 5 ), pixel_size, color, color_t( 193, 111, 28, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 7, pos.y + pixel_size.y * 6 ), pixel_size, color, color_t( 152, 89, 22, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 7, pos.y + pixel_size.y * 7 ), pixel_size, color, color_t( 110, 64, 16, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 7, pos.y + pixel_size.y * 8 ), pixel_size, color, color_t( 80, 47, 12, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 7, pos.y + pixel_size.y * 9 ), pixel_size, color, color_t( 82, 82, 82, alpha ) );
		}
		//8
		{
			color_pixel( vec2_t( pos.x + pixel_size.x * 8, pos.y + pixel_size.y ), pixel_size, color, color_t( 247, 218, 170, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 8, pos.y + pixel_size.y * 2 ), pixel_size, color, color_t( 244, 200, 124, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 8, pos.y + pixel_size.y * 3 ), pixel_size, color, color_t( 241, 182, 77, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 8, pos.y + pixel_size.y * 4 ), pixel_size, color, color_t( 239, 174, 44, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 8, pos.y + pixel_size.y * 5 ), pixel_size, color, color_t( 196, 137, 34, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 8, pos.y + pixel_size.y * 6 ), pixel_size, color, color_t( 154, 108, 27, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 8, pos.y + pixel_size.y * 7 ), pixel_size, color, color_t( 111, 77, 19, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 8, pos.y + pixel_size.y * 8 ), pixel_size, color, color_t( 80, 56, 14, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 8, pos.y + pixel_size.y * 9 ), pixel_size, color, color_t( 54, 54, 54, alpha ) );
		}
		//9
		{
			color_pixel( vec2_t( pos.x + pixel_size.x * 9, pos.y + pixel_size.y ), pixel_size, color, color_t( 254, 243, 187, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 9, pos.y + pixel_size.y * 2 ), pixel_size, color, color_t( 253, 237, 153, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 9, pos.y + pixel_size.y * 3 ), pixel_size, color, color_t( 253, 231, 117, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 9, pos.y + pixel_size.y * 4 ), pixel_size, color, color_t( 254, 232, 85, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 9, pos.y + pixel_size.y * 5 ), pixel_size, color, color_t( 242, 212, 53, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 9, pos.y + pixel_size.y * 6 ), pixel_size, color, color_t( 192, 169, 42, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 9, pos.y + pixel_size.y * 7 ), pixel_size, color, color_t( 138, 120, 30, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 9, pos.y + pixel_size.y * 8 ), pixel_size, color, color_t( 101, 87, 22, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 9, pos.y + pixel_size.y * 9 ), pixel_size, color, color_t( 29, 29, 29, alpha ) );
		}
		//10
		{
			color_pixel( vec2_t( pos.x + pixel_size.x * 10, pos.y + pixel_size.y ), pixel_size, color, color_t( 247, 243, 185, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 10, pos.y + pixel_size.y * 2 ), pixel_size, color, color_t( 243, 239, 148, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 10, pos.y + pixel_size.y * 3 ), pixel_size, color, color_t( 239, 232, 111, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 10, pos.y + pixel_size.y * 4 ), pixel_size, color, color_t( 235, 229, 76, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 10, pos.y + pixel_size.y * 5 ), pixel_size, color, color_t( 208, 200, 55, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 10, pos.y + pixel_size.y * 6 ), pixel_size, color, color_t( 164, 157, 43, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 10, pos.y + pixel_size.y * 7 ), pixel_size, color, color_t( 118, 114, 31, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 10, pos.y + pixel_size.y * 8 ), pixel_size, color, color_t( 86, 82, 21, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 10, pos.y + pixel_size.y * 9 ), pixel_size, color, color_t( 9, 9, 9, alpha ) );
		}
		//11
		{
			color_pixel( vec2_t( pos.x + pixel_size.x * 11, pos.y + pixel_size.y ), pixel_size, color, color_t( 218, 232, 182, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 11, pos.y + pixel_size.y * 2 ), pixel_size, color, color_t( 198, 221, 143, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 11, pos.y + pixel_size.y * 3 ), pixel_size, color, color_t( 181, 210, 103, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 11, pos.y + pixel_size.y * 4 ), pixel_size, color, color_t( 154, 186, 76, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 11, pos.y + pixel_size.y * 5 ), pixel_size, color, color_t( 130, 155, 64, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 11, pos.y + pixel_size.y * 6 ), pixel_size, color, color_t( 102, 121, 50, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 11, pos.y + pixel_size.y * 7 ), pixel_size, color, color_t( 74, 88, 36, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 11, pos.y + pixel_size.y * 8 ), pixel_size, color, color_t( 54, 64, 26, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 11, pos.y + pixel_size.y * 9 ), pixel_size, color, color_t( 0, 0, 0, alpha ) );
		}
		//12
		{
			color_pixel( vec2_t( pos.x + pixel_size.x * 12, pos.y + pixel_size.y ), pixel_size, color, color_t( 225, 255, 125, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 12, pos.y + pixel_size.y * 2 ), pixel_size, color, color_t( 170, 161, 255, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 12, pos.y + pixel_size.y * 3 ), pixel_size, color, color_t( 161, 255, 252, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 12, pos.y + pixel_size.y * 4 ), pixel_size, color, color_t( 127, 252, 73, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 12, pos.y + pixel_size.y * 5 ), pixel_size, color, color_t( 255, 84, 54, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 12, pos.y + pixel_size.y * 6 ), pixel_size, color, color_t( 255, 138, 54, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 12, pos.y + pixel_size.y * 7 ), pixel_size, color, color_t( 255, 54, 54, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 12, pos.y + pixel_size.y * 8 ), pixel_size, color, color_t( 54, 87, 255, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 12, pos.y + pixel_size.y * 9 ), pixel_size, color, color_t( 0, 255, 187, alpha ) );
		}
		//12
		{
			color_pixel( vec2_t( pos.x + pixel_size.x * 13, pos.y + pixel_size.y ), pixel_size, color, color_t( 255, 0, 255, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 13, pos.y + pixel_size.y * 2 ), pixel_size, color, color_t( 255, 255, 0, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 13, pos.y + pixel_size.y * 3 ), pixel_size, color, color_t( 0, 255, 255, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 13, pos.y + pixel_size.y * 4 ), pixel_size, color, color_t( 0, 255, 0, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 13, pos.y + pixel_size.y * 5 ), pixel_size, color, color_t( 255, 0, 125, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 13, pos.y + pixel_size.y * 6 ), pixel_size, color, color_t( 125, 0, 255, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 13, pos.y + pixel_size.y * 7 ), pixel_size, color, color_t( 125, 125, 255, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 13, pos.y + pixel_size.y * 8 ), pixel_size, color, color_t( 255, 125, 125, alpha ) );
			color_pixel( vec2_t( pos.x + pixel_size.x * 13, pos.y + pixel_size.y * 9 ), pixel_size, color, color_t( 255, 255, 125, alpha ) );
		}

		if( !hover_picker 
			&& lmb )
			active_picker = -1;	
	}
	else
	{
		if( hovered 
			&& lmb )
			active_picker = elements_count;
	}

	switch( child )
	{
	case 1:
		cursor1.y += 21;
		break;
	case 2:
		cursor2.y += 21;
		break;
	default:
		break;
	}
}

void c_framework::begin( )
{
	vec3_t cursor = g_cheat.mouse_pos;

	if( g_sdk.get_key( key_code::Mouse0 ) 
		&& is_hovering( position, vec2_t( size.x, 25 ) ) )
	{
		cursor.y = g_cheat.screen_size.y - cursor.y;

		x = cursor.x - size.x / 2.f;
		y = cursor.y - 10.f;
	}

	elements_count = 0;

	// background
	g_render.draw_filled_rect( vec4_t( position.x, position.y + 28, size.x + 180, size.y ), outline_color.alpha( alpha, true ) );
	g_render.outline_box( vec2_t( position.x, position.y + 28 ), vec2_t( size.x + 180, size.y ), options::accent_color.alpha( alpha, true ) );

	// separator line
	g_render.draw_filled_rect( vec4_t( position.x + 125, position.y + 29, 2, size.y - 2 ), color_t( 20, 20, 20, alpha ) );
	g_render.outline_box( vec2_t( position.x + 125, position.y + 29 ), vec2_t( 2, size.y - 2 ), color_t( 50, 50, 50, alpha ) );

	// first sub-tab.
	g_render.draw_filled_rect( vec4_t( position.x + 135, position.y + 35, 300, size.y - 13 ), color_t( 15, 15, 15, alpha ) );
	g_render.outline_box( vec2_t( position.x + 135, position.y + 34 ), vec2_t( 300, size.y - 14 ), elements_outline_color.alpha( alpha, true ) );

	// second sub-tab.
	g_render.draw_filled_rect( vec4_t( position.x + 440, position.y + 35, 300, size.y - 13 ), color_t( 15, 15, 15, alpha ) );
	g_render.outline_box( vec2_t( position.x + 440, position.y + 34 ), vec2_t( 300, size.y - 14 ), elements_outline_color.alpha( alpha, true ) );
}

void c_framework::end( )
{
	static bool has_initializated = false;

	size = vec2_t( 575, 855 );
	if( !has_initializated ) {
		if( !g_cheat.screen_size.is_zero( ) ) {
			x = g_cheat.screen_size.x / 2.f - size.x;
			y = g_cheat.screen_size.y / 2.f;
		}
		has_initializated = true;
	}
	position = vec2_t( x, y );

	lmb = get_lmb( );
	rmb = get_rmb( );
	cursor1 = vec2_t( position.x + 150, position.y + 45 );
	cursor2 = vec2_t( position.x + 455, position.y + 45 );
}
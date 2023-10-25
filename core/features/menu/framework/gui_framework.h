#pragma once
#include "../../../includes/includes.hpp"

// pre-declare.
enum class key_code;

class c_framework
{
public:
	vec2_t cursor1 = vec2_t( ), cursor2 = vec2_t( ),
		size = vec2_t( ), position = vec2_t( );

	bool in_alpha{ };
	float x{ }, y{ };
	int selected_tab = 0;
	bool lmb{ }, rmb{ }, open{ true };
	float alpha{ 255.f };

	color_t background_color = color_t( 25, 25, 25, alpha ), 
		outline_color = color_t( 15, 15, 15, alpha ), text_color = color_t( 225, 225, 225, alpha ), elements_outline_color = color_t( 48, 48, 48, alpha );

	int max_width = 250;

	int active_picker = -1, active_hotkey = -1;
	int elements_count;
	bool pressed_key = false;

	void create_hotkey( std::string name, int* key, int child );
	void color_pixel( vec2_t pos, vec2_t size, color_t* original, color_t color );
	void color_picker( std::string name, color_t* color, int child );

	bool get_lmb( );

	vec2_t get_cursor( int child );

	bool get_rmb( );

	bool get_ins( );

	bool is_hovering( vec2_t position, vec2_t size );

	void create_tab( std::string name, int index, int offset );

	void create_label( std::string text, int child, bool centered = false );

	void create_combo_box( std::vector< std::string > list, int* selected, int child );

	void create_check_box( std::string name, bool* value, int child );

	void slider_float( std::string name, float* value, float min, float max, int child );
	void slider_int( std::string name, int* value, int min, int max, int child );

	void begin( );

	void end( );
};

extern c_framework g_framework;
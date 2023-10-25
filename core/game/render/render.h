#pragma once
#include "../../vector/vector2.hpp"
#include "../../vector/vector3.hpp"
#include "../../vector/color.hpp"
#include "../../vector/vector4.hpp"
#include <string>

enum font_flags_t : int {
	none = 0,
	dropshadow,
	outline
};

enum begin_mode : int {
	lines = 1,
	line_strip,
	triangles = 4,
	triangle_strip,
	quads = 7
};

class c_renderer {
public:
	void get_draw_shader( );

	void set_up_draw_shader( );

	void begin_gl_draw( begin_mode mode );

	void draw_circle( vec2_t pos, float radius, color_t color );

	void gl_triangle( vec2_t pos, vec2_t pos1, vec2_t pos2, color_t col );

	void draw_line( vec2_t start, vec2_t end, color_t color );

	void draw_filled_rect( vec2_t position, vec2_t size, color_t color );
	void draw_filled_rect( vec4_t position, color_t color );
	void draw_filled_rect( float x, float y, float width, float height, color_t color );

	void get_n_white_texture( );

	void ddraw_line( vec3_t start, vec3_t end, color_t color, float duration = 7.0f, bool distanceFade = true, bool ztest = true );
	void ddraw_sphere( vec3_t start, vec3_t end, color_t color, float duration = 7.0f, bool distanceFade = true );
	void ddraw_arrow( vec3_t start, vec3_t end, float size, color_t color, float duration = 2.f );
	void ddraw_text( const char* text, vec3_t pos, color_t color, float duration = 0.5f );

	void horizontal_line( vec2_t pos, float size, color_t clr );
	void vertical_line( vec2_t pos, float size, color_t clr );

	void outline_box( vec2_t position, vec2_t size, color_t color, float girth = 1.f );

	void line( vec2_t point1, vec2_t point2, color_t color );
	void label( vec4_t position, std::string text, color_t color, bool centered = false, 
		int font_size = 12 );

	void draw_text( vec4_t position, std::string text, color_t color, bool centered = false, 
		int font_size = 12, font_flags_t flags = none, color_t outline_color = color_t( 0, 0, 0, 175 ) );

	void ddraw_get( );
};

extern c_renderer g_render;
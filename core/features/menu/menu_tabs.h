#pragma once
#include "../../includes/includes.hpp"

class c_menu {
public:
	int max_distance = 5000;

	enum color_tab_t {
		visible = 0,
		invisible = 1,
		npc_visible = 2,
		npc_invisible = 3
	};

	std::vector< std::string > bones = { xs( "head" ), xs( "neck" ), xs( "pelvis" ), xs( "dick" ) };

	std::vector< std::string > box_esp_color_tone = { xs( "green" ), xs( "turquoise" ), xs( "blue" ), xs( "purple" ) };

	std::vector< std::string > box_esp_mode = { xs( "off" ), xs( "normal" ), xs( "corner" ), xs( "3d box" ) };

	std::vector< std::string > aim_mode = { xs( "off" ), xs( "silent" ), xs( "memory" ) };

	std::vector< std::string > smooth_type = { xs( "off" ), xs( "constant" ), xs( "regular" ) };

	std::vector< std::string > chams_vector = { xs( "flat" ), xs( "hologram" ), xs( "invisible" ), xs( "galaxy" ), xs( "transparent" ), xs( "wireframe" ), xs( "circuit" ) };

	std::vector< std::string > cfg_vector = { xs( "rage" ), xs( "blatant" ), xs( "legit" ), xs( "secret" ), xs( "ziebel" ), xs( "alpha" ) };

	std::vector< std::string > color_list = { xs( "visible" ), xs( "invisible" ), xs( "npc visible" ), xs( "npc invisible" ) };

	std::vector< std::string > tab_list = { xs( "first" ), xs( "second" ) };

	std::vector< std::string > grade_tier_list = { xs( "none" ), xs( "wood" ), xs( "stone" ), xs( "metal" ), xs( "hqm" ) };

	std::vector< std::string > font_flags = { xs( "none" ), xs( "dropshadow" ), xs( "outline" ) };

	std::vector< std::string > tab_choice = { xs( "choice" ), xs( "colors" ), xs( "sliders" ) };

	std::vector< std::string > key_vector =
	{
		xs( "left mouse button" ), xs( "right mouse button" ),
		xs( "middle mouse button" ), xs( "x1 mouse button" ),
		xs( "x2 mouse button" ), xs( "control-break processing" ),
		xs( "backspace" ), xs( "tab" ), xs( "clear" ), xs( "enter" ),
		xs( "shift" ), xs( "ctrl" ), xs( "alt" ), xs( "caps lock" ),
		xs( "esc" ), xs( "space" ), xs( "a" ), xs( "b" ), xs( "c" ), xs( "d" ), xs( "e" ),
		xs( "f" ), xs( "g" ), xs( "h" ), xs( "i" ), xs( "j" ), xs( "k" ), xs( "l" ), xs( "m" ), xs( "n" ),
		xs( "o" ), xs( "p" ), xs( "q" ), xs( "r" ), xs( "s" ), xs( "t" ), xs( "u" ),
		xs( "v" ), xs( "w" ), xs( "x" ), xs( "y" ), xs( "z" ), xs( "f1" ), xs( "f2" ),
		xs( "f3" ), xs( "f4" ), xs( "f5" ), xs( "f6" ), xs( "f7" ), xs( "f8" ), xs( "f9" ),
		xs( "f10" ), xs( "f11" )
	};

	std::vector< std::string > default_gestures =
	{
		xs( "clap" ), xs( "friendly" ), xs( "thumbsdown" ),
		xs( "thumbsup" ), xs( "ok" ), xs( "point" ), xs( "shrug" ), xs( "victory" ),
		xs( "wave" ), xs( "cabbage patch" ), xs( "twist" )
	};

	/* draw menu tab */
	void draw_menu_tab( );

	/* draw aimbot tab */
	void draw_aimbot_tab( );

	/* draw visuals tab */
	void draw_visuals_tab( );

	/* draw world tab */
	void draw_worlds_tab( );
	
	/* draw combat tab */
	void draw_combat_tab( );

	/* draw time tab */
	void draw_time_tab( );

	/* draw movement tab */
	void draw_movement_tab( );

	/* draw misc tab */
	void draw_misc_tab( );

	/* draw modulations tab */
	void draw_modulations_tab( );

	/* draw automations tab */
	void draw_automations_tab( );

	/* draw menu */
	void draw_menu( );
};

extern c_menu g_menu;
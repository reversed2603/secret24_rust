#pragma once
#include "../../includes/includes.hpp"
#include "../../game/sdk.hpp"
#include "world_esp.hpp"

class c_esp
{
public:
	vec3_t manipulation_angle{ }, eye_manipulation_angle{ };
	core::bounds_t bbox{ };
	bool not_in_fly_action{ true };

	float maximum_eye_height{ }, melee_max_dist{ };

	font_flags_t font_flags{ };

	float indicators_spacing[ 2 ];
	float esp_spacing[ 6 ]; // uses 0 for weapon, then goes health, distance, show team id, knocked flag, ducking flag;

	color_t name_color{ 255, 255, 255 }, box_color{ 255, 255, 255 },
		skeleton_color{ 255, 255, 255 }, radar_color{ },
		oof_color{ 255, 255, 255 }, snap_lines_color{ 255, 255, 255 }, distance_color{ 255, 255, 255 }, weapon_color{ 255, 255, 255 },
		view_direction_color{ 255, 255, 255 }, knocked_color{ 0, 255, 0 }, ducking_color{ 255, 0, 0 },
		custom_health_color{ 255, 255, 255 }, health_text_color{ 255, 255, 255 };

	/* fly-hack violation related */
	float distance_vertical = 0.f, distance_horizontal = 0.f;
	float pause_time = 0.f;
	float current_horizontal_fly = 0.f, max_horizontal_fly = 0.f;
	float current_vertical_fly = 0.f, max_vertical_fly = 0.f;

	// for clothing / hotbars.
	bool  should_use_spacing{ };

	struct shot_record_t
	{
		float m_time{ };
		vec3_t m_start{ }, m_end{ };
		core::base_player* entity{ };
	};

	struct saved_position
	{
		bool is_home{ };
		vec3_t m_location{ };
		color_t color{ };
	};

	std::vector< saved_position > m_positions;

	std::vector< shot_record_t > m_shots;
	std::vector< core::base_player* > m_friends;

	void render_saved_positions( );
	void change_sky_ambient_color( );

	void draw_bullet_tracers( );

	void invoke_chams( core::base_player* );
	void draw_snap_lines( core::base_player* );
	void draw_health_text( core::base_player* );
	void draw_weapon( core::base_player* );
	void reset_fly_hack( );
	void draw_distance( core::base_player* );

	vec2_t radar_position = vec2_t( 20, 20 );
	vec2_t hotbar_position = vec2_t( 20, 20 );
	vec2_t clothes_position = vec2_t( 20, 20 );

	vec2_t info_bar_size = vec2_t( 175, 190 );

	void find_manipulate_angle( );
	
    void draw_knocked_flag( core::base_player* player );
    void draw_ducking_flag( core::base_player* player );

	void draw_name( core::base_player*, entity_type );
	void draw_box( core::base_player* );
    void draw_health( core::base_player* );
	void draw_hotbar( core::base_player* target );
	void draw_clothes( core::base_player* target );
	void draw_bones( core::base_player* );
	void draw_radar( core::base_player* );
	void draw_local_trails( );
	void draw_last_sent_tick( );

	void draw_out_of_fov_arrows( core::base_player* );
	void draw_view_direction( core::base_player* );

	void context_instance( core::base_player*, entity_type );

	void apply_fly_violation( );

	void fly_hack_bar( );
	void show_reload_bar( );
	void show_desync_bar( );

	core::base_entity* get_closest_object_of_class( std::string class_to_find, float max_dist = 250.f );
	void do_melee_attack( vec3_t pos, core::base_entity* entity, bool is_player = false );
};

extern c_esp g_esp;
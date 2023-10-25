#pragma once
#include "../../includes/includes.hpp"
#include "../../game/sdk.hpp"

class c_aimbot {
public:
	std::array< bone_list, 19 > scanning_bones = {
		head, spine1, spine2, spine3, spine4, pelvis, penis, neck,
		l_breast, r_breast, r_eye, l_eye, r_hip, r_knee,
		l_knee, l_hip, l_upperarm, r_upperarm, l_hip
	};

	void get_best_player( );
	void get_best_bone( );
	std::string get_key_from_combo( int key );
	void smooth_angles( vec2_t& angles, vec2_t local_view_angles );

	struct proj_weapon_mod
	{
		bool enabled{ };
		float scalar{ }, offset{ };
	};

	void update_weapon_information( );

	void start_movement_simulation( vec3_t& aim_pos, const vec3_t& from );

	// context..
	void process( );

	/*\ crucial data region /*/
	int aim_key;

	int aimbot_bone{ };
	vec2_t aim_angle{ };
	vec3_t shoot_position{ }, psilent_aim_angle{ };
	core::base_player* target{ };
	core::base_entity* best_helicopter{ };

	float bullet_speed{ FLT_MAX },
		bullet_gravity{ FLT_MAX },
		drag{ FLT_MAX }, closest_distance{ FLT_MAX };

	bool is_in_aim = false;
};

extern c_aimbot g_aimbot;
#include "aimbot.h"
#include "../options.h"
#include "../visuals/esp.h"

void c_aimbot::get_best_player( ) {
    target = NULL; // k to the y to the s
    closest_distance = FLT_MAX;

    for( int i = 0; i < g_cheat.player_list.size( ); i++ ) {
        core::base_player* player = g_cheat.player_list.at( i ).first;
		if( !player )
			continue;

        core::player_model* model = player->get_model( );
		if( !model )
			continue;

        float dist_to = g_cheat.local_pos.distance( model->get_position( ) );
        if( dist_to > options::aimbot::max_target_distance )
            continue;

		if( ( player->is_sleeping( ) 
            && !options::aimbot::aim_sleepers )
            || player->get_life_state( ) /* let's ignore dead players */
            || player == g_cheat.local
            || ( model->is_npc( ) 
            && !options::aimbot::aim_npc
            || ( player->is_knocked( )
            && !options::aimbot::aim_knocked ) ) )
            continue;

        vec3_t bone_position = player->get_bone_position( aimbot_bone );
        vec2_t bone_w2s = g_sdk.world_to_screen( bone_position );

        if( bone_w2s.is_zero( )
            || ( options::aimbot::aim_check
            && !player->is_visible( bone_position ) ) )
            continue;

        float length = g_cheat.screen_center.distance( bone_w2s );

        if( length < closest_distance
            && length < options::aimbot::fov_amount ) {
            closest_distance = length;
			target = player;

			for( auto& targets : g_esp.m_friends )
			{
				if( !targets )
					continue;

				core::player_model* model = targets->get_model( );
				if( !model )
					continue;

				if( target 
					&& target == targets ) {
					target = NULL;
					closest_distance = FLT_MAX;
				}
			}
        }
    }
}

void c_aimbot::get_best_bone( ) {
    if( !options::aimbot::aim_nearest_bone ) {
		switch( options::aimbot::aim_bone ) {
			case 0:
			{
				aimbot_bone = bone_list::head;
				break;
			}
			case 1:
			{
				aimbot_bone = bone_list::neck;
				break;
			}
			case 2:
			{
				aimbot_bone = bone_list::pelvis;
				break;
			}
			case 3:
			{
				aimbot_bone = bone_list::penis;
				break;
			}
		}
	}
    else {
        float closest = FLT_MAX;
        aimbot_bone = -1; // reset this too

        for( int i = 0; i < scanning_bones.size( ); i++ ) {
            vec3_t pos3d = target->get_bone_position( scanning_bones[ i ] );

            vec2_t pos = g_sdk.world_to_screen( pos3d );
            if( pos.is_zero( ) )
                continue;

            float length = g_cheat.screen_center.distance( pos );

            if( length < closest
                && length < options::aimbot::fov_amount ) {
                closest = length;
                aimbot_bone = scanning_bones[ i ];
            }
        }
    }
}

void c_aimbot::smooth_angles( vec2_t& angles, vec2_t local_view_angles ) {
	float smoothness = options::aimbot::smoothness_amount;
    if( smoothness ) {
		float smooth; // 0 is regular yaw, and 1 is pitch. 2 is being used for constant smooth.

	    vec2_t delta = ( angles - local_view_angles ).normalize( );

		float smoothing_value = 5.5f * ( smoothness / 100.f );
	    smooth = powf( 0.81f + smoothing_value, 0.4f );
	    smooth = min( 0.98f, smooth );

	    vec2_t new_delta = vec2_t( );

	    float coeff = ( 1.0f - smooth ) / delta.length( ) * 4.f;

	    // fast end
	    coeff = powf( coeff, 2.f ) * 80.f / smoothness;

	    coeff = min( 1.f, coeff );
	    new_delta = delta * coeff;

		angles = ( local_view_angles + new_delta );
    }
}

std::string c_aimbot::get_key_from_combo( int key ) {
	switch( key ) {
		case ( int )key_code::Mouse0:
		{
			return "lmouse";//lmouse button
			break;
		}
		case ( int )key_code::Mouse1:
		{
			return "rmouse";//rmouse button
			break;
		}
		case ( int )key_code::Mouse2:
		{
			return "middle mouse";//middle mouse button
			break;
		}
		case ( int )key_code::Mouse3:
		{
			return "x1 mbutton";//x1 mouse button
			break;
		}
		case ( int )key_code::Mouse4:
		{
			return "x2 mbutton";//x2 mouse button
			break;
		}
		case ( int )key_code::LeftControl:
		{
			return "lalt";//control break processing
			break;
		}
		case ( int )key_code::Backspace:
		{
			return "backspace";//backspace
			break;
		}
		case ( int )key_code::Tab:
		{
			return "tab";//tab
			break;
		}
		case ( int )key_code::Clear:
		{
			return "clear";//clear
			break;
		}
		case ( int )key_code::KeypadEnter:
		{
			return "enter";//enter
			break;
		}
		case ( int )key_code::LeftShift:
		{
			return "lshift";//shift
			break;
		}
		case ( int )key_code::RightControl:
		{
			return "rcontrol";//ctrl
			break;
		}
		case ( int )key_code::LeftAlt:
		{
			return "lalt";//alt
			break;
		}
		case ( int )key_code::CapsLock:
		{
			return "caps-lock";//caps lock
			break;
		}
		case ( int )key_code::Escape:
		{
			return "esc";//esc
			break;
		}
		case ( int )key_code::Space:
		{
			return "space";//space
			break;
		}
		case ( int )key_code::A:
		{
			return "a";//a
			break;
		}
		case ( int )key_code::B:
		{
			return "b";//b
			break;
		}
		case ( int )key_code::C:
		{
			return "c";//c
			break;
		}
		case ( int )key_code::D:
		{
			return "d";//d
			break;
		}
		case ( int )key_code::E:
		{
			return "e";//e
			break;
		}
		case ( int )key_code::F:
		{
			return "f";//f
			break;
		}
		case ( int )key_code::G:
		{
			return "g";//g
			break;
		}
		case ( int )key_code::H:
		{
			return "h";//h
			break;
		}
		case ( int )key_code::I:
		{
			return "i";//i
			break;
		}
		case ( int )key_code::J:
		{
			return "j";//j
			break;
		}
		case ( int )key_code::K:
		{
			return "k";//k
			break;
		}
		case ( int )key_code::L:
		{
			return "l";//L
			break;
		}
		case ( int )key_code::M:
		{
			return "m";//m
			break;
		}
		case ( int )key_code::N:
		{
			return "n";//n
			break;
		}
		case ( int )key_code::O:
		{
			return "o";//o
			break;
		}
		case ( int )key_code::P:
		{
			return "p";//p
			break;
		}
		case ( int )key_code::Q:
		{
			return "q";//q
			break;
		}
		case ( int )key_code::R:
		{
			return "r";//r
			break;
		}
		case ( int )key_code::S:
		{
			return "s";//s
			break;
		}
		case ( int )key_code::T:
		{
			return "t";//t
			break;
		}
		case ( int )key_code::U:
		{
			return "u";//u
			break;
		}
		case ( int )key_code::V:
		{
			return "v";//v
			break;
		}
		case ( int )key_code::W:
		{
			return "w";//w
			break;
		}
		case ( int )key_code::X:
		{
			return "x";//x
			break;
		}
		case ( int )key_code::Y:
		{
			return "y";//y
			break;
		}
		case ( int )key_code::Z:
		{
			return "z";//z
			break;
		}
		case ( int )key_code::F1: {
			return "f1";
			break;
		}
		case ( int )key_code::F2: {
			return "f2";
			break;
		}
		case ( int )key_code::F3: {
			return "f3";
			break;
		}
		case ( int )key_code::F4: {
			return "f4";
			break;
		}
		case ( int )key_code::F5: {
			return "f5";
			break;
		}
		case ( int )key_code::F6: {
			return "f6";
			break;
		}
		case ( int )key_code::F7: {
			return "f7";
			break;
		}
		case ( int )key_code::F8: {
			return "f8";
			break;
		}
		case ( int )key_code::F9: {
			return "f9";
			break;
		}
		case ( int )key_code::F10: {
			return "f10";
			break;
		}
		case ( int )key_code::F11: {
			return "f11";
			break;
		}
		default: {
			return "none";
			break;
		}
	}
	return "none";
}
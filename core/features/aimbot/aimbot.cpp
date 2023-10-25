#include "aimbot.h"
#include "../options.h"
#include "../../includes/includes.hpp"
#include "../visuals/esp.h"
#include "../../game/offsets.hpp"
#include "../../utilities/memory.hpp"

core::player_input* m_input{ };

// create global definition for aimbot class.
c_aimbot g_aimbot;

void c_aimbot::update_weapon_information( )
{
	core::base_player* local = g_cheat.local;
	if( !local )
		return;

    core::item* held_item = local->get_held_item( );
    if( !held_item )
		return;
		
	core::weapon_information bullet_info = held_item->get_weapon_information( );

    float bullet_velocity_scale = held_item->get_projectile_velocity_scale( );

    bullet_speed = bullet_info.bullet_speed;
    if( bullet_velocity_scale )
        bullet_speed *= bullet_velocity_scale;

    bullet_gravity = bullet_info.bullet_gravity;
    drag = bullet_info.drag;

    //g_render.draw_text( vec4_t( 100, 100, 35, 35 ), to_string( bullet_speed ), color_t( 255, 255, 255 ) );
    //g_render.draw_text( vec4_t( 100, 200, 35, 35 ), to_string( drag ), color_t( 255, 0, 255 ) );
    //g_render.draw_text( vec4_t( 100, 300, 35, 35 ), to_string( bullet_gravity ), color_t( 255, 0, 0 ) );
}

void c_aimbot::start_movement_simulation( vec3_t& aim_point, const vec3_t& from )
{
    shoot_position.clear( ); // clear this the fuck outta here.

    if( options::aimbot::should_simulate_movement ) {
        float distance = from.distance( aim_point );           

	    constexpr float time_step = 0.015625f;
	    float travelled{ }, y_speed{ }, travel_time{ };

	    for( float to_travel = 0.f; to_travel < distance; )
	    {
		    float speed_modifier = ( 1.f - ( time_step * drag ) );
		    bullet_speed *= speed_modifier;

		    if( bullet_speed <= 0.f 
                || bullet_speed >= 10000.f
                || travelled >= 10000.f 
                || travelled < 0.f )
			    break;

		    if( travel_time > 8.f )
			    break;

		    y_speed += ( ( ( 9.81f * bullet_gravity ) * time_step ) * speed_modifier );

		    to_travel += ( bullet_speed * time_step );
		    travelled += ( y_speed * time_step );
            travel_time += time_step;
	    }

        vec3_t velocity = target->get_model( )->get_velocity( ) * 0.75f;
	    if( velocity.y > 0.f )
		    velocity.y /= 3.25f;

	    aim_point.y += travelled;
	    aim_point += ( velocity * travel_time );
    }

	shoot_position = aim_point;
}

void c_aimbot::process( ) {
    if( options::aimbot::aim_type < 1 )
        return;

	// get our things to run aimbot..
    get_best_player( );

	core::base_player* local = g_cheat.local;

    if( !target
        || !local
        || g_cheat.cam_pos.is_zero( ) )
        return;

	core::item* held_item = local->get_held_item( );
	if( !held_item )
		return;

    if( held_item->is_melee( ) 
        || !held_item->is_gun( ) 
        || held_item->is_heal( ) )
        return;

    update_weapon_information( );

    m_input = local->get_input( );
    if( !m_input )
        return;

    vec2_t view_angles = m_input->get_view_angles( );
    if( view_angles.is_zero( ) )
        return shoot_position.clear( );

	/* we have shit ready, get our best bone to shoot at :p */
    get_best_bone( );

    vec3_t bone_position = target->get_bone_position( aimbot_bone );
    if( bone_position.is_zero( ) )
        return;

    /* update our weapon information before using any crucial data.. */
	start_movement_simulation( bone_position, g_cheat.cam_pos ); /* handle player prediction simulation */

    if( shoot_position.is_zero( ) ) // :P
        return;

	aim_angle = ( view_angles + ( g_math.unity_calculate_angle( g_cheat.cam_pos, shoot_position ) ) );

    if( !held_item->is_melee( ) 
        && held_item->is_gun( ) ) {
        aim_angle -= ( view_angles - m_input->get_recoil_angles( ) );
    }

    vec3_t silent_angle = vec3_t( shoot_position - g_cheat.cam_pos ); // now our aimbot also compensates for da recoilzz
    vec4_t quat_angle = vec4_t::quat_look_rot( silent_angle, vec3_t( 0, 1, 0 ) );
        
    if( options::aimbot::smooth_type > 0 )
        smooth_angles( aim_angle, view_angles );

    // normalize aimbot angles.
    aim_angle.normalize( );
    silent_angle.normalize( );

    is_in_aim = g_sdk.get_key( aim_key );
    if( !is_in_aim )
        return; // fuck it.

	core::player_eyes* eyes = local->get_eyes( );

    switch( options::aimbot::aim_type ) {
    case 1:
		if( eyes )
			eyes->set_body_rotation( quat_angle );
		else
			goto MEMORY_AIM;
        break;
    case 2:
		MEMORY_AIM:
        m_input->set_view_angles( aim_angle );
        break;
    }
}

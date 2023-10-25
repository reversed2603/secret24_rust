#include "esp.h"
#include <cmath>
#include "../aimbot/aimbot.h"

#include <Windows.h>
#include "../options.h"

#include "../../utilities/memory.hpp"
#include "../menu/framework/gui_framework.h"

// create global definition for esp class.
c_esp g_esp;

void draw_3d_box( vec3_t bottom, vec3_t head_pos, float wide, color_t col )
{
    vec3_t bottom_one = vec3_t( bottom.x + wide, bottom.y + wide, bottom.z );
    vec2_t bottom_one_pos = g_sdk.world_to_screen( bottom_one );

    vec3_t bottom_two = vec3_t( bottom.x - wide, bottom.y - wide, bottom.z );
    vec2_t bottom_two_pos = g_sdk.world_to_screen( bottom_two );

    vec3_t bottom_three = vec3_t( bottom.x + wide, bottom.y - wide, bottom.z );
    vec2_t bottom_three_pos = g_sdk.world_to_screen( bottom_three );

    vec3_t bottom_four = vec3_t( bottom.x - wide, bottom.y + wide, bottom.z );
    vec2_t bottom_four_pos = g_sdk.world_to_screen( bottom_four );

    vec3_t top_one = vec3_t( bottom.x + wide, bottom.y + wide, head_pos.z + 15 );
    vec2_t top_one_pos = g_sdk.world_to_screen( top_one );

    vec3_t top_two = vec3_t( bottom.x - wide, bottom.y - wide, head_pos.z + 15 );
    vec2_t top_two_pos = g_sdk.world_to_screen( top_two );

    vec3_t top_three = vec3_t( bottom.x + wide, bottom.y - wide, head_pos.z + 15 );
    vec2_t top_three_pos = g_sdk.world_to_screen( top_three );

    vec3_t top_four = vec3_t( bottom.x - wide, bottom.y + wide, head_pos.z + 15 );
    vec2_t top_four_pos = g_sdk.world_to_screen( top_four );

    g_render.draw_line( bottom_one_pos, bottom_three_pos, col );
    g_render.draw_line( bottom_three_pos, bottom_two_pos, col );
    g_render.draw_line( bottom_two_pos, bottom_four_pos, col );
    g_render.draw_line( bottom_four_pos, bottom_one_pos, col );

    g_render.draw_line( top_one_pos, top_three_pos, col );
    g_render.draw_line( top_three_pos, top_two_pos, col );
    g_render.draw_line( top_two_pos, top_four_pos, col );
    g_render.draw_line( top_four_pos, top_one_pos, col );

    g_render.draw_line( bottom_one_pos, top_one_pos, col );
    g_render.draw_line( bottom_two_pos, top_two_pos, col );
    g_render.draw_line( bottom_three_pos, top_three_pos, col );
    g_render.draw_line( bottom_four_pos, top_four_pos, col );
}

void c_esp::context_instance( core::base_player* player, entity_type type )
{
    core::player_model* model = player->get_model( );
    core::base_player* local = g_cheat.local;
    if( !local
        || player == local )
        return;

    bool npc = model->is_npc( );

	if( ( !options::visuals::draw_visuals
        || ( !options::visuals::can_show_sleepers 
		&& player->is_sleeping( ) ) 
		|| ( !options::visuals::can_show_knocked
		&& player->is_knocked( ) )
		|| ( !options::visuals::can_show_npc && npc )
		|| player->get_life_state( ) ) ) {
		return;
	}

    bool visible = player->is_visible( player->get_bone_position( head ) );

    if( npc ) {
        if( visible ) {
            name_color = options::visuals::npc_vis_name_color;
            box_color = options::visuals::npc_vis_box_color;

            skeleton_color = options::visuals::npc_vis_skeleton_color;
            radar_color = options::visuals::npc_vis_radar_color;
            oof_color = options::visuals::npc_vis_oof_color;
            snap_lines_color = options::visuals::npc_vis_snap_lines_color;
            distance_color = options::visuals::npc_vis_distance_color;
            weapon_color = options::visuals::npc_vis_weapon_color;
            view_direction_color = options::visuals::npc_vis_view_direction_color;
            knocked_color = options::visuals::npc_vis_knocked_color;
            ducking_color = options::visuals::npc_vis_ducking_color;
            custom_health_color = options::visuals::npc_vis_custom_health_color;
            health_text_color = options::visuals::npc_vis_health_text_color;
        }
        else {
            name_color = options::visuals::npc_name_color;
            box_color = options::visuals::npc_box_color;

            skeleton_color = options::visuals::npc_skeleton_color;
            radar_color = options::visuals::npc_radar_color;
            oof_color = options::visuals::npc_oof_color;
            snap_lines_color = options::visuals::npc_snap_lines_color;
            distance_color = options::visuals::npc_distance_color;
            weapon_color = options::visuals::npc_weapon_color;
            view_direction_color = options::visuals::npc_view_direction_color;
            knocked_color = options::visuals::npc_knocked_color;
            ducking_color = options::visuals::npc_ducking_color;
            custom_health_color = options::visuals::npc_custom_health_color;
            health_text_color = options::visuals::npc_health_text_color;
        }
    }
    else {
        if( visible ) {
            name_color = options::visuals::vis_name_color;
            box_color = options::visuals::vis_box_color;

            skeleton_color = options::visuals::vis_skeleton_color;
            radar_color = options::visuals::vis_radar_color;
            oof_color = options::visuals::vis_oof_color;
            snap_lines_color = options::visuals::vis_snap_lines_color;
            distance_color = options::visuals::vis_distance_color;
            weapon_color = options::visuals::vis_weapon_color;
            view_direction_color = options::visuals::vis_view_direction_color;
            knocked_color = options::visuals::vis_knocked_color;
            ducking_color = options::visuals::vis_ducking_color;
            custom_health_color = options::visuals::vis_custom_health_color;
            health_text_color = options::visuals::vis_health_text_color;
        }
        else {
            name_color = options::visuals::name_color;
            box_color = options::visuals::box_color;

            skeleton_color = options::visuals::skeleton_color;
            radar_color = options::visuals::radar_color;
            oof_color = options::visuals::oof_color;
            snap_lines_color = options::visuals::snap_lines_color;
            distance_color = options::visuals::distance_color;
            weapon_color = options::visuals::weapon_color;
            view_direction_color = options::visuals::view_direction_color;
            knocked_color = options::visuals::knocked_color;
            ducking_color = options::visuals::ducking_color;
            custom_health_color = options::visuals::custom_health_color;
            health_text_color = options::visuals::health_text_color;
        }
    }

	float dist_to = g_cheat.local_pos.distance( model->get_position( ) );
	if( dist_to > options::visuals::max_player_distance )
		return;

    bbox = core::get_bounds( player, 5.f );

    if( !bbox.on_screen ) {
        if( options::visuals::offscreen_arrows ) {
            draw_out_of_fov_arrows( player );
        }
    }
	else {
        if( options::visuals::show_name ) {
			draw_name( player, type );
		}
        if( options::visuals::box_type > 0 ) { 
			draw_box( player ); 
		}
        if( options::visuals::show_health )
		{
			draw_health( player );
		}
        if( options::visuals::draw_bones )
		{
			draw_bones( player );
		}
        if( options::visuals::show_lines 
            || options::aimbot::draw_target )
		{
			draw_snap_lines( player );
		}
        draw_view_direction( player );
        if( options::visuals::show_health_text )
        {
            draw_health_text( player );
        }
		draw_weapon( player ); // custom shit
		if( options::visuals::show_distance ) {
			draw_distance( player );
		}
        if( options::visuals::show_ducking_flag )
        {
            draw_ducking_flag( player );
        }
        if( options::visuals::show_knocked_flag )
        {
            draw_knocked_flag( player );
        }
        if( options::visuals::chams )
		{
			invoke_chams( player );
		}
	}

    if( options::visuals::draw_radar ) {
        draw_radar( player );
    }
}

void c_esp::draw_bullet_tracers( )
{
    if( !options::visuals::draw_tracers )
        return m_shots.clear( );

	if( m_shots.empty( ) )
		return;

    int font_size = 12;

    // keep this limited to 5 instances.
    while( m_shots.size( ) > 5 )
        m_shots.pop_back( );

    color_t color = options::visuals::tracers_color;

	for( size_t i = 0; i < m_shots.size( ); i++ )
	{
		auto& tr = m_shots[ i ];

        static float alpha = 0.f;

		float delta = g_sdk.get_time( ) - tr.m_time;
		if( ( delta > 1.0f
            || std::abs( delta ) > 3.f ) ) {

            alpha = std::lerp( alpha, 0.f, 0.025f );

            if( alpha < 0.1f )
			    m_shots.erase( m_shots.begin( ) + i );
        }
        else if( alpha < 1.f )
            alpha = std::lerp( alpha, 1.f, 0.025f );

        // measure alpha.
        color.a *= alpha;

        core::base_player* player = tr.entity;
        if( !player )
            continue;

        g_render.ddraw_line( tr.m_start, tr.m_end, color, 3.5f, false );
	}
}

vec2_t rotate_point( vec2_t to_rotate, vec2_t center, float angle )
{
    angle *= ( M_PI / 180.f );

    float ang_cos = cos( angle );
    float ang_sin = sin( angle );

    vec2_t to_return = vec2_t( );

    to_return.x = ( ( ang_cos * ( to_rotate.x - center.x ) - ang_sin * ( to_rotate.y - center.y ) ) + center.x );
    to_return.y = ( ( ang_sin * ( to_rotate.x - center.x ) + ang_cos * ( to_rotate.y - center.y ) ) + center.y );

    return to_return;
}

void c_esp::draw_local_trails( ) {
    core::base_player* local = g_cheat.local;
    if( !local )
        return;

    core::player_ticks* last_sent_tick = local->get_lastSentTick( );
    if( !last_sent_tick )
        return;

    g_render.ddraw_line( last_sent_tick->get_position( ), g_cheat.local_pos, options::visuals::trails_color, 2.5f, true, true );
}

void c_esp::draw_last_sent_tick( ) {
    core::base_player* local = g_cheat.local;
    if( !local )
        return;

    core::player_ticks* last_sent_tick = local->get_lastSentTick( );
    if( !last_sent_tick )
        return;

    g_render.ddraw_sphere( last_sent_tick->get_position( ), g_cheat.local_pos, color_t( 255, 0, 0 ), 2.5f, false );
}

void c_esp::draw_radar( core::base_player* player )
{
    vec2_t size = vec2_t( 4, 4 );
    float width = 200, height = 200;

    vec2_t screen_position = vec2_t( ), rotated_point = vec2_t( );
    vec2_t center = vec2_t( radar_position.x + ( width / 2 ), radar_position.y + 100 );
    vec2_t center_position = vec2_t( center.x, center.y );
        
    core::player_model* model = player->get_model( );
    if( !model )
        return;

    core::base_player* local = g_cheat.local;
    if( !local )
        return;

    core::player_input* input = local->get_input( );
    if( !input )
        return;

    vec3_t pos = model->get_position( );
    if( pos.is_zero( ) )
        return;

    vec2_t view_angles = input->get_view_angles( );
    if( view_angles.is_zero( ) )
        return;

    screen_position = vec2_t( ( -( g_cheat.local_pos.x - pos.x ) + center.x ),
        ( g_cheat.local_pos.z - pos.z ) + center.y );

    rotated_point = rotate_point( screen_position, center_position, ( 360.0f - view_angles.y ) );

    if( ( rotated_point.x < radar_position.x
        || rotated_point.y < radar_position.y
        || rotated_point.x > radar_position.x + ( width - size.x )
        || rotated_point.y > radar_position.y + ( height - size.y ) ) )
        return;

    g_render.draw_filled_rect( vec2_t( rotated_point.x, rotated_point.y ), vec2_t( 4, 4 ), radar_color );
    g_render.outline_box( vec2_t( rotated_point.x, rotated_point.y ), vec2_t( 4, 4 ), color_t( 10, 10, 10, 175 ) );

    g_render.draw_filled_rect( vec4_t( center.x, center.y, 4, 4 ), options::accent_color.alpha( 255, true ) );
    g_render.outline_box( vec2_t( center.x, center.y ), vec2_t( 4, 4 ), color_t( 10, 10, 10, 175 ) );
}

void c_esp::render_saved_positions( )
{
    core::base_player* local = g_cheat.local;
    if( !local )
        return;

    core::player_model* model = local->get_model( );
    if( !model )
        return;

    vec3_t local_pos = model->get_position( );
    if( local_pos.is_zero( ) )
        return;

    // make position higher than us.
    local_pos.y += 2;

    static int delay = 0;

    if( g_sdk.get_key_down( ( key_code )options::visuals::save_pos_key )
        && delay < 10 ) {
        delay = 10;
        m_positions.push_back( { options::visuals::is_home_pos, local_pos, options::visuals::pos_color } );
    }

    // remove delay by 1.
    --delay;

    if( g_sdk.get_key( options::visuals::remove_positions_key )
        && !m_positions.empty( ) )
        m_positions.pop_back( );

    for( int i = 0; i < m_positions.size( ); i++ ) {
        auto& pos = m_positions.at( i );
        if( pos.m_location.is_zero( ) )
            continue;

        vec2_t world_pos = g_sdk.world_to_screen( pos.m_location );
        if( world_pos.is_zero( ) )
            continue;

        std::string text = std::string( );

        if( pos.is_home )
            text = xs( "home pos" );
        else
            text = xs( "saved position" );

        text += xs( "[" ) + std::to_string( i );
        text += xs( "|" ) + std::to_string( int( g_cheat.local_pos.distance( pos.m_location ) ) ) + xs( "m" );
        text += xs( "]" );

        g_render.draw_text( vec4_t( world_pos.x, world_pos.y, 150, 20 ), text, pos.color, false, 12, font_flags );
    }
}

void c_esp::change_sky_ambient_color( ) {
    static uintptr_t sky = il2mgr::init_class( "TOD_Sky" );
    if( !sky )
        return;

	uintptr_t night = memory::read_chain< uintptr_t >( sky, { 0xB8, 0x0, 0x10, 0x20, 0x58 } );
	uintptr_t day = memory::read_chain< uintptr_t >( sky, { 0xB8, 0x0, 0x10, 0x20, 0x50 } );
	uintptr_t stars = memory::read_chain< uintptr_t >( sky, { 0xB8, 0x0, 0x10, 0x20, 0x70 } );
				
	if( stars ) {
		if( options::visuals::world::stars )
			*reinterpret_cast< int* >( stars + 0x14 ) = options::visuals::world::brightness_stars_amount;
		if( options::visuals::world::stars_size )
			*reinterpret_cast< int* >( stars + 0x10 ) = options::visuals::world::size_stars_amount;
	}

	if( options::aimbot::exploits::time::time_modifier )
        g_game.set_admin_time( options::aimbot::exploits::time::time_speed );

	if( night
		&& day 
		&& options::visuals::world::ambient ) {

		*reinterpret_cast< float* >( night + 0x48 ) = options::visuals::world::light_value;
		*reinterpret_cast< float* >( night + 0x50 ) = options::visuals::world::ambient_value;
		*reinterpret_cast< float* >( day + 0x48 ) = options::visuals::world::light_value;
		*reinterpret_cast< float* >( day + 0x50 ) = options::visuals::world::ambient_value;
	}

    color_t ambient = options::visuals::world::ambient_color;
    color_t sky_clr = options::visuals::world::sky_color;

    // modify alpha so it's not so bright as it is.

    if( options::visuals::world::change_world_color ) {
        uintptr_t components = *reinterpret_cast< uintptr_t* >( sky + 0xA8 );
        if( !components )
            return;

        uintptr_t scattering = *reinterpret_cast< uintptr_t* >( components + 0x1A0 );
        if( !scattering )
            return;

        uintptr_t sky_color = *reinterpret_cast< uintptr_t* >( day + 0x28 );
        if( !sky_color )
            return;

        uintptr_t ambient_color = *reinterpret_cast< uintptr_t* >( day + 0x40 );
        if( !ambient_color )
            return;

        uintptr_t sky_gradient = *reinterpret_cast< uintptr_t* >( sky_color + 0x10 );
        if( !sky_gradient )
            return;

        uintptr_t ambient_gradient = *reinterpret_cast< uintptr_t* >( ambient_color + 0x10 );
        if( !ambient_gradient )
            return;

        *reinterpret_cast< color_t* >( sky_gradient ) = color_t( sky_clr.r, sky_clr.g, sky_clr.b, 255.f );

        *reinterpret_cast< color_t* >( ambient_gradient ) = color_t( ambient.r, ambient.g, ambient.b, 255.f );
    }
}

void c_esp::find_manipulate_angle( ) {
    core::base_player* target = g_aimbot.target;
    if( !target ) {
        manipulation_angle.clear( );
        return;
    }

    core::base_player* local = g_cheat.local;
    if( !local ) {
        manipulation_angle.clear( );
        return;
    }

    core::transform* transform = local->get_transform( );
    if( !transform ) {
        manipulation_angle.clear( );
        return;
    }

    core::player_eyes* eyes = local->get_eyes( );
    if( !eyes ) {
        manipulation_angle.clear( );
        return;
    }

    vec3_t re_p = transform->get_position( ) + transform->up( ) * ( core::player_eyes::get_eyeOffset( ).y + eyes->get_viewoffset( ).y );

    vec3_t choice = vec3_t( );

    vec3_t z = target->get_bone_position( head );

    if( target->is_visible( z ) ) {
        manipulation_angle.clear( );
        return;
    }

	float max_v_multiplier = 6.2f;
	float v_maximum_eye_height = maximum_eye_height / max_v_multiplier;

    vec3_t right = eyes->get_bodyright( );
    vec3_t forward = eyes->get_movementforward( );

    std::array< vec3_t, 60 > arr = {
        vec3_t( right.x * maximum_eye_height, 0.f, right.z * maximum_eye_height ), // big right

        vec3_t( right.x * ( maximum_eye_height / 2 ), 0.65f, right.z * ( maximum_eye_height / 2 ) ), // small right up

        vec3_t( right.x * ( maximum_eye_height / 2 ), -0.65f, right.z * 2.f ), // small right down

        vec3_t( -( right.x * ( maximum_eye_height / 2 ) ), 0.65f, -( right.z * ( maximum_eye_height / 2 ) ) ), // small left up

        vec3_t( -( right.x * maximum_eye_height ), 1.5f, -( right.z * maximum_eye_height ) ), // big left up

        vec3_t( -( right.x * ( maximum_eye_height / 2 ) ), -0.65f, -( right.z * ( maximum_eye_height / 2 ) ) ), // small left down

        vec3_t( -( forward.x * maximum_eye_height ), 0.f, -( forward.z * maximum_eye_height ) ), // big backward

        vec3_t( forward.x * ( maximum_eye_height / 2 ), 0.65f, forward.z * ( maximum_eye_height / 2 ) ),// small forward up

        vec3_t( forward.x * ( maximum_eye_height / 2 ), -0.65f, forward.z * ( maximum_eye_height / 2 ) ),// small forward down

        vec3_t( -( forward.x * ( maximum_eye_height / 2 ) ), 0.f, -( forward.z * ( maximum_eye_height / 2 ) ) ),// small reverse

        vec3_t( -( forward.x * ( maximum_eye_height / 2 ) ), 0.65f, -( forward.z * ( maximum_eye_height / 2 ) ) ),// small reverse up

        vec3_t( -( forward.x * ( maximum_eye_height / 2 ) ), -0.65f, -( forward.z * ( maximum_eye_height / 2 ) ) ),// small reverse down

        vec3_t( right.x * maximum_eye_height, 1.5f, right.z * ( maximum_eye_height ) ) * 0.9f, // big diag-up-right

        vec3_t( -right.x * ( maximum_eye_height ), 1.5f, -right.z * ( maximum_eye_height ) ) * 0.9f, // big diag-up-left

        vec3_t( right.x * maximum_eye_height, -1.5f, right.z * ( maximum_eye_height ) ) * 0.9f, // big diag-down-right

        vec3_t( -right.x * ( maximum_eye_height ), -1.5f, -right.z * ( maximum_eye_height ) ) * 0.9f, // big diag-up-left

        vec3_t( ( right.x / 2 ) * maximum_eye_height, 1.5f, ( right.z / 2 ) * ( maximum_eye_height ) ), // big diag-up-right

        vec3_t( -( right.x / 2 ) * ( maximum_eye_height ), 1.5f, -( right.z / 2 ) * ( maximum_eye_height ) ), // big diag-up-left

        vec3_t( ( right.x / 2 ) * maximum_eye_height, -1.5f, ( right.z / 2 ) * ( maximum_eye_height ) ), // big diag-down-right

        vec3_t( -( right.x / 2 ) * ( maximum_eye_height ), -1.5f, -( right.z / 2 ) * ( maximum_eye_height ) ), // big diag-up-left

        vec3_t( ( forward.x / 2 ) * ( maximum_eye_height / 2 ), 1.5f, ( forward.z / 2 ) * ( maximum_eye_height / 2 ) ), // big diag-up-forward

        vec3_t( -( ( forward.x / 2 ) * ( maximum_eye_height / 2 ) ), 1.5f, -( ( forward.z / 2 ) * maximum_eye_height / 2 ) ), // big diag-up-backward

        vec3_t( 0.f, ( v_maximum_eye_height / 5 ), 0.f ), // small up

		vec3_t( 0.f, v_maximum_eye_height, 0.f ), // big up

		vec3_t( 0.f, -0.75f, 0.f ), // small down

		vec3_t( 0.f, -1.5f, 0.f ), // big down

        vec3_t( 1.5f, -v_maximum_eye_height, 0.f ), // big right-down

        vec3_t( -1.5f, v_maximum_eye_height, 0.f ), // big right-down

        vec3_t( 1.5f, v_maximum_eye_height, 0.f ), // big right-down

        vec3_t( maximum_eye_height, -v_maximum_eye_height, 0.f ), // big right-down

		vec3_t( right.x * ( maximum_eye_height / 2 ), 0.f, right.z * ( maximum_eye_height / 2 ) ), // small right

		vec3_t( right.x * ( maximum_eye_height / 2 ), 0.75f, right.z * ( maximum_eye_height / 2 ) ), // small right up

		vec3_t( right.x * maximum_eye_height, 1.5f, right.z * maximum_eye_height ), // big right up

		vec3_t( right.x * ( maximum_eye_height / 2 ), -0.75f, right.z * 2.f ), // small right down

		vec3_t( right.x * maximum_eye_height, -1.5f, right.z * maximum_eye_height ), // big right down

		vec3_t( -( right.x * ( maximum_eye_height / 2 ) ), 0.f, -( right.z * ( maximum_eye_height / 2 ) ) ), // small left

		vec3_t( -( right.x * maximum_eye_height ), 0.f, -( right.z * maximum_eye_height ) ), // big left

		vec3_t( -( right.x * ( maximum_eye_height / 2 ) ), 0.75f, -( right.z * ( maximum_eye_height / 2 ) ) ), // small left up

		vec3_t( -( right.x * ( maximum_eye_height / 2 ) ), -0.75f, -( right.z * ( maximum_eye_height / 2 ) ) ), // small left down

		vec3_t( -( right.x * maximum_eye_height ), -1.5f, -( right.z * maximum_eye_height ) ), // big left down 

		vec3_t( forward.x * maximum_eye_height, 0.f, forward.z * maximum_eye_height ), // big forward

		vec3_t( forward.x * ( maximum_eye_height / 2 ), 0.75f, forward.z * ( maximum_eye_height / 2 ) ),// small forward up

		vec3_t( forward.x * maximum_eye_height, 1.5f, forward.z * maximum_eye_height ), // big forward up

		vec3_t( forward.x * ( maximum_eye_height / 2 ), -0.75f, forward.z * ( maximum_eye_height / 2 ) ),// small forward down

		vec3_t( forward.x * maximum_eye_height, -1.5f, forward.z * maximum_eye_height ), // big forward down

		vec3_t( -( forward.x * ( maximum_eye_height / 2 ) ), 0.75f, -( forward.z * ( maximum_eye_height / 2 ) ) ),// small reverse up

		vec3_t( -( forward.x * 4.f ), 1.5f, -( forward.z * 4.f ) ), // big reverse up

		vec3_t( -( forward.x * ( maximum_eye_height / 2 ) ), -0.75f, -( forward.z * ( maximum_eye_height / 2 ) ) ),// small reverse down

		vec3_t( -( forward.x * maximum_eye_height ), -1.5f, -( forward.z * maximum_eye_height ) ), // big reverse down

		vec3_t( right.x * maximum_eye_height, v_maximum_eye_height, right.z * ( maximum_eye_height ) ) * 0.9f, // big diag-up-right

		vec3_t( -right.x * ( maximum_eye_height ), ( v_maximum_eye_height ), -right.z * ( maximum_eye_height ) ) * 0.9f, // big diag-up-left

		vec3_t( right.x * maximum_eye_height, -v_maximum_eye_height, right.z * ( maximum_eye_height ) ) * 0.9f, // big diag-down-right

		vec3_t( -right.x * ( maximum_eye_height ), ( -v_maximum_eye_height ), -right.z * ( maximum_eye_height ) ) * 0.9f, // big diag-up-left

		vec3_t( ( right.x / 2 ) * maximum_eye_height, v_maximum_eye_height, ( right.z / 2 ) * ( maximum_eye_height ) ), // big diag-up-right

		vec3_t( -( right.x / 2 ) * ( maximum_eye_height ), ( v_maximum_eye_height ), -( right.z / 2 ) * ( maximum_eye_height ) ), // big diag-up-left

		vec3_t( ( right.x / 2 ) * maximum_eye_height, -v_maximum_eye_height, ( right.z / 2 ) * ( maximum_eye_height ) ), // big diag-down-right

		vec3_t( -( right.x / 2 ) * ( maximum_eye_height ), ( -v_maximum_eye_height ), -( right.z / 2 ) * ( maximum_eye_height ) ), // big diag-up-left

		vec3_t( ( forward.x / 2 ) * ( maximum_eye_height / 2 ), ( v_maximum_eye_height / 1 ), ( forward.z / 2 ) * ( maximum_eye_height / 2 ) ), // big diag-up-forward

		vec3_t( -( ( forward.x / 2 ) * ( maximum_eye_height / 2 ) ), ( v_maximum_eye_height / 1 ), -( ( forward.z / 2 ) * maximum_eye_height / 2 ) ), // big diag-up-backward
    };

    for( vec3_t s : arr ) {
        vec3_t point = re_p + s;

        if( !g_sdk.is_visible( point, re_p ) )
            continue;

		g_render.ddraw_arrow( re_p, eyes->get_position( ), 0.3f, color_t( 255, 255, 255 ), 0.01f);

        if( !g_sdk.is_visible( target->get_bone_position( head ), point ) )
            continue;

        eye_manipulation_angle = point;
        choice = s;
        break;
    }
    if( choice.is_zero( ) ) {
        manipulation_angle.clear( );
        return;
    }

    manipulation_angle = choice;
}

void c_esp::invoke_chams( core::base_player* player )
{
    static uintptr_t shader = { };
    static uintptr_t type_obj = il2mgr::type_object( "UnityEngine", "Shader" );
    switch( options::visuals::chams_type ) {
    case 0:
        shader = g_sdk.load_asset( g_cheat.asset_bundle, "chams.shader", type_obj );
        break;
    case 1:
        shader = g_sdk.load_asset( g_cheat.chams_bundle, "hologramshader.shader", type_obj );
        break;
    case 2:
        shader = g_sdk.load_asset( g_cheat.chams_bundle, "invisible.shader", type_obj );
        break;
    case 3:
        shader = g_sdk.load_asset( g_cheat.chams_bundle, "assets\\sinevfx\\galaxymaterials\\resources\\shaders\\galaxymaterial.shader", type_obj );
        break;
    case 4:
        shader = g_sdk.load_asset( g_cheat.chams_bundle, "chams.shader", type_obj );
        break;
    case 5:
        shader = g_sdk.load_asset( g_cheat.wireframe_chams_bundle, "assets\\bundledassets\\wireframetransparentculled.shader", type_obj );
        break;
    case 6:
        shader = g_sdk.load_asset( g_cheat.circuit_chams_bundle, "nebnel.shader", type_obj );
        break;
    }
    if( !shader )
        return;

    core::player_model* model = player->get_model( );
    if( !model )
        return;

    uintptr_t multi_mesh = model->get_multimesh( );
    if( !multi_mesh )
        return;

    laddy_list< uintptr_t >* renderers = g_sdk.get2renderers( multi_mesh );
    if( !renderers )
        return;

    for( int i = 0; i < renderers->get_size( ); i++ )
    {
        uintptr_t renderer = renderers->get_value( i );
        if( !renderer )
            return;

        const uintptr_t material = g_sdk.get_material( renderer );
        if( !material )
            return;

        if( g_sdk.get_shader( material ) != shader )
            g_sdk.set_shader( material, shader );

        if( options::visuals::chams_type == 5 ) {
            g_sdk.set_color( material, "_WireColor", 
                color_t( options::visuals::chams_color.r * 255.f, options::visuals::chams_color.g * 255.f, options::visuals::chams_color.b * 255.f ) );

            g_sdk.set_color( material, "_BaseColor", 
                color_t( options::visuals::chams_color.r * 255.f, options::visuals::chams_color.g * 255.f, options::visuals::chams_color.b * 255.f ) );

            g_sdk.set_material_int( material, "_WireThickness", 
                1 );
        }

        if( options::visuals::chams_type == 6 ) {
            g_sdk.set_color( material, "_Color", 
                color_t( options::visuals::chams_color.r * 255.f, options::visuals::chams_color.g * 255.f, options::visuals::chams_color.b * 255.f ) );
        }
        if( options::visuals::chams_type == 1 || options::visuals::chams_type == 3 ) {
            g_sdk.set_color( material, "_InvisCol", 
                options::visuals::chams_color );

            g_sdk.set_color( material, "_VisCol", 
                options::visuals::chams_visible );
        }
        if( options::visuals::chams_type == 0
            || options::visuals::chams_type == 4 ) {
            g_sdk.set_color( material, "_ColorBehind", 
                options::visuals::chams_color );

            g_sdk.set_color( material, "_ColorVisible", 
                options::visuals::chams_visible );
        }
    }

    //uintptr_t skin_set = *reinterpret_cast< uintptr_t* >( ( uintptr_t )model + 0x140 );
    //if( !skin_set ) {
    //    skin_set = *reinterpret_cast< uintptr_t* >( ( uintptr_t )model + 0x148 );
    //    return;
    //}
            
    //uintptr_t skins = *reinterpret_cast< uintptr_t* >( skin_set + 0x18 );
    //if( !skins )
    //    return;

    //static uintptr_t sky = il2mgr::init_class( "TOD_Sky" );
    //if( !sky )
    //    return;

    //uintptr_t components = *reinterpret_cast< uintptr_t* >( sky + 0xA8 );
    //if( !components )
    //    return;

    //uintptr_t scattering = *reinterpret_cast< uintptr_t* >( components + 0x154 );
    //if( !scattering )
    //    return;

    //int size = *reinterpret_cast< int* >( skins + 0x18 );

    //for ( int idx = 0; idx < size; idx++ )
    //{
    //    uintptr_t skin_set = *reinterpret_cast< uintptr_t* >( skins + 0x20 + ( idx * sizeof( uint64_t ) ) );
    //    if( !skin_set )
    //        continue;

    //    *reinterpret_cast< uintptr_t* >( skin_set + 0x68 ) = scattering; // SkinSet HeadMaterial
    //    *reinterpret_cast< uintptr_t* >( skin_set + 0x70 ) = scattering; // SkinSet BodyMaterial
    //    *reinterpret_cast< uintptr_t* >( skin_set + 0x78 ) = scattering; // SkinSet EyeMaterial
    //}
}

void c_esp::draw_health( core::base_player* player )
{
    float health = min( 100.f, static_cast< float >( player->get_health( ) ) );

    float box_height = bbox.bottom - bbox.top;

    // calculate hp bar color.
    const float calculate_col = ( std::clamp< float >( health, 25, 75 ) - 25.f ) / 50.f;

    color_t color = color_t( 120.f + ( 135.f * ( 1.f - calculate_col ) ), 50.f + ( 175.f * calculate_col ), 80 );
    if( options::visuals::modify_health_color )
        color = custom_health_color/*.multiply( color_t( 255, 15, 15 ), ( health / 100.f ) )*/;

    // get hp bar height.
	int fill = static_cast< int >( std::round( health * box_height / 100.f ) );

    int thickness = options::visuals::health_thickness;

    g_render.draw_filled_rect( vec4_t( bbox.left - ( 5 + thickness ), bbox.top - 1, thickness + 2, box_height + 3 ), color_t( 0, 0, 0, 150 ) );
	g_render.draw_filled_rect( vec4_t( bbox.left - ( 4 + thickness ), bbox.top + box_height - fill, thickness, fill + 1 ), color );
}

void c_esp::draw_hotbar( core::base_player* target )
{
    if( !target
        || target->get_life_state( ) )
        return;

    // check if we have menu open.
	if( g_framework.in_alpha ) {
		vec3_t cursor = g_cheat.mouse_pos;

		if( g_sdk.get_key( key_code::Mouse0 ) 
			&& g_framework.is_hovering( hotbar_position, vec2_t( info_bar_size.x, 25 ) ) )
		{
			cursor.y = g_cheat.screen_size.y - cursor.y;

			hotbar_position.x = cursor.x - info_bar_size.x / 2.f;
			hotbar_position.y = cursor.y - 10.f;
		}
	}

    float info_y = 0;

    std::string name = std::string( );

    core::player_model* model = target->get_model( );
    if( !model )
        return;

    std::vector< core::item* > belt = target->get_hotbar_items( );

    if( belt.empty( ) )
        return;

    name = model->is_npc( ) ? xs( "npc" ) : g_sdk.ws2s( target->get_username( ) ).substr( 0, 14 );

    std::string text = name + xs( "'s hotbar" );

    g_render.draw_filled_rect( hotbar_position, info_bar_size, g_framework.outline_color );
    g_render.outline_box( hotbar_position, info_bar_size, options::accent_color.alpha( 255, true ) );

    g_render.draw_text( vec4_t( hotbar_position.x + 11, hotbar_position.y, 150, 30 ), text, color_t( 255, 255, 255 ), true, 11, font_flags );

    color_t color = color_t( 220, 220, 220 );

    core::item* held_item = target->get_held_item( );

    for( size_t i = 0; i < belt.size( ); i++ )
    {
        core::item* item = belt.at( i );
        if( !item )
            continue;

        int item_amount = item->get_amount( );
	    if( item_amount > 1000 )
            item_amount = 1000;

        std::string weapon_name = g_sdk.ws2s( item->get_weapon_name( ) );
        if( weapon_name.empty( ) )
            continue;

        if( held_item 
            && item == held_item )
            color = color_t( 255, 255, 255 );

        std::string text = weapon_name;
        if( item_amount > 1 )
            text += xs( " x" ) + std::to_string( item_amount );

        std::transform( text.begin( ), text.end( ), text.begin( ), ::tolower );

        g_render.draw_text( vec4_t( hotbar_position.x + 11, ( hotbar_position.y + 25 ) + info_y, 150, 40 ), text, color, true, 11, font_flags );
        info_y += 13;
    }

    info_y = 0; // whaat...
}

void c_esp::draw_clothes( core::base_player* target )
{
    if( !target
        || target->get_life_state( ) )
        return;

    float info_y = 0;

    // check if we have menu open.
	if( g_framework.in_alpha ) {
		vec3_t cursor = g_cheat.mouse_pos;

		if( g_sdk.get_key( key_code::Mouse0 ) 
			&& g_framework.is_hovering( clothes_position, vec2_t( info_bar_size.x, 25 ) ) )
		{
			cursor.y = g_cheat.screen_size.y - cursor.y;

			clothes_position.x = cursor.x - info_bar_size.x / 2.f;
			clothes_position.y = cursor.y - 10.f;
		}
	}

    std::string name = std::string( );

    core::player_model* model = target->get_model( );
    if( !model )
        return;

    std::vector< core::item* > wear = target->get_wear_items( );
    if( wear.empty( ) )
        return;

    name = model->is_npc( ) ? xs( "npc" ) : g_sdk.ws2s( target->get_username( ) ).substr( 0, 14 );

    std::string text = name + xs( "'s clothes" );

    g_render.draw_filled_rect( clothes_position, info_bar_size, g_framework.outline_color );
    g_render.outline_box( clothes_position, info_bar_size, options::accent_color.alpha( 255, true ) );

    g_render.draw_text( vec4_t( clothes_position.x + 11, clothes_position.y, 150, 30 ), text, color_t( 255, 255, 255 ), true, 11, font_flags );

    color_t color = color_t( 255, 255, 255 );

    for( size_t i = 0; i < wear.size( ); i++ )
    {
        core::item* item = wear.at( i );
        if( !item )
            continue;

        int item_amount = item->get_amount( );
	    if( item_amount > 1000 )
            item_amount = 1000;

        std::string item_name = g_sdk.ws2s( item->get_weapon_name( ) );
        if( item_name.empty( ) )
            continue;

        std::string text = item_name;
        if( item_amount > 1 )
            text += xs( " x" ) + std::to_string( item_amount );

        std::transform( text.begin( ), text.end( ), text.begin( ), ::tolower );

        g_render.draw_text( vec4_t( clothes_position.x + 11, ( clothes_position.y + 25 ) + info_y, 150, 40 ), text, color, true, 11, font_flags );
        info_y += 13;
    }

    info_y = 0; // whaat...
}

void c_esp::draw_box( core::base_player* player ) {
    float box_width = bbox.right - bbox.left;
    float box_height = bbox.bottom - bbox.top;
                         
    color_t dropshadow_color = color_t( 0, 0, 0, 150 );

    float box_left_x = bbox.left - 1;
    float box_right_x = bbox.right - 1;

    auto draw_corner_box = [ & ] {
        /* dropshadow */

        // horizontal line ----

        //// left
        //g_render.horizontal_line( vec2_t( box_left_x - 1.f, bbox.top - 1.f ), box_width / 4 + 1, dropshadow_color );

        //// right
        //g_render.horizontal_line( vec2_t( box_right_x + 1.f, bbox.top - 1.f ), -( box_width / 4 + 1 ), dropshadow_color );

        //// vertical line |

        //// left
        //g_render.vertical_line( vec2_t( box_left_x - 1.f, bbox.top ), box_height / 4, dropshadow_color );

        //// right
        //g_render.vertical_line( vec2_t( box_right_x + 1.f, bbox.top - 1.f ), box_height / 4 + 1, dropshadow_color );

        ///* bottom */

        //// horizontal line ----

        //// left
        //g_render.horizontal_line( vec2_t( box_left_x - 1.f, bbox.bottom + 1.f ), box_width / 4 + 1, dropshadow_color );

        //// right
        //g_render.horizontal_line( vec2_t( box_right_x + 2.f, bbox.bottom + 1.f ), -( box_width / 4 + 2 ), dropshadow_color );

        //// vertical line |

        //// left
        //g_render.vertical_line( vec2_t( box_left_x - 1.f, bbox.bottom + 1.f ), -( box_height / 4 + 1 ), dropshadow_color );

        //// right
        //g_render.vertical_line( vec2_t( box_right_x + 1.f, bbox.bottom + 1.f ), -( box_height / 4 + 1 ), dropshadow_color );

        // main part

        // horizontal line ----
        // left
        g_render.horizontal_line( vec2_t( box_left_x, bbox.top ), box_width / 4, box_color );

        // right
        g_render.horizontal_line( vec2_t( box_right_x, bbox.top ), -( box_width / 4 ), box_color );

        // vertical line |
        // left
        g_render.vertical_line( vec2_t( box_left_x, bbox.top ), box_height / 4, box_color );

        // right
        g_render.vertical_line( vec2_t( box_right_x, bbox.top ), box_height / 4, box_color );

        // lower part

        /* bottom */

        // horizontal line ----
        // left
        g_render.horizontal_line( vec2_t( box_left_x, bbox.bottom ), box_width / 4, box_color );

        // right
        g_render.horizontal_line( vec2_t( box_right_x, bbox.bottom ), -( box_width / 4 ), box_color );

        // vertical line |
        // left
        g_render.vertical_line( vec2_t( box_left_x, bbox.bottom ), -( box_height / 4 ), box_color );

        // right
        g_render.vertical_line( vec2_t( box_right_x, bbox.bottom + 1.f ), -( box_height / 4 + 1 ), box_color );
    };

    if( options::visuals::box_type == 1 ) {
        g_render.outline_box( 
            vec2_t( bbox.left - 2, bbox.top - 1 ),
            vec2_t( box_width + 2, box_height + 2 ),
            color_t( 0, 0, 0, 150 ) );

        g_render.outline_box( 
            vec2_t( bbox.left - 1, bbox.top ),
            vec2_t( box_width, box_height ),
            box_color );
    }
    else if( options::visuals::box_type == 2 ) {
        draw_corner_box( );
    }
    else {
        draw_3d_box( player->get_bone_position( pelvis ), player->get_bone_position( head ), 2.f, options::visuals::box_color );
    }
}

void c_esp::draw_snap_lines( core::base_player* player ) {
    vec3_t bone_pos = player->get_bone_position( g_aimbot.aimbot_bone );
    vec2_t pos = g_sdk.world_to_screen( bone_pos );
    if( pos.is_zero( ) )
        return;

    core::player_model* model = player->get_model( );
    if( !model )
        return;

    if( player == g_aimbot.target 
        && options::aimbot::draw_target ) {
        g_render.draw_line( vec2_t( g_cheat.screen_size.x / 2, g_cheat.screen_size.y / 2 ), pos, options::aimbot::target_line_color );
    }
    else if( options::visuals::show_lines ) {
        g_render.draw_line( vec2_t( g_cheat.screen_size.x / 2, g_cheat.screen_size.y ), vec2_t( bbox.left + ( ( bbox.right - bbox.left ) / 2 ), bbox.bottom ), options::visuals::snap_lines_color );
    }
}

void c_esp::draw_view_direction( core::base_player* player )
{
    if( !options::visuals::show_view_direction )
        return;

    core::player_model* model = player->get_model( );
    if( !model )
        return;

    core::base_player* local = g_cheat.local;
    if( !local )
        return;

    core::player_eyes* eyes = player->get_eyes( );
    if( !eyes )
        return;

    vec3_t head_pos = player->get_bone_position( head );
    vec2_t head = g_sdk.world_to_screen( head_pos );

    vec2_t forward = g_sdk.world_to_screen( head_pos + ( eyes->get_bodyforward( ) * 2.f ) );

    if( head.is_zero( )
        || forward.is_zero( ) )
        return;

    g_render.draw_line( vec2_t( head.x, head.y ), vec2_t( forward.x, forward.y ), snap_lines_color );
}

void c_esp::draw_out_of_fov_arrows( core::base_player* player )
{
    core::base_player* local = g_cheat.local;
    if( !local )
        return;

    core::player_model* model = player->get_model( );
    if( !model )
        return;

    core::player_eyes* eyes = local->get_eyes( );
    if( !eyes )
        return;

    vec2_t center = g_cheat.screen_center;

    vec3_t local_pos = g_cheat.local_pos;
    vec3_t player_pos = model->get_position( );
    if( local_pos.is_zero( ) 
        || player_pos.is_zero( ) )
        return;

    vec3_t euler_angles = g_math.to_euler_angles( eyes->get_rotation( ) );

    const vec2_t position = vec2_t( local_pos.x - player_pos.x, local_pos.z - player_pos.z ).normalize( );

    float angle = atan2( position.x, position.y ) * 57.29578f - 180.f - euler_angles.y;

    vec2_t pos_0 = g_math.cos_tan_horizontal( angle, 10.f, center.x, center.y, 140 );
    vec2_t pos_1 = g_math.cos_tan_horizontal( angle + 2.f, 10.f, center.x, center.y, 130 );
    vec2_t pos_2 = g_math.cos_tan_horizontal( angle - 2.f, 10.f, center.x, center.y, 130 );

    g_render.gl_triangle( vec2_t( pos_0.x + 1, pos_0.y + 1 ), vec2_t( pos_1.x + 1, pos_1.y + 1 ), vec2_t( pos_2.x + 1, pos_2.y + 1 ), color_t( 0, 0, 0, 150 ) );
    g_render.gl_triangle( vec2_t( pos_0.x, pos_0.y ), vec2_t( pos_1.x, pos_1.y ), vec2_t( pos_2.x, pos_2.y ), oof_color );
}

void c_esp::draw_knocked_flag( core::base_player* player ) {
    if( !player->is_knocked( ) )
        return;

    g_render.draw_text( vec4_t( bbox.center, bbox.top - 25.f - ( esp_spacing[ 3 ] + esp_spacing[ 4 ] ), bbox.half, 30 ),
        xs( "^knocked^" ), knocked_color,
        true, 11, font_flags );
}

void c_esp::draw_ducking_flag( core::base_player* player ) {
    std::string name = std::string( );

    core::model_state* model_state = player->get_modelstate( );
    if( !model_state ) {
        esp_spacing[ 4 ] = 0;
        return;
    }

    if( !model_state->get_ducked( ) 
        || player->is_sleeping( )
        || player->is_knocked( ) ) {
        esp_spacing[ 4 ] = 0;
        return;
    }

    g_render.draw_text( vec4_t( bbox.center, bbox.top - 25.f - esp_spacing[ 3 ], bbox.half, 30 ), 
        xs( "*ducking*" ), ducking_color,
        true, 11, font_flags );

    if( esp_spacing[ 4 ] < 12 )
        esp_spacing[ 4 ] = 12;
}

void c_esp::draw_name( core::base_player* player, entity_type type ) {
    std::string name = std::string( );

    core::player_model* model = player->get_model( );
    if( !model )
        return;

    if( type == scientist )
        name  = xs( "scientist" );
    else if( type == tunnel_dweller )
        name  = xs( "tunnel dweller" );
    else if( model->is_npc( ) )
        name = xs( "npc" );
    else
        name = g_sdk.ws2s( player->get_username( ) );

    std::string new_name = std::string( );

    new_name = name;

    /* added to friend list. */
	for( auto& targets : m_friends )
	{
        if( player == targets )
            new_name = xs( "[f]" ) + name;
    }

    new_name.substr( 0, 18 ); // limit to 18 chars.

    g_render.draw_text( vec4_t( bbox.center, bbox.top - 25.f, bbox.half, 30 ), 
        new_name, name_color,
        true, 11, font_flags );

    if( esp_spacing[ 3 ] < 12 )
        esp_spacing[ 3 ] = 12;
}

void c_esp::draw_health_text( core::base_player* player ) {
    std::string hp_str = std::to_string( static_cast< int >( player->get_health( ) ) ) + "hp";

    g_render.draw_text( vec4_t( bbox.center, bbox.bottom, bbox.half, 30 ), 
        hp_str, health_text_color,
        true, 11, font_flags );
}   

void c_esp::draw_distance( core::base_player* player ) {
	std::string dist_str = std::to_string( static_cast< int >( g_cheat.local_pos.distance( player->get_model( )->get_position( ) ) ) ) + "m";

    g_render.draw_text( vec4_t( bbox.center, bbox.bottom + ( esp_spacing[ 0 ] + esp_spacing[ 1 ] ), bbox.half, 30 ), 
        dist_str, distance_color,
        true, 11, font_flags );

    if( esp_spacing[ 2 ] < 12 )
        esp_spacing[ 2 ] = 12;
}    

void c_esp::draw_bones( core::base_player* player )
{
    vec3_t head_pos = player->get_bone_position( head );
	vec3_t spine4_pos = player->get_bone_position( spine4 );
	vec3_t l_clavicle_pos = player->get_bone_position( l_clavicle );
	vec3_t l_upperarm_pos = player->get_bone_position( l_upperarm );
	vec3_t l_forearm_pos = player->get_bone_position( l_forearm );
	vec3_t l_hand_pos = player->get_bone_position( l_hand );
	vec3_t r_clavicle_pos = player->get_bone_position( r_clavicle );
	vec3_t r_upperarm_pos = player->get_bone_position( r_upperarm );
	vec3_t r_forearm_pos = player->get_bone_position( r_forearm );
	vec3_t r_hand_pos = player->get_bone_position( r_hand );
	vec3_t pelvis_pos = player->get_bone_position( pelvis );
	vec3_t l_hip_pos = player->get_bone_position( l_hip );
	vec3_t l_knee_pos = player->get_bone_position( l_knee );
	vec3_t l_ankle_scale_pos = player->get_bone_position( l_ankle_scale );
	vec3_t l_foot_pos = player->get_bone_position( l_foot );
	vec3_t r_hip_pos = player->get_bone_position( r_hip );
	vec3_t r_knee_pos = player->get_bone_position( r_knee );
	vec3_t r_ankle_scale_pos = player->get_bone_position( r_ankle_scale );
	vec3_t r_foot_pos = player->get_bone_position( r_foot );

	vec2_t head = g_sdk.world_to_screen( head_pos );
    vec2_t spine = g_sdk.world_to_screen( spine4_pos ); 
    vec2_t l_clavicle = g_sdk.world_to_screen( l_clavicle_pos );
    vec2_t l_upperarm = g_sdk.world_to_screen( l_upperarm_pos );
    vec2_t l_forearm = g_sdk.world_to_screen( l_forearm_pos );
    vec2_t l_hand = g_sdk.world_to_screen( l_hand_pos );
    vec2_t r_clavicle = g_sdk.world_to_screen( r_clavicle_pos );
    vec2_t r_upperarm = g_sdk.world_to_screen( r_upperarm_pos );
    vec2_t r_forearm = g_sdk.world_to_screen( r_forearm_pos ); 
    vec2_t r_hand = g_sdk.world_to_screen( r_hand_pos ); 
    vec2_t pelvis = g_sdk.world_to_screen( pelvis_pos );
    vec2_t l_hip = g_sdk.world_to_screen( l_hip_pos );
    vec2_t l_knee = g_sdk.world_to_screen( l_knee_pos );
    vec2_t l_ankle_scale = g_sdk.world_to_screen( l_ankle_scale_pos );
    vec2_t l_foot = g_sdk.world_to_screen( l_foot_pos ); 
    vec2_t r_hip = g_sdk.world_to_screen( r_hip_pos );
    vec2_t r_knee = g_sdk.world_to_screen( r_knee_pos );
    vec2_t r_ankle_scale = g_sdk.world_to_screen( r_ankle_scale_pos ); 
    vec2_t r_foot = g_sdk.world_to_screen( r_foot_pos );

	if( head.is_zero( )
        || spine.is_zero( )
        || l_clavicle.is_zero( )
        || l_upperarm.is_zero( )
        || l_forearm.is_zero( )
        || l_hand.is_zero( )
        || r_clavicle.is_zero( )
        || r_upperarm.is_zero( )
        || r_forearm.is_zero( )
        || r_hand.is_zero( )
        || pelvis.is_zero( )
		|| l_hip.is_zero( )
        || l_knee.is_zero( )
        || l_ankle_scale.is_zero( )
        || l_foot.is_zero( )
        || r_hip.is_zero( )
        || r_knee.is_zero( )
        || r_ankle_scale.is_zero( )
        || r_foot.is_zero( ) )
        return;

    core::player_model* model = player->get_model( );
    if( !model )
        return;

    vec3_t vis = model->get_position( );

    g_render.draw_line( vec2_t( head.x, head.y ), vec2_t( spine.x, spine.y ), skeleton_color );
    g_render.draw_line( vec2_t( spine.x, spine.y ), vec2_t( l_upperarm.x, l_upperarm.y ), skeleton_color );
    g_render.draw_line( vec2_t( l_upperarm.x, l_upperarm.y ), vec2_t( l_forearm.x, l_forearm.y ), skeleton_color );
    g_render.draw_line( vec2_t( l_forearm.x, l_forearm.y ), vec2_t( l_hand.x, l_hand.y ), skeleton_color );
    g_render.draw_line( vec2_t( spine.x, spine.y ), vec2_t( r_upperarm.x, r_upperarm.y ), skeleton_color );
    g_render.draw_line( vec2_t( r_upperarm.x, r_upperarm.y ), vec2_t( r_forearm.x, r_forearm.y ), skeleton_color );
    g_render.draw_line( vec2_t( r_forearm.x, r_forearm.y ), vec2_t( r_hand.x, r_hand.y ), skeleton_color );
    g_render.draw_line( vec2_t( spine.x, spine.y ), vec2_t( pelvis.x, pelvis.y ), skeleton_color );
    g_render.draw_line( vec2_t( pelvis.x, pelvis.y ), vec2_t( l_hip.x, l_hip.y ), skeleton_color );
    g_render.draw_line( vec2_t( l_hip.x, l_hip.y ), vec2_t( l_knee.x, l_knee.y ), skeleton_color );
    g_render.draw_line( vec2_t( l_knee.x, l_knee.y ), vec2_t( l_foot.x, l_foot.y ), skeleton_color );
    g_render.draw_line( vec2_t( pelvis.x, pelvis.y ), vec2_t( r_hip.x, r_hip.y ), skeleton_color );
    g_render.draw_line( vec2_t( r_hip.x, r_hip.y ), vec2_t( r_knee.x, r_knee.y ), skeleton_color );
    g_render.draw_line( vec2_t( r_knee.x, r_knee.y ), vec2_t( r_foot.x, r_foot.y ), skeleton_color );
}

void c_esp::draw_weapon( core::base_player* player ) {
    if( !player->get_held_item( ) ) {
        esp_spacing[ 0 ] = 0;
        return;
    }

    std::string weapon_name = g_sdk.ws2s( player->get_held_item( )->get_weapon_name( ) );

    std::transform( weapon_name.begin( ), weapon_name.end( ), weapon_name.begin( ), ::tolower );

    if( options::visuals::show_weapon ) {
        g_render.draw_text( vec4_t( bbox.center, bbox.bottom + esp_spacing[ 1 ], bbox.half, 30 ),
            weapon_name, weapon_color,
            true, 11, font_flags );

        if( esp_spacing[ 0 ] < 12 )
            esp_spacing[ 0 ] = 12;
    }
    else if( !options::visuals::show_weapon
        || weapon_name.empty( ) )
        esp_spacing[ 0 ] = 0;
}

void c_esp::reset_fly_hack( ) {
    distance_vertical = distance_horizontal =
    pause_time = current_horizontal_fly = 0.f;
    current_vertical_fly = 0.f;
}

void c_esp::apply_fly_violation( ) {
    core::base_player* local = g_cheat.local;
    if( !local
        || local 
        && ( local->get_life_state( ) || local->get_on_ladder( ) ) )
        return reset_fly_hack( );

    core::player_ticks* last_sent_tick = local->get_lastSentTick( );
    if( !last_sent_tick )
        return reset_fly_hack( );

    float radius = local->get_radius( );
    if( !radius )
        return reset_fly_hack( );

    float height = local->get_height( false );
    if( !height )
        return reset_fly_hack( );

    float jump_height = local->get_jumpheight( );
    if( !jump_height )
        return reset_fly_hack( );

    vec3_t last_position = last_sent_tick->get_position( );
    if( last_position.is_zero( ) )
        return reset_fly_hack( );

    vec3_t position = g_cheat.local_pos;
    if( position.is_zero( ) )
        return reset_fly_hack( );

    bool has_silent_walk = options::aimbot::exploits::movement::silent_walk && g_sdk.get_key( key_code::LeftShift );

    vec3_t new_position = ( last_position + position ) * 0.5f;
    vec3_t start = new_position + vec3_t( 0.f, radius - 2.f, 0.f );
    vec3_t end = new_position + vec3_t( 0.f, height - radius, 0.f );

    if( g_game.water_level_test( new_position - vec3_t( 0.f, 2.f, 0.f ), true, false, local ) )
        return reset_fly_hack( );

    float lower_radius = radius - 0.05f;

    bool in_air = !g_sdk.physics_checkcapsule( start, end, lower_radius, 1503731969, QueryTriggerInteraction::Ignore );
    if( local->get_modelstate( )->has_flag( on_ladder ) 
        && !has_silent_walk ) {
        distance_horizontal = 0.f;
        distance_vertical = 0.f;
        in_air = false;
    }

    if( in_air ) {
        vec3_t position_difference = position - last_position;
        float position_height = abs( position_difference.y );
        float position_length = position_difference.unity_length( );
        if( position_difference.y >= 0.f )
            distance_vertical += position_difference.y;

        if( position_height < position_length )
            distance_horizontal += position_length;
    }
    else {
        distance_horizontal = 0.f;
        distance_vertical = 0.f;
    }

    pause_time = max( 0.f, pause_time - g_sdk.get_time( ), 0.0f );

    double time_since_violation = max( ( pause_time > 0.0 ) ? 10 : 1.5, 0.0, 0.0 );

	float new_jump_time = jump_height + time_since_violation;
	max_vertical_fly = new_jump_time;
    current_vertical_fly = distance_vertical;

	float new_speed_time = 5.f + time_since_violation;
    max_horizontal_fly = new_speed_time;
	current_horizontal_fly = distance_horizontal;
}

void c_esp::show_reload_bar( ) {
    if( !options::visuals::show_reload_bar ) {
        indicators_spacing[ 0 ] = 0.f;
        return;
    }

    core::base_player* local_player = g_cheat.local;
    if( !local_player ) {
        indicators_spacing[ 0 ] = 0.f;
        return;
    }

    core::item* held_item = local_player->get_held_item( );
    if( !held_item ) {
        indicators_spacing[ 0 ] = 0.f;
        return;
    }   

    float max_size = 130;
    float red{ }, green{ }, x{ };

    static float alpha{ };

    if( held_item->has_reload_cooldown( ) ) {
        float reload_dur = held_item->get_next_reload_time( ) - g_cheat.global_time;
        float reload_dur_total = held_item->calculate_cooldown_time( held_item->get_next_reload_time( ), held_item->get_reload_time( ) ) - g_cheat.global_time;

        float percentage = ( ( ( reload_dur / reload_dur_total ) * 100.0f ) + 1.f ) / 100;

        float num = percentage;

		if( num ) {
            num = std::clamp( num, 0.f, 1.f );
		}

        x = ( num * max_size );

        x = std::clamp( x, 1.f, max_size );

        if( alpha < 1.f )
            alpha = std::lerp( alpha, 1.f, 0.15f );
    }
    else {
        alpha = std::lerp( alpha, 0.f, 0.15f );
    }

    if( alpha > 0.15f ) {
        if( indicators_spacing[ 0 ] < 12.f )
            indicators_spacing[ 0 ] = std::lerp( indicators_spacing[ 0 ], 10.f, 0.25f );

        color_t color = options::visuals::reload_bar_color;
        color.a *= alpha;

        g_render.draw_filled_rect( vec4_t( g_cheat.screen_center.x - ( max_size / 2 ), g_cheat.screen_center.y + ( 20.f ), max_size, 4.f ), color_t( 0.f, 0.f, 0.f, 255.f * alpha ) );
        g_render.draw_filled_rect( vec4_t( g_cheat.screen_center.x - ( max_size / 2 ) + 1, g_cheat.screen_center.y + ( 21.f ), x - 2, 2.f ), color );
    }
    else {
        indicators_spacing[ 0 ] = std::lerp( indicators_spacing[ 0 ], 0.f, 0.25f );
    }
}

void c_esp::show_desync_bar( ) {
	if( !options::visuals::show_desync_bar ) {
        indicators_spacing[ 1 ] = std::lerp( indicators_spacing[ 1 ], 0.f, 0.25f );
        return;
    }

    static float alpha = 0.f;
    float max_size = 130;

	float desync_time = ( g_sdk.realtimeSinceStartup( ) - g_cheat.local->lastSentTickTime( ) ) - 0.03125 * 3;
    float desync_amount = ( ( ( desync_time / 0.85f ) * 100.0f ) + 1.f ) / 100;

	float num = desync_amount;

	if( desync_amount < 0.1f )
        num = 0;

	if( num ) {
        num = std::clamp( num, 0.f, 1.f );

        if( alpha < 1.f )
            alpha = std::lerp( alpha, 1.f, 0.15f );
	}
    else {
        alpha = std::lerp( alpha, 0.f, 0.15f );
    }

    float x = ( desync_time * max_size );

    x = std::clamp( x, 1.f, max_size );

    if( alpha > 0.15f ) {
        if( indicators_spacing[ 1 ] < 10.f )
            indicators_spacing[ 1 ] = std::lerp( indicators_spacing[ 1 ], 10.f, 0.25f );

        color_t color = options::visuals::desync_bar_color;
        color.a *= alpha;

        g_render.draw_filled_rect( vec4_t( g_cheat.screen_center.x - ( max_size / 2 ), g_cheat.screen_center.y + ( 20.f + indicators_spacing[ 0 ] ), max_size, 4.f ),
            color_t( 0.f, 0.f, 0.f, 255.f * alpha ) );

        g_render.draw_filled_rect( vec4_t( g_cheat.screen_center.x - ( max_size / 2 ) + 1, g_cheat.screen_center.y + ( 21.f + indicators_spacing[ 0 ] ), x - 2, 2.f ),
            color );
    }
    else {
        indicators_spacing[ 1 ] = std::lerp( indicators_spacing[ 1 ], 0.f, 0.25f );
    }
}

void c_esp::fly_hack_bar( ) {
    static float alpha[ 2 ]{ 0.f };

    if( current_vertical_fly > 0.f
        && alpha[ 1 ] < 1.f )
        alpha[ 1 ] = std::lerp( alpha[ 1 ], 1.f, 0.15f );
    else if( alpha[ 1 ] > 0.f )
        alpha[ 1 ] = std::lerp( alpha[ 1 ], 0.f, 0.15f );

    if( current_horizontal_fly > 0.f
        && alpha[ 0 ] < 1.f )
        alpha[ 0 ] = std::lerp( alpha[ 0 ], 1.f, 0.15f );
    else if( alpha[ 0 ] > 0.f )
        alpha[ 0 ] = std::lerp( alpha[ 0 ], 0.f, 0.15f );

    if( options::visuals::indicators 
        && options::visuals::fly_hack_indicator ) {
	    float vert_percentage = ( current_vertical_fly / max_vertical_fly );
		const float red = vert_percentage * 255.f;
		const float green = 255.f - red;
        vert_percentage = std::clamp( vert_percentage, 0.f, 1.f );

        if( alpha[ 1 ] ) {
		    g_render.draw_filled_rect( vec4_t( g_cheat.screen_center.x - 200, g_cheat.screen_center.y - 426, 402, 6 ), 
                color_t( 0, 0, 0, 255.f * alpha[ 1 ] ) );

		    g_render.draw_filled_rect( vec4_t( g_cheat.screen_center.x - 199, g_cheat.screen_center.y - 425, 400 * vert_percentage, 4 ), 
                color_t( red, green, 0, 255.f * alpha[ 1 ] ) );
        }

		float hor_percentage = ( current_horizontal_fly / max_horizontal_fly );
		const float red_horizontal = hor_percentage * 255.f;
		const float green_horizontal = 255.f - red_horizontal;
        hor_percentage = std::clamp( hor_percentage, 0.f, 1.f );

        if( alpha[ 0 ] ) {
		    g_render.draw_filled_rect( vec4_t( g_cheat.screen_center.x - 200, g_cheat.screen_center.y - 446, 402, 6 ), 
                color_t( 0, 0, 0, 255.f * alpha[ 0 ] ) );

		    g_render.draw_filled_rect( vec4_t( g_cheat.screen_center.x - 199, g_cheat.screen_center.y - 445, 400 * hor_percentage, 4 ), 
                color_t( red_horizontal, green_horizontal, 0, 255.f * alpha[ 0 ] ) );
        }
    }
}

core::base_entity* c_esp::get_closest_object_of_class( std::string class_to_find, float max_dist )
{
	float best_distance = max_dist;
	core::base_entity* best_object = NULL;

	if( !g_cheat.client_entities )
		return NULL;

	uintptr_t entity_realm = *reinterpret_cast< uintptr_t* >( g_cheat.client_entities + 0x10 );
	if( !entity_realm )
		return NULL;

	uintptr_t buffer_list = *reinterpret_cast< uintptr_t* >( entity_realm + 0x28 );
	if( !buffer_list )
		return NULL;

	uintptr_t object_list = *reinterpret_cast< uintptr_t* >( buffer_list + 0x18 );
	if( !object_list )
		return NULL;

	int object_list_size = *reinterpret_cast< int* >( buffer_list + 0x10 );
	if( !object_list_size )
		return NULL;

	for( int i = 0; i < object_list_size; i++ )
	{
		core::base_entity* current_object = *reinterpret_cast< core::base_entity** >( object_list + ( 0x20 + ( i * sizeof( uint64_t ) ) ) );

		if( !current_object )
			continue;

		std::string class_name = current_object->get_class_name( );

		if( class_name == class_to_find )
		{
			uintptr_t base_mono_object = *reinterpret_cast< uintptr_t* >( ( uintptr_t )current_object + 0x10 );
			if( !base_mono_object )
				continue;

			uintptr_t object = *reinterpret_cast< uintptr_t* >( base_mono_object + 0x30 );
			if( !object )
				continue;

			uintptr_t object_class = *reinterpret_cast< uintptr_t* >( object + 0x30 );
			if( !object_class )
				continue;

			uintptr_t entity_visual = *reinterpret_cast< uintptr_t* >( object_class + sizeof( uint64_t ) );
			if( !entity_visual )
				continue;

			uintptr_t visual_state = *reinterpret_cast< uintptr_t* >( entity_visual + 0x38 );
			if( !visual_state )
				continue;

			vec3_t position = *reinterpret_cast< vec3_t* >( visual_state + 0x90 );

			float distance = g_cheat.local_pos.distance( position );

			if( distance < best_distance )
			{
				best_distance = distance;
				best_object = current_object;
			}
		}
	}

	return best_object;
}

void c_esp::do_melee_attack( vec3_t pos, core::base_entity* entity, bool is_player )
{
    core::base_player* local = g_cheat.local;
    if( !local )
        return;

    core::player_eyes* eyes = local->get_eyes( );
    if( !eyes )
        return;
        
    core::item* held_item = local->get_held_item( );
    if( !held_item 
        || !held_item->is_melee( ) )
        return;

	if( !entity ) 
		return;

	if( held_item->get_next_attack_time( ) >= g_sdk.get_fixedTime( )
        || held_item->get_deploy_delay( ) > held_item->get_time_since_deploy( ) )
		return;

	core::transform* trans = is_player ? reinterpret_cast< core::base_player* >( entity )->get_bone_transform( head ) : entity->get_transform( );
	if( !trans )
		return;

	vec3_t transform_pos = trans->inverse_tranform_point( pos );

	core::Ray ray = core::Ray( eyes->get_position( ), ( pos - eyes->get_position( ) ).normalized( ) );

	core::hit_test* hit = core::hit_test::New( );
	if( hit ) {
		hit->set_hit_entity( entity );
		hit->set_did_hit( true );
		hit->set_max_distance( melee_max_dist );
		hit->set_hit_transform( trans );
		hit->set_attack_ray( ray );
		hit->set_hit_normal( transform_pos );
		hit->set_hit_hitpoint( transform_pos );
		hit->set_damage_properties( held_item->get_damage_properties( ) );
        held_item->process_attack( hit );
        held_item->start_attack_cooldown( held_item->get_repeat_delay( ) );
	}
}
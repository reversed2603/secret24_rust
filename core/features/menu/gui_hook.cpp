#include "gui_hook.h"
#include "../../includes/hinclude.h"
#include "../visuals/esp.h"
#include "../../game/offsets.hpp"
#include "../options.h"
#include "../aimbot/aimbot.h"
#include "framework/gui_framework.h"
#include <filesystem>
#include <shlobj.h>
#include "menu_tabs.h"

void entity_loop( )
{
	std::vector< std::pair< core::base_player*, entity_type > > player_list;
	
	event_type event_type = g_sdk.get_event_type( g_sdk.get_current( ) );

	auto clear_list = [ & ]( bool get_client_entities = false ) -> void
	{
		if( get_client_entities )
			g_cheat.client_entities = il2mgr::value( xs( "BaseNetworkable" ), xs( "clientEntities" ), false );

		/* fix for re-joining servers xd */
		player_list.clear( );
		g_cheat.player_list.clear( );
		g_cheat.local_pos.clear( );
		g_cheat.cam_pos.clear( );
	};

	if( !g_cheat.client_entities )
		return clear_list( true );

	uintptr_t entity_realm = *reinterpret_cast< uintptr_t* >( g_cheat.client_entities + 0x10 );
	if( !entity_realm )
		return clear_list( true );

	uintptr_t buffer_list = *reinterpret_cast< uintptr_t* >( entity_realm + 0x28 );
	if( !buffer_list )
		return clear_list( );

	uintptr_t object_list = *reinterpret_cast< uintptr_t* >( buffer_list + 0x18 );
	if( !object_list )
		return clear_list( );

	int object_list_size = *reinterpret_cast< int* >( buffer_list + 0x10 );

	if( !g_cheat.local )
		clear_list( );

	for( int i = 0; i < object_list_size; i++ )
	{
		core::base_entity* current_object = *reinterpret_cast< core::base_entity** >( object_list + ( 0x20 + ( i * sizeof( uint64_t ) ) ) );
		if( !current_object )
			continue;

		uintptr_t base_object = *reinterpret_cast< uintptr_t* >( ( uintptr_t )current_object + 0x10 );
		if( !base_object )
			continue;

		uintptr_t object = *reinterpret_cast< uintptr_t* >( base_object + 0x30 );
		if( !object )
			continue;

		uintptr_t object_class = *reinterpret_cast< uintptr_t* >( object + 0x30 );
		if( !object_class )
			continue;

		uintptr_t entity = *reinterpret_cast< uintptr_t* >( object_class + 0x18 );
		if( !entity )
			continue;

		std::string class_name = current_object->get_class_name( );

		core::base_player* player = *reinterpret_cast< core::base_player** >( entity + 0x28 );
		if( player ) {
			if( i == 0 )
			{
				g_cheat.local = player;

				if( g_cheat.local->get_life_state( ) )
					continue;

				core::player_model* model = g_cheat.local->get_model( );
				if( model )
					g_cheat.local_pos = model->get_position( );

				continue;
			}

			const uint16_t tag = *reinterpret_cast< uint16_t* >( object + 0x54 );
			if( tag == 6 )
			{
				static entity_type type = entity_type::player;

				if( ( class_name.length ( ) > 9
					&& ( class_name[ 9 ] == 'N' )
					|| ( class_name[ 0 ] == 'S' && class_name[ 1 ] == 'c' ) ) 
					|| ( class_name[ 0 ] == 'H' && class_name[ 1 ] == 'T' ) 
					|| ( class_name[ 0 ] == 'N' && class_name[ 3 ] == 'S' )
					|| ( class_name[ 0 ] == 'V' && class_name[ 7 ] == 'V' ) ) // Scientist
					type = scientist;
				else if( ( class_name[ 0 ] == 'T' && class_name[ 6 ] == 'D' ) ) // TunnelDweller
					type = tunnel_dweller;
				else 
					type = entity_type::player;

				player_list.emplace_back( std::make_pair( player, type ) );
			}
		}

		core::base_entity* base_entity = *reinterpret_cast< core::base_entity** >( base_object + 0x28 );
		if( !base_entity )
			continue;

		core::transform* transform = base_entity->get_transform( );
		if( !transform )
			continue;

		vec3_t position = transform->get_position( );
		if( position.is_zero( ) )
			continue;

		float distance = g_cheat.local_pos.distance( position );

		uintptr_t object_name_ptr = *reinterpret_cast< uintptr_t* >( object + 0x60 );
		if( !object_name_ptr )
			continue;

		std::string obj_name = g_sdk.read_ascii( object_name_ptr, 128 );

		vec2_t screen_pos = g_sdk.world_to_screen( position );
		if( screen_pos.is_zero( ) )
			continue;

		vec4_t render_position = vec4_t( screen_pos.x, screen_pos.y, 150, 55 );

		core::base_combat_entity* combat_entity = reinterpret_cast< core::base_combat_entity* >( current_object );

		g_world.render( render_position, class_name, obj_name, distance, combat_entity, event_type, base_entity );
	}

	g_cheat.player_list = player_list;
}

namespace perf_ui {
	void ongui_hook( )
	{
		g_cheat.mouse_pos = g_sdk.get_mouse_pos( );
		g_cheat.screen_size = vec2_t( g_sdk.get_screen_width( ), g_sdk.get_screen_height( ) ); // k to the y to the s
		if( !g_cheat.screen_size.is_zero( ) )
			g_cheat.screen_center = g_cheat.screen_size / 2;

		uintptr_t current_event = g_sdk.get_current( );
		if( !current_event )
			return;

		event_type event_type = g_sdk.get_event_type( current_event );
		if( event_type != event_type::re_paint )
			return;

		g_cheat.draw_skin = g_sdk.get_draw_skin( );
		if( !g_cheat.draw_label )
			g_cheat.draw_label = *reinterpret_cast< uintptr_t* >( g_cheat.draw_skin + 0x38 );
		else {
			g_sdk.set_draw_font_size( g_cheat.draw_label, 12 );
			g_sdk.set_draw_alignment( g_cheat.draw_label, 0x0 );
			g_sdk.set_draw_color( color_t( 255, 255, 255, 255 ) );
		}

		if( !g_cheat.circuit_chams_bundle )
			g_cheat.circuit_chams_bundle = g_sdk.load_bundle_file( "C:\\secrethack24\\circuit_chams_bundle.vmt" );

		if( !g_cheat.chams_bundle )
			g_cheat.chams_bundle = g_sdk.load_bundle_file( "C:\\secrethack24\\chams_bundle.vmt" );

		if( !g_cheat.wireframe_chams_bundle )
			g_cheat.wireframe_chams_bundle = g_sdk.load_bundle_file( "C:\\secrethack24\\wire_chams.vmt" );

		if( !g_cheat.asset_bundle )
			g_cheat.asset_bundle = g_sdk.load_bundle_file( "C:\\secrethack24\\chams.vmt" );

		if( !g_cheat.font_bundle )
			g_cheat.font_bundle = g_sdk.load_bundle_file( "C:\\secrethack24\\font_bundle.bndl" );
		else {
			static uintptr_t object = il2mgr::type_object( "UnityEngine", "Font" );

			static uintptr_t font_name = g_sdk.load_asset( g_cheat.font_bundle, "ubuntu-medium.ttf", object );
			if( font_name )
				*reinterpret_cast< uintptr_t* >( g_cheat.draw_skin + 0x18 ) = font_name;
		}

		g_cheat.pulsation.rainbow( 5.f );
		g_cheat.rainbow = color_t( g_cheat.pulsation.r, 127 + g_cheat.pulsation.g * 0.25f, g_cheat.pulsation.g );

		if( options::rainbow_accent )
			options::accent_color = g_cheat.rainbow;

		// draw our menu.
		g_menu.draw_menu( );

		// set-up shader before draw.
		g_render.set_up_draw_shader( );

		std::string config_direction = std::filesystem::current_path( ).string( );

		static std::vector< std::string > cfg_files;

		cfg_files.clear( );
		for( const auto& entry : std::filesystem::directory_iterator( config_direction ) )
		{
			if( entry.is_regular_file( ) 
				&& entry.path( ).extension( ) == ".cfg" )
				cfg_files.push_back( entry.path( ).filename( ).string( ) );
		}

		if( options::cfg_index >= 0 ) {
			std::string file_name = cfg_files.at( options::cfg_index );

			if( options::load_cfg
				&& options::cfg_index < cfg_files.size( ) )
			{
				g_cfg.load_cfg( file_name );
			}

			if( options::save_cfg
				&& options::cfg_index < cfg_files.size( ) )
			{
				g_cfg.save_cfg( file_name );
			}
		}

		if( options::aimbot::exploits::misc::no_flash )
			g_game.set_flash_duration( 0.f );
		else
			g_game.set_flash_duration( 2.5f );

		entity_loop( );

		// esp font flags.
		{
			switch( options::font_flags )
			{
			case 1:
				g_esp.font_flags = font_flags_t::dropshadow;
				break;
			case 2:
				g_esp.font_flags = font_flags_t::outline;
				break;
			default:
				g_esp.font_flags = font_flags_t::none;
				break;
			}
		}

		auto render_water_mark =[ & ]( ) -> void // tf is that lambda:P
		{
			std::string total_text = xs( "secret-hack24: RUST" );

			g_render.outline_box( vec2_t( 2, 3 ), vec2_t( 110, 20 ), color_t( 48, 48, 48 ) );
			g_render.draw_filled_rect( vec4_t( 2, 3, 110, 20 ), color_t( 10, 10, 10 ) );
			g_render.draw_filled_rect( vec4_t( 2, 3, 2, 20 ), options::accent_color.alpha( 255.f, true ) );
			g_render.draw_text( vec4_t( 7, 4, 150, 20 ), total_text, color_t( 225, 225, 225 ), false, 11, g_esp.font_flags );
		};

		if( options::visuals::show_watermark )
			render_water_mark( );

		if( options::visuals::world::mie_changer )
			g_game.set_mie( options::visuals::world::mie_amount );
		if( options::visuals::world::rayleigh_changer )
			g_game.set_rayleigh( options::visuals::world::rayleigh_amount );
		if( options::visuals::world::modify_rain )
			g_game.set_rain( options::visuals::world::rain_amount );

		if( options::aimbot::draw_fov )
		{
			g_render.draw_circle( g_cheat.screen_center, options::aimbot::fov_amount, 
				options::aimbot::fov_circle_color );
		}

		if( options::aimbot::draw_crosshair ) {
			g_render.draw_line( vec2_t( g_cheat.screen_center.x - 7.f, g_cheat.screen_center.y ), 
				vec2_t( g_cheat.screen_center.x - 2.f, g_cheat.screen_center.y ), color_t( g_cheat.pulsation.r, g_cheat.pulsation.g, 255 ) ); // left middle

			g_render.draw_line( vec2_t( g_cheat.screen_center.x + 6.f, g_cheat.screen_center.y ),
				vec2_t( g_cheat.screen_center.x + 1.f, g_cheat.screen_center.y ), color_t( g_cheat.pulsation.r, ( 0.5f + g_cheat.pulsation.g * 0.25f ), g_cheat.pulsation.g ) ); // right middle

			g_render.draw_line( vec2_t( g_cheat.screen_center.x, g_cheat.screen_center.y - 7.f ),
				vec2_t( g_cheat.screen_center.x, g_cheat.screen_center.y - 2.f ), color_t( g_cheat.pulsation.b, 255, g_cheat.pulsation.b ) ); // middle down

			g_render.draw_line( vec2_t( g_cheat.screen_center.x, g_cheat.screen_center.y + 6.f ),
				vec2_t( g_cheat.screen_center.x, g_cheat.screen_center.y + 1.f ), color_t( g_cheat.pulsation.r, g_cheat.pulsation.g, g_cheat.pulsation.b ) ); // middle up
		}

		g_esp.change_sky_ambient_color( );
		core::base_player* local_player = g_cheat.local;

		if( local_player )
		{			
			// reset this.
			g_esp.not_in_fly_action = true;

			bool manipulation_activated = g_sdk.get_key( options::aimbot::manipulation_key ) && options::aimbot::manipulation;

			if( manipulation_activated ) {
				local_player->set_clientTickInterval( 1.f );

				g_esp.find_manipulate_angle( );
				if( !g_esp.manipulation_angle.is_zero( ) ) {
					core::player_eyes* eyes = local_player->get_eyes( );
					if( eyes ) {
						if( g_sdk.get_key( key_code::F )
							&& local_player->get_clientTickInterval( ) > 0.75f )
							eyes->set_view_offset( g_esp.manipulation_angle );
					}
				}
			}
			else {
				g_esp.manipulation_angle.clear( );
			}

			g_esp.render_saved_positions( );

			if( options::aimbot::exploits::movement::modify_clothing_speed )
				local_player->set_clothing_speed_reduce( -options::aimbot::exploits::movement::clothing_speed );

			if( options::aimbot::exploits::combat::unlock_aim_on_jugger )
				local_player->set_clothing_blocks_aiming( false );

			// spacing handle lol.
			{
				if( options::visuals::show_health_text 
					&& g_esp.esp_spacing[ 1 ] < 13 )
					g_esp.esp_spacing[ 1 ] += 13;
				else if( !options::visuals::show_health_text )
					g_esp.esp_spacing[ 1 ] = 0;
			}

			if( options::visuals::draw_radar )
			{
				float width = 200, height = 200;

				// check if we have menu open.
				if( g_framework.in_alpha ) {
					vec3_t cursor = g_cheat.mouse_pos;

					if( g_sdk.get_key( key_code::Mouse0 ) 
						&& g_framework.is_hovering( g_esp.radar_position, vec2_t( width, 25 ) ) )
					{
						cursor.y = g_cheat.screen_size.y - cursor.y;

						g_esp.radar_position.x = cursor.x - width / 2.f;
						g_esp.radar_position.y = cursor.y - 10.f;
					}
				}

				g_render.draw_filled_rect( vec4_t( g_esp.radar_position.x, g_esp.radar_position.y, width, height ), color_t( 0, 0, 0, 255 ) );
				g_render.outline_box( vec2_t( g_esp.radar_position.x, g_esp.radar_position.y ), vec2_t( width, height ), color_t( 48, 48, 48, 255 ) );
			}

			if( options::visuals::rgb_chams )
				options::visuals::chams_color = options::visuals::chams_visible = g_cheat.rainbow;

			for( int i = 0; i < g_cheat.player_list.size( ); i++ )
			{
				std::pair< core::base_player*, entity_type > player = g_cheat.player_list.at( i ); // wow that's so ugly
				if( !player.first )
					continue;

				g_esp.context_instance( player.first, player.second );
			}

			g_aimbot.process( );

			if( g_aimbot.target ) {
				if( options::visuals::show_hotbar )
				{
					g_esp.draw_hotbar( g_aimbot.target ); 
				}
				if( options::visuals::show_clothes )
				{
					g_esp.draw_clothes( g_aimbot.target );
				}
			}

			if( g_sdk.get_key( options::add_friend_key )
				&& options::friend_system )
				g_esp.m_friends.push_back( g_aimbot.target );

			core::player_walk_movement* movement = local_player->get_movement( );
			core::player_eyes* eyes = local_player->get_eyes( );

			float speed = options::aimbot::exploits::movement::fly_speed / 100.f;

			bool has_triggered_stopper[ 2 ]{ false };
			has_triggered_stopper[ 0 ] = g_esp.current_vertical_fly >= g_esp.max_vertical_fly;
			has_triggered_stopper[ 1 ] = g_esp.current_horizontal_fly >= g_esp.max_horizontal_fly;

			if( eyes 
				&& movement ) {
				if( options::aimbot::exploits::movement::increase_height ) {
					if( g_sdk.get_key( options::aimbot::exploits::movement::increase_height_key ) )
						movement->set_capsule_height( options::aimbot::exploits::movement::height_amount );
					else
						movement->set_capsule_height( 1.8f );
				}

				if( options::aimbot::exploits::combat::head_teleportation
					&& g_sdk.get_key( options::aimbot::exploits::combat::teleport_key ) ) {
					core::base_player* target = g_aimbot.target;
					if( target ) {
						core::player_model* model = target->get_model( );
						if( model ) {
							vec3_t target_pos = model->get_position( );
							if( !target_pos.is_zero( )
								&& target_pos.distance( g_cheat.local_pos ) < 5.f )
								movement->teleport_to( vec3_t( target_pos.x, target_pos.y + 1.f, target_pos.z ) );
						}
					}
				}

				vec3_t movement_direction = vec3_t( );

				// get movement direction..
				{
					vec4_t rotation = eyes->get_body_rotation( );
					if( !rotation.is_zero( ) ) {
						const vec3_t vecright = vec3_t( 1.f, 0.f, 0.f );
						const vec3_t vecforward = vec3_t( 0.f, 0.f, 1.f );
						const vec3_t vecup = vec3_t( 0.f, 1.f, 0.f );

						if( g_sdk.get_key( key_code::W ) )
							movement_direction += g_math.quatmult( &vecforward, &rotation );
						if( g_sdk.get_key( key_code::S ) )
							movement_direction -= g_math.quatmult( &vecforward, &rotation );
						if( g_sdk.get_key( key_code::A ) )
							movement_direction -= g_math.quatmult( &vecright, &rotation );
						if( g_sdk.get_key( key_code::D ) )
							movement_direction += g_math.quatmult( &vecright, &rotation );
						if( g_sdk.get_key( key_code::Space ) )
							movement_direction.y += 1.f;
						if( g_sdk.get_key( key_code::LeftShift ) )
							movement_direction.y -= 1.f;
					}
				}

				if( options::aimbot::exploits::movement::always_sprint ) {
					movement->set_is_running( 1.f );
					g_game.set_is_sprinting( true );
				}

				if( options::aimbot::exploits::movement::fly_hack ) {
					bool is_moving = g_sdk.get_key( key_code::W ) || g_sdk.get_key( key_code::A ) ||
						g_sdk.get_key( key_code::S ) || g_sdk.get_key( key_code::D ) || g_sdk.get_key( key_code::Space );

					if( g_sdk.get_key( options::aimbot::exploits::movement::fly_key ) ) {
						g_esp.not_in_fly_action = false;

						movement->set_flying( true );
						movement->set_capsule_center( -1000.f );

						if( !movement_direction.is_zero( ) )
							movement->set_targetmovement( movement_direction * speed );
					}
					else {
						movement->set_capsule_center( 0.9f );
						movement->set_flying( false );
						g_esp.not_in_fly_action = true;
					}
				}

				if( options::aimbot::exploits::movement::stopper_fly
					&& ( has_triggered_stopper[ 0 ] || has_triggered_stopper[ 1 ] )
					&& !g_sdk.get_key( options::aimbot::exploits::movement::ignore_key ) )
				{
					vec3_t current = g_cheat.local_pos;

					vec3_t previous_position = current;

					core::player_ticks* last_sent_tick = local_player->get_lastSentTick( );

					if( last_sent_tick ) {
						// no fall damage when teleporting.
						movement->set_was_falling( true );
						movement->set_previous_velocity( vec3_t( ) );

						vec3_t old = last_sent_tick->get_position( );

						float height = ( current.y < old.y ? current.y : old.y ) - 0.75f;

						if( has_triggered_stopper[ 0 ] )
							previous_position = vec3_t( previous_position.x,
								height, previous_position.z );
						else if( has_triggered_stopper[ 1 ] )
							previous_position = vec3_t( old.x, height, old.z );

						movement->set_targetmovement( vec3_t( ) );

						if( !previous_position.is_zero( ) )
							movement->teleport_to( previous_position );// teleport to our previous position.
					}
				}
			}

			camera* camera = g_cheat.camera_ptr;
			if( camera ) {
				if( options::visuals::world::aspect_changer )
					camera->set_aspect_ratio( options::visuals::world::aspect_value );
			}

			g_esp.apply_fly_violation( );

			g_esp.show_reload_bar( ); // render reload bar BEFORE desync bar, so spacing works fine:p
			g_esp.show_desync_bar( );

			g_esp.draw_bullet_tracers( );

			//g_sdk.set_admin_ambient_mp( options::visuals::world::rayleigh_value );
			//g_sdk.set_admin_ref_mp( options::visuals::world::rayleigh_value );

			if( local_player->has_flag( player_flags::is_connected ) ) {
				if( options::visuals::local_trails )
					g_esp.draw_local_trails( );
				// ----------------------------- //
				if( options::visuals::show_last_sent_tick )
					g_esp.draw_last_sent_tick( );
			}

			int indicator_spacing = 0;

			if( options::visuals::indicators ) {
				if( options::visuals::fly_hack_indicator )
					g_esp.fly_hack_bar( );

				float current_lag = local_player->get_clientTickInterval( );

				if( g_aimbot.target )
				{
					std::string text = xs( "aimbot[t" );
					if( g_aimbot.is_in_aim )
						text += "|b]";
					else
						text += "]";

					g_render.draw_text( vec4_t( g_cheat.screen_center.x - 50, g_cheat.screen_center.y + ( 15 + 
						( g_esp.indicators_spacing[ 0 ] + g_esp.indicators_spacing[ 1 ] ) ), 150, 20 ),
						text, color_t( g_cheat.pulsation.r, 125, g_cheat.pulsation.b - 125.f ), true, 10, g_esp.font_flags );

					indicator_spacing += 10;
				}

				if( current_lag > 0.1f )
				{
					std::string text = xs( "lag" );
					text += xs( "(" );
					text += g_math.remove_trailing_zeros( current_lag );
					text += xs( "s)" );

					g_render.draw_text( vec4_t( g_cheat.screen_center.x - 50, g_cheat.screen_center.y + ( 15 + indicator_spacing 
						+ ( g_esp.indicators_spacing[ 0 ] + g_esp.indicators_spacing[ 1 ] ) ), 150, 20 ),
						text, g_cheat.rainbow, true, 10, g_esp.font_flags );

					indicator_spacing += 10;
				}

				if( !g_esp.not_in_fly_action )
				{
					std::string text = std::string( );
					bool unsafe[ 3 ]{ false };
					unsafe[ 1 ] = ( g_esp.current_vertical_fly - g_esp.max_vertical_fly ) > 2.f;
					unsafe[ 2 ] = ( g_esp.current_horizontal_fly - g_esp.max_horizontal_fly ) > 2.f;

					if( ( unsafe[ 1 ] ) )
						text += "*";
					text += xs( "noclipping" );
					if( ( unsafe[ 2 ] ) )
						text += "*";

					color_t color = color_t( g_cheat.pulsation.r - 127, g_cheat.pulsation.g * 0.25f, g_cheat.pulsation.g * 0.25f );
					if( unsafe[ 1 ] || unsafe[ 2 ] )
						color = color_t( g_cheat.pulsation.r * g_cheat.pulsation.g * 0.1f, 127, 0 );

					g_render.draw_text( vec4_t( g_cheat.screen_center.x - 50, g_cheat.screen_center.y + ( 15 + indicator_spacing 
						+ ( g_esp.indicators_spacing[ 0 ] + g_esp.indicators_spacing[ 1 ] ) ), 150, 20 ),
						text, color, true, 10, g_esp.font_flags );

					indicator_spacing += 10;
				}

				if( !g_esp.manipulation_angle.is_zero( ) )
				{
					std::string text = std::string( );
					text += xs( "manipulator" );
					if( current_lag > 0.5f )
						text += xs( "[r]" );
					else
						text += xs( "[c]" );

					color_t color = color_t( 255 / current_lag, 255 * current_lag, 255 - ( 125 * current_lag ) );

					g_render.draw_text( vec4_t( g_cheat.screen_center.x - 50, g_cheat.screen_center.y + ( 15 + indicator_spacing 
						+ ( g_esp.indicators_spacing[ 0 ] + g_esp.indicators_spacing[ 1 ] ) ), 150, 20 ),
						text, color, true, 10, g_esp.font_flags );
				}
			}

			g_game.set_underwater_blur( !options::visuals::world::clear_underwater );

			if( options::aimbot::exploits::misc::zoom_fov
				&& g_sdk.get_key( options::aimbot::exploits::misc::zoom_key ) )
				g_game.set_graphics_fov( options::aimbot::exploits::misc::zoom_fov_amount );
			else if( options::aimbot::exploits::misc::fov_changer )
				g_game.set_graphics_fov( options::aimbot::exploits::misc::fov_amount );
			else
				g_game.set_graphics_fov( 90.f );

			core::base_mountable* mountable = local_player->get_mountable( );

			if( mountable )
			{
				if( options::aimbot::exploits::combat::can_attack_in_vehicles )
					mountable->set_can_wield_item( true );

				if( options::aimbot::exploits::combat::unlock_view_angles )
					mountable->set_ignore_vehicle_parent( true );
			}

			g_sdk.ignore_layer_collision( layer::PlayerMovement, layer::Tree, options::aimbot::exploits::movement::walk_through_trees );
			g_sdk.ignore_layer_collision( layer::PlayerMovement, layer::AI, options::aimbot::exploits::movement::walk_through_players );
		}

		return; // yeah
	}

	void performance_ui_update_hook( void* instance )
	{
		if( first_loaded )
		{
			static uintptr_t game_object = il2mgr::methods::object_new( il2mgr::init_class( xs( "GameObject" ), xs( "UnityEngine" ) ) );
			g_sdk.create( game_object, xs( "" ) );

			static uintptr_t dev_controls = il2mgr::type_object( xs( "" ), xs( "DevControls" ) );
			g_sdk.add_component( game_object, dev_controls );
			g_sdk.dont_destroy_on_load( game_object );

			first_loaded = false;
		}

		static auto update_performance_ui = reinterpret_cast< void( * )( void* ) >( hook_address[ 5 ] );
		spoof_ret( update_performance_ui, instance );
	}
}
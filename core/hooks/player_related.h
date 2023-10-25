#pragma once

#include "../includes/hinclude.h"
#include "../features/aimbot/aimbot.h"
#include "../features/visuals/esp.h"
#include "../features/options.h"

void handle_exploits( core::base_player* local_player, core::item* held_item )
{
	if( options::aimbot::exploits::time::fast_switch )
	{
		held_item->set_deploy_delay( 0.f );
	}

	if( held_item->is_melee( ) )
	{
		if( options::aimbot::exploits::movement::disable_slow_down_melee )
		{
			held_item->set_block_sprint( false );
		}
		if( options::aimbot::exploits::combat::extended_melee )
		{
			held_item->set_attack_max_distance( options::aimbot::exploits::combat::attack_radius );
		}
	}
	else if( held_item->is_gun( ) ) {
		if( options::aimbot::exploits::combat::big_bullets )
		{
			held_item->set_bullet_thickness( options::aimbot::exploits::combat::bullet_size / 100.f );
		}
		if( options::aimbot::exploits::combat::aim_bolt_cycle )
		{
			held_item->set_aiming_while_cycling( false );
		}
		if( options::aimbot::exploits::time::fast_bow )
		{
			held_item->set_attack_ready( true );
			held_item->set_was_aiming( true );
		}
		if( options::aimbot::exploits::combat::modify_eoka_chance ) {
			float eoka_chance = options::aimbot::exploits::combat::eoka_chance / 100.f;

			held_item->set_always_eoka( eoka_chance );

			if( eoka_chance > 0.9f
				&& g_sdk.get_key( key_code::Mouse0 ) )
				held_item->set_did_spark_this_frame( true );
		}
		if( options::aimbot::exploits::time::rapid_fire )
		{
			held_item->set_repeat_delay( options::aimbot::exploits::time::rapid_fire_speed / 100.f );
		}

		if( options::aimbot::exploits::time::instant_charge_compound )
		{
			held_item->set_current_hold_progress( 1.5f );
			held_item->set_string_bonus_damage( 1000.f );
			held_item->set_movement_penalty_ramp_up_time( 1000.f );
		}

		if( options::aimbot::exploits::misc::fake_fire
			&& ( g_sdk.get_key( options::aimbot::exploits::misc::fake_fire_key ) || options::aimbot::exploits::misc::fake_fire_on ) )
		{
			static float last_shoot = 0.f;
			float delay = options::aimbot::exploits::misc::delay_fake_fire / 100.f;

			if( ( last_shoot - local_player->lastSentTickTime( ) ) > delay ) {
				held_item->send_broadcast_projectile( Signal::Attack, xs( "" ) );
				last_shoot = local_player->lastSentTickTime( );
			}
		}

		static bool just_shot{ }, did_reload{ };
		float time_since_last_shot = 0.0f, fixed_time_last_shot = 0.0f;

		if( options::aimbot::auto_reload )
		{
			if( !did_reload )
				time_since_last_shot = ( g_sdk.get_fixedTime( ) - fixed_time_last_shot );

			if( !just_shot 
				&& ( time_since_last_shot > 0.2f ) )
			{
				held_item->server_rpc( xs( "StartReload" ) );
				held_item->send_signal_broadcast( Signal::Reload );
				just_shot = true;
			}
			if( time_since_last_shot >
				( held_item->get_reload_time( ) - ( held_item->get_reload_time( ) / 10.f ) )
				&& !did_reload )
			{
				held_item->server_rpc( xs( "Reload" ) );
				did_reload = true;
				time_since_last_shot = 0;
			}

			fixed_time_last_shot = g_sdk.get_fixedTime( );
		}

		if( options::aimbot::exploits::combat::burst_weapons ) {
			held_item->set_is_burst( true );
		}
		if( options::aimbot::exploits::combat::automatic_weapons ) {
			held_item->set_is_automatic( true );
		}
		else if( options::aimbot::exploits::combat::semi_automatic_weapons ) {
			held_item->set_is_automatic( false );
		}

		float to_reduce = options::aimbot::exploits::combat::reduce_recoil / 100.f;

		held_item->set_recoil_min_max( options::aimbot::exploits::combat::no_recoil ?
			to_reduce : 1.f );

		if( options::aimbot::exploits::combat::no_sway )
		{
			held_item->set_aim_sway( 0.f );
			held_item->set_aim_sway_speed( 0.f );
		}
		if( options::aimbot::exploits::combat::no_spread )
		{
			float spread = options::aimbot::exploits::combat::reduce_spread / 100.f;

			//std::cout << "1:" << held_item->get_aim_cone( )  << std::endl;
			//std::cout << "2:" << held_item->get_aim_cone_penalty_per_shot( )  << std::endl;
			//std::cout << "3:" << held_item->get_aim_cone_penalty( )  << std::endl;
			//std::cout << "4:" << held_item->get_hip_aim_cone( )  << std::endl;
			//std::cout << "5:" << held_item->get_stance_penalty( )  << std::endl;
			//std::cout << "6:" << held_item->get_aim_cone_penalty_max( )  << std::endl;
			//std::cout << "7:" << held_item->get_aim_penalty_recover_time( )  << std::endl;
			//std::cout << "8:" << held_item->get_aim_penalty_recover_delay( )  << std::endl;
			//std::cout << "9:" << held_item->get_aim_sight_aim_cone_scale( )  << std::endl;
			//std::cout << "10:" << held_item->get_aim_sight_aim_cone_offset( )  << std::endl;
			//std::cout << "11:" << held_item->get_hip_aim_cone_scale( )  << std::endl;
			//std::cout << "12:" << held_item->get_hip_aim_cone_offset( )  << std::endl;

			held_item->set_aim_cone( spread );
			held_item->set_aim_cone_penalty_per_shot( spread );
			held_item->set_aim_cone_penalty( spread );
			held_item->set_hip_aim_cone( spread );
			held_item->set_stance_penalty( spread );
			held_item->set_aim_cone_penalty_max( spread );
			held_item->set_aim_penalty_recover_time( spread );
			held_item->set_aim_penalty_recover_delay( spread );
			held_item->set_aim_sight_aim_cone_scale( spread );
			held_item->set_aim_sight_aim_cone_offset( spread );
			held_item->set_hip_aim_cone_scale( spread );
			held_item->set_hip_aim_cone_offset( spread );
		}
		if( options::aimbot::exploits::combat::quick_bullets )
		{
			float speed = ( options::aimbot::exploits::combat::bullet_speed / 100.f );

			held_item->set_projectile_velocity_scale( speed );
		}
		if( options::aimbot::exploits::combat::spoof_hit_distance )
		{
			float distance = options::aimbot::exploits::combat::bullet_distance;

			held_item->set_projectile_distance_scale( distance );
		}
	}
}

void handle_rpc_exploits( core::base_player* local_player, core::item* held_item ) {
	core::base_player* best_target = g_aimbot.target;
	float distance = FLT_MAX;
	static float last_syringe = 0.f;

	if( !last_syringe )
		last_syringe = local_player->lastSentTickTime( );

	if( best_target ) {
		core::player_model* model = best_target->get_model( );
		if( !model )
			return;

		distance = g_cheat.local_pos.distance( model->get_position( ) );

		if( options::aimbot::exploits::time::instant_revive
			|| options::aimbot::exploits::misc::keep_wounded_alive )
		{
			if( best_target->is_knocked( ) ) {
				if( distance < 10.0f )
				{
					if( ( g_sdk.get_key( options::aimbot::exploits::time::revive_key ) || options::aimbot::exploits::time::always_revive_target )
						&& options::aimbot::exploits::time::instant_revive ) {
						best_target->server_rpc( xs( "RPC_Assist" ) );
					}
					if( options::aimbot::exploits::misc::keep_wounded_alive )
					{
						best_target->server_rpc( xs( "RPC_KeepAlive" ) );
					}
				}
			}
		}
	}

	if( held_item->is_heal( ) ) {
		if( options::aimbot::exploits::time::fast_heal )
		{
			if( ( local_player->lastSentTickTime( ) - last_syringe ) > 0.7f ) {
				if( distance < 5.f )
					held_item->server_rpc( xs( "UseOther" ) );
				else
					held_item->server_rpc( xs( "UseSelf" ) );
				last_syringe = local_player->lastSentTickTime( );
			}
		}
	}
}

namespace baseplayer
{
	inline void client_input_hook( core::base_player* player, core::input_state* state )
	{
		auto orig_baseplayer_client_input = reinterpret_cast< void( * )( core::base_player*, core::input_state* ) >( hook_address[ 1 ] );

		while( !g_cheat.camera_ptr )
			get_main_camera( );

		// reset this incase.
		if( ( g_sdk.get_key( key_code::End )
			|| !options::friend_system )
			&& !g_esp.m_friends.empty( ) )
			g_esp.m_friends.clear( );

		g_cheat.cam_pos = g_sdk.get_camera_pos( );

		g_render.ddraw_get( );

		core::base_player* local_player = g_cheat.local;
		if( local_player
			&& !local_player->get_life_state( ) ) {
			float desync_time = ( g_sdk.realtimeSinceStartup( ) - local_player->lastSentTickTime( ) ) - 0.03125 * 3;

			g_esp.maximum_eye_height = ( 0.1f + ( ( desync_time + 2.f / 60.f + 0.125f ) * 1.5f ) * local_player->get_max_speed( ) ) - 0.05f;

			core::item* item = local_player->get_held_item( );
			
			core::model_state* model_state = local_player->get_modelstate( );
			
			core::player_walk_movement* movement = local_player->get_movement( );
			core::player_input* input = local_player->get_input( );
			core::player_eyes* eyes = local_player->get_eyes( );
			if( eyes )
				g_cheat.local_eyes = eyes;

			if( eyes
				&& model_state
				&& movement ) {
				if( movement->flying( )
					|| !g_esp.not_in_fly_action )
					model_state->add_flag( model_state_flags::in_sprint );

				if( options::visuals::world::night_stars )
					model_state->add_flag( model_state_flags::asleep );

				model_state->remove_flag( model_state_flags::in_fly );

				static float x_value{ }, y_value{ }, w_value{ };

				float fake_lag = options::aimbot::exploits::time::fake_lag_amount;

				bool has_fake_lag = options::aimbot::exploits::time::fake_lag 
					&& ( g_sdk.get_key( options::aimbot::exploits::time::fake_lag_key ) || options::aimbot::exploits::time::fake_lag_on );

				if( has_fake_lag )
					local_player->set_clientTickInterval( fake_lag );
				else
					local_player->set_clientTickInterval( 0.05f );

				if( options::aimbot::exploits::combat::modify_can_attack )
				{
					model_state->add_flag( model_state_flags::on_ground );
					movement->set_is_grounded( 1.f );
				}

				if( options::aimbot::exploits::movement::climb_assist ) {
					movement->set_ground_angle_new( 0.f );
				}

				if( g_esp.not_in_fly_action ) {
					if( options::aimbot::exploits::misc::suicide
						&& g_sdk.get_key( options::aimbot::exploits::misc::suicide_key ) ) {
						movement->set_was_falling( true );
						movement->set_previous_velocity( vec3_t( 0, -1000, 0 ) );
						movement->set_ground_time( 0.f );
					}
					else {
						if( options::aimbot::exploits::misc::disable_land_damage )
						{
							movement->set_was_falling( true );
							movement->set_previous_velocity( vec3_t( ) );
						}
					}

					auto next_ground_time = movement->get_ground_time( ) + 0.5f;

					if( options::aimbot::exploits::movement::infinite_jump )
					{
						movement->set_jump_time( 0.f );
						movement->set_ground_time( next_ground_time );
						movement->set_land_time( 0.f );
					}
					movement->set_gravity_multiplier( options::aimbot::exploits::movement::high_jump ? options::aimbot::exploits::movement::jump_height / 100.f : 2.35f );
				}

				static bool has_debug_camera = false;

				if( options::aimbot::exploits::misc::debug_camera ) {
					static int delay = 0;

					if( g_sdk.get_key( options::aimbot::exploits::misc::debug_camera_key )
						&& --delay < 25 ) {
						has_debug_camera = !has_debug_camera;
						delay = 25;
					}

					static vec4_t rotation_before_debug = vec4_t( );
					static vec2_t view_before_debug = vec2_t( );

					if( has_debug_camera ) {
						bool has_pressed_left = g_sdk.get_key( key_code::A );

						bool has_pressed_right = g_sdk.get_key( key_code::D );

						bool has_pressed_down = g_sdk.get_key( key_code::S );

						bool has_pressed_up = g_sdk.get_key( key_code::W );

						bool has_pressed_shift = g_sdk.get_key( key_code::LeftShift );

						bool has_pressed_space = g_sdk.get_key( key_code::Space );

						//bool has_pressed_h = g_sdk.get_key( key_code::H );

						//bool has_pressed_k = g_sdk.get_key( key_code::K );

						if( has_pressed_left )
							x_value -= 0.25f;
						else if( has_pressed_right )
							x_value += 0.25f;

						if( has_pressed_down )
							w_value -= 0.25f;
						else if( has_pressed_up )
							w_value += 0.25f;

						if( has_pressed_shift )
							y_value -= 0.25f;
						else if( has_pressed_space )
							y_value += 0.25f;

						if( !rotation_before_debug.is_zero( ) )
							eyes->set_body_rotation( rotation_before_debug );

						if( input ) {
							if( !view_before_debug.is_zero( ) )
								input->set_view_angles( view_before_debug );
						}

						if( movement ) {
							movement->set_ground_time( 1.f );
							movement->set_jump_time( 0.f );
							movement->set_land_time( 0.f );
							movement->set_targetmovement( vec3_t( ) );
						}

						eyes->set_view_offset( vec3_t( x_value, y_value, w_value ) );
					}
					else {
						rotation_before_debug = eyes->get_body_rotation( );
						if( input )
							view_before_debug = input->get_view_angles( );

						x_value = w_value = y_value = 0; 
					}
				}
				else
					has_debug_camera = false;

				if( !has_debug_camera ) {
					bool has_up_view_offset = options::aimbot::exploits::misc::long_neck
						&& g_sdk.get_key( options::aimbot::exploits::misc::view_height );

					bool has_right_view_offset = options::aimbot::exploits::misc::long_neck_right
						&& g_sdk.get_key( options::aimbot::exploits::misc::view_right );

					bool has_left_view_offset = options::aimbot::exploits::misc::long_neck_left
						&& g_sdk.get_key( options::aimbot::exploits::misc::view_left );

					float height_view_offset = ( options::aimbot::exploits::misc::long_neck_height );
					if( options::aimbot::exploits::misc::use_max_view )
						height_view_offset = g_esp.maximum_eye_height;

					float left_view_offset = ( options::aimbot::exploits::misc::long_neck_left_amount );

					float right_view_offset = ( options::aimbot::exploits::misc::long_neck_right_amount );

					if( has_up_view_offset	
						&& ( has_left_view_offset || has_right_view_offset ) )
					{
						// we need this so shots are registered.
						local_player->set_clientTickInterval( fake_lag < 1.f ? 1.f : fake_lag );

						eyes->set_view_offset( vec3_t( has_left_view_offset ? -left_view_offset : right_view_offset, height_view_offset, 0 ) );
					}
					else if( has_up_view_offset )
					{
						if( options::aimbot::exploits::misc::use_max_view )
							local_player->set_clientTickInterval( 1.f );
						else {
							if( height_view_offset >= 0.4f )
								local_player->set_clientTickInterval( fake_lag * ( height_view_offset - 0.5f ) );
						}

						eyes->set_view_offset( vec3_t( 0, height_view_offset, 0 ) );
					}
					else if( has_right_view_offset )
					{
						if( right_view_offset >= 0.4f )
							local_player->set_clientTickInterval( fake_lag * ( right_view_offset - 0.5f ) );

						eyes->set_view_offset( vec3_t( right_view_offset, 0, 0 ) );
					}
					else if( has_left_view_offset )
					{
						if( left_view_offset >= 0.4f )
							local_player->set_clientTickInterval( fake_lag * ( left_view_offset - 0.5f ) );

						eyes->set_view_offset( vec3_t( -left_view_offset, 0, 0 ) );
					}
					else {
						if( !has_fake_lag )
							local_player->set_clientTickInterval( 0.05f );
					}
				}
			}

			if( item )
			{
				g_esp.melee_max_dist = item->get_attack_max_distance( ) + 2.f;

				if( options::aimbot::kill_aura ) {
					vec3_t pos = reinterpret_cast< core::base_player* >( g_aimbot.target )->get_bone_position( head );

					if( pos.distance( g_cheat.local_pos ) < g_esp.melee_max_dist )
						g_esp.do_melee_attack( pos, g_aimbot.target, true );
				}

				if( options::aimbot::exploits::misc::auto_farm_ores ) {
					if( options::aimbot::exploits::misc::auto_farm_only_hotspot ) {
						core::base_entity* hotspot = g_esp.get_closest_object_of_class( xs( "OreHotSpot" ), g_esp.melee_max_dist );
						if( hotspot ) {
							core::transform* transform = hotspot->get_transform( );
							if( transform ) {
								vec3_t pos = transform->get_position( );

								g_esp.do_melee_attack( pos, hotspot, false );
							}
						}
					}
					else {
						core::base_entity* ore = g_esp.get_closest_object_of_class( xs( "OreResourceEntity" ), g_esp.melee_max_dist );
						if( ore ) {
							core::transform* transform = ore->get_transform( );
							if( transform ) {
								vec3_t pos = transform->get_position( );

								// increase the height a bit.
								pos.y += 0.25f;

								g_esp.do_melee_attack( pos, ore, false );
							}
						}
					}
				}

				if( eyes ) {
					vec3_t eye_pos = eyes->get_position( );
					if( options::aimbot::exploits::misc::auto_farm_trees ) {
						if( options::aimbot::exploits::misc::auto_farm_only_hotspot ) {
							core::base_entity* marker = g_esp.get_closest_object_of_class( xs( "TreeMarker" ), g_esp.melee_max_dist );
							if( marker ) {
								core::transform* transform = marker->get_transform( );
								if( transform ) {
									vec3_t pos = transform->get_position( );
									pos.y = eye_pos.y;

									g_esp.do_melee_attack( pos, marker, false );
								}
							}
						}
						else {
							core::base_entity* tree = g_esp.get_closest_object_of_class( xs( "TreeEntity" ), g_esp.melee_max_dist );
							if( tree ) {
								core::transform* transform = tree->get_transform( );
								if( transform ) {
									vec3_t pos = transform->get_position( );
									pos.y = eye_pos.y;

									g_esp.do_melee_attack( pos, tree, false );
								}
							}
						}
					}
				}

				core::base_view_model* view = core::base_view_model::get_view( );
				if( view ) {
					core::viewmodel_bob* bob = view->get_bob( );

					core::viewmodel_lower* lower = view->get_lower( );

					if( bob
						&& options::aimbot::exploits::misc::no_viewmodel_bob ) {
						bob->set_bob_amount_run( 0.f );
						bob->set_bob_amount_walk( 0.f );
						bob->set_bob_speed_run( 0.f );
						bob->set_bob_speed_walk( 0.f );
					}

					if( lower
						&& options::aimbot::exploits::misc::no_lower )
						lower->set_should_lower( false );
				}

				//core::base_projectile* proj = reinterpret_cast< core::base_projectile* >( held_item );

				//if( proj ) {
				//	std::cout << "ayo" << std::endl;
				//	if( g_sdk.get_key( key_code::N ) ) {
				//		core::base_projectile::Magazine* magazine = proj->get_primaryMagazine( );
				//		if( magazine ) {
				//			proj->launch_projectile( );
				//			magazine->contents( )--;
				//			proj->update_ammo_display( );
				//			proj->shot_fired( );
				//			proj->did_attack_clientside( );
				//		}
				//	}
				//}

				handle_exploits( local_player, item );
				handle_rpc_exploits( local_player, item );
			}

			if( ( g_sdk.get_key( options::aimbot::exploits::misc::pickup_key ) || options::aimbot::exploits::misc::always_pickup ) ) {
				if( options::aimbot::exploits::misc::auto_pickup_items ) {
					core::base_entity* entity = g_esp.get_closest_object_of_class( xs( "DroppedItem" ), options::aimbot::exploits::misc::max_item_distance );
					if( entity ) {
						bool can_pickup = false;

						core::item* item = entity->get_world_item( );
						if( item ) {
							std::string text = g_sdk.ws2s( item->get_weapon_name( ) );
							if( options::aimbot::exploits::misc::pickup_everything )
								can_pickup = true;

							if( item->is_gun( ) )
								can_pickup = true;
							else if( item->is_melee( ) )
								can_pickup = true;
							else if( item->is_heal( ) )
								can_pickup = true;
							else if( text.find( "scrap" ) != std::string::npos )
								can_pickup = true;
							else if( text.find( "ammo" ) != std::string::npos ) {
								if( text.find( "incendiary" ) != std::string::npos )
									can_pickup = true;
								else if( text.find( "hv" ) != std::string::npos )
									can_pickup = true;
								else if( text.find( "explosive" ) != std::string::npos )
									can_pickup = true;
								else 
									can_pickup = true;
							}
						}
						if( can_pickup )
							entity->server_rpc( xs( "Pickup" ) );
					}
				}
				if( options::aimbot::exploits::misc::auto_pickup ) {
					core::base_entity* collectible = g_esp.get_closest_object_of_class( xs( "CollectibleEntity" ), options::aimbot::exploits::misc::max_collectible_distance );
					if( collectible )
						collectible->server_rpc( xs( "Pickup" ) );
				}
			}
			if( options::aimbot::exploits::misc::auto_grade
				&& ( g_sdk.get_key( options::aimbot::exploits::misc::grade_key ) || options::aimbot::exploits::misc::always_grade ) ) {
				core::building_block* building_block = ( core::building_block* )g_esp.get_closest_object_of_class( xs( "BuildingBlock" ), options::aimbot::exploits::misc::max_grade_distance );
				if( building_block )
					if( building_block->can_upgrade( options::aimbot::exploits::misc::grade_tier, 0, local_player ) ) {
						if( building_block->can_afford( options::aimbot::exploits::misc::grade_tier, 0, local_player ) )
							building_block->upgrade( options::aimbot::exploits::misc::grade_tier, 0, local_player );
					}
			}
			if( options::aimbot::exploits::misc::auto_codelock 
				&& ( g_sdk.get_key( options::aimbot::exploits::misc::codelock_key ) || options::aimbot::exploits::misc::always_pickup ) ) {
				auto code = std::to_string( options::aimbot::exploits::misc::code_lock_code );

				core::base_entity* code_lock = g_esp.get_closest_object_of_class( xs( "CodeLock" ), options::aimbot::exploits::misc::max_lock_distance );
				if( code_lock ) {
					local_player->server_rpc( ( uintptr_t )code_lock, xs( "RPC_ChangeCode" ), code.c_str( ), false );
					local_player->server_rpc( ( uintptr_t )code_lock, xs( "TryLock" ) );
					local_player->server_rpc( ( uintptr_t )code_lock, xs( "RPC_Lock" ) );
				}
			}
		}

		spoof_ret( orig_baseplayer_client_input, player, state );

		g_cheat.global_time = g_sdk.get_time( );

		if( local_player )
		{
			if( options::aimbot::exploits::misc::gesture_spam ) {
				switch( options::aimbot::exploits::misc::gesture_type ) {
				case 0:
					local_player->send_signal_broadcast( Signal::Gesture, xs( "clap" ) );
					break;
				case 1:
					local_player->send_signal_broadcast( Signal::Gesture, xs( "friendly" ) );
					break;
				case 2:
					local_player->send_signal_broadcast( Signal::Gesture, xs( "thumbsdown" ) );
					break;
				case 3:
					local_player->send_signal_broadcast( Signal::Gesture, xs( "thumbsup" ) );
					break;
				case 4:
					local_player->send_signal_broadcast( Signal::Gesture, xs( "ok" ) );
					break;
				case 5:
					local_player->send_signal_broadcast( Signal::Gesture, xs( "point" ) );
					break;
				case 6:
					local_player->send_signal_broadcast( Signal::Gesture, xs( "shrug" ) );
					break;
				case 7:
					local_player->send_signal_broadcast( Signal::Gesture, xs( "victory" ) );
					break;
				case 8:
					local_player->send_signal_broadcast( Signal::Gesture, xs( "wave" ) );
					break;
				case 9:
					local_player->send_signal_broadcast( Signal::Gesture, xs( "dance.cabbagepatch" ) );
					break;
				case 10:
					local_player->send_signal_broadcast( Signal::Gesture, xs( "dance.twist" ) );
					break;
				}
			}

			if( options::aimbot::exploits::misc::spin_bot )
			{
				vec3_t angle{ };
				angle.x = std::sinf( ( g_sdk.system_time( ) * 180.f ) * 3.14f ) * 180.f; // this will be our yaw.
				angle.y = std::sinf( ( g_sdk.system_time( ) * 360.f ) * 3.14f ) * 360.f; // pitch
				angle.z = std::sinf( ( g_sdk.system_time( ) * 90.f ) * 3.14f ) * 90.f; // roll

				core::input_message* input_message = state->get_input_message( );
				if( input_message )
					input_message->set_aim_angles( angle );
			}

			if( options::aimbot::exploits::misc::fake_admin )
				local_player->add_flag( player_flags::is_admin );

			core::model_state* model_state = local_player->get_modelstate( );
			if( model_state ) {
				model_state->remove_flag( model_state_flags::in_fly );
				if( options::aimbot::exploits::misc::interactive_debug )
					model_state->add_flag( model_state_flags::is_mounted );

				core::player_walk_movement* movement = local_player->get_movement( );
				if( movement ) {
					if( options::aimbot::exploits::movement::always_sprint ) {
						model_state->add_flag( model_state_flags::in_sprint );
						movement->set_is_running( 1.f );
					}
				}
				
				if( options::aimbot::exploits::movement::omni_sprint ) {
					model_state->add_flag( model_state_flags::in_sprint );
					model_state->set_sprinting( true );

					if( g_sdk.get_key( options::aimbot::exploits::movement::omni_sprint_key ) )
						g_sdk.set_timescale( options::aimbot::exploits::movement::omni_sprint_speed / 100.f );
					else
						g_sdk.set_timescale( 1.f );
				}
				else
					g_sdk.set_timescale( 1.f );

				if( options::visuals::world::night_stars )
					model_state->add_flag( model_state_flags::asleep );

				if( options::aimbot::exploits::movement::silent_walk
					&& g_sdk.get_key( key_code::LeftShift ) ) {
					model_state->set_onLadder( true );
					model_state->add_flag( model_state_flags::on_ladder );
				}
			}
		}
	}

	inline void fix_culling_hook( core::base_player* baseplayer, float dist, bool visibility = false )
	{
		auto orig_fix_culling = reinterpret_cast< void( * )( core::base_player*, float, bool ) >( hook_address[ 2 ] );
		if( options::visuals::chams )
			return spoof_ret( orig_fix_culling, baseplayer, 150.f, true );

		return spoof_ret( orig_fix_culling, baseplayer, dist, visibility );
	}

	inline void on_attacked_hook( void* instance, core::hit_info* hit_info )
	{
		auto orig_on_attacked = reinterpret_cast< void( * )( void*, core::hit_info* ) >( hook_address[ 3 ] );

		core::base_entity* hit_entity = hit_info->get_hit_entity( );

		core::base_player* local = g_cheat.local;
        if( !local )
			return spoof_ret( orig_on_attacked, instance, hit_info );

        core::player_eyes* eyes = local->get_eyes( );
        if( !eyes )
            return spoof_ret( orig_on_attacked, instance, hit_info );

        vec3_t head_pos = local->get_bone_position( head );

		bool has_up_view_offset = options::aimbot::exploits::misc::long_neck
			&& g_sdk.get_key( options::aimbot::exploits::misc::view_height );

		bool has_right_view_offset = options::aimbot::exploits::misc::long_neck_right
			&& g_sdk.get_key( options::aimbot::exploits::misc::view_right );

		bool has_left_view_offset = options::aimbot::exploits::misc::long_neck_left
			&& g_sdk.get_key( options::aimbot::exploits::misc::view_left );

		float height_view_offset = ( options::aimbot::exploits::misc::long_neck_height / 100.f );

		float left_view_offset = ( options::aimbot::exploits::misc::long_neck_left_amount / 100.f );

		float right_view_offset = ( options::aimbot::exploits::misc::long_neck_right_amount / 100.f );

		if( g_sdk.get_key( options::aimbot::exploits::misc::view_height ) )
			head_pos.y += height_view_offset;
		
		if( g_sdk.get_key( options::aimbot::exploits::misc::view_left ) )
			head_pos.x -= left_view_offset;
		else if( g_sdk.get_key( options::aimbot::exploits::misc::view_right ) )
			head_pos.x += right_view_offset;

		if( hit_entity )
			g_esp.m_shots.emplace_back( c_esp::shot_record_t( g_sdk.get_time( ), head_pos, hit_info->get_hit_end( ), 
				reinterpret_cast< core::base_player* >( hit_entity ) ) );

		return spoof_ret( orig_on_attacked, instance, hit_info );
	}
}

namespace item_icon {
	inline void try_to_move_hook( core::item_icon* item )
	{
		auto orig_try_to_move = reinterpret_cast< void( * )( core::item_icon* ) >( hook_address[ 4 ] );

		if( options::aimbot::exploits::time::fast_loot ) {
			if( item->queued_for_looting( ) )
				item->run_timed_action( );
		}

		spoof_ret( orig_try_to_move, item );
	}
}

namespace player_eyes {
	vec3_t get_body_lean_offset_hook( core::player_eyes* instance ) {
		auto orig_player_eyes_get_body_lean_offset = reinterpret_cast< vec3_t( * )( core::player_eyes* ) >( hook_address[ 4 ] );

		if( !g_esp.manipulation_angle.is_zero( ) ) {
			std::cout << "in hook cf" << std::endl;
			return g_esp.manipulation_angle;
		}
		std::cout << "in hook rn" << std::endl;
		return spoof_ret( orig_player_eyes_get_body_lean_offset, instance );
	}
}

namespace modelstate
{
	inline void is_flying_hook( bool is_flying )
	{
		auto orig_modelstate_is_flying = reinterpret_cast< void( * )( bool ) >( hook_address[ 4 ] );

		if( options::aimbot::exploits::misc::fake_admin ) {
			is_flying = false;
			return;
		}

		return spoof_ret( orig_modelstate_is_flying, is_flying );
	}
}
#pragma once

namespace options {
	inline bool friend_system = true, load_cfg = false, save_cfg = false, rainbow_accent = false;
	inline int cfg_index = 0, font_flags = 1, add_friend_key{ }, first_tab{ }, color_tab = 0, tab_selection{ };
	inline color_t accent_color = color_t( 255, 255, 255 );

	namespace visuals {
		inline bool draw_visuals{ true }, indicators{ }, fly_hack_indicator{ }, draw_tracers{ }, offscreen_arrows{ true }, draw_radar{ },
			show_name{ true }, show_weapon{ true }, show_knocked_flag{ true }, show_ducking_flag{ true },
			show_health{ true }, show_health_text{ false }, show_distance{ },
			show_hotbar{ }, show_clothes{ }, show_lines{ }, show_view_direction{ }, can_show_sleepers{ true },
			can_show_knocked{ true }, can_show_npc{ true },
			chams{ }, rgb_chams{ }, draw_bones{ true },
			show_watermark{ }, local_trails{ }, show_last_sent_tick{ }, 
			show_desync_bar{ }, show_reload_bar{ }, modify_health_color{ };

		inline bool can_show_sleepers_oof{ true },
			can_show_knocked_oof{ true }, can_show_npc_oof{ true };

		inline bool class_name_debug{ }, prefab_name_debug{ }, is_home_pos{ };

		inline int max_player_distance{ 750 }, offscreen_distance{ 100 }, health_thickness{ 1 };

		inline int box_type{ }, chams_type{ }, remove_positions_key{ }, save_pos_key{ };

		inline color_t tracers_color{ 255, 255, 255 }, desync_bar_color{ 255, 255, 255 }, trails_color{ 255, 255, 255 }, reload_bar_color{ 255, 255, 255 };

		namespace world {
			inline bool master_switch{ false }, show_stashes{ },
				show_corpse{ }, show_backpack{ }, change_rayleigh{ },
				todsky{ }, show_grenades{ }, night_stars{ }, clear_underwater{ }, change_world_color{ }, modify_rain{ };

			inline bool show_heal{ }, show_weapons{ }, show_melee_weapons{ }, show_everything{ };

			inline bool show_distance{ }, show_health{ }, show_item_amount{ };

			inline bool stars_size{ }, stars{ }, ambient{ }, mie_changer{ }, rayleigh_changer{ }, brightness_changer{ }, aspect_changer{ };

			inline bool show_sulfur_ore{ },
				show_metal_ore{ },
				show_stone_ore{ },
				show_tool_cupboard{ },
				show_box_storages{ };

			inline bool show_ammo_nails_arrows{ };

			inline bool show_supply_signals{ }, show_supply_drops{ };

			inline bool show_oil_barrel{ },
				show_regular_barrels{ },
				show_underwater_crate{ },
				show_elite_crate{ }, show_military_crate{ }, show_bradley_crate{ },
				show_food_crate{ }, show_medical_crate{ }, show_diesel_fuel{ }, show_helicopter_crate{ }, show_hackable_locked_crate{ },
				show_normal_crate{ }, show_chickens{ }, show_small_crate{ }, show_mine_crate{ },
				show_tool_box{ },
				show_boars{ }, show_wolves{ }, show_horses{ },
				show_sharks{ }, show_deers{ }, show_polar_bears{ },
				show_bears{ }, show_sulfur_collectibles{ },
				show_metal_collectibles{ }, show_wood_collectibles{ }, 
				show_vending_machine{ }, show_drone{ }, show_recycler{ },
				show_stone_collectibles{ };

			inline bool show_hemp{ }, show_mushroom{ }, show_pumpkin{ },
				show_berrys{ }, show_corns{ }, show_potatos{ };

			inline bool show_modular_car{ }, show_two_modules_car{ }, 
				show_minicopter{ }, show_scrap_helicopter{ }, show_rhib{ }, show_bradley_apc{ },
				show_kayak{ }, show_small_motorboat{ }, show_solo_submarine{ }, show_duo_submarine{ };

			inline bool show_landmines{ }, show_npc_turrets{ }, show_auto_turrets{ }, show_shotgun_traps{ },
				show_tesla_coil{ }, show_flame_turrets{ }, show_sam_site{ },
				show_land_spikes{ }, show_bear_trap{ };

			inline float size_stars_amount{ }, brightness_stars_amount{ }, ambient_value{ }, aspect_value{ },
				light_value{ }, rayleigh_amount{ }, brightness_amount{ }, mie_amount{ }, rain_amount{ };
			
			inline int max_stash_distance{ 500 },
				max_animal_distance{ 500 }, max_trap_distance{ 500 },
				max_storage_distance{ 500 }, max_vehicle_distance{ 500 },
				max_raid_distance{ 500 }, max_item_distance{ 500 },
				max_respawn_points_distance{ 500 }, max_helicopter_distance{ 500 },
				max_corpse_distance{ 500 }, max_ore_collectibles_distance{ 500 },
				max_container_distance{ 500 }, max_food_collectibles_distance{ 500 }, max_grenade_distance{ 500 },
				max_ores_distance{ 500 }, max_barrels_distance{ 500 }, max_cars_distance{ 500 };//, rayleigh_value{ };

			inline color_t color_heal{ 255, 255, 255 }, color_weapons{ 255, 255, 255 }, color_melee_weapons{ 255, 255, 255 }, color_everything{ 255, 255, 255 }, color_backpack{ 255, 255, 255 };

			inline color_t color_stashes{ 255, 255, 255 }, color_animals{ 255, 255, 255 },
				color_traps{ 255, 255, 255 }, color_storages{ 255, 255, 255 }, color_vehicles{ 255, 255, 255 },
				color_raid{ 255, 255, 255 }, color_item{ 255, 255, 255 }, color_respawn_points{ 255, 255, 255 },
				color_helicopter{ 255, 255, 255 }, color_ores{ 255, 255, 255 },
				color_corpse{ 255, 255, 255 }, color_ore_collectibles{ 255, 255, 255 }, color_food_collectibles{ 255, 255, 255 },
				color_loot_containers{ 255, 255, 255 }, color_barrels{ 255, 255, 255 }, color_cars{ 255, 255, 255 };

			inline color_t color_sulfur_ore{ 255, 255, 255 },
				color_metal_ore{ 255, 255, 255 },
				color_stone_ore{ 255, 255, 255 },
				color_tool_cupboard{ 255, 255, 255 },
				color_box_storages{ 255, 255, 255 };

			inline bool show_patrol_helicopter{ }, show_attack_helicopter{ }, show_chinook_helicopter{ };
			inline color_t color_patrol_helicopter{ 255, 255, 255 }, color_attack_helicopter{ 255, 255, 255 }, color_chinook_helicopter{ 255, 255, 255 };

			inline color_t color_ammo_nails_arrows{ 255, 255, 255 };

			inline color_t color_supply_signals{ 255, 255, 255 }, color_supply_drops{ 255, 255, 255 };

			inline color_t color_oil_barrel{ 255, 255, 255 },
				color_regular_barrels{ 255, 255, 255 },
				color_underwater_crate{ 255, 255, 255 },
				color_elite_crate{ 255, 255, 255 }, color_military_crate{ 255, 255, 255 }, color_bradley_crate{ 255, 255, 255 },
				color_food_crate{ 255, 255, 255 }, color_medical_crate{ 255, 255, 255 }, color_diesel_fuel{ 255, 255, 255 }, color_helicopter_crate{ 255, 255, 255 }, color_hackable_locked_crate{ 255, 255, 255 },
				color_normal_crate{ 255, 255, 255 }, color_chickens{ 255, 255, 255 }, color_small_crate{ 255, 255, 255 }, color_mine_crate{ 255, 255, 255 },
				color_tool_box{ 255, 255, 255 },
				color_boars{ 255, 255, 255 }, color_wolves{ 255, 255, 255 }, color_horses{ 255, 255, 255 },
				color_sharks{ 255, 255, 255 }, color_deers{ 255, 255, 255 }, color_polar_bears{ 255, 255, 255 },
				color_bears{ 255, 255, 255 }, color_sulfur_collectibles{ 255, 255, 255 },
				color_metal_collectibles{ 255, 255, 255 }, color_wood_collectibles{ 255, 255, 255 }, 
				color_vending_machine{ 255, 255, 255 }, color_drone{ 255, 255, 255 }, color_recycler{ 255, 255, 255 },
				color_stone_collectibles{ 255, 255, 255 };

			inline color_t color_hemp{ 255, 255, 255 }, color_mushroom{ 255, 255, 255 }, color_pumpkin{ 255, 255, 255 },
				color_berrys{ 255, 255, 255 }, color_corns{ 255, 255, 255 }, color_potatos{ 255, 255, 255 };

			inline color_t color_modular_car{ 255, 255, 255 }, color_two_modules_car{ 255, 255, 255 }, 
				color_minicopter{ 255, 255, 255 }, color_scrap_helicopter{ 255, 255, 255 }, color_rhib{ 255, 255, 255 }, color_bradley_apc{ 255, 255, 255 },
				color_kayak{ 255, 255, 255 }, color_small_motorboat{ 255, 255, 255 }, color_solo_submarine{ 255, 255, 255 }, color_duo_submarine{ 255, 255, 255 };

			inline color_t color_landmines{ 255, 255, 255 }, color_npc_turrets{ 255, 255, 255 }, color_auto_turrets{ 255, 255, 255 }, color_shotgun_traps{ 255, 255, 255 },
				color_tesla_coil{ 255, 255, 255 }, color_flame_turrets{ 255, 255, 255 }, color_sam_site{ 255, 255, 255 },
				color_land_spikes{ 255, 255, 255 }, color_bear_trap{ 255, 255, 255 };

			inline color_t ambient_color{ 255, 255, 255 }, sky_color{ 255, 255, 255 };
		}

		inline color_t name_color{ 255, 255, 255 }, box_color{ 255, 255, 255 },
			skeleton_color{ 255, 255, 255 }, radar_color{ },
			oof_color{ 255, 255, 255 }, snap_lines_color{ 255, 255, 255 }, distance_color{ 255, 255, 255 }, weapon_color{ 255, 255, 255 },
			view_direction_color{ 255, 255, 255 }, knocked_color{ 0, 255, 0 }, ducking_color{ 255, 0, 0 }, 
			custom_health_color{ 255, 255, 255 }, health_text_color{ 255, 255, 255 };

		inline color_t vis_name_color{ 255, 255, 255 }, vis_box_color{ 255, 255, 255 },
			vis_skeleton_color{ 255, 255, 255 }, vis_radar_color{ },
			vis_oof_color{ 255, 255, 255 }, vis_snap_lines_color{ 255, 255, 255 }, vis_distance_color{ 255, 255, 255 }, vis_weapon_color{ 255, 255, 255 },
			vis_view_direction_color{ 255, 255, 255 }, vis_knocked_color{ 0, 255, 0 }, vis_ducking_color{ 255, 0, 0 },
			vis_custom_health_color{ 255, 255, 255 }, vis_health_text_color{ 255, 255, 255 };

		inline color_t npc_name_color{ 255, 255, 255 }, npc_box_color{ 255, 255, 255 },
			npc_skeleton_color{ 255, 255, 255 }, npc_radar_color{ },
			npc_oof_color{ 255, 255, 255 }, npc_snap_lines_color{ 255, 255, 255 }, npc_distance_color{ 255, 255, 255 }, npc_weapon_color{ 255, 255, 255 },
			npc_view_direction_color{ 255, 255, 255 }, npc_knocked_color{ 0, 255, 0 }, npc_ducking_color{ 255, 0, 0 },
			npc_custom_health_color{ 255, 255, 255 }, npc_health_text_color{ 255, 255, 255 };

		inline color_t npc_vis_name_color{ 255, 255, 255 }, npc_vis_box_color{ 255, 255, 255 },
			npc_vis_skeleton_color{ 255, 255, 255 }, npc_vis_radar_color{ },
			npc_vis_oof_color{ 255, 255, 255 }, npc_vis_snap_lines_color{ 255, 255, 255 }, npc_vis_distance_color{ 255, 255, 255 }, npc_vis_weapon_color{ 255, 255, 255 },
			npc_vis_view_direction_color{ 255, 255, 255 }, npc_vis_knocked_color{ 0, 255, 0 }, npc_vis_ducking_color{ 255, 0, 0 },
			npc_vis_custom_health_color{ 255, 255, 255 }, npc_vis_health_text_color{ 255, 255, 255 };

		inline color_t chams_color{ 131, 171, 235 }, chams_visible{ 214, 224, 255 }, pos_color{ 255, 255, 255 };
	}

	namespace aimbot {
		inline bool aim_check{ },
			smoothness{ true }, auto_fire{ }, should_simulate_movement{ true },
			draw_fov{ }, draw_crosshair{ }, draw_target{ },
			aim_sleepers{ }, aim_npc{ true }, aim_helicopter{ }, aim_knocked{ },
			manipulation{ }, kill_aura{ }, auto_reload{ },
			aim_nearest_bone{ true };

		inline color_t fov_circle_color{ 255, 255, 255 }, target_line_color{ 255, 0, 0 };

		inline int aim_bone{ }, manipulation_key{ 1 }, aim_type{ 2 }, smooth_type{ },
			max_target_distance{ 750 }, fov_amount{ 150 };

		inline float smoothness_amount{ 2.f };

		namespace exploits {
			inline bool force_on_phone{ };
			namespace movement {
				inline bool infinite_jump{ }, stopper_fly{ },
					climb_assist{ }, fly_hack{ }, omni_sprint{ }, silent_walk{ },
					high_jump{ }, walk_on_water{ }, always_sprint{ }, walk_through_trees{ },
					walk_through_players{ }, disable_slow_down_melee{ }, modify_clothing_speed{ },
					increase_height{ };

				inline int fly_key{ 102 }, silent_walk_key{ 304 }, 
					ignore_key{ 118 }, omni_sprint_key{ 304 }, 
					increase_height_key{ 120 };

				inline int fly_speed{ 415 };

				inline float clothing_speed{ };

				inline float jump_height{ }, omni_sprint_speed{ }, height_amount{ };
			}
			namespace combat {
				inline bool automatic_weapons{ }, semi_automatic_weapons{ }, burst_weapons{ }, unlock_aim_on_jugger{ }, aim_bolt_cycle{ },
					extended_melee{ }, no_spread{ }, no_sway{ }, modify_eoka_chance{ },
					no_recoil{ }, modify_can_attack{ }, can_attack_in_vehicles{ }, unlock_view_angles{ },
					big_bullets{ }, quick_bullets{ }, pierce{ }, spoof_hit_distance{ }, no_shot_gun_spread{ }, head_teleportation{ };

				inline float reduce_recoil{ 100.f }, reduce_spread{ 100.f }, bullet_distance{ },
					eoka_chance{ }, attack_radius{ },
					bullet_size{ };

				inline int teleport_key{ 116 };
				inline int bullet_speed{ 50 };
			}
			namespace time {
				inline bool fast_heal{ }, fast_switch{ }, time_modifier{ },
					rapid_fire{ }, instant_charge_compound{ }, fake_lag{ }, fake_lag_on{ },
					instant_revive{ }, fast_bow{ }, always_revive_target{ }, fast_loot{ };

				inline float fake_lag_amount{ }, time_speed{ }, rapid_fire_speed{ };
				inline int fake_lag_key{ 102 }, revive_key{ 101 };
			}
			namespace misc {
				inline bool keep_wounded_alive{ }, always_hit_weak_spot{ }, long_neck{ },
					long_neck_right{ }, long_neck_left{ }, disable_land_damage{ },
					fov_changer{ }, zoom_fov{ true }, suicide{ }, fake_fire{ }, 
					fake_admin{ }, fake_fire_on{ }, debug_camera{ }, spin_bot{ }, gesture_spam{ }, interactive_debug{ },
					disarm_landmines{ }, stop_recycler{ }, use_max_view{ }, auto_pickup{ }, auto_grade{ }, auto_pickup_items{ }, 
					pickup_everything{ }, no_viewmodel_bob{ }, auto_codelock{ }, always_grade{ }, always_codelock{ },
					always_pickup{ }, auto_untie_crates{ }, auto_farm_ores{ }, auto_farm_trees{ }, auto_farm_only_hotspot{ }, 
					auto_farm_barrels{ }, no_lower{ }, no_flash{ };

				inline float long_neck_height{ 150.f }, long_neck_right_amount{ 150.f }, 
					long_neck_left_amount{ 150.f }, delay_fake_fire{ }, 
					max_grade_distance{ 5.f }, max_lock_distance{ 5.f }, max_item_distance{ 3.f }, max_collectible_distance{ 3.f };

				inline int zoom_fov_amount{ 10 }, fov_amount{ 90 }, gesture_type{ }, grade_tier{ }, code_lock_code{ }, codelock_key{ }, pickup_key{ }, grade_key{ };

				inline int view_left{ 41 }, view_right{ 42 },
					view_height{ 42 }, zoom_key{ 41 }, fake_fire_key{ 41 },
					debug_camera_key{ 3 }, suicide_key{ 7 };
			}
		}
	}
}
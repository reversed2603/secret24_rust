#include "menu_tabs.h"
#include "framework/gui_framework.h"
#include "../options.h"
#include "../aimbot/aimbot.h"

// create global definition of menu class.
c_menu g_menu;

void c_menu::draw_menu_tab( ) {
	g_framework.create_check_box( xs( "rainbow accent" ), &options::rainbow_accent, 1 );
	g_framework.color_picker( xs( "menu accent color" ), &options::accent_color, 1 );

	g_framework.create_label( xs( "quick config" ), 1 );
	g_framework.create_combo_box( cfg_vector, &options::cfg_index, 1 );
	g_framework.create_check_box( xs( "load" ), &options::load_cfg, 1 );
	g_framework.create_check_box( xs( "save" ), &options::save_cfg, 1 );

	g_framework.create_label( xs( "esp font flags" ), 1 );
	g_framework.create_combo_box( font_flags, &options::font_flags, 1 );
				
	g_framework.create_label( xs( "local indicators" ), 2 );
	g_framework.create_check_box( xs( "indicators" ), &options::visuals::indicators, 2 );
	if( options::visuals::indicators )
		g_framework.create_check_box( xs( "fly hack indicator" ), &options::visuals::fly_hack_indicator, 2 );

	g_framework.create_check_box( xs( "draw hit bullet tracers" ), &options::visuals::draw_tracers, 2 );
	g_framework.color_picker( xs( "hit tracers color" ), &options::visuals::tracers_color, 2 );
	g_framework.create_check_box( xs( "draw local trails" ), &options::visuals::local_trails, 2 );
	g_framework.color_picker( xs( "trails color" ), &options::visuals::trails_color, 2 );
	g_framework.create_check_box( xs( "draw desync bar" ), &options::visuals::show_desync_bar, 2 );
	g_framework.color_picker( xs( "desync bar color" ), &options::visuals::desync_bar_color, 2 );
	g_framework.create_check_box( xs( "draw reload bar" ), &options::visuals::show_reload_bar, 2 );
	g_framework.color_picker( xs( "reload bar color" ), &options::visuals::reload_bar_color, 2 );

	g_framework.create_label( xs( "location manager" ), 2 );
	g_framework.create_hotkey( xs( "remove last position" ), &options::visuals::remove_positions_key, 2 );
	g_framework.create_hotkey( xs( "save pos key" ), &options::visuals::save_pos_key, 2 );
	g_framework.create_check_box( xs( "is home position" ), &options::visuals::is_home_pos, 2 );
	g_framework.color_picker( xs( "position color" ), &options::visuals::pos_color, 2 );
}

void c_menu::draw_aimbot_tab( ) {
	g_framework.create_combo_box( aim_mode, &options::aimbot::aim_type, 1 );

	g_framework.create_check_box( xs( "manipulator" ), &options::aimbot::manipulation, 1 );
	g_framework.create_hotkey( xs( "manipulator key" ), &options::aimbot::manipulation_key, 1 );
	//g_framework.create_check_box( xs( "auto reload" ), &options::aimbot::auto_reload, 1 );
	g_framework.create_check_box( xs( "simulate player movement" ), &options::aimbot::should_simulate_movement, 1 );

	g_framework.create_check_box( xs( "aim at nearest bone" ), &options::aimbot::aim_nearest_bone, 1 );
	if( !options::aimbot::aim_nearest_bone )
		g_framework.create_combo_box( bones, &options::aimbot::aim_bone, 1 );

	g_framework.create_hotkey( xs( "aim key" ), &g_aimbot.aim_key, 1 );
				
	g_framework.create_check_box( xs( "draw field of view circle" ), &options::aimbot::draw_fov, 1 );
	g_framework.color_picker( xs( "fov circle color" ), &options::aimbot::fov_circle_color, 1 );

	g_framework.slider_int( xs( "field of view" ), &options::aimbot::fov_amount, 0, 1000, 1 );

	g_framework.create_label( xs( "smooth type" ), 1 );
	g_framework.create_combo_box( smooth_type, &options::aimbot::smooth_type, 1 );
	g_framework.slider_float( xs( "smoothness amount" ), &options::aimbot::smoothness_amount, 0.0f, 10.f, 1 );

	g_framework.create_check_box( xs( "draw line to target" ), &options::aimbot::draw_target, 1 );
	g_framework.color_picker( xs( "line color" ), &options::aimbot::target_line_color, 1 );

	g_framework.create_check_box( xs( "aim at knocked" ), &options::aimbot::aim_knocked, 1 );
	g_framework.create_check_box( xs( "aim at sleepers" ), &options::aimbot::aim_sleepers, 1 );
	g_framework.create_check_box( xs( "aim at npc" ), &options::aimbot::aim_npc, 1 );
	g_framework.create_check_box( xs( "aim at helicopter" ), &options::aimbot::aim_helicopter, 1 );
	g_framework.create_check_box( xs( "only aim at visible" ), &options::aimbot::aim_check, 1 );

	g_framework.create_check_box( xs( "draw crosshair" ), &options::aimbot::draw_crosshair, 1 );
	g_framework.create_check_box( xs( "killaura" ), &options::aimbot::kill_aura, 1 );

	g_framework.slider_int( xs( "target max distance" ), &options::aimbot::max_target_distance, 0, options::visuals::max_player_distance, 2 );
}

void c_menu::draw_visuals_tab( ) {
	g_framework.create_check_box( xs( "master-switch" ), &options::visuals::draw_visuals, 1 );
	g_framework.create_combo_box( color_list, &options::color_tab, 1 );
	if( options::visuals::draw_visuals ) {
		g_framework.create_check_box( xs( "name" ), &options::visuals::show_name, 1 );
		switch( options::color_tab ) {
		case invisible:
			g_framework.color_picker( xs( "name color" ), &options::visuals::name_color, 1 );
			break;
		case visible:
			g_framework.color_picker( xs( "name color" ), &options::visuals::vis_name_color, 1 );
			break;
		case npc_invisible:
			g_framework.color_picker( xs( "name color" ), &options::visuals::npc_name_color, 1 );
			break;
		case npc_visible:
			g_framework.color_picker( xs( "name color" ), &options::visuals::npc_vis_name_color, 1 );
			break;
		}

		g_framework.create_check_box( xs( "radar" ), &options::visuals::draw_radar, 1 );
		switch( options::color_tab ) {
		case invisible:
			g_framework.color_picker( xs( "radar color" ), &options::visuals::radar_color, 1 );
			break;
		case visible:
			g_framework.color_picker( xs( "radar color" ), &options::visuals::vis_radar_color, 1 );
			break;
		case npc_invisible:
			g_framework.color_picker( xs( "radar color" ), &options::visuals::npc_radar_color, 1 );
			break;
		case npc_visible:
			g_framework.color_picker( xs( "radar color" ), &options::visuals::npc_vis_radar_color, 1 );
			break;
		}

		g_framework.create_combo_box( box_esp_mode, &options::visuals::box_type, 1 );
		switch( options::color_tab ) {
		case invisible:
			g_framework.color_picker( xs( "box color" ), &options::visuals::box_color, 1 );
			break;
		case visible:
			g_framework.color_picker( xs( "box color" ), &options::visuals::vis_box_color, 1 );
			break;
		case npc_invisible:
			g_framework.color_picker( xs( "box color" ), &options::visuals::npc_box_color, 1 );
			break;
		case npc_visible:
			g_framework.color_picker( xs( "box color" ), &options::visuals::npc_vis_box_color, 1 );
			break;
		}

		g_framework.create_check_box( xs( "health" ), &options::visuals::show_health, 1 );
		if( options::visuals::show_health ) {
			g_framework.slider_int( xs( "health thickness" ), &options::visuals::health_thickness, 1, 3, 1 );
			g_framework.create_check_box( xs( "custom health color" ), &options::visuals::modify_health_color, 1 );
			if( options::visuals::modify_health_color ) {
				switch( options::color_tab ) {
				case invisible:
					g_framework.color_picker( xs( "health color" ), &options::visuals::custom_health_color, 1 );
					break;
				case visible:
					g_framework.color_picker( xs( "health color" ), &options::visuals::vis_custom_health_color, 1 );
					break;
				case npc_invisible:
					g_framework.color_picker( xs( "health color" ), &options::visuals::npc_custom_health_color, 1 );
					break;
				case npc_visible:
					g_framework.color_picker( xs( "health color" ), &options::visuals::npc_vis_custom_health_color, 1 );
					break;
				}
			}
		}
		g_framework.create_check_box( xs( "health text" ), &options::visuals::show_health_text, 1 );
		switch( options::color_tab ) {
		case invisible:
			g_framework.color_picker( xs( "health text color" ), &options::visuals::health_text_color, 1 );
			break;
		case visible:
			g_framework.color_picker( xs( "health text color" ), &options::visuals::vis_health_text_color, 1 );
			break;
		case npc_invisible:
			g_framework.color_picker( xs( "health text color" ), &options::visuals::npc_health_text_color, 1 );
			break;
		case npc_visible:
			g_framework.color_picker( xs( "health text color" ), &options::visuals::npc_vis_health_text_color, 1 );
			break;
		}

		g_framework.create_check_box( xs( "skeleton" ), &options::visuals::draw_bones, 1 );
		switch( options::color_tab ) {
		case invisible:
			g_framework.color_picker( xs( "skeleton color" ), &options::visuals::skeleton_color, 1 );
			break;
		case visible:
			g_framework.color_picker( xs( "skeleton color" ), &options::visuals::vis_skeleton_color, 1 );
			break;
		case npc_invisible:
			g_framework.color_picker( xs( "skeleton color" ), &options::visuals::npc_skeleton_color, 1 );
			break;
		case npc_visible:
			g_framework.color_picker( xs( "skeleton color" ), &options::visuals::npc_vis_skeleton_color, 1 );
			break;
		}

		g_framework.create_check_box( xs( "weapon" ), &options::visuals::show_weapon, 1 );
		switch( options::color_tab ) {
		case invisible:
			g_framework.color_picker( xs( "weapon color" ), &options::visuals::weapon_color, 1 );
			break;
		case visible:
			g_framework.color_picker( xs( "weapon color" ), &options::visuals::vis_weapon_color, 1 );
			break;
		case npc_invisible:
			g_framework.color_picker( xs( "weapon color" ), &options::visuals::npc_weapon_color, 1 );
			break;
		case npc_visible:
			g_framework.color_picker( xs( "weapon color" ), &options::visuals::npc_vis_weapon_color, 1 );
			break;
		}

		g_framework.create_check_box( xs( "distance" ), &options::visuals::show_distance, 1 );
		switch( options::color_tab ) {
		case invisible:
			g_framework.color_picker( xs( "distance color" ), &options::visuals::distance_color, 1 );
			break;
		case visible:
			g_framework.color_picker( xs( "distance color" ), &options::visuals::vis_distance_color, 1 );
			break;
		case npc_invisible:
			g_framework.color_picker( xs( "distance color" ), &options::visuals::npc_distance_color, 1 );
			break;
		case npc_visible:
			g_framework.color_picker( xs( "distance color" ), &options::visuals::npc_vis_distance_color, 1 );
			break;
		}

		g_framework.create_check_box( xs( "snap-lines" ), &options::visuals::show_lines, 1 );
		switch( options::color_tab ) {
		case invisible:
			g_framework.color_picker( xs( "lines color" ), &options::visuals::snap_lines_color, 1 );
			break;
		case visible:
			g_framework.color_picker( xs( "lines color" ), &options::visuals::vis_snap_lines_color, 1 );
			break;
		case npc_invisible:
			g_framework.color_picker( xs( "lines color" ), &options::visuals::npc_snap_lines_color, 1 );
			break;
		case npc_visible:
			g_framework.color_picker( xs( "lines color" ), &options::visuals::npc_vis_snap_lines_color, 1 );
			break;
		}

		g_framework.create_check_box( xs( "show view direction" ), &options::visuals::show_view_direction, 1 );
		switch( options::color_tab ) {
		case invisible:
			g_framework.color_picker( xs( "view direction color" ), &options::visuals::view_direction_color, 1 );
			break;
		case visible:
			g_framework.color_picker( xs( "view direction color" ), &options::visuals::vis_view_direction_color, 1 );
			break;
		case npc_invisible:
			g_framework.color_picker( xs( "view direction color" ), &options::visuals::npc_view_direction_color, 1 );
			break;
		case npc_visible:
			g_framework.color_picker( xs( "view direction color" ), &options::visuals::npc_vis_view_direction_color, 1 );
			break;
		}

		g_framework.create_check_box( xs( "offscreen arrows" ), &options::visuals::offscreen_arrows, 1 );
		switch( options::color_tab ) {
		case invisible:
			g_framework.color_picker( xs( "oof color" ), &options::visuals::oof_color, 1 );
			break;
		case visible:
			g_framework.color_picker( xs( "oof color" ), &options::visuals::vis_oof_color, 1 );
			break;
		case npc_invisible:
			g_framework.color_picker( xs( "oof color" ), &options::visuals::npc_oof_color, 1 );
			break;
		case npc_visible:
			g_framework.color_picker( xs( "oof color" ), &options::visuals::npc_vis_oof_color, 1 );
			break;
		}

		g_framework.create_check_box( xs( "chams" ), &options::visuals::chams, 1 );
		if( options::visuals::chams )
			g_framework.create_check_box( xs( "rgb chams" ), &options::visuals::rgb_chams, 1 );

		g_framework.create_combo_box( chams_vector, &options::visuals::chams_type, 1 );
					
		g_framework.create_label( xs( "states" ), 2 );
		g_framework.create_check_box( xs( "show sleepers" ), &options::visuals::can_show_sleepers, 2 );
		g_framework.create_check_box( xs( "show knocked" ), &options::visuals::can_show_knocked, 2 );
		g_framework.create_check_box( xs( "show npc" ), &options::visuals::can_show_npc, 2 );
		if( options::visuals::offscreen_arrows ) {
			g_framework.create_check_box( xs( "show sleepers oof" ), &options::visuals::can_show_sleepers_oof, 2 );
			g_framework.create_check_box( xs( "show knocked oof" ), &options::visuals::can_show_knocked_oof, 2 );
			g_framework.create_check_box( xs( "show npc oof" ), &options::visuals::can_show_npc_oof, 2 );
		}

		g_framework.create_label( xs( "flags" ), 2 );
		g_framework.create_check_box( xs( "in duck" ), &options::visuals::show_ducking_flag, 2 );
		switch( options::color_tab ) {
		case invisible:
			g_framework.color_picker( xs( "ducking color" ), &options::visuals::ducking_color, 2 );
			break;
		case visible:
			g_framework.color_picker( xs( "ducking color" ), &options::visuals::vis_ducking_color, 2 );
			break;
		case npc_invisible:
			g_framework.color_picker( xs( "ducking color" ), &options::visuals::npc_ducking_color, 2 );
			break;
		case npc_visible:
			g_framework.color_picker( xs( "ducking color" ), &options::visuals::npc_vis_ducking_color, 2 );
			break;
		}

		g_framework.create_check_box( xs( "is knocked" ), &options::visuals::show_knocked_flag, 2 );
		switch( options::color_tab ) {
		case invisible:
			g_framework.color_picker( xs( "knocked color" ), &options::visuals::knocked_color, 2 );
			break;
		case visible:
			g_framework.color_picker( xs( "knocked color" ), &options::visuals::vis_knocked_color, 2 );
			break;
		case npc_invisible:
			g_framework.color_picker( xs( "knocked color" ), &options::visuals::npc_knocked_color, 2 );
			break;
		case npc_visible:
			g_framework.color_picker( xs( "knocked color" ), &options::visuals::npc_vis_knocked_color, 2 );
			break;
		}

		g_framework.create_label( xs( "information" ), 2 );
		g_framework.create_check_box( xs( "show hot-bar" ), &options::visuals::show_hotbar, 2 );
		g_framework.create_check_box( xs( "show clothes" ), &options::visuals::show_clothes, 2 );

		g_framework.slider_int( xs( "player max distance" ), &options::visuals::max_player_distance, 0, max_distance, 2 );

		if( !options::visuals::rgb_chams ) {
			if( options::visuals::chams_type != 3 ) {
				bool one_color = options::visuals::chams_type == 6 || options::visuals::chams_type == 5;
				if( options::color_tab == invisible
					|| one_color )
					g_framework.color_picker( xs( "chams color" ), &options::visuals::chams_color, 1 );
				else
					g_framework.color_picker( xs( "chams color" ), &options::visuals::chams_visible, 1 );
			}
		}
	}
}

void c_menu::draw_worlds_tab( ) {
	g_framework.create_check_box( xs( "master-switch" ), &options::visuals::world::master_switch, 1 );

	if( options::visuals::world::master_switch ) {
		g_framework.create_check_box( xs( "show distance" ), &options::visuals::world::show_distance, 1 );
		g_framework.create_check_box( xs( "show health" ), &options::visuals::world::show_health, 1 );
		g_framework.create_check_box( xs( "show amount of items" ), &options::visuals::world::show_item_amount, 1 );

		g_framework.create_check_box( xs( "prefab name debug" ), &options::visuals::prefab_name_debug, 1 );
		g_framework.create_check_box( xs( "class name debug" ), &options::visuals::class_name_debug, 1 );

		// tab selection.
		g_framework.create_combo_box( tab_choice, &options::tab_selection, 1 );
		if( options::tab_selection == 0 ) {
			// first tab additionals.
			g_framework.create_combo_box( tab_list, &options::first_tab, 1 );

			if( options::first_tab == 1 ) {
				g_framework.create_label( xs( "additional" ), 1, true );
				g_framework.create_check_box( xs( "show grenades" ), &options::visuals::world::show_grenades, 1 );
				g_framework.create_check_box( xs( "player corpse" ), &options::visuals::world::show_corpse, 1 );
				g_framework.create_check_box( xs( "backpack" ), &options::visuals::world::show_backpack, 1 );

				g_framework.create_label( xs( "loot containers" ), 1, true );
				g_framework.create_check_box( xs( "mine crate" ), &options::visuals::world::show_mine_crate, 1 );
				g_framework.create_check_box( xs( "small loot crate" ), &options::visuals::world::show_small_crate, 1 );
				g_framework.create_check_box( xs( "tool box" ), &options::visuals::world::show_tool_box, 1 );
				g_framework.create_check_box( xs( "underwater crate" ), &options::visuals::world::show_underwater_crate, 1 );
				g_framework.create_check_box( xs( "elite crate" ), &options::visuals::world::show_elite_crate, 1 );
				g_framework.create_check_box( xs( "military crate" ), &options::visuals::world::show_military_crate, 1 );
				g_framework.create_check_box( xs( "food crate" ), &options::visuals::world::show_food_crate, 1 );
				g_framework.create_check_box( xs( "medical crate" ), &options::visuals::world::show_medical_crate, 1 );
				g_framework.create_check_box( xs( "normal crate" ), &options::visuals::world::show_normal_crate, 1 );
				g_framework.create_check_box( xs( "helicopter crate" ), &options::visuals::world::show_helicopter_crate, 1 );
				g_framework.create_check_box( xs( "bradley crate" ), &options::visuals::world::show_bradley_crate, 1 );
				g_framework.create_check_box( xs( "supply drop crate" ), &options::visuals::world::show_supply_drops, 1 );
				g_framework.create_check_box( xs( "supply signals" ), &options::visuals::world::show_supply_signals, 1 );
				g_framework.create_check_box( xs( "hackable locked crate" ), &options::visuals::world::show_hackable_locked_crate, 1 );
				g_framework.create_check_box( xs( "stashes" ), &options::visuals::world::show_stashes, 1 );

				g_framework.create_label( xs( "traps" ), 1, true );
				g_framework.create_check_box( xs( "landmine" ), &options::visuals::world::show_landmines, 1 );
				g_framework.create_check_box( xs( "npc turrets" ), &options::visuals::world::show_npc_turrets, 1 );
				g_framework.create_check_box( xs( "auto-turrets" ), &options::visuals::world::show_auto_turrets, 1 );
				g_framework.create_check_box( xs( "shotgun trap" ), &options::visuals::world::show_shotgun_traps, 1 );
				g_framework.create_check_box( xs( "tesla coil" ), &options::visuals::world::show_tesla_coil, 1 );
				g_framework.create_check_box( xs( "flame turret" ), &options::visuals::world::show_flame_turrets, 1 );
				g_framework.create_check_box( xs( "sam-site" ), &options::visuals::world::show_sam_site, 1 );
				g_framework.create_check_box( xs( "land spikes" ), &options::visuals::world::show_land_spikes, 1 );
				g_framework.create_check_box( xs( "bear trap" ), &options::visuals::world::show_bear_trap, 1 );
			}
			else {
				g_framework.create_label( xs( "items" ), 1, true );
				g_framework.create_check_box( xs( "weapons" ), &options::visuals::world::show_weapons, 1 );
				g_framework.create_check_box( xs( "melee weapons" ), &options::visuals::world::show_melee_weapons, 1 );
				g_framework.create_check_box( xs( "heal" ), &options::visuals::world::show_heal, 1 );
				g_framework.create_check_box( xs( "everything" ), &options::visuals::world::show_everything, 1 );
				g_framework.create_check_box( xs( "drone" ), &options::visuals::world::show_drone, 1 );
				g_framework.create_check_box( xs( "recycler" ), &options::visuals::world::show_recycler, 1 );
				g_framework.create_check_box( xs( "show nails and arrows" ), &options::visuals::world::show_ammo_nails_arrows, 1 );

				g_framework.create_label( xs( "ore collectibles" ), 1, true );
				g_framework.create_check_box( xs( "sulfur collectible" ), &options::visuals::world::show_sulfur_collectibles, 1 );
				g_framework.create_check_box( xs( "metal collectible" ), &options::visuals::world::show_metal_collectibles, 1 );
				g_framework.create_check_box( xs( "wood collectible" ), &options::visuals::world::show_wood_collectibles, 1 );
				g_framework.create_check_box( xs( "stone collectible" ), &options::visuals::world::show_stone_collectibles, 1 );

				g_framework.create_label( xs( "ores" ), 1, true );
				g_framework.create_check_box( xs( "sulfur ore" ), &options::visuals::world::show_sulfur_ore, 1 );
				g_framework.create_check_box( xs( "metal ore" ), &options::visuals::world::show_metal_ore, 1 );
				g_framework.create_check_box( xs( "stone ore" ), &options::visuals::world::show_stone_ore, 1 );

				g_framework.create_label( xs( "barrels" ), 1, true );
				g_framework.create_check_box( xs( "oil barrel" ), &options::visuals::world::show_oil_barrel, 1 );
				g_framework.create_check_box( xs( "regular barrels" ), &options::visuals::world::show_regular_barrels, 1 );
				g_framework.create_check_box( xs( "diesel barrels" ), &options::visuals::world::show_diesel_fuel, 1 );					

				g_framework.create_label( xs( "storages" ), 1, true );
				g_framework.create_check_box( xs( "tool cupboard" ), &options::visuals::world::show_tool_cupboard, 1 );
				g_framework.create_check_box( xs( "box storages" ), &options::visuals::world::show_box_storages, 1 );
				g_framework.create_check_box( xs( "vending machines" ), &options::visuals::world::show_vending_machine, 1 );
			}

			g_framework.create_label( xs( "food" ), 2, true );
			g_framework.create_check_box( xs( "hemp" ), &options::visuals::world::show_hemp, 2 );
			g_framework.create_check_box( xs( "mushroom" ), &options::visuals::world::show_mushroom, 2 );
			g_framework.create_check_box( xs( "pumpkin" ), &options::visuals::world::show_pumpkin, 2 );
			g_framework.create_check_box( xs( "corn" ), &options::visuals::world::show_corns, 2 );
			g_framework.create_check_box( xs( "berry" ), &options::visuals::world::show_berrys, 2 );
			g_framework.create_check_box( xs( "potato" ), &options::visuals::world::show_potatos, 2 );

			g_framework.create_label( xs( "animals" ), 2, true );
			g_framework.create_check_box( xs( "chicken" ), &options::visuals::world::show_chickens, 2 );
			g_framework.create_check_box( xs( "boars" ), &options::visuals::world::show_boars, 2 );
			g_framework.create_check_box( xs( "wolves" ), &options::visuals::world::show_wolves, 2 );
			g_framework.create_check_box( xs( "deer" ), &options::visuals::world::show_deers, 2 );
			g_framework.create_check_box( xs( "polar bear" ), &options::visuals::world::show_polar_bears, 2 );
			g_framework.create_check_box( xs( "bear" ), &options::visuals::world::show_bears, 2 );
			g_framework.create_check_box( xs( "sharks" ), &options::visuals::world::show_sharks, 2 );
			g_framework.create_check_box( xs( "horses" ), &options::visuals::world::show_horses, 2 );

			g_framework.create_label( xs( "vehicles" ), 2, true );
			g_framework.create_check_box( xs( "mini-copter" ), &options::visuals::world::show_minicopter, 2 );
			g_framework.create_check_box( xs( "scrap helicopter" ), &options::visuals::world::show_scrap_helicopter, 2 );
			g_framework.create_check_box( xs( "rhib" ), &options::visuals::world::show_rhib, 2 );
			g_framework.create_check_box( xs( "kayak" ), &options::visuals::world::show_kayak, 2 );
			g_framework.create_check_box( xs( "small motorboat" ), &options::visuals::world::show_small_motorboat, 2 );
			g_framework.create_check_box( xs( "solo submarine" ), &options::visuals::world::show_solo_submarine, 2 );
			g_framework.create_check_box( xs( "duo submarine" ), &options::visuals::world::show_duo_submarine, 2 );
			g_framework.create_check_box( xs( "bradley tank" ), &options::visuals::world::show_bradley_apc, 2 );

			g_framework.create_label( xs( "helicopters" ), 2, true );
			g_framework.create_check_box( xs( "attack helicopter" ), &options::visuals::world::show_attack_helicopter, 2 );
			g_framework.create_check_box( xs( "chinook helicopter" ), &options::visuals::world::show_chinook_helicopter, 2 );
			g_framework.create_check_box( xs( "patrol helicopter" ), &options::visuals::world::show_patrol_helicopter, 2 );

			g_framework.create_label( xs( "cars" ), 2, true );
			g_framework.create_check_box( xs( "modular car" ), &options::visuals::world::show_modular_car, 2 );
			g_framework.create_check_box( xs( "2 module car" ), &options::visuals::world::show_two_modules_car, 2 );
		}
		else if( options::tab_selection == 1 ) {
			// first tab additionals.
			g_framework.create_combo_box( tab_list, &options::first_tab, 1 );

			if( options::first_tab == 1 ) {
				g_framework.color_picker( xs( "player corpse" ), &options::visuals::world::color_corpse, 1 );
				g_framework.color_picker( xs( "backpack" ), &options::visuals::world::color_backpack, 1 );
				
				g_framework.create_label( xs( "loot containers" ), 1, true );

				g_framework.color_picker( xs( "mine crate" ), &options::visuals::world::color_mine_crate, 1 );
				g_framework.color_picker( xs( "small loot crate" ), &options::visuals::world::color_small_crate, 1 );
				g_framework.color_picker( xs( "tool box" ), &options::visuals::world::color_tool_box, 1 );
				g_framework.color_picker( xs( "underwater crate" ), &options::visuals::world::color_underwater_crate, 1 );
				g_framework.color_picker( xs( "elite crate" ), &options::visuals::world::color_elite_crate, 1 );
				g_framework.color_picker( xs( "military crate" ), &options::visuals::world::color_military_crate, 1 );
				g_framework.color_picker( xs( "food crate" ), &options::visuals::world::color_food_crate, 1 );
				g_framework.color_picker( xs( "medical crate" ), &options::visuals::world::color_medical_crate, 1 );
				g_framework.color_picker( xs( "normal crate" ), &options::visuals::world::color_normal_crate, 1 );
				g_framework.color_picker( xs( "helicopter crate" ), &options::visuals::world::color_helicopter_crate, 1 );
				g_framework.color_picker( xs( "bradley crate" ), &options::visuals::world::color_bradley_crate, 1 );
				g_framework.color_picker( xs( "supply drop crate" ), &options::visuals::world::color_supply_drops, 1 );
				g_framework.color_picker( xs( "supply signals" ), &options::visuals::world::color_supply_signals, 1 );
				g_framework.color_picker( xs( "hackable locked crate" ), &options::visuals::world::color_hackable_locked_crate, 1 );

				g_framework.create_label( xs( "traps" ), 1, true );
				g_framework.color_picker( xs( "landmine" ), &options::visuals::world::color_landmines, 1 );
				g_framework.color_picker( xs( "npc turrets" ), &options::visuals::world::color_npc_turrets, 1 );
				g_framework.color_picker( xs( "auto-turrets" ), &options::visuals::world::color_auto_turrets, 1 );
				g_framework.color_picker( xs( "shotgun trap" ), &options::visuals::world::color_shotgun_traps, 1 );
				g_framework.color_picker( xs( "tesla coil" ), &options::visuals::world::color_tesla_coil, 1 );
				g_framework.color_picker( xs( "flame turret" ), &options::visuals::world::color_flame_turrets, 1 );
				g_framework.color_picker( xs( "sam-site" ), &options::visuals::world::color_sam_site, 1 );
				g_framework.color_picker( xs( "land spikes" ), &options::visuals::world::color_land_spikes, 1 );
				g_framework.color_picker( xs( "bear trap" ), &options::visuals::world::color_bear_trap, 1 );
			}
			else {
				g_framework.create_label( xs( "items" ), 1, true );
				g_framework.color_picker( xs( "weapons" ), &options::visuals::world::color_weapons, 1 );
				g_framework.color_picker( xs( "melee weapons" ), &options::visuals::world::color_melee_weapons, 1 );
				g_framework.color_picker( xs( "heal" ), &options::visuals::world::color_heal, 1 );
				g_framework.color_picker( xs( "everything" ), &options::visuals::world::color_everything, 1 );
				g_framework.color_picker( xs( "drone" ), &options::visuals::world::color_drone, 1 );
				g_framework.color_picker( xs( "recycler" ), &options::visuals::world::color_recycler, 1 );

				g_framework.create_label( xs( "ore collectibles" ), 1, true );
				g_framework.color_picker( xs( "sulfur collectible" ), &options::visuals::world::color_sulfur_collectibles, 1 );
				g_framework.color_picker( xs( "metal collectible" ), &options::visuals::world::color_metal_collectibles, 1 );
				g_framework.color_picker( xs( "wood collectible" ), &options::visuals::world::color_wood_collectibles, 1 );
				g_framework.color_picker( xs( "stone collectible" ), &options::visuals::world::color_stone_collectibles, 1 );

				g_framework.create_label( xs( "ores" ), 1, true );
				g_framework.color_picker( xs( "sulfur ore" ), &options::visuals::world::color_sulfur_ore, 1 );
				g_framework.color_picker( xs( "metal ore" ), &options::visuals::world::color_metal_ore, 1 );
				g_framework.color_picker( xs( "stone ore" ), &options::visuals::world::color_stone_ore, 1 );

				g_framework.create_label( xs( "barrels" ), 1, true );
				g_framework.color_picker( xs( "oil barrel" ), &options::visuals::world::color_oil_barrel, 1 );
				g_framework.color_picker( xs( "regular barrels" ), &options::visuals::world::color_regular_barrels, 1 );
				g_framework.color_picker( xs( "diesel barrels" ), &options::visuals::world::color_diesel_fuel, 1 );					

				g_framework.create_label( xs( "storages" ), 1, true );
				g_framework.color_picker( xs( "tool cupboard" ), &options::visuals::world::color_tool_cupboard, 1 );
				g_framework.color_picker( xs( "box storages" ), &options::visuals::world::color_box_storages, 1 );
				g_framework.color_picker( xs( "vending machines" ), &options::visuals::world::color_vending_machine, 1 );
			}

			g_framework.create_label( xs( "food" ), 2, true );
			g_framework.color_picker( xs( "hemp" ), &options::visuals::world::color_hemp, 2 );
			g_framework.color_picker( xs( "mushroom" ), &options::visuals::world::color_mushroom, 2 );
			g_framework.color_picker( xs( "pumpkin" ), &options::visuals::world::color_pumpkin, 2 );
			g_framework.color_picker( xs( "corn" ), &options::visuals::world::color_corns, 2 );
			g_framework.color_picker( xs( "berry" ), &options::visuals::world::color_berrys, 2 );
			g_framework.color_picker( xs( "potato" ), &options::visuals::world::color_potatos, 2 );

			g_framework.create_label( xs( "animals" ), 2, true );
			g_framework.color_picker( xs( "chicken" ), &options::visuals::world::color_chickens, 2 );
			g_framework.color_picker( xs( "boars" ), &options::visuals::world::color_boars, 2 );
			g_framework.color_picker( xs( "wolves" ), &options::visuals::world::color_wolves, 2 );
			g_framework.color_picker( xs( "deer" ), &options::visuals::world::color_deers, 2 );
			g_framework.color_picker( xs( "polar bear" ), &options::visuals::world::color_polar_bears, 2 );
			g_framework.color_picker( xs( "bear" ), &options::visuals::world::color_bears, 2 );
			g_framework.color_picker( xs( "sharks" ), &options::visuals::world::color_sharks, 2 );
			g_framework.color_picker( xs( "horses" ), &options::visuals::world::color_horses, 2 );

			g_framework.create_label( xs( "vehicles" ), 2, true );
			g_framework.color_picker( xs( "mini-copter" ), &options::visuals::world::color_minicopter, 2 );
			g_framework.color_picker( xs( "scrap helicopter" ), &options::visuals::world::color_scrap_helicopter, 2 );
			g_framework.color_picker( xs( "rhib" ), &options::visuals::world::color_rhib, 2 );
			g_framework.color_picker( xs( "kayak" ), &options::visuals::world::color_kayak, 2 );
			g_framework.color_picker( xs( "small motorboat" ), &options::visuals::world::color_small_motorboat, 2 );
			g_framework.color_picker( xs( "solo submarine" ), &options::visuals::world::color_solo_submarine, 2 );
			g_framework.color_picker( xs( "duo submarine" ), &options::visuals::world::color_duo_submarine, 2 );
			g_framework.color_picker( xs( "bradley tank" ), &options::visuals::world::color_bradley_apc, 2 );

			g_framework.create_label( xs( "helicopters" ), 2, true );
			g_framework.color_picker( xs( "attack helicopter" ), &options::visuals::world::color_attack_helicopter, 2 );
			g_framework.color_picker( xs( "chinook helicopter" ), &options::visuals::world::color_chinook_helicopter, 2 );
			g_framework.color_picker( xs( "patrol helicopter" ), &options::visuals::world::color_patrol_helicopter, 2 );

			g_framework.create_label( xs( "cars" ), 2, true );
			g_framework.color_picker( xs( "modular car" ), &options::visuals::world::color_modular_car, 2 );
			g_framework.color_picker( xs( "2 module car" ), &options::visuals::world::color_two_modules_car, 2 );
		}
		else {
			g_framework.slider_int( xs( "helicopter max distance" ), &options::visuals::world::max_helicopter_distance, 0, max_distance, 1 );
			g_framework.slider_int( xs( "ores max distance" ), &options::visuals::world::max_ores_distance, 0, max_distance, 1 );
			g_framework.slider_int( xs( "corpse max distance" ), &options::visuals::world::max_corpse_distance, 0, max_distance, 1 );
			g_framework.slider_int( xs( "ore collectibles max distance" ), &options::visuals::world::max_ore_collectibles_distance, 0, max_distance, 1 );
			g_framework.slider_int( xs( "loot containers max distance" ), &options::visuals::world::max_container_distance, 0, max_distance, 1 );
			g_framework.slider_int( xs( "food collectibles max distance" ), &options::visuals::world::max_food_collectibles_distance, 0, max_distance, 1 );
			g_framework.slider_int( xs( "respawn points max distance" ), &options::visuals::world::max_respawn_points_distance, 0, max_distance, 1 );
			g_framework.slider_int( xs( "barrels max distance" ), &options::visuals::world::max_barrels_distance, 0, max_distance, 1 );
			g_framework.slider_int( xs( "cars max distance" ), &options::visuals::world::max_cars_distance, 0, max_distance, 1 );

			g_framework.slider_int( xs( "items max distance" ), &options::visuals::world::max_item_distance, 0, max_distance, 2 );
			g_framework.slider_int( xs( "grenades max distance" ), &options::visuals::world::max_grenade_distance, 0, max_distance, 2 );
			g_framework.slider_int( xs( "animal max distance" ), &options::visuals::world::max_animal_distance, 0, max_distance, 2 );
			g_framework.slider_int( xs( "traps max distance" ), &options::visuals::world::max_trap_distance, 0, max_distance, 2 );
			g_framework.slider_int( xs( "stashes max distance" ), &options::visuals::world::max_stash_distance, 0, max_distance, 2 );
			g_framework.slider_int( xs( "storages max distance" ), &options::visuals::world::max_storage_distance, 0, max_distance, 2 );
			g_framework.slider_int( xs( "vehicle max distance" ), &options::visuals::world::max_vehicle_distance, 0, max_distance, 2 );
			g_framework.slider_int( xs( "raid max distance" ), &options::visuals::world::max_raid_distance, 0, max_distance, 2 );
		}
	}
}
	
void c_menu::draw_combat_tab( ) {
	g_framework.create_check_box( xs( "aim during cycle" ), &options::aimbot::exploits::combat::aim_bolt_cycle, 1 );
	g_framework.create_check_box( xs( "can aim on jugger clothes" ), &options::aimbot::exploits::combat::unlock_aim_on_jugger, 1 );
	g_framework.create_check_box( xs( "burst weapons" ), &options::aimbot::exploits::combat::burst_weapons, 1 );
	g_framework.create_check_box( xs( "automatic weapons" ), &options::aimbot::exploits::combat::automatic_weapons, 1 );
	g_framework.create_check_box( xs( "semi-automatic weapons" ), &options::aimbot::exploits::combat::semi_automatic_weapons, 1 );
	//g_framework.create_check_box( xs( "reduce shotgun spread" ), &options::aimbot::exploits::combat::no_shot_gun_spread, 1 );
	g_framework.create_check_box( xs( "reduce spread" ), &options::aimbot::exploits::combat::no_spread, 1 );
	g_framework.slider_float( xs( "spread amount" ), &options::aimbot::exploits::combat::reduce_spread, 0.0f, 100.f, 1 );
	g_framework.create_check_box( xs( "remove sway" ), &options::aimbot::exploits::combat::no_sway, 1 );
	g_framework.create_check_box( xs( "modify eoka chance" ), &options::aimbot::exploits::combat::modify_eoka_chance, 1 );
	g_framework.slider_float( xs( "eoka chance" ), &options::aimbot::exploits::combat::eoka_chance, 0.0f, 100.f, 1 );
	g_framework.create_check_box( xs( "reduce recoil" ), &options::aimbot::exploits::combat::no_recoil, 1 );
	g_framework.slider_float( xs( "recoil amount" ), &options::aimbot::exploits::combat::reduce_recoil, 0.0f, 100.f, 1 );
	g_framework.create_check_box( xs( "extended melee" ), &options::aimbot::exploits::combat::extended_melee, 1 );
	g_framework.slider_float( xs( "attack radius" ), &options::aimbot::exploits::combat::attack_radius, 0.0f, 2.5f, 1 );
	//g_framework.create_check_box( xs( "big bullets" ), &options::aimbot::exploits::combat::big_bullets, 1 );
	//g_framework.slider_float( xs( "bullet size" ), &options::aimbot::exploits::combat::bullet_size, 0.0f, 250.f, 1 );
	g_framework.create_check_box( xs( "quick bullets" ), &options::aimbot::exploits::combat::quick_bullets, 1 );
	g_framework.slider_int( xs( "bullet speed" ), &options::aimbot::exploits::combat::bullet_speed, 50, 145, 1 );
	g_framework.create_check_box( xs( "spoof hit distance" ), &options::aimbot::exploits::combat::spoof_hit_distance, 1 );
	g_framework.slider_float( xs( "bullet distance" ), &options::aimbot::exploits::combat::bullet_distance, 1.0f, 1000.f, 1 );
	//g_framework.create_check_box( xs( "pierce" ), &options::aimbot::exploits::combat::pierce, 1 );
	g_framework.create_check_box( xs( "attack in air" ), &options::aimbot::exploits::combat::modify_can_attack, 1 );
	g_framework.create_check_box( xs( "attack in vehicles" ), &options::aimbot::exploits::combat::can_attack_in_vehicles, 1 );
	g_framework.create_check_box( xs( "unlock viewangles" ), &options::aimbot::exploits::combat::unlock_view_angles, 1 );
	g_framework.create_check_box( xs( "fake fire" ), &options::aimbot::exploits::misc::fake_fire, 1 );
	g_framework.create_check_box( xs( "fake fire always on" ), &options::aimbot::exploits::misc::fake_fire_on, 1 );	
	g_framework.slider_float( xs( "fire delay" ), &options::aimbot::exploits::misc::delay_fake_fire, 0.0f, 1000.f, 1 );				

	g_framework.create_check_box( xs( "teleport to player head" ), &options::aimbot::exploits::combat::head_teleportation, 2 );

	if( options::aimbot::exploits::combat::head_teleportation )
		g_framework.create_hotkey( xs( "teleport key" ), &options::aimbot::exploits::combat::teleport_key, 2 );

	if( !options::aimbot::exploits::misc::fake_fire_on )
		g_framework.create_hotkey( xs( "fake fire key" ), &options::aimbot::exploits::misc::fake_fire_key, 2 );
}

void c_menu::draw_time_tab( ) {
	g_framework.create_check_box( xs( "rapid-fire" ), &options::aimbot::exploits::time::rapid_fire, 1 );
	g_framework.slider_float( xs( "fire speed" ), &options::aimbot::exploits::time::rapid_fire_speed, 0.0f, 20.f, 1 );
	g_framework.create_check_box( xs( "instant revive" ), &options::aimbot::exploits::time::instant_revive, 1 );
	g_framework.create_check_box( xs( "always revive target" ), &options::aimbot::exploits::time::always_revive_target, 1 );
	g_framework.create_check_box( xs( "instant charge compound" ), &options::aimbot::exploits::time::instant_charge_compound, 1 );

	g_framework.create_label( xs( "additional" ), 2, true );
	g_framework.create_check_box( xs( "fake-lag" ), &options::aimbot::exploits::time::fake_lag, 2 );
	g_framework.create_check_box( xs( "fake-lag always on" ), &options::aimbot::exploits::time::fake_lag_on, 2 );
	g_framework.slider_float( xs( "fake-lag amount" ), &options::aimbot::exploits::time::fake_lag_amount, 0.0f, 2.f, 2 );
	if( !options::aimbot::exploits::time::fake_lag_on )
		g_framework.create_hotkey( xs( "fake-lag key" ), &options::aimbot::exploits::time::fake_lag_key, 2 );

	g_framework.create_check_box( xs( "fast heal" ), &options::aimbot::exploits::time::fast_heal, 2 );
	g_framework.create_check_box( xs( "fast switch" ), &options::aimbot::exploits::time::fast_switch, 2 );
	g_framework.create_check_box( xs( "fast loot" ), &options::aimbot::exploits::time::fast_loot, 2 );

	g_framework.create_check_box( xs( "fast bow" ), &options::aimbot::exploits::time::fast_bow, 2 );

	if( !options::aimbot::exploits::time::always_revive_target )
		g_framework.create_hotkey( xs( "revive key" ), &options::aimbot::exploits::time::revive_key, 1 );
}

void c_menu::draw_movement_tab( ) {
	g_framework.create_check_box( xs( "walk through trees" ), &options::aimbot::exploits::movement::walk_through_trees, 1 );
	g_framework.create_check_box( xs( "walk through ai" ), &options::aimbot::exploits::movement::walk_through_players, 1 );

	g_framework.create_check_box( xs( "modify clothing speed" ), &options::aimbot::exploits::movement::modify_clothing_speed, 1 );
	g_framework.slider_float( xs( "clothing speed" ), &options::aimbot::exploits::movement::clothing_speed, 0.f, 2.5f, 1 );			

	g_framework.create_check_box( xs( "always sprint" ), &options::aimbot::exploits::movement::always_sprint, 1 );
				
	g_framework.create_check_box( xs( "speed hack" ), &options::aimbot::exploits::movement::omni_sprint, 1 );
	g_framework.slider_float( xs( "[s] speed" ), &options::aimbot::exploits::movement::omni_sprint_speed, 100.0f, 300.f, 1 );
	g_framework.create_check_box( xs( "infinite jump" ), &options::aimbot::exploits::movement::infinite_jump, 1 );
	g_framework.create_check_box( xs( "silent walk(shift)" ), &options::aimbot::exploits::movement::silent_walk, 1 );
	g_framework.create_check_box( xs( "climb assistance" ), &options::aimbot::exploits::movement::climb_assist, 1 );
	g_framework.create_check_box( xs( "no slow down on melee" ), &options::aimbot::exploits::movement::disable_slow_down_melee, 1 );
	g_framework.create_check_box( xs( "high jump" ), &options::aimbot::exploits::movement::high_jump, 1 );
	g_framework.slider_float( xs( "jump height" ), &options::aimbot::exploits::movement::jump_height, 100.0f, 275.f, 1 );
	g_framework.create_check_box( xs( "fly-hack" ), &options::aimbot::exploits::movement::fly_hack, 1 );
	g_framework.slider_int( xs( "fly speed" ), &options::aimbot::exploits::movement::fly_speed, 0.0f, 1000.f, 1 );
	g_framework.create_check_box( xs( "anti fly violation" ), &options::aimbot::exploits::movement::stopper_fly, 1 );

	g_framework.create_hotkey( xs( "fly key" ), &options::aimbot::exploits::movement::fly_key, 1 );

	g_framework.create_hotkey( xs( "ignore stopper key" ), &options::aimbot::exploits::movement::ignore_key, 1 );

	g_framework.create_check_box( xs( "increase height" ), &options::aimbot::exploits::movement::increase_height, 2 );
	g_framework.slider_float( xs( "height amount" ), &options::aimbot::exploits::movement::height_amount, 1.8f, 7.5f, 2 );
	g_framework.create_hotkey( xs( "height key" ), &options::aimbot::exploits::movement::increase_height_key, 2 );

	if( options::aimbot::exploits::movement::omni_sprint )
		g_framework.create_hotkey( xs( "speed-hack bind" ), &options::aimbot::exploits::movement::omni_sprint_key, 2 );
}

void c_menu::draw_misc_tab( ) {
	g_framework.create_check_box( xs( "enable friend system" ), &options::friend_system, 1 );
	g_framework.create_hotkey( xs( "add friend key" ), &options::add_friend_key, 1 );

	g_framework.create_label( xs( "disablers" ), 1 );
	g_framework.create_check_box( xs( "disarm landmines" ), &options::aimbot::exploits::misc::disarm_landmines, 1 );
	g_framework.create_check_box( xs( "disable recycler" ), &options::aimbot::exploits::misc::stop_recycler, 1 );

	g_framework.create_check_box( xs( "interactive debug" ), &options::aimbot::exploits::misc::interactive_debug, 2 );
	g_framework.create_check_box( xs( "gesture spam" ), &options::aimbot::exploits::misc::gesture_spam, 2 );
	g_framework.create_combo_box( default_gestures, &options::aimbot::exploits::misc::gesture_type, 2 );

	g_framework.create_check_box( xs( "debug camera" ), &options::aimbot::exploits::misc::debug_camera, 1 );
	g_framework.create_hotkey( xs( "debug camera key" ), &options::aimbot::exploits::misc::debug_camera_key, 1 );

	g_framework.create_check_box( xs( "disable land damage" ), &options::aimbot::exploits::misc::disable_land_damage, 1 );
	g_framework.create_check_box( xs( "always hit weak spot" ), &options::aimbot::exploits::misc::always_hit_weak_spot, 1 );

	g_framework.create_check_box( xs( "change fov" ), &options::aimbot::exploits::misc::fov_changer, 1 );
	g_framework.slider_int( xs( "fov amount" ), &options::aimbot::exploits::misc::fov_amount, 0.0f, 150, 1 );
	g_framework.create_check_box( xs( "zoom" ), &options::aimbot::exploits::misc::zoom_fov, 1 );
	g_framework.slider_int( xs( "zoom fov amount" ), &options::aimbot::exploits::misc::zoom_fov_amount, 0.0f, 40.f, 1 );
		
	g_framework.create_check_box( xs( "keep wounded alive" ), &options::aimbot::exploits::misc::keep_wounded_alive, 1 );
				
	g_framework.create_check_box( xs( "use max view" ), &options::aimbot::exploits::misc::use_max_view, 1 );

	g_framework.create_check_box( xs( "view offset height" ), &options::aimbot::exploits::misc::long_neck, 1 );
	g_framework.slider_float( xs( "height" ), &options::aimbot::exploits::misc::long_neck_height, 0.f, 1.50f, 1 );
	g_framework.create_check_box( xs( "view offset right" ), &options::aimbot::exploits::misc::long_neck_right, 1 );
	g_framework.slider_float( xs( "right" ), &options::aimbot::exploits::misc::long_neck_right_amount, 0.f, 1.50f, 1 );
	g_framework.create_check_box( xs( "view offset left" ), &options::aimbot::exploits::misc::long_neck_left, 1 );
	g_framework.slider_float( xs( "left" ), &options::aimbot::exploits::misc::long_neck_left_amount, 0.f, 1.50f, 1 );

	g_framework.create_check_box( xs( "spin-bot" ), &options::aimbot::exploits::misc::spin_bot, 1 );

	g_framework.create_check_box( xs( "suicide" ), &options::aimbot::exploits::misc::suicide, 1 );

	g_framework.create_check_box( xs( "fake admin" ), &options::aimbot::exploits::misc::fake_admin, 1 );			

	g_framework.create_label( xs( "view" ), 2 );
	g_framework.create_check_box( xs( "no view lower" ), &options::aimbot::exploits::misc::no_lower, 2 );
	g_framework.create_check_box( xs( "no view bob" ), &options::aimbot::exploits::misc::no_viewmodel_bob, 2 );
	g_framework.create_check_box( xs( "no flash" ), &options::aimbot::exploits::misc::no_flash, 2 );

	g_framework.create_check_box( xs( "remove water blur" ), &options::visuals::world::clear_underwater, 2 );

	g_framework.create_check_box( xs( "watermark" ), &options::visuals::show_watermark, 2 );				
				
	g_framework.create_label( xs( "bind related" ), 2 );
	g_framework.create_hotkey( xs( "height key" ), &options::aimbot::exploits::misc::view_height, 2 );
	g_framework.create_hotkey( xs( "right key" ), &options::aimbot::exploits::misc::view_right, 2 );
	g_framework.create_hotkey( xs( "left key" ), &options::aimbot::exploits::misc::view_left, 2 );
	g_framework.create_hotkey( xs( "zoom key" ), &options::aimbot::exploits::misc::zoom_key, 2 );

	g_framework.create_hotkey( xs( "suicide key" ), &options::aimbot::exploits::misc::suicide_key, 2 );
}

void c_menu::draw_modulations_tab( ) {
	g_framework.create_check_box( xs( "modify rain" ), &options::visuals::world::modify_rain, 1 );
	g_framework.slider_float( xs( "rain amount" ), &options::visuals::world::rain_amount, 0.f, 5.f, 1 );

	//g_framework.create_check_box( xs( "night stars" ), &options::visuals::world::night_stars, 1 );
	g_framework.create_check_box( xs( "change aspect ratio" ), &options::visuals::world::aspect_changer, 1 );
	g_framework.slider_float( xs( "aspect ratio" ), &options::visuals::world::aspect_value, 0.1f, 1.92f, 1 );
				
	g_framework.create_check_box( xs( "change time duration" ), &options::aimbot::exploits::time::time_modifier, 1 );
	g_framework.slider_float( xs( "time" ), &options::aimbot::exploits::time::time_speed, 0.0f, 24.f, 1 );

	g_framework.create_check_box( xs( "mie changer" ), &options::visuals::world::mie_changer, 1 );
	if( options::visuals::world::mie_changer )
		g_framework.slider_float( xs( "mie amount" ), &options::visuals::world::mie_amount, 1.0f, 100.f, 1 );	

	g_framework.create_check_box( xs( "rayleigh changer" ), &options::visuals::world::rayleigh_changer, 1 );
	if( options::visuals::world::rayleigh_changer )
		g_framework.slider_float( xs( "rayleigh amount" ), &options::visuals::world::rayleigh_amount, 1.0f, 100.f, 1 );

	g_framework.create_check_box( xs( "stars brightness" ), &options::visuals::world::stars, 1 );
	if( options::visuals::world::stars )
		g_framework.slider_float( xs( "stars amount" ), &options::visuals::world::brightness_stars_amount, 1.0f, 5000.f, 1 );
				
	g_framework.create_check_box( xs( "stars size" ), &options::visuals::world::stars_size, 1 );
	if( options::visuals::world::stars_size )
		g_framework.slider_float( xs( "stars amount size" ), &options::visuals::world::size_stars_amount, 1.0f, 50.f, 1 );

	g_framework.create_check_box( xs( "change ambient" ), &options::visuals::world::ambient, 1 );
	if( options::visuals::world::ambient ) { 
		g_framework.slider_float( xs( "ambient value" ), &options::visuals::world::ambient_value, 1.0f, 15.f, 1 );
		g_framework.slider_float( xs( "light value" ), &options::visuals::world::light_value, 1.0f, 15.f, 1 );
	}

	g_framework.create_check_box( xs( "change world color" ), &options::visuals::world::change_world_color, 1 );
	g_framework.color_picker( xs( "sky color" ), &options::visuals::world::sky_color, 1 );
	g_framework.color_picker( xs( "ambient color" ), &options::visuals::world::ambient_color, 1 );
}

void c_menu::draw_automations_tab( ) {
	g_framework.create_check_box( xs( "auto pickup items" ), &options::aimbot::exploits::misc::auto_pickup_items, 1 );
	if( options::aimbot::exploits::misc::auto_pickup_items )
		g_framework.create_check_box( xs( "pickup everything" ), &options::aimbot::exploits::misc::pickup_everything, 1 );
	g_framework.create_hotkey( xs( "pickup key" ), &options::aimbot::exploits::misc::pickup_key, 1 );
	g_framework.slider_float( xs( "item distance" ), &options::aimbot::exploits::misc::max_item_distance, 0.f, 15.f, 1 );
	g_framework.create_check_box( xs( "always pickup items" ), &options::aimbot::exploits::misc::always_pickup, 1 );

	g_framework.create_check_box( xs( "auto pickup collectibles" ), &options::aimbot::exploits::misc::auto_pickup, 1 );
	g_framework.slider_float( xs( "collectible distance" ), &options::aimbot::exploits::misc::max_collectible_distance, 0.f, 15.f, 1 );

	g_framework.create_check_box( xs( "always set code" ), &options::aimbot::exploits::misc::always_codelock, 1 );
	g_framework.create_check_box( xs( "auto code lock" ), &options::aimbot::exploits::misc::auto_codelock, 1 );
	g_framework.slider_int( xs( "code" ), &options::aimbot::exploits::misc::code_lock_code, 1000, 9999, 1 );
	g_framework.slider_float( xs( "lock distance" ), &options::aimbot::exploits::misc::max_lock_distance, 0.f, 15.f, 1 );
	g_framework.create_hotkey( xs( "code key" ), &options::aimbot::exploits::misc::codelock_key, 1 );

	g_framework.create_check_box( xs( "always grade" ), &options::aimbot::exploits::misc::always_grade, 1 );
	g_framework.create_check_box( xs( "auto grade" ), &options::aimbot::exploits::misc::auto_grade, 1 );
	g_framework.slider_float( xs( "grade distance" ), &options::aimbot::exploits::misc::max_grade_distance, 0.f, 100.f, 1 );
	g_framework.create_combo_box( grade_tier_list, &options::aimbot::exploits::misc::grade_tier, 1 );
	g_framework.create_hotkey( xs( "grade key" ), &options::aimbot::exploits::misc::grade_key, 1 );

	g_framework.create_check_box( xs( "auto untie crates" ), &options::aimbot::exploits::misc::auto_untie_crates, 1 );

	g_framework.create_label( xs( "farm" ), 2 );
	g_framework.create_check_box( xs( "auto farm barrels" ), &options::aimbot::exploits::misc::auto_farm_barrels, 2 );
	g_framework.create_check_box( xs( "auto farm ores" ), &options::aimbot::exploits::misc::auto_farm_ores, 2 );
	g_framework.create_check_box( xs( "auto farm trees" ), &options::aimbot::exploits::misc::auto_farm_trees, 2 );
	g_framework.create_check_box( xs( "farm hotspot" ), &options::aimbot::exploits::misc::auto_farm_only_hotspot, 2 );
}

/* draw menu */
void c_menu::draw_menu( ) {
	if( g_framework.get_ins( ) )
		g_framework.open = !g_framework.open;

	if( g_framework.open
		&& g_framework.alpha < 255.f )
		g_framework.alpha = std::lerp( g_framework.alpha, 255.f, 0.35f );
	else if( !g_framework.open
		&& g_framework.alpha > 0.f )
		g_framework.alpha = std::lerp( g_framework.alpha, 0.f, 0.35f );

	g_framework.in_alpha = g_framework.alpha > 5.f;
	options::accent_color.a = g_framework.alpha;

	if( !g_framework.in_alpha ) {
		g_framework.pressed_key = false;
		g_framework.active_hotkey = g_framework.active_picker = -1;
		return;
	}

	g_framework.begin( );
	g_framework.create_tab( xs( "aimbot" ), 0, 1 );
	g_framework.create_tab( xs( "players" ), 1, 2 );
	g_framework.create_tab( xs( "world" ), 2, 3 );
	g_framework.create_tab( xs( "weapon mods" ), 3, 4 );
	g_framework.create_tab( xs( "time" ), 4, 5 );
	g_framework.create_tab( xs( "movement" ), 5, 6 );
	g_framework.create_tab( xs( "misc" ), 6, 7 );
	g_framework.create_tab( xs( "modulations" ), 7, 8 );
	g_framework.create_tab( xs( "automations" ), 8, 9 );
	g_framework.create_tab( xs( "main" ), 9, 10 );

	// vis check in aim
	// omni-sprint

	switch( g_framework.selected_tab ) {
	case 0:
		draw_aimbot_tab( );
	break;
	case 1:
		draw_visuals_tab( );
	break;
	case 2:
		draw_worlds_tab( );
	break;
	case 3:
		draw_combat_tab( );
	break;
	case 4:
		draw_time_tab( );
	break;
	case 5:
		draw_movement_tab( );
	break;
	case 6:
		draw_misc_tab( );
	break;
	case 7:
		draw_modulations_tab( );
	break;
	case 8:
		draw_automations_tab( );
	break;
	case 9:
		draw_menu_tab( );
	break;
	}

	g_framework.end( );
}

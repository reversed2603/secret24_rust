#pragma once
#include "cfg.h"
#include "../../includes/hinclude.h"
#include "../options.h"
#include "../aimbot/aimbot.h"
#include "../visuals/esp.h"

// create global definition of cfg class.
c_cfg_sys g_cfg;

void c_cfg_sys::save_cfg( const std::string& filename ) {
	std::ofstream cfg_file( filename );
	if( !cfg_file.is_open( ) ) {
		std::cout << xs( "can't open file with name: " ) << filename << std::endl;
		return;
	}

	cfg_file << xs( "add_friend_key " ) << options::add_friend_key << std::endl;

	cfg_file << xs( "aim_check " ) << options::aimbot::aim_check << std::endl;
	cfg_file << xs( "smoothness " ) << options::aimbot::smoothness << std::endl;
	cfg_file << xs( "auto_fire " ) << options::aimbot::auto_fire << std::endl;
	cfg_file << xs( "should_simulate_movement " ) << options::aimbot::should_simulate_movement << std::endl;
	cfg_file << xs( "draw_fov " ) << options::aimbot::draw_fov << std::endl;
	cfg_file << xs( "draw_crosshair " ) << options::aimbot::draw_crosshair << std::endl;
	cfg_file << xs( "draw_target " ) << options::aimbot::draw_target << std::endl;
	cfg_file << xs( "aim_npc " ) << options::aimbot::aim_npc << std::endl;

	cfg_file << xs( "auto_pickup " ) << options::aimbot::exploits::misc::auto_pickup << std::endl;
	cfg_file << xs( "auto_grade " ) << options::aimbot::exploits::misc::auto_grade << std::endl;
	cfg_file << xs( "grade_tier " ) << options::aimbot::exploits::misc::grade_tier << std::endl;
	cfg_file << xs( "auto_pickup_items " ) << options::aimbot::exploits::misc::auto_pickup_items << std::endl;
	cfg_file << xs( "pickup_everything " ) << options::aimbot::exploits::misc::pickup_everything << std::endl;

	cfg_file << xs( "auto_farm_only_hotspot " ) << options::aimbot::exploits::misc::auto_farm_only_hotspot << std::endl;
	cfg_file << xs( "auto_farm_ores " ) << options::aimbot::exploits::misc::auto_farm_ores << std::endl;
	cfg_file << xs( "auto_farm_trees " ) << options::aimbot::exploits::misc::auto_farm_trees << std::endl;
	cfg_file << xs( "auto_farm_barrels " ) << options::aimbot::exploits::misc::auto_farm_barrels << std::endl;

	cfg_file << xs( "max_grade_distance " ) << options::aimbot::exploits::misc::max_grade_distance << std::endl;
	cfg_file << xs( "max_item_distance " ) << options::aimbot::exploits::misc::max_item_distance << std::endl;
	cfg_file << xs( "max_collectible_distance " ) << options::aimbot::exploits::misc::max_collectible_distance << std::endl;

	cfg_file << xs( "manipulation_key " ) << options::aimbot::manipulation_key << std::endl;

	cfg_file << xs( "aim_helicopter " ) << options::aimbot::aim_helicopter << std::endl;
	cfg_file << xs( "manipulation " ) << options::aimbot::manipulation << std::endl;
	cfg_file << xs( "kill_aura " ) << options::aimbot::kill_aura << std::endl;
	cfg_file << xs( "auto_reload " ) << options::aimbot::auto_reload << std::endl;
	cfg_file << xs( "aim_nearest_bone " ) << options::aimbot::aim_nearest_bone << std::endl;

	cfg_file << xs( "aim_type " ) << options::aimbot::aim_type << std::endl;

	cfg_file << xs( "aim_bone " ) << options::aimbot::aim_bone << std::endl;
	cfg_file << xs( "manipulation_key " ) << options::aimbot::manipulation_key << std::endl;
	cfg_file << xs( "smooth_type " ) << options::aimbot::smooth_type << std::endl;
	cfg_file << xs( "max_target_distance " ) << options::aimbot::max_target_distance << std::endl;
	cfg_file << xs( "fov_amount " ) << options::aimbot::fov_amount << std::endl;

	cfg_file << xs( "always_grade " ) << options::aimbot::exploits::misc::always_grade << std::endl;
	cfg_file << xs( "always_codelock " ) << options::aimbot::exploits::misc::always_codelock << std::endl;
	cfg_file << xs( "always_pickup " ) << options::aimbot::exploits::misc::always_pickup << std::endl;

	cfg_file << xs( "codelock_key " ) << options::aimbot::exploits::misc::codelock_key << std::endl;
	cfg_file << xs( "grade_key " ) << options::aimbot::exploits::misc::grade_key << std::endl;
	cfg_file << xs( "pickup_key " ) << options::aimbot::exploits::misc::pickup_key << std::endl;
	cfg_file << xs( "auto_codelock " ) << options::aimbot::exploits::misc::auto_codelock << std::endl;
	cfg_file << xs( "code_lock_code " ) << options::aimbot::exploits::misc::code_lock_code << std::endl;
	cfg_file << xs( "max_lock_distance " ) << options::aimbot::exploits::misc::max_lock_distance << std::endl;

	cfg_file << xs( "no_viewmodel_bob " ) << options::aimbot::exploits::misc::no_viewmodel_bob << std::endl;
	cfg_file << xs( "no_lower " ) << options::aimbot::exploits::misc::no_lower << std::endl;

	cfg_file << xs( "smoothness_amount " ) << options::aimbot::smoothness_amount << std::endl;

	cfg_file << xs( "infinite_jump " ) << options::aimbot::exploits::movement::infinite_jump << std::endl;
	cfg_file << xs( "stopper_fly " ) << options::aimbot::exploits::movement::stopper_fly << std::endl;
	cfg_file << xs( "climb_assist " ) << options::aimbot::exploits::movement::climb_assist << std::endl;
	cfg_file << xs( "fly_hack " ) << options::aimbot::exploits::movement::fly_hack << std::endl;
	cfg_file << xs( "omni_sprint " ) << options::aimbot::exploits::movement::omni_sprint << std::endl;
	cfg_file << xs( "silent_walk " ) << options::aimbot::exploits::movement::silent_walk << std::endl;
	cfg_file << xs( "always_sprint " ) << options::aimbot::exploits::movement::always_sprint << std::endl;
	cfg_file << xs( "high_jump " ) << options::aimbot::exploits::movement::high_jump << std::endl;

	cfg_file << xs( "walk_through_players " ) << options::aimbot::exploits::movement::walk_through_players << std::endl;
	cfg_file << xs( "disable_slow_down_melee " ) << options::aimbot::exploits::movement::disable_slow_down_melee << std::endl;
	cfg_file << xs( "modify_clothing_speed " ) << options::aimbot::exploits::movement::modify_clothing_speed << std::endl;
	cfg_file << xs( "increase_height " ) << options::aimbot::exploits::movement::increase_height << std::endl;

	cfg_file << xs( "fly_key " ) << options::aimbot::exploits::movement::fly_key << std::endl;
	cfg_file << xs( "ignore_key " ) << options::aimbot::exploits::movement::ignore_key << std::endl;
	cfg_file << xs( "omni_sprint_key " ) << options::aimbot::exploits::movement::omni_sprint_key << std::endl;
	cfg_file << xs( "silent_walk_key " ) << options::aimbot::exploits::movement::silent_walk_key << std::endl;
	cfg_file << xs( "increase_height_key " ) << options::aimbot::exploits::movement::increase_height_key << std::endl;
	cfg_file << xs( "fly_speed " ) << options::aimbot::exploits::movement::fly_speed << std::endl;
	cfg_file << xs( "jump_height " ) << options::aimbot::exploits::movement::jump_height << std::endl;
	cfg_file << xs( "omni_sprint_speed " ) << options::aimbot::exploits::movement::omni_sprint_speed << std::endl;
	cfg_file << xs( "height_amount " ) << options::aimbot::exploits::movement::height_amount << std::endl;

	cfg_file << xs( "show_ducking_flag " ) << options::visuals::show_ducking_flag << std::endl;
	cfg_file << xs( "ducking_color[0] " ) << options::visuals::ducking_color.r << std::endl;
	cfg_file << xs( "ducking_color[1] " ) << options::visuals::ducking_color.g << std::endl;
	cfg_file << xs( "ducking_color[2] " ) << options::visuals::ducking_color.b << std::endl;

	cfg_file << xs( "show_knocked_flag " ) << options::visuals::show_knocked_flag << std::endl;
	cfg_file << xs( "knocked_color[0] " ) << options::visuals::knocked_color.r << std::endl;
	cfg_file << xs( "knocked_color[1] " ) << options::visuals::knocked_color.g << std::endl;
	cfg_file << xs( "knocked_color[2] " ) << options::visuals::knocked_color.b << std::endl;

	cfg_file << xs( "sky_color[0] " ) << options::visuals::world::sky_color.r << std::endl;
	cfg_file << xs( "sky_color[1] " ) << options::visuals::world::sky_color.g << std::endl;
	cfg_file << xs( "sky_color[2] " ) << options::visuals::world::sky_color.b << std::endl;

	cfg_file << xs( "ambient_color[0] " ) << options::visuals::world::ambient_color.r << std::endl;
	cfg_file << xs( "ambient_color[1] " ) << options::visuals::world::ambient_color.g << std::endl;
	cfg_file << xs( "ambient_color[2] " ) << options::visuals::world::ambient_color.b << std::endl;

	cfg_file << xs( "automatic_weapons " ) << options::aimbot::exploits::combat::automatic_weapons << std::endl;
	cfg_file << xs( "semi_automatic_weapons " ) << options::aimbot::exploits::combat::semi_automatic_weapons << std::endl;
	cfg_file << xs( "burst_weapons " ) << options::aimbot::exploits::combat::burst_weapons << std::endl;
	cfg_file << xs( "unlock_aim_on_jugger " ) << options::aimbot::exploits::combat::unlock_aim_on_jugger << std::endl;
	cfg_file << xs( "aim_bolt_cycle " ) << options::aimbot::exploits::combat::aim_bolt_cycle << std::endl;
	cfg_file << xs( "extended_melee " ) << options::aimbot::exploits::combat::extended_melee << std::endl;
	cfg_file << xs( "no_spread " ) << options::aimbot::exploits::combat::no_spread << std::endl;
	cfg_file << xs( "no_sway " ) << options::aimbot::exploits::combat::no_sway << std::endl;
	cfg_file << xs( "modify_eoka_chance " ) << options::aimbot::exploits::combat::modify_eoka_chance << std::endl;
	cfg_file << xs( "no_recoil " ) << options::aimbot::exploits::combat::no_recoil << std::endl;
	cfg_file << xs( "modify_can_attack " ) << options::aimbot::exploits::combat::modify_can_attack << std::endl;
	cfg_file << xs( "can_attack_in_vehicles " ) << options::aimbot::exploits::combat::can_attack_in_vehicles << std::endl;
	cfg_file << xs( "unlock_view_angles " ) << options::aimbot::exploits::combat::unlock_view_angles << std::endl;
	cfg_file << xs( "big_bullets " ) << options::aimbot::exploits::combat::big_bullets << std::endl;
	cfg_file << xs( "quick_bullets " ) << options::aimbot::exploits::combat::quick_bullets << std::endl;

	cfg_file << xs( "pierce " ) << options::aimbot::exploits::combat::pierce << std::endl;
	cfg_file << xs( "spoof_hit_distance " ) << options::aimbot::exploits::combat::spoof_hit_distance << std::endl;
	cfg_file << xs( "no_shot_gun_spread " ) << options::aimbot::exploits::combat::no_shot_gun_spread << std::endl;
	cfg_file << xs( "head_teleportation " ) << options::aimbot::exploits::combat::head_teleportation << std::endl;

	cfg_file << xs( "reduce_recoil " ) << options::aimbot::exploits::combat::reduce_recoil << std::endl;
	cfg_file << xs( "reduce_spread " ) << options::aimbot::exploits::combat::reduce_spread << std::endl;
	cfg_file << xs( "bullet_distance " ) << options::aimbot::exploits::combat::bullet_distance << std::endl;
	cfg_file << xs( "eoka_chance " ) << options::aimbot::exploits::combat::eoka_chance << std::endl;
	cfg_file << xs( "attack_radius " ) << options::aimbot::exploits::combat::attack_radius << std::endl;
	cfg_file << xs( "bullet_size " ) << options::aimbot::exploits::combat::bullet_size << std::endl;
	cfg_file << xs( "teleport_key " ) << options::aimbot::exploits::combat::teleport_key << std::endl;
	cfg_file << xs( "bullet_speed " ) << options::aimbot::exploits::combat::bullet_speed << std::endl;

	cfg_file << xs( "show_diesel_fuel " ) << options::visuals::world::show_diesel_fuel << std::endl;

	cfg_file << xs( "fast_loot " ) << options::aimbot::exploits::time::fast_loot << std::endl;
	cfg_file << xs( "fast_heal " ) << options::aimbot::exploits::time::fast_heal << std::endl;
	cfg_file << xs( "fast_switch " ) << options::aimbot::exploits::time::fast_switch << std::endl;
	cfg_file << xs( "time_modifier " ) << options::aimbot::exploits::time::time_modifier << std::endl;
	cfg_file << xs( "rapid_fire " ) << options::aimbot::exploits::time::rapid_fire << std::endl;
	cfg_file << xs( "fake_lag " ) << options::aimbot::exploits::time::fake_lag << std::endl;
	cfg_file << xs( "instant_charge_compound " ) << options::aimbot::exploits::time::instant_charge_compound << std::endl;
	cfg_file << xs( "fake_lag_on " ) << options::aimbot::exploits::time::fake_lag_on << std::endl;
	cfg_file << xs( "fake_lag_amount " ) << options::aimbot::exploits::time::fake_lag_amount << std::endl;


	cfg_file << xs( "revive_key " ) << options::aimbot::exploits::time::revive_key << std::endl;
	cfg_file << xs( "fake_lag_key " ) << options::aimbot::exploits::time::fake_lag_key << std::endl;
	cfg_file << xs( "instant_revive " ) << options::aimbot::exploits::time::instant_revive << std::endl;
	cfg_file << xs( "fast_bow " ) << options::aimbot::exploits::time::fast_bow << std::endl;
	cfg_file << xs( "always_revive_target " ) << options::aimbot::exploits::time::always_revive_target << std::endl;
	cfg_file << xs( "rapid_fire_speed " ) << options::aimbot::exploits::time::rapid_fire_speed << std::endl;
	cfg_file << xs( "time_speed " ) << options::aimbot::exploits::time::time_speed << std::endl;

	cfg_file << xs( "keep_wounded_alive " ) << options::aimbot::exploits::misc::keep_wounded_alive << std::endl;
	cfg_file << xs( "always_hit_weak_spot " ) << options::aimbot::exploits::misc::always_hit_weak_spot << std::endl;
	cfg_file << xs( "long_neck " ) << options::aimbot::exploits::misc::long_neck << std::endl;
	cfg_file << xs( "long_neck_right " ) << options::aimbot::exploits::misc::long_neck_right << std::endl;
	cfg_file << xs( "long_neck_left " ) << options::aimbot::exploits::misc::long_neck_left << std::endl;
	cfg_file << xs( "disable_land_damage " ) << options::aimbot::exploits::misc::disable_land_damage << std::endl;
	cfg_file << xs( "fov_changer " ) << options::aimbot::exploits::misc::fov_changer << std::endl;
	cfg_file << xs( "zoom_fov " ) << options::aimbot::exploits::misc::zoom_fov << std::endl;

	cfg_file << xs( "radar_position[0] " ) << g_esp.radar_position.x << std::endl;
	cfg_file << xs( "radar_position[1] " ) << g_esp.radar_position.y << std::endl;

	cfg_file << xs( "hotbar_position[0] " ) << g_esp.hotbar_position.x << std::endl;
	cfg_file << xs( "hotbar_position[1] " ) << g_esp.hotbar_position.y << std::endl;

	cfg_file << xs( "clothes_position[0] " ) << g_esp.clothes_position.x << std::endl;
	cfg_file << xs( "clothes_position[1] " ) << g_esp.clothes_position.y << std::endl;

	cfg_file << xs( "suicide " ) << options::aimbot::exploits::misc::suicide << std::endl;
	cfg_file << xs( "fake_fire " ) << options::aimbot::exploits::misc::fake_fire << std::endl;
	cfg_file << xs( "fake_admin " ) << options::aimbot::exploits::misc::fake_admin << std::endl;
	cfg_file << xs( "fake_fire_on " ) << options::aimbot::exploits::misc::fake_fire_on << std::endl;
	cfg_file << xs( "debug_camera " ) << options::aimbot::exploits::misc::debug_camera << std::endl;
	cfg_file << xs( "spin_bot " ) << options::aimbot::exploits::misc::spin_bot << std::endl;
	cfg_file << xs( "gesture_spam " ) << options::aimbot::exploits::misc::gesture_spam << std::endl;
	cfg_file << xs( "interactive_debug " ) << options::aimbot::exploits::misc::interactive_debug << std::endl;
	cfg_file << xs( "disarm_landmines " ) << options::aimbot::exploits::misc::disarm_landmines << std::endl;
	cfg_file << xs( "stop_recycler " ) << options::aimbot::exploits::misc::stop_recycler << std::endl;
	cfg_file << xs( "long_neck_height " ) << options::aimbot::exploits::misc::long_neck_height << std::endl;
	cfg_file << xs( "long_neck_right_amount " ) << options::aimbot::exploits::misc::long_neck_right_amount << std::endl;
	cfg_file << xs( "delay_fake_fire " ) << options::aimbot::exploits::misc::delay_fake_fire << std::endl;
	cfg_file << xs( "long_neck_left_amount " ) << options::aimbot::exploits::misc::long_neck_left_amount << std::endl;
	cfg_file << xs( "zoom_fov_amount " ) << options::aimbot::exploits::misc::zoom_fov_amount << std::endl;
	cfg_file << xs( "no_flash " ) << options::aimbot::exploits::misc::no_flash << std::endl;
	
	cfg_file << xs( "fov_amount " ) << options::aimbot::exploits::misc::fov_amount << std::endl;
	cfg_file << xs( "view_left " ) << options::aimbot::exploits::misc::view_left << std::endl;
	cfg_file << xs( "view_right " ) << options::aimbot::exploits::misc::view_right << std::endl;
	cfg_file << xs( "view_height " ) << options::aimbot::exploits::misc::view_height << std::endl;
	cfg_file << xs( "zoom_key " ) << options::aimbot::exploits::misc::zoom_key << std::endl;
	cfg_file << xs( "fake_fire_key " ) << options::aimbot::exploits::misc::fake_fire_key << std::endl;
	cfg_file << xs( "gesture_type " ) << options::aimbot::exploits::misc::gesture_type << std::endl;
	cfg_file << xs( "debug_camera_key " ) << options::aimbot::exploits::misc::debug_camera_key << std::endl;
	cfg_file << xs( "suicide_key " ) << options::aimbot::exploits::misc::suicide_key << std::endl;
	cfg_file << xs( "gesture_type " ) << options::aimbot::exploits::misc::gesture_type << std::endl;

	cfg_file << xs( "auto_untie_crates " ) << options::aimbot::exploits::misc::auto_untie_crates << std::endl;

	cfg_file << xs( "master_switch ") << options::visuals::world::master_switch << std::endl;

	cfg_file << xs( "draw_visuals " ) << options::visuals::draw_visuals << std::endl;
	cfg_file << xs( "indicators " ) << options::visuals::indicators << std::endl;
	cfg_file << xs( "fly_hack_indicator " ) << options::visuals::fly_hack_indicator << std::endl;
	cfg_file << xs( "draw_tracers " ) << options::visuals::draw_tracers << std::endl;
	cfg_file << xs( "offscreen_arrows " ) << options::visuals::offscreen_arrows << std::endl;
	cfg_file << xs( "draw_radar " ) << options::visuals::draw_radar << std::endl;
	cfg_file << xs( "show_name " ) << options::visuals::show_name << std::endl;
	cfg_file << xs( "show_weapon " ) << options::visuals::show_weapon << std::endl;
	cfg_file << xs( "show_health " ) << options::visuals::show_health << std::endl;
	cfg_file << xs( "show_health_text " ) << options::visuals::show_health_text << std::endl;
	cfg_file << xs( "show_distance " ) << options::visuals::show_distance << std::endl;
	cfg_file << xs( "show_hotbar " ) << options::visuals::show_hotbar << std::endl;
	cfg_file << xs( "show_clothes " ) << options::visuals::show_clothes << std::endl;
	cfg_file << xs( "show_lines " ) << options::visuals::show_lines << std::endl;
	cfg_file << xs( "show_view_direction " ) << options::visuals::show_view_direction << std::endl;
	cfg_file << xs( "can_show_sleepers " ) << options::visuals::can_show_sleepers << std::endl;
	cfg_file << xs( "can_show_knocked " ) << options::visuals::can_show_knocked << std::endl;
	cfg_file << xs( "can_show_npc " ) << options::visuals::can_show_npc << std::endl;
	cfg_file << xs( "chams " ) << options::visuals::chams << std::endl;
	cfg_file << xs( "rgb_chams " ) << options::visuals::rgb_chams << std::endl;
	cfg_file << xs( "draw_bones " ) << options::visuals::draw_bones << std::endl;
	cfg_file << xs( "show_watermark " ) << options::visuals::show_watermark << std::endl;
	cfg_file << xs( "local_trails " ) << options::visuals::local_trails << std::endl;
	cfg_file << xs( "show_last_sent_tick " ) << options::visuals::show_last_sent_tick << std::endl;
	cfg_file << xs( "show_desync_bar " ) << options::visuals::show_desync_bar << std::endl;
	cfg_file << xs( "show_reload_bar " ) << options::visuals::show_reload_bar << std::endl;
	cfg_file << xs( "can_show_sleepers_oof " ) << options::visuals::can_show_sleepers_oof << std::endl;
	cfg_file << xs( "can_show_knocked_oof " ) << options::visuals::can_show_knocked_oof << std::endl;
	cfg_file << xs( "can_show_npc_oof " ) << options::visuals::can_show_npc_oof << std::endl;
	cfg_file << xs( "max_player_distance " ) << options::visuals::max_player_distance << std::endl;
	cfg_file << xs( "box_type " ) << options::visuals::box_type << std::endl;
	cfg_file << xs( "offscreen_distance " ) << options::visuals::offscreen_distance << std::endl;

	cfg_file << xs( "show_stashes " ) << options::visuals::world::show_stashes << std::endl;

	cfg_file << xs( "rainbow_accent " ) << options::rainbow_accent << std::endl;

	cfg_file << xs( "show_corpse " ) << options::visuals::world::show_corpse << std::endl;
	cfg_file << xs( "show_backpack " ) << options::visuals::world::show_backpack << std::endl;
	cfg_file << xs( "todsky " ) << options::visuals::world::todsky << std::endl;
	cfg_file << xs( "show_grenades " ) << options::visuals::world::show_grenades << std::endl;
	cfg_file << xs( "night_stars " ) << options::visuals::world::night_stars << std::endl;
	cfg_file << xs( "clear_underwater " ) << options::visuals::world::clear_underwater << std::endl;
	cfg_file << xs( "change_world_color " ) << options::visuals::world::change_world_color << std::endl;

	cfg_file << xs( "todsky " ) << options::visuals::world::todsky << std::endl;
	cfg_file << xs( "show_grenades " ) << options::visuals::world::show_grenades << std::endl;
	cfg_file << xs( "night_stars " ) << options::visuals::world::night_stars << std::endl;
	cfg_file << xs( "clear_underwater " ) << options::visuals::world::clear_underwater << std::endl;
	cfg_file << xs( "change_world_color " ) << options::visuals::world::change_world_color << std::endl;

	cfg_file << xs( "show_heal " ) << options::visuals::world::show_heal << std::endl;
	cfg_file << xs( "show_weapons " ) << options::visuals::world::show_weapons << std::endl;
	cfg_file << xs( "show_melee_weapons " ) << options::visuals::world::show_melee_weapons << std::endl;
	cfg_file << xs( "show_everything " ) << options::visuals::world::show_everything << std::endl;

	cfg_file << xs( "show_item_amount " ) << options::visuals::world::show_item_amount << std::endl;
	cfg_file << xs( "stars_size " ) << options::visuals::world::stars_size << std::endl;
	cfg_file << xs( "stars " ) << options::visuals::world::stars << std::endl;
	cfg_file << xs( "ambient " ) << options::visuals::world::ambient << std::endl;
	cfg_file << xs( "mie_changer " ) << options::visuals::world::mie_changer << std::endl;

	cfg_file << xs( "rayleigh_changer " ) << options::visuals::world::rayleigh_changer << std::endl;
	cfg_file << xs( "brightness_changer " ) << options::visuals::world::brightness_changer << std::endl;
	cfg_file << xs( "aspect_changer " ) << options::visuals::world::aspect_changer << std::endl;
	cfg_file << xs( "show_sulfur_ore " ) << options::visuals::world::show_sulfur_ore << std::endl;
	cfg_file << xs( "show_metal_ore " ) << options::visuals::world::show_metal_ore << std::endl;
	cfg_file << xs( "show_stone_ore " ) << options::visuals::world::show_stone_ore << std::endl;
	cfg_file << xs( "show_box_storages " ) << options::visuals::world::show_box_storages << std::endl;
	cfg_file << xs( "show_tool_cupboard " ) << options::visuals::world::show_tool_cupboard << std::endl;
	cfg_file << xs( "aspect_changer " ) << options::visuals::world::aspect_changer << std::endl;
	cfg_file << xs( "show_sulfur_ore " ) << options::visuals::world::show_sulfur_ore << std::endl;
	cfg_file << xs( "show_metal_ore " ) << options::visuals::world::show_metal_ore << std::endl;
	cfg_file << xs( "show_stone_ore " ) << options::visuals::world::show_stone_ore << std::endl;
	cfg_file << xs( "show_vending_machine " ) << options::visuals::world::show_vending_machine << std::endl;
	cfg_file << xs( "show_drone " ) << options::visuals::world::show_drone << std::endl;
	cfg_file << xs( "show_recycler " ) << options::visuals::world::show_recycler << std::endl;
	cfg_file << xs( "show_tool_cupboard " ) << options::visuals::world::show_tool_cupboard << std::endl;
	cfg_file << xs( "show_oil_barrel " ) << options::visuals::world::show_oil_barrel << std::endl;
	cfg_file << xs( "show_regular_barrels " ) << options::visuals::world::show_regular_barrels << std::endl;
	cfg_file << xs( "show_underwater_crate " ) << options::visuals::world::show_underwater_crate << std::endl;
	cfg_file << xs( "show_elite_crate " ) << options::visuals::world::show_elite_crate << std::endl;
	cfg_file << xs( "show_military_crate " ) << options::visuals::world::show_military_crate << std::endl;
	cfg_file << xs( "show_bradley_crate " ) << options::visuals::world::show_bradley_crate << std::endl;

	cfg_file << xs( "show_helicopter_crate " ) << options::visuals::world::show_helicopter_crate << std::endl;
	cfg_file << xs( "show_hackable_locked_crate " ) << options::visuals::world::show_hackable_locked_crate << std::endl;
	cfg_file << xs( "show_normal_crate " ) << options::visuals::world::show_normal_crate << std::endl;
	cfg_file << xs( "show_chickens " ) << options::visuals::world::show_chickens << std::endl;
	cfg_file << xs( "show_small_crate " ) << options::visuals::world::show_small_crate << std::endl;
	cfg_file << xs( "show_mine_crate " ) << options::visuals::world::show_mine_crate << std::endl;
	cfg_file << xs( "show_tool_box " ) << options::visuals::world::show_tool_box << std::endl;
	cfg_file << xs( "show_tool_cupboard " ) << options::visuals::world::show_tool_cupboard << std::endl;
	cfg_file << xs( "show_boars " ) << options::visuals::world::show_boars << std::endl;
	cfg_file << xs( "show_wolves " ) << options::visuals::world::show_wolves << std::endl;
	cfg_file << xs( "show_horses " ) << options::visuals::world::show_horses << std::endl;

	cfg_file << xs( "show_sharks " ) << options::visuals::world::show_sharks << std::endl;
	cfg_file << xs( "show_deers " ) << options::visuals::world::show_deers << std::endl;
	cfg_file << xs( "show_polar_bears " ) << options::visuals::world::show_polar_bears << std::endl;

	cfg_file << xs( "show_bears " ) << options::visuals::world::show_bears << std::endl;
	cfg_file << xs( "show_sulfur_collectibles " ) << options::visuals::world::show_sulfur_collectibles << std::endl;
	cfg_file << xs( "show_metal_collectibles " ) << options::visuals::world::show_metal_collectibles << std::endl;
	cfg_file << xs( "show_wood_collectibles " ) << options::visuals::world::show_wood_collectibles << std::endl;
	cfg_file << xs( "show_stone_collectibles " ) << options::visuals::world::show_military_crate << std::endl;

	cfg_file << xs( "show_supply_signals " ) << options::visuals::world::show_supply_signals << std::endl;
	cfg_file << xs( "show_supply_drops " ) << options::visuals::world::show_supply_drops << std::endl;
	cfg_file << xs( "show_ammo_nails_arrows " ) << options::visuals::world::show_ammo_nails_arrows << std::endl;

	cfg_file << xs( "show_food_crate " ) << options::visuals::world::show_food_crate << std::endl;
	cfg_file << xs( "show_medical_crate " ) << options::visuals::world::show_medical_crate << std::endl;

	cfg_file << xs( "show_duo_submarine " ) << options::visuals::world::show_duo_submarine << std::endl;
	cfg_file << xs( "show_solo_submarine " ) << options::visuals::world::show_solo_submarine << std::endl;
	cfg_file << xs( "show_small_motorboat " ) << options::visuals::world::show_small_motorboat << std::endl;

	cfg_file << xs( "show_kayak " ) << options::visuals::world::show_kayak << std::endl;

	cfg_file << xs( "show_bradley_apc " ) << options::visuals::world::show_bradley_apc << std::endl;
	cfg_file << xs( "show_rhib " ) << options::visuals::world::show_rhib << std::endl;
	cfg_file << xs( "show_scrap_helicopter " ) << options::visuals::world::show_scrap_helicopter << std::endl;
	cfg_file << xs( "show_minicopter " ) << options::visuals::world::show_minicopter << std::endl;
	cfg_file << xs( "show_two_modules_car " ) << options::visuals::world::show_two_modules_car << std::endl;
	cfg_file << xs( "show_modular_car " ) << options::visuals::world::show_modular_car << std::endl;

	cfg_file << xs( "show_potatos " ) << options::visuals::world::show_potatos << std::endl;
	cfg_file << xs( "show_corns " ) << options::visuals::world::show_corns << std::endl;
	cfg_file << xs( "show_berrys " ) << options::visuals::world::show_berrys << std::endl;
	cfg_file << xs( "show_pumpkin " ) << options::visuals::world::show_pumpkin << std::endl;
	cfg_file << xs( "show_mushroom " ) << options::visuals::world::show_mushroom << std::endl;
	cfg_file << xs( "show_hemp " ) << options::visuals::world::show_hemp << std::endl;

	cfg_file << xs( "show_potatos " ) << options::visuals::world::show_potatos << std::endl;
	cfg_file << xs( "show_corns " ) << options::visuals::world::show_corns << std::endl;
	cfg_file << xs( "show_berrys " ) << options::visuals::world::show_berrys << std::endl;
	cfg_file << xs( "show_pumpkin " ) << options::visuals::world::show_pumpkin << std::endl;
	cfg_file << xs( "show_mushroom " ) << options::visuals::world::show_mushroom << std::endl;
	cfg_file << xs( "show_hemp " ) << options::visuals::world::show_hemp << std::endl;

	cfg_file << xs( "show_potatos " ) << options::visuals::world::show_potatos << std::endl;
	cfg_file << xs( "show_corns " ) << options::visuals::world::show_corns << std::endl;
	cfg_file << xs( "show_berrys " ) << options::visuals::world::show_berrys << std::endl;
	cfg_file << xs( "show_pumpkin " ) << options::visuals::world::show_pumpkin << std::endl;
	cfg_file << xs( "show_mushroom " ) << options::visuals::world::show_mushroom << std::endl;
	cfg_file << xs( "show_hemp " ) << options::visuals::world::show_hemp << std::endl;

	cfg_file << xs( "show_landmines " ) << options::visuals::world::show_landmines << std::endl;
	cfg_file << xs( "show_npc_turrets " ) << options::visuals::world::show_npc_turrets << std::endl;
	cfg_file << xs( "show_auto_turrets " ) << options::visuals::world::show_auto_turrets << std::endl;
	cfg_file << xs( "show_shotgun_traps " ) << options::visuals::world::show_shotgun_traps << std::endl;
	cfg_file << xs( "show_tesla_coil " ) << options::visuals::world::show_tesla_coil << std::endl;

	cfg_file << xs( "show_flame_turrets " ) << options::visuals::world::show_flame_turrets << std::endl;
	cfg_file << xs( "show_sam_site " ) << options::visuals::world::show_sam_site << std::endl;
	cfg_file << xs( "show_bear_trap " ) << options::visuals::world::show_bear_trap << std::endl;

	cfg_file << xs( "size_stars_amount " ) << options::visuals::world::size_stars_amount << std::endl;
	cfg_file << xs( "brightness_stars_amount " ) << options::visuals::world::brightness_stars_amount << std::endl;
	cfg_file << xs( "ambient_value " ) << options::visuals::world::ambient_value << std::endl;
	cfg_file << xs( "aspect_value " ) << options::visuals::world::aspect_value << std::endl;
	cfg_file << xs( "light_value " ) << options::visuals::world::light_value << std::endl;
	cfg_file << xs( "rayleigh_amount " ) << options::visuals::world::rayleigh_amount << std::endl;
	cfg_file << xs( "brightness_amount " ) << options::visuals::world::brightness_amount << std::endl;
	cfg_file << xs( "mie_amount " ) << options::visuals::world::mie_amount << std::endl;

	// distance
	cfg_file << xs( "max_cars_distance " ) << options::visuals::world::max_cars_distance << std::endl;
	cfg_file << xs( "max_barrels_distance " ) << options::visuals::world::max_barrels_distance << std::endl;
	cfg_file << xs( "max_ores_distance " ) << options::visuals::world::max_ores_distance << std::endl;
	cfg_file << xs( "max_grenade_distance " ) << options::visuals::world::max_grenade_distance << std::endl;
	cfg_file << xs( "max_food_collectibles_distance " ) << options::visuals::world::max_food_collectibles_distance << std::endl;
	cfg_file << xs( "max_container_distance " ) << options::visuals::world::max_container_distance << std::endl;
	cfg_file << xs( "max_corpse_distance " ) << options::visuals::world::max_corpse_distance << std::endl;
	cfg_file << xs( "max_vehicle_distance " ) << options::visuals::world::max_vehicle_distance << std::endl;
	cfg_file << xs( "max_ore_collectibles_distance " ) << options::visuals::world::max_ore_collectibles_distance << std::endl;
	cfg_file << xs( "max_respawn_points_distance " ) << options::visuals::world::max_respawn_points_distance << std::endl;
	cfg_file << xs( "max_helicopter_distance " ) << options::visuals::world::max_helicopter_distance << std::endl;

	cfg_file << xs( "color_heal[0] " ) << options::visuals::world::color_heal.r << std::endl;
	cfg_file << xs( "color_heal[1] " ) << options::visuals::world::color_heal.g << std::endl;
	cfg_file << xs( "color_heal[2] " ) << options::visuals::world::color_heal.b << std::endl;

	cfg_file << xs( "color_weapons[0] " ) << options::visuals::world::color_weapons.r << std::endl;
	cfg_file << xs( "color_weapons[1] " ) << options::visuals::world::color_weapons.g << std::endl;
	cfg_file << xs( "color_weapons[2] " ) << options::visuals::world::color_weapons.b << std::endl;

	cfg_file << xs( "color_corpse[0] " ) << options::visuals::world::color_corpse.r << std::endl;
	cfg_file << xs( "color_corpse[1] " ) << options::visuals::world::color_corpse.g << std::endl;
	cfg_file << xs( "color_corpse[2] " ) << options::visuals::world::color_corpse.b << std::endl;

	cfg_file << xs( "color_backpack[0] " ) << options::visuals::world::color_backpack.r << std::endl;
	cfg_file << xs( "color_backpack[1] " ) << options::visuals::world::color_backpack.g << std::endl;
	cfg_file << xs( "color_backpack[2] " ) << options::visuals::world::color_backpack.b << std::endl;

	cfg_file << xs( "color_melee_weapons[0] " ) << options::visuals::world::color_melee_weapons.r << std::endl;
	cfg_file << xs( "color_melee_weapons[1] " ) << options::visuals::world::color_melee_weapons.g << std::endl;
	cfg_file << xs( "color_melee_weapons[2] " ) << options::visuals::world::color_melee_weapons.b << std::endl;

	cfg_file << xs( "color_everything[0] " ) << options::visuals::world::color_everything.r << std::endl;
	cfg_file << xs( "color_everything[1] " ) << options::visuals::world::color_everything.g << std::endl;
	cfg_file << xs( "color_everything[2] " ) << options::visuals::world::color_everything.b << std::endl;

	cfg_file << xs( "color_stashes[0] " ) << options::visuals::world::color_stashes.r << std::endl;
	cfg_file << xs( "color_stashes[1] " ) << options::visuals::world::color_stashes.g << std::endl;
	cfg_file << xs( "color_stashes[2] " ) << options::visuals::world::color_stashes.b << std::endl;
	
	cfg_file << xs( "color_animals[0] " ) << options::visuals::world::color_animals.r << std::endl;
	cfg_file << xs( "color_animals[1] " ) << options::visuals::world::color_animals.g << std::endl;
	cfg_file << xs( "color_animals[2] " ) << options::visuals::world::color_animals.b << std::endl;

	cfg_file << xs( "color_traps[0] " ) << options::visuals::world::color_traps.r << std::endl;
	cfg_file << xs( "color_traps[1] " ) << options::visuals::world::color_traps.g << std::endl;
	cfg_file << xs( "color_traps[2] " ) << options::visuals::world::color_traps.b << std::endl;

	cfg_file << xs( "color_storages[0] " ) << options::visuals::world::color_storages.r << std::endl;
	cfg_file << xs( "color_storages[1] " ) << options::visuals::world::color_storages.g << std::endl;
	cfg_file << xs( "color_storages[2] " ) << options::visuals::world::color_storages.b << std::endl;

	cfg_file << xs( "color_vehicles[0] " ) << options::visuals::world::color_vehicles.r << std::endl;
	cfg_file << xs( "color_vehicles[1] " ) << options::visuals::world::color_vehicles.g << std::endl;
	cfg_file << xs( "color_vehicles[2] " ) << options::visuals::world::color_vehicles.b << std::endl;

	cfg_file << xs( "color_raid[0] " ) << options::visuals::world::color_raid.r << std::endl;
	cfg_file << xs( "color_raid[1] " ) << options::visuals::world::color_raid.g << std::endl;
	cfg_file << xs( "color_raid[2] " ) << options::visuals::world::color_raid.b << std::endl;

	cfg_file << xs( "color_item[0] " ) << options::visuals::world::color_item.r << std::endl;
	cfg_file << xs( "color_item[1] " ) << options::visuals::world::color_item.g << std::endl;
	cfg_file << xs( "color_item[2] " ) << options::visuals::world::color_item.b << std::endl;

	cfg_file << xs( "color_respawn_points[0] " ) << options::visuals::world::color_respawn_points.r << std::endl;
	cfg_file << xs( "color_respawn_points[1] " ) << options::visuals::world::color_respawn_points.g << std::endl;
	cfg_file << xs( "color_respawn_points[2] " ) << options::visuals::world::color_respawn_points.b << std::endl;

	cfg_file << xs( "color_chickens[0] " ) << options::visuals::world::color_chickens.r << std::endl;
	cfg_file << xs( "color_chickens[1] " ) << options::visuals::world::color_chickens.g << std::endl;
	cfg_file << xs( "color_chickens[2] " ) << options::visuals::world::color_chickens.b << std::endl;

	cfg_file << xs( "color_helicopter[0] " ) << options::visuals::world::color_helicopter.r << std::endl;
	cfg_file << xs( "color_helicopter[1] " ) << options::visuals::world::color_helicopter.g << std::endl;
	cfg_file << xs( "color_helicopter[2] " ) << options::visuals::world::color_helicopter.b << std::endl;

	cfg_file << xs( "color_ores[0] " ) << options::visuals::world::color_ores.r << std::endl;
	cfg_file << xs( "color_ores[1] " ) << options::visuals::world::color_ores.g << std::endl;
	cfg_file << xs( "color_ores[2] " ) << options::visuals::world::color_ores.b << std::endl;

	cfg_file << xs( "color_sulfur_ore[0] " ) << options::visuals::world::color_sulfur_ore.r << std::endl;
	cfg_file << xs( "color_sulfur_ore[1] " ) << options::visuals::world::color_sulfur_ore.g << std::endl;
	cfg_file << xs( "color_sulfur_ore[2] " ) << options::visuals::world::color_sulfur_ore.b << std::endl;

	cfg_file << xs( "color_metal_ore[0] " ) << options::visuals::world::color_metal_ore.r << std::endl;
	cfg_file << xs( "color_metal_ore[1] " ) << options::visuals::world::color_metal_ore.g << std::endl;
	cfg_file << xs( "color_metal_ore[2] " ) << options::visuals::world::color_metal_ore.b << std::endl;

	cfg_file << xs( "color_stone_ore[0] " ) << options::visuals::world::color_stone_ore.r << std::endl;
	cfg_file << xs( "color_stone_ore[1] " ) << options::visuals::world::color_stone_ore.g << std::endl;
	cfg_file << xs( "color_stone_ore[2] " ) << options::visuals::world::color_stone_ore.b << std::endl;

	cfg_file << xs( "color_tool_cupboard[0] " ) << options::visuals::world::color_tool_cupboard.r << std::endl;
	cfg_file << xs( "color_tool_cupboard[1] " ) << options::visuals::world::color_tool_cupboard.g << std::endl;
	cfg_file << xs( "color_tool_cupboard[2] " ) << options::visuals::world::color_tool_cupboard.b << std::endl;

	cfg_file << xs( "color_box_storages[0] " ) << options::visuals::world::color_box_storages.r << std::endl;
	cfg_file << xs( "color_box_storages[1] " ) << options::visuals::world::color_box_storages.g << std::endl;
	cfg_file << xs( "color_box_storages[2] " ) << options::visuals::world::color_box_storages.b << std::endl;

	cfg_file << xs( "color_ammo_nails_arrows[0] " ) << options::visuals::world::color_ammo_nails_arrows.r << std::endl;
	cfg_file << xs( "color_ammo_nails_arrows[1] " ) << options::visuals::world::color_ammo_nails_arrows.g << std::endl;
	cfg_file << xs( "color_ammo_nails_arrows[2] " ) << options::visuals::world::color_ammo_nails_arrows.b << std::endl;

	cfg_file << xs( "color_supply_signals[0] " ) << options::visuals::world::color_supply_signals.r << std::endl;
	cfg_file << xs( "color_supply_signals[1] " ) << options::visuals::world::color_supply_signals.g << std::endl;
	cfg_file << xs( "color_supply_signals[2] " ) << options::visuals::world::color_supply_signals.b << std::endl;

	cfg_file << xs( "color_supply_drops[0] " ) << options::visuals::world::color_supply_drops.r << std::endl;
	cfg_file << xs( "color_supply_drops[1] " ) << options::visuals::world::color_supply_drops.g << std::endl;
	cfg_file << xs( "color_supply_drops[2] " ) << options::visuals::world::color_supply_drops.b << std::endl;

	cfg_file << xs( "color_hemp[0] " ) << options::visuals::world::color_hemp.r << std::endl;
	cfg_file << xs( "color_hemp[1] " ) << options::visuals::world::color_hemp.g << std::endl;
	cfg_file << xs( "color_hemp[2] " ) << options::visuals::world::color_hemp.b << std::endl;

	cfg_file << xs( "color_mushroom[0] " ) << options::visuals::world::color_mushroom.r << std::endl;
	cfg_file << xs( "color_mushroom[1] " ) << options::visuals::world::color_mushroom.g << std::endl;
	cfg_file << xs( "color_mushroom[2] " ) << options::visuals::world::color_mushroom.b << std::endl;

	cfg_file << xs( "color_pumpkin[0] " ) << options::visuals::world::color_pumpkin.r << std::endl;
	cfg_file << xs( "color_pumpkin[1] " ) << options::visuals::world::color_pumpkin.g << std::endl;
	cfg_file << xs( "color_pumpkin[2] " ) << options::visuals::world::color_pumpkin.b << std::endl;

	cfg_file << xs( "color_berrys[0] " ) << options::visuals::world::color_berrys.r << std::endl;
	cfg_file << xs( "color_berrys[1] " ) << options::visuals::world::color_berrys.g << std::endl;
	cfg_file << xs( "color_berrys[2] " ) << options::visuals::world::color_berrys.b << std::endl;

	cfg_file << xs( "color_corns[0] " ) << options::visuals::world::color_corns.r << std::endl;
	cfg_file << xs( "color_corns[1] " ) << options::visuals::world::color_corns.g << std::endl;
	cfg_file << xs( "color_corns[2] " ) << options::visuals::world::color_corns.b << std::endl;

	cfg_file << xs( "color_potatos[0] " ) << options::visuals::world::color_potatos.r << std::endl;
	cfg_file << xs( "color_potatos[1] " ) << options::visuals::world::color_potatos.g << std::endl;
	cfg_file << xs( "color_potatos[2] " ) << options::visuals::world::color_potatos.b << std::endl;

	cfg_file << xs( "color_modular_car[0] " ) << options::visuals::world::color_modular_car.r << std::endl;
	cfg_file << xs( "color_modular_car[1] " ) << options::visuals::world::color_modular_car.g << std::endl;
	cfg_file << xs( "color_modular_car[2] " ) << options::visuals::world::color_modular_car.b << std::endl;

	cfg_file << xs( "color_two_modules_car[0] " ) << options::visuals::world::color_two_modules_car.r << std::endl;
	cfg_file << xs( "color_two_modules_car[1] " ) << options::visuals::world::color_two_modules_car.g << std::endl;
	cfg_file << xs( "color_two_modules_car[2] " ) << options::visuals::world::color_two_modules_car.b << std::endl;

	cfg_file << xs( "color_minicopter[0] " ) << options::visuals::world::color_minicopter.r << std::endl;
	cfg_file << xs( "color_minicopter[1] " ) << options::visuals::world::color_minicopter.g << std::endl;
	cfg_file << xs( "color_minicopter[2] " ) << options::visuals::world::color_minicopter.b << std::endl;

	cfg_file << xs( "color_scrap_helicopter[0] " ) << options::visuals::world::color_scrap_helicopter.r << std::endl;
	cfg_file << xs( "color_scrap_helicopter[1] " ) << options::visuals::world::color_scrap_helicopter.g << std::endl;
	cfg_file << xs( "color_scrap_helicopter[2] " ) << options::visuals::world::color_scrap_helicopter.b << std::endl;

	cfg_file << xs( "color_rhib[0] " ) << options::visuals::world::color_rhib.r << std::endl;
	cfg_file << xs( "color_rhib[1] " ) << options::visuals::world::color_rhib.g << std::endl;
	cfg_file << xs( "color_rhib[2] " ) << options::visuals::world::color_rhib.b << std::endl;

	cfg_file << xs( "color_bradley_apc[0] " ) << options::visuals::world::color_bradley_apc.r << std::endl;
	cfg_file << xs( "color_bradley_apc[1] " ) << options::visuals::world::color_bradley_apc.g << std::endl;
	cfg_file << xs( "color_bradley_apc[2] " ) << options::visuals::world::color_bradley_apc.b << std::endl;

	cfg_file << xs( "color_kayak[0] " ) << options::visuals::world::color_kayak.r << std::endl;
	cfg_file << xs( "color_kayak[1] " ) << options::visuals::world::color_kayak.g << std::endl;
	cfg_file << xs( "color_kayak[2] " ) << options::visuals::world::color_kayak.b << std::endl;

	cfg_file << xs( "color_small_motorboat[0] " ) << options::visuals::world::color_small_motorboat.r << std::endl;
	cfg_file << xs( "color_small_motorboat[1] " ) << options::visuals::world::color_small_motorboat.g << std::endl;
	cfg_file << xs( "color_small_motorboat[2] " ) << options::visuals::world::color_small_motorboat.b << std::endl;

	cfg_file << xs( "color_solo_submarine[0] " ) << options::visuals::world::color_solo_submarine.r << std::endl;
	cfg_file << xs( "color_solo_submarine[1] " ) << options::visuals::world::color_solo_submarine.g << std::endl;
	cfg_file << xs( "color_solo_submarine[2] " ) << options::visuals::world::color_solo_submarine.b << std::endl;

	cfg_file << xs( "color_duo_submarine[0] " ) << options::visuals::world::color_duo_submarine.r << std::endl;
	cfg_file << xs( "color_duo_submarine[1] " ) << options::visuals::world::color_duo_submarine.g << std::endl;
	cfg_file << xs( "color_duo_submarine[2] " ) << options::visuals::world::color_duo_submarine.b << std::endl;

	cfg_file << xs( "color_landmines[0] " ) << options::visuals::world::color_landmines.r << std::endl;
	cfg_file << xs( "color_landmines[1] " ) << options::visuals::world::color_landmines.g << std::endl;
	cfg_file << xs( "color_landmines[2] " ) << options::visuals::world::color_landmines.b << std::endl;

	cfg_file << xs( "color_npc_turrets[0] " ) << options::visuals::world::color_npc_turrets.r << std::endl;
	cfg_file << xs( "color_npc_turrets[1] " ) << options::visuals::world::color_npc_turrets.g << std::endl;
	cfg_file << xs( "color_npc_turrets[2] " ) << options::visuals::world::color_npc_turrets.b << std::endl;

	cfg_file << xs( "color_auto_turrets[0] " ) << options::visuals::world::color_auto_turrets.r << std::endl;
	cfg_file << xs( "color_auto_turrets[1] " ) << options::visuals::world::color_auto_turrets.g << std::endl;
	cfg_file << xs( "color_auto_turrets[2] " ) << options::visuals::world::color_auto_turrets.b << std::endl;

	cfg_file << xs( "color_shotgun_traps[0] " ) << options::visuals::world::color_shotgun_traps.r << std::endl;
	cfg_file << xs( "color_shotgun_traps[1] " ) << options::visuals::world::color_shotgun_traps.g << std::endl;
	cfg_file << xs( "color_shotgun_traps[2] " ) << options::visuals::world::color_shotgun_traps.b << std::endl;

	cfg_file << xs( "color_tesla_coil[0] " ) << options::visuals::world::color_tesla_coil.r << std::endl;
	cfg_file << xs( "color_tesla_coil[1] " ) << options::visuals::world::color_tesla_coil.g << std::endl;
	cfg_file << xs( "color_tesla_coil[2] " ) << options::visuals::world::color_tesla_coil.b << std::endl;

	cfg_file << xs( "color_flame_turrets[0] " ) << options::visuals::world::color_flame_turrets.r << std::endl;
	cfg_file << xs( "color_flame_turrets[1] " ) << options::visuals::world::color_flame_turrets.g << std::endl;
	cfg_file << xs( "color_flame_turrets[2] " ) << options::visuals::world::color_flame_turrets.b << std::endl;

	cfg_file << xs( "color_sam_site[0] " ) << options::visuals::world::color_sam_site.r << std::endl;
	cfg_file << xs( "color_sam_site[1] " ) << options::visuals::world::color_sam_site.g << std::endl;
	cfg_file << xs( "color_sam_site[2] " ) << options::visuals::world::color_sam_site.b << std::endl;

	cfg_file << xs( "color_land_spikes[0] " ) << options::visuals::world::color_land_spikes.r << std::endl;
	cfg_file << xs( "color_land_spikes[1] " ) << options::visuals::world::color_land_spikes.g << std::endl;
	cfg_file << xs( "color_land_spikes[2] " ) << options::visuals::world::color_land_spikes.b << std::endl;

	cfg_file << xs( "color_bear_trap[0] " ) << options::visuals::world::color_bear_trap.r << std::endl;
	cfg_file << xs( "color_bear_trap[1] " ) << options::visuals::world::color_bear_trap.g << std::endl;
	cfg_file << xs( "color_bear_trap[2] " ) << options::visuals::world::color_bear_trap.b << std::endl;

	cfg_file << xs( "color_oil_barrel[0] " ) << options::visuals::world::color_oil_barrel.r << std::endl;
	cfg_file << xs( "color_oil_barrel[1] " ) << options::visuals::world::color_oil_barrel.g << std::endl;
	cfg_file << xs( "color_oil_barrel[2] " ) << options::visuals::world::color_oil_barrel.b << std::endl;

	cfg_file << xs( "color_regular_barrels[0] " ) << options::visuals::world::color_regular_barrels.r << std::endl;
	cfg_file << xs( "color_regular_barrels[1] " ) << options::visuals::world::color_regular_barrels.g << std::endl;
	cfg_file << xs( "color_regular_barrels[2] " ) << options::visuals::world::color_regular_barrels.b << std::endl;

	cfg_file << xs( "color_underwater_crate[0] " ) << options::visuals::world::color_underwater_crate.r << std::endl;
	cfg_file << xs( "color_underwater_crate[1] " ) << options::visuals::world::color_underwater_crate.g << std::endl;
	cfg_file << xs( "color_underwater_crate[2] " ) << options::visuals::world::color_underwater_crate.b << std::endl;

	cfg_file << xs( "color_elite_crate[0] " ) << options::visuals::world::color_elite_crate.r << std::endl;
	cfg_file << xs( "color_elite_crate[1] " ) << options::visuals::world::color_elite_crate.g << std::endl;
	cfg_file << xs( "color_elite_crate[2] " ) << options::visuals::world::color_elite_crate.b << std::endl;

	cfg_file << xs( "color_military_crate[0] " ) << options::visuals::world::color_military_crate.r << std::endl;
	cfg_file << xs( "color_military_crate[1] " ) << options::visuals::world::color_military_crate.g << std::endl;
	cfg_file << xs( "color_military_crate[2] " ) << options::visuals::world::color_military_crate.b << std::endl;
	
	cfg_file << xs( "color_bradley_crate[0] " ) << options::visuals::world::color_bradley_crate.r << std::endl;
	cfg_file << xs( "color_bradley_crate[1] " ) << options::visuals::world::color_bradley_crate.g << std::endl;
	cfg_file << xs( "color_bradley_crate[2] " ) << options::visuals::world::color_bradley_crate.b << std::endl;

	cfg_file << xs( "color_food_crate[0] " ) << options::visuals::world::color_food_crate.r << std::endl;
	cfg_file << xs( "color_food_crate[1] " ) << options::visuals::world::color_food_crate.g << std::endl;
	cfg_file << xs( "color_food_crate[2] " ) << options::visuals::world::color_food_crate.b << std::endl;
	
	cfg_file << xs( "color_medical_crate[0] " ) << options::visuals::world::color_medical_crate.r << std::endl;
	cfg_file << xs( "color_medical_crate[1] " ) << options::visuals::world::color_medical_crate.g << std::endl;
	cfg_file << xs( "color_medical_crate[2] " ) << options::visuals::world::color_medical_crate.b << std::endl;

	cfg_file << xs( "color_diesel_fuel[0] " ) << options::visuals::world::color_diesel_fuel.r << std::endl;
	cfg_file << xs( "color_diesel_fuel[1] " ) << options::visuals::world::color_diesel_fuel.g << std::endl;
	cfg_file << xs( "color_diesel_fuel[2] " ) << options::visuals::world::color_diesel_fuel.b << std::endl;

	cfg_file << xs( "color_helicopter_crate[0] " ) << options::visuals::world::color_helicopter_crate.r << std::endl;
	cfg_file << xs( "color_helicopter_crate[1] " ) << options::visuals::world::color_helicopter_crate.g << std::endl;
	cfg_file << xs( "color_helicopter_crate[2] " ) << options::visuals::world::color_helicopter_crate.b << std::endl;

	cfg_file << xs( "color_hackable_locked_crate[0] " ) << options::visuals::world::color_hackable_locked_crate.r << std::endl;
	cfg_file << xs( "color_hackable_locked_crate[1] " ) << options::visuals::world::color_hackable_locked_crate.g << std::endl;
	cfg_file << xs( "color_hackable_locked_crate[2] " ) << options::visuals::world::color_hackable_locked_crate.b << std::endl;

	cfg_file << xs( "color_normal_crate[0] " ) << options::visuals::world::color_normal_crate.r << std::endl;
	cfg_file << xs( "color_normal_crate[1] " ) << options::visuals::world::color_normal_crate.g << std::endl;
	cfg_file << xs( "color_normal_crate[2] " ) << options::visuals::world::color_normal_crate.b << std::endl;

	cfg_file << xs( "color_small_crate[0] " ) << options::visuals::world::color_small_crate.r << std::endl;
	cfg_file << xs( "color_small_crate[1] " ) << options::visuals::world::color_small_crate.g << std::endl;
	cfg_file << xs( "color_small_crate[2] " ) << options::visuals::world::color_small_crate.b << std::endl;

	cfg_file << xs( "color_mine_crate[0] " ) << options::visuals::world::color_mine_crate.r << std::endl;
	cfg_file << xs( "color_mine_crate[1] " ) << options::visuals::world::color_mine_crate.g << std::endl;
	cfg_file << xs( "color_mine_crate[2] " ) << options::visuals::world::color_mine_crate.b << std::endl;

	cfg_file << xs( "color_tool_box[0] " ) << options::visuals::world::color_tool_box.r << std::endl;
	cfg_file << xs( "color_tool_box[1] " ) << options::visuals::world::color_tool_box.g << std::endl;
	cfg_file << xs( "color_tool_box[2] " ) << options::visuals::world::color_tool_box.b << std::endl;

	cfg_file << xs( "color_boars[0] " ) << options::visuals::world::color_boars.r << std::endl;
	cfg_file << xs( "color_boars[1] " ) << options::visuals::world::color_boars.g << std::endl;
	cfg_file << xs( "color_boars[2] " ) << options::visuals::world::color_boars.b << std::endl;

	cfg_file << xs( "color_wolves[0] " ) << options::visuals::world::color_wolves.r << std::endl;
	cfg_file << xs( "color_wolves[1] " ) << options::visuals::world::color_wolves.g << std::endl;
	cfg_file << xs( "color_wolves[2] " ) << options::visuals::world::color_wolves.b << std::endl;

	cfg_file << xs( "color_horses[0] " ) << options::visuals::world::color_horses.r << std::endl;
	cfg_file << xs( "color_horses[1] " ) << options::visuals::world::color_horses.g << std::endl;
	cfg_file << xs( "color_horses[2] " ) << options::visuals::world::color_horses.b << std::endl;

	cfg_file << xs( "color_sharks[0] " ) << options::visuals::world::color_sharks.r << std::endl;
	cfg_file << xs( "color_sharks[1] " ) << options::visuals::world::color_sharks.g << std::endl;
	cfg_file << xs( "color_sharks[2] " ) << options::visuals::world::color_sharks.b << std::endl;

	cfg_file << xs( "color_deers[0] " ) << options::visuals::world::color_deers.r << std::endl;
	cfg_file << xs( "color_deers[1] " ) << options::visuals::world::color_deers.g << std::endl;
	cfg_file << xs( "color_deers[2] " ) << options::visuals::world::color_deers.b << std::endl;

	cfg_file << xs( "color_polar_bears[0] " ) << options::visuals::world::color_polar_bears.r << std::endl;
	cfg_file << xs( "color_polar_bears[1] " ) << options::visuals::world::color_polar_bears.g << std::endl;
	cfg_file << xs( "color_polar_bears[2] " ) << options::visuals::world::color_polar_bears.b << std::endl;

	cfg_file << xs( "color_bears[0] " ) << options::visuals::world::color_bears.r << std::endl;
	cfg_file << xs( "color_bears[1] " ) << options::visuals::world::color_bears.g << std::endl;
	cfg_file << xs( "color_bears[2] " ) << options::visuals::world::color_bears.b << std::endl;

	cfg_file << xs( "color_sulfur_collectibles[0] " ) << options::visuals::world::color_sulfur_collectibles.r << std::endl;
	cfg_file << xs( "color_sulfur_collectibles[1] " ) << options::visuals::world::color_sulfur_collectibles.g << std::endl;
	cfg_file << xs( "color_sulfur_collectibles[2] " ) << options::visuals::world::color_sulfur_collectibles.b << std::endl;

	cfg_file << xs( "color_drone[0]" ) << options::visuals::world::color_drone.r << std::endl;
	cfg_file << xs( "color_drone[1]" ) << options::visuals::world::color_drone.g << std::endl;
	cfg_file << xs( "color_drone[2]" ) << options::visuals::world::color_drone.b << std::endl;

	cfg_file << xs( "color_recycler[0]" ) << options::visuals::world::color_recycler.r << std::endl;
	cfg_file << xs( "color_recycler[1]" ) << options::visuals::world::color_recycler.g << std::endl;
	cfg_file << xs( "color_recycler[2]" ) << options::visuals::world::color_recycler.b << std::endl;

	cfg_file << xs( "color_metal_collectibles[0]" ) << options::visuals::world::color_metal_collectibles.r << std::endl;
	cfg_file << xs( "color_metal_collectibles[1]" ) << options::visuals::world::color_metal_collectibles.g << std::endl;
	cfg_file << xs( "color_metal_collectibles[2]" ) << options::visuals::world::color_metal_collectibles.b << std::endl;

	cfg_file << xs( "color_wood_collectibles[0]" ) << options::visuals::world::color_wood_collectibles.r << std::endl;
	cfg_file << xs( "color_wood_collectibles[1]" ) << options::visuals::world::color_wood_collectibles.g << std::endl;
	cfg_file << xs( "color_wood_collectibles[2]" ) << options::visuals::world::color_wood_collectibles.b << std::endl;

	cfg_file << xs( "color_stone_collectibles[0]" ) << options::visuals::world::color_stone_collectibles.r << std::endl;
	cfg_file << xs( "color_stone_collectibles[1]" ) << options::visuals::world::color_stone_collectibles.g << std::endl;
	cfg_file << xs( "color_stone_collectibles[2]" ) << options::visuals::world::color_stone_collectibles.b << std::endl;

	cfg_file << xs( "color_vending_machine[0]" ) << options::visuals::world::color_vending_machine.r << std::endl;
	cfg_file << xs( "color_vending_machine[1]" ) << options::visuals::world::color_vending_machine.g << std::endl;
	cfg_file << xs( "color_vending_machine[2]" ) << options::visuals::world::color_vending_machine.b << std::endl;

	cfg_file << xs( "chams_color[0] " ) << options::visuals::chams_color.r << std::endl;
	cfg_file << xs( "chams_color[1] " ) << options::visuals::chams_color.g << std::endl;
	cfg_file << xs( "chams_color[2] " ) << options::visuals::chams_color.b << std::endl;

	cfg_file << xs( "font_flags " ) << options::font_flags << std::endl;

	cfg_file << xs( "health_thickness " ) << options::visuals::health_thickness << std::endl;

	cfg_file << xs( "chams_visible[0] " ) << options::visuals::chams_visible.r << std::endl;
	cfg_file << xs( "chams_visible[1] " ) << options::visuals::chams_visible.g << std::endl;
	cfg_file << xs( "chams_visible[2] " ) << options::visuals::chams_visible.b << std::endl;

	cfg_file << xs( "target_line_color[0] " ) << options::aimbot::target_line_color.r << std::endl;
	cfg_file << xs( "target_line_color[1] " ) << options::aimbot::target_line_color.g << std::endl;
	cfg_file << xs( "target_line_color[2] " ) << options::aimbot::target_line_color.b << std::endl;

	cfg_file << xs( "fov_circle_color[0] " ) << options::aimbot::fov_circle_color.r << std::endl;
	cfg_file << xs( "fov_circle_color[1] " ) << options::aimbot::fov_circle_color.g << std::endl;
	cfg_file << xs( "fov_circle_color[2] " ) << options::aimbot::fov_circle_color.b << std::endl;

	cfg_file << xs( "npc_vis_name_color[0] " ) << options::visuals::npc_vis_name_color.r << std::endl;
	cfg_file << xs( "npc_vis_name_color[1] " ) << options::visuals::npc_vis_name_color.g << std::endl;
	cfg_file << xs( "npc_vis_name_color[2] " ) << options::visuals::npc_vis_name_color.b << std::endl;

	cfg_file << xs( "npc_vis_skeleton_color[0] " ) << options::visuals::npc_vis_skeleton_color.r << std::endl;
	cfg_file << xs( "npc_vis_skeleton_color[1] " ) << options::visuals::npc_vis_skeleton_color.g << std::endl;
	cfg_file << xs( "npc_vis_skeleton_color[2] " ) << options::visuals::npc_vis_skeleton_color.b << std::endl;

	cfg_file << xs( "npc_vis_box_color[0] " ) << options::visuals::npc_vis_box_color.r << std::endl;
	cfg_file << xs( "npc_vis_box_color[1] " ) << options::visuals::npc_vis_box_color.g << std::endl;
	cfg_file << xs( "npc_vis_box_color[2] " ) << options::visuals::npc_vis_box_color.b << std::endl;

	cfg_file << xs( "npc_vis_radar_color[0] " ) << options::visuals::npc_vis_radar_color.r << std::endl;
	cfg_file << xs( "npc_vis_radar_color[1] " ) << options::visuals::npc_vis_radar_color.g << std::endl;
	cfg_file << xs( "npc_vis_radar_color[2] " ) << options::visuals::npc_vis_radar_color.b << std::endl;

	cfg_file << xs( "npc_vis_oof_color[0] " ) << options::visuals::npc_vis_oof_color.r << std::endl;
	cfg_file << xs( "npc_vis_oof_color[1] " ) << options::visuals::npc_vis_oof_color.g << std::endl;
	cfg_file << xs( "npc_vis_oof_color[2] " ) << options::visuals::npc_vis_oof_color.b << std::endl;

	cfg_file << xs( "npc_vis_ducking_color[0] " ) << options::visuals::npc_vis_ducking_color.r << std::endl;
	cfg_file << xs( "npc_vis_ducking_color[1] " ) << options::visuals::npc_vis_ducking_color.g << std::endl;
	cfg_file << xs( "npc_vis_ducking_color[2] " ) << options::visuals::npc_vis_ducking_color.b << std::endl;

	cfg_file << xs( "npc_vis_knocked_color[0] " ) << options::visuals::npc_vis_knocked_color.r << std::endl;
	cfg_file << xs( "npc_vis_knocked_color[1] " ) << options::visuals::npc_vis_knocked_color.g << std::endl;
	cfg_file << xs( "npc_vis_knocked_color[2] " ) << options::visuals::npc_vis_knocked_color.b << std::endl;

	cfg_file << xs( "npc_vis_snap_lines_color[0] " ) << options::visuals::npc_vis_snap_lines_color.r << std::endl;
	cfg_file << xs( "npc_vis_snap_lines_color[1] " ) << options::visuals::npc_vis_snap_lines_color.g << std::endl;
	cfg_file << xs( "npc_vis_snap_lines_color[2] " ) << options::visuals::npc_vis_snap_lines_color.b << std::endl;

	cfg_file << xs( "npc_vis_view_direction_color[0] " ) << options::visuals::npc_vis_view_direction_color.r << std::endl;
	cfg_file << xs( "npc_vis_view_direction_color[1] " ) << options::visuals::npc_vis_view_direction_color.g << std::endl;
	cfg_file << xs( "npc_vis_view_direction_color[2] " ) << options::visuals::npc_vis_view_direction_color.b << std::endl;

	cfg_file << xs( "npc_name_color[0] " ) << options::visuals::npc_name_color.r << std::endl;
	cfg_file << xs( "npc_name_color[1] " ) << options::visuals::npc_name_color.g << std::endl;
	cfg_file << xs( "npc_name_color[2] " ) << options::visuals::npc_name_color.b << std::endl;

	cfg_file << xs( "npc_skeleton_color[0] " ) << options::visuals::npc_skeleton_color.r << std::endl;
	cfg_file << xs( "npc_skeleton_color[1] " ) << options::visuals::npc_skeleton_color.g << std::endl;
	cfg_file << xs( "npc_skeleton_color[2] " ) << options::visuals::npc_skeleton_color.b << std::endl;

	cfg_file << xs( "npc_box_color[0] " ) << options::visuals::npc_box_color.r << std::endl;
	cfg_file << xs( "npc_box_color[1] " ) << options::visuals::npc_box_color.g << std::endl;
	cfg_file << xs( "npc_box_color[2] " ) << options::visuals::npc_box_color.b << std::endl;

	cfg_file << xs( "npc_radar_color[0] " ) << options::visuals::npc_radar_color.r << std::endl;
	cfg_file << xs( "npc_radar_color[1] " ) << options::visuals::npc_radar_color.g << std::endl;
	cfg_file << xs( "npc_radar_color[2] " ) << options::visuals::npc_radar_color.b << std::endl;

	cfg_file << xs( "npc_oof_color[0] " ) << options::visuals::npc_oof_color.r << std::endl;
	cfg_file << xs( "npc_oof_color[1] " ) << options::visuals::npc_oof_color.g << std::endl;
	cfg_file << xs( "npc_oof_color[2] " ) << options::visuals::npc_oof_color.b << std::endl;

	cfg_file << xs( "npc_ducking_color[0] " ) << options::visuals::npc_ducking_color.r << std::endl;
	cfg_file << xs( "npc_ducking_color[1] " ) << options::visuals::npc_ducking_color.g << std::endl;
	cfg_file << xs( "npc_ducking_color[2] " ) << options::visuals::npc_ducking_color.b << std::endl;

	cfg_file << xs( "npc_knocked_color[0] " ) << options::visuals::npc_knocked_color.r << std::endl;
	cfg_file << xs( "npc_knocked_color[1] " ) << options::visuals::npc_knocked_color.g << std::endl;
	cfg_file << xs( "npc_knocked_color[2] " ) << options::visuals::npc_knocked_color.b << std::endl;

	cfg_file << xs( "npc_snap_lines_color[0] " ) << options::visuals::npc_snap_lines_color.r << std::endl;
	cfg_file << xs( "npc_snap_lines_color[1] " ) << options::visuals::npc_snap_lines_color.g << std::endl;
	cfg_file << xs( "npc_snap_lines_color[2] " ) << options::visuals::npc_snap_lines_color.b << std::endl;

	cfg_file << xs( "npc_view_direction_color[0] " ) << options::visuals::npc_view_direction_color.r << std::endl;
	cfg_file << xs( "npc_view_direction_color[1] " ) << options::visuals::npc_view_direction_color.g << std::endl;
	cfg_file << xs( "npc_view_direction_color[2] " ) << options::visuals::npc_view_direction_color.b << std::endl;

	cfg_file << xs( "vis_name_color[0] " ) << options::visuals::vis_name_color.r << std::endl;
	cfg_file << xs( "vis_name_color[1] " ) << options::visuals::vis_name_color.g << std::endl;
	cfg_file << xs( "vis_name_color[2] " ) << options::visuals::vis_name_color.b << std::endl;

	cfg_file << xs( "vis_skeleton_color[0] " ) << options::visuals::vis_skeleton_color.r << std::endl;
	cfg_file << xs( "vis_skeleton_color[1] " ) << options::visuals::vis_skeleton_color.g << std::endl;
	cfg_file << xs( "vis_skeleton_color[2] " ) << options::visuals::vis_skeleton_color.b << std::endl;

	cfg_file << xs( "vis_box_color[0] " ) << options::visuals::vis_box_color.r << std::endl;
	cfg_file << xs( "vis_box_color[1] " ) << options::visuals::vis_box_color.g << std::endl;
	cfg_file << xs( "vis_box_color[2] " ) << options::visuals::vis_box_color.b << std::endl;

	cfg_file << xs( "vis_radar_color[0] " ) << options::visuals::vis_radar_color.r << std::endl;
	cfg_file << xs( "vis_radar_color[1] " ) << options::visuals::vis_radar_color.g << std::endl;
	cfg_file << xs( "vis_radar_color[2] " ) << options::visuals::vis_radar_color.b << std::endl;

	cfg_file << xs( "vis_oof_color[0] " ) << options::visuals::vis_oof_color.r << std::endl;
	cfg_file << xs( "vis_oof_color[1] " ) << options::visuals::vis_oof_color.g << std::endl;
	cfg_file << xs( "vis_oof_color[2] " ) << options::visuals::vis_oof_color.b << std::endl;

	cfg_file << xs( "vis_distance_color[0] " ) << options::visuals::vis_distance_color.r << std::endl;
	cfg_file << xs( "vis_distance_color[1] " ) << options::visuals::vis_distance_color.g << std::endl;
	cfg_file << xs( "vis_distance_color[2] " ) << options::visuals::vis_distance_color.b << std::endl;

	cfg_file << xs( "vis_weapon_color[0] " ) << options::visuals::vis_weapon_color.r << std::endl;
	cfg_file << xs( "vis_weapon_color[1] " ) << options::visuals::vis_weapon_color.g << std::endl;
	cfg_file << xs( "vis_weapon_color[2] " ) << options::visuals::vis_weapon_color.b << std::endl;

	cfg_file << xs( "vis_ducking_color[0] " ) << options::visuals::vis_ducking_color.r << std::endl;
	cfg_file << xs( "vis_ducking_color[1] " ) << options::visuals::vis_ducking_color.g << std::endl;
	cfg_file << xs( "vis_ducking_color[2] " ) << options::visuals::vis_ducking_color.b << std::endl;

	cfg_file << xs( "vis_knocked_color[0] " ) << options::visuals::vis_knocked_color.r << std::endl;
	cfg_file << xs( "vis_knocked_color[1] " ) << options::visuals::vis_knocked_color.g << std::endl;
	cfg_file << xs( "vis_knocked_color[2] " ) << options::visuals::vis_knocked_color.b << std::endl;

	cfg_file << xs( "vis_snap_lines_color[0] " ) << options::visuals::vis_snap_lines_color.r << std::endl;
	cfg_file << xs( "vis_snap_lines_color[1] " ) << options::visuals::vis_snap_lines_color.g << std::endl;
	cfg_file << xs( "vis_snap_lines_color[2] " ) << options::visuals::vis_snap_lines_color.b << std::endl;

	cfg_file << xs( "vis_view_direction_color[0] " ) << options::visuals::vis_view_direction_color.r << std::endl;
	cfg_file << xs( "vis_view_direction_color[1] " ) << options::visuals::vis_view_direction_color.g << std::endl;
	cfg_file << xs( "vis_view_direction_color[2] " ) << options::visuals::vis_view_direction_color.b << std::endl;

	cfg_file << xs( "name_color[0] " ) << options::visuals::name_color.r << std::endl;
	cfg_file << xs( "name_color[1] " ) << options::visuals::name_color.g << std::endl;
	cfg_file << xs( "name_color[2] " ) << options::visuals::name_color.b << std::endl;

	cfg_file << xs( "tracers_color[0] " ) << options::visuals::tracers_color.r << std::endl;
	cfg_file << xs( "tracers_color[1] " ) << options::visuals::tracers_color.g << std::endl;
	cfg_file << xs( "tracers_color[2] " ) << options::visuals::tracers_color.b << std::endl;

	cfg_file << xs( "desync_bar_color[0] " ) << options::visuals::desync_bar_color.r << std::endl;
	cfg_file << xs( "desync_bar_color[1] " ) << options::visuals::desync_bar_color.g << std::endl;
	cfg_file << xs( "desync_bar_color[2] " ) << options::visuals::desync_bar_color.b << std::endl;

	cfg_file << xs( "reload_bar_color[0] " ) << options::visuals::reload_bar_color.r << std::endl;
	cfg_file << xs( "reload_bar_color[1] " ) << options::visuals::reload_bar_color.g << std::endl;
	cfg_file << xs( "reload_bar_color[2] " ) << options::visuals::reload_bar_color.b << std::endl;

	cfg_file << xs( "trails_color[0] " ) << options::visuals::trails_color.r << std::endl;
	cfg_file << xs( "trails_color[1] " ) << options::visuals::trails_color.g << std::endl;
	cfg_file << xs( "trails_color[2] " ) << options::visuals::trails_color.b << std::endl;

	cfg_file << xs( "reload_bar_color[0] " ) << options::visuals::reload_bar_color.r << std::endl;
	cfg_file << xs( "reload_bar_color[1] " ) << options::visuals::reload_bar_color.g << std::endl;
	cfg_file << xs( "reload_bar_color[2] " ) << options::visuals::reload_bar_color.b << std::endl;

	cfg_file << xs( "skeleton_color[0] " ) << options::visuals::skeleton_color.r << std::endl;
	cfg_file << xs( "skeleton_color[1] " ) << options::visuals::skeleton_color.g << std::endl;
	cfg_file << xs( "skeleton_color[2] " ) << options::visuals::skeleton_color.b << std::endl;

	cfg_file << xs( "box_color[0] " ) << options::visuals::box_color.r << std::endl;
	cfg_file << xs( "box_color[1] " ) << options::visuals::box_color.g << std::endl;
	cfg_file << xs( "box_color[2] " ) << options::visuals::box_color.b << std::endl;

	cfg_file << xs( "radar_color[0] " ) << options::visuals::radar_color.r << std::endl;
	cfg_file << xs( "radar_color[1] " ) << options::visuals::radar_color.g << std::endl;
	cfg_file << xs( "radar_color[2] " ) << options::visuals::radar_color.b << std::endl;

	cfg_file << xs( "oof_color[0] " ) << options::visuals::oof_color.r << std::endl;
	cfg_file << xs( "oof_color[1] " ) << options::visuals::oof_color.g << std::endl;
	cfg_file << xs( "oof_color[2] " ) << options::visuals::oof_color.b << std::endl;

	cfg_file << xs( "snap_lines_color[0] " ) << options::visuals::snap_lines_color.r << std::endl;
	cfg_file << xs( "snap_lines_color[1] " ) << options::visuals::snap_lines_color.g << std::endl;
	cfg_file << xs( "snap_lines_color[2] " ) << options::visuals::snap_lines_color.b << std::endl;

	cfg_file << xs( "view_direction_color[0] " ) << options::visuals::view_direction_color.r << std::endl;
	cfg_file << xs( "view_direction_color[1] " ) << options::visuals::view_direction_color.g << std::endl;
	cfg_file << xs( "view_direction_color[2] " ) << options::visuals::view_direction_color.b << std::endl;

	cfg_file << xs( "accent_color[0] " ) << options::accent_color.r << std::endl;
	cfg_file << xs( "accent_color[1] " ) << options::accent_color.g << std::endl;
	cfg_file << xs( "accent_color[2] " ) << options::accent_color.b << std::endl;

	cfg_file << xs( "distance_color[0] " ) << options::visuals::distance_color.r << std::endl;
	cfg_file << xs( "distance_color[1] " ) << options::visuals::distance_color.g << std::endl;
	cfg_file << xs( "distance_color[2] " ) << options::visuals::distance_color.b << std::endl;

	cfg_file << xs( "weapon_color[0] " ) << options::visuals::weapon_color.r << std::endl;
	cfg_file << xs( "weapon_color[1] " ) << options::visuals::weapon_color.g << std::endl;
	cfg_file << xs( "weapon_color[2] " ) << options::visuals::weapon_color.b << std::endl;

	cfg_file << xs( "health_text_color[0] " ) << options::visuals::health_text_color.r << std::endl;
	cfg_file << xs( "health_text_color[1] " ) << options::visuals::health_text_color.g << std::endl;
	cfg_file << xs( "health_text_color[2] " ) << options::visuals::health_text_color.b << std::endl;

	cfg_file << xs( "custom_health_color[0] " ) << options::visuals::custom_health_color.r << std::endl;
	cfg_file << xs( "custom_health_color[1] " ) << options::visuals::custom_health_color.g << std::endl;
	cfg_file << xs( "custom_health_color[2] " ) << options::visuals::custom_health_color.b << std::endl;

	cfg_file << xs( "modify_health_color " ) << options::visuals::modify_health_color << std::endl;

	cfg_file << xs( "modify_rain " ) << options::visuals::world::modify_rain << std::endl;
	cfg_file << xs( "rain_amount " ) << options::visuals::world::rain_amount << std::endl;

	cfg_file << xs( "aim_key " ) << g_aimbot.aim_key << std::endl;

	cfg_file.close( );
	std::cout << xs( "saved file with name: " ) << filename << std::endl;
	options::save_cfg = false;
}

void c_cfg_sys::load_cfg( const std::string& filename ) {
	std::ifstream cfg_file( filename );
	if( !cfg_file.is_open( ) ) {
		std::cout << xs( "can't open file with name: " ) << filename << std::endl;
		return;
	}

	std::string line;
	while ( std::getline( cfg_file, line ) ) {
		std::istringstream string_str( line );
		std::string feature_name;	
		if( string_str >> feature_name ) {
			if( feature_name == xs( "rainbow_accent" ) ) string_str >> options::rainbow_accent;

			if( feature_name == xs( "aim_check" ) ) string_str >> options::aimbot::aim_check;
			if( feature_name == xs( "smoothness" ) ) string_str >> options::aimbot::smoothness;
			if( feature_name == xs( "auto_fire" ) ) string_str >> options::aimbot::auto_fire;
			if( feature_name == xs( "should_simulate_movement" ) ) string_str >> options::aimbot::should_simulate_movement;
			if( feature_name == xs( "draw_fov" ) ) string_str >> options::aimbot::draw_fov;
			if( feature_name == xs( "draw_crosshair" ) ) string_str >> options::aimbot::draw_crosshair;
			if( feature_name == xs( "draw_target" ) ) string_str >> options::aimbot::draw_target;
			if( feature_name == xs( "aim_npc" ) ) string_str >> options::aimbot::aim_npc;

			if( feature_name == xs( "target_line_color[0]" ) ) string_str >> options::aimbot::target_line_color.r;
			if( feature_name == xs( "target_line_color[1]" ) ) string_str >> options::aimbot::target_line_color.g;
			if( feature_name == xs( "target_line_color[2]" ) ) string_str >> options::aimbot::target_line_color.b;

			if( feature_name == xs( "fov_circle_color[0]" ) ) string_str >> options::aimbot::fov_circle_color.r;
			if( feature_name == xs( "fov_circle_color[1]" ) ) string_str >> options::aimbot::fov_circle_color.g;
			if( feature_name == xs( "fov_circle_color[2]" ) ) string_str >> options::aimbot::fov_circle_color.b;

			if( feature_name == xs( "vis_name_color[0]" ) ) string_str >> options::visuals::vis_name_color.r;
			if( feature_name == xs( "vis_name_color[1]" ) ) string_str >> options::visuals::vis_name_color.g;
			if( feature_name == xs( "vis_name_color[2]" ) ) string_str >> options::visuals::vis_name_color.b;

			if( feature_name == xs( "vis_skeleton_color[0]" ) ) string_str >> options::visuals::vis_skeleton_color.r;
			if( feature_name == xs( "vis_skeleton_color[1]" ) ) string_str >> options::visuals::vis_skeleton_color.g;
			if( feature_name == xs( "vis_skeleton_color[2]" ) ) string_str >> options::visuals::vis_skeleton_color.b;

			if( feature_name == xs( "vis_box_color[0]" ) ) string_str >> options::visuals::vis_box_color.r;
			if( feature_name == xs( "vis_box_color[1]" ) ) string_str >> options::visuals::vis_box_color.g;
			if( feature_name == xs( "vis_box_color[2]" ) ) string_str >> options::visuals::vis_box_color.b;

			if( feature_name == xs( "vis_radar_color[0]" ) ) string_str >> options::visuals::vis_radar_color.r;
			if( feature_name == xs( "vis_radar_color[1]" ) ) string_str >> options::visuals::vis_radar_color.g;
			if( feature_name == xs( "vis_radar_color[2]" ) ) string_str >> options::visuals::vis_radar_color.b;

			if( feature_name == xs( "vis_oof_color[0]" ) ) string_str >> options::visuals::vis_oof_color.r;
			if( feature_name == xs( "vis_oof_color[1]" ) ) string_str >> options::visuals::vis_oof_color.g;
			if( feature_name == xs( "vis_oof_color[2]" ) ) string_str >> options::visuals::vis_oof_color.b;

			if( feature_name == xs( "vis_ducking_color[0]" ) ) string_str >> options::visuals::vis_ducking_color.r;
			if( feature_name == xs( "vis_ducking_color[1]" ) ) string_str >> options::visuals::vis_ducking_color.g;
			if( feature_name == xs( "vis_ducking_color[2]" ) ) string_str >> options::visuals::vis_ducking_color.b;

			if( feature_name == xs( "vis_knocked_color[0]" ) ) string_str >> options::visuals::vis_knocked_color.r;
			if( feature_name == xs( "vis_knocked_color[1]" ) ) string_str >> options::visuals::vis_knocked_color.g;
			if( feature_name == xs( "vis_knocked_color[2]" ) ) string_str >> options::visuals::vis_knocked_color.b;

			if( feature_name == xs( "vis_snap_lines_color[0]" ) ) string_str >> options::visuals::vis_snap_lines_color.r;
			if( feature_name == xs( "vis_snap_lines_color[1]" ) ) string_str >> options::visuals::vis_snap_lines_color.g;
			if( feature_name == xs( "vis_snap_lines_color[2]" ) ) string_str >> options::visuals::vis_snap_lines_color.b;

			if( feature_name == xs( "vis_view_direction_color[0]" ) ) string_str >> options::visuals::vis_view_direction_color.r;
			if( feature_name == xs( "vis_view_direction_color[1]" ) ) string_str >> options::visuals::vis_view_direction_color.g;
			if( feature_name == xs( "vis_view_direction_color[2]" ) ) string_str >> options::visuals::vis_view_direction_color.b;

			if( feature_name == xs( "npc_vis_name_color[0]" ) ) string_str >> options::visuals::npc_vis_name_color.r;
			if( feature_name == xs( "npc_vis_name_color[1]" ) ) string_str >> options::visuals::npc_vis_name_color.g;
			if( feature_name == xs( "npc_vis_name_color[2]" ) ) string_str >> options::visuals::npc_vis_name_color.b;

			if( feature_name == xs( "npc_vis_skeleton_color[0]" ) ) string_str >> options::visuals::npc_vis_skeleton_color.r;
			if( feature_name == xs( "npc_vis_skeleton_color[1]" ) ) string_str >> options::visuals::npc_vis_skeleton_color.g;
			if( feature_name == xs( "npc_vis_skeleton_color[2]" ) ) string_str >> options::visuals::npc_vis_skeleton_color.b;

			if( feature_name == xs( "npc_vis_box_color[0]" ) ) string_str >> options::visuals::npc_vis_box_color.r;
			if( feature_name == xs( "npc_vis_box_color[1]" ) ) string_str >> options::visuals::npc_vis_box_color.g;
			if( feature_name == xs( "npc_vis_box_color[2]" ) ) string_str >> options::visuals::npc_vis_box_color.b;

			if( feature_name == xs( "npc_vis_radar_color[0]" ) ) string_str >> options::visuals::npc_vis_radar_color.r;
			if( feature_name == xs( "npc_vis_radar_color[1]" ) ) string_str >> options::visuals::npc_vis_radar_color.g;
			if( feature_name == xs( "npc_vis_radar_color[2]" ) ) string_str >> options::visuals::npc_vis_radar_color.b;

			if( feature_name == xs( "npc_vis_oof_color[0]" ) ) string_str >> options::visuals::npc_vis_oof_color.r;
			if( feature_name == xs( "npc_vis_oof_color[1]" ) ) string_str >> options::visuals::npc_vis_oof_color.g;
			if( feature_name == xs( "npc_vis_oof_color[2]" ) ) string_str >> options::visuals::npc_vis_oof_color.b;

			if( feature_name == xs( "npc_vis_ducking_color[0]" ) ) string_str >> options::visuals::npc_vis_ducking_color.r;
			if( feature_name == xs( "npc_vis_ducking_color[1]" ) ) string_str >> options::visuals::npc_vis_ducking_color.g;
			if( feature_name == xs( "npc_vis_ducking_color[2]" ) ) string_str >> options::visuals::npc_vis_ducking_color.b;

			if( feature_name == xs( "npc_vis_knocked_color[0]" ) ) string_str >> options::visuals::npc_vis_knocked_color.r;
			if( feature_name == xs( "npc_vis_knocked_color[1]" ) ) string_str >> options::visuals::npc_vis_knocked_color.g;
			if( feature_name == xs( "npc_vis_knocked_color[2]" ) ) string_str >> options::visuals::npc_vis_knocked_color.b;

			if( feature_name == xs( "npc_vis_snap_lines_color[0]" ) ) string_str >> options::visuals::npc_vis_snap_lines_color.r;
			if( feature_name == xs( "npc_vis_snap_lines_color[1]" ) ) string_str >> options::visuals::npc_vis_snap_lines_color.g;
			if( feature_name == xs( "npc_vis_snap_lines_color[2]" ) ) string_str >> options::visuals::npc_vis_snap_lines_color.b;

			if( feature_name == xs( "npc_vis_view_direction_color[0]" ) ) string_str >> options::visuals::npc_vis_view_direction_color.r;
			if( feature_name == xs( "npc_vis_view_direction_color[1]" ) ) string_str >> options::visuals::npc_vis_view_direction_color.g;
			if( feature_name == xs( "npc_vis_view_direction_color[2]" ) ) string_str >> options::visuals::npc_vis_view_direction_color.b;

			if( feature_name == xs( "npc_name_color[0]" ) ) string_str >> options::visuals::npc_name_color.r;
			if( feature_name == xs( "npc_name_color[1]" ) ) string_str >> options::visuals::npc_name_color.g;
			if( feature_name == xs( "npc_name_color[2]" ) ) string_str >> options::visuals::npc_name_color.b;

			if( feature_name == xs( "npc_skeleton_color[0]" ) ) string_str >> options::visuals::npc_skeleton_color.r;
			if( feature_name == xs( "npc_skeleton_color[1]" ) ) string_str >> options::visuals::npc_skeleton_color.g;
			if( feature_name == xs( "npc_skeleton_color[2]" ) ) string_str >> options::visuals::npc_skeleton_color.b;

			if( feature_name == xs( "npc_box_color[0]" ) ) string_str >> options::visuals::npc_box_color.r;
			if( feature_name == xs( "npc_box_color[1]" ) ) string_str >> options::visuals::npc_box_color.g;
			if( feature_name == xs( "npc_box_color[2]" ) ) string_str >> options::visuals::npc_box_color.b;

			if( feature_name == xs( "npc_radar_color[0]" ) ) string_str >> options::visuals::npc_radar_color.r;
			if( feature_name == xs( "npc_radar_color[1]" ) ) string_str >> options::visuals::npc_radar_color.g;
			if( feature_name == xs( "npc_radar_color[2]" ) ) string_str >> options::visuals::npc_radar_color.b;

			if( feature_name == xs( "npc_oof_color[0]" ) ) string_str >> options::visuals::npc_oof_color.r;
			if( feature_name == xs( "npc_oof_color[1]" ) ) string_str >> options::visuals::npc_oof_color.g;
			if( feature_name == xs( "npc_oof_color[2]" ) ) string_str >> options::visuals::npc_oof_color.b;

			if( feature_name == xs( "npc_ducking_color[0]" ) ) string_str >> options::visuals::npc_ducking_color.r;
			if( feature_name == xs( "npc_ducking_color[1]" ) ) string_str >> options::visuals::npc_ducking_color.g;
			if( feature_name == xs( "npc_ducking_color[2]" ) ) string_str >> options::visuals::npc_ducking_color.b;

			if( feature_name == xs( "npc_knocked_color[0]" ) ) string_str >> options::visuals::npc_knocked_color.r;
			if( feature_name == xs( "npc_knocked_color[1]" ) ) string_str >> options::visuals::npc_knocked_color.g;
			if( feature_name == xs( "npc_knocked_color[2]" ) ) string_str >> options::visuals::npc_knocked_color.b;

			if( feature_name == xs( "npc_snap_lines_color[0]" ) ) string_str >> options::visuals::npc_snap_lines_color.r;
			if( feature_name == xs( "npc_snap_lines_color[1]" ) ) string_str >> options::visuals::npc_snap_lines_color.g;
			if( feature_name == xs( "npc_snap_lines_color[2]" ) ) string_str >> options::visuals::npc_snap_lines_color.b;

			if( feature_name == xs( "npc_view_direction_color[0]" ) ) string_str >> options::visuals::npc_view_direction_color.r;
			if( feature_name == xs( "npc_view_direction_color[1]" ) ) string_str >> options::visuals::npc_view_direction_color.g;
			if( feature_name == xs( "npc_view_direction_color[2]" ) ) string_str >> options::visuals::npc_view_direction_color.b;

			if( feature_name == xs( "name_color[0]" ) ) string_str >> options::visuals::name_color.r;
			if( feature_name == xs( "name_color[1]" ) ) string_str >> options::visuals::name_color.g;
			if( feature_name == xs( "name_color[2]" ) ) string_str >> options::visuals::name_color.b;

			if( feature_name == xs( "tracers_color[0]" ) ) string_str >> options::visuals::tracers_color.r;
			if( feature_name == xs( "tracers_color[1]" ) ) string_str >> options::visuals::tracers_color.g;
			if( feature_name == xs( "tracers_color[2]" ) ) string_str >> options::visuals::tracers_color.b;

			if( feature_name == xs( "desync_bar_color[0]" ) ) string_str >> options::visuals::desync_bar_color.r;
			if( feature_name == xs( "desync_bar_color[1]" ) ) string_str >> options::visuals::desync_bar_color.g;
			if( feature_name == xs( "desync_bar_color[2]" ) ) string_str >> options::visuals::desync_bar_color.b;

			if( feature_name == xs( "reload_bar_color[0]" ) ) string_str >> options::visuals::reload_bar_color.r;
			if( feature_name == xs( "reload_bar_color[1]" ) ) string_str >> options::visuals::reload_bar_color.g;
			if( feature_name == xs( "reload_bar_color[2]" ) ) string_str >> options::visuals::reload_bar_color.b;

			if( feature_name == xs( "trails_color[0]" ) ) string_str >> options::visuals::trails_color.r;
			if( feature_name == xs( "trails_color[1]" ) ) string_str >> options::visuals::trails_color.g;
			if( feature_name == xs( "trails_color[2]" ) ) string_str >> options::visuals::trails_color.b;

			if( feature_name == xs( "reload_bar_color[0]" ) ) string_str >> options::visuals::reload_bar_color.r;
			if( feature_name == xs( "reload_bar_color[1]" ) ) string_str >> options::visuals::reload_bar_color.g;
			if( feature_name == xs( "reload_bar_color[2]" ) ) string_str >> options::visuals::reload_bar_color.b;

			if( feature_name == xs( "skeleton_color[0]" ) ) string_str >> options::visuals::skeleton_color.r;
			if( feature_name == xs( "skeleton_color[1]" ) ) string_str >> options::visuals::skeleton_color.g;
			if( feature_name == xs( "skeleton_color[2]" ) ) string_str >> options::visuals::skeleton_color.b;

			if( feature_name == xs( "box_color[0]" ) ) string_str >> options::visuals::box_color.r;
			if( feature_name == xs( "box_color[1]" ) ) string_str >> options::visuals::box_color.g;
			if( feature_name == xs( "box_color[2]" ) ) string_str >> options::visuals::box_color.b;

			if( feature_name == xs( "radar_color[0]" ) ) string_str >> options::visuals::radar_color.r;
			if( feature_name == xs( "radar_color[1]" ) ) string_str >> options::visuals::radar_color.g;
			if( feature_name == xs( "radar_color[2]" ) ) string_str >> options::visuals::radar_color.b;

			if( feature_name == xs( "oof_color[0]" ) ) string_str >> options::visuals::oof_color.r;
			if( feature_name == xs( "oof_color[1]" ) ) string_str >> options::visuals::oof_color.g;
			if( feature_name == xs( "oof_color[2]" ) ) string_str >> options::visuals::oof_color.b;

			if( feature_name == xs( "show_ducking_flag" ) ) string_str >> options::visuals::show_ducking_flag;
			if( feature_name == xs( "ducking_color[0]" ) ) string_str >> options::visuals::ducking_color.r;
			if( feature_name == xs( "ducking_color[1]" ) ) string_str >> options::visuals::ducking_color.g;
			if( feature_name == xs( "ducking_color[2]" ) ) string_str >> options::visuals::ducking_color.b;

			if( feature_name == xs( "show_knocked_flag" ) ) string_str >> options::visuals::show_knocked_flag;
			if( feature_name == xs( "knocked_color[0]" ) ) string_str >> options::visuals::knocked_color.r;
			if( feature_name == xs( "knocked_color[1]" ) ) string_str >> options::visuals::knocked_color.g;
			if( feature_name == xs( "knocked_color[2]" ) ) string_str >> options::visuals::knocked_color.b;

			if( feature_name == xs( "snap_lines_color[0]" ) ) string_str >> options::visuals::snap_lines_color.r;
			if( feature_name == xs( "snap_lines_color[1]" ) ) string_str >> options::visuals::snap_lines_color.g;
			if( feature_name == xs( "snap_lines_color[2]" ) ) string_str >> options::visuals::snap_lines_color.b;

			if( feature_name == xs( "view_direction_color[0]" ) ) string_str >> options::visuals::view_direction_color.r;
			if( feature_name == xs( "view_direction_color[1]" ) ) string_str >> options::visuals::view_direction_color.g;
			if( feature_name == xs( "view_direction_color[2]" ) ) string_str >> options::visuals::view_direction_color.b;

			if( feature_name == xs( "accent_color[0]" ) ) string_str >> options::accent_color.r;
			if( feature_name == xs( "accent_color[1]" ) ) string_str >> options::accent_color.g;
			if( feature_name == xs( "accent_color[2]" ) ) string_str >> options::accent_color.b;

			if( feature_name == xs( "aim_helicopter" ) ) string_str >> options::aimbot::aim_helicopter;
			if( feature_name == xs( "manipulation" ) ) string_str >> options::aimbot::manipulation;
			if( feature_name == xs( "kill_aura" ) ) string_str >> options::aimbot::kill_aura;
			if( feature_name == xs( "auto_reload" ) ) string_str >> options::aimbot::auto_reload;
			if( feature_name == xs( "aim_nearest_bone" ) ) string_str >> options::aimbot::aim_nearest_bone;

			if( feature_name == xs( "aim_bone" ) ) string_str >> options::aimbot::aim_bone;
			if( feature_name == xs( "manipulation_key" ) ) string_str >> options::aimbot::manipulation_key;
			if( feature_name == xs( "smooth_type" ) ) string_str >> options::aimbot::smooth_type;
			if( feature_name == xs( "max_target_distance" ) ) string_str >> options::aimbot::max_target_distance;
			if( feature_name == xs( "fov_amount" ) ) string_str >> options::aimbot::fov_amount;

			if( feature_name == xs( "smoothness_amount" ) ) string_str >> options::aimbot::smoothness_amount;

			if( feature_name == xs( "infinite_jump" ) ) string_str >> options::aimbot::exploits::movement::infinite_jump;
			if( feature_name == xs( "stopper_fly" ) ) string_str >> options::aimbot::exploits::movement::stopper_fly;
			if( feature_name == xs( "climb_assist" ) ) string_str >> options::aimbot::exploits::movement::climb_assist;
			if( feature_name == xs( "fly_hack" ) ) string_str >> options::aimbot::exploits::movement::fly_hack;
			if( feature_name == xs( "omni_sprint" ) ) string_str >> options::aimbot::exploits::movement::omni_sprint;
			if( feature_name == xs( "silent_walk" ) ) string_str >> options::aimbot::exploits::movement::silent_walk;
			if( feature_name == xs( "always_sprint" ) ) string_str >> options::aimbot::exploits::movement::always_sprint;
			if( feature_name == xs( "high_jump" ) ) string_str >> options::aimbot::exploits::movement::high_jump;

			if( feature_name == xs( "walk_through_players" ) ) string_str >> options::aimbot::exploits::movement::walk_through_players;
			if( feature_name == xs( "disable_slow_down_melee" ) ) string_str >> options::aimbot::exploits::movement::disable_slow_down_melee;
			if( feature_name == xs( "modify_clothing_speed" ) ) string_str >> options::aimbot::exploits::movement::modify_clothing_speed;
			if( feature_name == xs( "increase_height" ) ) string_str >> options::aimbot::exploits::movement::increase_height;

			if( feature_name == xs( "fly_key" ) ) string_str >> options::aimbot::exploits::movement::fly_key;
			if( feature_name == xs( "ignore_key" ) ) string_str >> options::aimbot::exploits::movement::ignore_key;
			if( feature_name == xs( "omni_sprint_key" ) ) string_str >> options::aimbot::exploits::movement::omni_sprint_key;
			if( feature_name == xs( "silent_walk_key" ) ) string_str >> options::aimbot::exploits::movement::silent_walk_key;
			if( feature_name == xs( "increase_height_key" ) ) string_str >> options::aimbot::exploits::movement::increase_height_key;
			if( feature_name == xs( "fly_speed" ) ) string_str >> options::aimbot::exploits::movement::fly_speed;
			if( feature_name == xs( "jump_height" ) ) string_str >> options::aimbot::exploits::movement::jump_height;
			if( feature_name == xs( "omni_sprint_speed" ) ) string_str >> options::aimbot::exploits::movement::omni_sprint_speed;
			if( feature_name == xs( "height_amount" ) ) string_str >> options::aimbot::exploits::movement::height_amount;

			if( feature_name == xs( "master_switch" ) ) string_str >> options::visuals::world::master_switch;

			if( feature_name == xs( "show_diesel_fuel" ) ) string_str >> options::visuals::world::show_diesel_fuel;

			if( feature_name == xs( "color_heal[0]" ) ) string_str >> options::visuals::world::color_heal.r;
			if( feature_name == xs( "color_heal[1]" ) ) string_str >> options::visuals::world::color_heal.g;
			if( feature_name == xs( "color_heal[2]" ) ) string_str >> options::visuals::world::color_heal.b;

			if( feature_name == xs( "color_weapons[0]" ) ) string_str >> options::visuals::world::color_weapons.r;
			if( feature_name == xs( "color_weapons[1]" ) ) string_str >> options::visuals::world::color_weapons.g;
			if( feature_name == xs( "color_weapons[2]" ) ) string_str >> options::visuals::world::color_weapons.b;

			if( feature_name == xs( "color_melee_weapons[0]" ) ) string_str >> options::visuals::world::color_melee_weapons.r;
			if( feature_name == xs( "color_melee_weapons[1]" ) ) string_str >> options::visuals::world::color_melee_weapons.g;
			if( feature_name == xs( "color_melee_weapons[2]" ) ) string_str >> options::visuals::world::color_melee_weapons.b;

			if( feature_name == xs( "color_everything[0]" ) ) string_str >> options::visuals::world::color_everything.r;
			if( feature_name == xs( "color_everything[1]" ) ) string_str >> options::visuals::world::color_everything.g;
			if( feature_name == xs( "color_everything[2]" ) ) string_str >> options::visuals::world::color_everything.b;

			if( feature_name == xs( "color_stashes[0]" ) ) string_str >> options::visuals::world::color_stashes.r;
			if( feature_name == xs( "color_stashes[1]" ) ) string_str >> options::visuals::world::color_stashes.g;
			if( feature_name == xs( "color_stashes[2]" ) ) string_str >> options::visuals::world::color_stashes.b;
	
			if( feature_name == xs( "color_animals[0]" ) ) string_str >> options::visuals::world::color_animals.r;
			if( feature_name == xs( "color_animals[1]" ) ) string_str >> options::visuals::world::color_animals.g;
			if( feature_name == xs( "color_animals[2]" ) ) string_str >> options::visuals::world::color_animals.b;

			if( feature_name == xs( "color_traps[0]" ) ) string_str >> options::visuals::world::color_traps.r;
			if( feature_name == xs( "color_traps[1]" ) ) string_str >> options::visuals::world::color_traps.g;
			if( feature_name == xs( "color_traps[2]" ) ) string_str >> options::visuals::world::color_traps.b;

			if( feature_name == xs( "color_storages[0]" ) ) string_str >> options::visuals::world::color_storages.r;
			if( feature_name == xs( "color_storages[1]" ) ) string_str >> options::visuals::world::color_storages.g;
			if( feature_name == xs( "color_storages[2]" ) ) string_str >> options::visuals::world::color_storages.b;

			if( feature_name == xs( "color_vehicles[0]" ) ) string_str >> options::visuals::world::color_vehicles.r;
			if( feature_name == xs( "color_vehicles[1]" ) ) string_str >> options::visuals::world::color_vehicles.g;
			if( feature_name == xs( "color_vehicles[2]" ) ) string_str >> options::visuals::world::color_vehicles.b;

			if( feature_name == xs( "color_raid[0]" ) ) string_str >> options::visuals::world::color_raid.r;
			if( feature_name == xs( "color_raid[1]" ) ) string_str >> options::visuals::world::color_raid.g;
			if( feature_name == xs( "color_raid[2]" ) ) string_str >> options::visuals::world::color_raid.b;

			if( feature_name == xs( "color_item[0]" ) ) string_str >> options::visuals::world::color_item.r;
			if( feature_name == xs( "color_item[1]" ) ) string_str >> options::visuals::world::color_item.g;
			if( feature_name == xs( "color_item[2]" ) ) string_str >> options::visuals::world::color_item.b;

			if( feature_name == xs( "color_respawn_points[0]" ) ) string_str >> options::visuals::world::color_respawn_points.r;
			if( feature_name == xs( "color_respawn_points[1]" ) ) string_str >> options::visuals::world::color_respawn_points.g;
			if( feature_name == xs( "color_respawn_points[2]" ) ) string_str >> options::visuals::world::color_respawn_points.b;

			if( feature_name == xs( "color_chickens[0]" ) ) string_str >> options::visuals::world::color_chickens.r;
			if( feature_name == xs( "color_chickens[1]" ) ) string_str >> options::visuals::world::color_chickens.g;
			if( feature_name == xs( "color_chickens[2]" ) ) string_str >> options::visuals::world::color_chickens.b;

			if( feature_name == xs( "color_helicopter[0]" ) ) string_str >> options::visuals::world::color_helicopter.r;
			if( feature_name == xs( "color_helicopter[1]" ) ) string_str >> options::visuals::world::color_helicopter.g;
			if( feature_name == xs( "color_helicopter[2]" ) ) string_str >> options::visuals::world::color_helicopter.b;

			if( feature_name == xs( "color_ores[0]" ) ) string_str >> options::visuals::world::color_ores.r;
			if( feature_name == xs( "color_ores[1]" ) ) string_str >> options::visuals::world::color_ores.g;
			if( feature_name == xs( "color_ores[2]" ) ) string_str >> options::visuals::world::color_ores.b;

			if( feature_name == xs( "color_sulfur_ore[0]" ) ) string_str >> options::visuals::world::color_sulfur_ore.r;
			if( feature_name == xs( "color_sulfur_ore[1]" ) ) string_str >> options::visuals::world::color_sulfur_ore.g;
			if( feature_name == xs( "color_sulfur_ore[2]" ) ) string_str >> options::visuals::world::color_sulfur_ore.b;

			if( feature_name == xs( "color_metal_ore[0]" ) ) string_str >> options::visuals::world::color_metal_ore.r;
			if( feature_name == xs( "color_metal_ore[1]" ) ) string_str >> options::visuals::world::color_metal_ore.g;
			if( feature_name == xs( "color_metal_ore[2]" ) ) string_str >> options::visuals::world::color_metal_ore.b;

			if( feature_name == xs( "color_stone_ore[0]" ) ) string_str >> options::visuals::world::color_stone_ore.r;
			if( feature_name == xs( "color_stone_ore[1]" ) ) string_str >> options::visuals::world::color_stone_ore.g;
			if( feature_name == xs( "color_stone_ore[2]" ) ) string_str >> options::visuals::world::color_stone_ore.b;

			if( feature_name == xs( "color_tool_cupboard[0]" ) ) string_str >> options::visuals::world::color_tool_cupboard.r;
			if( feature_name == xs( "color_tool_cupboard[1]" ) ) string_str >> options::visuals::world::color_tool_cupboard.g;
			if( feature_name == xs( "color_tool_cupboard[2]" ) ) string_str >> options::visuals::world::color_tool_cupboard.b;

			if( feature_name == xs( "color_box_storages[0]" ) ) string_str >> options::visuals::world::color_box_storages.r;
			if( feature_name == xs( "color_box_storages[1]" ) ) string_str >> options::visuals::world::color_box_storages.g;
			if( feature_name == xs( "color_box_storages[2]" ) ) string_str >> options::visuals::world::color_box_storages.b;

			if( feature_name == xs( "color_ammo_nails_arrows[0]" ) ) string_str >> options::visuals::world::color_ammo_nails_arrows.r;
			if( feature_name == xs( "color_ammo_nails_arrows[1]" ) ) string_str >> options::visuals::world::color_ammo_nails_arrows.g;
			if( feature_name == xs( "color_ammo_nails_arrows[2]" ) ) string_str >> options::visuals::world::color_ammo_nails_arrows.b;

			if( feature_name == xs( "color_supply_signals[0]" ) ) string_str >> options::visuals::world::color_supply_signals.r;
			if( feature_name == xs( "color_supply_signals[1]" ) ) string_str >> options::visuals::world::color_supply_signals.g;
			if( feature_name == xs( "color_supply_signals[2]" ) ) string_str >> options::visuals::world::color_supply_signals.b;

			if( feature_name == xs( "color_supply_drops[0]" ) ) string_str >> options::visuals::world::color_supply_drops.r;
			if( feature_name == xs( "color_supply_drops[1]" ) ) string_str >> options::visuals::world::color_supply_drops.g;
			if( feature_name == xs( "color_supply_drops[2]" ) ) string_str >> options::visuals::world::color_supply_drops.b;

			if( feature_name == xs( "color_hemp[0]" ) ) string_str >> options::visuals::world::color_hemp.r;
			if( feature_name == xs( "color_hemp[1]" ) ) string_str >> options::visuals::world::color_hemp.g;
			if( feature_name == xs( "color_hemp[2]" ) ) string_str >> options::visuals::world::color_hemp.b;

			if( feature_name == xs( "color_mushroom[0]" ) ) string_str >> options::visuals::world::color_mushroom.r;
			if( feature_name == xs( "color_mushroom[1]" ) ) string_str >> options::visuals::world::color_mushroom.g;
			if( feature_name == xs( "color_mushroom[2]" ) ) string_str >> options::visuals::world::color_mushroom.b;

			if( feature_name == xs( "color_pumpkin[0]" ) ) string_str >> options::visuals::world::color_pumpkin.r;
			if( feature_name == xs( "color_pumpkin[1]" ) ) string_str >> options::visuals::world::color_pumpkin.g;
			if( feature_name == xs( "color_pumpkin[2]" ) ) string_str >> options::visuals::world::color_pumpkin.b;

			if( feature_name == xs( "color_berrys[0]" ) ) string_str >> options::visuals::world::color_berrys.r;
			if( feature_name == xs( "color_berrys[1]" ) ) string_str >> options::visuals::world::color_berrys.g;
			if( feature_name == xs( "color_berrys[2]" ) ) string_str >> options::visuals::world::color_berrys.b;

			if( feature_name == xs( "color_corns[0]" ) ) string_str >> options::visuals::world::color_corns.r;
			if( feature_name == xs( "color_corns[1]" ) ) string_str >> options::visuals::world::color_corns.g;
			if( feature_name == xs( "color_corns[2]" ) ) string_str >> options::visuals::world::color_corns.b;

			if( feature_name == xs( "show_corpse" ) ) string_str >> options::visuals::world::show_corpse;
			if( feature_name == xs( "show_backpack" ) ) string_str >> options::visuals::world::show_backpack;

			if( feature_name == xs( "color_corpse[0]" ) ) string_str >> options::visuals::world::color_corpse.r;
			if( feature_name == xs( "color_corpse[1]" ) ) string_str >> options::visuals::world::color_corpse.g;
			if( feature_name == xs( "color_corpse[2]" ) ) string_str >> options::visuals::world::color_corpse.b;

			if( feature_name == xs( "color_backpack[0]" ) ) string_str >> options::visuals::world::color_backpack.r;
			if( feature_name == xs( "color_backpack[1]" ) ) string_str >> options::visuals::world::color_backpack.g;
			if( feature_name == xs( "color_backpack[2]" ) ) string_str >> options::visuals::world::color_backpack.b;

			if( feature_name == xs( "color_potatos[0]" ) ) string_str >> options::visuals::world::color_potatos.r;
			if( feature_name == xs( "color_potatos[1]" ) ) string_str >> options::visuals::world::color_potatos.g;
			if( feature_name == xs( "color_potatos[2]" ) ) string_str >> options::visuals::world::color_potatos.b;

			if( feature_name == xs( "color_modular_car[0]" ) ) string_str >> options::visuals::world::color_modular_car.r;
			if( feature_name == xs( "color_modular_car[1]" ) ) string_str >> options::visuals::world::color_modular_car.g;
			if( feature_name == xs( "color_modular_car[2]" ) ) string_str >> options::visuals::world::color_modular_car.b;

			if( feature_name == xs( "color_two_modules_car[0]" ) ) string_str >> options::visuals::world::color_two_modules_car.r;
			if( feature_name == xs( "color_two_modules_car[1]" ) ) string_str >> options::visuals::world::color_two_modules_car.g;
			if( feature_name == xs( "color_two_modules_car[2]" ) ) string_str >> options::visuals::world::color_two_modules_car.b;

			if( feature_name == xs( "color_minicopter[0]" ) ) string_str >> options::visuals::world::color_minicopter.r;
			if( feature_name == xs( "color_minicopter[1]" ) ) string_str >> options::visuals::world::color_minicopter.g;
			if( feature_name == xs( "color_minicopter[2]" ) ) string_str >> options::visuals::world::color_minicopter.b;

			if( feature_name == xs( "color_scrap_helicopter[0]" ) ) string_str >> options::visuals::world::color_scrap_helicopter.r;
			if( feature_name == xs( "color_scrap_helicopter[1]" ) ) string_str >> options::visuals::world::color_scrap_helicopter.g;
			if( feature_name == xs( "color_scrap_helicopter[2]" ) ) string_str >> options::visuals::world::color_scrap_helicopter.b;

			if( feature_name == xs( "color_rhib[0]" ) ) string_str >> options::visuals::world::color_rhib.r;
			if( feature_name == xs( "color_rhib[1]" ) ) string_str >> options::visuals::world::color_rhib.g;
			if( feature_name == xs( "color_rhib[2]" ) ) string_str >> options::visuals::world::color_rhib.b;

			if( feature_name == xs( "color_bradley_apc[0]" ) ) string_str >> options::visuals::world::color_bradley_apc.r;
			if( feature_name == xs( "color_bradley_apc[1]" ) ) string_str >> options::visuals::world::color_bradley_apc.g;
			if( feature_name == xs( "color_bradley_apc[2]" ) ) string_str >> options::visuals::world::color_bradley_apc.b;

			if( feature_name == xs( "color_kayak[0]" ) ) string_str >> options::visuals::world::color_kayak.r;
			if( feature_name == xs( "color_kayak[1]" ) ) string_str >> options::visuals::world::color_kayak.g;
			if( feature_name == xs( "color_kayak[2]" ) ) string_str >> options::visuals::world::color_kayak.b;

			if( feature_name == xs( "color_small_motorboat[0]" ) ) string_str >> options::visuals::world::color_small_motorboat.r;
			if( feature_name == xs( "color_small_motorboat[1]" ) ) string_str >> options::visuals::world::color_small_motorboat.g;
			if( feature_name == xs( "color_small_motorboat[2]" ) ) string_str >> options::visuals::world::color_small_motorboat.b;

			if( feature_name == xs( "color_solo_submarine[0]" ) ) string_str >> options::visuals::world::color_solo_submarine.r;
			if( feature_name == xs( "color_solo_submarine[1]" ) ) string_str >> options::visuals::world::color_solo_submarine.g;
			if( feature_name == xs( "color_solo_submarine[2]" ) ) string_str >> options::visuals::world::color_solo_submarine.b;

			if( feature_name == xs( "color_duo_submarine[0]" ) ) string_str >> options::visuals::world::color_duo_submarine.r;
			if( feature_name == xs( "color_duo_submarine[1]" ) ) string_str >> options::visuals::world::color_duo_submarine.g;
			if( feature_name == xs( "color_duo_submarine[2]" ) ) string_str >> options::visuals::world::color_duo_submarine.b;

			if( feature_name == xs( "color_landmines[0]" ) ) string_str >> options::visuals::world::color_landmines.r;
			if( feature_name == xs( "color_landmines[1]" ) ) string_str >> options::visuals::world::color_landmines.g;
			if( feature_name == xs( "color_landmines[2]" ) ) string_str >> options::visuals::world::color_landmines.b;

			if( feature_name == xs( "color_npc_turrets[0]" ) ) string_str >> options::visuals::world::color_npc_turrets.r;
			if( feature_name == xs( "color_npc_turrets[1]" ) ) string_str >> options::visuals::world::color_npc_turrets.g;
			if( feature_name == xs( "color_npc_turrets[2]" ) ) string_str >> options::visuals::world::color_npc_turrets.b;

			if( feature_name == xs( "color_auto_turrets[0]" ) ) string_str >> options::visuals::world::color_auto_turrets.r;
			if( feature_name == xs( "color_auto_turrets[1]" ) ) string_str >> options::visuals::world::color_auto_turrets.g;
			if( feature_name == xs( "color_auto_turrets[2]" ) ) string_str >> options::visuals::world::color_auto_turrets.b;

			if( feature_name == xs( "color_shotgun_traps[0]" ) ) string_str >> options::visuals::world::color_shotgun_traps.r;
			if( feature_name == xs( "color_shotgun_traps[1]" ) ) string_str >> options::visuals::world::color_shotgun_traps.g;
			if( feature_name == xs( "color_shotgun_traps[2]" ) ) string_str >> options::visuals::world::color_shotgun_traps.b;

			if( feature_name == xs( "color_tesla_coil[0]" ) ) string_str >> options::visuals::world::color_tesla_coil.r;
			if( feature_name == xs( "color_tesla_coil[1]" ) ) string_str >> options::visuals::world::color_tesla_coil.g;
			if( feature_name == xs( "color_tesla_coil[2]" ) ) string_str >> options::visuals::world::color_tesla_coil.b;

			if( feature_name == xs( "color_flame_turrets[0]" ) ) string_str >> options::visuals::world::color_flame_turrets.r;
			if( feature_name == xs( "color_flame_turrets[1]" ) ) string_str >> options::visuals::world::color_flame_turrets.g;
			if( feature_name == xs( "color_flame_turrets[2]" ) ) string_str >> options::visuals::world::color_flame_turrets.b;

			if( feature_name == xs( "color_sam_site[0]" ) ) string_str >> options::visuals::world::color_sam_site.r;
			if( feature_name == xs( "color_sam_site[1]" ) ) string_str >> options::visuals::world::color_sam_site.g;
			if( feature_name == xs( "color_sam_site[2]" ) ) string_str >> options::visuals::world::color_sam_site.b;

			if( feature_name == xs( "color_land_spikes[0]" ) ) string_str >> options::visuals::world::color_land_spikes.r;
			if( feature_name == xs( "color_land_spikes[1]" ) ) string_str >> options::visuals::world::color_land_spikes.g;
			if( feature_name == xs( "color_land_spikes[2]" ) ) string_str >> options::visuals::world::color_land_spikes.b;

			if( feature_name == xs( "color_bear_trap[0]" ) ) string_str >> options::visuals::world::color_bear_trap.r;
			if( feature_name == xs( "color_bear_trap[1]" ) ) string_str >> options::visuals::world::color_bear_trap.g;
			if( feature_name == xs( "color_bear_trap[2]" ) ) string_str >> options::visuals::world::color_bear_trap.b;

			if( feature_name == xs( "color_oil_barrel[0]" ) ) string_str >> options::visuals::world::color_oil_barrel.r;
			if( feature_name == xs( "color_oil_barrel[1]" ) ) string_str >> options::visuals::world::color_oil_barrel.g;
			if( feature_name == xs( "color_oil_barrel[2]" ) ) string_str >> options::visuals::world::color_oil_barrel.b;

			if( feature_name == xs( "color_regular_barrels[0]" ) ) string_str >> options::visuals::world::color_regular_barrels.r;
			if( feature_name == xs( "color_regular_barrels[1]" ) ) string_str >> options::visuals::world::color_regular_barrels.g;
			if( feature_name == xs( "color_regular_barrels[2]" ) ) string_str >> options::visuals::world::color_regular_barrels.b;

			if( feature_name == xs( "color_underwater_crate[0]" ) ) string_str >> options::visuals::world::color_underwater_crate.r;
			if( feature_name == xs( "color_underwater_crate[1]" ) ) string_str >> options::visuals::world::color_underwater_crate.g;
			if( feature_name == xs( "color_underwater_crate[2]" ) ) string_str >> options::visuals::world::color_underwater_crate.b;

			if( feature_name == xs( "color_elite_crate[0]" ) ) string_str >> options::visuals::world::color_elite_crate.r;
			if( feature_name == xs( "color_elite_crate[1]" ) ) string_str >> options::visuals::world::color_elite_crate.g;
			if( feature_name == xs( "color_elite_crate[2]" ) ) string_str >> options::visuals::world::color_elite_crate.b;

			if( feature_name == xs( "color_military_crate[0]" ) ) string_str >> options::visuals::world::color_military_crate.r;
			if( feature_name == xs( "color_military_crate[1]" ) ) string_str >> options::visuals::world::color_military_crate.g;
			if( feature_name == xs( "color_military_crate[2]" ) ) string_str >> options::visuals::world::color_military_crate.b;
	
			if( feature_name == xs( "color_bradley_crate[0]" ) ) string_str >> options::visuals::world::color_bradley_crate.r;
			if( feature_name == xs( "color_bradley_crate[1]" ) ) string_str >> options::visuals::world::color_bradley_crate.g;
			if( feature_name == xs( "color_bradley_crate[2]" ) ) string_str >> options::visuals::world::color_bradley_crate.b;

			if( feature_name == xs( "color_food_crate[0]" ) ) string_str >> options::visuals::world::color_food_crate.r;
			if( feature_name == xs( "color_food_crate[1]" ) ) string_str >> options::visuals::world::color_food_crate.g;
			if( feature_name == xs( "color_food_crate[2]" ) ) string_str >> options::visuals::world::color_food_crate.b;
	
			if( feature_name == xs( "color_medical_crate[0]" ) ) string_str >> options::visuals::world::color_medical_crate.r;
			if( feature_name == xs( "color_medical_crate[1]" ) ) string_str >> options::visuals::world::color_medical_crate.g;
			if( feature_name == xs( "color_medical_crate[2]" ) ) string_str >> options::visuals::world::color_medical_crate.b;

			if( feature_name == xs( "color_diesel_fuel[0]" ) ) string_str >> options::visuals::world::color_diesel_fuel.r;
			if( feature_name == xs( "color_diesel_fuel[1]" ) ) string_str >> options::visuals::world::color_diesel_fuel.g;
			if( feature_name == xs( "color_diesel_fuel[2]" ) ) string_str >> options::visuals::world::color_diesel_fuel.b;

			if( feature_name == xs( "color_helicopter_crate[0]" ) ) string_str >> options::visuals::world::color_helicopter_crate.r;
			if( feature_name == xs( "color_helicopter_crate[1]" ) ) string_str >> options::visuals::world::color_helicopter_crate.g;
			if( feature_name == xs( "color_helicopter_crate[2]" ) ) string_str >> options::visuals::world::color_helicopter_crate.b;

			if( feature_name == xs( "color_hackable_locked_crate[0]" ) ) string_str >> options::visuals::world::color_hackable_locked_crate.r;
			if( feature_name == xs( "color_hackable_locked_crate[1]" ) ) string_str >> options::visuals::world::color_hackable_locked_crate.g;
			if( feature_name == xs( "color_hackable_locked_crate[2]" ) ) string_str >> options::visuals::world::color_hackable_locked_crate.b;

			if( feature_name == xs( "color_normal_crate[0]" ) ) string_str >> options::visuals::world::color_normal_crate.r;
			if( feature_name == xs( "color_normal_crate[1]" ) ) string_str >> options::visuals::world::color_normal_crate.g;
			if( feature_name == xs( "color_normal_crate[2]" ) ) string_str >> options::visuals::world::color_normal_crate.b;

			if( feature_name == xs( "color_small_crate[0]" ) ) string_str >> options::visuals::world::color_small_crate.r;
			if( feature_name == xs( "color_small_crate[1]" ) ) string_str >> options::visuals::world::color_small_crate.g;
			if( feature_name == xs( "color_small_crate[2]" ) ) string_str >> options::visuals::world::color_small_crate.b;

			if( feature_name == xs( "color_mine_crate[0]" ) ) string_str >> options::visuals::world::color_mine_crate.r;
			if( feature_name == xs( "color_mine_crate[1]" ) ) string_str >> options::visuals::world::color_mine_crate.g;
			if( feature_name == xs( "color_mine_crate[2]" ) ) string_str >> options::visuals::world::color_mine_crate.b;

			if( feature_name == xs( "color_tool_box[0]" ) ) string_str >> options::visuals::world::color_tool_box.r;
			if( feature_name == xs( "color_tool_box[1]" ) ) string_str >> options::visuals::world::color_tool_box.g;
			if( feature_name == xs( "color_tool_box[2]" ) ) string_str >> options::visuals::world::color_tool_box.b;

			if( feature_name == xs( "color_boars[0]" ) ) string_str >> options::visuals::world::color_boars.r;
			if( feature_name == xs( "color_boars[1]" ) ) string_str >> options::visuals::world::color_boars.g;
			if( feature_name == xs( "color_boars[2]" ) ) string_str >> options::visuals::world::color_boars.b;

			if( feature_name == xs( "color_wolves[0]" ) ) string_str >> options::visuals::world::color_wolves.r;
			if( feature_name == xs( "color_wolves[1]" ) ) string_str >> options::visuals::world::color_wolves.g;
			if( feature_name == xs( "color_wolves[2]" ) ) string_str >> options::visuals::world::color_wolves.b;

			if( feature_name == xs( "color_horses[0]" ) ) string_str >> options::visuals::world::color_horses.r;
			if( feature_name == xs( "color_horses[1]" ) ) string_str >> options::visuals::world::color_horses.g;
			if( feature_name == xs( "color_horses[2]" ) ) string_str >> options::visuals::world::color_horses.b;

			if( feature_name == xs( "color_sharks[0]" ) ) string_str >> options::visuals::world::color_sharks.r;
			if( feature_name == xs( "color_sharks[1]" ) ) string_str >> options::visuals::world::color_sharks.g;
			if( feature_name == xs( "color_sharks[2]" ) ) string_str >> options::visuals::world::color_sharks.b;

			if( feature_name == xs( "color_deers[0]" ) ) string_str >> options::visuals::world::color_deers.r;
			if( feature_name == xs( "color_deers[1]" ) ) string_str >> options::visuals::world::color_deers.g;
			if( feature_name == xs( "color_deers[2]" ) ) string_str >> options::visuals::world::color_deers.b;

			if( feature_name == xs( "color_polar_bears[0]" ) ) string_str >> options::visuals::world::color_polar_bears.r;
			if( feature_name == xs( "color_polar_bears[1]" ) ) string_str >> options::visuals::world::color_polar_bears.g;
			if( feature_name == xs( "color_polar_bears[2]" ) ) string_str >> options::visuals::world::color_polar_bears.b;

			if( feature_name == xs( "color_bears[0]" ) ) string_str >> options::visuals::world::color_bears.r;
			if( feature_name == xs( "color_bears[1]" ) ) string_str >> options::visuals::world::color_bears.g;
			if( feature_name == xs( "color_bears[2]" ) ) string_str >> options::visuals::world::color_bears.b;

			if( feature_name == xs( "color_drone[0]" ) ) string_str >> options::visuals::world::color_drone.r;
			if( feature_name == xs( "color_drone[1]" ) ) string_str >> options::visuals::world::color_drone.g;
			if( feature_name == xs( "color_drone[2]" ) ) string_str >> options::visuals::world::color_drone.b;

			if( feature_name == xs( "color_recycler[0]" ) ) string_str >> options::visuals::world::color_recycler.r;
			if( feature_name == xs( "color_recycler[1]" ) ) string_str >> options::visuals::world::color_recycler.g;
			if( feature_name == xs( "color_recycler[2]" ) ) string_str >> options::visuals::world::color_recycler.b;

			if( feature_name == xs( "color_metal_collectibles[0]" ) ) string_str >> options::visuals::world::color_metal_collectibles.r;
			if( feature_name == xs( "color_metal_collectibles[1]" ) ) string_str >> options::visuals::world::color_metal_collectibles.g;
			if( feature_name == xs( "color_metal_collectibles[2]" ) ) string_str >> options::visuals::world::color_metal_collectibles.b;

			if( feature_name == xs( "color_wood_collectibles[0]" ) ) string_str >> options::visuals::world::color_wood_collectibles.r;
			if( feature_name == xs( "color_wood_collectibles[1]" ) ) string_str >> options::visuals::world::color_wood_collectibles.g;
			if( feature_name == xs( "color_wood_collectibles[2]" ) ) string_str >> options::visuals::world::color_wood_collectibles.b;

			if( feature_name == xs( "color_stone_collectibles[0]" ) ) string_str >> options::visuals::world::color_stone_collectibles.r;
			if( feature_name == xs( "color_stone_collectibles[1]" ) ) string_str >> options::visuals::world::color_stone_collectibles.g;
			if( feature_name == xs( "color_stone_collectibles[2]" ) ) string_str >> options::visuals::world::color_stone_collectibles.b;

			if( feature_name == xs( "color_vending_machine[0]" ) ) string_str >> options::visuals::world::color_vending_machine.r;
			if( feature_name == xs( "color_vending_machine[1]" ) ) string_str >> options::visuals::world::color_vending_machine.g;
			if( feature_name == xs( "color_vending_machine[2]" ) ) string_str >> options::visuals::world::color_vending_machine.b;

			if( feature_name == xs( "vis_distance_color[0]" ) ) string_str >> options::visuals::vis_distance_color.r;
			if( feature_name == xs( "vis_distance_color[1]" ) ) string_str >> options::visuals::vis_distance_color.g;
			if( feature_name == xs( "vis_distance_color[2]" ) ) string_str >> options::visuals::vis_distance_color.b;

			if( feature_name == xs( "vis_weapon_color[0]" ) ) string_str >> options::visuals::vis_weapon_color.r;
			if( feature_name == xs( "vis_weapon_color[1]" ) ) string_str >> options::visuals::vis_weapon_color.g;
			if( feature_name == xs( "vis_weapon_color[2]" ) ) string_str >> options::visuals::vis_weapon_color.b;

			if( feature_name == xs( "distance_color[0]" ) ) string_str >> options::visuals::distance_color.r;
			if( feature_name == xs( "distance_color[1]" ) ) string_str >> options::visuals::distance_color.g;
			if( feature_name == xs( "distance_color[2]" ) ) string_str >> options::visuals::distance_color.b;

			if( feature_name == xs( "weapon_color[0]" ) ) string_str >> options::visuals::weapon_color.r;
			if( feature_name == xs( "weapon_color[1]" ) ) string_str >> options::visuals::weapon_color.g;
			if( feature_name == xs( "weapon_color[2]" ) ) string_str >> options::visuals::weapon_color.b;

			if( feature_name == xs( "health_text_color[0]" ) ) string_str >> options::visuals::health_text_color.r;
			if( feature_name == xs( "health_text_color[1]" ) ) string_str >> options::visuals::health_text_color.g;
			if( feature_name == xs( "health_text_color[2]" ) ) string_str >> options::visuals::health_text_color.b;

			if( feature_name == xs( "custom_health_color[0]" ) ) string_str >> options::visuals::custom_health_color.r;
			if( feature_name == xs( "custom_health_color[1]" ) ) string_str >> options::visuals::custom_health_color.g;
			if( feature_name == xs( "custom_health_color[2]" ) ) string_str >> options::visuals::custom_health_color.b;

			if( feature_name == xs( "modify_health_color" ) ) string_str >> options::visuals::modify_health_color;

			if( feature_name == xs( "health_thickness" ) ) string_str >> options::visuals::health_thickness;

			if( feature_name == xs( "auto_pickup" ) ) string_str >> options::aimbot::exploits::misc::auto_pickup;
			if( feature_name == xs( "manipulation_key" ) ) string_str >> options::aimbot::manipulation_key;

			if( feature_name == xs( "auto_untie_crates" ) ) string_str >> options::aimbot::exploits::misc::auto_untie_crates;

			if( feature_name == xs( "automatic_weapons" ) ) string_str >> options::aimbot::exploits::combat::automatic_weapons;
			if( feature_name == xs( "semi_automatic_weapons" ) ) string_str >> options::aimbot::exploits::combat::semi_automatic_weapons;
			if( feature_name == xs( "burst_weapons" ) ) string_str >> options::aimbot::exploits::combat::burst_weapons;
			if( feature_name == xs( "unlock_aim_on_jugger" ) ) string_str >> options::aimbot::exploits::combat::unlock_aim_on_jugger;
			if( feature_name == xs( "aim_bolt_cycle" ) ) string_str >> options::aimbot::exploits::combat::aim_bolt_cycle;
			if( feature_name == xs( "extended_melee" ) ) string_str >> options::aimbot::exploits::combat::extended_melee;
			if( feature_name == xs( "no_spread" ) ) string_str >> options::aimbot::exploits::combat::no_spread;
			if( feature_name == xs( "no_sway" ) ) string_str >> options::aimbot::exploits::combat::no_sway;
			if( feature_name == xs( "modify_eoka_chance" ) ) string_str >> options::aimbot::exploits::combat::modify_eoka_chance;
			if( feature_name == xs( "no_recoil" ) ) string_str >> options::aimbot::exploits::combat::no_recoil;
			if( feature_name == xs( "modify_can_attack" ) ) string_str >> options::aimbot::exploits::combat::modify_can_attack;
			if( feature_name == xs( "can_attack_in_vehicles" ) ) string_str >> options::aimbot::exploits::combat::can_attack_in_vehicles;
			if( feature_name == xs( "unlock_view_angles" ) ) string_str >> options::aimbot::exploits::combat::unlock_view_angles;
			if( feature_name == xs( "big_bullets" ) ) string_str >> options::aimbot::exploits::combat::big_bullets;
			if( feature_name == xs( "quick_bullets" ) ) string_str >> options::aimbot::exploits::combat::quick_bullets;

			if( feature_name == xs( "aim_type" ) ) string_str >> options::aimbot::aim_type;

			if( feature_name == xs( "pierce" ) ) string_str >> options::aimbot::exploits::combat::pierce;
			if( feature_name == xs( "spoof_hit_distance" ) ) string_str >> options::aimbot::exploits::combat::spoof_hit_distance;
			if( feature_name == xs( "no_shot_gun_spread" ) ) string_str >> options::aimbot::exploits::combat::no_shot_gun_spread;
			if( feature_name == xs( "head_teleportation" ) ) string_str >> options::aimbot::exploits::combat::head_teleportation;

			if( feature_name == xs( "reduce_recoil" ) ) string_str >> options::aimbot::exploits::combat::reduce_recoil;
			if( feature_name == xs( "reduce_spread" ) ) string_str >> options::aimbot::exploits::combat::reduce_spread;
			if( feature_name == xs( "bullet_distance" ) ) string_str >> options::aimbot::exploits::combat::bullet_distance;
			if( feature_name == xs( "eoka_chance" ) ) string_str >> options::aimbot::exploits::combat::eoka_chance;
			if( feature_name == xs( "attack_radius" ) ) string_str >> options::aimbot::exploits::combat::attack_radius;
			if( feature_name == xs( "bullet_size" ) ) string_str >> options::aimbot::exploits::combat::bullet_size;
			if( feature_name == xs( "teleport_key" ) ) string_str >> options::aimbot::exploits::combat::teleport_key;
			if( feature_name == xs( "bullet_speed" ) ) string_str >> options::aimbot::exploits::combat::bullet_speed;

			if( feature_name == xs( "fast_loot" ) ) string_str >> options::aimbot::exploits::time::fast_loot;
			if( feature_name == xs( "fast_heal" ) ) string_str >> options::aimbot::exploits::time::fast_heal;
			if( feature_name == xs( "fast_switch" ) ) string_str >> options::aimbot::exploits::time::fast_switch;
			if( feature_name == xs( "time_modifier" ) ) string_str >> options::aimbot::exploits::time::time_modifier;
			if( feature_name == xs( "rapid_fire" ) ) string_str >> options::aimbot::exploits::time::rapid_fire;
			if( feature_name == xs( "fake_lag" ) ) string_str >> options::aimbot::exploits::time::fake_lag;
			if( feature_name == xs( "instant_charge_compound" ) ) string_str >> options::aimbot::exploits::time::instant_charge_compound;
			if( feature_name == xs( "fake_lag_on" ) ) string_str >> options::aimbot::exploits::time::fake_lag_on;
			if( feature_name == xs( "fake_lag_amount" ) ) string_str >> options::aimbot::exploits::time::fake_lag_amount;

			if( feature_name == xs( "radar_position[0]" ) ) string_str >> g_esp.radar_position.x;
			if( feature_name == xs( "radar_position[1]" ) ) string_str >> g_esp.radar_position.y;

			if( feature_name == xs( "hotbar_position[0]" ) ) string_str >> g_esp.hotbar_position.x;
			if( feature_name == xs( "hotbar_position[1]" ) ) string_str >> g_esp.hotbar_position.y;

			if( feature_name == xs( "clothes_position[0]" ) ) string_str >> g_esp.clothes_position.x;
			if( feature_name == xs( "clothes_position[1]" ) ) string_str >> g_esp.clothes_position.y;
			
			if( feature_name == xs( "revive_key" ) ) string_str >> options::aimbot::exploits::time::revive_key;
			if( feature_name == xs( "fake_lag_key" ) ) string_str >> options::aimbot::exploits::time::fake_lag_key;
			if( feature_name == xs( "instant_revive" ) ) string_str >> options::aimbot::exploits::time::instant_revive;
			if( feature_name == xs( "fast_bow" ) ) string_str >> options::aimbot::exploits::time::fast_bow;
			if( feature_name == xs( "always_revive_target" ) ) string_str >> options::aimbot::exploits::time::always_revive_target;
			if( feature_name == xs( "rapid_fire_speed" ) ) string_str >> options::aimbot::exploits::time::rapid_fire_speed;
			if( feature_name == xs( "time_speed" ) ) string_str >> options::aimbot::exploits::time::time_speed;

			if( feature_name == xs( "no_viewmodel_bob" ) ) string_str >> options::aimbot::exploits::misc::no_viewmodel_bob;
			if( feature_name == xs( "no_lower" ) ) string_str >> options::aimbot::exploits::misc::no_lower;
			if( feature_name == xs( "no_flash" ) ) string_str >> options::aimbot::exploits::misc::no_flash;

			if( feature_name == xs( "grade_key" ) ) string_str >> options::aimbot::exploits::misc::grade_key;
			if( feature_name == xs( "pickup_key" ) ) string_str >> options::aimbot::exploits::misc::pickup_key;
			if( feature_name == xs( "codelock_key" ) ) string_str >> options::aimbot::exploits::misc::codelock_key;
			if( feature_name == xs( "auto_codelock" ) ) string_str >> options::aimbot::exploits::misc::auto_codelock;
			if( feature_name == xs( "code_lock_code" ) ) string_str >> options::aimbot::exploits::misc::code_lock_code;
			if( feature_name == xs( "max_lock_distance" ) ) string_str >> options::aimbot::exploits::misc::max_lock_distance;

			if( feature_name == xs( "auto_farm_trees" ) ) string_str >> options::aimbot::exploits::misc::auto_farm_trees;
			if( feature_name == xs( "auto_farm_only_hotspot" ) ) string_str >> options::aimbot::exploits::misc::auto_farm_only_hotspot;
			if( feature_name == xs( "auto_farm_ores" ) ) string_str >> options::aimbot::exploits::misc::auto_farm_ores;
			if( feature_name == xs( "auto_farm_barrels" ) ) string_str >> options::aimbot::exploits::misc::auto_farm_barrels;

			if( feature_name == xs( "always_pickup" ) ) string_str >> options::aimbot::exploits::misc::always_pickup;
			if( feature_name == xs( "always_codelock" ) ) string_str >> options::aimbot::exploits::misc::always_codelock;
			if( feature_name == xs( "always_grade" ) ) string_str >> options::aimbot::exploits::misc::always_grade;

			if( feature_name == xs( "add_friend_key" ) ) string_str >> options::add_friend_key;

			if( feature_name == xs( "keep_wounded_alive" ) ) string_str >> options::aimbot::exploits::misc::keep_wounded_alive;
			if( feature_name == xs( "always_hit_weak_spot" ) ) string_str >> options::aimbot::exploits::misc::always_hit_weak_spot;
			if( feature_name == xs( "long_neck" ) ) string_str >> options::aimbot::exploits::misc::long_neck;
			if( feature_name == xs( "long_neck_right" ) ) string_str >> options::aimbot::exploits::misc::long_neck_right;
			if( feature_name == xs( "long_neck_left" ) ) string_str >> options::aimbot::exploits::misc::long_neck_left;
			if( feature_name == xs( "disable_land_damage" ) ) string_str >> options::aimbot::exploits::misc::disable_land_damage;
			if( feature_name == xs( "fov_changer" ) ) string_str >> options::aimbot::exploits::misc::fov_changer;
			if( feature_name == xs( "zoom_fov" ) ) string_str >> options::aimbot::exploits::misc::zoom_fov;

			if( feature_name == xs( "font_flags" ) ) string_str >> options::font_flags;
			if( feature_name == xs( "auto_pickup_items" ) ) string_str >> options::aimbot::exploits::misc::auto_pickup_items;

			if( feature_name == xs( "suicide" ) ) string_str >> options::aimbot::exploits::misc::suicide;
			if( feature_name == xs( "fake_fire" ) ) string_str >> options::aimbot::exploits::misc::fake_fire;
			if( feature_name == xs( "fake_admin" ) ) string_str >> options::aimbot::exploits::misc::fake_admin;
			if( feature_name == xs( "fake_fire_on" ) ) string_str >> options::aimbot::exploits::misc::fake_fire_on;
			if( feature_name == xs( "debug_camera" ) ) string_str >> options::aimbot::exploits::misc::debug_camera;
			if( feature_name == xs( "spin_bot" ) ) string_str >> options::aimbot::exploits::misc::spin_bot;
			if( feature_name == xs( "gesture_spam" ) ) string_str >> options::aimbot::exploits::misc::gesture_spam;
			if( feature_name == xs( "interactive_debug" ) ) string_str >> options::aimbot::exploits::misc::interactive_debug;
			if( feature_name == xs( "disarm_landmines" ) ) string_str >> options::aimbot::exploits::misc::disarm_landmines;
			if( feature_name == xs( "stop_recycler" ) ) string_str >> options::aimbot::exploits::misc::stop_recycler;
			if( feature_name == xs( "long_neck_height" ) ) string_str >> options::aimbot::exploits::misc::long_neck_height;
			if( feature_name == xs( "long_neck_right_amount" ) ) string_str >> options::aimbot::exploits::misc::long_neck_right_amount;
			if( feature_name == xs( "delay_fake_fire" ) ) string_str >> options::aimbot::exploits::misc::delay_fake_fire;
			if( feature_name == xs( "long_neck_left_amount" ) ) string_str >> options::aimbot::exploits::misc::long_neck_left_amount;
			if( feature_name == xs( "zoom_fov_amount" ) ) string_str >> options::aimbot::exploits::misc::zoom_fov_amount;

			if( feature_name == xs( "fov_amount" ) ) string_str >> options::aimbot::exploits::misc::fov_amount;
			if( feature_name == xs( "view_left" ) ) string_str >> options::aimbot::exploits::misc::view_left;
			if( feature_name == xs( "view_right" ) ) string_str >> options::aimbot::exploits::misc::view_right;
			if( feature_name == xs( "view_height" ) ) string_str >> options::aimbot::exploits::misc::view_height;
			if( feature_name == xs( "zoom_key" ) ) string_str >> options::aimbot::exploits::misc::zoom_key;
			if( feature_name == xs( "fake_fire_key" ) ) string_str >> options::aimbot::exploits::misc::fake_fire_key;
			if( feature_name == xs( "gesture_type" ) ) string_str >> options::aimbot::exploits::misc::gesture_type;
			if( feature_name == xs( "debug_camera_key" ) ) string_str >> options::aimbot::exploits::misc::debug_camera_key;
			if( feature_name == xs( "suicide_key" ) ) string_str >> options::aimbot::exploits::misc::suicide_key;

			if( feature_name == xs( "pickup_everything" ) ) string_str >> options::aimbot::exploits::misc::pickup_everything;

			if( feature_name == xs( "max_grade_distance" ) ) string_str >> options::aimbot::exploits::misc::max_grade_distance;
			if( feature_name == xs( "max_item_distance" ) ) string_str >> options::aimbot::exploits::misc::max_item_distance;
			if( feature_name == xs( "max_collectible_distance" ) ) string_str >> options::aimbot::exploits::misc::max_collectible_distance;

			if( feature_name == xs( "auto_grade" ) ) string_str >> options::aimbot::exploits::misc::auto_grade;
			if( feature_name == xs( "grade_tier" ) ) string_str >> options::aimbot::exploits::misc::grade_tier;

			if( feature_name == xs( "aim_key" ) ) string_str >> g_aimbot.aim_key;

			if( feature_name == xs( "draw_visuals" ) ) string_str >> options::visuals::draw_visuals;
			if( feature_name == xs( "indicators" ) ) string_str >> options::visuals::indicators;
			if( feature_name == xs( "fly_hack_indicator" ) ) string_str >> options::visuals::fly_hack_indicator;
			if( feature_name == xs( "draw_tracers" ) ) string_str >> options::visuals::draw_tracers;
			if( feature_name == xs( "offscreen_arrows" ) ) string_str >> options::visuals::offscreen_arrows;
			if( feature_name == xs( "draw_radar" ) ) string_str >> options::visuals::draw_radar;
			if( feature_name == xs( "show_name" ) ) string_str >> options::visuals::show_name;
			if( feature_name == xs( "show_weapon" ) ) string_str >> options::visuals::show_weapon;
			if( feature_name == xs( "show_health" ) ) string_str >> options::visuals::show_health;
			if( feature_name == xs( "show_health_text" ) ) string_str >> options::visuals::show_health_text;
			if( feature_name == xs( "show_distance" ) ) string_str >> options::visuals::show_distance;
			if( feature_name == xs( "show_hotbar" ) ) string_str >> options::visuals::show_hotbar;
			if( feature_name == xs( "show_clothes" ) ) string_str >> options::visuals::show_clothes;
			if( feature_name == xs( "show_lines" ) ) string_str >> options::visuals::show_lines;
			if( feature_name == xs( "show_view_direction" ) ) string_str >> options::visuals::show_view_direction;
			if( feature_name == xs( "can_show_sleepers" ) ) string_str >> options::visuals::can_show_sleepers;
			if( feature_name == xs( "can_show_knocked" ) ) string_str >> options::visuals::can_show_knocked;
			if( feature_name == xs( "can_show_npc" ) ) string_str >> options::visuals::can_show_npc;
			if( feature_name == xs( "chams" ) ) string_str >> options::visuals::chams;
			if( feature_name == xs( "rgb_chams" ) ) string_str >> options::visuals::rgb_chams;
			if( feature_name == xs( "draw_bones" ) ) string_str >> options::visuals::draw_bones;
			if( feature_name == xs( "show_watermark" ) ) string_str >> options::visuals::show_watermark;
			if( feature_name == xs( "local_trails" ) ) string_str >> options::visuals::local_trails;
			if( feature_name == xs( "show_last_sent_tick" ) ) string_str >> options::visuals::show_last_sent_tick;
			if( feature_name == xs( "show_desync_bar" ) ) string_str >> options::visuals::show_desync_bar;
			if( feature_name == xs( "show_reload_bar" ) ) string_str >> options::visuals::show_reload_bar;
			if( feature_name == xs( "can_show_sleepers_oof" ) ) string_str >> options::visuals::can_show_sleepers_oof;
			if( feature_name == xs( "can_show_knocked_oof" ) ) string_str >> options::visuals::can_show_knocked_oof;
			if( feature_name == xs( "can_show_npc_oof" ) ) string_str >> options::visuals::can_show_npc_oof;
			if( feature_name == xs( "max_player_distance" ) ) string_str >> options::visuals::max_player_distance;
			if( feature_name == xs( "box_type" ) ) string_str >> options::visuals::box_type;
			if( feature_name == xs( "offscreen_distance" ) ) string_str >> options::visuals::offscreen_distance;

			if( feature_name == xs( "modify_rain" ) ) string_str >> options::visuals::world::modify_rain;
			if( feature_name == xs( "rain_amount" ) ) string_str >> options::visuals::world::rain_amount;

			if( feature_name == xs( "chams_color[0]" ) ) string_str >> options::visuals::chams_color.r;
			if( feature_name == xs( "chams_color[1]" ) ) string_str >> options::visuals::chams_color.g;
			if( feature_name == xs( "chams_color[2]" ) ) string_str >> options::visuals::chams_color.b;

			if( feature_name == xs( "chams_visible[0]" ) ) string_str >> options::visuals::chams_visible.r;
			if( feature_name == xs( "chams_visible[1]" ) ) string_str >> options::visuals::chams_visible.g;
			if( feature_name == xs( "chams_visible[2]" ) ) string_str >> options::visuals::chams_visible.b;

			if( feature_name == xs( "sky_color[0]" ) ) string_str >> options::visuals::world::sky_color.r;
			if( feature_name == xs( "sky_color[1]" ) ) string_str >> options::visuals::world::sky_color.g;
			if( feature_name == xs( "sky_color[2]" ) ) string_str >> options::visuals::world::sky_color.b;

			if( feature_name == xs( "show_chinook_helicopter" ) ) string_str >> options::visuals::world::show_chinook_helicopter;
			if( feature_name == xs( "show_patrol_helicopter" ) ) string_str >> options::visuals::world::show_patrol_helicopter;
			if( feature_name == xs( "show_attack_helicopter" ) ) string_str >> options::visuals::world::show_attack_helicopter;

			if( feature_name == xs( "color_chinook_helicopter[0]" ) ) string_str >> options::visuals::world::color_chinook_helicopter.r;
			if( feature_name == xs( "color_chinook_helicopter[1]" ) ) string_str >> options::visuals::world::color_chinook_helicopter.g;
			if( feature_name == xs( "color_chinook_helicopter[2]" ) ) string_str >> options::visuals::world::color_chinook_helicopter.b;

			if( feature_name == xs( "color_patrol_helicopter[0]" ) ) string_str >> options::visuals::world::color_patrol_helicopter.r;
			if( feature_name == xs( "color_patrol_helicopter[1]" ) ) string_str >> options::visuals::world::color_patrol_helicopter.g;
			if( feature_name == xs( "color_patrol_helicopter[2]" ) ) string_str >> options::visuals::world::color_patrol_helicopter.b;

			if( feature_name == xs( "color_attack_helicopter[0]" ) ) string_str >> options::visuals::world::color_attack_helicopter.r;
			if( feature_name == xs( "color_attack_helicopter[1]" ) ) string_str >> options::visuals::world::color_attack_helicopter.g;
			if( feature_name == xs( "color_attack_helicopter[2]" ) ) string_str >> options::visuals::world::color_attack_helicopter.b;

			if( feature_name == xs( "ambient_color[0]" ) ) string_str >> options::visuals::world::ambient_color.r;
			if( feature_name == xs( "ambient_color[1]" ) ) string_str >> options::visuals::world::ambient_color.g;
			if( feature_name == xs( "ambient_color[2]" ) ) string_str >> options::visuals::world::ambient_color.b;

			if( feature_name == xs( "show_stashes" ) ) string_str >> options::visuals::world::show_stashes;
			if( feature_name == xs( "todsky" ) ) string_str >> options::visuals::world::todsky;
			if( feature_name == xs( "show_grenades" ) ) string_str >> options::visuals::world::show_grenades;
			if( feature_name == xs( "night_stars" ) ) string_str >> options::visuals::world::night_stars;
			if( feature_name == xs( "clear_underwater" ) ) string_str >> options::visuals::world::clear_underwater;
			if( feature_name == xs( "change_world_color" ) ) string_str >> options::visuals::world::change_world_color;

			if( feature_name == xs( "show_heal" ) ) string_str >> options::visuals::world::show_heal;
			if( feature_name == xs( "show_weapons" ) ) string_str >> options::visuals::world::show_weapons;
			if( feature_name == xs( "show_melee_weapons" ) ) string_str >> options::visuals::world::show_melee_weapons;
			if( feature_name == xs( "show_everything" ) ) string_str >> options::visuals::world::show_everything;

			if( feature_name == xs( "show_item_amount" ) ) string_str >> options::visuals::world::show_item_amount;
			if( feature_name == xs( "stars_size" ) ) string_str >> options::visuals::world::stars_size;
			if( feature_name == xs( "stars" ) ) string_str >> options::visuals::world::stars;
			if( feature_name == xs( "ambient" ) ) string_str >> options::visuals::world::ambient;
			if( feature_name == xs( "mie_changer" ) ) string_str >> options::visuals::world::mie_changer;

			if( feature_name == xs( "rayleigh_changer" ) ) string_str >> options::visuals::world::rayleigh_changer;
			if( feature_name == xs( "brightness_changer" ) ) string_str >> options::visuals::world::brightness_changer;
			if( feature_name == xs( "aspect_changer" ) ) string_str >> options::visuals::world::aspect_changer;
			if( feature_name == xs( "aspect_value" ) ) string_str >> options::visuals::world::aspect_value;
			if( feature_name == xs( "show_sulfur_ore" ) ) string_str >> options::visuals::world::show_sulfur_ore;
			if( feature_name == xs( "show_metal_ore" ) ) string_str >> options::visuals::world::show_metal_ore;
			if( feature_name == xs( "show_stone_ore" ) ) string_str >> options::visuals::world::show_stone_ore;
			if( feature_name == xs( "show_box_storages" ) ) string_str >> options::visuals::world::show_box_storages;
			if( feature_name == xs( "show_tool_cupboard" ) ) string_str >> options::visuals::world::show_tool_cupboard;
			if( feature_name == xs( "show_sulfur_ore" ) ) string_str >> options::visuals::world::show_sulfur_ore;
			if( feature_name == xs( "show_metal_ore" ) ) string_str >> options::visuals::world::show_metal_ore;
			if( feature_name == xs( "show_stone_ore" ) ) string_str >> options::visuals::world::show_stone_ore;
			if( feature_name == xs( "show_vending_machine" ) ) string_str >> options::visuals::world::show_vending_machine;
			if( feature_name == xs( "show_drone" ) ) string_str >> options::visuals::world::show_drone;
			if( feature_name == xs( "show_recycler" ) ) string_str >> options::visuals::world::show_recycler;

			if( feature_name == xs( "show_tool_cupboard" ) ) string_str >> options::visuals::world::show_tool_cupboard;
			if( feature_name == xs( "show_oil_barrel" ) ) string_str >> options::visuals::world::show_oil_barrel;
			if( feature_name == xs( "show_regular_barrels" ) ) string_str >> options::visuals::world::show_regular_barrels;
			if( feature_name == xs( "show_underwater_crate" ) ) string_str >> options::visuals::world::show_underwater_crate;
			if( feature_name == xs( "show_elite_crate" ) ) string_str >> options::visuals::world::show_elite_crate;
			if( feature_name == xs( "show_military_crate" ) ) string_str >> options::visuals::world::show_military_crate;
			if( feature_name == xs( "show_bradley_crate" ) ) string_str >> options::visuals::world::show_bradley_crate;

			if( feature_name == xs( "show_helicopter_crate" ) ) string_str >> options::visuals::world::show_helicopter_crate;
			if( feature_name == xs( "show_hackable_locked_crate" ) ) string_str >> options::visuals::world::show_hackable_locked_crate;
			if( feature_name == xs( "show_normal_crate" ) ) string_str >> options::visuals::world::show_normal_crate;
			if( feature_name == xs( "show_chickens" ) ) string_str >> options::visuals::world::show_chickens;
			if( feature_name == xs( "show_small_crate" ) ) string_str >> options::visuals::world::show_small_crate;
			if( feature_name == xs( "show_mine_crate" ) ) string_str >> options::visuals::world::show_mine_crate;
			if( feature_name == xs( "show_tool_box" ) ) string_str >> options::visuals::world::show_tool_box;
			if( feature_name == xs( "show_tool_cupboard" ) ) string_str >> options::visuals::world::show_tool_cupboard;
			if( feature_name == xs( "show_boars" ) ) string_str >> options::visuals::world::show_boars;
			if( feature_name == xs( "show_wolves" ) ) string_str >> options::visuals::world::show_wolves;
			if( feature_name == xs( "show_horses" ) ) string_str >> options::visuals::world::show_horses;

			if( feature_name == xs( "show_sharks" ) ) string_str >> options::visuals::world::show_sharks;
			if( feature_name == xs( "show_deers" ) ) string_str >> options::visuals::world::show_deers;
			if( feature_name == xs( "show_polar_bears" ) ) string_str >> options::visuals::world::show_polar_bears;

			if( feature_name == xs( "show_bears" ) ) string_str >> options::visuals::world::show_bears;
			if( feature_name == xs( "show_sulfur_collectibles" ) ) string_str >> options::visuals::world::show_sulfur_collectibles;
			if( feature_name == xs( "show_metal_collectibles" ) ) string_str >> options::visuals::world::show_metal_collectibles;
			if( feature_name == xs( "show_wood_collectibles" ) ) string_str >> options::visuals::world::show_wood_collectibles;
			if( feature_name == xs( "show_stone_collectibles" ) ) string_str >> options::visuals::world::show_military_crate;

			if( feature_name == xs( "show_supply_signals" ) ) string_str >> options::visuals::world::show_supply_signals;
			if( feature_name == xs( "show_supply_drops" ) ) string_str >> options::visuals::world::show_supply_drops;
			if( feature_name == xs( "show_ammo_nails_arrows" ) ) string_str >> options::visuals::world::show_ammo_nails_arrows;

			if( feature_name == xs( "show_food_crate" ) ) string_str >> options::visuals::world::show_food_crate;
			if( feature_name == xs( "show_medical_crate" ) ) string_str >> options::visuals::world::show_medical_crate;


			if( feature_name == xs( "show_duo_submarine" ) ) string_str >> options::visuals::world::show_duo_submarine;
			if( feature_name == xs( "show_solo_submarine" ) ) string_str >> options::visuals::world::show_solo_submarine;
			if( feature_name == xs( "show_small_motorboat" ) ) string_str >> options::visuals::world::show_small_motorboat;

			if( feature_name == xs( "show_kayak" ) ) string_str >> options::visuals::world::show_kayak;

			if( feature_name == xs( "show_bradley_apc" ) ) string_str >> options::visuals::world::show_bradley_apc;
			if( feature_name == xs( "show_rhib" ) ) string_str >> options::visuals::world::show_rhib;
			if( feature_name == xs( "show_scrap_helicopter" ) ) string_str >> options::visuals::world::show_scrap_helicopter;
			if( feature_name == xs( "show_minicopter" ) ) string_str >> options::visuals::world::show_minicopter;
			if( feature_name == xs( "show_two_modules_car" ) ) string_str >> options::visuals::world::show_two_modules_car;
			if( feature_name == xs( "show_modular_car" ) ) string_str >> options::visuals::world::show_modular_car;

			if( feature_name == xs( "show_potatos" ) ) string_str >> options::visuals::world::show_potatos;
			if( feature_name == xs( "show_corns" ) ) string_str >> options::visuals::world::show_corns;
			if( feature_name == xs( "show_berrys" ) ) string_str >> options::visuals::world::show_berrys;
			if( feature_name == xs( "show_pumpkin" ) ) string_str >> options::visuals::world::show_pumpkin;
			if( feature_name == xs( "show_mushroom" ) ) string_str >> options::visuals::world::show_mushroom;
			if( feature_name == xs( "show_hemp" ) ) string_str >> options::visuals::world::show_hemp;

			if( feature_name == xs( "show_potatos" ) ) string_str >> options::visuals::world::show_potatos;
			if( feature_name == xs( "show_corns" ) ) string_str >> options::visuals::world::show_corns;
			if( feature_name == xs( "show_berrys" ) ) string_str >> options::visuals::world::show_berrys;
			if( feature_name == xs( "show_pumpkin" ) ) string_str >> options::visuals::world::show_pumpkin;
			if( feature_name == xs( "show_mushroom" ) ) string_str >> options::visuals::world::show_mushroom;
			if( feature_name == xs( "show_hemp" ) ) string_str >> options::visuals::world::show_hemp;

			if( feature_name == xs( "show_potatos" ) ) string_str >> options::visuals::world::show_potatos;
			if( feature_name == xs( "show_corns" ) ) string_str >> options::visuals::world::show_corns;
			if( feature_name == xs( "show_berrys" ) ) string_str >> options::visuals::world::show_berrys;
			if( feature_name == xs( "show_pumpkin" ) ) string_str >> options::visuals::world::show_pumpkin;
			if( feature_name == xs( "show_mushroom" ) ) string_str >> options::visuals::world::show_mushroom;
			if( feature_name == xs( "show_hemp" ) ) string_str >> options::visuals::world::show_hemp;

			if( feature_name == xs( "show_landmines" ) ) string_str >> options::visuals::world::show_landmines;
			if( feature_name == xs( "show_npc_turrets" ) ) string_str >> options::visuals::world::show_npc_turrets;
			if( feature_name == xs( "show_auto_turrets" ) ) string_str >> options::visuals::world::show_auto_turrets;
			if( feature_name == xs( "show_shotgun_traps" ) ) string_str >> options::visuals::world::show_shotgun_traps;
			if( feature_name == xs( "show_tesla_coil" ) ) string_str >> options::visuals::world::show_tesla_coil;

			if( feature_name == xs( "show_flame_turrets" ) ) string_str >> options::visuals::world::show_flame_turrets;
			if( feature_name == xs( "show_sam_site" ) ) string_str >> options::visuals::world::show_sam_site;
			if( feature_name == xs( "show_bear_trap" ) ) string_str >> options::visuals::world::show_bear_trap;

			if( feature_name == xs( "size_stars_amount" ) ) string_str >> options::visuals::world::size_stars_amount;
			if( feature_name == xs( "brightness_stars_amount" ) ) string_str >> options::visuals::world::brightness_stars_amount;
			if( feature_name == xs( "ambient_value" ) ) string_str >> options::visuals::world::ambient_value;
			if( feature_name == xs( "aspect_value" ) ) string_str >> options::visuals::world::aspect_value;
			if( feature_name == xs( "light_value" ) ) string_str >> options::visuals::world::light_value;
			if( feature_name == xs( "rayleigh_amount" ) ) string_str >> options::visuals::world::rayleigh_amount;
			if( feature_name == xs( "brightness_amount" ) ) string_str >> options::visuals::world::brightness_amount;
			if( feature_name == xs( "mie_amount" ) ) string_str >> options::visuals::world::mie_amount;

			if( feature_name == xs( "size_stars_amount" ) ) string_str >> options::visuals::world::size_stars_amount;
			if( feature_name == xs( "brightness_stars_amount" ) ) string_str >> options::visuals::world::brightness_stars_amount;
			if( feature_name == xs( "ambient_value" ) ) string_str >> options::visuals::world::ambient_value;
			if( feature_name == xs( "light_value" ) ) string_str >> options::visuals::world::light_value;
			if( feature_name == xs( "rayleigh_amount" ) ) string_str >> options::visuals::world::rayleigh_amount;
			if( feature_name == xs( "brightness_amount" ) ) string_str >> options::visuals::world::brightness_amount;
			if( feature_name == xs( "mie_amount" ) ) string_str >> options::visuals::world::mie_amount;

			// distance
			if( feature_name == xs( "max_cars_distance" ) ) string_str >> options::visuals::world::max_cars_distance;
			if( feature_name == xs( "max_barrels_distance" ) ) string_str >> options::visuals::world::max_barrels_distance;
			if( feature_name == xs( "max_ores_distance" ) ) string_str >> options::visuals::world::max_ores_distance;
			if( feature_name == xs( "max_grenade_distance" ) ) string_str >> options::visuals::world::max_grenade_distance;
			if( feature_name == xs( "max_food_collectibles_distance" ) ) string_str >> options::visuals::world::max_food_collectibles_distance;
			if( feature_name == xs( "max_container_distance" ) ) string_str >> options::visuals::world::max_container_distance;
			if( feature_name == xs( "max_corpse_distance" ) ) string_str >> options::visuals::world::max_corpse_distance;
			if( feature_name == xs( "max_vehicle_distance" ) ) string_str >> options::visuals::world::max_vehicle_distance;
			if( feature_name == xs( "max_ore_collectibles_distance" ) ) string_str >> options::visuals::world::max_ore_collectibles_distance;
			if( feature_name == xs( "max_respawn_points_distance" ) ) string_str >> options::visuals::world::max_respawn_points_distance;
			if( feature_name == xs( "max_helicopter_distance" ) ) string_str >> options::visuals::world::max_helicopter_distance;
		}
	}
	cfg_file.close( );
	std::cout << xs( "loaded file with name: " ) << filename << std::endl;
	options::load_cfg = false;
}
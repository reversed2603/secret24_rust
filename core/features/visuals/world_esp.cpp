#include "world_esp.hpp"
#include "esp.h"
#include "../options.h"
#include "../../includes/fnv1a.hpp"
#include "../../utilities/memory.hpp"
#include "../../game/offsets.hpp"

// create global definition for world class.
c_world_esp g_world;

void c_world_esp::render( vec4_t render_position, std::string class_name,
	std::string obj_name, int distance, core::base_combat_entity* combat_entity,
	event_type event, core::base_entity* base_entity )
{
	if( !options::visuals::world::master_switch 
		|| event != event_type::re_paint
		|| distance >= 5000 )
		return;

	std::string dist_str = std::to_string( static_cast< int >( distance ) );
	std::string text = std::string( );
	color_t color = color_t( 0, 0, 0, 0 );

	float closest_distance = FLT_MAX;
		
	core::base_player* local = g_cheat.local;
	if( !local )
		return;

	static float last_sent_tick = local->lastSentTickTime( );

	//g_render.draw_text( render_position, obj_name, color_t( 255, 255, 255 ) );
	if( options::visuals::prefab_name_debug ) {
		render_position.y += 15;
		g_render.draw_text( render_position, obj_name, color_t( 255, 255, 255 ), false, 10, g_esp.font_flags );
		render_position.y -= 15;
	}

	if( options::visuals::class_name_debug ) {
		render_position.y += options::visuals::prefab_name_debug ? 30 : 15;

		g_render.draw_text( vec4_t( render_position.x, render_position.y + 40, render_position.z, render_position.w ), 
			class_name, color_t( 255 ,255, 255 ), false, 10, g_esp.font_flags );

		render_position.y -= options::visuals::prefab_name_debug ? 30 : 15;
	}

	if( distance < options::visuals::world::max_grenade_distance
		&& options::visuals::world::show_grenades ) {
		if( strstr( obj_name.c_str( ), xs( "grenade.f1.deployed.prefab" ) ) )
		{
			color = color_t( 177, 232, 95 );
			text = xs( "f1 grenade" );
		}
		if( strstr( obj_name.c_str( ), xs( "grenade.flashbang.deployed.prefab" ) ) )
		{
			color = color_t( 165, 183, 201 );
			text = xs( "flashbang" );
		}
		if( strstr( obj_name.c_str( ), xs( "grenade.molotov.deployed.prefab" ) ) )
		{
			color = color_t( 199, 138, 74 );
			text = xs( "molotov" );
		}
		if( strstr( obj_name.c_str( ), xs( "grenade.beancan.deployed.prefab" ) ) )
		{
			color = color_t( 220, 220, 220 );
			text = xs( "bean can" );
		}
	}
	if( distance < options::visuals::world::max_corpse_distance ) {
		bool npc_corpse = class_name == xs( "NPCPlayerCorpse" );
		if( ( class_name == xs( "PlayerCorpse" ) || npc_corpse )
			&& options::visuals::world::show_corpse )
		{
			color = options::visuals::world::color_corpse;
			text = npc_corpse ? xs( "npc corpse" ) : xs( "player corpse" );
		}
		if( strstr( obj_name.c_str( ), xs( "item_drop_backpack.prefab" ) )
			&& options::visuals::world::show_backpack )
		{
			color = options::visuals::world::color_backpack;
			text = xs( "backpack" );
		}
	}
	if( distance < options::visuals::world::max_ores_distance
		&& class_name == xs( "OreResourceEntity" ) ) {
		if( ( strstr( obj_name.c_str( ), xs( "metal-ore.prefab" ) )
			|| strstr( obj_name.c_str( ), xs( "ore_metal.prefab" ) ) )
			&& options::visuals::world::show_metal_ore ) {
			color = options::visuals::world::color_metal_ore;
			text = xs( "metal ore" );
		}
		else if( ( strstr( obj_name.c_str( ), xs( "sulfur-ore.prefab" ) )
			|| strstr( obj_name.c_str( ), xs( "ore_sulfur.prefab" ) ) )
			&& options::visuals::world::show_sulfur_ore ) {
			color = options::visuals::world::color_sulfur_ore;
			text = xs( "sulfur ore" );
		}
		else if( ( strstr( obj_name.c_str( ), xs( "stone-ore.prefab" ) )
			|| strstr( obj_name.c_str( ), xs( "ore_stone.prefab" ) ) )
			&& options::visuals::world::show_stone_ore ) {
			color = options::visuals::world::color_stone_ore;
			text = xs( "stone ore" );
		}
	}
	if( distance < options::visuals::world::max_item_distance ) {
		core::item* item = base_entity->get_world_item( );
		if( item ) {
			if( class_name == xs( "DroppedItem" ) )
			{
				int item_amt = item->get_amount( );
				std::string item_amount = std::to_string( item_amt );

				text = g_sdk.ws2s( item->get_weapon_name( ) );
				if( options::visuals::world::show_item_amount 
					&& item_amt > 1 )
					text += ( " x" ) + item_amount;

				if( text.find( "arrow" ) != std::string::npos 
					|| text.find( "nails" ) != std::string::npos ) {
					color = color_t( 143, 165, 199 );
					if( !options::visuals::world::show_ammo_nails_arrows )
						return;
				}
				else if( item->is_gun( ) ) {
					color = color_t( 145, 187, 255 );
					if( !options::visuals::world::show_weapons )
						return;
				}
				else if( item->is_melee( ) ) {
					color = color_t( 145, 156, 255 );
					if( !options::visuals::world::show_melee_weapons )
						return;
				}
				else if( item->is_heal( )
					&& !options::visuals::world::show_heal ) {
					color = color_t( 188, 255, 112 );
					return;
				}
				else if( !options::visuals::world::show_everything ) {
					color = color_t( 230, 247, 255 );
					return;
				}
				else if( text.find( "scrap" ) != std::string::npos )
					color = color_t( 222, 113, 60 );
				else if( text.find( "ammo" ) != std::string::npos ) {
					if( text.find( "incendiary" ) != std::string::npos )
						color = color_t( 255, 169, 112 );
					else if( text.find( "hv" ) != std::string::npos )
						color = color_t( 112, 169, 255 ); 
					else if( text.find( "explosive" ) != std::string::npos )
						color = color_t( 255, 119, 28 );
					else 
						color = color_t( 159, 167, 196 );
				}
				else if( text.find( "blue" ) != std::string::npos )
					color = color_t( 173, 199, 255 );
				else if( text.find( "white" ) != std::string::npos )
					color = color_t( 255, 255, 255 );
				else if( text.find( "green" ) != std::string::npos )
					color = color_t( 199, 255, 173 );
				else if( text.find( "red" ) != std::string::npos )
					color = color_t( 255, 110, 139 );
				else if( text.find( "purple" ) != std::string::npos )
					color = color_t( 156, 110, 255 );
				else if( text.find( "yellow" ) != std::string::npos )
					color = color_t( 217, 197, 95 );
				else
					color = color_t( 217, 237, 255 );
			}
		}
		if( class_name == xs( "Drone" )
			&& options::visuals::world::show_drone )
		{
			color = options::visuals::world::color_drone;
			text = xs( "drone" );
		}
		if( class_name == xs( "Recycler" ) )
		{  
			if( base_entity 
				&& options::aimbot::exploits::misc::stop_recycler
				&& distance < 5.f 
				&& ( local->lastSentTickTime( ) - last_sent_tick ) > 2.5 ) {
				base_entity->server_rpc( "SVSwitch" );
				last_sent_tick = local->lastSentTickTime( );
			}

			if( options::visuals::world::show_recycler ) {
				color = options::visuals::world::color_recycler;
				text = xs( "recycler" );
			}
		}
	}
	if( distance < options::visuals::world::max_respawn_points_distance )
	{
		if( class_name == xs( "SleepingBag" ) )
		{
			color = color_t( 175, 175, 175 );
			text = xs( "sleeping bag" );
		}
		if( strstr( obj_name.c_str( ), "bed_deployed.prefab" ) )
		{
			color = color_t( 225, 225, 225 );
			text = xs( "bed" );
		}
	}
	if( distance < options::visuals::world::max_raid_distance )
	{
		if( strstr( obj_name.c_str( ), "c4_explosion.prefab" ) ) {
			text = xs( "c4" );
			color = color_t( 255, 0, 0 );
		}
		else if( strstr( obj_name.c_str( ), xs( "satchel-charge-explosion.prefab" ) ) ) {
			text = xs( "satchel" );
			color = color_t( 242, 164, 63 );
		}
		else if( strstr( obj_name.c_str( ), xs( "beancan_grenade_explosion.prefab" ) ) ) {
			text = xs( "bean can grenade" );
			color = color_t( 255, 114, 59 );
		}
		else if( strstr( obj_name.c_str( ), xs( "rocket_explosion.prefab" ) ) ) {
			text = xs( "rocket" );
			color = color_t( 255, 114, 59 );
		}
	}
	if( distance < options::visuals::world::max_container_distance )
	{
		if( class_name == xs( "HackableLockedCrate" )
			&& options::visuals::world::show_hackable_locked_crate )
		{
			text = xs( "hackable crate" );
			color = options::visuals::world::color_hackable_locked_crate;
		}
		else if( class_name == xs( "LootContainer" ) )
		{
			if( strstr( obj_name.c_str( ), xs( "crate_elite.prefab" ) )
				&& options::visuals::world::show_elite_crate )
			{
				text = xs( "elite crate" );
				color = options::visuals::world::color_elite_crate;
			}
			else if( strstr( obj_name.c_str( ), xs( "crate_basic.prefab" ) )
				&& options::visuals::world::show_small_crate )
			{
				text = xs( "small crate" );
				color = options::visuals::world::color_small_crate;
			}
			else if( strstr( obj_name.c_str( ), xs( "crate_normal_2.prefab" ) )
				&& options::visuals::world::show_normal_crate )
			{
				text = xs( "crate" );
				color = options::visuals::world::color_normal_crate;
			}
			else if( strstr( obj_name.c_str( ), xs( "crate_underwater_advanced.prefab" ) )
				&& options::visuals::world::show_underwater_crate )
			{
				text = xs( "advanced underwater crate" );
				color = color_t( 3, 136, 252 );

				if( options::aimbot::exploits::misc::auto_untie_crates
					&& distance < 5.f )
					base_entity->server_rpc( xs( "RPC_FreeCrate" ) ); 
			}
			else if( strstr( obj_name.c_str( ), xs( "crate_underwater_basic.prefab" ) )
				&& options::visuals::world::show_underwater_crate )
			{
				text = xs( "underwater crate" );
				color = color_t( 113, 159, 199 );

				if( options::aimbot::exploits::misc::auto_untie_crates
					&& distance < 5.f )
					base_entity->server_rpc( xs( "RPC_FreeCrate" ) ); 
			}
			else if( strstr( obj_name.c_str( ), xs( "crate_tools.prefab" ) )
				&& options::visuals::world::show_tool_box )
			{
				text = xs( "toolbox" );
				color = options::visuals::world::color_tool_box;
			}
			else if( strstr( obj_name.c_str( ), xs( "crate_normal.prefab" ) )
				&& options::visuals::world::show_military_crate )
			{
				text = xs( "military crate" );
				color = options::visuals::world::color_military_crate;
			}
			else if( ( strstr( obj_name.c_str( ), xs( "minecart.prefab" ) ) )
				&& options::visuals::world::show_mine_crate )
			{
				text = xs( "mine crate" );
				color = options::visuals::world::color_mine_crate;
			}
			else if( ( strstr( obj_name.c_str( ), xs( "crate_foodbox.prefab" ) ) 
				|| strstr( obj_name.c_str( ), xs( "crate_normal_2_food.prefab" ) ) )
				&& options::visuals::world::show_food_crate )
			{
				text = xs( "food crate" );
				color = options::visuals::world::color_food_crate;
			}
			//else if( strstr( obj_name.c_str( ), xs( "crate_bradley.prefab" ) ) )
			//{
			//	text = xs( "bradley crate" );
			//	color = color_t( 206, 255, 150 ) ;
			//}
			//else if( strstr( obj_name.c_str( ), xs( "codelockedhackablecrate.prefab" ) ) )
			//{
			//	text = xs( "hackable crate" );
			//	color = color_t( 206, 255, 150 ) ;
			//}
			//else if( strstr( obj_name.c_str( ), xs( "codelockedhackablecrate_oilrig.prefab" ) ) )
			//{
			//	text = xs( "hackable oil-rig crate" );
			//	color = color_t( 206, 255, 150 ) ;
			//}
			else if( strstr( obj_name.c_str( ), xs( "crate_normal_2_medic.prefab" ) )
				&& options::visuals::world::show_medical_crate )
			{
				text = xs( "medic crate" );
				color = options::visuals::world::color_medical_crate;
			}
			//else if( strstr( obj_name.c_str( ), xs( "codelockedhackablecrate.prefab" ) ) )
			//{
			//	text = xs( "hackable crate" );
			//	color = color_t( 206, 255, 150 ) ;
			//}
			//else if( strstr( obj_name.c_str( ), xs( "codelockedhackablecrate_oilrig.prefab" ) ) )
			//{
			//	text = xs( "hackable oil-rig crate" );
			//	color = color_t( 206, 255, 150 ) ;
			//}
		}
		else if( class_name == xs( "SupplyDrop" )
			&& options::visuals::world::show_supply_drops )
		{
			color = options::visuals::world::color_supply_drops;
			text = xs( "supply drop" );
		}
		else if( class_name == xs( "SupplySignal" )
			&& options::visuals::world::show_supply_signals )
		{
			color = options::visuals::world::color_supply_signals;
			text = xs( "supply signal" );
		}
		else if( ( strstr( obj_name.c_str( ), xs( "bradley_crate" ) ) && strstr( obj_name.c_str( ), xs( ".prefab" ) ) )
			&& options::visuals::world::show_bradley_crate )
		{
			text = xs( "bradley crate" );
			color = options::visuals::world::color_bradley_crate;
		}
		else if( strstr( obj_name.c_str( ), xs( "heli_crate.prefab" ) )
			&& options::visuals::world::show_helicopter_crate )
		{
			text = xs( "helicopter crate" );
			color = options::visuals::world::color_helicopter_crate;
		}
		//else if( class_name == xs( "MobileMapMarker" )
			//&& class_name != xs( "HackableLockedCrate" ) )
		//{
			//text = xs( "marker" );
					
			//g_render.draw_text( render_position, text, color_t( 255, 255, 255 ), false, 10, font_flags_t::dropshadow );
		//}
	}
	if( distance < options::visuals::world::max_food_collectibles_distance )
	{
		if( strstr( obj_name.c_str( ), xs( "hemp/hemp" ) )
			&& options::visuals::world::show_hemp ) {
			text = xs( "hemp" );
			color = options::visuals::world::color_hemp;
		}
		else if( strstr( obj_name.c_str( ), xs( "mushroom-cluster-6.prefab" ) )
			&& options::visuals::world::show_mushroom ) {
			text = xs( "mushroom" );
			color = options::visuals::world::color_mushroom;
		}
		else if( strstr( obj_name.c_str( ), xs( "pumpkin-collectable.prefab" ) )
			&& options::visuals::world::show_pumpkin ) {
			text = xs( "pumpkin" );
			color = options::visuals::world::color_pumpkin;
		}
		else if( strstr( obj_name.c_str( ), xs( "corn-collectable.prefab" ) )
			&& options::visuals::world::show_corns ) {
			text = xs( "corn" );
			color = options::visuals::world::color_corns;
		}
		else if( strstr( obj_name.c_str( ), xs( "berry-" ) )
			&& options::visuals::world::show_berrys ) {
			text = xs( "berry" );
			color = color_t( 143, 128, 217 );
			if( strstr( obj_name.c_str( ), xs( "white" ) ) )
				color = color_t( 209, 209, 209 );
			if( strstr( obj_name.c_str( ), xs( "yellow" ) ) )
				color = color_t( 235, 196, 89 );
			if( strstr( obj_name.c_str( ), xs( "blue" ) ) )
				color = color_t( 115, 171, 255 );
			if( strstr( obj_name.c_str( ), xs( "red" ) ) )
				color = color_t( 255, 46, 99 );
			if( strstr( obj_name.c_str( ), xs( "black" ) ) )
				color = color_t( 150, 150, 150 );
			if( strstr( obj_name.c_str( ), xs( "green" ) ) )
				color = color_t( 117, 255, 117 );
		}
		else if( strstr( obj_name.c_str( ), xs( "potato-collectable.prefab" ) )
			&& options::visuals::world::show_potatos ) {
			text = xs( "potato" );
			color = options::visuals::world::color_potatos;
		}
	}

	if( distance < options::visuals::world::max_ore_collectibles_distance )
	{
		if( strstr( obj_name.c_str( ), xs( "metal-collectable.prefab" ) )
			&& options::visuals::world::show_metal_collectibles ) {
			text = xs( "metal collectible" );
			color = options::visuals::world::color_metal_collectibles;
		}
		else if( strstr( obj_name.c_str( ), xs( "wood-collectable.prefab" ) ) 
			&& options::visuals::world::show_wood_collectibles ) {
			text = xs( "wood collectible" );
			color = options::visuals::world::color_wood_collectibles;
		}
		else if( strstr( obj_name.c_str( ), xs( "stone-collectable.prefab" ) )
			&& options::visuals::world::show_stone_collectibles ) {
			text = xs( "stone collectible" );
			color = options::visuals::world::color_stone_collectibles;
		}
		else if( strstr( obj_name.c_str( ), xs( "sulfur-collectable.prefab" ) )
			&& options::visuals::world::show_sulfur_collectibles ) {
			text = xs( "sulfur collectible" );
			color = options::visuals::world::color_sulfur_collectibles;
		}
	}

	//std::string stash_state = std::string( );
	//core::stash_container* stash_container = reinterpret_cast< core::stash_container* >( combat_entity );

	//if( stash_container ) {
	//	float buried_offset = stash_container->get_burried_offset( );
	//	if( buried_offset == 2048 )
	//		stash_state = " | buried";
	//	else if( buried_offset == 8 )
	//		stash_state = " | being looted";
	//	else
	//		stash_state = " | not buried";

	//	stash_state += std::to_string( buried_offset );

	//	if( distance < options::visuals::world::max_stash_distance 
	//		&& options::visuals::world::show_stashes ) {
	//		if( class_name == xs( "StashContainer" ) )
	//		{
	//			text = xs( "stash" ) + stash_state;
	//			
	//			g_render.draw_text( render_position, text, color_t( 255, 255, 255 ), false, 10, font_flags_t::dropshadow );
	//		}
	//	}
	//}

	if( distance < options::visuals::world::max_barrels_distance )
	{
		bool is_barrel = false;

		if( class_name == xs( "LootContainer" ) )
		{
			if( ( strstr( obj_name.c_str( ), xs( "loot-barrel-1.prefab" ) )
				|| strstr( obj_name.c_str( ), xs( "loot-barrel-2.prefab" ) )
				|| ( strstr( obj_name.c_str( ), xs( "loot_barrel_1.prefab" ) )
				|| strstr( obj_name.c_str( ), xs( "loot_barrel_2.prefab" ) ) ) ) )
			{
				if( options::visuals::world::show_regular_barrels ) {
					text = xs( "barrel" );
					if( strstr( obj_name.c_str( ), xs( "loot-barrel-1.prefab" ) )
						|| strstr( obj_name.c_str( ), xs( "loot_barrel_1.prefab" ) ) )
						color = color_t( 135, 177, 222 );
					else
						color = color_t( 227, 193, 113 );
				}
				is_barrel = true;
			}
			else if( strstr( obj_name.c_str( ), xs( "oil_barrel.prefab" ) ) )
			{
				if( options::visuals::world::show_oil_barrel ) {
					text = xs( "oil barrel" );
					color = options::visuals::world::color_oil_barrel;
				}
				is_barrel = true;
			}
		}
		else if( ( strstr( obj_name.c_str( ), xs( "diesel" ) ) && strstr( obj_name.c_str( ), xs( ".prefab" ) ) ) )
		{
			if( options::visuals::world::show_diesel_fuel ) {
				text = xs( "diesel fuel" );
				color = options::visuals::world::color_diesel_fuel;
			}
			is_barrel = true;
		}

		if( options::aimbot::exploits::misc::auto_farm_barrels ) {
			if( is_barrel ) {
				core::transform* transform = base_entity->get_transform( );
				if( transform
					&& distance < g_esp.melee_max_dist )
					g_esp.do_melee_attack( transform->get_position( ), base_entity, false );
			}
		}
	}
	if( distance < options::visuals::world::max_cars_distance )
	{
		if( !strstr( obj_name.c_str( ), xs( "lift" ) ) ) {
			if( strstr( obj_name.c_str( ), xs( "modularcar" ) )
				&& options::visuals::world::show_modular_car )
			{
				text = xs( "modular car" );
				color = options::visuals::world::color_modular_car;
			}
			else if( strstr( obj_name.c_str( ), xs( "2module_camper" ) )
				&& options::visuals::world::show_two_modules_car )
			{
				text = xs( "two module car" );
				color = options::visuals::world::color_two_modules_car;
			}
		}
	}
	if( distance < options::visuals::world::max_storage_distance )
	{
		//std::string upkeep_time = std::to_string( static_cast< int >( base_entity->get_protected_minutes( ) / 60 ) );

		if( class_name == xs( "BuildingPrivlidge" )
			&& options::visuals::world::show_tool_cupboard )
		{
			color = options::visuals::world::color_tool_cupboard;
			text = xs( "tool cupboard" );
		}
		if( class_name == xs( "VendingMachine" )
			&& options::visuals::world::show_vending_machine )
		{
			color = options::visuals::world::color_vending_machine;
			text = xs( "vending machine" );
		}
		if( class_name == xs( "BoxStorage" )
			&& options::visuals::world::show_box_storages )
		{
			color = options::visuals::world::color_box_storages;
			text = xs( "box storage" );
		}
	}

	if( distance < options::visuals::world::max_stash_distance 
		&& options::visuals::world::show_stashes ) {
		if( class_name == xs( "StashContainer" ) )
		{
			color = options::visuals::world::color_stashes;
			text = xs( "stash" );
		}
	}
	if( distance < options::visuals::world::max_animal_distance ) {
		if( class_name == xs( "Boar" )
			&& options::visuals::world::show_boars )
		{
			text = xs( "boar" );
			color = options::visuals::world::color_boars;
		}
		if( class_name == xs( "Chicken" )
			&& options::visuals::world::show_chickens )
		{	
			color = options::visuals::world::color_chickens;
			text = xs( "chicken" );
		}
		if( class_name == xs( "Stag" ) 
			&& options::visuals::world::show_deers )
		{
			color = options::visuals::world::color_deers;
			text = xs( "deer" );
		}
		if( class_name == xs( "Wolf" )
			&& options::visuals::world::show_wolves )
		{
			color = options::visuals::world::color_wolves;
			text = xs( "wolf" );
		}
		if( class_name == xs( "Bear" )
			&& options::visuals::world::show_bears )
		{
			color = options::visuals::world::color_bears;
			text = xs( "bear" );
		}
		if( class_name == xs( "Polarbear" )
			&& options::visuals::world::show_polar_bears )
		{
			color = options::visuals::world::color_polar_bears;
			text = xs( "polar bear" );
		}
		if( class_name == xs( "RidableHorse" )
			&& options::visuals::world::show_horses )
		{
			color = options::visuals::world::color_horses;
			text = xs( "horse" );
		}
		if( strstr( obj_name.c_str( ), xs( "simpleshark.prefab" ) )
			&& options::visuals::world::show_sharks )
		{
			color = options::visuals::world::color_sharks;
			text = xs( "shark" );
		}
	}
	if( distance < options::visuals::world::max_vehicle_distance )
	{
		if( strstr( obj_name.c_str( ), xs( "submarineduo.entity.prefab" ) )
			&& options::visuals::world::show_duo_submarine )
		{
			color = options::visuals::world::color_duo_submarine;
			text = xs( "duo submarine" );
		}
		if( strstr( obj_name.c_str( ), xs( "submarinesolo.entity.prefab" ) )
			&& options::visuals::world::show_solo_submarine )
		{
			color = options::visuals::world::color_solo_submarine;
			text = xs( "solo submarine" );
		}
		if( class_name == xs( "MotorRowboat" )
			&& options::visuals::world::show_small_motorboat )
		{
			color = options::visuals::world::color_small_motorboat;
			text = xs( "motor boat" );
		}
		if( strstr( obj_name.c_str( ), xs( "kayak.prefab" ) )
			&& options::visuals::world::show_kayak )
		{
			color = options::visuals::world::color_kayak;
			text = xs( "kayak" );
		}
		if( class_name == xs( "RHIB" )
			&& options::visuals::world::show_rhib )
		{
			color = options::visuals::world::color_rhib;
			text = xs( "rhib" );
		}
		if( strstr( obj_name.c_str( ), xs( "bradleyapc.prefab" ) )
			&& options::visuals::world::show_bradley_apc )
		{
			color = options::visuals::world::color_bradley_apc;
			text = xs( "bradley apc" );
		}
		if( class_name == xs( "MiniCopter" )
			&& options::visuals::world::show_minicopter )
		{
			color = options::visuals::world::color_rhib;
			text = xs( "minicopter" );
		}
		if( class_name == xs( "ScrapTransportHelicopter" )
			&& options::visuals::world::show_scrap_helicopter )
		{
			color = options::visuals::world::color_scrap_helicopter;
			text = xs( "scrap helicopter" );
		}
	}
	if( distance < options::visuals::world::max_helicopter_distance ) {

		if( class_name == xs( "PatrolHelicopter" )
			&& options::visuals::world::show_patrol_helicopter )
		{
			color = options::visuals::world::color_patrol_helicopter;
			text = xs( "patrol helicopter" );
		}
		if( strstr( obj_name.c_str( ), xs( "attackhelicopter.entity.prefab" ) )
			&& options::visuals::world::show_attack_helicopter )
		{
			color = options::visuals::world::color_attack_helicopter;
			text = xs( "attack helicopter" );
		}
		if( strstr( obj_name.c_str( ), xs( "ch47.entity.prefab" ) )
			&& options::visuals::world::show_chinook_helicopter )
		{
			color = options::visuals::world::color_chinook_helicopter;
			text = xs( "chinook helicopter" );
		}
	}
	if( distance < options::visuals::world::max_trap_distance )
	{
		if( class_name == xs( "Landmine" ) 
			&& options::visuals::world::show_landmines )
		{
			color = options::visuals::world::color_landmines;
			text = xs( "landmine" );

			core::base_player* local = g_cheat.local;

			if( local ) {
				if( base_entity 
					&& options::aimbot::exploits::misc::disarm_landmines
					&& distance < 5.f 
					&& ( local->lastSentTickTime( ) - last_sent_tick ) > 0.05 ) {
					base_entity->server_rpc( "RPC_Disarm" );
					last_sent_tick = local->lastSentTickTime( );
				}
			}
		}
		if( class_name == xs( "NPCAutoTurret" )
			&& options::visuals::world::show_npc_turrets )
		{
			color = options::visuals::world::color_npc_turrets;
			text = xs( "npc turret" );
		}
		if( strstr( obj_name.c_str( ), xs( "spikes.floor.prefab" ) )
			&& options::visuals::world::show_land_spikes )
		{
			color = options::visuals::world::color_land_spikes;
			text = xs( "floor spikes" );
		}
		if( class_name == xs( "FlameTurret" )
			&& options::visuals::world::show_flame_turrets )
		{
			color = options::visuals::world::color_flame_turrets;
			text = xs( "flame turret" );
		}
		if( class_name == xs( "TeslaCoil" )
			&& options::visuals::world::show_tesla_coil )
		{
			color = options::visuals::world::color_tesla_coil;
			text = xs( "tesla coil" );
		}
		if( class_name == xs( "AutoTurret" )
			&& options::visuals::world::show_auto_turrets )
		{
			color = options::visuals::world::color_auto_turrets;
			text = xs( "turret" );
		}
		if( class_name == xs( "GunTrap" )
			&& options::visuals::world::show_shotgun_traps )
		{
			color = options::visuals::world::color_shotgun_traps;
			text = xs( "shotgun trap" );
		}
		if( class_name == xs( "SamSite" )
			&& options::visuals::world::show_sam_site )
		{
			color = options::visuals::world::color_sam_site;
			text = xs( "sam-site" );
		}
		if( class_name == xs( "BearTrap" )
			&& options::visuals::world::show_bear_trap )
		{
			color = options::visuals::world::color_bear_trap;
			text = xs( "bear trap" );
		}
	}

	if( !text.empty( )
		&& color.a > 0 ) {
		std::transform( text.begin( ), text.end( ), text.begin( ), ::tolower );

		bool show_distance = options::visuals::world::show_distance;
		bool show_health = options::visuals::world::show_health 
			&& combat_entity
			&& combat_entity->get_health( ) > 0;

		if( show_distance || show_health )
			text += xs( "[" );

		if( show_distance )
			text += dist_str + xs( "m" );
		
		if( show_health ) {
			std::string health_str = std::to_string( int( combat_entity->get_health( ) ) ) + xs( "hp" );

			text += show_distance ? xs( "|" ) + health_str : health_str;
		}

		if( show_distance || show_health )
			text += xs( "]" );

		g_render.draw_text( render_position, text, color, false, 10, g_esp.font_flags );
	}
}
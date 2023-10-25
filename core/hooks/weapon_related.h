#pragma once
#include "../includes/hinclude.h"
#include "../features/options.h"

namespace basemelee
{
	inline void process_attack_hook( core::item* base_item, core::hit_test* hittest )
	{
		auto orig_basemelee_process_attack = reinterpret_cast< void( * )( core::item*, core::hit_test* ) >( hook_address[ 0 ] );
		core::base_player* local = g_cheat.local;

		if( !local )
			return spoof_ret( orig_basemelee_process_attack, base_item, hittest );

		if( !options::aimbot::exploits::misc::always_hit_weak_spot )
			return spoof_ret( orig_basemelee_process_attack, base_item, hittest );

		core::base_entity* hit_entity = hittest->get_hit_entity( );
		if( !hit_entity )
			return spoof_ret( orig_basemelee_process_attack, base_item, hittest );

		core::transform* hit_entity_transform = hit_entity->get_transform( );
		if( !hit_entity_transform )
			return spoof_ret( orig_basemelee_process_attack, base_item, hittest );

		std::string hit_entity_class = hit_entity->get_class_name( );

		float max_dist = options::aimbot::exploits::combat::extended_melee ? options::aimbot::exploits::combat::attack_radius : 2;

		if( hit_entity_class == xs( "OreResourceEntity" ) )
		{
			core::base_entity* closest_object = g_esp.get_closest_object_of_class( xs( "OreHotSpot" ), max_dist );
			if( !closest_object )
				return spoof_ret( orig_basemelee_process_attack, base_item, hittest );

			core::transform* hot_spot_transform = closest_object->get_transform( );
			if( !hot_spot_transform )
				return spoof_ret( orig_basemelee_process_attack, base_item, hittest );

			hittest->set_hit_entity( hit_entity );
			hittest->set_hit_transform( hot_spot_transform );
			vec3_t hotspot_position = hot_spot_transform->get_position( );
			vec3_t inverse_point = hot_spot_transform->inverse_tranform_point( hotspot_position );
			hittest->set_hit_hitpoint( inverse_point );
		}
		else if( hit_entity_class == xs( "TreeEntity" ) )
		{
			vec3_t tree_pos = hit_entity_transform->get_position( );
			vec3_t inverse_point = hit_entity_transform->inverse_tranform_point( tree_pos + vec3_t( 0.f, 1.f, 0.f ) );
			float dist = g_cheat.local->get_closest_point( tree_pos ).distance( tree_pos );
			core::base_entity* closest_object = g_esp.get_closest_object_of_class( xs( "TreeMarker" ), max_dist );

			if( !closest_object )
			{
				hittest->set_hit_distance( dist );
				hittest->set_hit_hitpoint( inverse_point );
				return spoof_ret( orig_basemelee_process_attack, base_item, hittest );
			}
			else
			{
				core::transform* transform = closest_object->get_transform( );
				if( !transform )
					return spoof_ret( orig_basemelee_process_attack, base_item, hittest );

				vec3_t pos3 = transform->get_position( );
				vec3_t pos3_inverse_point = hit_entity_transform->inverse_tranform_point( pos3 );
				hittest->set_hit_distance( dist );
				hittest->set_hit_hitpoint( pos3_inverse_point );
				hit_entity->set_hit_direction( vec3_t( tree_pos.x, 0, tree_pos.z ) - vec3_t( pos3.x, 0, pos3.z ) );
				return spoof_ret( orig_basemelee_process_attack, base_item, hittest );
			}
		}

		return spoof_ret( orig_basemelee_process_attack, base_item, hittest );
	}
}
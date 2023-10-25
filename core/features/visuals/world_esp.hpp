#pragma once
#include "../../includes/includes.hpp"
#include "../../game/sdk.hpp"

class c_world_esp 
{
public:
	void render( vec4_t, std::string,
		std::string, int, core::base_combat_entity*,
		event_type, core::base_entity* );
};
extern c_world_esp g_world;
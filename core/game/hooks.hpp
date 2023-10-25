#pragma once
#include "../includes/hinclude.h"
#include "../features/menu/gui_hook.h"
#include "../hooks/player_related.h"
#include "../hooks/weapon_related.h"

namespace hooks
{
	__forceinline void init( )
	{
		hook_address[ 5 ] = *reinterpret_cast< uintptr_t* >( il2mgr::method( xs( "PerformanceUI" ), xs( "Update" ), 0, xs( "Facepunch" ) ) );

		il2mgr::hook( &perf_ui::performance_ui_update_hook, xs( "PerformanceUI" ), xs( "Update" ), 0, xs( "Facepunch" ) );
		il2mgr::hook( &perf_ui::ongui_hook, xs( "DevControls" ), xs( "OnGUI" ), 0, xs( "" ) );

		hook_address[ 0 ] = il2mgr::hook_virt( xs( "BaseMelee" ), xs( "ProcessAttack" ), &basemelee::process_attack_hook, 1 );
		hook_address[ 1 ] = il2mgr::hook_virt( xs( "BasePlayer" ), xs( "ClientInput" ), &baseplayer::client_input_hook, 1 );
		hook_address[ 2 ] = il2mgr::hook_virt( xs( "BasePlayer" ), xs( "VisUpdateUsingCulling" ), &baseplayer::fix_culling_hook, 2 );
		hook_address[ 3 ] = il2mgr::hook_virt( xs( "BasePlayer" ), xs( "OnAttacked" ), &baseplayer::on_attacked_hook, 1 );
		hook_address[ 4 ] = il2mgr::hook_virt( xs( "ItemIcon" ), xs( "TryToMove" ), &item_icon::try_to_move_hook, 0 );

		if (hook_address[4])
			printf("ayeee\n");
	}
}
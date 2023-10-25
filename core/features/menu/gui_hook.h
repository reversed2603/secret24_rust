#pragma once
#include "cfg.h"

namespace perf_ui
{
	void ongui_hook( );

	inline static bool first_loaded = true;
	void performance_ui_update_hook( void* instance );
}
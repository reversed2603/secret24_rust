#pragma once
#include "../includes/includes.hpp"
#include "il2cpp.hpp"
#include "enums.hpp"

#define print( a, args ) printf( "%s(%s:%d) " a,  __func__,__FILE__, __LINE__, ##args )
#define println( a, args ) print( a "\n", ##args )


template< typename T >
class laddy_list {
public:
	T get( uint32_t idx )
	{
		const auto internal_list = reinterpret_cast< uintptr_t >( this + 0x20 );
		return *reinterpret_cast< T* >( internal_list + idx * sizeof( T ) );
	}

	T get_value( uint32_t idx )
	{
		const auto list = *reinterpret_cast< uintptr_t* >( ( uintptr_t )this + 0x10 );
		const auto internal_list = list + 0x20;
		return *reinterpret_cast< T* >( internal_list + idx * sizeof( T ) );
	}

	T operator[ ]( uint32_t idx ) { return get( idx ); }

	const uint32_t get_size( ) { return *reinterpret_cast< uint32_t* >( ( uintptr_t )this + 0x18 ); }

	template< typename F >
	void for_each( const F callback )
	{
		for( auto i = 0; i < get_size( ); i++ ) {
			auto object = this->get( i );
			if( !object )
				continue;

			callback( object, i );
		}
	}
};

class camera
{
public:
	void				set_aspect_ratio( float );
	matrix_4x4			get_view_matrix( );
};

class c_sdk
{
public:
	vec2_t					world_to_screen( vec3_t ent_pos );

	char* memstr( char* haystack, const char* needle, int size );
	uintptr_t				scan_for_camera_list( );
	vec3_t					get_camera_pos( );
	vec3_t					get_mouse_pos( );
	int						get_screen_width( );
	uintptr_t				get_texture( uintptr_t sprite );
	int						get_screen_height( );
	float					realtimeSinceStartup( );
	float					get_fixedTime( );
	std::string				ws2s( const std::wstring& wstr );
	std::wstring			s2ws( const std::string& str );
	std::wstring			read_unicode( uint64_t address, std::size_t size );
	std::string				read_ascii( uint64_t address, std::size_t size = 0x50 );
	bool					get_key_down( key_code key );
	bool					get_key_up( key_code key );
	bool					get_key( int key );
	bool					get_key( key_code key );
	void					ignore_layer_collision( layer the_layer, layer ignore_layer, bool should_collide );
	bool					line_of_sight( vec3_t start, vec3_t end, int layer_mask, float padding = 0 );
	bool					is_visible( vec3_t start, vec3_t end );
	void					set_timescale( float );

	laddy_list< uintptr_t >* get2renderers( uintptr_t multimesh );
	uintptr_t				get_material( uintptr_t renderer );
	uintptr_t				get_shader( uintptr_t material );
	uintptr_t				load_asset( uintptr_t assetbundle, std::string shader, uintptr_t typeobject );
	uintptr_t				load_bundle_file( std::string data );
	uintptr_t				find( const char* shader );
	void					create_shader( uintptr_t self, uintptr_t shader );
	void					set_shader( uintptr_t material, uintptr_t shader );
	void					set_gl_color( color_t color );
	void					set_color( uintptr_t material, const char* name, color_t color );
	void					push_matrix( );
	void					begin( int mode );
	void					end( );
	void					pop_matrix( );
	void					vertex( vec3_t vertex );
	void					set_pass( uintptr_t material, int value );
	void					set_material_float( uintptr_t material, const char* name, float value );
	void					set_material_int( uintptr_t material, const char* name, int value );
	uintptr_t				get_current( );
	event_type				get_event_type( uintptr_t current );
	uintptr_t				get_draw_skin( );
	uintptr_t				get_white_texture( );
	uintptr_t				get_guicontent_temp( il2mgr::il2cppstring* content );
	void					set_draw_font_size( uintptr_t label, int size );
	void					set_draw_color( color_t color );
	void					set_draw_alignment( uintptr_t label, uintptr_t value );
	void					set_cursor_lockstate( int value );
	void					create( uintptr_t self, const char* shader );
	void					dont_destroy_on_load( uintptr_t target );
	void					add_component( uintptr_t self, uintptr_t componentType );
	void					draw_texture( vec4_t position, uintptr_t texture );

	uintptr_t				CreatePrefab( const char* prefab, bool active = true );
	void					Destroy( uintptr_t object );
	float					system_time( );
	float					get_time( );
	float					get_deltaTime( );

	float					random_range( float min, float max );
	bool					physics_checkcapsule( vec3_t start, vec3_t end, float radius, int layer_mask, QueryTriggerInteraction querytriggerinteraction );

	uintptr_t				get_component( uintptr_t game_object, const char* name_str );
};

extern c_sdk g_sdk;

class bone_data;

namespace core
{
	class transform
	{
	public:
		vec3_t				get_position( );
		void				set_position( vec3_t );
		vec3_t				inverse_tranform_point( vec3_t );
		vec3_t				transform_direction( vec3_t );
		vec3_t				up( );
	};

	class item;

	class item_icon {
	public:
		bool queued_for_looting( );
		void run_timed_action( );
	};

	class base_entity
	{
	public:
		std::wstring		get_name( );
		std::wstring	    get_item_name( );
		std::string			get_prefab_name( );
		std::string			get_prefab_namehash( );

		item*				get_world_item( );

		std::string			get_class_name( );
		vec3_t				get_visual_position( uintptr_t );
		vec3_t				get_closest_point( vec3_t position );
		transform*			get_transform( );
		float				get_max_speed( );
		float				max_velocity( );
		bool				mounted( );
		void				set_hit_direction( vec3_t value );
		void				server_rpc( const char* );
		static void			server_rpc( uintptr_t, const char* );
		static void			server_rpc( uintptr_t, const char*, const char*, bool );
		void				send_signal_broadcast( Signal signal, const char* arg = "" );
		float				get_protected_minutes( );
	};

	class base_combat_entity : public base_entity
	{
	public:
		float				get_health( );
		float				get_max_health( );
		int					get_life_state( );
	};

	class rigid_body
	{
	public:
		void				set_velocity( vec3_t val );
	};

	class base_player; // pre-declare.

	class player_walk_movement
	{
	public:
		rigid_body*			get_body( );
		void				set_ground_angle( float );
		float				get_ground_angle_new( );
		void				set_gravity_test_radius( float );
		void				set_ground_angle_new( float );
		void				set_is_running( float );
		void				set_max_angle_walking( float );
		void				set_max_angle_climbing( float );
		void				set_ground_time( float );
		void				set_previous_velocity( vec3_t );
		float				get_ground_time( );
		void				set_capsule_center( float );
		float				get_capsule_center( );
		void				set_capsule_height( float );
		float				get_capsule_height( );
		void				set_capsule_radius( float );
		void				set_gravity_multiplier( float );
		void				set_jump_time( float );
		void				set_land_time( float );
		vec3_t				get_targetmovement( );
		void				set_targetmovement( vec3_t );
		void				set_speed( float );
		bool				ducking( );
		void				set_was_falling( bool );
		void				teleport_to( vec3_t );
		bool				swimming( );
		void				set_grounded( bool );
		void				set_flying( bool );
		bool				flying( );
		void				set_is_grounded( float );
	};

	class input_message {
	public:
		void set_aim_angles( vec3_t );
	};

	class input_state {
	public:
		input_message* get_input_message( );
	};

	class player_input
	{
	public:
		vec2_t				get_view_angles( );
		vec2_t				get_recoil_angles( );
		void				set_view_angles( vec2_t angle );
		void				set_head_rotation( vec4_t angle );
		void				set_recoil_angles( vec2_t angle );
		input_state*		get_input_state( );
	};

	class item_definition : public base_entity
	{
	public:
		int					get_itemid( );
		std::wstring		get_shortname( );

	};

	struct weapon_information {
		float bullet_gravity{ }, bullet_speed{ }, drag{ };

		// ctor.
		weapon_information( ) {
			bullet_gravity = bullet_speed = drag = 0.f;
		};
		weapon_information( float gravity, float speed, float drag ) { 
			bullet_gravity = gravity; bullet_speed = speed, this->drag = drag;
		};
	};

	class base_projectile : public base_entity
	{
	public:
		class Magazine : public base_entity
		{
		public:
			int get_ammotype( );
			int& contents( );
		};

		void launch_projectile( );
		void update_ammo_display( );
		void did_attack_clientside( );

		void begin_cycle( );
		void shot_fired( );

		Magazine* get_primaryMagazine( );
	};

	struct Ray {
		vec3_t origin;
		vec3_t dir;
		Ray( ) { };
		
		Ray( vec3_t o, vec3_t d ) {
			origin = o;
			dir = d;
		}
	};

	class hit_test
	{
	public:
		static hit_test*	New( );
		base_entity*		get_hit_entity( );
		vec3_t				get_hit_normal( );
		void				set_hit_entity( base_entity* entity );
		void				set_hit_transform( transform* transform );
		void				set_hit_hitpoint( vec3_t hit_point );
		void				set_hit_distance( float distance );
		void				set_max_distance( float distance );
		void				set_did_hit( bool didhit );
		void				set_damage_properties( uintptr_t properties );
		void				set_attack_ray( Ray );
		void				set_hit_normal( vec3_t );
	};

	class item : public base_entity
	{
	public:
		int					get_amount( );
		int					get_uid( );
		int32_t				get_definition_id( );
		bool				is_deployed( );
		void				set_was_aiming( bool );
		void				set_attack_ready( bool );
		void				set_did_spark_this_frame( bool );
		float				get_attack_max_distance( );
		void				set_attack_max_distance( float );
		std::wstring		get_weapon_name( );
		void				send_broadcast_projectile( Signal signal, const char* text );
		std::wstring		get_short_name( );
		uintptr_t			get_sprite( );
		base_projectile*	get_base_projectile( );
		vec3_t				get_visual_position( uintptr_t );
		bool				get_recoil_min_max( vec2_t&, vec2_t& );
		void				set_bullet_thickness( float );
		void				set_can_attack( float );
		void				set_is_automatic( bool );
		void				set_is_burst( bool );
		void				set_recoil_min_max( float );
		base_entity*		get_held_entity( );
		float				get_bullet_velocity( );
		weapon_information  get_weapon_information( );
		float				bullet_gravity(  );
		float				get_bullet_drag( );
		std::string			get_bullet_name( );
		uintptr_t			get_damage_properties( );
		void				set_block_sprint( bool );
		void				set_reload_start_time( float );
		void				set_reload_time( float );
		float				get_reload_time( );
		float				get_next_reload_time( );
		bool				has_reload_cooldown( );
		float				calculate_cooldown_time( float, float );
		float				get_repeat_delay( );
		float				get_static_repeat_delay( );
		void		        set_deploy_delay( float );
		float				get_time_since_deploy( );
		float				get_next_attack_time( );
		float				get_deploy_delay( );
		void		        set_repeat_delay( float );
		void				set_current_hold_progress( float );
		void				set_string_bonus_damage( float );
		void				set_movement_penalty_ramp_up_time( float );
		void				process_attack( core::hit_test* );
		int					ammocount( );
		void				do_throw( );
		bool				can_throw_as_projectile( );
		int					ammotype( );
		void				set_aiming_while_cycling( bool );
		void				set_projectile_velocity_scale( float );
		void				set_projectile_distance_scale( float );

		float				get_projectile_velocity_scale( );

		int					get_max_ammo( );
		void				set_always_eoka( float );
		void				set_aim_sway_speed( float );
		void				set_aim_sway( float );
		void				do_attack( );
		void				set_aim_cone( float );
		void				set_aim_cone_curve_scale( float );
		void				set_hip_aim_cone( float );
		void				set_hip_aim_cone_scale( float );
		void				set_aim_cone_penalty( float );
		void				set_hip_aim_cone_offset( float );
		void				set_aim_cone_penalty_max( float );
		void				set_aim_cone_penalty_per_shot( float );
		void				set_stance_penalty_scale( float );
		void				set_aim_penalty_recover_delay( float );
		void				set_aim_penalty_recover_time( float );
		void				set_aim_sight_aim_cone_scale( float );
		void				set_aim_sight_aim_cone_offset( float );
		void				set_stance_penalty( float );
		
		float				get_aim_sway_speed( );

		float				get_aim_cone( );
		float				get_aim_penalty_recover_delay( );
		float				get_aim_penalty_recover_time( );

		float				get_aim_sight_aim_cone_scale( );

		float				get_aim_sight_aim_cone_offset( );

		float				get_stance_penalty( );

		float				get_aim_cone_curve_scale( );

		float				get_aim_cone_penalty_max( );

		float				get_aim_cone_penalty_per_shot( );

		float				get_stance_penalty_scale( );

		float				get_hip_aim_cone( );

		float				get_aim_cone_penalty( );

		float				get_hip_aim_cone_scale( );
		float				get_hip_aim_cone_offset( );

		void				start_attack_cooldown( float );
		bool				is_heal( );
		bool				is_melee( );
		bool				is_gun( );
	};

	class item_container
	{
	public:
		item* get_item( int );
		int get_size( );
	};

	class player_inventory
	{
	public:
		item_container* get_belt( );
		item_container* get_wear( );
	};

	class player_name_id {
	public:
		std::string get_user_name( );
	};

	class team_member : public base_entity
	{
	public:
		long				get_uid( );
	};

	class player_team
	{
	public:
		std::vector< long >	get_members( );
		long				get_team_id( );
	};

	class player_model
	{
	public:
		vec3_t				get_position( );
		vec3_t				get_velocity( );
		uintptr_t			get_multimesh( );
		void				disable_hands( );
		bool				is_npc( );
		void				set_velocity( vec3_t );
		void				set_position( vec3_t );
	};

	class base_mountable {
	public:
		void set_can_wield_item( bool );
		void set_ignore_vehicle_parent( bool );
	};

	class model_state
	{
	public:
		void				set_sprinting( bool );
		void				set_onLadder( bool  );
		void				remove_flag( int );
		void				add_flag( int );
		bool				get_ducked( );
		bool				has_flag( int );
		void				InteractiveDebug( bool );
		void				Setfly( bool );
		void				set_water_level( int );
	};

	class game_physics {

	};

	class player_eyes : public base_entity
	{
	public:
		vec3_t              get_viewoffset( );
		static vec3_t		get_eyeOffset( );
		vec3_t				get_position( );
		vec3_t				get_center( );
		vec3_t				get_bodyforward( );
		vec3_t				get_bodyright( );
		vec4_t				get_rotation( );
		void				set_position( vec3_t );
		void				set_center( vec3_t );
		void				set_body_rotation( vec4_t );
		vec4_t				get_body_rotation( );

		vec3_t				get_movementforward( );
		vec3_t				get_movementright( );

		void				set_view_offset( vec3_t );
	};

	class player_ticks
	{
	public:
		vec3_t				get_position( );
		void				SetTicks( float ticks );
		float				TicksPerSec( );
	};

	class viewmodel_lower
	{
	public:
		void					set_should_lower( bool );
	};

	class viewmodel_bob
	{
	public:
		void					set_bob_speed_walk( float );
		void					set_bob_speed_run( float );
		void					set_bob_amount_walk( float );
		void					set_bob_amount_run( float );
	};

	class base_view_model {
	public:
		static base_view_model* get_view( );
		viewmodel_bob*			get_bob( );
		viewmodel_lower*		get_lower( );
	};
		
	class base_player : public base_combat_entity
	{
	public:
		std::vector< item* >get_hotbar_items( );
		std::vector< item* >get_wear_items( );
		std::wstring		get_username( );
		unsigned long		get_uid( );
		base_mountable*		get_mountable( );
		void				set_clientTickInterval( float );
		float				get_clientTickInterval( );
		int					get_active_weapon_id( );
		player_walk_movement* get_movement( );
		player_input*		get_input( );
		player_inventory*	get_inventory( );
		player_team*		get_team( );
		player_model*		get_model( );
		model_state*		get_modelstate( );
		player_eyes*		get_eyes( );
		player_ticks*		get_lastSentTick( );
		float				lastSentTickTime( );
		void				on_land( float velocity );
		item*				get_held_item( );
		bool				is_same_team( );
		bool				is_knocked( );
		bool				is_sleeping( );
		bool				is_visible( vec3_t end );
		bool				is_visible( vec3_t start, vec3_t end );
		vec3_t				get_bone_position( int bone );
		transform*			get_bone_transform( int bone );
		int					get_mpv_bone( );
		static uintptr_t	visiblePlayerList( );
		void				add_flag( int flag );
		void				remove_flag( int );
		void				invite_to_team( base_player* player );
		float				get_radius( );
		float				get_height( bool ducked );
		void				set_clothing_blocks_aiming( bool );
		void				set_clothing_speed_reduce( float );
		void				set_is_frozen( bool );
		bool				get_on_ladder( );
		float				get_jumpheight( );
		void				set_can_attack( bool value );
		bool				has_flag( player_flags flag );
	};

	class player {
	public:
		core::base_player* this_player;
		uintptr_t object_class;

		player( core::base_player* input, uintptr_t input2 )
		{
			this_player = input;
			object_class = input2;
		}

		bool operator == ( player input ) {
			if( this->this_player == input.this_player )
				return true;
			else
				return false;
		}

	};

	struct bone_t {
		vec2_t screen;
		int8_t     index;
		bool       on_screen;
		vec3_t world_position;
		bool visible;
	};

	inline std::array< bone_t, 20 > bones = {
		bone_t{ vec2_t{ }, 17, false, vec3_t{ }, false }, bone_t{ vec2_t{ }, 18, false, vec3_t{ }, false },
		bone_t{ vec2_t{ }, 15, false, vec3_t{ }, false }, bone_t{ vec2_t{ }, 14, false, vec3_t{ }, false },
		bone_t{ vec2_t{ }, 1, false, vec3_t{ }, false },  bone_t{ vec2_t{ }, 2, false, vec3_t{ }, false },
		bone_t{ vec2_t{ }, 3, false, vec3_t{ }, false }, bone_t{ vec2_t{ }, 6, false, vec3_t{ }, false },
		bone_t{ vec2_t{ }, 5, false, vec3_t{ }, false }, bone_t{ vec2_t{ }, 21, false, vec3_t{ }, false },
		bone_t{ vec2_t{ }, 23, false, vec3_t{ }, false }, bone_t{ vec2_t{ }, 48, false, vec3_t{ }, false },
		bone_t{ vec2_t{ }, 24, false, vec3_t{ }, false }, bone_t{ vec2_t{ }, 25, false, vec3_t{ }, false },
		bone_t{ vec2_t{ }, 26, false, vec3_t{ }, false }, bone_t{ vec2_t{ }, 27, false, vec3_t{ }, false },
		bone_t{ vec2_t{ }, 55, false, vec3_t{ }, false }, bone_t{ vec2_t{ }, 56, false, vec3_t{ }, false },
		bone_t{ vec2_t{ }, 57, false, vec3_t{ }, false }, bone_t{ vec2_t{ }, 76, false, vec3_t{ }, false }
	};

	struct bounds_t {
		float left{ }, right{ }, 
			top{ }, bottom{ }, center{ }, half{ };

		bool on_screen{ };
	};

	inline bounds_t get_bounds( core::base_player* player, float expand = 0 ) {
		bounds_t bounds = { FLT_MAX, FLT_MIN, FLT_MAX, FLT_MIN, FLT_MAX, FLT_MAX, false };

		for( auto& [ bone_screen, bone_idx, on_screen, world_position, visible ] : bones ) {
			world_position = player->get_bone_position( bone_idx );

			if( bone_idx == jaw ) // lol
				world_position.y += 0.2f;

			bone_screen = g_sdk.world_to_screen( world_position );

			if( !bone_screen.is_zero( ) ) {
				if( bone_screen.x < bounds.left )
					bounds.left = bone_screen.x;
				if( bone_screen.x > bounds.right )
					bounds.right = bone_screen.x;
				if( bone_screen.y < bounds.top )
					bounds.top = bone_screen.y;
				if( bone_screen.y > bounds.bottom )
					bounds.bottom = bone_screen.y;
			}

			bounds.on_screen = true;
		}

		if( bounds.left == FLT_MAX
			|| bounds.right == FLT_MIN
			|| bounds.top == FLT_MAX
			|| bounds.bottom == FLT_MIN )
			return bounds_t( );

		bounds.left -= expand;
		bounds.right += expand;
		bounds.top -= expand;
		bounds.bottom += expand;
		bounds.center = bounds.left - 80;

		auto half = ( bounds.right - bounds.left ) / 2;

		bounds.half = ( 80.f + half * 2 + 80.f );

		return bounds;
	};

	class local_player : base_player {
	public:
		static base_player* Entity( );
		static void			ConsoleMessage( const char* message );
	};

	class item_mod_projectile
	{
	public:
		void				set_projectile_spread( float );
		void				set_projectile_velocity_spread( float );
	};

	class projectile : public base_entity
	{
	public:
		float				get_thickness( );
		float				get_integrity( );
		float				get_traveled_distance( );
		float				get_max_distance( );
		//float				get_partial_time( );
		float				get_traveled_time( );
		float				get_move_delta_time( );
		float				get_gravity_modifier( );
		float				get_drag( );
		bool				is_authoritative( );
		base_player*		get_owner( );
		item_mod_projectile* get_item_mod_projectile( );
		vec3_t				get_initial_velocity( );
		vec3_t				get_current_position( );
		vec3_t				get_current_velocity( );
		bool				is_alive( );
		void				set_thickness( float );
		void				set_current_velocity( vec3_t );
	};

	class hit_info
	{
	public:
		base_entity*		get_initiator( );
		base_entity*		get_hit_entity( );
		int					get_hit_bone( );
		vec3_t				get_hit_start( );
		vec3_t				get_hit_end( );
		vec3_t				get_hit_position_world( );
		vec3_t				get_hit_position_local( );
		vec3_t				get_hit_velocity( );
		float				get_hit_distance( );

	};

	class building_block
	{
	public:
		bool				can_afford( int grade, int skin, base_player* player );
		bool				can_upgrade( int grade, int skin, base_player* player );
		void				upgrade( int grade, int skin, base_player* player );
	};

	class stash_container
	{
	public:
		float				get_burried_offset( );
	};
}

class bone_data
{
public:
	int							index;
	vec3_t						position;
	core::transform*			transform;
	bool						is_visible;

	bone_data( )
	{
		this->index = 0;
		this->position.clear( );
		this->is_visible = false;
		this->transform = nullptr;
	}

	bone_data( int index, vec3_t position, bool visible, core::transform* trans )
	{
		this->index = index;
		this->position = position;
		this->is_visible = visible;
		this->transform = trans;
	}

	bool check_is_visible( vec3_t from )
	{
		return g_sdk.is_visible( this->position, from );
	}
};

class c_cheat	
{
public:
	uintptr_t asset_bundle = NULL, font_bundle = NULL, chams_bundle = NULL,
		wireframe_chams_bundle = NULL, circuit_chams_bundle = NULL;

	core::base_player* local = NULL;
	core::player_eyes* local_eyes = NULL;
	vec3_t cam_pos = vec3_t( ), local_pos = vec3_t( ), mouse_pos = vec3_t( );
	vec2_t screen_size = vec2_t( ), screen_center = vec2_t( );

	uintptr_t draw_label = NULL, draw_skin = NULL, white_texture = NULL, client_entities = NULL;

	float global_time;
	std::vector< std::pair< core::base_player*, entity_type > > player_list = { };
	camera* camera_ptr = NULL;
	color_t pulsation, rainbow;
};

extern c_cheat g_cheat;

class c_game	
{
public:
	bool					water_level_test( vec3_t pos, bool value1, bool value2, core::base_entity* entity );
	void					set_flash_duration( float );
	void					set_graphics_fov( float );
	void					set_admin_time( float );
	void					set_underwater_blur( bool );

	void					set_admin_ref_mp( float );
	void					set_admin_ambient_mp( float );
	void					set_rain( float );
	void					set_rayleigh( float );
	void					set_mie( float );
	void					set_brightness( float );
	void					set_is_sprinting( bool );
};

extern c_game g_game;

inline camera* get_main_camera( ) {
	static auto fn = reinterpret_cast< camera*( * )( ) >( il2mgr::methods::resolve_icall( xs( "UnityEngine.Camera::get_main()" ) ) );

	g_cheat.camera_ptr = fn( );

	return g_cheat.camera_ptr;
}
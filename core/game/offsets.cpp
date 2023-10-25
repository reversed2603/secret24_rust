#include "offsets.hpp"
#include "il2cpp.hpp"
#include "../utilities/memory.hpp"

namespace offsets
{
	uintptr_t get_material = il2mgr::method( xs( "Renderer" ), xs( "get_material" ), 0, xs( "UnityEngine" ) );
	uintptr_t get_shader = il2mgr::method( xs( "Material" ), xs( "get_shader" ), 0, xs( "UnityEngine" ) );
	uintptr_t find = il2mgr::method( xs( "Shader" ), xs( "Find" ), 1, xs( "UnityEngine" ) );
	uintptr_t set_shader = il2mgr::method( xs( "Material" ), xs( "set_shader" ), 1, xs( "UnityEngine" ) );
	uintptr_t CreateWithShader = il2mgr::method( xs( "Material" ), xs( "CreateWithShader" ), 2, xs( "UnityEngine" ) );
	uintptr_t set_color = il2mgr::method( xs( "Material" ), xs( "SetColor" ), 2, xs( "UnityEngine" ) );
	uintptr_t set_pass = il2mgr::method( xs( "Material" ), xs( "SetPass" ), 0, xs( "UnityEngine" ) );
	uintptr_t set_int = il2mgr::method( xs( "Material" ), xs( "SetInt" ), 2, xs( "UnityEngine" ) );
	uintptr_t set_float = il2mgr::method( xs( "Material" ), xs( "SetFloat" ), 2, xs( "UnityEngine" ) );

	uintptr_t _displayName = il2mgr::value( xs( "BasePlayer" ), xs( "_displayName" ) );
	uintptr_t userID = il2mgr::value( xs( "BasePlayer" ), xs( "userID" ) );
	uintptr_t clActiveItem = il2mgr::value( xs( "BasePlayer" ), xs( "clActiveItem" ) );
	uintptr_t movement = il2mgr::value( xs( "BasePlayer" ), xs( "movement" ) );
	uintptr_t GestureViewModel = il2mgr::value( xs( "BasePlayer" ), xs( "GestureViewModel" ) );
	uintptr_t sway = il2mgr::value( xs( "BaseViewModel" ), xs( "sway" ) );
	uintptr_t lower = il2mgr::value( xs( "BaseViewModel" ), xs( "lower" ) );
	uintptr_t bob = il2mgr::value( xs( "BaseViewModel" ), xs( "bob" ) );

	uintptr_t bob_amount_run = il2mgr::value( xs( "ViewmodelBob" ), xs( "bobAmountRun" ) );
	uintptr_t bob_amount_walk = il2mgr::value( xs( "ViewmodelBob" ), xs( "bobAmountWalk" ) );
	uintptr_t bob_speed_run = il2mgr::value( xs( "ViewmodelBob" ), xs( "bobSpeedRun" ) );
	uintptr_t bob_speed_walk = il2mgr::value( xs( "ViewmodelBob" ), xs( "bobSpeedWalk" ) );
	uintptr_t should_lower = il2mgr::value( xs( "ViewmodelLower" ), xs( "shouldLower" ) );

	uintptr_t waterlevel_test = il2mgr::method( xs( "WaterLevel" ), xs( "Test" ), 4 );

	uintptr_t view = il2mgr::method( xs( "BaseViewModel" ), xs( "get_ActiveModel" ), 0 );

	uintptr_t animator = il2mgr::value( xs( "BaseViewModel" ), xs( "animator" ) );
	uintptr_t Speed = il2mgr::value( xs( "Animator" ), xs( "Animator" ) );

	uintptr_t body_rotation = il2mgr::value( xs( "PlayerEyes" ), xs( "<bodyRotation>k__BackingField" ) );
	uintptr_t get_body_lean_offset = il2mgr::method( xs( "PlayerEyes" ), xs( "get_BodyLeanOffset" ), 0 );
	uintptr_t view_offset = il2mgr::value( xs( "PlayerEyes" ), xs( "viewOffset" ) );

	uintptr_t get_projectile_velocity_scale = il2mgr::method( xs( "BaseProjectile" ), xs( "GetProjectileVelocityScale" ), 1, xs( "getMax" ), xs( "" ), 1 );

	uintptr_t projectile_velocity_scale = il2mgr::value( xs( "BaseProjectile" ), xs( "projectileVelocityScale" ) );
	uintptr_t projectile_distance_scale = il2mgr::value( xs( "BaseProjectile" ), xs( "distanceScale" ) );

    uintptr_t push_matrix = il2mgr::method( xs( "GL" ), xs( "PushMatrix" ), 0, xs( "UnityEngine" ) );
    uintptr_t begin = il2mgr::method( xs( "GL" ), xs( "Begin" ), 1, xs( "UnityEngine" ) );
    uintptr_t vertex = il2mgr::method( xs( "GL" ), xs( "Vertex" ), 1, xs( "UnityEngine" ) );
    uintptr_t end = il2mgr::method( xs( "GL" ), xs( "End" ), 0, xs( "UnityEngine" ) );
    uintptr_t pop_matrix = il2mgr::method( xs( "GL" ), xs( "PopMatrix" ), 0, xs( "UnityEngine" ) );
	uintptr_t set_gl_color = il2mgr::method( xs( "GL" ), xs( "Color" ), 1, xs( "UnityEngine" ) );
	
	uintptr_t input = il2mgr::value( xs( "BasePlayer" ), xs( "input" ) );
	uintptr_t inventory = il2mgr::value( xs( "BasePlayer" ), xs( "inventory" ) );
	uintptr_t Frozen = il2mgr::value( xs( "BasePlayer" ), xs( "Frozen" ) );
	uintptr_t clothingBlocksAiming = il2mgr::value( xs( "BasePlayer" ), xs( "clothingBlocksAiming" ) );
	uintptr_t clothingMoveSpeedReduction = il2mgr::value( xs( "BasePlayer" ), xs( "clothingMoveSpeedReduction" ) );

	uintptr_t HasPlayerFlag = il2mgr::value( xs( "BasePlayer" ), xs( "HasPlayerFlag" ) );
	uintptr_t clientTeam = il2mgr::value( xs( "BasePlayer" ), xs( "clientTeam" ) );
	uintptr_t playerFlags = il2mgr::value( xs( "BasePlayer" ), xs( "playerFlags" ) );
	uintptr_t player_model = il2mgr::value( xs( "BasePlayer" ), xs( "playerModel" ) );
	uintptr_t player_eyes = il2mgr::value( xs( "BasePlayer" ), xs( "eyes" ) );
	uintptr_t player_lastSentTick = il2mgr::value( xs( "BasePlayer" ), xs( "lastSentTick" ) );
	uintptr_t player_lastSentTickTime = il2mgr::value( xs( "BasePlayer" ), xs( "lastSentTickTime" ) );
	uintptr_t invitetoteam = il2mgr::method( xs( "BasePlayer" ), xs( "InviteToTeam" ), 1 );
	uintptr_t baseplayer_get_height = il2mgr::method( xs( "BasePlayer" ), xs( "GetHeight" ), 1 );
	uintptr_t get_max_speed = il2mgr::method( xs( "BasePlayer" ), xs( "GetMaxSpeed" ), 0 );
	uintptr_t baseplayer_get_radius = il2mgr::method( xs( "BasePlayer" ), xs( "GetRadius" ), 0 );
	uintptr_t baseplayer_onladder = il2mgr::method( xs( "BasePlayer" ), xs( "OnLadder" ), 0 );

	uintptr_t baseplayer_get_jumpheight = il2mgr::method( xs( "BasePlayer" ), xs( "GetJumpHeight" ), 0 );
	uintptr_t model = il2mgr::value( xs( "BaseEntity" ), xs( "model" ) );
	uintptr_t modelstate = il2mgr::value( xs( "BasePlayer" ), xs( "modelState" ) );
	uintptr_t playereyes_get_position = il2mgr::method( xs( "PlayerEyes" ), xs( "get_position" ), 0 );
	uintptr_t chams = il2mgr::value( xs( "SkinnedMultiMesh" ), xs( "<Renderers>k__BackingField" ) );
	uintptr_t LoadAsset_Internal = il2mgr::method( xs( "AssetBundle" ), xs( "LoadAsset_Internal" ), 2, xs( "UnityEngine" ) );
	uintptr_t LoadFromFile_Internal = il2mgr::method( xs( "AssetBundle" ), xs( "LoadFromFile_Internal" ), 3, xs( "UnityEngine" ) );
	uintptr_t get_Renderers = il2mgr::method( xs( "SkinnedMultiMesh" ), xs( "get_Renderers" ), 0 );
	uintptr_t DoHit = il2mgr::method( xs( "Projectile" ), xs( "DoHit" ), 3 );
	uintptr_t teamID = il2mgr::value( xs( "PlayerTeam" ), xs( "teamID" ) );
	uintptr_t underwater_effect = il2mgr::value( xs( "Admin" ), xs( "underwater_effect" ) );

	uintptr_t Animator = il2mgr::method( xs( "PlayerModel" ), xs( "get_animator" ), 0 );
	uintptr_t Nohands = il2mgr::value( xs( "PlayerModel" ), xs( "get_ShouldShowHands" ) );
	uintptr_t playermodel_position = il2mgr::value( xs( "PlayerModel" ), xs( "position" ) );
	uintptr_t playermodel_newVelocity = il2mgr::value( xs( "PlayerModel" ), xs( "newVelocity" ) );
	uintptr_t playermodel_get_IsNpc = il2mgr::value( xs( "PlayerModel" ), xs( "<IsNpc>k__BackingField" ) );
	uintptr_t playermodel_multimesh = il2mgr::value( xs( "PlayerModel" ), xs( "_multiMesh" ) );

	uintptr_t boneTransforms = il2mgr::value( xs( "Model" ), xs( "boneTransforms" ) );
	uintptr_t get_mousePosition = il2mgr::method( xs( "Input" ), xs( "get_mousePosition" ), 0, xs( "UnityEngine" ) );
	uintptr_t screen_get_width = il2mgr::method( xs( "Screen" ), xs( "get_width" ), 0, xs( "UnityEngine" ) );
	uintptr_t screen_get_height = il2mgr::method( xs( "Screen" ), xs( "get_height" ), 0, xs( "UnityEngine" ) );
	uintptr_t input_get_key_down = il2mgr::method( xs( "Input" ), xs( "GetKeyDown" ), 1, xs( "UnityEngine" ) );
	uintptr_t input_get_key_up = il2mgr::method( xs( "Input" ), xs( "GetKeyUp" ), 1, xs( "UnityEngine" ) );
	uintptr_t input_get_key = il2mgr::method( xs( "Input" ), xs( "GetKey" ), 1, xs( "UnityEngine" ) );
	uintptr_t gamephysics_line_of_site = il2mgr::method( xs( "GamePhysics" ), xs( "LineOfSight" ), 4 );
	uintptr_t ignore_layer_collision = il2mgr::methods::resolve_icall( xs( "UnityEngine.Physics::IgnoreLayerCollision()" ) );
	uintptr_t mathf_clamp = il2mgr::method( xs( "Mathf" ), xs( "Clamp" ), 3, xs( "UnityEngine" ) );
	uintptr_t mathf_atan2 = il2mgr::method( xs( "Mathf" ), xs( "Atan2" ), 2, xs( "UnityEngine" ) );
	uintptr_t mathf_max = il2mgr::method( xs( "Mathf" ), xs( "Max" ), 2, xs( "UnityEngine" ) );

	uintptr_t mathf_abs = il2mgr::method( xs( "Mathf" ), xs( "Abs" ), 1, xs( "UnityEngine" ) );
	uintptr_t transform_get_position = il2mgr::method( xs( "Transform" ), xs( "get_position" ), 0, xs( "UnityEngine" ) );
	uintptr_t transform_set_position = il2mgr::method( xs( "Transform" ), xs( "set_position" ), 1, xs( "UnityEngine" ) );
	uintptr_t transform_inverse_transform_point = il2mgr::method( xs( "Transform" ), xs( "InverseTransformPoint" ), 1, xs( "UnityEngine" ) );
	uintptr_t calcsize = il2mgr::method( xs( "GUIStyle" ), xs( "CalcSize" ), 0, xs( "UnityEngine" ) );
	uintptr_t transform_transform_direction = il2mgr::method( xs( "Transform" ), xs( "TransformDirection" ), 1, xs( "UnityEngine" ) );
	uintptr_t real_time_since_startup = il2mgr::method( xs( "Time" ), xs( "get_realtimeSinceStartup" ), 0, xs( "UnityEngine" ) );
	uintptr_t get_fixed_time = il2mgr::method( xs( "Time" ), xs( "get_fixedTime" ), 0, xs( "UnityEngine" ) );
	uintptr_t baseentity__name = il2mgr::value( xs( "BaseEntity" ), xs( "_name" ) );
	uintptr_t get_iconSprite = il2mgr::method( xs( "Item" ), xs( "get_iconSprite" ), 0 );
	uintptr_t get_texture = il2mgr::method( xs( "Sprite" ), xs( "get_texture" ), 0, xs( "UnityEngine" ) );

	uintptr_t set_aspect = il2mgr::method( xs( "Camera" ), xs( "set_aspect" ), 1, xs( "UnityEngine" ) );

	uintptr_t player_name_id_username = il2mgr::value( xs( "PlayerNameID" ), xs( "username" ) );

	uintptr_t CanAttack = il2mgr::method( xs( "BaseProjectile" ), xs( "CanAttack" ), 0 );
	uintptr_t noAimingWhileCycling = il2mgr::value( xs( "BaseProjectile" ), xs( "noAimingWhileCycling" ) );

	uintptr_t mounted = il2mgr::value( xs( "BasePlayer" ), xs( "mounted" ) );
	
	uintptr_t clientTickInterval = il2mgr::value( xs( "BasePlayer" ), xs( "clientTickInterval" ) );
	uintptr_t baseentity_closest_point = il2mgr::method( xs( "BaseEntity" ), xs( "ClosestPoint" ), 1 );
	uintptr_t baseentity_serverrpc_1arg = il2mgr::method( xs( "BaseEntity" ), xs( "ServerRPC" ), 1 );
	uintptr_t baseentity_serverrpc_4arg = il2mgr::method( xs( "BaseEntity" ), xs( "ServerRPC" ), 4 );

	uintptr_t baseentity_sendsignalbroadcast = il2mgr::method( xs( "BaseEntity" ), xs( "SendSignalBroadcast" ), 2 );
	uintptr_t component_get_transform = il2mgr::method( xs( "Component" ), xs( "get_transform" ), 0, xs( "UnityEngine" ) );
	uintptr_t get_transform_up = il2mgr::method( xs( "Transform" ), xs( "get_up" ), 0, xs( "UnityEngine" ) );
	uintptr_t treeentity_hit_direction = il2mgr::value( xs( "TreeEntity" ), xs( "hitDirection" ) );
	uintptr_t basecombatentity__lifestate = il2mgr::value( xs( "BaseCombatEntity" ), xs( "lifestate" ) );
	uintptr_t basecombatentity__health = il2mgr::value( xs( "BaseCombatEntity" ), xs( "_health" ) );
	uintptr_t stashcontainer_burriedOffset = il2mgr::value( xs( "StashContainer" ), xs( "burriedOffset" ) );
	uintptr_t basecombatentity__maxHealth = il2mgr::value( xs( "BaseCombatEntity" ), xs( "_maxHealth" ) );
	uintptr_t basecombatentity_lifestate = il2mgr::value( xs( "BaseCombatEntity" ), xs( "lifestate" ) );
	uintptr_t playerwalkmovement_flying = il2mgr::value( xs( "PlayerWalkMovement" ), xs( "flying" ) );
	uintptr_t playerwalkmovement_swimming = il2mgr::value( xs( "PlayerWalkMovement" ), xs( "swimming" ) );
	uintptr_t playerwalkmovement_grounded = il2mgr::value( xs( "PlayerWalkMovement" ), xs( "grounded" ) );
	uintptr_t playerwalkmovement_capsuleCenter = il2mgr::value( xs( "PlayerWalkMovement" ), xs( "capsuleCenter" ) );
	uintptr_t playerwalkmovement_capsuleHeight = il2mgr::value( xs( "PlayerWalkMovement" ), xs( "capsuleHeight" ) );
	uintptr_t playerwalkmovement_ducking = il2mgr::value( xs( "BaseMovement" ), xs( "<Ducking>k__BackingField" ) );
	uintptr_t playerwalkmovement_grounded_field = il2mgr::value( xs( "BaseMovement" ), xs( "<Grounded>k__BackingField" ) );
	uintptr_t playerwalkmovement_running = il2mgr::value( xs( "BaseMovement" ), xs( "<Running>k__BackingField" ) );


	uintptr_t playerwalkmovement_gravityTestRadius = il2mgr::value( xs( "PlayerWalkMovement" ), xs( "gravityTestRadius" ) );
	uintptr_t playerwalkmovement_groundAngle = il2mgr::value( xs( "PlayerWalkMovement" ), xs( "groundAngle" ) );
	uintptr_t playerwalkmovement_groundAngleNew = il2mgr::value( xs( "PlayerWalkMovement" ), xs( "groundAngleNew" ) );
	uintptr_t playerwalkmovement_previousVelocity = il2mgr::value( xs( "PlayerWalkMovement" ), xs( "previousVelocity" ) );
	uintptr_t playerwalkmovement_wasFalling = il2mgr::value( xs( "PlayerWalkMovement" ), xs( "wasFalling" ) );
	uintptr_t playerwalkmovement_capsule_radius = il2mgr::value( xs( "CapsuleCollider" ), xs( "radius" ) );
	uintptr_t playerwalkmovement_maxAngleWalking = il2mgr::value( xs( "PlayerWalkMovement" ), xs( "maxAngleWalking" ) );
	uintptr_t playerwalkmovement_maxAngleClimbing = il2mgr::value( xs( "PlayerWalkMovement" ), xs( "maxAngleClimbing" ) );
	uintptr_t playerwalkmovement_groundTime = il2mgr::value( xs( "PlayerWalkMovement" ), xs( "groundTime" ) );
	uintptr_t playerwalkmovement_gravityMultiplier = il2mgr::value( xs( "PlayerWalkMovement" ), xs( "gravityMultiplier" ) );
	uintptr_t playerwalkmovement_jumpTime = il2mgr::value( xs( "PlayerWalkMovement" ), xs( "jumpTime" ) );
	uintptr_t playerwalkmovement_landTime = il2mgr::value( xs( "PlayerWalkMovement" ), xs( "landTime" ) );
	uintptr_t playerwalkmovement_TeleportTo = il2mgr::method( xs( "PlayerWalkMovement" ), xs( "TeleportTo" ), 2 );

	uintptr_t item_heldEntity = il2mgr::value( xs( "Item" ), xs( "heldEntity" ) );
	uintptr_t baseprojectile_DoAttack = il2mgr::value( xs( "BaseProjectile" ), xs( "DoAttack" ) );
	uintptr_t baseprojectile_aimCone = il2mgr::value( xs( "BaseProjectile" ), xs( "aimCone" ) );
	uintptr_t bowweapon_wasAiming = il2mgr::value( xs( "BowWeapon" ), xs( "wasAiming" ) );
	uintptr_t bowweapon_attackReady = il2mgr::value( xs( "BowWeapon" ), xs( "attackReady" ) );
	uintptr_t basemelee_maxDistance = il2mgr::value( xs( "BaseMelee" ), xs( "maxDistance" ) );
	uintptr_t basemelee_attack_radius = il2mgr::value( xs( "BaseMelee" ), xs( "attackRadius" ) );
	uintptr_t basemelee_dothrow = il2mgr::method( xs( "BaseMelee" ), xs( "DoThrow" ), 0 );
	uintptr_t basemelee_can_throw_as_projectile = il2mgr::value( xs( "BaseMelee" ), xs( "canThrowAsProjectile" ) );

	uintptr_t item_icon_queued_for_looting = il2mgr::value( xs( "ItemIcon" ), xs( "queuedForLooting" ) );
	uintptr_t item_icon_run_timed_action = il2mgr::method( xs( "ItemIcon" ), xs( "RunTimedAction" ), 0 );

	uintptr_t baseprojectile_aimconePenalty = il2mgr::value( xs( "BaseProjectile" ), xs( "aimconePenalty" ) );
	uintptr_t baseprojectile_stancePenaltyScale = il2mgr::value( xs( "BaseProjectile" ), xs( "stancePenaltyScale" ) );

	uintptr_t baseprojectile_hipAimCone = il2mgr::value( xs( "BaseProjectile" ), xs( "hipAimCone" ) );
	uintptr_t baseprojectile_aimConePenaltyMax = il2mgr::value( xs( "BaseProjectile" ), xs( "aimConePenaltyMax" ) );
	uintptr_t baseprojectile_aimconePenaltyRecoverTime = il2mgr::value( xs( "BaseProjectile" ), xs( "aimconePenaltyRecoverTime" ) );
	uintptr_t baseprojectile_aimconePenaltyRecoverDelay = il2mgr::value( xs( "BaseProjectile" ), xs( "aimconePenaltyRecoverDelay" ) );
	uintptr_t baseprojectile_stancePenalty = il2mgr::value( xs( "BaseProjectile" ), xs( "stancePenalty" ) );
	uintptr_t baseprojectile_sightAimConeScale = il2mgr::value( xs( "BaseProjectile" ), xs( "sightAimConeScale" ) );
	uintptr_t baseprojectile_sightAimConeOffset = il2mgr::value( xs( "BaseProjectile" ), xs( "sightAimConeOffset" ) );
	uintptr_t baseprojectile_hipAimConeScale = il2mgr::value( xs( "BaseProjectile" ), xs( "hipAimConeScale" ) );
	uintptr_t baseprojectile_hipAimConeOffset = il2mgr::value( xs( "BaseProjectile" ), xs( "hipAimConeOffset" ) );

	uintptr_t baseprojectile_LaunchProjectile = il2mgr::method( xs( "BaseProjectile" ), xs( "LaunchProjectile" ), 0 );
	uintptr_t baseprojectile_ShotFired = il2mgr::method( xs( "BaseProjectile" ), xs( "ShotFired" ), 0 );
	uintptr_t baseprojectile_UpdateAmmoDisplay = il2mgr::method( xs( "BaseProjectile" ), xs( "UpdateAmmoDisplay" ), 0 );
	uintptr_t baseprojectile_DidAttackClientside = il2mgr::method( xs( "BaseProjectile" ), xs( "DidAttackClientside" ), 0 );
	uintptr_t baseprojectile_BeginCycle = il2mgr::method( xs( "BaseProjectile" ), xs( "BeginCycle" ), 0 );

	uintptr_t magazine_contents = il2mgr::value( xs( "Magazine" ), xs( "contents" ) );
	uintptr_t magazine_ammoType = il2mgr::value( xs( "Magazine" ), xs( "ammoType" ) );

	uintptr_t building_privlidge_cachedProtectedMinutes = il2mgr::value( xs( "BuildingPrivlidge" ), xs( "cachedProtectedMinutes" ) );	
	uintptr_t building_privlidge_authorizedPlayers = il2mgr::value( xs( "BuildingPrivlidge" ), xs( "authorizedPlayers" ) );
	
	uintptr_t baseprojectile_baseProjectile = il2mgr::value( xs( "Entity" ), xs( "baseProjectile" ) );
	uintptr_t baseprojectile_aimconePenaltyPerShot = il2mgr::value( xs( "BaseProjectile" ), xs( "aimconePenaltyPerShot" ) );
	uintptr_t baseprojectile_createdProjectiles = il2mgr::value( xs( "BaseProjectile" ), xs( "createdProjectiles" ) );
	uintptr_t baseprojectile_automatic = il2mgr::value( xs( "BaseProjectile" ), xs( "automatic" ) );
	uintptr_t baseprojectile_is_burst = il2mgr::value( xs( "BaseProjectile" ), xs( "isBurstWeapon" ) );
	
	uintptr_t baseprojectile_aimSway = il2mgr::value( xs( "BaseProjectile" ), xs( "aimSway" ) );
	uintptr_t baseprojectile_aimSwaySpeed = il2mgr::value( xs( "BaseProjectile" ), xs( "aimSwaySpeed" ) );
	uintptr_t baseprojectile_primaryMagazine = il2mgr::value( xs( "BaseProjectile" ), xs( "primaryMagazine" ) );
	uintptr_t baseprojectile_recoil = il2mgr::value( xs( "BaseProjectile" ), xs( "recoil" ) );
	uintptr_t attackentity_repeatDelay = il2mgr::value( xs( "AttackEntity" ), xs( "repeatDelay" ) );
	uintptr_t attackentity_deployDelay = il2mgr::value( xs( "AttackEntity" ), xs( "deployDelay" ) );
	uintptr_t flintstrikeweapon_successFraction = il2mgr::value( xs( "FlintStrikeWeapon" ), xs( "successFraction" ) );
	uintptr_t flintstrikeweapon_didSparkThisFrame = il2mgr::value( xs( "FlintStrikeWeapon" ), xs( "_didSparkThisFrame" ) );
	uintptr_t client_convar = il2mgr::init_class( xs( "Client" ), xs( "ConVar" ) );
	uintptr_t graphics_convar = il2mgr::init_class( xs( "Graphics" ), xs( "ConVar" ) );
	uintptr_t flashbang_overlay_instance = il2mgr::init_class( xs( "FlashbangOverlay" ), xs( "Instance" ) );
	uintptr_t compoundbow_currentHoldProgress = il2mgr::value( xs( "CompoundBowWeapon" ), xs( "currentHoldProgress" ) );
	uintptr_t compoundbow_movementPenaltyRampUpTime = il2mgr::value( xs( "CompoundBowWeapon" ), xs( "movementPenaltyRampUpTime" ) );
	uintptr_t compoundbow_stringBonusDamage = il2mgr::value( xs( "CompoundBowWeapon" ), xs( "stringBonusDamage" ) );
	uintptr_t input_convar = il2mgr::init_class( xs( "Input" ), xs( "ConVar" ) );

	uintptr_t recoilproperties_newRecoilOverride = il2mgr::value( xs( "RecoilProperties" ), xs( "newRecoilOverride" ) );
	uintptr_t recoilproperties_recoilYawMin = il2mgr::value( xs( "RecoilProperties" ), xs( "recoilYawMin" ) );
	uintptr_t recoilproperties_recoilYawMax = il2mgr::value( xs( "RecoilProperties" ), xs( "recoilYawMax" ) );
	uintptr_t recoilproperties_recoilPitchMin = il2mgr::value( xs( "RecoilProperties" ), xs( "recoilPitchMin" ) );
	uintptr_t recoilproperties_recoilPitchMax = il2mgr::value( xs( "RecoilProperties" ), xs( "recoilPitchMax" ) );
	uintptr_t admin_convar = il2mgr::init_class( xs( "Admin" ), xs( "ConVar" ) );
	uintptr_t adminambientmultiplier = il2mgr::init_class( xs( "Admin" ), xs( "adminambientmultiplier" ) );
	uintptr_t adminreflectionmultiplier = il2mgr::init_class( xs( "Admin" ), xs( "adminreflectionmultiplier" ) );

	uintptr_t worldItem_item = il2mgr::value( xs( "WorldItem" ), xs( "item" ) );
	uintptr_t heldentity_isdeployed = il2mgr::value( xs( "HeldEntity" ), xs( "isDeployed" ) );
	uintptr_t item_info = il2mgr::value( xs( "Item" ), xs( "info" ) );
	uintptr_t itemdefinition_itemid = il2mgr::value( xs( "ItemDefinition" ), xs( "itemid" ) );
	uintptr_t ProjectileWeaponMod_projectileVelocity = il2mgr::value( xs( "ProjectileWeaponMod" ), xs( "projectileVelocity" ) );
	uintptr_t itemdefinition_displayName = il2mgr::value( xs( "ItemDefinition" ), xs( "displayName" ) );
	uintptr_t itemdefinition_shortname = il2mgr::value( xs( "ItemDefinition" ), xs( "shortname" ) );
	uintptr_t item_amount = il2mgr::value( xs( "Item" ), xs( "amount" ) );
	uintptr_t item_uid = il2mgr::value( xs( "Item" ), xs( "uid" ) );
	uintptr_t playerinventory_containerBelt = il2mgr::value( xs( "PlayerInventory" ), xs( "containerBelt" ) );
	uintptr_t playerinventory_containerWear = il2mgr::value( xs( "PlayerInventory" ), xs( "containerWear" ) );

	uintptr_t itemcontainer_itemList = il2mgr::value( xs( "ItemContainer" ), xs( "itemList" ) );
	uintptr_t projectile_integrity = il2mgr::value( xs( "Projectile" ), xs( "integrity" ) );
	uintptr_t projectile_traveledDistance = il2mgr::value( xs( "Projectile" ), xs( "traveledDistance" ) );
	uintptr_t projectile_maxDistance = il2mgr::value( xs( "Projectile" ), xs( "maxDistance" ) );
	uintptr_t projectile_traveledTime = il2mgr::value( xs( "Projectile" ), xs( "traveledTime" ) );
	uintptr_t projectile_owner = il2mgr::value( xs( "Projectile" ), xs( "owner" ) );
	uintptr_t projectile_mod = il2mgr::value( xs( "Projectile" ), xs( "mod" ) );
	uintptr_t itemmodprojectile_projectileSpread = il2mgr::value( xs( "ItemModProjectile" ), xs( "projectileSpread" ) );
	uintptr_t itemmodprojectile_projectileVelocity = il2mgr::value( xs( "ItemModProjectile" ), xs( "projectileVelocity" ) );
	uintptr_t itemmodprojectile_projectileVelocitySpread = il2mgr::value( xs( "ItemModProjectile" ), xs( "projectileVelocitySpread" ) );
	uintptr_t projectile_initialVelocity = il2mgr::value( xs( "Projectile" ), xs( "initialVelocity" ) );
	uintptr_t projectile_currentVelocity = il2mgr::value( xs( "Projectile" ), xs( "currentVelocity" ) );
	uintptr_t projectile_drag = il2mgr::value( xs( "Projectile" ), xs( "drag" ) );
	uintptr_t projectile_gravityModifier = il2mgr::value( xs( "Projectile" ), xs( "gravityModifier" ) );
	uintptr_t projectile_thickness = il2mgr::value( xs( "Projectile" ), xs( "thickness" ) );
	uintptr_t hittest_hitEntity = il2mgr::value( xs( "HitTest" ), xs( "HitEntity" ) );
	uintptr_t hittest_hitNormal = il2mgr::value( xs( "HitTest" ), xs( "HitNormal" ) );
	uintptr_t hittest_hitTransform = il2mgr::value( xs( "HitTest" ), xs( "HitTransform" ) );
	uintptr_t hittest_hitPoint = il2mgr::value( xs( "HitTest" ), xs( "HitPoint" ) );
	uintptr_t hittest_hitDistance = il2mgr::value( xs( "HitTest" ), xs( "HitDistance" ) );
	uintptr_t hittest_attackray = il2mgr::value( xs( "HitTest" ), xs( "AttackRay" ) );
	uintptr_t hittest_maxDistance = il2mgr::value( xs( "HitTest" ), xs( "MaxDistance" ) );
	uintptr_t hittest_didHit = il2mgr::value( xs( "HitTest" ), xs( "DidHit" ) );
	uintptr_t hittest_damageProperties = il2mgr::value( xs( "HitTest" ), xs( "damageProperties" ) );
	uintptr_t playerinput_bodyAngles = il2mgr::value( xs( "PlayerInput" ), xs( "bodyAngles" ) );
	uintptr_t playerinput_headRotation = il2mgr::value( xs( "PlayerInput" ), xs( "headRotation" ) );
	uintptr_t event_get_current = il2mgr::method( xs( "Event" ), xs( "get_current" ), 0, xs( "UnityEngine" ) );
	uintptr_t event_get_type = il2mgr::method( xs( "Event" ), xs( "get_type" ), 0, xs( "UnityEngine" ) );
	uintptr_t cursor_set_lockState = il2mgr::method( xs( "Cursor" ), xs( "set_lockState" ), 1, xs( "UnityEngine" ) );
	uintptr_t gui_get_skin = il2mgr::method( xs( "GUI" ), xs( "get_skin" ), 0, xs( "UnityEngine" ) );
	uintptr_t gui_set_color = il2mgr::method( xs( "GUI" ), xs( "set_color" ), 1, xs( "UnityEngine" ) );
	uintptr_t gui_drawtexture = il2mgr::method( xs( "GUI" ), xs( "DrawTexture" ), 2, xs( "UnityEngine" ) );
	uintptr_t gui_label = il2mgr::method( xs( "GUI" ), xs( "Label" ), 3, xs( "UnityEngine" ) );
	uintptr_t texture2d_get_whitetexture = il2mgr::method( xs( "Texture2D" ), xs( "get_whiteTexture" ), 0, xs( "UnityEngine" ) );
	uintptr_t guistyle_set_fontsize = il2mgr::method( xs( "GUIStyle" ), xs( "set_fontSize" ), 1, xs( "UnityEngine" ) );
	uintptr_t guistyle_set_alignment = il2mgr::method( xs( "GUIStyle" ), xs( "set_alignment" ), 1, xs( "UnityEngine" ) );
	uintptr_t guicontent_temp = il2mgr::method( xs( "GUIContent" ), xs( "Temp" ), 1, xs( "UnityEngine" ) );
	uintptr_t ddraw_get = il2mgr::method( xs( "DDraw" ), xs( "Get" ), 0, xs( "UnityEngine" ) );
	uintptr_t ddraw_line = il2mgr::method( xs( "DDraw" ), xs( "Line" ), 6, xs( "UnityEngine" ) );
	uintptr_t ddraw_sphere = il2mgr::method( xs( "DDraw" ), xs( "Sphere" ), 5, xs( "UnityEngine" ) );

	uintptr_t ddraw_arrow = il2mgr::method( xs( "DDraw" ), xs( "Arrow" ), 5, xs( "UnityEngine" ) );
	uintptr_t ddraw_text = il2mgr::method( xs( "DDraw" ), xs( "Text" ), 4, xs( "UnityEngine" ) );
	uintptr_t modelstate_set_onLadder = il2mgr::method( xs( "ModelState" ), xs( "set_onLadder" ), 1 );
	uintptr_t modelstate_set_sprinting = il2mgr::method( xs( "ModelState" ), xs( "set_sprinting" ), 1 );
	uintptr_t SetFlying = il2mgr::method( xs( "ModelState" ), xs( "set_flying" ), 1 ); 
	uintptr_t SetMounted = il2mgr::method( xs( "ModelState" ), xs( "set_mounted" ), 1 );
	uintptr_t set_pose_type = il2mgr::value( xs( "ModelState" ), xs( "poseType" ) );
	uintptr_t waterLevel = il2mgr::value( xs( "ModelState" ), xs( "waterLevel" ) );	
	uintptr_t get_ducked = il2mgr::method( xs( "ModelState" ), xs( "get_ducked" ), 0 );

	uintptr_t gamemanager_createprefab = il2mgr::method( xs( "GameManager" ), xs( "CreatePrefab" ), 2 );
	uintptr_t prefab = il2mgr::method( xs( "BaseNetworkable" ), xs( "ShortPrefabName" ), 0 );

	uintptr_t gamemanager_destroy = il2mgr::method( xs( "GameManager" ), xs( "Destroy" ), 2 );
	uintptr_t buildingblock_canaffordupgrade = il2mgr::method( xs( "BuildingBlock" ), xs( "CanAffordUpgrade" ), 3 );
	uintptr_t buildingblock_canchangetograde = il2mgr::method( xs( "BuildingBlock" ), xs( "CanChangeToGrade" ), 3 );
	uintptr_t buildingblock_upgradetograde = il2mgr::method( xs( "BuildingBlock" ), xs( "UpgradeToGrade" ), 3 );
	uintptr_t baseplayer_consolemessage = il2mgr::method( xs( "BasePlayer" ), xs( "ConsoleMessage" ), 1 );
	
	uintptr_t Settime = il2mgr::method( xs( "Time" ), xs( "set_timeScale" ), 1, xs( "UnityEngine" ) );
	uintptr_t set_atmosphere_rayleigh = il2mgr::method( xs( "Weather" ), xs( "set_atmosphere_rayleigh" ), 1, xs( "ConVar" ) );
	uintptr_t set_atmosphere_mie = il2mgr::method( xs( "Weather" ), xs( "set_atmosphere_mie" ), 1, xs( "ConVar" ) );
	uintptr_t set_atmosphere_brightness = il2mgr::method( xs( "Weather" ), xs( "set_atmosphere_brightness" ), 1, xs( "ConVar" ) );

	uintptr_t set_rain = il2mgr::method( xs( "Weather" ), xs( "set_rain" ), 1, xs( "ConVar" ) );
	uintptr_t set_storm_chance = il2mgr::method( xs( "Weather" ), xs( "set_storm_chance" ), 1, xs( "ConVar" ) );
	uintptr_t set_fog_chance = il2mgr::method( xs( "Weather" ), xs( "set_fog_chance" ), 1, xs( "ConVar" ) );

	uintptr_t alwayssprint = il2mgr::method( xs( "Input" ), xs( "alwayssprint" ), 1, xs( "ConVar" ) );

	uintptr_t time_get_time = il2mgr::method( xs( "Time" ), xs( "get_time" ), 0, xs( "UnityEngine" ) );
	uintptr_t time_get_deltaTime = il2mgr::method( xs( "Time" ), xs( "get_deltaTime" ), 0, xs( "UnityEngine" ) );
	uintptr_t debug_draw_ray = il2mgr::method( xs( "Debug" ), xs( "DrawLine" ), 4, xs( "UnityEngine" ) );
	uintptr_t create = il2mgr::method( xs( "GameObject" ), xs( "Internal_CreateGameObject" ), 2, xs( "UnityEngine" ) );
	uintptr_t dont_destroy_on_load = il2mgr::method( xs( "Object" ), xs( "DontDestroyOnLoad" ), 1, xs( "UnityEngine" ) );
	uintptr_t object_name = il2mgr::value( xs( "Object" ), xs( "name" ) );
	uintptr_t add_component = il2mgr::method( xs( "GameObject" ), xs( "AddComponent" ), 1, xs( "UnityEngine" ) );
	uintptr_t guiutility_rotatearoundpivot = il2mgr::method( xs( "GUIUtility" ), xs( "RotateAroundPivot" ), 2, xs( "UnityEngine" ) );
	uintptr_t randomrange = il2mgr::method( xs( "Random" ), xs( "Range" ), 2, xs( "UnityEngine" ) );
	uintptr_t baseplayer_mounted = il2mgr::value( xs( "BasePlayer" ), xs( "mounted" ) );
	uintptr_t basemountable_canwielditems = il2mgr::value( xs( "BaseMountable" ), xs( "canWieldItems" ) );
	uintptr_t basemountable_ignoreVehicleParent = il2mgr::value( xs( "BaseMountable" ), xs( "ignoreVehicleParent" ) );
	uintptr_t tod_sky_get_instance = il2mgr::method( xs( "TOD_Sky" ), xs( "get_Instance" ), 0 );
	uintptr_t attackentity_nextattacktime = il2mgr::value( xs( "AttackEntity" ), xs( "nextAttackTime" ) );
	uintptr_t attackentity_timesincedeploy = il2mgr::value( xs( "AttackEntity" ), xs( "timeSinceDeploy" ) );
	uintptr_t attackentity_deploydelay = il2mgr::value( xs( "AttackEntity" ), xs( "deployDelay" ) );
	uintptr_t basemelee_damageproperties = il2mgr::value( xs( "BaseMelee" ), xs( "damageProperties" ) );
	uintptr_t basemelee_processattack = il2mgr::method( xs( "BaseMelee" ), xs( "ProcessAttack" ), 1 );
	uintptr_t basemelee_blockSprintOnAttack = il2mgr::value( xs( "BaseMelee" ), xs( "blockSprintOnAttack" ) );
	uintptr_t basemelee_isAutomatic = il2mgr::method( xs( "BaseMelee" ), xs( "isAutomatic" ), 1 );
	uintptr_t attackentity_startattackcooldown = il2mgr::method( xs( "AttackEntity" ), xs( "StartAttackCooldown" ), 1 );
	uintptr_t playereyes_bodyforward = il2mgr::method( xs( "PlayerEyes" ), xs( "BodyForward" ), 0 );
	uintptr_t playereyes_movementright = il2mgr::method( xs( "PlayerEyes" ), xs( "MovementRight" ), 0 );
	uintptr_t playereyes_movementforward = il2mgr::method( xs( "PlayerEyes" ), xs( "MovementForward" ), 0 );

	uintptr_t playereyes_bodyright = il2mgr::method( xs( "PlayerEyes" ), xs( "BodyRight" ), 0 );
	uintptr_t playereyes_eye_rotation = il2mgr::method( xs( "PlayerEyes" ), xs( "get_rotation" ), 0 );

	uintptr_t physics_checkcapsule = il2mgr::method( xs( "Physics" ), xs( "CheckCapsule" ), 5, xs( "UnityEngine" ) );
	uintptr_t playertick_position = il2mgr::value( xs( "PlayerTick" ), xs( "position" ) );
	uintptr_t rigidbody_setVelocity = il2mgr::method( xs( "Rigidbody" ), xs( "set_velocity" ), 1, xs( "UnityEngine" ) );
	uintptr_t basemodel = il2mgr::value( xs( "BasePlayer" ), xs( "PlayerModel" ) );
	
	uintptr_t reloadStartDuration = il2mgr::value( xs( "BaseProjectile" ), xs( "reloadStartDuration" ) );
	uintptr_t reloadTime = il2mgr::value( xs( "BaseProjectile" ), xs( "reloadTime" ) );
	uintptr_t nextReloadTime = il2mgr::value( xs( "BaseProjectile" ), xs( "nextReloadTime" ) );

	uintptr_t OnLand = il2mgr::method( xs( "BasePlayer" ), xs( "OnLand" ), 1 );
	uintptr_t GetComponent = il2mgr::method( xs( "Component" ), xs( "Component" ), 1, xs( "UnityEngine" ) );

	uintptr_t Sp = il2mgr::method( xs( "BasePlayer" ), xs( "set_displayName" ), 1 );
}
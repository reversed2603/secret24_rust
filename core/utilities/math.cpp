#include "math.hpp"

#define M_PI_2 1.57079632679489661923
#define M_PI 3.14159265358979323846f
#define M_RADPI	57.295779513082f
#define M_PI_F ( ( float )( M_PI ) )
#define RAD2DEG( x ) ( ( float )( x ) * ( float )( 180.f / M_PI_F ) )
#define DEG2RAD( x ) ( ( float )( x ) * ( float )( M_PI_F / 180.f ) )
//#define min( a,b )            ( ( ( a ) < ( b ) ) ? ( a ) : ( b ) )
#define powww( a )	( a ) * ( a )
//#define atan2( a, b ) ( ( float )FC_NTDLL( atan2, ( double )( a ), ( double )( b ) ) )
static volatile const double Tiny = 0x1p-1022;
static volatile const double Infinity = INFINITY;
unsigned short lfsr = 0xACE1u;
unsigned int bit = 0;

// create global definition for math class.
c_math g_math;

std::string c_math::remove_trailing_zeros( float number ) {
	std::stringstream stream;
	stream << std::fixed << std::setprecision( 2 ) << number;
	std::string float_string = stream.str( );

	while( float_string.find( '.' ) != std::string::npos 
		&& float_string.back( ) == '0' 
		|| float_string.back( ) == '.' )
		float_string.pop_back( );

	return float_string;
}

vec2_t c_math::calculate_angle( const vec3_t& src, const vec3_t& dst ) {
	vec3_t dir = src - dst;
	float length = dir.length( );
	return vec2_t{ RAD2DEG( asin( dir.y / length ) ), RAD2DEG( -atan2( dir.x, -dir.z ) ) };
}

vec3_t c_math::quatmult( const vec3_t* point, vec4_t* quat )
{
	float num = quat->x * 2.f;
	float num2 = quat->y * 2.f;
	float num3 = quat->z * 2.f;
	float num4 = quat->x * num;
	float num5 = quat->y * num2;
	float num6 = quat->z * num3;
	float num7 = quat->x * num2;
	float num8 = quat->x * num3;
	float num9 = quat->y * num3;
	float num10 = quat->w * num;
	float num11 = quat->w * num2;
	float num12 = quat->w * num3;
	vec3_t result{ };
	result.x = ( 1.f - ( num5 + num6 ) ) * point->x + ( num7 - num12 ) * point->y + ( num8 + num11 ) * point->z;
	result.y = ( num7 + num12 ) * point->x + ( 1.f - ( num4 + num6 ) ) * point->y + ( num9 - num10 ) * point->z;
	result.z = ( num8 - num11 ) * point->x + ( num9 + num10 ) * point->y + ( 1.f - ( num4 + num5 ) ) * point->z;
	return result;
}

vec2_t c_math::unity_calculate_angle( const vec3_t& src, const vec3_t& dst )
{
	vec3_t dir = src - dst;

	const auto sqrtss = [ ]( float in )
	{ // thx can
		__m128 reg = _mm_load_ss( &in );
		return _mm_mul_ss( reg, _mm_rsqrt_ss( reg ) ).m128_f32[ 0 ];
	};

	float hyp = sqrtss( dir.x * dir.x + dir.y * dir.y + dir.z * dir.z );
	float nigga = roundf( dir.y );

	if( isnan( hyp ) )
		hyp = sqrtss( dir.x * dir.x + nigga * nigga );

	double ax = asin( dir.y / hyp );
	double ay = -atan2( dir.x, -dir.z );

	double x = RAD2DEG( ax );
	double y = RAD2DEG( ay );

	return vec2_t( static_cast< float >( x ), static_cast< float >( y ) );
}

float c_math::normalize_angle( float angle ) {
	while( angle > 360.0f ) {
		angle -= 360.0f;
	}
	while( angle < 0.0f ) {
		angle += 360.0f;
	}
	return angle;
}

vec3_t c_math::normalize_angles( vec3_t angles ) {
	angles.x = normalize_angle( angles.x );
	angles.y = normalize_angle( angles.y );
	angles.z = normalize_angle( angles.z );
	return angles;
}

void c_math::normalize( vec2_t& angle ) {
	if( angle.x < -89 ) 
		angle.x = -89;
	else if( angle.x > 89 ) 
		angle.x = 89;

	if( angle.y < -360 )
		angle.y += 360;
	else if( angle.y > 360 ) 
		angle.y -= 360;
}

float c_math::to_rad( float val ) {
	return val * ( PI / 180.f );
}

vec3_t c_math::cross_vector( vec3_t first_vec, vec3_t second_vec )
{
	vec3_t returnme = vec3_t( );
	returnme.x = first_vec.y * second_vec.z - first_vec.z * second_vec.y;
	returnme.y = first_vec.z * second_vec.x - first_vec.x * second_vec.z; //first_vec.x * second_vec.z - first_vec.z * second_vec.x;
	returnme.z = first_vec.x * second_vec.y - first_vec.y * second_vec.x;
	return returnme;
}

vec3_t c_math::to_euler_angles( vec4_t q1 ) {
	float num = q1.w * q1.w;
	float num2 = q1.x * q1.x;
	float num3 = q1.y * q1.y;
	float num4 = q1.z * q1.z;
	float num5 = num2 + num3 + num4 + num;
	float num6 = q1.x * q1.w - q1.y * q1.z;
	vec3_t vector = vec3_t( );
	if( num6 > 0.4995f * num5 ) {
		vector.y = 2.0f * std::atan2f( q1.y, q1.x );
		vector.x = 1.57079637f;
		vector.z = 0.0f;
		return normalize_angles( vector * 57.2958f );
	}
	if( num6 < -0.4995f * num5 ) {
		vector.y = -2.0f * std::atan2f( q1.y, q1.x );
		vector.x = -1.57079637f;
		vector.z = 0.0f;
		return normalize_angles( vector * 57.2958f );
	}
	vec4_t quaternion = vec4_t( q1.w, q1.z, q1.x, q1.y );
	vector.y = std::atan2f( 2.0f * quaternion.x * quaternion.w + 2.0f * quaternion.y * quaternion.z, 1.0f - 2.0f * ( quaternion.z * quaternion.z + quaternion.w * quaternion.w ) );
	vector.x = std::asin( 2.0f * ( quaternion.x * quaternion.z - quaternion.w * quaternion.y ) );
	vector.z = std::atan2f( 2.0f * quaternion.x * quaternion.y + 2.0f * quaternion.z * quaternion.w, 1.0f - 2.0f * ( quaternion.y * quaternion.y + quaternion.z * quaternion.z ) );
	return normalize_angles( vector * 57.2958f );
}

vec2_t c_math::cos_tan_horizontal( float angle, float range, float x, float y, int length ) {
	float our_angle = ( angle + 45.f );

	float yaw = our_angle * ( M_PI / 180.0 );

	float view_cosinus = cos( yaw );
	float view_sinus = sin( yaw );

	float x2 = range * ( -view_cosinus ) + range * view_sinus;
	float y2 = range * ( -view_cosinus ) - range * view_sinus;

	int screen_x = x + static_cast< int >( x2 / range * length );
	int screen_y = y + static_cast< int >( y2 / range * length );

	return vec2_t( screen_x, screen_y );
}

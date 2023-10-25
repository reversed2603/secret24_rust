#pragma once

#include "math.hpp"

class vec4_t {
public:
	float x, y, z, w;

public:
	inline vec4_t( ) {
		x = y = z = w = 0.0f;
	}

	inline vec4_t( float X, float Y, float Z, float W = 1.f ) {
		x = X; y = Y; z = Z; w = W;
	}

	inline float operator[ ]( int i ) const {
		return ( ( float* )this )[ i ];
	}
	
	inline vec4_t& operator-=( float v ) {
		x -= v; y -= v; z -= v, w -= v; return *this;
	}

	inline vec4_t operator*( float v ) const {
		return vec4_t( x * v, y * v, z * v, w * v );
	}

	inline vec4_t operator/( float v ) const
	{
		return vec4_t( x / v, y / v, z / v, w / v );
	}

	inline vec4_t& operator+=( const vec4_t& v ) {
		x += v.x; y += v.y; z += v.z; w += v.w; return *this;
	}

	inline vec4_t& operator+=( const float& v ) {
		x += v; y += v; z += v; w += v; return *this;
	}

	inline vec4_t& operator-=( const vec4_t& v ) {
		x -= v.x; y -= v.y; z -= v.z, w -= v.w; return *this;
	}

	inline vec4_t operator-( const vec4_t& v ) const {
		return vec4_t( x - v.x, y - v.y, z - v.z, w - v.w );
	}

	inline vec4_t operator+( const vec4_t& v ) const {
		return vec4_t( x + v.x, y + v.y, z + v.z, w + v.w );
	}

	inline bool is_zero( ) {
		return ( this->x == 0 && this->y == 0 && this->w == 0 && this->z == 0 );
	}

	inline bool contains( vec2_t point )
	{
		return point.x >= x && point.x < ( x + z ) && point.y >= y && point.y < ( y + w );
	}

	static inline float this_sqrt( float number )
	{
		long        i;
		float       x2, y;
		const float threehalfs = 1.5F;

		x2 = number * 0.5F;
		y = number;
		i = *( long* )&y; // floating point bit level hacking [ sic ]
		i = 0x5f3759df - ( i >> 1 ); // Newton's approximation
		y = *( float* )&i;
		y = y * ( threehalfs - ( x2 * y * y ) ); // 1st iteration
		y = y * ( threehalfs - ( x2 * y * y ) ); // 2nd iteration

		return 1 / y;
	}

	static vec4_t quat_look_rot( vec3_t forward, vec3_t up )
	{
		vec3_t vector = forward.unity_normalize( );
		vec3_t vector2 = up.cross( vector ).unity_normalize( );
		vec3_t vector3 = vector.cross( vector2 );
		auto m00 = vector2.x;
		auto m01 = vector2.y;
		auto m02 = vector2.z;
		auto m10 = vector3.x;
		auto m11 = vector3.y;
		auto m12 = vector3.z;
		auto m20 = vector.x;
		auto m21 = vector.y;
		auto m22 = vector.z;

		float num8 = ( m00 + m11 ) + m22;
		auto quaternion = vec4_t ( );
		if( num8 > 0.f )
		{
			auto num = this_sqrt( num8 + 1.f );
			quaternion.w = num * 0.5f;
			num = 0.5f / num;
			quaternion.x = ( m12 - m21 ) * num;
			quaternion.y = ( m20 - m02 ) * num;
			quaternion.z = ( m01 - m10 ) * num;
			return quaternion;
		}
		if( ( m00 >= m11 ) 
			&& ( m00 >= m22 ) )
		{
			auto num7 = this_sqrt( ( ( 1.f + m00 ) - m11 ) - m22 );
			auto num4 = 0.5f / num7;
			quaternion.x = 0.5f * num7;
			quaternion.y = ( m01 + m10 ) * num4;
			quaternion.z = ( m02 + m20 ) * num4;
			quaternion.w = ( m12 - m21 ) * num4;
			return quaternion;
		}
		if( m11 > m22 )
		{
			auto num6 = this_sqrt( ( ( 1.f + m11 ) - m00 ) - m22 );
			auto num3 = 0.5f / num6;
			quaternion.x = ( m10 + m01 ) * num3;
			quaternion.y = 0.5f * num6;
			quaternion.z = ( m21 + m12 ) * num3;
			quaternion.w = ( m20 - m02 ) * num3;
			return quaternion;
		}
		auto num5 = this_sqrt ( ( ( 1.f + m22 ) - m00 ) - m11 );
		auto num2 = 0.5f / num5;
		quaternion.x = ( m20 + m02 ) * num2;
		quaternion.y = ( m21 + m12 ) * num2;
		quaternion.z = 0.5f * num5;
		quaternion.w = ( m01 - m10 ) * num2;
		return quaternion;
	}

	vec4_t to_unity_color( )
	{
		return vec4_t( x / 255.f, y / 255.f, z / 255.f, w / 255.f );
	}
};

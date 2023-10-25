#pragma once
#include <Windows.h>
#include <vector>
#include <cmath>
#include <iostream>
#include "../includes/includes.hpp"

#include "../vector/vector2.hpp"
#include "../vector/vector3.hpp"
#include "../vector/vector4.hpp"
#include "../vector/color.hpp"

#define M_PI 3.14159265358979323846f
#define M_PI_F ( ( float )( M_PI ) )
#define RAD2DEG( x ) ( ( float )( x ) * ( float )( 180.f / M_PI_F ) )

#define PI 3.14159265358979323846f
#define PIX2 6.28318530718
#define PI_2 1.57079632679489661923

struct matrix_4x4 {
	public:
	inline float* operator[ ]( int i ) {
		return m[ i ];
	}

	inline const float* operator[ ]( int i ) const {
		return m[ i ];
	}

	inline float* base( ) {
		return &m[ 0 ][ 0 ];
	}

	inline const float* base( ) const {
		return &m[ 0 ][ 0 ];
	}
public:
	inline matrix_4x4( ) {
		init( 
			0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f
		 );
	}

	inline matrix_4x4( 
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33 ) {
		init( 
			m00, m01, m02, m03,
			m10, m11, m12, m13,
			m20, m21, m22, m23,
			m30, m31, m32, m33
		 );
	}

	inline void init( 
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33
	 ) {
		m[ 0 ][ 0 ] = m00;
		m[ 0 ][ 1 ] = m01;
		m[ 0 ][ 2 ] = m02;
		m[ 0 ][ 3 ] = m03;

		m[ 1 ][ 0 ] = m10;
		m[ 1 ][ 1 ] = m11;
		m[ 1 ][ 2 ] = m12;
		m[ 1 ][ 3 ] = m13;

		m[ 2 ][ 0 ] = m20;
		m[ 2 ][ 1 ] = m21;
		m[ 2 ][ 2 ] = m22;
		m[ 2 ][ 3 ] = m23;

		m[ 3 ][ 0 ] = m30;
		m[ 3 ][ 1 ] = m31;
		m[ 3 ][ 2 ] = m32;
		m[ 3 ][ 3 ] = m33;
	}

	matrix_4x4 transpose( ) const {
		return matrix_4x4( 
			m[ 0 ][ 0 ], m[ 1 ][ 0 ], m[ 2 ][ 0 ], m[ 3 ][ 0 ],
			m[ 0 ][ 1 ], m[ 1 ][ 1 ], m[ 2 ][ 1 ], m[ 3 ][ 1 ],
			m[ 0 ][ 2 ], m[ 1 ][ 2 ], m[ 2 ][ 2 ], m[ 3 ][ 2 ],
			m[ 0 ][ 3 ], m[ 1 ][ 3 ], m[ 2 ][ 3 ], m[ 3 ][ 3 ] );
	}

	float m[ 4 ][ 4 ];
};

class c_math
{
public:
	vec3_t cross_vector( vec3_t first_vec, vec3_t second_vec );

	typedef struct { double d0, d1; } double2;

	vec3_t to_euler_angles( vec4_t q1 );

	vec2_t cos_tan_horizontal( float, float, float, float, int );

	std::string remove_trailing_zeros( float );

	vec2_t calculate_angle( const vec3_t& Src, const vec3_t& Dst );
	vec3_t quatmult( const vec3_t* point, vec4_t* quat );
	vec2_t unity_calculate_angle( const vec3_t& src, const vec3_t& dst );

	float normalize_angle( float angle );

	vec3_t normalize_angles( vec3_t angles );

	void normalize( vec2_t& angle );

    float to_rad( float val );
};

extern c_math g_math;

#define ImSqrt( x ) g_math.sqrt( x )
#define ImFabs( x ) g_math.abs( x )
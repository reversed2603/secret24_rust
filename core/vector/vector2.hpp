#pragma once

class vec2_t {
public:
	float x, y;

	inline vec2_t( ) {
		x = y = 0.0f;
	}

	inline vec2_t operator/( float v ) const {
		return vec2_t( x / v, y / v );
	}
	inline vec2_t( float X, float Y ) {
		x = X; y = Y;
	}

	inline vec2_t operator-( const vec2_t& v ) const {
		return vec2_t( x - v.x, y - v.y );
	}

	inline vec2_t operator+( const vec2_t& v ) const {
		return vec2_t( x + v.x, y + v.y );
	}
	
	inline vec2_t& operator*=( const vec2_t& v ) {
		x *= v.x; y *= v.y; return *this;
	}

	inline vec2_t& operator+=( const vec2_t& v ) {
		x += v.x; y += v.y; return *this;
	}

	inline vec2_t& operator-=( const vec2_t& v ) {
		x -= v.x; y -= v.y; return *this;
	}

	inline vec2_t operator*( const float& v ) const {
		return vec2_t( x * v, y * v );
	}

	inline vec2_t& operator*=( float v ) {
		x *= v; 
		y *= v; 
		return *this;
	}

	inline bool is_zero( ) const {
		return ( x > -0.1f && x < 0.1f && y > -0.1f && y < 0.1f );
	}

	inline vec2_t& operator/=( float fl )
	{
		x /= fl;
		y /= fl;
		return *this;
	}

	inline bool operator==( const vec2_t& v ) const {
		if( this->x == v.x && this->y == v.y )
			return true;
		else
			return false;
	}

	inline vec2_t normalize( )
	{
		if( x > 89.f )
			x -= 180.f;
		else if( x < -89.f )
			x += 180.f;

		while( y < -180.0f )
			y += 360.0f;

		while( y > 180.0f )
			y -= 360.0f;

		return *this;
	}

	inline bool bigger( float x, float y, bool check_equals = false ) const
	{
		return check_equals ? ( this->x >= x || this->y >= y )
			: ( this->x > x || this->y > y );
	}

	inline float length( ) const
	{
		return std::sqrt( 
			( x * x )
			+
			( y * y )
		 );
	}

	vec2_t normalized( ) const
	{
		return vec2_t( x / length( ), y / length( ) );
	}

	float distance( vec2_t input ) const
	{
		return ( *this - input ).length( );
	}
};

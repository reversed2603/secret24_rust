#pragma once

class vec3_t
{
public:
	float x, y, z;

	inline vec3_t( ) {
		x = y = z = 0.0f;
	}

	inline vec3_t( float X, float Y, float Z ) {
		x = X; y = Y; z = Z;
	}

	inline float operator[ ]( int i ) const {
		return ( ( float* )this )[ i ];
	}

	inline vec3_t& operator-=( float v ) {
		x -= v; y -= v; z -= v; return *this;
	}

	inline vec3_t operator-( const vec2_t& v ) const {
		return vec3_t( x - v.x, y - v.y, z );
	}

	inline vec3_t operator*( float v ) const {
		return vec3_t( x * v, y * v, z * v );
	}

	inline vec3_t operator/( float v ) const
	{
		return vec3_t( x / v, y / v, z / v );
	}

	inline vec3_t& operator+=( const vec3_t& v ) {
		x += v.x; y += v.y; z += v.z; return *this;
	}

	inline vec3_t& operator+=( const float& v ) {
		x += v; y += v; z += v; return *this;
	}

	inline vec3_t& operator*=( const float& v ) {
		x *= v; y *= v; z *= v; return *this;
	}

	inline vec3_t& operator*=( const vec3_t& v ) {
		x *= v.x; y *= v.y; z *= v.z; return *this;
	}

	inline vec3_t& operator-=( const vec3_t& v ) {
		x -= v.x; y -= v.y; z -= v.z; return *this;
	}

	inline vec3_t operator-( const vec3_t& v ) const {
		return vec3_t( x - v.x, y - v.y, z - v.z );
	}

	inline vec3_t operator+( const vec3_t& v ) const {
		return vec3_t( x + v.x, y + v.y, z + v.z );
	}

	inline float length( )
	{
		auto number = ( x * x + y * y + z * z );
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

	inline vec3_t normalize( )
	{
		float mag = length( );
		if( mag > 0.00001f )
		{
			x = x / mag;
			y = y / mag;
			z = z / mag;
		}
		else
		{
			x = 0;
			y = 0;
			z = 0;
		}
		return *this;
	}

	inline bool is_zero( )
	{
		return this->x == 0 && this->y == 0 && this->z == 0;
	}

	inline float length2d( vec3_t apple )
	{
		return sqrtf( 
			( apple.x * apple.x )
			+
			( apple.z * apple.z ) );
	}

	inline bool operator==( const vec3_t& v ) const {
		return this->x == v.x && this->y == v.y && this->z == v.z;
	}

	inline bool operator==( const float v ) const {
		return this->x == v && this->y == v && this->z == v;
	}

	inline bool operator!=( const vec3_t& v ) const {
		return this->x == v.x && this->y == v.y && this->z == v.z;
	}

	inline bool operator!=( const float v ) const {
		return this->x == v && this->y == v && this->z == v;
	}

	float dot_product( vec3_t input ) const {
		return ( x * input.x ) + ( y * input.y ) + ( z * input.z );
	}

	float unity_length( )
	{
		return sqrt( ( x * x + y * y + z * z ) );
	}

	vec3_t cross( vec3_t rhs )
	{
		return vec3_t ( y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x );
	}

	void clear( )
	{
		this->x = this->y = this->z = 0;
	}

	vec3_t unity_normalize ( )
	{
		float num = unity_length( );
		if( num > 1E-05f )
		{
			x /= num;
			y /= num;
			z /= num;
		}
		else
		{
			x = 0;
			y = 0;
			z = 0;
		}

		return vec3_t( x, y, z );
	}

	float dot( const vec3_t& vector )
	{
		return x * vector.x + y * vector.y + z * vector.z;
	}

	float distance ( vec3_t input ) const
	{
		return ( *this - input ).length ( );
	}

	vec3_t normalized( ) {
		float len = length( );
		return vec3_t( x / len, y / len, z / len );
	}
};

#pragma once

class color_t {
public:
	float r{ }, g{ }, b{ }, a{ };

public:
	inline color_t( ) {
		r = g = b = a = 0.0f;
	}

	inline color_t( float R, float G, float B, float A = 255.f ) {
		r = ( R / 255.f );
		g = ( G / 255.f );
		b = ( B / 255.f );
		a = ( A / 255.f );
	}

	inline float operator[ ]( int i ) const {
		return ( ( float* )this )[ i ];
	}

	inline bool operator==( const color_t& to ) const {
		return ( to.r == this->r && to.g == this->g && to.b == this->b && to.a == this->a );
	}

	inline color_t to_normal( )
	{
		return color_t( r * 255.f, g * 255.f, b * 255.f, a * 255.f );
	}

	inline color_t to_unity( )
	{
		return color_t( r / 255.f, g / 255.f, b / 255.f, a / 255.f );
	}

	inline color_t multiply( const color_t& other, float strength ) {
		if( *this == other )
			return *this;

		return color_t(
			std::lerp( r, other.r, strength ),
			std::lerp( g, other.g, strength ),
			std::lerp( b, other.b, strength )
		 );
	}

	inline color_t alpha( float alpha, bool normal = false ) {
		float new_alpha = std::clamp( alpha, 0.f, 255.f );

		return normal ? color_t( r * 255.f, g * 255.f, b * 255.f, new_alpha ) : color_t( r, g, b, new_alpha );
	}

	inline void rainbow( float speed = 1.f ) {
		static int cases = 0;
		switch( cases )
		{
			case 0: {
				this->r -= speed;
				if( this->r <= 0 )
					cases += 1; 
				break;
			}
			case 1: {
				this->g += speed; this->b -= speed;
				if( this->g >= 255 )
					cases += 1;
				break; }
			case 2: {
				this->r += speed;
				if( this->r >= 255 ) 
					cases += 1; 
				break;
			}
			case 3: { 
				this->b += speed; this->g -= speed;
				if( this->b >= 255 ) 
					cases = 0;
				break; }
			default: {
				this->r = 255.00f; this->g = 255.00f; this->b = 0.00f;
				break; 
			}
		}
	}
};
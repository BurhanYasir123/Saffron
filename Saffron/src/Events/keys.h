#pragma once

#include "Core.h"

namespace Saffron
{
	namespace Key
	{
		#define def_key(x) constexpr int x = GLFW_KEY_##x;
		#define def_key_num(x) constexpr int D##x = GLFW_KEY_##x;
		#define def_button(x) constexpr int Mouse##x = GLFW_MOUSE_BUTTON_##x;

		// Letters
		def_key( A ); def_key( I ); def_key( Q ); def_key( Y );
		def_key( B ); def_key( J ); def_key( R ); def_key( Z );
		def_key( C ); def_key( K ); def_key( S );
		def_key( D ); def_key( L ); def_key( T );
		def_key( E ); def_key( M ); def_key( U );
		def_key( F ); def_key( N ); def_key( V );
		def_key( G ); def_key( O ); def_key( W );
		def_key( H ); def_key( P ); def_key( X );

		// Numbers
		def_key_num( 0 );
		def_key_num( 1 ); def_key_num( 2 ); def_key_num( 3 );
		def_key_num( 4 ); def_key_num( 5 ); def_key_num( 6 );
		def_key_num( 7 ); def_key_num( 8 ); def_key_num( 9 );

		// Mouse Buttons
		def_button(LEFT); def_button(MIDDLE); def_button(RIGHT);

		// Function Keys
		def_key(F1); def_key(F2); def_key(F3); def_key(F4);
		def_key(F5); def_key(F6); def_key(F7); def_key(F8);
		def_key(F9); def_key(F10); def_key(F11); def_key(F12);

		// Arrows

		def_key(RIGHT); def_key(LEFT);
		def_key(DOWN); def_key(UP);

		// Modifiers
		// todo...
	}
}
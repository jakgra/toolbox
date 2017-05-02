#include "../jak_dbg.h"
#include "../jak_ht.h"

#include "murmur3.h"

#include <stdint.h>




static int compare_keys( void * k1, void * k2 ) {
	return ( strcmp( (const char *)k1, (const char *)k2 ) == 0 );
}

static uint32_t key_to_hash( void * k ) {

	uint32_t hash;


	MurmurHash3_x86_32( k, strlen( (const char *)k ), 55, &hash );

	return hash;

}




int main() {

	int rc;
	const char * rc_char_ptr;

	jak_ht_t * ht;


	ht = jak_ht_new(
			3,
			1.65f,
			compare_keys,
			key_to_hash,
			NULL
		       );
	check( ht, final_cleanup );

	rc = jak_ht_set( ht, "buhu", "behe" );
	check( rc == 0, final_cleanup );
	check(
			( rc_char_ptr = (const char *)jak_ht_get( ht, (void *)"buhu" ) )
			&& strcmp( "behe", rc_char_ptr ) == 0,
			final_cleanup
	     );

	rc = jak_ht_set( ht, "bruhu", "brehe" );
	check( rc == 0, final_cleanup );
	check(
			( rc_char_ptr = (const char *)jak_ht_get( ht, (void *)"bruhu" ) )
			&& strcmp( "brehe", rc_char_ptr ) == 0,
			final_cleanup
	     );

	rc = jak_ht_set( ht, "bruhur", "breher" );
	check( rc == 0, final_cleanup );
	check(
			( rc_char_ptr = (const char *)jak_ht_get( ht, (void *)"bruhur" ) )
			&& strcmp( "brehe", rc_char_ptr ) != 0,
			final_cleanup
	     );


	jak_ht_free( ht );

	return 0;

final_cleanup:
	return -1;

}

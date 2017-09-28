#include "jak_da.h"

#include "jak_dbg.h"
#include <stdlib.h>
#include <string.h>




jak_da_t * jak_da_new( unsigned int initial_size, float growth_factor, unsigned int el_size ) {

	jak_da_t * a;


	if( growth_factor == -1.0f ) growth_factor = 1.618f;

	check( growth_factor > 1.0f, final_cleanup );

	a = malloc( sizeof( jak_da_t ) );
	check( a, final_cleanup );

	a->el = malloc( initial_size * el_size );
	check( a->el, a_cleanup );

	a->len = 0;
	a->max_len = initial_size;
	a->factor = growth_factor;
	a->el_size = el_size;

	return a;

a_cleanup:
	free( a );

final_cleanup:
	return NULL;

}

int jak_da_push( jak_da_t * a, void * el ) {

	int rc;


	rc = jak_da_resize( a, a->len + 1 );
	check( rc == 0, final_cleanup );

	memcpy( (char *)a->el + ( a->len - 1 ) * a->el_size, el, a->el_size );

	return 0;

final_cleanup:
	return -1;

}

void jak_da_free( jak_da_t * a ) {

	free( a->el );
	free( a );

}

int jak_da_resize( jak_da_t * a, unsigned int i ) {

	unsigned int new_len;
	void * tmp;


	if( i > a->max_len || i * a->factor < a->max_len ) {

		new_len = i * a->factor;

		tmp = realloc( a->el, new_len * a->el_size );
		check( tmp, final_cleanup );

		a->el = tmp;
		a->max_len = new_len;

	}

	a->len = i;

	return 0;

final_cleanup:
	return -1;

}

int jak_da_pop( jak_da_t * a ) {

	check( a->len > 0, final_cleanup );
	return jak_da_resize( a, a->len - 1 );

final_cleanup:
	return -1;

}

void jak_da_zero_out( jak_da_t * a ) {
	memset( a->el, 0, a->el_size * a->len );
}

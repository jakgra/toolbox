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

	unsigned int new_len;
	void * tmp;


	check( a->len <= a->max_len, final_cleanup );

	if( a->len == a->max_len ) {

		new_len = a->max_len * a->factor;
		check( new_len > a->len, final_cleanup );

		tmp = realloc( a->el, new_len * a->el_size );
		check( tmp, final_cleanup );

		a->el = tmp;
		a->max_len = new_len;

	}

	memcpy( (char *)a->el + a->len * a->el_size, el, a->el_size );
	a->len++;

	return 0;

final_cleanup:
	return -1;

}

void jak_da_free( jak_da_t * a ) {

	free( a->el );
	free( a );

}

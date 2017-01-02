#include "jak_ht.h"

#include "jak_da.h"
#include "jak_dbg.h"

#include <stdlib.h>




struct jak_ht {
	int (*compare_keys)( void *, void * );
	int (*key_to_hash)( void *, void * );
	void (*value_destructor)( void * );
	float factor;
	unsigned int buckets_c;
	jak_da_t * buckets;
};

struct buck {
	void * key;
	void * val;
};




// public functions

jak_ht_t * jak_ht_new(
		unsigned int initial_buckets_count,
		float growth_factor,
		int (*compare_keys)( void *, void * ),
		uint32_t (*key_to_hash)( void * ),
		void (*value_destructor)( void * )
		) {

	jak_ht_t * ht;


	check( initial_buckets_count > 0 && compare_keys && key_to_hash, final_cleanup );

	ht = malloc( sizeof( jak_ht_t ) );
	check( ht, final_cleanup );

	ht->buckets = calloc( initial_buckets_count, sizeof( jak_da_t ) );
	check( ht->buckets, ht_cleanup );

	ht->buckets_c = initial_buckets_count;
	ht->factor = growth_factor;
	ht->compare_keys = compare_keys;
	ht->key_to_hash = key_to_hash;
	ht->value_destructor = value_destructor;

	return ht;

ht_cleanup:
	free( ht );

final_cleanup:
	return NULL;

}

void jak_ht_free( jak_ht_t * ht ) {

	struct buck cur;
	unsigned int i;
	unsigned int j;


	if( ht->value_destructor ) {

		for( i = 0; i < ht->buckets_c; i++ ) {

			if( ! ht->buckets[i] ) continue;

			for( j = 0; j < ht->buckets[i]->len; j++ ) {

				cur = (struct buck *)jak_da_get( ht->buckets[i], j );
				if( ! cur ) continue;

				ht->value_destructor( cur->val );

			}

			jak_da_free( ht->buckets[i] );

		}

	}

	free( ht->buckets );
	free( ht );

}

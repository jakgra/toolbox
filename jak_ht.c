#include "jak_ht.h"

#include "jak_da.h"
#include "jak_dbg.h"

#include <stdlib.h>




struct jak_ht {
	int (*compare_keys)( void *, void * );
	uint32_t (*key_to_hash)( void * );
	void (*destructor)( void *, void * );
	float factor;
	unsigned int buckets_c;
	jak_da_t * * buckets;
};

struct buck {
	void * key;
	void * val;
};

struct buck * find_buck( jak_ht_t * ht, void * key, int * i ) {

	unsigned int j;
	struct buck * cur;


	*i = ht->key_to_hash( key ) % ht->buckets_c;
	if( ht->buckets[ *i ] ) {
		for( j = 0; j < ht->buckets[ *i ]->len; j++ ) {
			cur = (struct buck *)jak_da_get( ht->buckets[ *i ], j );
			if( cur && ht->compare_keys( cur->key, key ) ) {
				return cur;
			}
		}
	}
	return NULL;

}




// public functions

jak_ht_t * jak_ht_new(
		unsigned int initial_buckets_count,
		float growth_factor,
		int (*compare_keys)( void * key1, void * key2 ),
		uint32_t (*key_to_hash)( void * key ),
		void (*destructor)( void * key, void * value )
		) {

	jak_ht_t * ht;


	check( initial_buckets_count > 0 && compare_keys && key_to_hash, final_cleanup );

	ht = malloc( sizeof( jak_ht_t ) );
	check( ht, final_cleanup );

	ht->buckets = calloc( initial_buckets_count, sizeof( jak_da_t * ) );
	check( ht->buckets, ht_cleanup );

	ht->buckets_c = initial_buckets_count;
	ht->factor = growth_factor;
	ht->compare_keys = compare_keys;
	ht->key_to_hash = key_to_hash;
	ht->destructor = destructor;

	return ht;

ht_cleanup:
	free( ht );

final_cleanup:
	return NULL;

}

void jak_ht_free( jak_ht_t * ht ) {

	struct buck * cur;
	unsigned int i;
	unsigned int j;


	for( i = 0; i < ht->buckets_c; i++ ) {

		if( ! ht->buckets[i] ) continue;

		if( ht->destructor ) {

			for( j = 0; j < ht->buckets[i]->len; j++ ) {

				cur = (struct buck *)jak_da_get( ht->buckets[i], j );
				if( ! cur ) continue;

				ht->destructor( cur->key, cur->val );

			}

		}

		jak_da_free( ht->buckets[i] );

	}

	free( ht->buckets );
	free( ht );

}

int jak_ht_set( jak_ht_t * ht, void * key, void * value ) {

	int rc;

	struct buck * cur;
	int i;
	struct buck new;


	cur = find_buck( ht, key, &i );

	if( cur ) {

		cur->val = value;

	} else {

		if( ! ht->buckets[i] ) {
			ht->buckets[i] = jak_da_new( 1, 2, sizeof( struct buck ) );
			check( ht->buckets[i], final_cleanup );
		}

		new.key = key;
		new.val = value;

		rc = jak_da_push( ht->buckets[i], &new );
		check( rc == 0, final_cleanup );

	}

	return 0;

final_cleanup:
	return -1;

}

void * jak_ht_get( jak_ht_t * ht, void * key ) {

	int i;
	struct buck * cur;


	cur = find_buck( ht, key, &i );
	if( cur ) {
		return cur->val;
	} else {
		return NULL;
	}

}

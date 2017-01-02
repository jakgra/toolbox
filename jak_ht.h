#ifndef jak_ht_h
#define jak_ht_h

/**
 * @file
 * @brief Hashtable class
 *
 * All functions that return int return 0 on success if not specified otherwise
 */




/**
 * The main opaque hashtable type.
 */
typedef struct jak_ht jak_ht_t;

/**
 * Creates a new hashtable object.
 *
 * \Returns NULL on error.
 */
jak_ht_t * jak_ht_new(
		unsigned int initial_buckets_count,
		float growth_factor,
		int (*compare_keys)( void *, void * ),
		uint32_t (*key_to_hash)( void * ),
		void (*value_destructor)( void * )
		);

/**
 * Frees all the memory associated with the ht object created via jak_ht_new() and deallocates it.
 */
void jak_ht_free( jak_ht_t * ht );

/**
 * Pushes a new element to the hashtable or assigns the value to an existing one.
 */
int jak_ht_set( jak_ht_t * ht, void * key, void * value );

/**
 * \Returns the element identified by the key or NULL if no matching elements are found.
 */
void * jak_ht_get( jak_ht_t * ht, void * key );




#endif

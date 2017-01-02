#ifndef jak_da_h
#define jak_da_h

/**
 * @file
 * @brief Dynamic array class
 *
 * All functions that return int return 0 on success if not specified otherwise
 */




/**
 * The main dynamic array type. This type should be used as readonly.
 * It is only public so you can access the len and el elements without an accessor function.
 */
typedef struct {
	unsigned int len;
	unsigned int max_len;
	float factor;
	unsigned int el_size;
	void * el;
} jak_da_t;

/**
 * Creates a new dynamic array.
 * If growth factor is -1.0f then the default value is used ( golden ratio ).
 * Growth factor must be more than 1.0f
 * el_size is the size of the elements. It can be sizeof( void * ) or sizeof( sturct some_struct ) or sizeof( int )
 * The functions then use memcpy to copy the structures where needed ...
 *
 * \Returns NULL on error.
 */
jak_da_t * jak_da_new( unsigned int initial_size, float growth_factor, unsigned int el_size );

/**
 * Pushes a new element to the end of the array. Adds +1 to a->len and
 * reallocates/grows the backing memory store if needed.
 */
int jak_da_push( jak_da_t * a, void * el );




#endif

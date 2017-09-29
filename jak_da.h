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
 * The following must be true or pushing to the array will fail with a nice error message :)
 * (int)( initial_size * growth_factor ) > (int)initial_size
 * So for example for the default factor the minimal initial_size is 2.
 * If growth factor is -1.0f then the default value is used ( golden ratio ).
 * Growth factor must be more than 1.0f
 * el_size is the size of the elements. It can be sizeof( void * ) or sizeof( sturct some_struct ) or sizeof( int )
 * The functions then use memcpy to copy the structures where needed ...
 *
 * \Returns NULL on error.
 */
jak_da_t * jak_da_new( unsigned int initial_size, float growth_factor, unsigned int el_size );

/**
 * Frees all the memory associated with the a object created via jak_da_new() and deallocates it.
 */
void jak_da_free( jak_da_t * a );

/**
 * Pushes a new element to the end of the array. Adds +1 to a->len and
 * reallocates/grows the backing memory store if needed.
 */
int jak_da_push( jak_da_t * a, void * el );

/**
 * Pops the last element off the array (attention it doesn't memset() it to NULL!)
 */
int jak_da_pop( jak_da_t * a );

/**
 * Accessor macro for array elements.
 * To access the element at index i of array a use: jak_da_el( a, i )
 */
#define jak_da_get( a, i ) ( ( i < a->len && i >= 0 ) ? ( (void *)( (char *)( a )->el + ( i ) * a->el_size ) ) : NULL )

/**
 * Accessor macro for last element in array.
 */
#define jak_da_last( a ) ( ( a->len > 0  ) ? ( (void *)( (char *)( a )->el + ( a->len - 1 ) * a->el_size ) ) : NULL )

/**
 * Allocates or deallocates place in the array so it contains i members.
 * The lenght is changed and the buffer backing the dynamic array
 * is grown or shrinked according to the growth factor.
 */
int jak_da_resize( jak_da_t * a, unsigned int i );

/**
 * Overwrites the buffer backing the dynamic array with zeros.
 */
void jak_da_zero_out( jak_da_t * a );




#endif

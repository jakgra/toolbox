#ifndef jak_sl_h
#define jak_sl_h

/**
 * @file
 * @brief Single linked list class
 *
 * All functions that return int return 0 on success if not specified otherwise
 */




/**
 * The main list element type. This type should normally be used as readonly.
 * It is only public so looping is easier.
 */
typedef struct jak_sl_el {
	void * val;
	struct jak_sl_el * next;
} jak_sl_el_t;

/**
 * The main list element type. This type should normally be used as readonly.
 * It is only public so looping is easier.
 */
typedef struct {
	jak_sl_el_t * first;
	jak_sl_el_t * last;
	void (*destructor)( void * );
} jak_sl_t;

/**
 * Creates a new list.
 * \Return NULL on error.
 * \param value_destructor A destructor that gets called for each (jak_sl_el_t *)->val. Can be NULL.
 */
jak_sl_t * jak_sl_new( void (*value_destructor)( void * ) );

/**
 * Frees all memory associated with this list calling all the destructors.
 */
void jak_sl_free( jak_sl_t * l );

/**
 * Pushes a new element to the end of the list
 */
int jak_sl_push( jak_sl_t * l, void * val );

/**
 * Adds a new element to the beginning of the list.
 */
int jak_sl_unshift( jak_sl_t * l, void * val );

/**
 * Deletes the first element of the list and calls its destructor if set.
 */
void jak_sl_shift( jak_sl_t * l );

/**
 * Deletes the element with the same pointer for val as this functions argument.
 */
void jak_sl_remove( jak_sl_t * l, void * val );

/**
 * A macro for easier looping trough the list.
 */
#define JAK_SL_FOREACH( L, V ) \
{ \
	jak_sl_el_t * jak_sl_p_el = L->first; \
	for( V = ( jak_sl_p_el ? jak_sl_p_el->val : NULL ); jak_sl_p_el; ( jak_sl_p_el = jak_sl_p_el->next ), ( V = ( jak_sl_p_el ? jak_sl_p_el->val : NULL ) ) )
#define JAK_SL_FOREACH_END }




#endif

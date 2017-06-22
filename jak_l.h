#ifndef jak_l_h
#define jak_l_h

/**
 * @file
 * @brief Double linked list class
 *
 * All functions that return int return 0 on success if not specified otherwise
 */




/**
 * The main list element type. This type should normally be used as readonly.
 * It is only public so looping is easier.
 */
typedef struct jak_l_el {
	void * val;
	struct jak_l_el * next;
	struct jak_l_el * prev;
} jak_l_el_t;

/**
 * The main list element type. This type should normally be used as readonly.
 * It is only public so looping is easier.
 */
typedef struct {
	jak_l_el_t * first;
	jak_l_el_t * last;
	void (*destructor)( void * );
} jak_l_t;

/**
 * Creates a new list.
 * \Return NULL on error.
 * \param value_destructor A destructor that gets called for each (jak_l_el_t *)->val. Can be NULL.
 */
jak_l_t * jak_l_new( void (*value_destructor)( void * ) );

/**
 * Frees all memory associated with this list calling all the destructors.
 */
void jak_l_free( jak_l_t * l );

/**
 * Pushes a new element to the end of the list
 */
int jak_l_push( jak_l_t * l, void * val );

/**
 * Deletes the last element of the list, calling its destructor if set.
 */
void jak_l_pop( jak_l_t * l );

/**
 * Adds a new element to the beginning of the list.
 */
int jak_l_unshift( jak_l_t * l, void * val );

/**
 * Deletes the first element of the list and calls its destructor if set.
 */
void jak_l_shift( jak_l_t * l );

/**
 * Deletes the element with the same pointer for val as this functions argument.
 */
void jak_l_remove( jak_l_t * l, void * val );

/**
 * A macro for easier looping trough the list.
 */
#define JAK_L_FOREACH( L, V ) \
{ \
	jak_l_el_t * jak_l_p_el = L->first; \
	for( V = ( jak_l_p_el ? jak_l_p_el->val : NULL ); jak_l_p_el; ( jak_l_p_el = jak_l_p_el->next ), ( V = ( jak_l_p_el ? jak_l_p_el->val : NULL ) ) )
#define JAK_L_FOREACH_END }

/**
 * A macro for easier reverse looping trough the list.
 */
#define JAK_L_FOREACH_REV( L, V ) \
{ \
	jak_l_el_t * jak_l_p_el = L->last; \
	for( V = ( jak_l_p_el ? jak_l_p_el->val : NULL ); jak_l_p_el; ( jak_l_p_el = jak_l_p_el->prev ), ( V = ( jak_l_p_el ? jak_l_p_el->val : NULL ) ) )




#endif

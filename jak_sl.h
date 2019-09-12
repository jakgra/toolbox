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

/**
 * A very usefull macro to make the linked list typesafe.
 * To create a list of integers just use
 * JAK_DA_TYPE_SAFE(my_l, int)
 * and then use the above functions with the my_l prefix:
 * my_l_t *list = my_l_new(NULL);
 * int *a = malloc(sizeof(int));
 * *a = 3;
 * my_l_push(list, a);
 * for (my_l_el_t *el = my_l_first(list); el; el = my_l_next(el)) {
 * int *b = my_l_val(el);
 * if (b) {
 * printf("3 = %d", *b);
 * }
 * }
 */
#define JAK_SL_TYPE_SAFE(prefix, type)                                         \
                                                                               \
  typedef struct {                                                             \
  } prefix##_t;                                                                \
                                                                               \
  typedef struct {                                                             \
  } prefix##_el_t;                                                             \
                                                                               \
  static inline prefix##_t *prefix##_new(void (*value_destructor)(type *)) {   \
    return (prefix##_t *)jak_sl_new((void (*)(void *))value_destructor);       \
  }                                                                            \
                                                                               \
  static inline void prefix##_free(prefix##_t *l) {                            \
    return jak_sl_free((jak_sl_t *)l);                                         \
  }                                                                            \
                                                                               \
  static inline int prefix##_push(prefix##_t *l, type *val) {                  \
    return jak_sl_push((jak_sl_t *)l, (void *)val);                            \
  }                                                                            \
                                                                               \
  static inline int prefix##_unshift(prefix##_t *l, type *val) {               \
    return jak_sl_unshift((jak_sl_t *)l, (void *)val);                         \
  }                                                                            \
                                                                               \
  static inline void prefix##_shift(prefix##_t *l) {                           \
    jak_sl_shift((jak_sl_t *)l);                                               \
  }                                                                            \
                                                                               \
  static inline void prefix##_remove(prefix##_t *l, type *val) {               \
    jak_sl_remove((jak_sl_t *)l, (void *)val);                                 \
  }                                                                            \
                                                                               \
  static inline prefix##_el_t *prefix##_first(prefix##_t *l) {                 \
    return (prefix##_el_t *)(((jak_sl_t *)l)->first);                          \
  }                                                                            \
                                                                               \
  static inline type *prefix##_val(prefix##_el_t *el) {                        \
    return (type *)(el ? ((jak_sl_el_t *)el)->val : NULL);                     \
  }                                                                            \
                                                                               \
  static inline prefix##_el_t *prefix##_next(prefix##_el_t *el) {              \
    return (prefix##_el_t *)(el ? ((jak_sl_el_t *)el)->next : NULL);           \
  }

#endif

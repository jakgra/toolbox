#include "jak_l.h"
#include "jak_dbg.h"

#include <stdlib.h>




jak_l_t * jak_l_new( void (*value_destructor)( void * ) ) {

	jak_l_t * l;


	l = malloc( sizeof( jak_l_t ) );
	check( l, final_cleanup );

	l->first = NULL;
	l->last = NULL;
	l->destructor = value_destructor;

	return l;

final_cleanup:
	return NULL;

}

void jak_l_free( jak_l_t * l ) {

	jak_l_el_t * cur;
	jak_l_el_t * prev;


	if( l ) {
		cur = l->first;
		while( cur ) {
			if( l->destructor ) l->destructor( cur->val );
			prev = cur;
			cur = cur->next;
			free( prev );
		}
		free( l );
	}
	return;

}

int jak_l_push( jak_l_t * l, void * val ) {

	jak_l_el_t * el;


	el = malloc( sizeof( jak_l_el_t ) );
	check( el, final_cleanup );

	el->val = val;
	el->next = NULL;
	el->prev = l->last;
	if( l->last ) l->last->next = el;
	l->last = el;

	if( ! l->first ) l->first = el;

	return 0;

final_cleanup:
	return -1;

}

void jak_l_pop( jak_l_t * l ) {

	jak_l_el_t * el;


	if( l->last ) {
		el = l->last;
		l->last = el->prev;
		l->last->next = NULL;
		if( l->destructor ) l->destructor( el->val );
		free( el );
	}
	return;

}

int jak_l_unshift( jak_l_t * l, void * val ) {

	jak_l_el_t * el;


	el = malloc( sizeof( jak_l_t ) );
	check( el, final_cleanup );

	el->val = val;
	el->next = l->first;
	el->prev = NULL;
	if( l->first ) l->first->prev = el;
	l->first = el;

	if( ! l->last ) l->last = el;

	return 0;

final_cleanup:
	return -1;

}

void jak_l_shift( jak_l_t * l ) {

	jak_l_el_t * el;


	if( l->first ) {
		el = l->first;
		if( l->destructor ) l->destructor( el->val );
		if( el->next ) el->next->prev = NULL;
		l->first = el->next;
		free( el );
	}
	return;

}

void jak_l_remove( jak_l_t * l, void * val ) {

	jak_l_el_t * el;


	for( el = l->first; el; el = el->next ) {
		if( el->val == val ) {
			break;
		}
	}

	if( el ) {
		if( el->prev ) {
			el->prev->next = el->next;
		} else {
			l->first = el->next;
		}
		if( el->next ) {
			el->next->prev = el->prev;
		} else {
			l->last = el->prev;
		}
		if( l->destructor ) l->destructor( el->val );
		free( el );
	}
	return;

}

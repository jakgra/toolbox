#include "jak_sl.h"
#include "jak_dbg.h"

#include <stdlib.h>




jak_sl_t * jak_sl_new( void (*value_destructor)( void * ) ) {

	jak_sl_t * l;


	l = malloc( sizeof( jak_sl_t ) );
	check( l, final_cleanup );

	l->first = NULL;
	l->last = NULL;
	l->destructor = value_destructor;

	return l;

final_cleanup:
	return NULL;

}

void jak_sl_free( jak_sl_t * l ) {

	jak_sl_el_t * cur;
	jak_sl_el_t * prev;


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

int jak_sl_push( jak_sl_t * l, void * val ) {

	jak_sl_el_t * el;


	el = malloc( sizeof( jak_sl_el_t ) );
	check( el, final_cleanup );

	el->val = val;
	el->next = NULL;
	if( l->last ) l->last->next = el;
	l->last = el;

	if( ! l->first ) l->first = el;

	return 0;

final_cleanup:
	return -1;

}

int jak_sl_unshift( jak_sl_t * l, void * val ) {

	jak_sl_el_t * el;


	el = malloc( sizeof( jak_sl_t ) );
	check( el, final_cleanup );

	el->val = val;
	el->next = l->first;
	l->first = el;

	if( ! l->last ) l->last = el;

	return 0;

final_cleanup:
	return -1;

}

void jak_sl_shift( jak_sl_t * l ) {

	jak_sl_el_t * el;


	if( l->first ) {
		el = l->first;
		if( l->destructor ) l->destructor( el->val );
		l->first = el->next;
		free( el );
	}
	return;

}

void jak_sl_remove( jak_sl_t * l, void * val ) {

	jak_sl_el_t * el;
	jak_sl_el_t * prev;


	prev = NULL;
	for( el = l->first; el; el = el->next ) {
		if( el->val == val ) {
			break;
		}
		prev = el;
	}

	if( el ) {
		if( prev ) {
			prev->next = el->next;
		} else {
			l->first = el->next;
		}
		if( ! el->next ) {
			l->last = prev;
		}
		if( l->destructor ) l->destructor( el->val );
		free( el );
	}
	return;

}

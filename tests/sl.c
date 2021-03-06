#include "../jak_sl.h"
#include "../jak_dbg.h"

#include <stdlib.h>




int main() {

	int rc;

	jak_sl_t * l;
#define ELS_LEN 111
	int i;
	int * val;
	void * val2;
	float v;
	float v1;
	float v2;
	float v3;


	l = jak_sl_new( free );
	check( l, final_cleanup );

	for( i = 1; i < ELS_LEN - 1; i++ ) {
		val = malloc( sizeof( int ) );
		check( val, final_cleanup );
		*val = 22 * i;
		rc = jak_sl_push( l, val );
		check( rc == 0, final_cleanup );
	}

	val = malloc( sizeof( int ) );
	check( val, final_cleanup );
	*val = 0;
	rc = jak_sl_unshift( l, val );
	check( rc == 0, final_cleanup );

	val = malloc( sizeof( int ) );
	check( val, final_cleanup );
	*val = i * 22;
	rc = jak_sl_push( l, val );
	check( rc == 0, final_cleanup );

	i = 0;

	JAK_SL_FOREACH( l, val2 ) {
		check( *( (int *)val2 ) == i * 22, final_cleanup );
		i++;
	}
	JAK_SL_FOREACH_END;
	check( i == ELS_LEN, final_cleanup );

	jak_sl_free( l );

	l = jak_sl_new( NULL );

	v1 = 0.5f;
	v2 = 0.55f;
	v3 = 0.555f;

	rc = jak_sl_push( l, &v1 );
	check( rc == 0, final_cleanup );

	rc = jak_sl_unshift( l, &v2 );
	check( rc == 0, final_cleanup );

	rc = jak_sl_push( l, &v3 );
	check( rc == 0, final_cleanup );

	i = 0;
	JAK_SL_FOREACH( l, val2 ) {
		if( i == 0 ) {
			v = 0.55f;
		} else if( i == 1 ) {
			v = 0.5f;
		} else {
			v = 0.555f;
		}
		check( *( (float *)val2 ) == v, final_cleanup );
		i++;
	}
	JAK_SL_FOREACH_END;
	check( i == 3, final_cleanup );

	jak_sl_remove( l, &v3 );
	jak_sl_remove( l, &v2 );

	i = 0;
	JAK_SL_FOREACH( l, val2 ) {
		check( *( (float *)val2 ) == 0.5f, final_cleanup );
		i++;
	}
	JAK_SL_FOREACH_END;
	check( i == 1, final_cleanup );

	jak_sl_free( l );

	return 0;

final_cleanup:
	return -1;

}

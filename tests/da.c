#include "../jak_dbg.h"
#include "../jak_da.h"




int main() {

	int rc;

	jak_da_t * a;
#define ELS_LEN 300
	int els[ ELS_LEN ];
	unsigned int i;


	a = jak_da_new( 2, -1.0f, sizeof( int ) );
	check( a, final_cleanup );

	for( i = 0; i < ELS_LEN; i++ ) {

		els[i] = (int)i * 22;

		rc = jak_da_push( a, &els[i] );
		check( rc == 0, final_cleanup );

	}

	for( i = 0; i < a->len; i++ ) {

		check( *( (int *)jak_da_get( a, i ) ) == (int)i * 22, final_cleanup );

	}
	check( i == ELS_LEN, final_cleanup );

	while( a->len > 1 ) {

		rc = jak_da_pop( a );
		check( rc == 0, final_cleanup );

	}
	check( a->len == 1, final_cleanup );

	rc = jak_da_push( a, &els[5] );
	check( rc == 0, final_cleanup );

	rc = jak_da_push( a, &els[3] );
	check( rc == 0, final_cleanup );

	jak_da_zero_out( a );
	check(
			*( (int *)jak_da_get( a, 0 ) ) == 0
			&& *( (int *)jak_da_get( a, 1 ) ) == 0,
			final_cleanup
	     );

	jak_da_free( a );

	return 0;

final_cleanup:
	return -1;

}

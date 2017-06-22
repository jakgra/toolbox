#include <jak_hash_bstring.h>
#include <murmur3.h>




uint32_t jak_hash_bstring( void * key ) {

	bstring s;
	uint32_t hash;


	s = (bstring)key;
	MurmurHash3_x86_32( (void *)s->data, s->slen, 55, &hash );

	return hash;

}

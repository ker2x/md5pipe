/*
           DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
                   Version 2, December 2004
 
Copyright (C) 2004 Sam Hocevar
 14 rue de Plaisance, 75014 Paris, France
Everyone is permitted to copy and distribute verbatim or modified
copies of this license document, and changing it is allowed as long
as the name is changed.
 
           DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 
 0. You just DO WHAT THE FUCK YOU WANT TO.
*/

#include "stdio.h"
#include "stdlib.h"
#include "md5.h"

void main(int argc, char **argv) {

	char buffer[MD5_BLOCK_LENGTH];

	size_t buffer_size = MD5_BLOCK_LENGTH;
	size_t bytes_read = 0;
	uint8_t digest[MD5_DIGEST_LENGTH];

	char printable_digest[MD5_DIGEST_LENGTH];

	struct md5_ctx md5;

	md5_reset(&md5);

	while(1) {
		bytes_read = fread(&buffer,1 , 64, stdin); 
		if(bytes_read == 0) { break; }
		md5_update(&md5,&buffer, bytes_read);
		fwrite(&buffer, sizeof(char), bytes_read, stdout);
	}

	md5_final(digest,&md5);
	hash2hex(digest,printable_digest);
	fprintf(stderr,"%s",printable_digest);

}

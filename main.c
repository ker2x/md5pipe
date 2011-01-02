#include "stdio.h"
#include "stdlib.h"
#include "md5.h"

void main(int argc, char **argv) {

	FILE *instream;
	FILE *outstream;

	char buffer[MD5_BLOCK_LENGTH];

	size_t buffer_size = sizeof(char) * (MD5_BLOCK_LENGTH);
	size_t bytes_read = 0;

	uint64_t total_byte_read = 0;
	struct md5_ctx md5;
	uint8_t digest[MD5_DIGEST_LENGTH];
	char printable_digest[MD5_DIGEST_LENGTH];

	//initialisation
	md5_reset(&md5);

	instream = fopen("/dev/stdin","r");
	if(instream == NULL) { printf("can't open /dev/stdin"); exit(1); }

	outstream = fopen("/dev/stdout","w");
	if(outstream == NULL) { printf("can't open /dev/stdout"); exit(1); }


	while(1) {
		bytes_read = fread(&buffer,sizeof(char), 64, instream); 
		md5_update(&md5,&buffer, bytes_read);
		fwrite(&buffer, sizeof(char), bytes_read / sizeof(char), outstream);
		if(bytes_read == 0) { break; }
	}
	md5_final(digest,&md5);
	hash2hex(digest,printable_digest);
	fprintf(stderr,"%s",printable_digest);

	fclose(instream);
	fclose(outstream);
}

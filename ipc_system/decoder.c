#include "decoder.h"

void u8_to_hex( char *result, const uint8_t x ) {
	uint8_t x1 = ( x % 16 );
	uint8_t x2 = ( (x/16) % 16 );
	if ( x2 <= 9 ) { result[0] = x2+48; }
	if ( x1 <= 9 ) { result[1] = x1+48; }
	if ( x2 > 9 ) { result[0] = x2+87; }
	if ( x1 > 9 ) { result[1] = x1+87; }
	result[2] = '\0';
}

char* encoder( const char const *program_name, const char const *recipient_program, const char const *state, const int return_code, const char const *action, char *encoded_str ) {
	uint8_t len[3] = {0,0,0};
	char hex_table[9];
	char hex_len[3];
	char hex_len2[3];
	char hex_len3[3];
	char hex_code[3];

	len[0] = strlen( program_name );
	len[1] = strlen( recipient_program );
	len[2] = strlen( action );
	printf("len = %d\n", len[0]);
	printf("len2 = %d\n", len[1]);
	printf("len3 = %d\n", len[2]);

	u8_to_hex( hex_len, len[0] );
	u8_to_hex( hex_len2, len[1] );
	u8_to_hex( hex_len3, len[2] );

	u8_to_hex( hex_code, return_code );
	printf("hex_code = %s\n", hex_code);

	printf("hex_len = %s\n", hex_len);
	printf("hex_len2 = %s\n", hex_len2);
	printf("hex_len3 = %s\n", hex_len3);

	for ( uint8_t i = 0; i < strlen(hex_len); i++ ) {
		hex_table[i] = hex_len[i];
	}
	hex_table[ strlen(hex_len) ] = ';';

	for ( uint8_t i = 0; i < strlen(hex_len2); i++ ) {
		hex_table[ i + strlen(hex_len) + 1 ] = hex_len2[i];
	}
	hex_table[ strlen(hex_len) + strlen(hex_len2) + 1 ] = ';';

	for ( uint8_t i = 0; i < strlen(hex_len3); i++ ) {
		hex_table[ i + strlen(hex_len) + strlen(hex_len2) + 2 ] = hex_len3[i];
	}
	hex_table[ strlen(hex_len) + strlen(hex_len2) + strlen(hex_len3) + 2 ] = '\0';

	printf("hex_table = %s\n", hex_table);


	sprintf(encoded_str, "{%s\n%s\n&%s\n*%s\n!%s\n-%s\n}\n\0", hex_table, program_name, recipient_program, state, hex_code, action);


	printf("encoded_str = \n%s\n", encoded_str);

	return encoded_str;
}



char* encode_msg( const char const *program_name, const char const *recipient_program, const char const *msg, char *encoded_str ) {
	uint8_t len[3] = {0,0,0};
	char hex_len[3];
	char hex_len2[3];
	char hex_len3[3];

	len[0] = strlen( program_name );
	len[1] = strlen( recipient_program );
	len[2] = strlen( msg );

	u8_to_hex( hex_len, len[0] );
	u8_to_hex( hex_len2, len[1] );
	u8_to_hex( hex_len3, len[2] );

	sprintf(encoded_str, "{%s;%s;%s\n%s\n&%s\n~%s\n}\n\0", hex_len, hex_len2, hex_len3, program_name, recipient_program, msg);

	return encoded_str;
}


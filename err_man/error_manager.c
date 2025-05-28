#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#include "../shm_system/utils.h"
#include "error_manager.h"
#include "../ipc_system/decoder.h"


#define this_DEBUG


void check_dependencies( const char directory[], const char library[] ) {
	DIR             *dirp;
	struct dirent   *direntp;

	dirp = opendir( directory );

	if ( dirp == NULL ) {
		fprintf(stderr, "can't open '%s' directory", directory );
	} else {
		while (true) {
			direntp = readdir( dirp );
			if ( direntp == NULL ) { break; }
			if ( strcmp(direntp->d_name, library) == 0 ) {
				printf("\033[36mlibtheLib.so\033[0m : are find\033[0m\n");
			}
			//printf( "\033[2m\033[35m%s\033[0m\n", direntp->d_name );
			}
		closedir( dirp );
	}
}



int main( const uint8_t argc, const char const *argv[] ) {
//	ErrMemData test;
//	test.err_semaphore = create_err_semaphore();
//	MsgMemData test2;
//	test2.msg_semaphore = create_msg_semaphore();

//	if (argc == 3) {
		//drop_semaphore( test2.msg_semaphore );
		//drop_semaphore( test.err_semaphore );
//        	printf("semaphore are dropped.\n");
//	}

	//char msg[12] = "hello world!";

//	printf("\033[2m\033[36mSemaphore is taken. Waiting for it to be dropped.\033[0m\n");
//    	sem_wait(test.err_semaphore);


//	test.shm = open_err_shm();
//	char *addr;
//	addr = read_shm( test.shm, addr );
//	printf("get from from : %s\n", addr);
	char directory[4] = "lib\0";
	char library[13] = "libtheLib.so\0";
	check_dependencies( directory, library );
//	free(addr);
	//delete_msg();


//	drop_semaphore( test.err_semaphore );
//        printf("\033[2m\033[35merr semaphore are dropped.\033[0m\n");


//	char msg[255];
//	const char m1[12] = "err_manager\0";
//	const char m2[16] = "program_starter\0";
//	const char m3[13] = "the success!\0";
//	encode_msg(m1, m2, m3, msg);
//	printf("msg addr = %s", msg);

//	printf("\033[2m\033[36mSemaphore is taken. Waiting for it to be dropped.\033[0m\n");
//    	sem_wait(test2.msg_semaphore);

//	test2.shm = open_msg_shm();
//	write_shm( test2.shm, msg );
	//delete_err();

//	drop_semaphore( test2.msg_semaphore );
//        printf("\033[2m\033[35merr semaphore are dropped.\033[0m\n");



//	sem_close(test.err_semaphore);
//    	printf("\033[2m\033[36mclose err sem\033[0m\n");

//	sem_close(test2.msg_semaphore);
//    	printf("\033[2m\033[36mclose err sem\033[0m\n");

	return 0;
}

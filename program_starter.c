#include <stdio.h>
#include <stdlib.h>

#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>

#include <assert.h>

//#include <errno.h>
//#include <sys/types.h>
#include <sys/wait.h>

#include "shm_system/utils.h"
#include "ipc_system/decoder.h"

#define starter_DEBUG
#define starter_INFO
#define starter_ERROR
#define starter_FATAL




int main( const uint8_t argc, const char const *argv[] ) {
#ifdef starter_DEBUG
	fprintf(stderr, "\033[0m\033[2m▇▇▇\033[100m \e[48;5;235m Hi Friend!! \033[100m \033[0m\033[2m▇▇▇\033[0m\n");
#endif

	bool isArg = false;
	char **progv = NULL;
	uint8_t progc = 0;
#ifdef starter_INFO
	fprintf(stderr, "\033[3m\033[2mstarter start.. xD\033[0m\n");
#endif

	for ( uint8_t i = 1; i < argc; i++ ) {
		if ( argv[i][0] == '-' ) {
			isArg = true;
		}
		if ( isArg == true ) {
			for ( uint8_t j = 1; j < strlen( argv[i] ); j++ ) {
				if ( argv[i][j] == 'h' && argv[i][j+1] == 0 ) {
					fprintf(stderr, "imagine help text\n");
					exit(0);
				}// -h
				if ( argv[i][j] == 'a' && argv[i][j+1] == 0 ) {
					fprintf(stderr, "arguments count: %d\n", argc);
					for ( uint8_t k = 0; k < argc; k++ ) {
						fprintf( stderr, "%s\n", argv[k] );
					}
				}// -a
				if ( argv[i][j] == '-' && argv[i][j+=1] == 'a' && argv[i][j+=1] == 'r' && argv[i][j+=1] == 'g' && argv[i][j+1] == 0 ) {
					fprintf(stderr, "arguments count: %d\n", argc);
					for ( uint8_t k = 0; k < argc; k++ ) {
						fprintf( stderr, "%s\n", argv[k] );
					}
				}// --arg
				if ( argv[i][j] == 'c' && argv[i][j+=1] == '=' && argv[i][j+=1] != 0 ) {
					uint8_t progc_1 = 0;
					uint8_t progc_2 = 0;
					if ( argv[i][j+1] == 0 ) {
						progc_2 = argv[i][j] - 48;
					} else {
						progc_1 = argv[i][j] - 48;
						progc_2 = argv[i][j+1] - 48;
					}
					progc = (progc_1 * 10) + progc_2;
				}// -c
			}
		}// if isArg = true
		isArg = false;
	}// argc for

	assert(progc > 0);
	progv = malloc( sizeof(*progv) * progc );

	uint8_t j = 0;
	for ( uint8_t i = 1; i < argc; i++ ) {
		if ( argv[i][0] == '-' ) {
			isArg = true;
		}
		if ( isArg == false ) {
			if ( j < progc ) {
				for ( uint8_t k = 0; k < strlen( argv[i] ); k++ ) {
					progv[j] = malloc( sizeof(**progv) * strlen(argv[i]) );
				}
				for ( uint8_t k = 0; k < strlen( argv[i] ); k++ ) {
					progv[j][k] = argv[i][k];
				}
			}
			j++;
		}
		isArg = false;
	}// argc for 2

	pid_t pids[progc];
	int prog_s[progc];
	int stat_var = 0;
	bool is_fail = false;

	for ( uint8_t i = 0; i < progc; ++i ) {
		int pid = fork();
		if ( pid == 0 ) {
			//printf(" CHILD MAIN: PID %d : PARENT PID  %d\n", getpid(), getppid());
			prog_s[i] = execl( progv[i], progv[i], "arg2", NULL );
			exit( prog_s[i] );
		} else {
			pids[i] = pid;
		}
	}// start proceses

#ifdef starter_INFO
	fprintf( stderr, "\033[3m\033[2mstarter wait..\033[0m\n" );
#endif

	waitpid( -1, &stat_var, 0 );
	if ( WEXITSTATUS(stat_var) != 0 ) {
		is_fail = true;
#ifdef starter_DEBUG
		fprintf( stderr, "\033[2m\033[31m%s \033[0m\033[2mreturn: \033[36m%d\033[0m\n", "none", WEXITSTATUS(stat_var) );
#endif
		for ( uint8_t i = 0; i < progc; ++i ) {
			kill(pids[i], SIGKILL);
		}
	}

	for ( uint8_t i = 0; i < progc; ++i ) {
		waitpid( pids[i], &prog_s[i], 0 );
#ifdef starter_DEBUG
		if ( WEXITSTATUS(prog_s[i]) != 0 ) {
			is_fail = true;
			fprintf( stderr, "\033[2m\033[31m%s \033[0m\033[2mreturn: \033[36m%d\033[0m\n", progv[i], WEXITSTATUS(prog_s[i]) );
		} else {
			fprintf( stderr, "\033[2m\033[34m%s \033[0m\033[2mreturn: \033[36m%d\033[0m\n", progv[i], WEXITSTATUS(prog_s[i]) );
		}
#endif
    	}// getting proceses return values
	
	for ( uint8_t i = 0; i < progc; i++ ) {
		free(progv[i]);
	}
	free(progv);

	if (is_fail) {
		const char prog_name[16] = "program_starter\0";
		const char recipient_prog_name[12] = "err_manager\0";
		const char state[9] = "E-notify\0";
		const int return_code = WEXITSTATUS(stat_var);
		const char action[6] = "C-DEP\0";
		char buffer[255];

		encoder( prog_name, recipient_prog_name, state, return_code, action, buffer );
		ErrMemData test2;
		test2.err_semaphore = create_err_semaphore();
		printf("\033[2m\033[36mSemaphore is taken. Waiting for it to be dropped.\033[0m\n");
    		sem_wait(test2.err_semaphore);

		test2.shm = open_err_shm();
		write_shm( test2.shm, buffer );
		//delete_err();

		drop_semaphore( test2.err_semaphore );
        	printf("\033[2m\033[35merr semaphore are dropped.\033[0m\n");

		sem_close(test2.err_semaphore);
    		printf("\033[2m\033[36mclose err sem\033[0m\n");
	}

#ifdef starter_INFO
    	fprintf( stderr, "\033[3m\033[2mstarter stop.\033[0m\n" );
#endif
	return 0;
}

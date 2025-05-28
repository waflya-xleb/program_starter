#include "utils.h"


inline sem_t* create_task_semaphore() {
	sem_t *sem = sem_open(TASK_SEMAPHORE_NAME, O_CREAT, 0777, 0);
	return sem;
}
inline sem_t* create_msg_semaphore() {
	sem_t *sem = sem_open(MSG_SEMAPHORE_NAME, O_CREAT, 0777, 0);
	return sem;
}
inline sem_t* create_err_semaphore() {
	sem_t *sem = sem_open(ERR_SEMAPHORE_NAME, O_CREAT, 0777, 0);
	return sem;
}
inline sem_t* create_out_semaphore() {
	sem_t *sem = sem_open(OUT_SEMAPHORE_NAME, O_CREAT, 0777, 0);
	return sem;
}

inline void open_task_semaphore( sem_t *sem ) {
	sem = sem_open(TASK_SEMAPHORE_NAME, 0);
}
inline void open_msg_semaphore( sem_t *sem ) {
	sem = sem_open(MSG_SEMAPHORE_NAME, 0);
}
inline void open_err_semaphore( sem_t *sem ) {
	sem = sem_open(ERR_SEMAPHORE_NAME, 0);
}
inline void open_out_semaphore( sem_t *sem ) {
	sem = sem_open(OUT_SEMAPHORE_NAME, 0);
}

inline void drop_semaphore( sem_t *sem ) {
        sem_post( sem );
}


int open_task_shm() {
	int shm = 0;

	if ( (shm = shm_open(TASK_SHM_NAME, O_CREAT|O_RDWR, 0777)) == -1 ) {
		fprintf(stderr, "\033[31mtask shm open error.\033[0m\n");
		exit(1);
	}
	if ( ftruncate(shm, SHM_BASE_SIZE+1) == -1 ) {
		fprintf(stderr, "\033[31mftruncate error.\033[0m\n");
		exit(1);
	}
	fprintf(stderr, "\033[2m\033[32mtask memory open, shm = %d\033[0m\n", shm);
	return shm;
}
int open_msg_shm() {
	int shm = 0;

	if ( (shm = shm_open(MSG_SHM_NAME, O_CREAT|O_RDWR, 0777)) == -1 ) {
		fprintf(stderr, "\033[31mmsg shm open error.\033[0m\n");
		exit(1);
	}
	if ( ftruncate(shm, SHM_BASE_SIZE+1) == -1 ) {
		fprintf(stderr, "\033[31mftruncate error.\033[0m\n");
		exit(1);
	}
	fprintf(stderr, "\033[2m\033[32mmsg memory open, shm = %d\033[0m\n", shm);
	return shm;
}
int open_err_shm() {
	int shm = 0;

	if ( (shm = shm_open(ERR_SHM_NAME, O_CREAT|O_RDWR, 0777)) == -1 ) {
		fprintf(stderr, "\033[31merr shm open error.\033[0m\n");
		exit(1);
	}
	if ( ftruncate(shm, SHM_BASE_SIZE+1) == -1 ) {
		fprintf(stderr, "\033[31mftruncate error.\033[0m\n");
		exit(1);
	}
	fprintf(stderr, "\033[2m\033[32merr memory open, shm = %d\033[0m\n", shm);
	return shm;
}
int open_out_shm() {
	int shm = 0;

	if ( (shm = shm_open(OUT_SHM_NAME, O_CREAT|O_RDWR, 0777)) == -1 ) {
		fprintf(stderr, "\033[31mout shm open error.\033[0m\n");
		exit(1);
	}
	if ( ftruncate(shm, SHM_BASE_SIZE+1) == -1 ) {
		fprintf(stderr, "\033[31mftruncate error.\033[0m\n");
		exit(1);
	}
	fprintf(stderr, "\033[2m\033[32mout memory open, shm = %d\033[0m\n", shm);
	return shm;
}








void write_shm( const int shm, const char msg[] ) {
	int len = 0;

	len = strlen( msg );
	len = len<=SHM_BASE_SIZE ? len : SHM_BASE_SIZE;
	fprintf(stderr, "len = %d\n", len);

	char *addr = mmap(0, SHM_BASE_SIZE+1, PROT_WRITE|PROT_READ, MAP_SHARED, shm, 0);

	printf("Get from old shared memory: %s\n", addr);
	memcpy(addr, msg, len);
	if ( addr == (char*)-1 ) {
		fprintf(stderr, "\033[31maddr mmap error.");
		exit(1);
	}
	printf("\033[2m\033[33mshm memory writed.\033[0m\n");
	printf("Get from new shared memory: %s\n", addr);

	munmap(addr, SHM_BASE_SIZE);
	close(shm);
}

char* read_shm( const int shm, char *msg ) {
	char *addr = mmap(0, SHM_BASE_SIZE+1, PROT_READ, MAP_SHARED, shm, 0);

	msg = malloc( sizeof(char) * strlen(addr) );
	for ( uint16_t i = 0; i < strlen(addr); i++ ) {
		msg[i] = addr[i];
	}
	//printf("Get from old shared memory: %s\n", addr);
	munmap(addr, SHM_BASE_SIZE);
	close(shm);
	return msg;
}

void print_shm( const int shm ) {
	char *addr = mmap(0, SHM_BASE_SIZE+1, PROT_READ, MAP_SHARED, shm, 0);

	printf("Get from old shared memory: %s\n", addr);
	munmap(addr, SHM_BASE_SIZE);
	close(shm);
}


inline void delete_task() {
	shm_unlink(TASK_SHM_NAME);
	fprintf(stderr, "\033[2m\033[32mtask memory clean\033[0m\n");
}
inline void delete_msg() {
	shm_unlink(MSG_SHM_NAME);
	fprintf(stderr, "\033[2m\033[32mmsg memory clean\033[0m\n");
}
inline void delete_err() {
	shm_unlink(ERR_SHM_NAME);
	fprintf(stderr, "\033[2m\033[32merr memory clean\033[0m\n");
}
inline void delete_out() {
	shm_unlink(OUT_SHM_NAME);
	fprintf(stderr, "\033[2m\033[32mout memory clean\033[0m\n");
}

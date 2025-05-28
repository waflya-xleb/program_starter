#pragma once
#ifndef _STARTER_UTILS_C_
#define _STARTER_UTILS_C_

#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <unistd.h>
#include <stdint.h>

#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <fcntl.h>


#define TASK_SEMAPHORE_NAME "/task_semaphore"
#define MSG_SEMAPHORE_NAME "/msg_semaphore"
#define ERR_SEMAPHORE_NAME "/err_semaphore"
#define OUT_SEMAPHORE_NAME "/out_semaphore"

#define TASK_SHM_NAME "task_mem"
#define MSG_SHM_NAME "msg_mem"
#define ERR_SHM_NAME "err_mem"
#define OUT_SHM_NAME "out_mem"
#define SHM_BASE_SIZE 64

#define SHM_CREATE 1
#define SHM_PRINT  3
#define SHM_CLOSE  4


#define this_DEBUG



typedef struct TaskMemData {
	sem_t *task_semaphore;
	int shm;
	char *addr;
} TaskMemData;

typedef struct MsgMemData {
	sem_t *msg_semaphore;
	int shm;
	char *addr;
} MsgMemData;

typedef struct ErrMemData {
	sem_t *err_semaphore;
	int shm;
	char *addr;
} ErrMemData;

typedef struct OutMemData {
	sem_t *out_semaphore;
	int shm;
	char *addr;
} OutMemData;




sem_t* create_task_semaphore();
sem_t* create_msg_semaphore();
sem_t* create_err_semaphore();
sem_t* create_out_semaphore();

void open_task_semaphore( sem_t *sem );
void open_msg_semaphore( sem_t *sem );
void open_err_semaphore( sem_t *sem );
void open_out_semaphore( sem_t *sem );

void drop_semaphore( sem_t *sem );






int open_task_shm();
int open_msg_shm();
int open_err_shm();
int open_out_shm();

void write_shm( const int shm, const char msg[] );
char* read_shm( const int shm, char *addr );
void print_shm( const int shm );

void delete_task();
void delete_msg();
void delete_err();
void delete_out();

#endif

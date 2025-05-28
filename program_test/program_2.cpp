#include <stdio.h>
#include <stdbool.h>
#include <dlfcn.h>
#include <stdint.h>
#include <unistd.h>

#include "../theLib/theLib.hpp"
#include "../thetheLib/thetheLib.hpp"

//factory * myFactory;

int main( const uint16_t argc, const char *argv[] ) {
	fprintf(stderr, "it's second program\n");
	int pid = getpid();

	//void (*foo)(int a);
	void *ptr_the_variable;
	int a = 2;

	void *the_lib = dlopen("./libtheLib.so", RTLD_LAZY);
	void *thethe_lib = dlopen("./libthetheLib.so", RTLD_LAZY);

	if ( !the_lib ) {
		fprintf(stderr, "dlopen() error: %s\n", dlerror());
		FILE* err_f = fopen("err.txt", "w");
		const char str[17] = {'p', 'r', 'o', 'g', 'r', 'a', 'm', '_', '2', ' ', 'l', 'i', 'b', ' ', 'e', 'r', 'r'};
		if ( err_f == NULL ) {
			fprintf(stderr, "the file error!\n");
		}
		for ( uint8_t i = 0; i < 17; i++ ) {
			fputc(str[i], err_f);
		}
		fclose(err_f);
		return 2;
	}
	if ( !thethe_lib ) {
		fprintf(stderr, "dlopen() error: %s\n", dlerror());
		FILE* err_f = fopen("err.txt", "w");
		const char str[17] = {'p', 'r', 'o', 'g', 'r', 'a', 'm', '_', '2', ' ', 'l', 'i', 'b', ' ', 'e', 'r', 'r'};
		if ( err_f == NULL ) {
			fprintf(stderr, "the file error!\n");
		}
		for ( uint8_t i = 0; i < 17; i++ ) {
			fputc(str[i], err_f);
		}
		fclose(err_f);
		return 2;
	}

	for (int i = 0; i < 2500; i++) {
		if (i == 2000) {
			fprintf(stderr, "the program_2 work..\n");
		}
	}


	//*(void**)(&foo) = dlsym(the_lib, "foo");
	ptr_the_variable = dlsym(thethe_lib, "the_variable");
	int *the_variable = (int *) ptr_the_variable;

	fprintf(stderr, "the_variable = %d\n", *the_variable);
	//foo(a);

//--------------------------------------------



    	factory * myFactory = (factory *)dlsym(thethe_lib, "Factory");

    	if ( !myFactory ) {  std::cout << "the error\n";  return -1;  }

	parent_class * the_class = myFactory->makedyn();
    	the_class->test(2);
    	delete the_class;


//--------------------------------------------


	dlclose(the_lib);
	dlclose(thethe_lib);
	return 0;
}

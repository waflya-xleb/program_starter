#include "theLib.hpp"

void foo( const int a ) {
	//std::cout << "123 the lib foo() : " << a << "\n";
	printf("the lib foo()\n");
}

int super_foo_2_9( const int x, const int y, const char msg[], const bool super_flag ) {
	fprintf(stderr, "super_foo_2_9() : x=%d,y=%d,msg=%s,super_flag=%d", x, y, msg[0], super_flag);
	return x+y;
}

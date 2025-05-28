#include "thetheLib.hpp"

void thethefoo() {
	printf("thetheLib thethefoo()\n");
}


class the_class : public parent_class {
    public:
        the_class()  {
		std::cerr << "    the_class::the_class()\n";
	};

        ~the_class() {
		std::cerr << "    the_class::~foo()\n";
	};

        virtual void test( int x ) {
		std::cout << "    the_class::test()\n";
	};
};


class foofactory : factory {
    public:
        the_class * makedyn() {
		std::cerr << "    foofactory::makedyn()\n";
		return new the_class; 
	}
};

foofactory Factory;

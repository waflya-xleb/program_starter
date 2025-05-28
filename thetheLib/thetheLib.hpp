#pragma once
#ifndef THETHE_LIB_CPP
#define THETHE_LIB_CPP

#include <iostream>
#include <stdio.h>

void thethefoo();

int the_variable = 43;

class parent_class
{
    public:
        // default constructor
        virtual void test( int x ) { };
        virtual ~parent_class() {};
};

class factory
{
    public:
        virtual parent_class * makedyn() { };
};

#endif

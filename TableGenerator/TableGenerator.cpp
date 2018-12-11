// TableGenerator.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"

#include <iostream>
#include <math.h>

int main()
{
	for (int i = 0; i < 1024; i++) {
		std::cout << (int)(256 * sin(6.28 * i / 2047.0f)) << ", ";
		if (i % 32 == 0)
			std::cout << std::endl;
	}
    return 0;
}


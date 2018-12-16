// TableGenerator.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"

#include <iostream>
#include <math.h>
#include <minmax.h>

int main()
{
	std::cout << "Sine" << std::endl;
	for (int i = 0; i < 1024; i++) {
		std::cout << (int)(256 * sin(6.28 * i / 2047.0f)) << ", ";
		if (i % 32 == 0)
			std::cout << std::endl;
	}

	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "Triangle" << std::endl;
	for (int i = 0; i < 1024; i++) {
		std::cout << (int)(255 * (1.0 - abs(512.0 - i) / 512)) << ", ";
		if (i % 32 == 0)
			std::cout << std::endl;
	}

	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "Flicker" << std::endl;
	for (int i = 0; i < 1024; i++) {
		std::cout << (int)(255.0 * rand() / RAND_MAX) << ", ";
		if (i % 32 == 0)
			std::cout << std::endl;
	}

	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "Linear" << std::endl;
	for (int i = 0; i < 1024; i++) {
		std::cout << i / 4 << ", ";
		if (i % 32 == 0)
			std::cout << std::endl;
	}

	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "Eye Correction" << std::endl;
	std::cout << "0, ";
	for (int i = 1; i < 256; i++) {
		std::cout << max(1, (int)(pow(2.0, 8.0 * (i + 1) / 256)) - 1) << ", ";
		if (i % 32 == 0)
			std::cout << std::endl;
	}

	return 0;
}


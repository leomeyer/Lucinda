// TableGenerator.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"

#include <iostream>
#include <math.h>
#include <minmax.h>

#define WAVETABLE_LENGTH		1024
#define RESOLUTION_BITS			10
#define RESOLUTION_MAX			(1 << RESOLUTION_BITS)
#define RESOLUTION_MAX_FLOAT	(RESOLUTION_MAX * 1.0f)

int main()
{
	std::cout << "Sine" << std::endl;
	for (int i = 0; i < WAVETABLE_LENGTH; i++) {
		std::cout << (int)(RESOLUTION_MAX * sin(6.28 * i / (WAVETABLE_LENGTH * 2 - 1.0f))) << (i < WAVETABLE_LENGTH - 1 ? ", " : "");
		if ((i > 0) && i % 32 == 0)
			std::cout << std::endl;
	}

	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "Triangle" << std::endl;
	for (int i = 0; i < WAVETABLE_LENGTH; i++) {
		std::cout << (int)((RESOLUTION_MAX - 1) * (1.0 - abs(1.0f *(WAVETABLE_LENGTH / 2 - i) / (WAVETABLE_LENGTH / 2)))) << (i < WAVETABLE_LENGTH - 1 ? ", " : "");
		if ((i > 0) && i % 32 == 0)
			std::cout << std::endl;
	}

	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "Flicker" << std::endl;
	for (int i = 0; i < WAVETABLE_LENGTH; i++) {
		std::cout << (int)((RESOLUTION_MAX_FLOAT - 1) * rand() / RAND_MAX) << (i < WAVETABLE_LENGTH - 1 ? ", " : "");
		if ((i > 0) && i % 32 == 0)
			std::cout << std::endl;
	}

	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "Linear" << std::endl;
	for (int i = 0; i < WAVETABLE_LENGTH; i++) {
		std::cout << i / (RESOLUTION_MAX / WAVETABLE_LENGTH) << (i < WAVETABLE_LENGTH - 1 ? ", " : "");
		if ((i > 0) && i % 32 == 0)
			std::cout << std::endl;
	}

	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "Eye Correction" << std::endl;
	std::cout << "0, ";
	for (int i = 1; i < RESOLUTION_MAX; i++) {
		std::cout << max(1, (int)(pow(2.0, 1.0f * RESOLUTION_BITS * (i + 1) / RESOLUTION_MAX)) - 1) << (i < WAVETABLE_LENGTH - 1 ? ", " : "");
		if ((i > 0) && i % 32 == 0)
			std::cout << std::endl;
	}

	return 0;
}


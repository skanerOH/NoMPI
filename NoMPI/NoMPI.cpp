#include "pch.h"
#include <chrono>
#include <iostream>
#include <cmath>

inline double F(double x)
{
	return cos(sin(x*x) - x * x*x + x * x*x*x / 47 - 54 * cos(pow(x, -1.5)));
}

int main()
{
	auto start_time = std::chrono::high_resolution_clock::now();

	const double begin = 1;
	const double end = 200;
	const long int values_count = 1000001;

	double* web = new double[values_count];
	web[0] = begin;
	for (int i = 1; i < values_count - 1; ++i)
		web[i] = begin + ((end - begin) / (values_count - 1))*i;
	web[values_count - 1] = end;

	double res = 0;
	double a, b;
	for (long int i = 0; i < (values_count-1); ++i)
	{
		a = web[i];
		b = web[i + 1];
		res += (b - a)*(F((a + b) / 2.0 - (b - a) / (2 * sqrt(3))) + F((a + b) / 2.0 + (b - a) / (2 * sqrt(3)))) / 2;
	}

	delete[] web;

	auto stop_time = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop_time - start_time);

	printf("Integral = %f\n", res);
	std::cout << "Time spent: " << duration.count() << std::endl;
}

#include "Deflnt_header.h"
#include <iostream>
#include <cmath>
using namespace std;


Deflnt::Deflnt(double aa, double bb, double(*function)(double x)) {
	a = aa;
	b = bb;
	f = function;
}

Deflnt::Deflnt(const Deflnt& d)
{
	a = d.a;
	b = d.b;
	f = d.f;
}


double Deflnt::ByTrapzoid(int N) {
	double h = (b - a) / N;
	double sum = f(a);
	for (int k = 1; k < N; k++) {
		sum += 2 * f(a + h * k);
	}
	sum += f(b);
	return ((b - a) * sum) / (2 * N);

}



double Deflnt::BySimpson() {
	return (b - a) * (f(a) + 4 * f((a + b) / 2) + f(b)) / 6;
}




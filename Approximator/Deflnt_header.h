#pragma once

class Deflnt {
	private:
		double a;
		double b;
		double (*f) (double x);

	public:
		Deflnt();
		Deflnt(const Deflnt& d);
		Deflnt(double aa, double bb, double (*function)(double x));
		double ByTrapzoid(int N);
		double BySimpson();

};


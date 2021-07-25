#include<iostream>
#include<cmath>
#include<math.h>
#include<string.h>
#include "gnuplot.h"

#define double long double

const double G = 9.81;

double m;  
double r,u,per;  

void define_variables(gnuplot &p) {
	p("m="+to_string(m));
	p("r=" + to_string(r));
	p("u=" + to_string(u));
	p("g=" + to_string(G));
	p("per=" + to_string(per));
}
void v_t(gnuplot &p) {
	//setting range
	p("set xrange [0:(m*per/(100*r))]");

	//plot v1 and v2
	p("v1(t)=u*log(m/(m-r*t))");
	p("v2(t)=u*log(m/(m-r*t))-g*t");
	p("der(t)=(m*g-r*u)/(r*g)");
	p("vv2(t)=(0<=t&&t<der(t)) ? 0 : v2(t)-v2(der(t))");
	p("v1_r(t)=(0<=t && t<=m*per/(100*r)) ? v1(t) : 1/0");
	p("v2_r(t)=(0<=t && t<=m*per/(100*r)) ? (der(t)>=0 ? vv2(t) : v2(t)) : 1/0");
	p("plot v1_r(x) title 'v(t) without g',v2_r(x) title 'v(t) with const g'"); 
}
void v_m(gnuplot &p) {
	//setting range
	p("set xrange [m*(100-per)/100:m]");

	//plot v1 and v2
	p("v_m1(x)=u*log(m/(m-r*((m-x)/r)))");
	p("v_m2(x)=u*log(m/(m-r*((m-x)/r)))-g*((m-x)/r)");
	p("der(x)=u*r/g");
	p("vv_m2(x)=(der(x)<x&&x<=m) ? 0 : v_m2(x)-v_m2(der(x))");
	p("v_m1_r(x)=(m*(100-per)/100<=x && x<=m) ? v_m1(x) : 1/0");
	p("v_m2_r(x)=(m*(100-per)/100<=x && x<=m) ? (der(x)<=m ? vv_m2(x) : v_m2(x)) : 1/0");
	p("plot v_m1_r(x) title 'v(m) without g',v_m2_r(x) title 'v(m) with const g'");
}
void a_r(gnuplot &p) {
	p("set xrange [0:10000]");

	//plot a1 and a2
	p("a1(r)=r>=0 ? ((u*r/m) >=0 ? (u*r/m) : 0) : 1/0");
	p("a2(r)=r>=0 ? ((u*r/m-g) >=0 ? (u*r/m-g) : 0) : 1/0");
	p("plot a1(x) title 'a(r) without g',a2(x) title 'a(r) with const g'");
}
/*double f(double t) {
	return u * log(m / (m - r * t));
}
double Integral(double a, double b) {
	double area = 0.0;
	double E = 1e-3;
	double length = (double)(b - a) / 2;
	long long ile = 2;
	double P1 = 0;
	double P2 = f(a)*length + f(a + length)*length;
	//double P2 = pol.func(a)*length+pol.func(a+length)*length;
	while (abs(P1 - P2) > E) {
		std::cout << P1 << " " << P2 <<" "<<E<< "\n";
		P2 = P1;
		P1 = 0;
		length /= 2;
		ile *= 2;
		for (int i = 0; i < ile; i++) {
			P1 += f(a + length * i)*length;
			//P1 += pol.func(a+length*i)*length;
		}
	}
	return P1;
}*/
int main() {
	std::cout.precision(15);

	std::cout << "Podaj mase poczatkowa rakiety(kg): "; std::cin >> m;
	std::cout << "Podaj ilosc paliwa w rakiecie(1% - 99%): "; std::cin >> per;
	std::cout << "Podaj szybkosc wyrzutu paliwa: "; std::cin >> r;
	std::cout << "Podaj predkosc wyrzucanego paliwa: "; std::cin >> u; std::cout << "\n";

	gnuplot pg, rg, qg;

	//variables
	define_variables(pg);
	define_variables(rg);
	define_variables(qg);
	//v(t) and const G
	v_t(pg);
	//v_m(t) and const G
	v_m(rg);
	//a(r)
	a_r(qg);

	//std::cout << Integral(0, m*per / (100 * r)) << "\n";

	return 0;
}
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
	p("plot v1(x),v2(x)"); 
}
void v_m(gnuplot &p) {
	//setting range
	p("set xrange [m*(100-per)/100:m]");

	//plot v1 and v2
	p("v_m1(x)=u*log(m/(m-r*((m-x)/r)))");
	p("v_m2(x)=u*log(m/(m-r*((m-x)/r)))-g*((m-x)/r)");
	p("plot v_m1(x),v_m2(x)");
}
void a_r(gnuplot &p) {
	p("set xrange [0:2000]");

	//plot a1 and a2
	p("a1(r)=u*r/m");
	p("a2(r)=u*r/m-g");
	p("plot a1(x),a2(x)");
}
int main() {
	std::cout.precision(15);

	std::cout << "Podaj mase poczatkowa rakiety(kg): "; std::cin >> m;
	std::cout << "Podaj ilosc paliwa w rakiecie(1% - 99%): "; std::cin >> per;
	std::cout << "Podaj szybkosc wyrzutu paliwa: "; std::cin >> r;
	std::cout << "Podaj predkosc wyrzucanego paliwa: "; std::cin >> u; std::cout << "\n";

	gnuplot p, r, q;

	//variables
	define_variables(p);
	define_variables(r);
	define_variables(q);
	//v(t) and const G
	v_t(p);
	//v_m(t) and const G
	v_m(r);
	//a(r)
	a_r(q);

	for (int i = 0; i < 1000; i++) {
		//std::cout <<i<<" : "<< u * i / m - G<<"\n";
	}

	return 0;
}
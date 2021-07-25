#include<iostream>
#include<cmath>
#include<math.h>
#include<string.h>
#include "gnuplot.h"

#define double long double

const double g = 9.81;
const double G = 6.6743015151e-11;
//normal M = 5.9736*1e24
const double M = 5.9736*1e24;
const double Rz = 6373140;
double m;  
double r,u,per;  

void define_variables(gnuplot &p) {
	p("m="+to_string(m));
	p("r=" + to_string(r));
	p("u=" + to_string(u));
	p("g=" + to_string(g));
	p("G=" + to_string(G));
	p("M=" + to_string(M));
	p("Rz=" + to_string(Rz));
	p("per=" + to_string(per));
}
void v_t(gnuplot &p) {
	//setting range
	p("set xrange [0:(m*per/(100*r))]");

	//v1 and v2
	p("v1(t)=u*log(m/(m-r*t))");
	p("v2(t)=u*log(m/(m-r*t))-g*t");
	//derivative of v2
	p("der(t)=(m*g-r*u)/(r*g)");
	//moved v2 from der(t) of const
	p("vv2(t)=(0<=t && t<der(t)) ? 0 : v2(t)-v2(der(t))");
	//v1 and v2 in range
	p("v1_r(t)=(0<=t && t<=m*per/(100*r)) ? v1(t) : 1/0");
	p("v2_r(t)=(0<=t && t<=m*per/(100*r)) ? (der(t)>=0 ? vv2(t) : v2(t)) : 1/0");
	
	//g
	p("integral(t)=u*(m-r*t)*log(abs(r*t-m))/r - g*t**2/2 + u*log(m)*t + u*t - u*m*log(m)/r");
	//too big numbers
	p("g(t)=(G*M/(integral(t)+Rz)**2)");
	//v3
	p("v3(t)=u*log(m/(m-r*t))-g(t)*t");
	//v3 in range
	p("v3_r(t)=(0<=t && t<=m*per/(100*r)) ? v3(t) : 1/0");
	//plot v1, v2 and v3
		
	p("plot g(x),v1_r(x) title 'v(t) without g',v2_r(x) title 'v(t) with const g',v3_r(x) title 'v(t) with accurate g'"); 
}
void v_m(gnuplot &p) {
	//setting range
	p("set xrange [m*(100-per)/100:m]");

	//v1_m and v2_m
	p("v_m1(x)=u*log(m/(m-r*((m-x)/r)))");
	p("v_m2(x)=u*log(m/(m-r*((m-x)/r))) - g*((m-x)/r)");
	//derivative of v_m2
	p("der(x)=u*r/g");
	//moved v_m2 from der(x) of const
	p("vv_m2(x)=(der(x)<x && x<=m) ? 0 : v_m2(x) - v_m2(der(x))");
	//v_m1 and v_m2 in range
	p("v_m1_r(x)=(m*(100-per)/100<=x && x<=m) ? v_m1(x) : 1/0");
	p("v_m2_r(x)=(m*(100-per)/100<=x && x<=m) ? (der(x)<=m ? vv_m2(x) : v_m2(x)) : 1/0");
	//plot v_m1 and v_m2
	p("plot v_m1_r(x) title 'v(m) without g',v_m2_r(x) title 'v(m) with const g'");
}
void a_r(gnuplot &p) {
	//setting xrange
	p("set xrange [0:10000]");

	//a1 and a2 in range
	p("a1(r)=r>=0 ? ((u*r/m) >=0 ? (u*r/m) : 0) : 1/0");
	p("a2(r)=r>=0 ? ((u*r/m-g) >=0 ? (u*r/m-g) : 0) : 1/0");
	//plot a1 and a2
	p("plot a1(x) title 'a(r) without g',a2(x) title 'a(r) with const g'");
}
void s_t(gnuplot &p) {
	//setting xrange
	p("set xrange [0:(m*per/(100*r))]");
	//s1 and a2
	p("s1(t)=(-u*(r*t-m)*(log(abs(r*t-m))-log(m)-1)+u*m)/r");
	p("s2(t)=u*(m-r*t)*log(abs(r*t-m))/r - g*t**2/2 + u*log(m)*t + u*t - u*m*log(m)/r");
	//s1 and s2 in range
	p("s1_r(t)=(0<=t && t<=m*per/(100*r)) ? s1(t) : 1/0");
	p("s2_r(t)=(0<=t && t<=m*per/(100*r)) ? s2(t) : 1/0");
	//plot s1 and s2
	p("plot s1_r(x) title 's(t) without g',s2_r(x) title 's(t) with const g'");
}
int main() {
	std::cout.precision(15);

	std::cout << "Podaj mase poczatkowa rakiety(kg): "; std::cin >> m;
	std::cout << "Podaj ilosc paliwa w rakiecie(1% - 99%): "; std::cin >> per;
	std::cout << "Podaj szybkosc wyrzutu paliwa: "; std::cin >> r;
	std::cout << "Podaj predkosc wyrzucanego paliwa: "; std::cin >> u; std::cout << "\n";

	gnuplot pg, rg, qg, sg;

	//variables
	define_variables(pg);
	define_variables(rg);
	define_variables(qg);
	define_variables(sg);
	//v(t)
	v_t(pg);
	//v_m(t)
	//v_m(rg);
	//a(r) 
	//a_r(qg);
	//s(t)
	s_t(sg);

	return 0;
}
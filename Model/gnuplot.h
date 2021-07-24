#pragma once
//GNUPLOT 5.2.0
#include<iostream>
#include<string>

using namespace std;

class gnuplot {
public:
	gnuplot();
	~gnuplot();
	void operator () (const string & command);
protected:
	FILE *gnuplotpipe;
};
gnuplot::gnuplot() {
	gnuplotpipe = _popen("gnuplot -persist", "w");
	if (!gnuplotpipe)
		cerr << ("Gnuplot not found!");
}
gnuplot::~gnuplot() {
	fprintf(gnuplotpipe, "exit\n");
	_pclose(gnuplotpipe);
}
void gnuplot::operator()(const string & command) {
	fprintf(gnuplotpipe, "%s\n%", command.c_str());
	fflush(gnuplotpipe);
}

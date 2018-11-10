#include "TimeStamp.h"
#include <iostream>
using namespace std;

TimeStamp::TimeStamp(int h, int m, int s, int ms) {
    if ((h < 0) || (h > 10) || (m < 0) || (m > 59) || (s < 0) || (s > 59) || (ms < 0) || (ms > 999)) throw GreskaVreme();
	this->h = h; this->m = m; this->s = s; this->ms = ms;
}

bool TimeStamp::operator<(const TimeStamp& ts) {
	if (this->vreme() < ts.vreme()) return true;
	else return false;
}

bool TimeStamp::operator>(const TimeStamp& ts) {
	if (this->vreme() > ts.vreme()) return true;
	else return false;
}

bool TimeStamp::operator>=(const TimeStamp& ts) {
	if (this->vreme() >= ts.vreme()) return true;
	else return false;
}

bool TimeStamp::operator<=(const TimeStamp& ts) {
	if (this->vreme() <= ts.vreme()) return true;
	else return false;
}

TimeStamp* TimeStamp::dodajVreme(double vreme) {
	vreme = this->vreme() + vreme;
    if (vreme < 39600) {
        this->ms = (int)((vreme - floor(vreme)) * 1000);
        vreme = floor(vreme);
        this->h = (int)vreme / 3600;
        vreme -= this->h * 3600;
        this->m = (int)vreme / 60;
        vreme -= this->m * 60;
        this->s = (int)vreme;
    }
    else {
        this->ms = 999;
        this->h = 9;
        this->m = 59;
        this->s = 59;
    }
	return this;
}

TimeStamp* TimeStamp::oduzmiVreme(double vreme) {
	vreme = this->vreme() - vreme;
	if (vreme > 0) {
		this->ms = (int)((vreme - floor(vreme)) * 1000);
		vreme = floor(vreme);
		this->h = (int)vreme / 3600;
		vreme -= this->h * 3600;
		this->m = (int)vreme / 60;
		vreme -= this->m * 60;
		this->s = (int)vreme;
	}
	else {
		this->ms = 0;
		this->h = 0;
		this->m = 0;
		this->s = 0;
	}
	return this;
}

double TimeStamp::vreme() const { 
	double t = h * 3600 + m * 60 + s + (double)ms / 1000; 
	return t + 0.0001; 
}

long long int TimeStamp::hashKey() const { 
	double t = h * 3600 + m * 60 + s + (double)ms / 1000; 
	return (long long int)(t*10000); 
}

int TimeStamp::geth() const { return h; }

int TimeStamp::getm() const { return m; }

int TimeStamp::gets() const { return s; }

int TimeStamp::getms() const { return ms; }

ostream& operator<<(ostream& os, const TimeStamp& ts) {
	os << setfill('0') << setw(2) << ts.geth();
	os << ":";
	os << setfill('0') << setw(2) << ts.getm();
	os << ":";
	os << setfill('0') << setw(2) << ts.gets();
	os << ",";
	os << setfill('0') << setw(3) << ts.getms();
	return os;
}

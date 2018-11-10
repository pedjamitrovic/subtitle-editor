#ifndef _TIMESTAMP_H_
#define _TIMESTAMP_H_
#include <iomanip>
#include <exception>
#include <QString>
using namespace std;

class GreskaVreme : public exception {
public:
	virtual const char* what() const override { return "Greska prilikom zadavanja vremena titla."; }
	friend ostream& operator<<(ostream& os, const GreskaVreme& gv) {
		return os << gv.what();
	}
};

class TimeStamp {
private:
	int h, m, s, ms;
public:
	TimeStamp(int h, int m, int s, int ms);
	virtual ~TimeStamp(){}
	bool operator <(const TimeStamp& ts);
	bool operator >(const TimeStamp& ts);
	bool operator>=(const TimeStamp& ts);
	bool operator<=(const TimeStamp& ts);
	TimeStamp* dodajVreme(double vreme);
	TimeStamp* oduzmiVreme(double vreme);
	double vreme() const;
	long long int hashKey() const;
	int geth() const;
	int getm() const;
	int gets() const;
    int getms() const;
	friend ostream& operator<<(ostream& os, const TimeStamp& ts);
};


#endif // !_TIMESTAMP_H_

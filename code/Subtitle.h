#ifndef _SUBTITLE_H_
#define _SUBTITLE_H_
#include "TimeStamp.h"
#include <string>

class Subtitle {
private:
	TimeStamp *pocetak, *kraj;
	string text;
	double trajanje;
public:
	Subtitle(TimeStamp* poc, TimeStamp* kra, string t_t);
    virtual ~Subtitle();
	TimeStamp* dohPocetak() const;
	TimeStamp* dohKraj() const;
	bool setPocetak(TimeStamp* newbeg);
	bool setKraj(TimeStamp* newend);
	const string& dohTekst() const;
	string& dohTekst();
	bool setTekst(const string& _text);
	double dohTrajanje() const;
	friend ostream& operator<<(ostream& os, const Subtitle& s);
};



#endif // !_SUBTITLE_H_

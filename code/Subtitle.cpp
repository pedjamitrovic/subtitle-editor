#include "Subtitle.h"

Subtitle::Subtitle(TimeStamp* poc, TimeStamp* kra, string t_t) {
	pocetak = poc;
	kraj = kra;
	trajanje = kraj->vreme() - pocetak->vreme();
	text = t_t;
}

Subtitle::~Subtitle() {if(pocetak!=nullptr) delete pocetak; if(kraj!=nullptr) delete kraj;}

TimeStamp* Subtitle::dohPocetak() const { return pocetak; }

bool Subtitle::setPocetak(TimeStamp* newbeg) { 
    if(pocetak!=nullptr) delete pocetak;
	trajanje = kraj->vreme() - newbeg->vreme();
	if (trajanje < 0) return false;
	pocetak = newbeg; 
	return true; 
}

TimeStamp* Subtitle::dohKraj() const { return kraj; }

bool Subtitle::setKraj(TimeStamp* newend) { 
    if(kraj!=nullptr) delete kraj;
	trajanje = newend->vreme() - pocetak->vreme();
    kraj = newend;
	return true;
}

const string& Subtitle::dohTekst() const { return text; }

string& Subtitle::dohTekst() { return text; }

bool Subtitle::setTekst(const string& _text) {
	text = _text;
	return true;
}

double Subtitle::dohTrajanje() const { return trajanje; }

ostream& operator<<(ostream& os, const Subtitle& s) {
    os << *s.dohPocetak() << " - " << *s.dohKraj() << " - " << endl;//s.dohTrajanje() << endl;
    os << "XD";
	os << s.dohTekst();
	return os;
}

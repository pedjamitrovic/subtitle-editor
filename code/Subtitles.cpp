#include "Subtitles.h"

Subtitles::~Subtitles() { mapa.clear(); }

const map<long long int, Subtitle*>& Subtitles::getMap() const {
	return mapa;
}
map<long long int, Subtitle*>& Subtitles::getMap() {
	return mapa;
}

bool Subtitles::add(long long int key, Subtitle* title) {
	if (!mapa.insert(make_pair(key, title)).second) return false;
	return true;
}

bool Subtitles::erase(long long int key) {
	if (!mapa.erase(key)) return false;
	return true;
}

size_t Subtitles::numberOfSubtitles() { return mapa.size(); }

ostream& operator<<(ostream& os, const Subtitles& s) {
	for (map<long long int, Subtitle*>::const_iterator it = s.getMap().cbegin(); it != s.getMap().cend(); ++it) {
        os << (*(*it).second) << endl;
	}
	return os;
}

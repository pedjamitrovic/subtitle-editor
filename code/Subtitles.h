#ifndef _SUBTITLES_H_
#define _SUBTITLES_H_
#include <list>
#include <map>
#include "Subtitle.h"

class Subtitles {
private:
	map<long long int, Subtitle*> mapa;
public:
	virtual ~Subtitles();
	const map<long long int, Subtitle*>& getMap() const;
	map<long long int, Subtitle*>& getMap();
	bool add(long long int key, Subtitle* title);
	bool erase(long long int key);
    size_t numberOfSubtitles();
	friend ostream& operator<<(ostream& os, const Subtitles& s);
};



#endif // !_SUBTITLES_H_

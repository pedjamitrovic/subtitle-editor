#include "SubtitleProcessing.h"
#include <iostream>

#define MAX_TIME 40000
#define MIN_TIME 0

SubtitleProcessing::SubtitleProcessing(Subtitles* _titles) { titles = _titles; }

SubtitleProcessing::~SubtitleProcessing() { titles = nullptr; }

Subtitles* SubtitleProcessing::getTitles(){
    return titles;
}

bool SubtitleProcessing::addOneTitle(long long int key, Subtitle* newsub) { 
	if (!titles->add(key, newsub)) return false; 
	return true; 
}

bool SubtitleProcessing::deleteOneTitle(long long int key) {
	if (!titles->erase(key)) return false;
	return true;
}

Subtitle* SubtitleProcessing::getExactTitle(long long int key) {
	return titles->getMap()[key];
}

double SubtitleProcessing::getAppearingTime(long long int key) {
	return titles->getMap()[key]->dohTrajanje();
}

bool SubtitleProcessing::setBegTime(long long int key, TimeStamp* newbeg) {
	Subtitle* temp = getExactTitle(key);
	if (!temp->setPocetak(newbeg)) return false;
	addOneTitle(newbeg->hashKey(), temp);
	deleteOneTitle(key);
	return true;
}

bool SubtitleProcessing::setEndTime(long long int key, TimeStamp* newend) {
	if (!titles->getMap()[key]->setKraj(newend)) return false;
	return true;
}

bool SubtitleProcessing::setText(long long int key, const string& text) {
	if (!titles->getMap()[key]->setTekst(text)) return false;
	return true;
}

bool SubtitleProcessing::checkAllTimes() {
    size_t i = 1;
	bool ok = true;
	for (map<long long int, Subtitle*>::const_iterator it = titles->getMap().cbegin(); it != titles->getMap().cend(); ++it, ++i) {
		if (it->second->dohTrajanje() <= 0) std::cout << i << " ", ok = false;
	}
	cout << endl;
	i = 1;
	for (map<long long int, Subtitle*>::const_iterator it1 = titles->getMap().cbegin(); i < titles->getMap().size() ; ++it1, ++i) {
		map<long long int, Subtitle*>::const_iterator it2 = it1;
		++it2;
		if(*(it1->second->dohKraj()) > *(it2->second->dohPocetak())) std::cout << i-1 << ", " << i << "\n", ok = false;
	}
    return ok;
}

int SubtitleProcessing::mergeEveryTwo(double time_space, size_t char_number) {
    int counter = 0;
    size_t i = 1;
    for (map<long long int, Subtitle*>::const_iterator it1 = titles->getMap().cbegin(); i < titles->getMap().size(); ++it1, i++) {
        map<long long int, Subtitle*>::const_iterator it2 = it1;
		++it2;
		if ((it2->second->dohPocetak()->vreme() - it1->second->dohKraj()->vreme()) < time_space)
			if ((it2->second->dohTekst().size() + it1->second->dohTekst().size()) < char_number) {
                it1->second->setKraj(it2->second->dohKraj());
                it1->second->dohTekst().append(it2->second->dohTekst());
                deleteOneTitle(it2->second->dohPocetak()->hashKey());
                counter++;
			}
	}
    return counter;
}

bool SubtitleProcessing::mergeTwo(Subtitle* first, Subtitle* second, double time_space, size_t char_number) {
        if ((second->dohPocetak()->vreme() - first->dohKraj()->vreme()) <= time_space)
            if ((second->dohTekst().size() + first->dohTekst().size()) < char_number) {
                first->setKraj(second->dohKraj());
                first->dohTekst().append(second->dohTekst());
                deleteOneTitle(second->dohPocetak()->hashKey());
				return true;
			}
		return false;
}

int SubtitleProcessing::splitEveryToMore(double time_duration, size_t char_number, size_t split_count) {
    int counter = 0;
    for (map<long long int, Subtitle*>::const_iterator it = titles->getMap().cbegin(); it != titles->getMap().cend(); ++it){
            map<long long int, Subtitle*>::const_iterator it_temp = it;
            ++it_temp;
            if (splitToMore(it->second, time_duration, char_number, split_count)) counter++;
            it = it_temp;
    }
    return counter;
}

bool SubtitleProcessing::splitToMore(Subtitle* sub, double time_duration, size_t char_number, size_t split_count) {
    if (split_count > sub->dohTekst().size()) return false;
	double trajanje = sub->dohTrajanje() / split_count;
	long long int hashKey = sub->dohPocetak()->hashKey();
	if (sub->dohTrajanje() > time_duration)
        if (sub->dohTekst().size() > char_number) {
			TimeStamp* pocetak = sub->dohPocetak();
            titles->erase(hashKey);
            for (size_t i = 0, char_count = 0; i < split_count; i++) {
				string tekst;
                if (i < split_count - 1) tekst = sub->dohTekst().substr(char_count, sub->dohTekst().size() / split_count);
                else tekst = sub->dohTekst().substr(char_count);
                if (i!=0) pocetak->dodajVreme(0.001);
                TimeStamp* novipocetak = new TimeStamp(pocetak->geth(), pocetak->getm(), pocetak->gets(), pocetak->getms());
				pocetak->dodajVreme(trajanje);
				TimeStamp* novikraj = new TimeStamp(pocetak->geth(), pocetak->getm(), pocetak->gets(), pocetak->getms());
                Subtitle* novi = new Subtitle(novipocetak, novikraj, tekst);
                titles->add(novipocetak->hashKey(), novi);
				char_count = char_count + sub->dohTekst().size() / split_count;
            }
			return true;
		}
	return false;
}

int SubtitleProcessing::moveAllTimes(double time_duration) {
    int counter = 0;
    if (time_duration == 0) return (int)titles->numberOfSubtitles();
    if (time_duration > 0) {
        map<long long int, Subtitle*>::const_iterator it = titles->getMap().cend();
        --it;
        while (it != titles->getMap().cbegin()) {
            map<long long int, Subtitle*>::const_iterator it_temp = it;
            --it_temp;
            long long int stariKey = it->second->dohPocetak()->hashKey();
            it->second->dohPocetak()->dodajVreme(time_duration);
            it->second->dohKraj()->dodajVreme(time_duration);
            TimeStamp* novipocetak = new TimeStamp(it->second->dohPocetak()->geth(), it->second->dohPocetak()->getm(), it->second->dohPocetak()->gets(), it->second->dohPocetak()->getms());
            TimeStamp* novikraj = new TimeStamp(it->second->dohKraj()->geth(), it->second->dohKraj()->getm(), it->second->dohKraj()->gets(), it->second->dohKraj()->getms());
            string text = it->second->dohTekst();
            Subtitle* novi = new Subtitle(novipocetak, novikraj, text);
            deleteOneTitle(stariKey);
            while(!addOneTitle(novipocetak->hashKey(), novi)) { novipocetak->oduzmiVreme(0.001); novikraj->oduzmiVreme(0.001); }
            counter++;
            it = it_temp;
        }
        long long int stariKey = it->second->dohPocetak()->hashKey();
        it->second->dohPocetak()->dodajVreme(time_duration);
        it->second->dohKraj()->dodajVreme(time_duration);
        TimeStamp* novipocetak = new TimeStamp(it->second->dohPocetak()->geth(), it->second->dohPocetak()->getm(), it->second->dohPocetak()->gets(), it->second->dohPocetak()->getms());
        TimeStamp* novikraj = new TimeStamp(it->second->dohKraj()->geth(), it->second->dohKraj()->getm(), it->second->dohKraj()->gets(), it->second->dohKraj()->getms());
        string text = it->second->dohTekst();
        Subtitle* novi = new Subtitle(novipocetak, novikraj, text);
        deleteOneTitle(stariKey);
        while(!addOneTitle(novipocetak->hashKey(), novi)) { novipocetak->oduzmiVreme(0.001); novikraj->oduzmiVreme(0.001); }
        counter++;
    }
    if (time_duration < 0) {
        map<long long int, Subtitle*>::const_iterator it = titles->getMap().cbegin();
        time_duration = -time_duration;
        while (it != titles->getMap().cend()) {
            map<long long int, Subtitle*>::const_iterator it_temp = it;
            ++it_temp;
            long long int stariKey = it->second->dohPocetak()->hashKey();
            it->second->dohPocetak()->oduzmiVreme(time_duration);
            it->second->dohKraj()->oduzmiVreme(time_duration);
            TimeStamp* novipocetak = new TimeStamp(it->second->dohPocetak()->geth(), it->second->dohPocetak()->getm(), it->second->dohPocetak()->gets(), it->second->dohPocetak()->getms());
            TimeStamp* novikraj = new TimeStamp(it->second->dohKraj()->geth(), it->second->dohKraj()->getm(), it->second->dohKraj()->gets(), it->second->dohKraj()->getms());
            string text = it->second->dohTekst();
            Subtitle* novi = new Subtitle(novipocetak, novikraj, text);
            deleteOneTitle(stariKey);
            while(!addOneTitle(novipocetak->hashKey(), novi)) { novipocetak->dodajVreme(0.001); novikraj->dodajVreme(0.001); }
            counter++;
            it = it_temp;
        }
    }
    return counter;
}

int SubtitleProcessing::moveSpecificTimes(double from, double until, double time_duration) {
    int counter = 0;
    if (time_duration == 0) return 0;
    if (time_duration > 0){
        map<long long int, Subtitle*>::const_iterator it = titles->getMap().cend();
        --it;
        while (it != titles->getMap().cbegin() && it->second->dohPocetak()->vreme() >= until) --it;
        while (it != titles->getMap().cend() && it->second->dohPocetak()->vreme() >= from){
            map<long long int, Subtitle*>::const_iterator it_temp = it;
            --it_temp;
            long long int stariKey = it->second->dohPocetak()->hashKey();
            it->second->dohPocetak()->dodajVreme(time_duration);
            it->second->dohKraj()->dodajVreme(time_duration);
            TimeStamp* novipocetak = new TimeStamp(it->second->dohPocetak()->geth(), it->second->dohPocetak()->getm(), it->second->dohPocetak()->gets(), it->second->dohPocetak()->getms());
            TimeStamp* novikraj = new TimeStamp(it->second->dohKraj()->geth(), it->second->dohKraj()->getm(), it->second->dohKraj()->gets(), it->second->dohKraj()->getms());
            string text = it->second->dohTekst();
            Subtitle* novi = new Subtitle(novipocetak, novikraj, text);
            deleteOneTitle(stariKey);
            while(!addOneTitle(novipocetak->hashKey(), novi)) { novipocetak->oduzmiVreme(0.001); novikraj->oduzmiVreme(0.001); }
            counter++;
            it = it_temp;
        }
    }
    if (time_duration < 0){
        time_duration = -time_duration;
        map<long long int, Subtitle*>::const_iterator it = titles->getMap().cbegin();
        while (it != titles->getMap().cend() && it->second->dohPocetak()->vreme() <= from) ++it;
        while (it != titles->getMap().cend() && it->second->dohPocetak()->vreme() <= until){
            map<long long int, Subtitle*>::const_iterator it_temp = it;
            ++it_temp;
            long long int stariKey = it->second->dohPocetak()->hashKey();
            it->second->dohPocetak()->oduzmiVreme(time_duration);
            it->second->dohKraj()->oduzmiVreme(time_duration);
            TimeStamp* novipocetak = new TimeStamp(it->second->dohPocetak()->geth(), it->second->dohPocetak()->getm(), it->second->dohPocetak()->gets(), it->second->dohPocetak()->getms());
            TimeStamp* novikraj = new TimeStamp(it->second->dohKraj()->geth(), it->second->dohKraj()->getm(), it->second->dohKraj()->gets(), it->second->dohKraj()->getms());
            string text = it->second->dohTekst();
            Subtitle* novi = new Subtitle(novipocetak, novikraj, text);
            deleteOneTitle(stariKey);
            while(!addOneTitle(novipocetak->hashKey(), novi)) { novipocetak->dodajVreme(0.001); novikraj->dodajVreme(0.001); }
            counter++;
            it = it_temp;
        }
    }
    return counter;
}

int SubtitleProcessing::increaseAllDistance(double time_duration) {
    if (time_duration == 0) return (int)titles->numberOfSubtitles();
    increaseSpecificDistance(MIN_TIME, MAX_TIME, time_duration);
    return (int)titles->numberOfSubtitles();
}

void SubtitleProcessing::increaseSpecificDistance(double from, double until, double time_duration) {
    int k = (int)titles->numberOfSubtitles() - 1;
    map<long long int, Subtitle*>::const_iterator it1 = titles->getMap().cend();
    --it1;
    while (it1 != titles->getMap().cbegin() && it1->second->dohPocetak()->vreme() > until) { --it1; k--; }
    map<long long int, Subtitle*>::const_iterator it2 = it1;
    --it2;
    while (it1 != titles->getMap().cbegin() && it1->second->dohPocetak()->vreme() > from) {
            long long int oldKey = it1->second->dohPocetak()->hashKey();
            it1->second->dohPocetak()->dodajVreme(k*time_duration);
            it1->second->dohKraj()->dodajVreme(k*time_duration);
            TimeStamp* novipocetak = new TimeStamp(it1->second->dohPocetak()->geth(), it1->second->dohPocetak()->getm(), it1->second->dohPocetak()->gets(), it1->second->dohPocetak()->getms());
            TimeStamp* novikraj = new TimeStamp(it1->second->dohKraj()->geth(), it1->second->dohKraj()->getm(), it1->second->dohKraj()->gets(), it1->second->dohKraj()->getms());
            string text = it1->second->dohTekst();
            Subtitle* novi = new Subtitle(novipocetak, novikraj, text);
            it1 = it2;
            --it2;
            deleteOneTitle(oldKey);
            while(!addOneTitle(novipocetak->hashKey(), novi)) { novipocetak->oduzmiVreme(0.001); novikraj->oduzmiVreme(0.001); }
            k--;
            cout << k <<endl;
    }
}

int SubtitleProcessing::decreaseAllDistance(double time_duration) {
    if (time_duration == 0) return (int)titles->numberOfSubtitles();
    decreaseSpecificDistance(MIN_TIME, MAX_TIME, time_duration);
    return (int)titles->numberOfSubtitles();
}

void SubtitleProcessing::decreaseSpecificDistance(double from, double until, double time_duration) {
    int k = 0;
    map<long long int, Subtitle*>::const_iterator it1 = titles->getMap().cbegin();
    while (it1 != titles->getMap().cend() && it1->second->dohPocetak()->vreme() < from) { it1++; k++; }
    map<long long int, Subtitle*>::const_iterator it2 = it1;
    ++it2;
    while (it1 != titles->getMap().cend() && it1->second->dohPocetak()->vreme() < until ) {
            long long int oldKey = it1->second->dohPocetak()->hashKey();
            it1->second->dohPocetak()->oduzmiVreme(k*time_duration);
            it1->second->dohKraj()->oduzmiVreme(k*time_duration);
            TimeStamp* novipocetak = new TimeStamp(it1->second->dohPocetak()->geth(), it1->second->dohPocetak()->getm(), it1->second->dohPocetak()->gets(), it1->second->dohPocetak()->getms());
            TimeStamp* novikraj = new TimeStamp(it1->second->dohKraj()->geth(), it1->second->dohKraj()->getm(), it1->second->dohKraj()->gets(), it1->second->dohKraj()->getms());
            string text = it1->second->dohTekst();
            Subtitle* novi = new Subtitle(novipocetak, novikraj, text);
            it1 = it2;
            it2++;
            deleteOneTitle(oldKey);
            while(!addOneTitle(novipocetak->hashKey(), novi)) { novipocetak->dodajVreme(0.001); novikraj->dodajVreme(0.001); }
            k++;
            cout << k <<endl;
    }
}

void SubtitleProcessing::resolveErrors(){
    for (map<long long int, Subtitle*>::const_iterator it = titles->getMap().cbegin(); it != titles->getMap().cend(); ++it) {
        if (it->second->dohTrajanje() < 0) it->second->setKraj(it->second->dohPocetak());
    }
}

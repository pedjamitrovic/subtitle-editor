#ifndef _SUBTITLEIO_H_
#define _SUBTITLEIO_H_
#include "Subtitles.h"
#include "FileInfo.h"
#include <regex>
#include <functional>
#include <iostream>
using namespace std;

#define DEFAULT_FPS 25

class GreskaOtvaranje : public exception {
public:
    virtual const char* what() const override { return "Neuspesno otvaranje fajla."; }
    friend ostream& operator<<(ostream& os, const GreskaOtvaranje& go) {
        return os << go.what();
    }
};

class GreskaFPS : public exception {
public:
    virtual const char* what() const override { return "Uneli ste nedozvoljenu vrednost FPS. Dozvoljen opseg je (1-1000)."; }
    friend ostream& operator<<(ostream& os, const GreskaFPS& gfps) {
        return os << gfps.what();
    }
};

class GreskaFormat : public exception {
private:
    int linija;
public:
    GreskaFormat(int i) { linija = i; }
    int dohLiniju() const { return linija; }
    virtual const char* what() const override { return "Greska u formatu u liniji broj "; }
    friend ostream& operator<<(ostream& os, const GreskaFormat& gf) {
        if (gf.dohLiniju() == 1) return os << "Greska u formatu prevoda." << endl << "Obratite paznju da li ste izabrali odgovarajuci format.";
        return os << gf.what() << gf.dohLiniju();
    }
};

class SubtitleIO {
protected:
	Subtitles* titles;
	ifstream input;
	ofstream output;
	regex expr;
	function<int(string)> timeconvert;
    FileInfo* inputinfo;
    double fps = DEFAULT_FPS;
public:
	SubtitleIO();
	virtual ~SubtitleIO();
	Subtitles* getTitles() const;
    void setTitles(Subtitles* sub);
    void setFPS(double user_fps);
	FileInfo* getFileInfo() const;
    virtual void readFile() = 0;
	virtual void writeFile(const string& filename) = 0;
	ifstream::pos_type fileSize(const string& filename);
	TimeStamp* titlesDuration();
};



#endif // !_SUBTITLEIO_H_

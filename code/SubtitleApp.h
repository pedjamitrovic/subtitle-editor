#ifndef _SUBTITLEAPP_H_
#define _SUBTITLEAPP_H_
#include "SubtitleIO.h"
#include "mainwindow.h"
#include <QApplication>

class SubtitleApp final {
private:
	SubtitleIO* io;
    Subtitles* titles;
public:
	SubtitleApp();
	~SubtitleApp();
	void setNewIO(SubtitleIO* newIO);
    SubtitleIO* getIO();
	void setNewTitles(Subtitles* newtitles);
    void start(int argc, char *argv[]);
};



#endif // !_SUBTITLEAPP_H_

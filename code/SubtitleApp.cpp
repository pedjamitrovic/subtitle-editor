#include "SubtitleApp.h"

SubtitleApp::SubtitleApp() { io = nullptr; titles = nullptr; }

SubtitleApp::~SubtitleApp() { if (io != nullptr) delete io; io = nullptr; }

void SubtitleApp::setNewIO(SubtitleIO* newIO) {
    if (io != nullptr) delete io;
	io = newIO;
}

SubtitleIO* SubtitleApp::getIO() {
    return io;
}

void SubtitleApp::setNewTitles(Subtitles* newtitles) {
    titles = newtitles;
}

void SubtitleApp::start(int argc, char *argv[]){
    QApplication a(argc,argv);
    MainWindow w;
    w.setApp(this);
    w.show();
    a.exec();
}

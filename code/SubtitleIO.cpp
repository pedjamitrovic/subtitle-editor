#include "SubtitleIO.h"

SubtitleIO::SubtitleIO() { titles = new Subtitles(); }

SubtitleIO::~SubtitleIO() { if(titles!=nullptr) delete titles; titles = nullptr; if(inputinfo!=nullptr) delete inputinfo; inputinfo = nullptr;}

Subtitles* SubtitleIO::getTitles() const { return titles; }

void SubtitleIO::setTitles(Subtitles* sub) { titles = sub; }

FileInfo* SubtitleIO::getFileInfo() const { return inputinfo; }

ifstream::pos_type SubtitleIO::fileSize(const string& filename) {
	ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
	return in.tellg();
}

TimeStamp* SubtitleIO::titlesDuration() {
	double duration = 0;
	for (map<long long int, Subtitle*>::const_iterator it = titles->getMap().cbegin(); it != titles->getMap().cend(); ++it) {
		duration += (*it).second->dohTrajanje();
	}
	int ms = (int)((duration - floor(duration)) * 1000);
	duration = floor(duration);
	int h = (int)duration / 3600;
	duration -= h * 3600;
	int m = (int)duration / 60;
	duration -= m * 60;
	int s = (int)duration;
	return new TimeStamp(h, m, s, ms);
}

void SubtitleIO::setFPS(double user_fps){
    if (user_fps > 0 && user_fps < 1000) fps = user_fps;
}

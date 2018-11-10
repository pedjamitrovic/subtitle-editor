#include "FileInfo.h"

FileInfo::FileInfo(const string& _name, TimeStamp* _titlesduration, SubtitleFormat _format, int _titlecount, ifstream::pos_type _filesize)
{
	name = _name;
	titlesduration = _titlesduration;
	format = _format;
	titlecount = _titlecount;
	filesize = _filesize;
}

string FileInfo::getname() const {
	return name;
}

TimeStamp* FileInfo::gettitlesduration() const {
	return titlesduration;
}

FileInfo::SubtitleFormat FileInfo::getformat() const {
	return format;
}

int FileInfo::gettitlecount() const {
	return titlecount;
}

ifstream::pos_type FileInfo::getfilesize() const {
	return filesize;
}

ostream& operator<<(ostream& os, const FileInfo& fi) {
	os << "Naziv fajla: " << fi.getname().c_str() << endl;
	os << "Ukupno trajanje titlova: " << *(fi.gettitlesduration()) << endl;
	os << "Format: ";
	if (fi.getformat() == FileInfo::SubtitleFormat::SRT) os << "SubRip" << endl;
	else if (fi.getformat() == FileInfo::SubtitleFormat::MicroDVD) os << "MicroDVD" << endl;
	else if (fi.getformat() == FileInfo::SubtitleFormat::MPSub) os << "MPlayer" << endl;
	else os << "Nepoznat format" << endl;
	os << "Ukupan broj titlova: " << fi.gettitlecount() << endl;
	os << "Velicina fajla u bajtovima: " << fi.getfilesize() << endl;
	return os;
}
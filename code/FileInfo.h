#ifndef _FILEINFO_H_
#define _FILEINFO_H_
#include "TimeStamp.h"
#include <fstream>

class FileInfo {
public:
	enum class SubtitleFormat { SRT, MicroDVD, MPSub };
private:
	string name;
	TimeStamp* titlesduration;
	SubtitleFormat format;
	int titlecount;
	ifstream::pos_type filesize;
public:
	FileInfo(const string& _name, TimeStamp* _titlesduration, SubtitleFormat _format, int _titlecount, ifstream::pos_type _filesize);
	string getname() const;
	TimeStamp* gettitlesduration() const;
	SubtitleFormat getformat() const;
	int gettitlecount() const;
	ifstream::pos_type getfilesize() const;
	friend ostream& operator<<(ostream& os, const FileInfo& fi);
};

#endif
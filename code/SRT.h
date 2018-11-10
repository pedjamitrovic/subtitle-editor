#ifndef _SRT_H_
#define _SRT_H_
#include "SubtitleIO.h"

class SRT : public SubtitleIO {
public:
	SRT();
	SRT(const string& filename);
	virtual ~SRT(){}
    void readFile() override;
	void writeFile(const string& filename) override;
};



#endif // !_SRT_H_

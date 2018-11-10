#ifndef _MPSUB_H_
#define _MPSUB_H_
#include "SubtitleIO.h"

class MPSub: public SubtitleIO {
public:
	MPSub();
	MPSub(const string& filename);
	virtual ~MPSub() {}
    void readFile() override;
	void writeFile(const string& filename) override;
};



#endif // !_MPSUB_H_

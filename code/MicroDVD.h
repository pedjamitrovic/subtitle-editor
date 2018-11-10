#ifndef _MICRODVD_H_
#define _MICRODVD_H_
#include "SubtitleIO.h"

class MicroDVD: public SubtitleIO {
private:
public:
    MicroDVD(double user_fps = DEFAULT_FPS);
    MicroDVD(const string& filename, double user_fps = DEFAULT_FPS);
	virtual ~MicroDVD() {}
    void readFile() override;
	void writeFile(const string& filename) override;
};



#endif // !_MICRODVD_H_

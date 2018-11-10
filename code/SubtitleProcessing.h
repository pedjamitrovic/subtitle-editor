#ifndef _SUBTITLEPROCESSING_H_
#define _SUBTITLEPROCESSING_H_
#include "Subtitles.h"

class SubtitleProcessing {
private:
	Subtitles* titles;
public:
	SubtitleProcessing(Subtitles* titles);
	~SubtitleProcessing();
    Subtitles* getTitles();
	bool addOneTitle(long long int key, Subtitle* sub);
	bool deleteOneTitle(long long int key);
	Subtitle* getExactTitle(long long int key);
	double getAppearingTime(long long int key);
	bool setBegTime(long long int key, TimeStamp* newbeg);
	bool setEndTime(long long int key, TimeStamp* newend);
	bool setText(long long int key, const string& text);
	bool checkAllTimes();
    int mergeEveryTwo(double time_space, size_t char_number);
	bool mergeTwo(Subtitle* first, Subtitle* second, double time_space, size_t char_number);
    int splitEveryToMore(double time_duration, size_t char_number, size_t split_count);
	bool splitToMore(Subtitle* sub, double time_duration, size_t char_number, size_t split_count);
    int moveAllTimes(double time_duration);
    int moveSpecificTimes(double from, double until, double time_duration);
    int increaseAllDistance(double time_duration);
	void increaseSpecificDistance(double from, double until, double time_duration);
    int decreaseAllDistance(double time_duration);
    void decreaseSpecificDistance(double from, double until, double time_duration);
    void resolveErrors();
};



#endif // !_SUBTITLEPROCESSING_H_

#include "MPSub.h"

MPSub::MPSub() {
	expr = "^(\\d+)(?:\\.(\\d{1,2}))?\\s(\\d+)(?:\\.(\\d{1,2}))?";
	timeconvert = [](string x) -> int { return atoi(x.c_str()); };
}

MPSub::MPSub(const string& filename) {
	input.open(filename);
	if (!input.is_open()) throw GreskaOtvaranje();
	expr = "^(\\d+)(?:\\.(\\d{1,2}))?\\s(\\d+)(?:\\.(\\d{1,2}))?";
	timeconvert = [](string x) -> int { return atoi(x.c_str()); };
    readFile();
	input.close();
    inputinfo = new FileInfo(filename, titlesDuration(), FileInfo::SubtitleFormat::MPSub, (int)titles->numberOfSubtitles(), fileSize(filename));
}

void MPSub::readFile() {
	string line, text, time;
	smatch sm;
	int title_counter = 0;
	int hold = 0, mold = 0, sold = 0, msold = 0, hnew = 0, mnew = 0, snew= 0, msnew = 0;

	while (!input.eof()) {
		title_counter++;
		text = "";
		getline(input, time);
		bool match = regex_search(time, sm, expr);
		if (!match) throw GreskaFormat(title_counter);
		getline(input, line);
		while (line != "\r" && line != "") {
			text.append(line);
			text.append("\n");
			getline(input, line);
		}
		text.erase(text.length() - 1, 1);

		if(sm[2].length() < 2) msold += timeconvert(sm[2]) * 100;
		else msold += timeconvert(sm[2]) * 10;
		sold += timeconvert(sm[1]);
		if (msold > 999) sold += 1, msold %= 1000;
		if (sold > 59) mold += 1, sold %= 60;
		if (mold > 59) hold += 1, mold %= 60;

		if (sm[4].length() < 2) msnew = msold + timeconvert(sm[4]) * 100;
		else msnew = msold + timeconvert(sm[4]) * 10;
		snew = sold + timeconvert(sm[3]);
		if (msnew > 999) snew += 1, msnew %= 1000;
		mnew = mold;
		if (snew > 59) mnew += 1, snew %= 60;
		hnew = hold;
		if (mnew > 59) hnew += 1, mnew %= 60;

		TimeStamp key_temp(hold, mold, sold, msold);
		long long int key = key_temp.hashKey();
		titles->add(key, new Subtitle(new TimeStamp(hold, mold, sold, msold), new TimeStamp(hnew, mnew, snew, msnew), text));

		hold = hnew;
		mold = mnew;
		sold = snew;
		msold = msnew;
	}
}

void MPSub::writeFile(const string& filename) {
    double prethodno_vreme = 0;
	string x = filename + ".sub";
	output.open(x);
	if (!output.is_open()) throw GreskaOtvaranje();
    for (map<long long int, Subtitle*>::const_iterator it = titles->getMap().cbegin(); it != titles->getMap().cend(); ) {
        int time_temp = ((*it).second->dohPocetak()->vreme() - prethodno_vreme) * 100;
        if(time_temp % 100 == 0){
            output.setf(ios::fixed,ios::floatfield);
            output.precision(0);
            output << (*it).second->dohPocetak()->vreme() - prethodno_vreme << " ";
        }
        else if(time_temp % 10 == 0){
            output.setf(ios::fixed,ios::floatfield);
            output.precision(1);
            output << (*it).second->dohPocetak()->vreme() - prethodno_vreme << " ";
        }
        else {
            output.setf(ios::fixed,ios::floatfield);
            output.precision(2);
            output << (*it).second->dohPocetak()->vreme() - prethodno_vreme << " ";
        }
        time_temp = (*it).second->dohTrajanje() * 100;
        //time_temp = (*it).second->dohTrajanje() * 100;
        if(time_temp % 100 == 0){
            output.setf(ios::fixed,ios::floatfield);
            output.precision(0);
            output << (*it).second->dohTrajanje() << endl;
        }
        else if(time_temp % 10 == 0){
            output.setf(ios::fixed,ios::floatfield);
            output.precision(1);
            output << (*it).second->dohTrajanje() << endl;
        }
        else {
            output.setf(ios::fixed,ios::floatfield);
            output.precision(2);
            output << (*it).second->dohTrajanje() << endl;
        }
		output << (*it).second->dohTekst() << endl;
		prethodno_vreme = (*it).second->dohKraj()->vreme();
        if (++it != titles->getMap().cend()) output << endl;
	}
    output.close();
}

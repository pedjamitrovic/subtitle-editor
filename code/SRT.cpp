#include "SRT.h"
#include <QApplication>

SRT::SRT() {
	expr = "([0-9][0-9]):([0-5][0-9]):([0-5][0-9]),([0-9]{3})\\s-->\\s([0-9][0-9]):([0-5][0-9]):([0-5][0-9]),([0-9]{3})";
	timeconvert = [](string x) -> int { return atoi(x.c_str()); };
}

SRT::SRT(const string& filename) {
    input.open(filename);
    if (!input.is_open()) throw GreskaOtvaranje();
	expr = "([0-9][0-9]):([0-5][0-9]):([0-5][0-9]),([0-9]{3})\\s-->\\s([0-9][0-9]):([0-5][0-9]):([0-5][0-9]),([0-9]{3})";
	timeconvert = [](string x) -> int { return atoi(x.c_str()); };
    readFile();
	input.close();
    inputinfo = new FileInfo(filename, titlesDuration(), FileInfo::SubtitleFormat::SRT, (int)titles->numberOfSubtitles(), fileSize(filename));
}

void SRT::readFile() {
	int title_counter;
	string line, text, time;
	smatch sm;

	while (!input.eof()) {
		text = "";
		input >> title_counter;
		getline(input, line);
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

		TimeStamp key_temp(timeconvert(sm[1]), timeconvert(sm[2]), timeconvert(sm[3]), timeconvert(sm[4]));
		long long int key = key_temp.hashKey();
		titles->add(key, new Subtitle(new TimeStamp(timeconvert(sm[1]), timeconvert(sm[2]), timeconvert(sm[3]), timeconvert(sm[4])), new TimeStamp(timeconvert(sm[5]), timeconvert(sm[6]), timeconvert(sm[7]), timeconvert(sm[8])), text));
	}
}

void SRT::writeFile(const string& filename) {
	int i = 1;
    string x = filename + ".srt";
	output.open(x);
	if (!output.is_open()) throw GreskaOtvaranje();
	for (map<long long int, Subtitle*>::const_iterator it = titles->getMap().cbegin(); it != titles->getMap().cend(); i++) {
		output << i << endl;
		output << setfill('0') << setw(2) << (*it).second->dohPocetak()->geth() << ":"  << setfill('0') << setw(2) << (*it).second->dohPocetak()->getm() << ":" << setfill('0') << setw(2) << (*it).second->dohPocetak()->gets() << "," << setfill('0') << setw(3) << (*it).second->dohPocetak()->getms();
		output << " --> ";
		output << setfill('0') << setw(2) << (*it).second->dohKraj()->geth() << ":"  << setfill('0') << setw(2) << (*it).second->dohKraj()->getm() << ":" << setfill('0') << setw(2) << (*it).second->dohKraj()->gets() << "," << setfill('0') << setw(3) << (*it).second->dohKraj()->getms() << endl;
		output << (*it).second->dohTekst() << endl;
		if (++it != titles->getMap().cend()) output << endl;
	}
	output.close();
}

#include "MicroDVD.h"

MicroDVD::MicroDVD(double user_fps) {
	if (user_fps > 0 && user_fps < 1000) fps = user_fps;
	else throw GreskaFPS();
	expr = "\\{(\\d+)\\}\\{(\\d+)\\}(.*)";
	timeconvert = [](string x) -> int { return atoi(x.c_str()); };
}

MicroDVD::MicroDVD(const string& filename, double user_fps) {
	if (user_fps > 0 && user_fps < 1000) fps = user_fps;
    else throw GreskaFPS();
	input.open(filename);
    if (!input.is_open()) throw GreskaOtvaranje();
	expr = "\\{(\\d+)\\}\\{(\\d+)\\}(.*)";
	timeconvert = [](string x) -> int { return atoi(x.c_str()); };
    readFile();
	input.close();
    inputinfo = new FileInfo(filename, titlesDuration(), FileInfo::SubtitleFormat::MicroDVD, (int)titles->numberOfSubtitles(), fileSize(filename));
}

void MicroDVD::readFile() {
	int title_counter = 0;
	string line, text;
	smatch sm;
	int hold, mold, sold, msold, hnew, mnew, snew, msnew;
	double pocetak, kraj;

	while (!input.eof()) {
		title_counter++;
		text = "";
		getline(input, line);
		if (line == "") break;
		bool match = regex_search(line, sm, expr);
		if (!match) throw GreskaFormat(title_counter);

		pocetak = timeconvert(sm[1]) / fps;
		kraj = timeconvert(sm[2]) / fps;

		msold = (int)((pocetak - floor(pocetak)) * 1000);
		pocetak = floor(pocetak);
		hold = (int)pocetak / 3600;
		pocetak -= hold * 3600;
		mold = (int)pocetak / 60;
		pocetak -= mold * 60;
		sold = (int)pocetak;

		msnew = (int)((kraj - floor(kraj)) * 1000);
		kraj = floor(kraj);
		hnew = (int)kraj / 3600;
		kraj -= hnew * 3600;
		mnew = (int)kraj / 60;
		kraj -= mnew * 60;
		snew = (int)kraj;

		text = sm[3].str();
		for (size_t i = 0; i < text.length(); i++) if (text[i] == '|') text[i] = '\n';
		
		TimeStamp key_temp(hold, mold, sold, msold);
		long long int key = key_temp.hashKey();
		titles->add(key, new Subtitle(new TimeStamp(hold, mold, sold, msold), new TimeStamp(hnew, mnew, snew, msnew), text));
	}
}

void MicroDVD::writeFile(const string& filename) {
	string x = filename + ".txt";
	output.open(x);
	if (!output.is_open()) throw GreskaOtvaranje();
	for (map<long long int, Subtitle*>::const_iterator it = titles->getMap().cbegin(); it != titles->getMap().cend(); ++it) {
		output << "{" << round((*it).second->dohPocetak()->vreme() * fps) << "}" << "{" << round((*it).second->dohKraj()->vreme() * fps) << "}";
		string text = (*it).second->dohTekst();
		for (size_t i = 0; i < text.length(); i++) if (text[i] == '\n') text[i] = '|';
		output << text << endl;
	}
	output.close();
}

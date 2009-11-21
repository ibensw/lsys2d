#include <stdio.h>
#include <list>
#include <utility>
#include <string>
#include <fstream>
#include "../../tinyxml/tinyxml.h"

using namespace std;

string escape(string crap){
	for (unsigned int i = 0; i < crap.length(); i++){
		if (crap[i] ==' '){
			crap.replace(i,1,"");
		}
	}
	for (unsigned int i = 0; i < crap.length(); i++){
		if (crap[i] =='&'){
			crap.replace(i,1,"&amp;");
		}
	}
	for (unsigned int i = 0; i < crap.length(); i++){
		if (crap[i] =='<'){
			crap.replace(i,1,"&lt;");
		}
	}
	for (unsigned int i = 0; i < crap.length(); i++){
		if (crap[i] =='>'){
			crap.replace(i,1,"&gt;");
		}
	}
	for (unsigned int i = 0; i < crap.length(); i++){
		if (crap[i] =='\''){
			crap.replace(i,1,"&apos;");
		}
	}
	for (unsigned int i = 0; i < crap.length(); i++){
		if (crap[i] =='"'){
			crap.replace(i,1,"&quot;");
		}
	}
	return crap;
}

int main(int argc, char *argv[]){
	if (argc < 2){
		return 1;
	}

	list< pair<char, string> > rules;

	ifstream infile(argv[1]);
	if (!infile.is_open()){
		printf("Could not open file.\n");
		return 1;
	}

	char buffer[512];

	float params[3];
	unsigned int readparams=0;
	string axiom;
	string replace;
	bool eof=false;

	while (!infile.eof() && !eof){
		infile.getline(buffer, 512);

		sscanf(buffer, "%[^#]", buffer);

		if (buffer[0] != '#'){
			if (buffer[0] == '@'){
				eof=true;
			}else if (readparams < 3){
				sscanf(buffer, "%f", &(params[readparams]));
				++readparams;
			}else if (readparams == 3){
				axiom=buffer;
				axiom=escape(axiom);
				++readparams;
			}else{
				replace=buffer+2;
				replace=escape(replace);
				rules.push_back(pair<char, string>(buffer[0], replace));
			}
		}
	}

	infile.close();

	params[2]/=100.0;

	//printf("angle=%f\nthick=%f\naxiom=%s\n", params[1], params[2], axiom.c_str());
	string filename=argv[1];
	filename+=".xml";
	ofstream outfile(filename.c_str());

	outfile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl
			<< "<lsystem sigma='" << params[1] << "' length='1.0' radius='" << params[2] << "'>" << endl
			<< "\t<initiator>" << axiom << "</initiator>" << endl << endl;

	for (list< pair<char, string> >::iterator it=rules.begin(); it != rules.end(); it++){
		outfile << "\t<rule find='" << (*it).first << "'>" << (*it).second << "</rule>" << endl;
	}

	outfile << "</lsystem>" << endl;

	outfile.close();

}

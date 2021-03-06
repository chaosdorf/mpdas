#include "mpdas.h"
#include <iostream>
#include <cstdlib>

CConfig* Config = 0;

void CConfig::ParseLine(std::string line)
{
	std::vector<std::string> tokens;
	char* pstr = 0;
	char* szline = new char[line.size()+1];

	strncpy(szline, line.c_str(), line.size()+1);

	pstr = strtok(szline, " :=\t");
	while(pstr) {
		tokens.push_back(pstr);
		pstr = strtok(NULL, " :=\t");
	}
	delete[] szline;

	if(tokens.size() > 1) {
		if(tokens[0] == "username")
			_lusername = tokens[1];
		else if(tokens[0] == "password")
			_lpassword = tokens[1];
		else if(tokens[0] == "host")
			_mhost = tokens[1];
		else if(tokens[0] == "mpdpassword")
			_mpassword = tokens[1];
		else if(tokens[0] == "service" && tokens[1] == "librefm")
			_service = LibreFm;
		else if(tokens[0] == "port")
			_mport = atoi(tokens[1].c_str());
		else if(tokens[0] == "runas")
			_runninguser = tokens[1];
		else if(tokens[0] == "debug") {
			if(tokens[1] == "1" || tokens[1] == "true")
				_debug = true;
		}

	}
}

void CConfig::LoadConfig(std::string path)
{
	std::string line = "";

	std::ifstream ifs(path.c_str(), std::ios::in);

	if(!ifs.good()) {
		iprintf("Config file (%s) does not exist or is not readable.", path.c_str());
		return;
	}

	while(ifs.good()) {
		getline(ifs, line);
		ParseLine(line);
	}

}

CConfig::CConfig(char* cfg)
{
	/* Set optional settings to default */
	_mhost = "localhost";
	_service = LastFm;
	_mport = 6600;
	_debug = false;

	std::string path = "";

	if(!cfg) {
		path = CONFDIR;
		path.append("/mpdasrc");
	}
	else {
		path = cfg;
	}

	LoadConfig(path);

  if(const char* mhost = std::getenv("MPD_SERVER")) _mhost = mhost;
  if(const char* debug = std::getenv("DEBUG")) _debug = debug;
  if(const char* lusername = std::getenv("LASTFM_USERNAME")) _lusername = lusername;
  if(const char* lpassword = std::getenv("LASTFM_PASSWORD_MD5")) _lpassword = lpassword;
}

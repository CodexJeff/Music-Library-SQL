#include <string>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

#include "str_util.h"
#include "command.h"

Command::Command(string cmdStr){
	commandString = cmdStr;
	parse(commandString);
}

string Command::getCommandString(){return commandString;}
string Command::getCommandName(){return tokens[0];}
int Command::indexOfToken(string s){
	//answer whether token s exists in tokens vector
	if(s.empty()) return -1;
	for(int i=0; i<tokens.size(); i++){
		if(s.compare(tokens[i]) == 0) return i;
	}
	return -1;
}
bool Command::hasToken(string s){
	return indexOfToken(s) >= 0;
}
string Command::getToken(int i){
	if(i >= 0 && i<tokens.size())
	return tokens[i];
	else
	return "";
}

string Command::getToken(string s){
	//e.g. for use with commands like: add -s "The Girl From Ipanema"
	//getToken("-s") should return "The Girl From Ipanema"
	string emptyToken = "";
	if(!hasToken(s)) return emptyToken;
	int tokenIndex = indexOfToken(s);
	if(tokenIndex < tokens.size()-1) return tokens[tokenIndex + 1];
	return emptyToken;
}

bool Command::isCommand(string aCommandName){
	return getCommandName().compare(aCommandName) == 0;
}

bool Command::isTokenAt(int index, const string & s){
	//answer whether token at index equals string s
	if(index < 0) return false;
	if(tokens.size() < index + 1) return false;
	return (tokens[index]).compare(s) == 0;
}

bool Command::isValidIndex(string anIndexString){
	if(anIndexString.empty()) return false;
	if(anIndexString.compare("?") == 0 ) return true;
	try{
		int index = stoi(anIndexString);
		if(index < 0) return false;
		const int MAX_INDEX_VALUE = 99999; //bad hard-coding
		if(index > MAX_INDEX_VALUE) return false;
		return true;
	}
	catch(const invalid_argument &a) {
		return false;
	}
}

bool Command::isUICommand(){
	for(int i=0; i<NumberOfUICommands; i++)
	if(getCommandName().compare(UICommands[i]) == 0) return true;
	return false;
}

bool Command::isAppCommand(){
	for(int i=0; i<NumberOfAppCommands; i++)
	if(getCommandName().compare(AppCommands[i]) == 0) return true;
	return false;
}

bool Command::isDevCommand(){
	for(int i=0; i<NumberOfDevCommands; i++)
	if(getCommandName().compare(DevCommands[i]) == 0) return true;
	return false;
}
void Command::parse(string cmdStr){
	/*
	Parse (tokenize) the command

	Parse a command like:
	add -s "The Girl From Ipanema"
	into:
	add
	-s
	The Girl From Ipanema
	*/
	string buffer;
	stringstream ss(cmdStr); // Insert the string into a stringstream

	//Tokenize the command
	//collect substrings between "" quotation marks as a single token
	//and strip off the "" quotation marks.
	//This parser essentially does a trim() as well because it
	//uses a stringstream that strips off white space

	string tokenStr = ""; //for collecting "" quoted substring words
	bool collecting = false; //not collecting quoted words
	while (ss >> buffer){
		if((buffer.length() == 2) &&
		(buffer[0] == '"') &&(buffer[1] == '"')){
			//word is a "" empty string
		}
		else if((buffer.length() > 2) &&
		(buffer[0] == '"') &&
		(buffer[buffer.length()-1] == '"')){
			//single word in "" quotes -strip off the quotes
			tokens.push_back(buffer.substr(1,buffer.length()-2));
		}
		else if((buffer.length() == 1) && (buffer[0] == '"')) {
			//word is a single "
			//could be the starting quote or ending quote
			if(collecting == false) {
				collecting = true; //start collecting
			}
			else {
				collecting = false; //stop collecting
				tokens.push_back(StrUtil::trim(tokenStr));
				tokenStr = "";
			}
		}
		else if((buffer.length() > 1) && (buffer[buffer.length()-1] == '"')) {
			//word ends with "
			tokenStr.append(" " + buffer.substr(0,buffer.length()-1));
			collecting = false;
			tokens.push_back(StrUtil::trim(tokenStr));
			tokenStr = "";
		}
		else if((buffer.length() > 1) && (buffer[0] == '"')) {
			//word starts with "
			tokenStr.append(buffer.substr(1,buffer.length()-1));
			collecting = true;
		}
		else if(collecting == true)
		//word within "" quoted substring
		tokenStr.append(" " + buffer);
		else
		tokens.push_back(buffer);
	}
	if(tokens.size() == 0) tokens.push_back("NO COMMAND");

	//Command is now tokenized into tokens vector

	//Print parsed command tokens for now
	cout << "PARSED COMMAND:" << '\n';
	//shows use of iterator
	for (vector<string>::iterator it = tokens.begin(); it!=tokens.end(); ++it)
	cout << *it << '\n';
}

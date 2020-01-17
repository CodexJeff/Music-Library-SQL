#include <string>
#include <sstream>
using namespace std;
#include "str_util.h"

string StrUtil::trim(const string & s) {

	//trim returns a trimmed version of s
	//trim removes leading and trailing white space
	//AND also removes repeated white space between words

	stringstream stream(s);
	string trimmedString;
	stream >> trimmedString;  //grab first word
	string buffer;
	while (stream >> buffer){
		trimmedString.append(" " + buffer);
	}
	return trimmedString;
}

string StrUtil::toTitleCase(const string & s) {

	//Return a title-cased version of s
	//In Title Case each word should start with a captial letter
	//and the remaining letters should be lower case.
	//Also strings starting with "The " will have that replaced
	//with ", The" at the end of the string.
	//e.g. "The Girl From Ipanema" becomes "Girl From Ipanema, The"
	//Note this function effectively does a trim() operation as well

	stringstream stream(s);
	string buffer;
	string titleCasedString;
	while (stream >> buffer){
		buffer = StrUtil::toLowerCase(buffer);
		buffer[0] = toupper(buffer[0]);
		titleCasedString.append(" " + buffer);
	}
	//strip off leading blank
	titleCasedString = StrUtil::trim(titleCasedString);

	if(StrUtil::startsWith(titleCasedString, "The ")) {
		titleCasedString = titleCasedString.substr(4,titleCasedString.length() -4) + ", The";
	}
	return titleCasedString;
}

string StrUtil::toUpperCase(const string & s){
	string upperCaseString;
	for(string::const_iterator itr=s.begin(); itr != s.end(); ++itr){
		upperCaseString.append(1,toupper(*itr));
	}
	return upperCaseString;
}

string StrUtil::toLowerCase(const string & s){
	string lowerCaseString;
	for(string::const_iterator itr=s.begin(); itr != s.end(); ++itr){
		lowerCaseString.append(1,tolower(*itr));
	}
	return lowerCaseString;
}

bool StrUtil::startsWith(const string & s, const string & prefix){
	//answer whether s starts with prefix
	if(prefix.length() > s.length()) return false;
	return (prefix.compare(s.substr(0, prefix.length())) == 0);
}

bool StrUtil::endsWith(const string & s, const string & suffix){
	//answer whether s ends with suffix
	if(suffix.length() > s.length()) return false;
	return (suffix.compare(s.substr(s.length()-suffix.length(), suffix.length())) == 0);
}

bool StrUtil::isComment(const string & s){
	//answer whether s is a comment string
	//comment strings start with "//" prefix

	string trimmed = StrUtil::trim(s);
	string commentPrefix = "//";
	return StrUtil::startsWith(trimmed, commentPrefix);
}

#ifndef STR_UTIL_H
#define STR_UTIL_H

#include <string>
#include <sstream>
using namespace std;

//String Utilties Class
//Should this be done by sub-classing the <string> lib?

class StrUtil{
public:
  static string trim(const string & s);
  static string toTitleCase(const string & s);
  static string toUpperCase(const string & s);
  static string toLowerCase(const string & s);
  static bool startsWith(const string & s, const string & prefix);
  static bool endsWith(const string & s, const string & suffix);
  static bool isComment(const string & s);
};

#endif

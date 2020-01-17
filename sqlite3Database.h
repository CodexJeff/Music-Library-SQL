#ifndef SQLITE3DATABASE_H
#define SQLITE3DATABASE_H

#include <string>
#include <vector>
#include "sqlite3.h"
using namespace std;

class sqlite3Database{
public:
	sqlite3Database(string file);
	~sqlite3Database();
	void queryDatabase(string query);
	void close();
private:
	sqlite3 *database;
};
#endif

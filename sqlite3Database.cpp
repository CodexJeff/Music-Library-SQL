#include "sqlite3Database.h"
#include <iostream>
#include <string>
using namespace std;

sqlite3Database::sqlite3Database(string file){
  char *fileNew = const_cast<char*>(file.c_str());
  sqlite3_open(fileNew, &database);
}

sqlite3Database::~sqlite3Database(){
}

static int callback(
  //callback funtion that will be called by sqlite3_exec() when SQL
  //query has completed
  void * data, //data provided to sqlite3_exec() [4th argument]
  int argc, //Number of columns in answer table row
  char ** argv, //array of string representing table row values
  char ** azColName //array of strings representing column names
){
  //cout << (const char *) data << "\n";
  for (int i = 0; i < argc; i++){
    cout << argv[i] << ", ";
  }
  cout << "\n";
  return 0;
}

void sqlite3Database::queryDatabase(string queryString){
  //execute SQL queryString against the database
  int rc;
  const char * data = "callback called";
  char * zErrMsg = 0;
  if(queryString.empty()) return;
  const char * sqlQuery = queryString.c_str();
  rc = sqlite3_exec(database, sqlQuery, callback, (void *) data, &zErrMsg);
  if(rc != SQLITE_OK) {
    cout << "ERROR EXECUTING SQL: " << zErrMsg;
    sqlite3_free(zErrMsg);
  }
  else {
    cout << "\nSQL QUERY SUCCEEDED\n";
  }
}

void sqlite3Database::close(){
  sqlite3_close(database);
}

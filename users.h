#ifndef _Users_H
#define _Users_H

#include <ostream>
#include <vector>
#include <string>
using namespace std;
#include "UI.h"
#include "user.h"

class Users {
	/*
	Users represents a collection of compositions, specifically User objects
	A Users container OWNS the Users within it.
	If the container is destroyed it deletes the User objects it contains
	If a User is removed from the container the User object is deleted from heap space.
	*/
public:
	Users();
	~Users(void);
	User * findByID(int anID);
	User * findByUserID(const string & aUserID);
	vector<User*> getCollection();
	void add(User & aUser);
	void remove(User & aUser);
	void showOn(UI & aView);
	void showOn(UI & aView, const string & memberID);
private:
	vector<User*> collection;
	vector<User*>::iterator findPosition(User & aUser);
};

#endif

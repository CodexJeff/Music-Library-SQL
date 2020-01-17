#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "user.h"
#include "users.h"

Users::Users(){
}
Users::~Users(void){
	for(int i=0; i<collection.size(); i++)
	delete collection[i]; //delete Users in this container
}

vector<User*> Users::getCollection(){
	return collection; //return copy of collection
}

User * Users::findByID(int anID) {
	for (vector<User*>::iterator itr = collection.begin() ; itr != collection.end(); ++itr)
	if((*itr)->getID() == anID) return *itr;
	return NULL;
}

User * Users::findByUserID(const string & aUserID) {
	for (vector<User*>::iterator itr = collection.begin() ; itr != collection.end(); ++itr)
	if(((*itr)->getUserID()).compare(aUserID) == 0) return *itr;
	return NULL;
}

vector<User*>::iterator Users::findPosition(User & aUser)  {
	for (vector<User*>::iterator it = collection.begin() ; it != collection.end(); ++it)
	if(*it == &aUser) return it;
	return collection.end();
}

void Users::add(User & aUser){
	collection.push_back(&aUser);
}

void Users::remove(User & aUser){
	vector<User*>::iterator itr = findPosition(aUser);
	if(itr != collection.end()) {
		User * theUser = *itr;
		collection.erase(itr);
		delete theUser; //free the memory of theUser
	}
}

void Users::showOn(UI & view) {
	view.printOutput("Users:");
	for(int i=0; i<collection.size(); i++)
	view.printOutput((*collection[i]).toString());
}

void Users::showOn(UI & view, const string & memberID) {
	view.printOutput("User:");
	User * user = findByUserID(memberID);
	if( user != NULL)
	view.printOutput(user->toString());
}

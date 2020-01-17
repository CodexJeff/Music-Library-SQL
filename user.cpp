#include <iostream>
#include <string>
using namespace std;

#include "user.h"

int User::nextUserNumericID = 1000;

User::User(const string & aUserID, const string & aName){
	cout << "User(string&, string&, int)" << endl;
	userid = aUserID;
	name = aName;
	id = nextUserNumericID++;
}

User::User(const User & aUser){
	cout << "User(const User & aUser)" << endl;
	cout << "ERROR: User(const User & aUser) --should never run" << endl;
}

User::~User(){
	cout << "~User(void)" << endl;
	//user objects own playlists
	for(int i=0; i<playlists.size(); i++)
	delete playlists[i]; //delete playlists this user owns

}

int User::getID(){return id;}

string User::getUserID(){return userid;}

vector<Playlist*>::iterator User::findPosition(Playlist & aPlaylist){
	for (vector<Playlist*>::iterator itr = playlists.begin() ; itr != playlists.end(); ++itr)
	if(*itr == &aPlaylist) return itr;
	return playlists.end();
}

Playlist* User::findPlaylist(const string & aPlaylistName){
	for (vector<Playlist*>::iterator itr = playlists.begin() ; itr != playlists.end(); ++itr)
	if(((*itr)->getName()).compare(aPlaylistName) == 0) return *itr;
	return NULL;
}

void User::addPlaylist(Playlist & aPlaylist){
	//add playlist if it does not already exist
	vector<Playlist*>::iterator itr = findPosition(aPlaylist);
	if(itr == playlists.end()) {
		playlists.push_back(&aPlaylist);
	}
}

void User::removePlaylist(Playlist & aPlaylist){
	vector<Playlist*>::iterator itr = findPosition(aPlaylist);
	if(itr != playlists.end()) {
		Playlist * playlist = *itr;
		playlists.erase(itr);
		delete playlist;
	}
}

void User::removeTrack(Track & aTrack){
	for (vector<Playlist*>::iterator itr = playlists.begin() ; itr != playlists.end(); ++itr){
		Playlist * playlist = *itr;
		playlist->removeTrack(aTrack);
	}
}

string User::toString()const {
	string indent = "     ";
	string s;
	s.append(userid + " " + name);
	s.append("\n");
	s.append(indent + "Playlists:\n");
	for (vector<Playlist*>::size_type i = 0 ; i < playlists.size(); i++){
		s.append(indent + to_string(i) + " " + (playlists[i])->toString() + "\n");
		s.append("\n");
	}
	return s;
}

ostream & operator<<(ostream & out, const User & aUser){
	out << aUser.toString() << endl;
	return out;
}

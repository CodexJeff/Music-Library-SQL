#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "track.h"
#include "tracks.h"

Tracks::Tracks(){
}

Tracks::~Tracks(void){
	for(int i=0; i<collection.size(); i++)
	delete collection[i]; //delete Tracks in this container
}

vector<Track*> Tracks::getCollection(){return collection;}

vector<Track*>::iterator Tracks::findPosition(Track & aTrack){
	for (vector<Track*>::iterator it = collection.begin() ; it != collection.end(); ++it)
	if(*it == &aTrack) return it;
	return collection.end();
}

Track * Tracks::findByID(int anID){
	for (vector<Track*>::iterator it = collection.begin() ; it != collection.end(); ++it)
	if((*it)->getID() == anID) return *it;
	return NULL;
}

void Tracks::add(Track & aTrack){
	collection.push_back(&aTrack);
}

void Tracks::remove(Track & aTrack){
	vector<Track*>::iterator index = findPosition(aTrack);
	if(index != collection.end()) {
		Track * theTrack = *index;
		collection.erase(index);
		delete theTrack; //free the memory of theTrack
	}
}

void Tracks::showOn(UI & view) {
	view.printOutput("Tracks:");
	for(int i=0; i<collection.size(); i++)
	view.printOutput((*collection[i]).toString());
}

void Tracks::showOn(UI & view, int memberID)  {
	view.printOutput("Track:");
	Track * track = findByID(memberID);
	if( track != NULL)
	view.printOutput(track->toString());
}

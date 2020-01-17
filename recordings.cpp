#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "recordings.h"
#include "recording.h"

Recordings::Recordings(){
}

Recordings::~Recordings(void){
	for(int i=0; i<collection.size(); i++)
	delete collection[i]; //delete Recordings in this container
}

vector<Recording*> Recordings::getCollection(){return collection;}

vector<Recording*>::iterator Recordings::findPosition(Recording & aRecording){
	for (vector<Recording*>::iterator it = collection.begin() ; it != collection.end(); ++it)
	if(*it == &aRecording) return it;
	return collection.end();
}

Recording * Recordings::findByID(int anID){
	for (vector<Recording*>::iterator it = collection.begin() ; it != collection.end(); ++it)
	if((*it)->getID() == anID) return *it;
	return NULL;
}

void Recordings::add(Recording & aRecording){
	collection.push_back(&aRecording);
}

void Recordings::remove(Recording & aRecording){
	vector<Recording*>::iterator index = findPosition(aRecording);
	if(index != collection.end()) {
		Recording * theRecording = *index;
		collection.erase(index);
		delete theRecording; //free the memory of theRecording
	}
}

void Recordings::showOn(UI & view){
	view.printOutput("Recordings:");
	for(int i=0; i<collection.size(); i++){
		view.printOutput((*collection[i]).toString());
	}
}

void Recordings::showOn(UI & view, int memberID){
	view.printOutput("Recording:");
	Recording * recording = findByID(memberID);
	if( recording != NULL)
	view.printOutput(recording->toString());
}

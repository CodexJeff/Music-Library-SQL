#include <iostream>
#include <string>
using namespace std;

#include "track.h"

Track::Track(const int aTrackId, Song * songptr, const string & anMp3FileName ){
	cout << "Track(int, Song*, string&)" << endl;
	id = aTrackId;
	song = songptr;
	mp3FileName = anMp3FileName;
}

Track::Track(const Track & aTrack){
	cout << "Track(const Track & aTrack)" << endl;
	cout << "ERROR: Track(const Track & aTrack) --should never run" << endl;
}

Track::~Track(){
	cout << "~Track(void)" << endl;
}

int Track::getID(){return id;}
Song * Track::getSong(){return song;}
string Track::getMp3FileName(){return mp3FileName;}

string Track::toString()const {
	return to_string(id) + ": " + song->getTitle() + " mp3: " + mp3FileName;
}

ostream & operator<<(ostream & out, const Track & aTrack){
	out << aTrack.toString() << endl;
	return out;
}

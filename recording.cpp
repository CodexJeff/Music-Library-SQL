#include <iostream>
#include <string>
using namespace std;

#include "recording.h"

Recording::Recording(const string & aTitle,
  const string & anArtist,
  const string & aProducer,
  const string & aYear,
  const int anID){
    cout << "Recording(string&, string&, String&, String&, int)" << endl;
    title = aTitle;
    artist = anArtist;
    producer = aProducer;
    year = aYear;
    id = anID;
    tracks = vector<Track*>(MAX_NUMBER_OF_TRACKS, NULL);
  }

  Recording::Recording(const Recording & aRecording){
    cout << "Recording(const Recording & aRecording)" << endl;
    cout << "ERROR: Recording(const Recording & aRecording) --should never run" << endl;
  }

  Recording::~Recording(){
    cout << "~Recording(void)" << endl;
  }

  int Recording::getID(){return id;}
  vector<Track*> & Recording::getTracks(){return tracks;}

  vector<Track*>::iterator Recording::findPosition(Track & aTrack){
    for (vector<Track*>::iterator it = tracks.begin() ; it != tracks.end(); ++it)
    if(*it == &aTrack) return it;
    return tracks.end();
  }

  void Recording::addTrack(Track & aTrack, int position){
    //add track if it does not already exist
    vector<Track*>::iterator itr = findPosition(aTrack);
    if(itr == tracks.end()) {
      if(position >=0 && position < MAX_NUMBER_OF_TRACKS)
      tracks[position] = &aTrack;
    }
  }

  void Recording::removeTrack(Track & aTrack){
    //remove track from recording
    for(vector<Track*>::size_type i = 0; i<tracks.size(); i++)
    if(tracks[i] == &aTrack) tracks[i] = NULL;
  }

  string Recording::toString()const {
    string indent = "     ";
    string s;
    s.append(to_string(id) + " " + title + " " + artist + " " + producer + " " + year);
    s.append("\n");
    s.append(indent + "Tracks:\n");
    for (vector<Track*>::size_type i = 0 ; i < tracks.size(); i++){
      if(tracks[i] != NULL)
      s.append(indent + to_string(i) + " " + (tracks[i])->toString() + "\n");
    }
    return s;
  }

  ostream & operator<<(ostream & out, const Recording & aRecording){
    out << aRecording.toString() << endl;
    return out;
  }

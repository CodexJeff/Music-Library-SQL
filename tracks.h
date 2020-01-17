#ifndef _TRACKS_H
#define _TRACKS_H

#include <ostream>
#include <vector>
#include <string>
using namespace std;
#include "UI.h"
#include "track.h"

class Tracks {
	/*
	Tracks represents a collection of compositions, specifically Track objects
	A Tracks container OWNS the Tracks within it.
	If the container is destroyed it deletes the Track objects it contains
	If a Track is removed from the container the Track object is deleted from heap space.
	*/
public:
	Tracks();
	~Tracks(void);
	Track * findByID(int anID);
	vector<Track*> getCollection();
	void add(Track & aTrack);
	void remove(Track & aTrack);
	void showOn(UI & aView);
	void showOn(UI & aView, int memberID);
private:
	vector<Track*> collection;
	vector<Track*>::iterator findPosition(Track & aTrack);
};

#endif

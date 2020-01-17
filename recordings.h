#ifndef _RECORDINGS_H
#define _RECORDINGS_H

#include <ostream>
#include <vector>
#include <string>
using namespace std;
#include "UI.h"
#include "recording.h"

class Recordings {
	/*
	Recordings represents a collection of Recording objects
	A Recordings container OWNS the Recording objects within it.
	If the container is destroyed it deletes the Recording objects it contains
	If a Recording is removed from the container the Recording object is deleted from heap space.
	*/
public:
	Recordings();
	~Recordings(void);
	Recording * findByID(int anID);
	vector<Recording*> getCollection();
	void add(Recording & aRecording);
	void remove(Recording & aRecording);
	void showOn(UI & aView);
	void showOn(UI & aView, int memberID);

private:
	vector<Recording*> collection;
	vector<Recording*>::iterator findPosition(Recording & aRecording);
};

#endif

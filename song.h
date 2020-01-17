#ifndef _SONG_H
#define _SONG_H

#include <ostream>
#include <string>

class Song {
	/*
	Song represents a musical composition (not an audio recording)
	*/
public:
	Song(const string & aTitle, const string & aComposer, const int anId = -1);
	~Song(void);
	int getID()const;
	string getTitle()const;
	string toString() const;
private:
	string title;
	string composer;
	int id;
	Song(const Song & aSong); //hide copy constructor in private section
};

ostream & operator<<(ostream & out, const Song & aSong);

#endif

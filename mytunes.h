#ifndef MYTUNES_H
#define MYTUNES_H
#include <sstream>
using namespace std;
#include "UI.h"
#include "command.h"
#include "song.h"
#include "songs.h"
#include "recording.h"
#include "recordings.h"
#include "track.h"
#include "tracks.h"
//#include "playlist.h"
#include "user.h"
#include "users.h"
#include "sqlite3Database.h"

/*
This is the main application class.
It has knowlege of the UI and data model (not done in this assignment).
*/

class MyTunes{
public:
  MyTunes();
  void run();
  void executeCommand(Command cmd);
private:
  UI view;
  sqlite3Database *db;
  //Data Model
  //available ID's for app assigned ID's
  //These should only be used after database data has loaded
  int nextAvailableSongID;
  int nextAvailableRecordingID;
  int nextAvailableTrackID;
  //Data collections
  Songs songs;
  Recordings recordings;
  Tracks tracks;
  Users users;

  void executeCMDADD(Command cmd);
  void executeCMDDELETE(Command cmd);
  void executeCMDSHOW(Command cmd);

  void executeAddSong(Command cmd);
  void executeAddRecording(Command cmd);
  void executeAddTrack(Command cmd);
  void executeAddUser(Command cmd);
  void executeAddPlaylist(Command cmd);
  void executeAddPlaylistTrack(Command cmd);

  void executeDeleteRecording(Command cmd);
  void executeDeleteUser(Command cmd);
  void executeDeleteUserPlaylist(Command cmd);
  void executeDeleteUserPlaylistTrack(Command cmd);
  void executeDeleteTrack(Command cmd); //cascading delete
  void executeDeleteSong(Command cmd);
};
#endif

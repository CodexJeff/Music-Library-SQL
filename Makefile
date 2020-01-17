OBJ = main.o mytunes.o UI.o command.o str_util.o song.o songs.o recording.o recordings.o track.o tracks.o user.o users.o playlist.o sqlite3.o sqlite3Database.o

mytunes: $(OBJ)
	g++ -o mytunes $(OBJ) -lpthread -ldl

main.o: main.cpp
	g++ -c main.cpp

mytunes.o: mytunes.cpp mytunes.h sqlite3Database.h
	g++ -c -std=c++11 mytunes.cpp

UI.o: UI.cpp UI.h
	g++ -c -std=c++11 UI.cpp

command.o: command.cpp command.h
	g++ -c -std=c++11 command.cpp

song.o: song.cpp song.h
	g++ -c -std=c++11 song.cpp

songs.o: songs.cpp songs.h
	g++ -c songs.cpp

user.o: user.cpp user.h
	g++ -c -std=c++11 user.cpp

users.o: users.cpp users.h
	g++ -c -std=c++11 users.cpp

playlist.o: playlist.cpp playlist.h
	g++ -c -std=c++11 playlist.cpp

recording.o: recording.cpp recording.h
	g++ -c -std=c++11 recording.cpp

recordings.o: recordings.cpp recordings.h
	g++ -c -std=c++11 recordings.cpp

track.o: track.cpp track.h
	g++ -c -std=c++11 track.cpp

tracks.o: tracks.cpp tracks.h
	g++ -c -std=c++11 tracks.cpp

str_util.o: str_util.cpp str_util.h
	g++ -c -std=c++11 str_util.cpp

sqlite3Database.o: sqlite3Database.cpp sqlite3Database.h
	g++ -c -std=c++11 sqlite3Database.cpp

sqlite3.o: sqlite3.c sqlite3.h
	gcc -c sqlite3.c

clean:
	rm -f $(OBJ) mytunes

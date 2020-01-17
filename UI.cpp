#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

#include "str_util.h"
#include "UI.h"
#include "command.h"
#include "mytunes.h"

UI::UI(MyTunes * ownerApp) {
	owner = ownerApp;
	logging = OFF;
}

void UI::run(){

	//initialize app with input script
	Command cmd = Command(".read insert_beatles_tracks_rev1.txt");
	//executeCommand(cmd);

	executeCommand(UICMD_HELP); //show help menu on startup

	string input;

	while (true) {
		promptForStr("CMD or " + UICMD_QUIT, input);
		if(input.compare(UICMD_QUIT) == 0) break; //we are done
		if(input.empty()) {/*do nothing*/}
		else if(StrUtil::isComment(input)) {
			/*comment do nothing*/
			if(logging != OFF) logs.push_back(StrUtil::trim(input));
		}
		else {
			/* parse and execute user command */
			Command cmd = Command(input);
			if((logging == COMMAND) || (logging == BOTH))
			logs.push_back(cmd.getCommandString());
			if(cmd.isUICommand()) executeCommand(cmd);
			else if(cmd.isAppCommand()) owner->executeCommand(cmd);
			else if(cmd.isDevCommand()) executeDevCommand(cmd);
			else printError("UNRECOGNIZED COMMAND");
		}
	}
	printMessage("BYE");
}

void UI::executeCommand(Command cmd){
	if(cmd.isCommand(UICMD_READ)) executeUIREAD(cmd);
	else if(cmd.isCommand(UICMD_LOG)) executeUILOG(cmd);
	else if(cmd.isCommand(UICMD_HELP)) executeUIHELP(cmd);
}

void UI::executeDevCommand(Command cmd){
	if(cmd.isCommand(DEV_startsWith)) {
		cout << boolalpha << StrUtil::startsWith(cmd.getToken(1), cmd.getToken(2)) << endl;
	}
	else if(cmd.isCommand(DEV_endsWith)) {
		cout << boolalpha <<  StrUtil::endsWith(cmd.getToken(1), cmd.getToken(2)) <<endl;
	}
	else if(cmd.isCommand(DEV_trim)) {
		cout <<  StrUtil::trim(cmd.getToken(1)) <<endl;
	}
	else if(cmd.isCommand(DEV_toTitleCase)) {
		cout <<  StrUtil::toTitleCase(cmd.getToken(1)) <<endl;
	}
}

void UI::printError(string err){
	cout << "ERROR: " << err << endl;
}

void UI::printOutput(string outStr){
	//public method that can be used by clients of UI to
	//print to UI output
	//If logging is in progress the output will be written
	//to the log file as well.
	if(logging == OUTPUT || logging == BOTH) logs.push_back(outStr);
	cout << outStr << endl;
}

void UI::printMessage(string msg){
	cout << "MESSAGE: " << msg << endl;
}


void UI::promptForStr(string prompt, string& str){
	cout << prompt << ": ";
	getline(cin, str);
}

void UI::pause(){
	string str;
	cout << endl << "\nPress enter to continue...";
	getline(cin, str);
}

//EXECUTE UI COMMANDS
void UI::executeUIREAD(Command cmd){
	//printOutput("EXECUTING: UICMD_READ:" + cmd.getCommandString());
	//Read a script file of commands one line at at time
	//and execute each line as a command

	enum arguments {READ,FILENAME}; //.read file_name
	string scriptFileName = cmd.getToken(FILENAME);
	ifstream file(scriptFileName, ifstream::in);
	if(!file){
		printError(".read Could Not Open File: " + scriptFileName);
		return;
	}
	string input;
	while(getline(file, input)){
		if(StrUtil::trim(input).empty()) {/*do nothing*/}
		else if(StrUtil::isComment(input)) {
			/*do nothing*/
			if(logging != OFF) logs.push_back(StrUtil::trim(input));
			printOutput(input); //write comment to output
		}
		else {
			Command cmd = Command(input);

			if(cmd.isUICommand()) executeCommand(cmd);
			else if(cmd.isAppCommand()) owner->executeCommand(cmd);
			else if(cmd.isDevCommand()) executeDevCommand(cmd);
			else printError("UNRECOGNIZED COMMAND");
		}
	}
	file.close();
}
void UI::executeUILOG(Command cmd){
	/*
	.log    //log commands and output
	.log clear //clear the logs
	.log start //begin logging
	.log start_both //begin logging both commands and output
	.log stop //stop logging
	.log save filename //save log to filename
	.log show //display current log contents on console
	*/
	enum arguments {LOG, OPERATION, FILENAME};
	if(cmd.getToken(OPERATION).compare("clear")==0){logs.clear();}
	else if(cmd.getToken(OPERATION).compare("start")==0){logging=COMMAND;}
	else if(cmd.getToken(OPERATION).compare("start_output")==0){logging=OUTPUT;}
	else if(cmd.getToken(OPERATION).compare("start_both")==0){logging=BOTH;}
	else if(cmd.getToken(OPERATION).compare("stop")==0){logging=OFF;}
	else if(cmd.getToken(OPERATION).compare("show")==0){
		//show logs on console
		cout << "//LOGS-----------------------------" << endl;
		for(int i=0; i<logs.size(); i++)
		cout << (logs[i]) << endl;
		cout << "-----------------------------------" << endl;
	}
	else if(cmd.getToken(OPERATION).compare("save")==0){
		//save log to file
		string logFileName = cmd.getToken(FILENAME);
		ofstream file(logFileName, ofstream::out);
		if(!file) {
			printError("Could not open log file: " + logFileName);
			return;
		}
		for(int i=0; i<logs.size(); i++)
		file << logs[i] << endl;
		file.close();
	}
}
void UI::executeUIHELP(Command cmd){
	//show help menu on console
	printOutput("EXECUTING: UICMD_HELP:" + cmd.getCommandString());
	ifstream file(HELP_FILE_NAME, ifstream::in);
	if(!file){
		printError("Could Not Open Helpfile: " + HELP_FILE_NAME);
		return;
	}
	string input;
	while(getline(file, input)){
		printOutput(input);
	}
	file.close();
}

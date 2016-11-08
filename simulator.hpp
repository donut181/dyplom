#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP
#include<sys/types.h>
#include<sys/stat.h>
#include<string>
#include<cstdio>
#include<vector>
#include<signal.h>
#include<unistd.h>
#include<iostream>

class Simulator{
	private:
		pid_t pid;
		pid_t sid;
		std::string programName;
		std::string _stdout;
		std::string _stdin;
		std::string _stderr;
		std::vector<std::string> flags;
		std::vector<char*> cFlags;
	public:
		Simulator();
		void setCommand(std::string program = "Sleeper.sh");
		void data();
		void start();
		void kill();
};
#endif

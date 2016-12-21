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
		std::string _command;
		std::string _stdout;
		std::string _stdin;
		std::string _stderr;
		std::vector<std::string> flags;
		std::vector<char*> cFlags;
	public:
		Simulator();
		void setCommand(std::string command);
		void print_data();
		void start();
		void kill();
		void setOut(std::string out);
};
#endif

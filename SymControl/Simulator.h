#ifndef SIMULATOR_H
#define SIMULATOR_H

#include<sys/types.h>
#include<sys/stat.h>
#include<string>
#include<cstdio>
#include<vector>
#include<signal.h>
#include<unistd.h>
#include<iostream>
#include<QString>

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
        Simulator(QString workspace_path);
        void setCommand(std::string program = "Sleeper.sh");
        void addFlag(std::string flag);
        std::string command()const;
        std::string firstFlag()const;
        void data();
        void start();
        void kill();
};
#endif // SIMULATOR_H

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
#include<QDebug>
#include<Config.h>

class Simulator{
    private:
        Simulator();

        pid_t pid;
        pid_t sid;
        std::string programName;
        std::string _stdout;
        std::string _stdin;
        std::string _stderr;
        std::vector<std::string> flags;
        std::vector<char*> cFlags;
        QString m_state;
        QString m_progress;
        QString m_workspace;
        QString m_stateFile = "state";

        void setState(QString);
        void getState();
        void start();
        void setCommand(std::string);
        void prepareCommand();
        void write_pid_to_file();
        void get_progress();
public:
        Simulator(QString workspace_path,QString uuid);
        void addFlag(std::string flag);
        void data();
        void refresh_state();
        //void kill();

        QString m_uuid;
};
#endif // SIMULATOR_H

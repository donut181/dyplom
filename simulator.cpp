#include"simulator.hpp"

Simulator::Simulator(){
	std::cout << "Simulator created" << std::endl;
	_stdout = "/dev/null";
	_stdin = "/dev/null";
	_stderr = "/dev/null";
}

void Simulator::setCommand(std::string command){
	_command = command;
	//adding flag 0 -> name of program
	flags.push_back(_command.substr(_command.find_last_of('/')+1));
}

void Simulator::print_data(){
	std::cout << "Program: " << _command
		<< " pid: " << pid << std::endl
		<< "out:" << _stdout
		<< " in :" << _stdin
		<< " err:" << _stderr
		<< std::endl<<std::endl;
}

void Simulator::start(){
	if(_command.empty() || _stdin.empty() || _stdout.empty() || _stderr.empty()){
		std::cout << "cant start new process, no name,stdin,stdout or stderr" << std::endl;
	}else{
		pid = fork();
		if(pid == 0){//only for child
			
			//steps to daemonize
			//1.changing file mode mask
			umask(0);

			//2.creatin SID for child process
			sid = setsid();
			if (sid<0){
				//error
				std::cout << "error with setsid" << std::endl;
			}

			//3.changing dir so current wont be locked
			if((chdir("/")) < 0){
				std::cout << "error with chdir" << std::endl;
			}

			//4.redirect stdio [e.g. to null]
			freopen(_stdin.c_str(),"r",stdin);
			freopen(_stdout.c_str(),"w",stdout);
			freopen(_stderr.c_str(),"w",stderr);

			//and now exec sth
			for(size_t i=0; i<flags.size(); ++i)
				cFlags.push_back(const_cast<char*>(flags[i].c_str()));
			cFlags.push_back(NULL);

			if(execvp(_command.c_str(), &cFlags[0]) == -1){
				std::cout<< "execvp failed" << std::endl;
			}
			

		}else if(pid <0){
			//error
			std::cout << "error during fork() " << std::endl;
		}else{
			std::cout << "child process has started" << std::endl;
		}
	}
}

void Simulator::kill(){
	::kill(pid,SIGTERM);
}

void Simulator::setOut(std::string out){
	_stdout = out;
}

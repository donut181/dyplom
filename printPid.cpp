#include<iostream>
#include"simulator.hpp"
#include<unistd.h>
#include<string>
#include<vector>

//		execvp(program, arg_list);
//		std::cout << "error from execvp" << std::endl;

int main(){
   	Simulator sim;
  	sim.setCommand("./sleeper.sh");
  	sim.data();
  	sim.start();
  	sim.data();
	sleep(5);
	sim.kill();

 	return 0;
}

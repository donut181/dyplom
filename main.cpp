#include<iostream>
#include"simulator.hpp"
#include<unistd.h>
#include<string>
#include<vector>

int main(){
   	Simulator sim;
  	sim.setCommand("/home/marcin/cpp/sleeper.sh");
	sim.setOut("/home/marcin/cpp/output.txt");
  	sim.print_data();
  	sim.start();
  	sim.print_data();
	sleep(5);
	sim.kill();

 	return 0;
}

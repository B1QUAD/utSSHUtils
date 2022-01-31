#include "nlohmann/json.hpp"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "main.h"

using json = nlohmann::json;



int main (void) {
	json conf = readFile("user-config.json"); 
	// std::cout << conf.dump(4) << std::endl;
	int selection = serverPrompt(conf);

	std::stringstream sshCmd;
	sshCmd << "ssh " <<  
			   conf["uname"] <<
			   "@" <<
			   conf["server-list"][selection] <<
			   conf["base-URL"] <<
			   " -p " << 
			   conf["port"];
	
	system(sshCmd.str().c_str());
	return 0;
}

int serverPrompt (json input) {
	system("clear");
	std::cout << "Plese select a server from the below list:" << std::endl;
	
	int serverListLength = input["server-list"].size();

	for (int i = 0; i < serverListLength; i++) {
		std::cout << i << ": " << input["server-list"][i] << std::endl;
	}

	int userInput = 0, inputValid = 0;

	while (!inputValid) {
		std::cout << "> ";
		std::cin >> userInput;
		// std::cout << std::endl;
		if (userInput >= 0 && userInput <= serverListLength)
		   inputValid = 1;
		else
			std::cout << "Invalid input" << std::endl;	
	}

	return userInput;
}	

json readFile(std::string fileName) {
	std::ifstream i(fileName);
	json j;

	i >> j;
	return j;
}


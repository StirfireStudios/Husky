//
//  main.cpp
//  dummyTest
//
//  Created by Brendan Ragan on 19/12/13.
//  Copyright (c) 2013 Stirfire Studios. All rights reserved.
//

#include <iostream>
#include "HuskyLoader.h"

class TestObserver : public HuskyObserver {
	void setAchievementCallback(char *name, bool success);
};

void TestObserver::setAchievementCallback(char *name, bool success) {
	if (success) {
		std::cout << "Achievement " << name << " set successfully!" << std::endl;
	} else {
		std::cout << "Achievement " << name << " could not be set :(" << std::endl;
	}
}


int main(int argc, const char * argv[]) {
	HuskyLoader *loader = HuskyLoader::getInstance();
	unsigned long huskies = loader->scanForHuskies();
	std::cout << "Found " << huskies << " Huskies " << std::endl;
	for(int i = 0; i < huskies; i++) {
		std::cout << "Husky " << i << " is for: " << loader->getHuskyName(i) << std::endl;
	}
		
	Husky *husky = loader->getHuskyInstance((char*)"Dummy");
	
	std::cout << "Trying to set an achievement" << std::endl;
	husky->setAchievement((char*)"Test Achievement");

	std::cout << "Trying to set an achievement with an observer." << std::endl;
	TestObserver* observer = new TestObserver();
	husky->setObserver(observer);
	husky->setAchievement((char*)"Test Achievement");
	husky->setAchievement((char*)"Failed Achievement");
	std::cout << "Observer should have generated output above" << std::endl;
	
    return 0;
}


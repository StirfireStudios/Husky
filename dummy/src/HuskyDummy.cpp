//
//  HuskyDummy.cpp
//  dummy
//
//  Created by Brendan Ragan on 19/12/13.
//  Copyright (c) 2013 Stirfire Studios. All rights reserved.
//

#include "HuskyDummy.h"

#define EXPORT __attribute__((visibility("default")))

HuskyDummy* HuskyDummy::instance;

EXPORT
HuskyDummy::HuskyDummy() {
	_observer = NULL;
}

EXPORT
HuskyDummy::~HuskyDummy() {
}

EXPORT
HuskyDummy* HuskyDummy::getInstance() {
	if(!instance) {
		instance = new HuskyDummy();
	}
	return instance;
}

EXPORT
void HuskyDummy::setObserver(HuskyObserver *observer) {
	_observer = observer;
}

EXPORT
void HuskyDummy::setAchievement(const char *name) {
	if (_observer != NULL) {
		if (strcmp(name, "Failed Achievement") == 0) {
			std::cout << "Dummy Husky: Failed Achievement used, sending failure callback: " << std::endl;
			_observer->HuskyObserverAchievementCallback(name, false);
		} else {
			std::cout << "Dummy Husky: sending success callback for " << name << std::endl;
			_observer->HuskyObserverAchievementCallback(name, true);
		}
	} else {
		std::cout << "Dummy Husky: Setting Achievement Earned: " << name << std::endl;
	}
}

EXPORT
Husky *getHuskyInstance() {
	return HuskyDummy::getInstance();
}

EXPORT
char *getHuskyName() {
	return (char*)"Dummy";
}
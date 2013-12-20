//
//  HuskyDummy.h
//  dummy
//
//  Created by Brendan Ragan on 19/12/13.
//  Copyright (c) 2013 Stirfire Studios. All rights reserved.
//

#ifndef __dummy__HuskyDummy__
#define __dummy__HuskyDummy__

#include <iostream>
#include "Husky.h"


class HuskyDummy : public Husky {
public:
	/** Get a handle to the husky singleton **/
	static HuskyDummy* getInstance();
	
	/** Returns the name of the Husky **/
	static char* getName();
	
	void setObserver(HuskyObserver* observer);
	
	/** Try and set the achievement with this name. Will return a setAchievementCallback if an observer is set.
		If an observer is set and an achievement called "Failed Achievement" is set, the observer will get a failed callback
	 **/
	void setAchievement(char* name);
	
private:
	static HuskyDummy* instance;
	
	HuskyDummy();
	~HuskyDummy();
	
	HuskyObserver* _observer;
	
};

#endif /* defined(__dummy__HuskyDummy__) */

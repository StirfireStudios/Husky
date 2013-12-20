//
//  Husky.h
//  dummy
//
//  Created by Brendan Ragan on 19/12/13.
//  Copyright (c) 2013 Stirfire Studios. All rights reserved.
//

#ifndef dummy_Husky_h
#define dummy_Husky_h

/** Observers for Husky callbacks **/
class HuskyObserver {
public:
	virtual void HuskyObserverAchievementCallback(const char *name, bool success) = 0;
};


class Husky {
public:
	/** Get a handle to the husky singleton **/
	static Husky* getInstance();
	
	virtual void setObserver(HuskyObserver *observer) = 0;

	/** Try and set the achievement with this name. Will return a setAchievementCallback if an observer is set **/
	virtual void setAchievement(const char *name) = 0;
};


extern "C" Husky* getHuskyInstance();
typedef Husky* HuskyGetStaticInstance();
extern "C" char *getHuskyName();
typedef char* HuskyGetName();

#endif

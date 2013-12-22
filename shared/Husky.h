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
	
	virtual void HuskyObserverLeaderboardScoreSetCallback(const char *name, bool success) = 0;
};

/** Leaderboard Timeframes **/
enum {
	HuskyLeaderboardTodaysScores = 0,
	HuskyLeaderboardWeeksScores,
	HuskyLeaderboardAllScores
};

typedef unsigned short HuskyLeaderboardScoreTimeFrame;

class Husky {
public:
	/** Get a handle to the husky singleton **/
	static Husky *getInstance();
	
	/** Perform any shutdown required for this husky **/
	static void shutdownInstance();
	
	virtual void setObserver(HuskyObserver *observer) = 0;

	/** Try and set the achievement with this name. Will return a setAchievementCallback if an observer is set **/
	virtual void setAchievement(const char *name) = 0;
	
	/** resets users's achievements and stats data **/
	virtual void resetAchievements() = 0;
	
	/** uploads a score to the specified leaderboard **/
	virtual void uploadLeaderboardScore(const char *name, int32 score) = 0;

	/** requests a set of scores from this leaderboard **/
	/** friends = request only scores that the user is friends with **/
	/** timeframe = the timeframe to request scores in **/
	/** offset = the start offset of scores to request **/
	/** number = the number of scores to request **/
	virtual void requestLeaderboardScores(const char *name, bool friends, HuskyLeaderboardScoreTimeFrame timeframe, int offset, int number) = 0;

	/** requests a set of scores from this leaderboard around the player **/
	/** same parameters as above, but offset 0 is the player's current score on this board */
	/** so offset = -3, would request scores 3 ranks above the player **/
	virtual void requestLeaderboardScoresNearPlayer(const char *name, bool friends, HuskyLeaderboardScoreTimeFrame timeframe, int offset, int number) = 0;
};


extern "C" Husky* getHuskyInstance();
typedef Husky* HuskyGetStaticInstance();
extern "C" void shutdownHuskyInstance();
typedef void HuskyShutdownStaticInstance();
extern "C" char *getHuskyName();
typedef char* HuskyGetName();

#endif

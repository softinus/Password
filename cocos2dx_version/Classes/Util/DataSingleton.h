#pragma once
#include "cocos2d.h"
class DataSingleton {
private:
	DataSingleton();
	DataSingleton(const DataSingleton& other);
	~DataSingleton();
	static DataSingleton inst;
public:
	static DataSingleton& getInstance() { return inst; }

	int nLevel;

	//int nSpentTime;
	std::string strSpentTime;
	
	int nSpentCount;

	// 인게임 -> 결과창 
	bool bClear;
	int nStageRepeatCount;
	int nLeftLife;

	// 결과창 -> 스테이지 선택
	int nCleardStage;
	bool bNewRanked;
};
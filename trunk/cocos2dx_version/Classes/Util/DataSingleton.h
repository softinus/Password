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

	// stage select -> ingame
	int nPlayMode;	// save current page in select stage scene
	int nLevel;

	
	//std::string strSpentTime;
	

	// �ΰ��� -> ���â 
	bool bClear;
	int nStageRepeatCount;
	int nLeftLife;
	int nSpentTime;
	int nSpentCount;

	// ���â -> �������� ����
	int nCleardStage;
	bool bNewRanked;

};
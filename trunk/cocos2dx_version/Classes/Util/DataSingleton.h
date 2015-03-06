#pragma once
class DataSingleton {
private:
	DataSingleton();
	DataSingleton(const DataSingleton& other);
	~DataSingleton();
	static DataSingleton inst;
public:
	static DataSingleton& getInstance() { return inst; }

	int nLevel;

	int nSpentTime;
	int nSpentCount;

	bool bClear;
	int nStageRepeatCount;
	int nLeftLife;
};
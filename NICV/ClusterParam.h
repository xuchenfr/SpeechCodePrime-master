#ifndef	ZHOULU_CLT_PERAMETER_H
#define	ZHOULU_CLT_PERAMETER_H

#include <string>
#include <vector>

class CSpeechFile {
	friend class ClusterParam;

private:
	std::string featureFile;

	std::string maskFile;

	std::string answerFile;

public:
	std::string getFeatureFileName() {
		return featureFile;
	}

	std::string getMaskFileName() {
		return maskFile;
	}

	std::string getAnswerFileName() {
		return answerFile;
	}

};

class ClusterParam {
private:
	int fileNum;//�ļ�����

	int fDim;//ά��

	double rate;//DTW ѹ����rate

	double threshold;//NICV ����

	std::string saveDir;//�����·��

	bool useDTW;//�Ƿ�ʹ��DTW

	bool useNICV;//�Ƿ�ʹ��NICV

	bool useHalfLen;//�Ƿ�ʹ�ð�֡��

	std::vector<CSpeechFile> fileSets;

	void checkExist(const char* str);

	void checkExist(const std::string& str);

	void trim(std::string& s);

public:
	ClusterParam(const char* filename);

	int getFileNum();//

	std::vector<CSpeechFile> getClusterFiles();

	std::string getSaveDir();

	int getFdim();

	bool getDTWflag();

	bool getHalfLen();

	bool getNICVflag();

	double getRate();

	double getThres();
};

#endif
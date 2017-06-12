#ifndef	WJQ_FEATURE_READER_H
#define	WJQ_FEATURE_READER_H

#include <stdio.h>
#include <string>
#include <vector>
struct FeatureIndex {
	long	offset;
	long	byteSize;
};

struct MaskIndex {
	long	offset;
	long	endpointNum;
};
struct ClusterIndex {
	long	offset;
	long	ClusterNum;
};
struct SegPointIndex{
	long	offset;
	long	SegPtNum;
};

struct AnswerIndex{
	long	offset;
	long	wordNum;
};

class FeatureFileSet {
private:

	char* featureFileBuf;

	char* maskFileBuf;

	char* answerFileBuf;

	int speechNum;

	int featureDim;

	std::vector<SegPointIndex>SegPtList;
	std::vector<std::vector<int>>SegmentpoitData;

public:
	FeatureFileSet(const std::string& featureFileName, const std::string& maskFileName, const std::string& answerFileName, int featureDim);

	int fileByteNum(FILE* f);

	int getSpeechNum();

	void printFeatureFileToTxt(const char * filename);

	//��ȡ֡��������
	void getSpeechAt(int speechIdx, double* outputBuffer);

	//��ȡ֡��
	int getFrameNumInSpeech(int speechIdx);

	//��ȡ������
	int getWordNumInSpeech(int speechIdx);

	//��ȡ��֡��������
	void getMultiSpeechAt(int speechIdx, double* outputBuffer);

	//��ȡ�𰸱�
	void getWordListInSpeech(int speechIdx, int* outputWordList);

	//����ָ��
	void SaveSegmentPointToBuf(int speechIdx, std::vector<int> &res);

	void PrintSegmentPointBuf(std::string fileName);

	//������������ε���Ϣ
	void getMaskData(int* buffer, const int& speechIdx);

	//��ȡ����mask��֡��
	int getPrimeFrameLen(const int& speechIdx);

	void getPrimeSpeechAt(int speechIdx, double* outputBuffer);

	int getMaskLen(const int& speechIdx);

	~FeatureFileSet();

	//��ȡ5ms֡�Ƶ�����ʸ��
	void getSpeechAt_half_framelen(int speechIdx, double* outputBuffer, int e);
	
	//��ȡ5ms֡�Ƶ�֡��
	int getFrameNumInSpeech_half_framelen(int speechIdx);
};


#endif
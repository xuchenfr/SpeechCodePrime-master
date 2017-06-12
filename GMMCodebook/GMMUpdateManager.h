#ifndef WJQ_GMM_UPDATE_MANAGER_H
#define WJQ_GMM_UPDATE_MANAGER_H

#include "GMMEstimator.h"
#include "../CommonLib/Dict/WordDict.h"
#include "GMMCodebookSet.h"
#include "FrameWarehouse.h"
#include "string"
#include "../SpeechSegmentAlgorithm/SegmentAlgorithm.h"

class SegmentResult;
class GMMUpdateManager {
private:

	GMMCodebookSet* codebooks;

	GMMEstimator* estimator;

	double* firstMoment;

	double* secondMoment;

	double* firstMomentOfLog;

	int* successUpdateTime;

	int updateIter;

	int* durCnt;

	bool useSegmentModel;

	bool m_bCuda;

	WordDict* dict;

	double minDurVar;

	FrameWarehouse* fw;

	GMMProbBatchCalc* gbc;

	FILE* logFile;

public:

	GMMUpdateManager(GMMCodebookSet* codebooks, int maxIter, WordDict* dict, double minDurSigma, const char* logFileName, bool useCuda, bool useSegmentModel);

	//����ֵ��ʾִ���걾�κ������ۻ���ȫ���뱾����֡��
	int collect(const std::vector<int>& frameLabel, double* frames, bool bCollectFrame = true,int* clusterInfo = nullptr);

	//��ȡ�뱾��
	int getUaCbnum(){return codebooks->CodebookNum;}

	//����ֵΪ����Ϊcbnum��vector��vector��ÿ��Ԫ�ش�����Ӧ���뱾�ĸ��½��
	std::vector<int> update();

	//��ȡFrameWareHouseָ��
	FrameWarehouse* getFW(){return fw;}

	//��ȡ״̬idx�ĳɹ����´���
	int getSuccessUpdateTime(int cbidx) const;

	//���ⲿ����GBC
	void setGBC(GMMProbBatchCalc* pGbc){
		gbc = pGbc;
	}
	//����ǰ���֡��ȫ���뱾��֡��
	int collectMultiFrames(const std::vector<int>& frameLabel, double* multiframes);

	//����Kerasѵ��DNN
	void trainKerasNN(bool bMakeNewModel, std::string ot, std::string it);

	~GMMUpdateManager();

	//�ܽ�ѵ�����
	void summaryUpdateRes(const vector<int>& r, FILE* fid, int iterNum);
};

#endif
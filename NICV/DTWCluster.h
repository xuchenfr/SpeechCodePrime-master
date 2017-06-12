#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class DTWCluster
{
public:
	DTWCluster(int x){
		m_nFDim = x;
	}
	~DTWCluster();

	//�������֡����������
	double doCluster(double* fts, const int& frameLen, int flag = RANDOM_CENTER, const int* jumpTable = NULL, const int& segNum = 0);

	//��ʼ���������͵��������Լ�ά��
	void init(const int & clusterNum, const int& iterNum, const int&fdim);


	//ͨ��ǰ��֡��ľ����ʼ����������ʼ����֡���С����С��һ���������ж�Ϊ���Ծ���
	float initDistance(double* fts, const int&fdim, const int& frameLen, const double& thes);

	//���������n����outLen���ȵ� ���ظ���������С�
	//�������5��outlen��3�������Ŀ�����1��2��5
	void getUnrepRandomList(int* outVect, const int &n, const int &outLen);
	
	//��ȡ������Ϣ
	vector<int> getClusterInfo(const int& flag= MEAN_CENTER);

	//��ȡ�ڽӾ���
	double calcAdjionDistance();
	static const int MEAN_CENTER = 0;
	static const int FIRST_CENTER = 1;
	static const int MIDDLE_CENTER = 2;
	static const int RIGHT_CENTER = 3;
	static const int RANDOM_CENTER = 4;
	static const int MEDOIDS_CENTER = 5;
private:
	int m_nFDim;
	// ��������ά��
	int m_nIterNum;
	// ��������
	int m_nFrameLen;
	// ֡��
	int m_nClusterNum;
	// ����֡��

	double* m_pFeatures;
	// ������������ָ��
	double* m_pCenters;
	// ������������ָ��
	vector<double> m_vecDistances;
	// DTW�ľ�������
	vector<int> m_vecSimplePointCenters;
	// �������ģ�ûɶ�ã���λ�ã�����MEdoids�㷨��ʱ���õģ�kmeans���� 
	vector<int> m_vecSegInfo;
	// ����ֶ���Ϣ
	vector<vector<int>>m_HistoryMap;
	// ��ʷ·������

	void calcCenters(double* fts, bool bInit, int flag);
	double calcDistance(double* ft, const int& idx, bool d15 = true);
	double calcDistance(double* ft, double* ft2, bool d15= true);
	double calcBCdistance();
	double getWCdistance(double* features);
	int getClusterIdx(int& idx);


};


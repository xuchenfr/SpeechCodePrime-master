#include "CmdWordRecg.h"
#include "../CommonLib/FileFormat/CWaveFormatFile.h"
#include "../VAD/VAD.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <conio.h>
using namespace std;

vector<string> readRecList(string filename) {
	vector<string> r;

	ifstream infile(filename);
	string t;
	while (infile >> t) {
		r.push_back(t);
	}
	infile.close();
	return r;
}

void saveBinData(const char* filename, short* buf, int n) {
	FILE* fid = fopen(filename, "wb");
	if (!fid) {
		printf("cannot open file [%s]\n", filename);
		exit(-1);
	}
	fwrite(buf, sizeof(short), n, fid);
	fclose(fid);
	return;
}

long DoRecg(void* pInfo, short* SpeechBuf, long DataNum) {

	printf("��⵽��������ʼ����ʶ�𣮣���\n");
	CmdWordRecg* r = (CmdWordRecg*)pInfo;
	
	saveBinData("test.fm",SpeechBuf,DataNum);
	CmdRecgResult res = r->cmdRecg(SpeechBuf, DataNum);
	printf("%d\n", res.rank[0]);

	return 0;
}


int main() {
	//���������ļ�·��
	const char* cbfile = "D:/MyCodes/DDBHMMTasks/codebooks/all_codebook/full_8mix.cb";
	const char* dictfile = "../DictConfig/worddict.txt";
	const char* cmdwordfile = "cmdword.txt";
	//��ʼ����
	double durWeight = 0;
	bool useCuda = false;
	bool useSegmentModel = false;
	//�½������ʶ����
	CmdWordRecg* rec = new CmdWordRecg(cmdwordfile, cbfile, dictfile, durWeight, useCuda, useSegmentModel);
	//����VAD�������м��ʶ��
	CVAD* vad = new CVAD();
	vad->IniClass(rec);
	vad->SetRecgCallback(DoRecg);

	::fflush(stdin);
	while( _kbhit() == 0 ) {
		vad->WaitForSpeechDetected();
	}

	delete vad;
	delete rec;


	return 0;
}
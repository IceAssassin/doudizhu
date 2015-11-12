//��������Ϸ����
#pragma once

#include "Global.h"
#include <vector>
using namespace  std;

struct PkStruct //�� ���� ��С
{
	int pk_type;
	int pk_num;
};

class Rule 
{
public:
	Rule();
	~Rule();
	void InitPks();//��ʼ��
	void Shuffle();//ϴ��
	void SelectShort(PkStruct* pData,int count);
	int Call(int index);//����npc�ǵڼ���
	int Plane(PkStruct* pData,int count);
	int Bomb(PkStruct* pData,int count);
	int GetCallBigPks(PkStruct* pData,int count);//��ȡ����2�Ľ��Ʒ���
	public:
	 PkStruct pks[54];
	 PkStruct pks_player[17];
	 PkStruct pks_npc1[17];
	 PkStruct pks_npc2[17];
};

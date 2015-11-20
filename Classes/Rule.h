//��������Ϸ����
#pragma once

#include "cocos2d.h"

#include "Global.h"
#include <vector>

USING_NS_CC;
using namespace  std;

struct PkHandleTypeStruct//��������
{
	CARD_TYPE type;
	std::vector<PkStruct> pk_structs;
};

class Rule 
{
public:
	Rule();
	~Rule();

	void InitPks();//��ʼ��
	void Shuffle();//ϴ��
	void GiveDizhuPks(int type);//������

	int Call(int index);//����npc�ǵڼ���
	void AiSplitPks(int type);//��������
	
private:
	int Plane(vector<PkStruct> pData);//�ɻ���1����0
	int Bomb(vector<PkStruct> pData);//ը���м���
	int GetCallBigPks(vector<PkStruct> pData);//��ȡ����2�Ľ��Ʒ���
	static bool SelectShort(const PkStruct& p1,const PkStruct& p2);

	std::vector<PkStruct> AiThreePks(vector<PkHandleTypeStruct> vec_pk_handle_struct_,std::vector<PkStruct> &vec_pks);//��ȡ��˳
	std::vector<PkStruct> AiSingleShunzhi(std::vector<PkStruct> &vec_pks);//��ȡ˳��
	std::vector<PkStruct> AiDouble(std::vector<PkStruct> &vec_pks);//��ȡ����
	void AiSingle(std::vector<PkStruct> &vec_pks);//���ƻ�ȡ

public:
	PkStruct pks[54];
	std::vector<PkStruct> pks_player;
	std::vector<PkStruct> pks_npc1;
	std::vector<PkStruct> pks_npc2;
	std::vector<PkStruct> pks_three;
	std::vector<PkHandleTypeStruct> vec_pk_hand_type_struct;//�����������
};

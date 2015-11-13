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
	
	int Call(int index);//����npc�ǵڼ���
	int Plane(vector<PkStruct> pData);//�ɻ���1����0
	int Bomb(vector<PkStruct> pData);//ը���м���
	int GetCallBigPks(vector<PkStruct> pData);//��ȡ����2�Ľ��Ʒ���
	static bool SelectShort(const PkStruct& p1,const PkStruct& p2);
	void AiSplitPks(std::vector<PkStruct> &pks);//�ڼ������
	void AiThreePks(std::vector<PkHandleTypeStruct> vec_pk_hand_type_struct_buff);//��ȡ��˳


	bool IsPlane(CCArray *arr);//�Ƿ�Ϊ�ɻ�
	bool IsBomb(CCArray *arr);//�Ƿ�Ϊը��
	bool IsDouble(CCArray *arr);//�Ƿ�Ϊ˫
	bool IsThreePk(CCArray *arr);//����
	bool IsThreePkAddOne(CCArray *arr);//����һ
	bool IsSingleShunzhi(CCArray *arr);//��˳
	bool IsDoubleShunzhi(CCArray *arr);//˫˳
	bool IsThreeShunzhi(CCArray *arr);//��˳
	bool IsPlaneAddWings(CCArray *arr);//�ɻ������
	bool BombAddTwo(CCArray *arr);//�Ĵ�2

	public:
	 PkStruct pks[54];
	 std::vector<PkStruct> pks_player;
	 std::vector<PkStruct> pks_npc1;
	 std::vector<PkStruct> pks_npc2;
	 std::vector<PkHandleTypeStruct> vec_pk_hand_type_struct;
};

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

	public:
	 PkStruct pks[54];
};

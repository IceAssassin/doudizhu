#include "Rule.h"
#include <stdlib.h>
#include <ctime>

Rule::Rule(){

}

Rule::~Rule(){

}
void Rule::InitPks(){
	for (int i=0;i<4;++i){
		for (int j=0;j<13;++j){
			pks[i*13+j].pk_type = i;
			pks[i*13+j].pk_num = j;
		}
	}

	pks[52].pk_type = Joker;
	pks[52].pk_num = BlackJoker;

	pks[53].pk_type = Joker;
	pks[53].pk_num = RedJoker;
}

void Rule::Shuffle(){
	srand(unsigned(time(0)));
	for (int i=0;i<54;i++){
		int a = rand()%54;
		int b = rand()%54;
		swap(pks[a],pks[b]);
	}

	const int pk_num = 17;
	PkStruct buff;
	for (int i=0;i<51;i++)
	{
		int index = i%pk_num;
		int witch_player = i/pk_num;

		buff.pk_type = pks[index].pk_type;
		buff.pk_num = pks[index].pk_num;

		if (witch_player == 0)
			pks_player.push_back(buff);
		
		if (witch_player == 1)
			pks_npc1.push_back(buff);

		if (witch_player == 2)
			pks_npc2.push_back(buff);
	}
}

bool Rule::SelectShort(const PkStruct& p1,const PkStruct& p2){
	return p1.pk_num > p2.pk_num;
}

int Rule::Plane(vector<PkStruct> pData){
	if ( pData[0].pk_num == RedJoker  && pData[1].pk_num == BlackJoker)
	{
		return 1;
	}
	return 0;
}

int Rule::Bomb(vector<PkStruct> pData){
	int count = pData.size();
	int bomb_num = 0;
	int pk_num1 = 0;//�Ƶĸ���
	int pk_num2 = 0;//�Ƶķ���
	for (int i = 0; i < count; i++){
		int buff = pData[i].pk_num;
		if (buff != pk_num2){
			pk_num2 = buff;
		}else{
			pk_num1+=1;
			if (pk_num1 == 4)
			{
				bomb_num+=1;
			}
		}
	}
	return bomb_num;
}

/*
����4�֣�С��3�֣�һ��2Ϊ2��
*/
int Rule::GetCallBigPks(vector<PkStruct> pData){
	int score = 0;
	int count = pData.size();
	for (int i=0;i<count;i++){
		if (pData[i].pk_num == RedJoker){
			score += 4;
		}
		if (pData[i].pk_num == BlackJoker){
			score += 3;
		}
		if (pData[i].pk_num == Er){
			score += 2;
		}
	}
	return score;
}

/*
�ٶ����Ϊ8�֣�ը��Ϊ6�֣�����4�֣�С��3�֣�һ��2Ϊ2�֣��򵱷���
���ڵ���7��ʱ��������
���ڵ���5��ʱ�ж�����
���ڵ���3��ʱ��һ����
С�����ֲ��С�
*/
int Rule::Call(int index){ //�е������� index 0,1,2 ��� npc1,npc2
	int plane_num = 0;
	int bomb_num = 0;
	int extra_num = 0;

	int double_one = 1;
	int double_two = 2;
	int double_three = 3;
	if (index == 0){
		sort(pks_player.begin(),pks_player.end(),Rule::SelectShort);
		plane_num = Plane(pks_player);
		bomb_num = Bomb(pks_player); 
		extra_num = GetCallBigPks(pks_player);
	}

	if (index == 1){
		sort(pks_npc1.begin(),pks_npc1.end(),Rule::SelectShort);
		plane_num = Plane(pks_npc1);
		bomb_num = Bomb(pks_npc1); 
		extra_num = GetCallBigPks(pks_npc1);
	}

	if (index == 2){
		sort(pks_npc2.begin(),pks_npc2.end(),Rule::SelectShort);
		plane_num = Plane(pks_npc2);
		bomb_num = Bomb(pks_npc2); 
		extra_num = GetCallBigPks(pks_npc2);
	}

	int total_score = plane_num*7 + bomb_num*6 + extra_num;
	if (total_score >= 17)
		return double_three;
	else if (total_score >= 15)
		return double_two;
	else if (total_score >= 13)
		return double_one;
	else
	return 0;
}

void Rule::AiSplitPks(std::vector<PkStruct> &pks){ //0 1 2 ��� npc1 npc2 
	//����
	sort(pks.begin(),pks.end(),Rule::SelectShort);
	PkHandleTypeStruct pk_handle_typestruct;
	
	//��ȡ˫��
	if (pks[0].pk_type == Joker && pks[1].pk_type == Joker){	
		 pk_handle_typestruct.type = PLANE_PK;
		 pk_handle_typestruct.pk_structs.push_back(pks[0]);
		 pk_handle_typestruct.pk_structs.push_back(pks[1]);
		 vec_pk_hand_type_struct.push_back(pk_handle_typestruct);
	}

	//��������
	 vector<PkStruct>::iterator iter;  
	 vector<PkStruct>::iterator iter_next;  
	 std::vector<PkHandleTypeStruct> vec_pk_hand_type_struct_buff;
	for (iter=pks.begin();iter!=pks.end();iter++) {
		for (iter_next=iter; iter_next != pks.end();iter_next++){
			if (iter->pk_num == iter_next->pk_num){
				++iter;
				pk_handle_typestruct.pk_structs.push_back(*iter);
			}
		}

		if (pk_handle_typestruct.pk_structs.size() == 4){//��ȡը��
			pk_handle_typestruct.type = BOMB_PK;
			vec_pk_hand_type_struct.push_back(pk_handle_typestruct);
			break;
		}
		if (pk_handle_typestruct.pk_structs.size() == 3)
			pk_handle_typestruct.type = THREE_NO_ADD_PK;
		if (pk_handle_typestruct.pk_structs.size() == 2)
			pk_handle_typestruct.type = DOUBLE_PK;
		if (pk_handle_typestruct.pk_structs.size() == 1)
			pk_handle_typestruct.type = SINGLE_PK;

		vec_pk_hand_type_struct_buff.push_back(pk_handle_typestruct);
	}

	//�Ʒ���
	//a) ��ȷ��������ж��Ƿ��д�С����
	//b) ��ȷ��ը���������Ƿ�����ͷ��
	//c) ��ȷ���������ڳ���ը������������ж��Ƿ����������
	//d) ��ȷ����˳�����Ѿ�ȷ�����������ж��Ƿ�������ڵ�����������У����������˳��ע�⣬Ӧ��ʹ��˳�����������ܴ󡣼������444555666������ϳ�һ����˳�������Ƿֳ�444555һ����˳��666һ��������
	//e) ��ȷ����˳���жϵ�˳ʱ����ȥ���ĸ�2���������ը���������ж��Ƿ���ڳ��������ƣ������������ָ���е���������������ƣ�����У�������ȡ��������Σ���ʣ�������ÿһ����������������˳����������ϣ�����ܹ�������ɵ�˳�Ͷ��ӣ���ԭ�е�����ȡ����������ϳ����ƺ͵�˳������4566678�������45678��66������󣬽���֪�����ơ���������������˳����ʣ�µ�����������ϣ���������45678����֪�����ƣ�999��������10J�����ƣ���������ϳ�45678910J��99��ͨ�����ϵķ��������ܽ����ƺ������ܺõ�������ϡ�
	//f) ��ȷ��˫˳�����ȣ��������˳����ȫ�غϣ�����������ϳ�˫˳����Σ��ڳ�ը������˳����������˳��������м���Ƿ����˫˳������У�������ȡ������
	//g) ��ȷ�����ӣ���ը������˳�����������ơ�˫˳��������м���Ƿ���ڶ��ӣ�������ڽ�����ȡ������
	//h) ��ȷ������

	AiThreePks(vec_pk_hand_type_struct_buff);
	

}

//��ȡ��˳ �� ����
void Rule::AiThreePks(std::vector<PkHandleTypeStruct> vec_pk_hand_type_struct_buff){
	vector<PkHandleTypeStruct> result;
	vector<PkHandleTypeStruct>::iterator iter_pk_handle_strct; //��ȡ��˳
	std::vector<int> three_pk_vec;
	

	for (iter_pk_handle_strct = vec_pk_hand_type_struct_buff.begin();iter_pk_handle_strct != vec_pk_hand_type_struct_buff.end();iter_pk_handle_strct++){
		if (iter_pk_handle_strct->type == THREE_NO_ADD_PK){
			three_pk_vec.push_back(iter_pk_handle_strct->pk_structs[0].pk_num);
			result.push_back(*iter_pk_handle_strct);
		}
	}

	PkHandleTypeStruct old_struct = *result.begin();
	PkHandleTypeStruct end_struct = *result.end();  
	for (iter_pk_handle_strct = (result.begin()+1);iter_pk_handle_strct != result.end();iter_pk_handle_strct++)
	{   
		if ( (iter_pk_handle_strct->pk_structs[0].pk_num != Er) && (old_struct.pk_structs[0].pk_num+1) == iter_pk_handle_strct->pk_structs[0].pk_num ){
			old_struct.type = THREE_SHUNZHI_PK;
			old_struct.pk_structs.push_back(iter_pk_handle_strct->pk_structs[0]);
			old_struct.pk_structs.push_back(iter_pk_handle_strct->pk_structs[1]);
			old_struct.pk_structs.push_back(iter_pk_handle_strct->pk_structs[2]);
			 
		}else{
			vec_pk_hand_type_struct.push_back(old_struct);
			if (end_struct.pk_structs[0].pk_num == iter_pk_handle_strct->pk_structs[0].pk_num){
				vec_pk_hand_type_struct.push_back(end_struct);
			}
		}
		old_struct = *iter_pk_handle_strct;
	}
}
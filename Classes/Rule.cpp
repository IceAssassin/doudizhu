#include "Rule.h"
#include <iostream>
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

void Rule::Shuffle() {
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

		if (witch_player == 0){
			pks_player.push_back(buff);
		}	

		if (witch_player == 1){
			pks_npc1.push_back(buff);
		}
			
		if (witch_player == 2){
			pks_npc2.push_back(buff);
		}	
	}

	pks_three.push_back( pks[51]);
	pks_three.push_back( pks[52]);
	pks_three.push_back( pks[53]);
}

void Rule::GiveDizhuPks(int type){
	switch (type)
	{
		case 0:
			 pks_player.push_back(pks_three[0]);
			 pks_player.push_back(pks_three[1]);
			 pks_player.push_back(pks_three[2]);
			break;
		case 1:
			pks_npc1.push_back(pks_three[0]);
			pks_npc1.push_back(pks_three[1]);
			pks_npc1.push_back(pks_three[2]);
			break;
		case 2:
			pks_npc2.push_back(pks_three[0]);
			pks_npc2.push_back(pks_three[1]);
			pks_npc2.push_back(pks_three[2]);
			break;
	default:
		break;
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
	if (total_score >= 7)
		return double_three;
	else if (total_score >= 5)
		return double_two;
	else if (total_score >= 3)
		return double_one;
	else
	return 0;
}

void Rule::AiSplitPks(int type){ //0 1 2 ��� npc1 npc2 

	std::vector<PkStruct> my_pks;
	switch (type)
	{
	case 0:
		for (vector<PkStruct>::iterator iter=pks_player.begin();iter!=pks_player.end();iter++) {
			my_pks.push_back(*iter);
		}
		break;
	case 1:
		for (vector<PkStruct>::iterator iter=pks_npc1.begin();iter!=pks_npc1.end();iter++) {
			my_pks.push_back(*iter);
		}
		break;
	case 2:
		for (vector<PkStruct>::iterator iter=pks_npc2.begin();iter!=pks_npc2.end();iter++) {
			my_pks.push_back(*iter);
		}
		break;
	default:
		break;
	}

	//����
	sort(my_pks.begin(),my_pks.end(),Rule::SelectShort);
	vector<PkHandleTypeStruct> vec_pk_handle_struct_;
	//��ȡ˫��
	if (my_pks[0].pk_type == Joker && my_pks[1].pk_type == Joker){	
		 PkHandleTypeStruct pk_handle_typestruct;
		 pk_handle_typestruct.type = PLANE_PK;
		 pk_handle_typestruct.pk_structs.push_back(my_pks[0]);
		 pk_handle_typestruct.pk_structs.push_back(my_pks[1]);
		 vec_pk_hand_type_struct.push_back(pk_handle_typestruct);

		 my_pks.erase(my_pks.begin());
		 my_pks.erase(my_pks.begin());
	}

	//��������
	vector<int> boom_score;
	for (vector<PkStruct>::iterator iter=my_pks.begin();iter!=my_pks.end();iter++) {
		PkHandleTypeStruct pk_handle_typestruct;
		pk_handle_typestruct.pk_structs.push_back(*iter);
		for (vector<PkStruct>::iterator iter_next = iter+1; iter_next != my_pks.end();iter_next++){
			if (iter->pk_num == iter_next->pk_num){
				pk_handle_typestruct.pk_structs.push_back(*iter);
				++iter;
			}else{
				break;
			}
		}

		if (pk_handle_typestruct.pk_structs.size() == 4){//��ȡը��
			pk_handle_typestruct.type = BOMB_PK;
			vec_pk_hand_type_struct.push_back(pk_handle_typestruct);
			boom_score.push_back(pk_handle_typestruct.pk_structs[0].pk_num);
			break;
		}

		if (pk_handle_typestruct.pk_structs.size() == 3){ //��ȡ����
			pk_handle_typestruct.type = THREE_NO_ADD_PK;
			vec_pk_handle_struct_.push_back(pk_handle_typestruct);
		}
		if (pk_handle_typestruct.pk_structs.size() == 2)
			pk_handle_typestruct.type = DOUBLE_PK;
		if (pk_handle_typestruct.pk_structs.size() == 1)
			pk_handle_typestruct.type = SINGLE_PK;
	}

	//�Ƴ�ը����ص���
	for (vector<PkStruct>::iterator iter=my_pks.begin();iter!=my_pks.end();iter++) {
		for (std::vector<int>::iterator inter2=boom_score.begin();inter2!=boom_score.end();inter2++){
			if (iter->pk_num == *inter2){
				my_pks.erase(iter);
				iter=my_pks.begin();
				inter2=boom_score.begin();
			}
		}
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

	std::vector<PkStruct> pks_erase_three = AiThreePks(vec_pk_handle_struct_,my_pks);//��ȡ3��

	std::vector<PkStruct> pks_erase_shunzi = AiSingleShunzhi(pks_erase_three);//��ȡ����

	std::vector<PkStruct> pks_erase_double = AiDouble(pks_erase_shunzi);//��ȡ����

	AiSingle(pks_erase_double);//����
}

//��ȡ����һ������
std::vector<PkStruct> Rule::AiThreePks(vector<PkHandleTypeStruct> vec_pk_handle_struct_,std::vector<PkStruct> &vec_pks){
	if (vec_pk_handle_struct_.size() == 0)
		return vec_pks;
	if (vec_pk_handle_struct_.size() == 1)
	{
		vec_pk_hand_type_struct.push_back(vec_pk_handle_struct_[0]);
	}
	
	//�ϲ���˳
	PkHandleTypeStruct pk_handle_type_struct_;
	int oldScore = 0;
	if (vec_pk_handle_struct_.size() >= 2){
		 for (vector<PkHandleTypeStruct>::iterator iter = vec_pk_handle_struct_.begin();iter!= vec_pk_handle_struct_.end();iter++){
			oldScore = iter->pk_structs[0].pk_num;
			pk_handle_type_struct_= *iter;
			for (vector<PkHandleTypeStruct>::iterator iter2 = iter+1;iter2!= vec_pk_handle_struct_.end();iter2++){
				 if (oldScore-1 == iter2->pk_structs[0].pk_num){
					 oldScore = iter2->pk_structs[0].pk_num;
					 pk_handle_type_struct_.type = THREE_SHUNZHI_PK;
					 for (int i=0;i<3;i++){
						 pk_handle_type_struct_.pk_structs.push_back(iter2->pk_structs[i]);
					 }
					 ++iter;
				 }
			}
			vec_pk_hand_type_struct.push_back(pk_handle_type_struct_);
		 }
	}

	//�Ƴ�������
	for (vector<PkStruct>::iterator inter = vec_pks.begin();inter != vec_pks.end();inter++){
		for (vector<PkHandleTypeStruct>::iterator inter2 = vec_pk_handle_struct_.begin();inter2 != vec_pk_handle_struct_.end();inter2++){
			if (inter->pk_num == inter2->pk_structs[0].pk_num){
				vec_pks.erase(inter);
				inter = vec_pks.begin();
				inter2 = vec_pk_handle_struct_.begin();
			}
		}
	}

	return vec_pks;
	
}


//��ȡ˳��
std::vector<PkStruct> Rule::AiSingleShunzhi(std::vector<PkStruct> &vec_pks){
	vec_pks.clear();
	PkStruct vec_pk;

	if (vec_pks.size() < 5){
		return vec_pks;
	}

	std::vector<PkHandleTypeStruct> vec_pk_hand_type_struct_;

	//��˳��ȡ
	for (std::vector<PkStruct>::iterator inter = vec_pks.begin();inter!=vec_pks.end();inter++){
		PkHandleTypeStruct result;
		if (inter->pk_num == Er || inter->pk_type == Joker){
			continue;
		}

		result.type = SINGLE_SHUNZHI_PK;
		result.pk_structs.push_back(*inter);
		int single_num = 1;

		if (inter+1 != vec_pks.end()){
			break;
		}
		for (std::vector<PkStruct>::iterator inter2 = inter+1;inter2!=vec_pks.end();++inter2){
			if (inter2->pk_num == inter->pk_num){
				++inter2;
				++inter;
			}

			if ( (inter->pk_num)-1 == inter2->pk_num){
				++inter;
				++single_num;
				result.pk_structs.push_back(*inter2);
				if (single_num == 5){
					vec_pk_hand_type_struct_.push_back(result);
				}
			}else {
				break;
			}
		}
	}

	//�Ƴ�˳���е���
	for (std::vector<PkStruct>::iterator inter = vec_pks.begin();inter!=vec_pks.end();inter++){
		for (std::vector<PkHandleTypeStruct>::iterator inter2=vec_pk_hand_type_struct_.begin();inter2!=vec_pk_hand_type_struct_.end();inter2++){
			for (std::vector<PkStruct>::iterator inter3 = inter2->pk_structs.begin();inter3 != inter2->pk_structs.end();inter3++){
				if (inter->pk_num == inter3->pk_num && inter->pk_type == inter3->pk_type){
					vec_pks.erase(inter);
					inter = vec_pks.begin();
					inter2=vec_pk_hand_type_struct_.begin();
					inter3 = inter2->pk_structs.begin();
				}
			}
		}
	}

	//��չ˳��
	for (std::vector<PkStruct>::iterator inter = vec_pks.begin();inter!=vec_pks.end();inter++){
		bool is_add_extra = false;
		sort(pks_npc1.begin(),pks_npc1.end(),Rule::SelectShort);

		if (inter->pk_num == Er || inter->pk_type == Joker){
			continue;
		}

		for (std::vector<PkHandleTypeStruct>::iterator inter2=vec_pk_hand_type_struct_.begin();inter2!=vec_pk_hand_type_struct_.end();inter2++){
			if (inter->pk_num-1 == inter2->pk_structs[0].pk_num){//��չ���
				inter2->pk_structs.insert(inter2->pk_structs.begin(),*inter);
				is_add_extra = true;
				break;
			}

			int len = inter2->pk_structs.size();
			if (inter->pk_num+1 == inter2->pk_structs[len-1].pk_num){ //��չ�ұ�
				inter2->pk_structs.push_back(*inter);
				is_add_extra = true;
				break;
			}
		} 


		if (is_add_extra)//���õ�����
		{
			vec_pks.erase(inter);
			inter = vec_pks.begin();
		}
	}

	//�ϲ�˳��
	if (vec_pk_hand_type_struct_.size() == 2){
		if (vec_pk_hand_type_struct_[0].pk_structs.size() == vec_pk_hand_type_struct_[1].pk_structs.size())
		{
			int len = vec_pk_hand_type_struct_[0].pk_structs.size();
			if ( vec_pk_hand_type_struct_[0].pk_structs[0].pk_num == vec_pk_hand_type_struct_[1].pk_structs[0].pk_num  && vec_pk_hand_type_struct_[0].pk_structs[len-1].pk_num == vec_pk_hand_type_struct_[1].pk_structs[len-1].pk_num  ){
				for (std::vector<PkStruct>::iterator inter = vec_pk_hand_type_struct_[1].pk_structs.begin();inter!=vec_pk_hand_type_struct_[1].pk_structs.end();inter++){
					vec_pk_hand_type_struct_[0].pk_structs.push_back(*inter);
				}
				vec_pk_hand_type_struct_[0].type = DOUBLE_SHUNZHI_PK;
				vec_pk_hand_type_struct_.erase(vec_pk_hand_type_struct_.end());
			}
		}
	}
	 
	//��ֵ
	for (std::vector<PkHandleTypeStruct>::iterator inter=vec_pk_hand_type_struct_.begin();inter!=vec_pk_hand_type_struct_.end();inter++){
		vec_pk_hand_type_struct.push_back(*inter);
	}
	
	return vec_pks;
}

//��ȡ����
std::vector<PkStruct> Rule::AiDouble(std::vector<PkStruct> &vec_pks){

	for (std::vector<PkStruct>::iterator inter = vec_pks.begin();inter!=vec_pks.end();){

		bool is_can_add = false;
		if (inter+1 == vec_pks.end()){
			break;
		}

		for (std::vector<PkStruct>::iterator inter2 = inter+1;inter2!=vec_pks.end();){
			if (inter->pk_num == inter2->pk_num){
				PkHandleTypeStruct type_struct;
				type_struct.type = DOUBLE_PK;
				type_struct.pk_structs.push_back(*inter);
				type_struct.pk_structs.push_back(*inter2);
				vec_pk_hand_type_struct.push_back(type_struct);
				
				inter2 = vec_pks.erase(inter2);
				inter = vec_pks.erase(inter);
				is_can_add = true;
				break;
			}else{
				inter2++;
			}
		}

		if (!is_can_add){
			++inter;
		}
	}

	return vec_pks;
}

//��ȡ����
void Rule::AiSingle(std::vector<PkStruct> &vec_pks){
	for (std::vector<PkStruct>::iterator inter = vec_pks.begin();inter!=vec_pks.end();inter++){
		PkHandleTypeStruct type_struct;
		type_struct.type = SINGLE_PK;
		type_struct.pk_structs.push_back(*inter);
		vec_pk_hand_type_struct.push_back(type_struct);
	}
}
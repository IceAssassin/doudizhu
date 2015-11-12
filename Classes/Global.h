#pragma once
#include <vector>
using namespace std;

const int pkWidth = 71;//�ƵĿ��
const int pkHeight = 96;//�Ƶĸ߶�
const int pkDistance = 20;//�����Ƶļ��
const int pkTopHeight = 10;//�Ƶ�������ƶ�����
const int menu_score_top = 88;//�з�����λ�ø߶�
const int menu_score_distance = 20;//�зּ��
//��ɫ
enum PKType
{
	Spade = 0,//����
	Heart,//����
	Club,//÷��
	Dianmond,//����
	Joker,//��
	PKBack = 4,//��ɫ����
};

enum PKNum {
	Num = 0,Four,Five,Six,Seven,Eight,Nine,Ten,Jack,Queen,King,Ace,Er,BlackJoker,RedJoker,
	PkBackNum = 2 //��������ͼƬλ��
};

enum Table {
	Score,
	NpcOneNotPlay,
	NpcTwoNotPlay
};

enum CARD_TYPE{
	SINGLE_CARD = 1,		//����-
	DOUBLE_CARD,			//����-
	THREE_CARD,				//3����-
	BOMB_CARD,				//ը��
	THREE_ONE_CARD,			//3��1-
	THREE_TWO_CARD,			//3��2-
	BOMB_TWO_CARD,			//�ĸ���2�ŵ���
	BOMB_DOUBLE_TWO_CARD,	//�ĸ���2��
	CONNECT_CARD,			//����-
	COMPANY_CARD,			//����-
	AIRCRAFT_CARD,			//�ɻ�����-
	AIRCRAFT_SINGLE_CARD,	//�ɻ�������-
	AIRCRAFT_DOULBE_CARD,	//�ɻ�������-
	ERROR_CARD				//���������
};


enum PLAYER_HANDLE_TYPE ////�������:0Ϊ������ڵ��ƣ�1Ϊ�����У�2Ϊ��ʾ��������,3Ϊ���Ҫ�����ƣ�4Ϊ����1Ҫ�����ƣ�5Ϊ����2Ҫ������
{
	PLAYER_ARRAY_PK = 0,
	COMPUTER_ARRAY_PK,
	THREE_PK,
	PLAYER_HAND_PK,
	COMPUTER_1_HANDLE_PK,
	COMPUTER_2_HANDLE_PK
};


enum SCORE{
	score_zero,
	score_one ,
	score_two,
	score_three
};
struct AIR_ADD_CARD_TYPE //�ɻ�����
{
	std::vector<int> single_card;//����
	std::vector<int> double_card;//˫��
	std::vector<int> three_card;//����
	std::vector<int> four_card;//����
};

struct StructCallPk
{
	int People;
	int CallScore;
};
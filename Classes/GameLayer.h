#pragma once
#include "cocos2d.h"
#include "Rule.h"
#include "Player.h"
#include "Poker.h"
USING_NS_CC;

class GameLayer : public Layer
{
public:

	GameLayer(void);
	~GameLayer(void);
	virtual bool init();
	CREATE_FUNC(GameLayer);


	bool initBackGround();
	bool createPokers();
	Poker *selectPoker(int pokerType,int num);
	bool initPlayer();
	bool initButton();
private: 
	 CCArray* m_arrPokers;
	 CC_SYNTHESIZE(CCArray*,m_arrayPlayerOut,ArrayPlayerOut);//���Ҫ������
	 CC_SYNTHESIZE(Player*,m_player,Player);//���
	 Player* m_npcOne;//����1
	 Player* m_npcTwo;//����2
	 Player* m_Three;//��ʾ����ʣ����
	 Rule rule;//�ƹ���
};
#pragma once
#include "cocos2d.h"
#include "MySocket.h"
#include "protocol.pb.h"
#include "TextFieldTTF.h"

#include <string>
#include <fstream>

USING_NS_CC;
using namespace std;


struct LoginInfo
{
	string name;
	string pwd;
};

class NetGameLayer : public CCLayer
{
public:
	NetGameLayer(void);
	~NetGameLayer(void);
	virtual bool init();

	bool initBackGround();
	void CreateNetWork();//��������
	bool GetLoginInfo();//��ȡ��ҵĵ�½ �˺� ����
	void setText(const char* tip);
	CREATE_FUNC(NetGameLayer);

private: 
	 ODSocket cSocket;
	 LoginInfo login_info;//��½�����Ϣ

	 MyTextFieldTTF* text_name;
	 MyTextFieldTTF* text_pwd;
	 MenuItemFont* commit_menu;
	 Menu* m_handle_menu;
};
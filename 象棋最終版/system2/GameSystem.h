#pragma once
#pragma comment(lib, "winmm.lib")
#include"AI.h"
#include"Music.h"
#include"UI.h"
#include"Log.h"
#include<conio.h>
#include<cctype>
#include<fstream>
#include<algorithm>


//typedef pair<int, int>Coordinate;

enum Status {
	/******************/
	/****�D��檺���A****/
	/******************/

	Beginning, //
	SelectMode, //��ܼҦ�(��H/���H)
	SinglePlayerMenu, // ��ܥ��� or ���
	SelectSinglePlayer,
	DuoPlayerMenu, //�}�l�s�C��orŪ������
	SelectPlayer, //��ܶ¤� or ����
	Read, //Ū�ɮ�
	Read_Error, //�ɮ�Ū�����~
	Option, //�t�γ]�w
	Sound,

	/******************/
	/****�C���������A****/
	/******************/

	SelectChess, //��ܴѤl
	MoveChess, //���ʴѤl
	help, //���U�M��
	regret, //�O�_����
	pause, //�Ȱ����A
	pause_restart, //�T�w���s�}�l?
	Win, //���
	Store, //�x�s�C��
	Cannot_regret, //�L�k����
	Warning,
	help_2,
};

enum Key {
	UP = 72,
	DOWN = 80,
	RIGHT = 77,
	LEFT = 75,
	ESC = 27,
	ENTER = 30,
	Z = 122,
	invalid = 0,
	LogLeft = 44,
	LogRight = 46,
	H = 100,
	Save = 115,
};



class GameSystem {

	Log log;

	Coordinate BoardCursor; //�ѽL�����(�H�ѽL9*10����)
	Screen screen; //�{�b�b���ӵe��
	Status nowStatus; //�{�b�C���b�ƻ򪬺A
	Music::MusicMode musicMode; //�C�����ļҦ�

	int SelectedIndex; //�{�b��ܪ����ﶵ(�p�Ȱ��C���B����)
	int player; //1������
	pair<int, Coordinate> SelectedChess; //�{�b��ܪ��Ѥl(pair�Ĥ@�ӰѼƬ��Ѥlindex�A�ĤG�ӰѼƬ��y��)
	vector<pair<int, Coordinate>> AvailableMove;
	string FileName;
	int LogPage; //Log�`�@���X��
	int nowLogPage; //�{�bLog�b����
	int GameMode; //�C���Ҧ�(1�G��H�C��,2�G���H�C��)

	vector<string> TXTFiles; //�����Ҧ��ɮצW�� byHans
	int nowDataPage;//�{�bData�b�ĴX��
	Status HansMem;

public:
	static GameSystem* instance;

	GameSystem();
	~GameSystem();
	void setMode(Screen screen);
	void setPlayer(int player);
	void keyInput();


	bool ChessSelect(Coordinate co);
	int ChessMove(Coordinate destination);

	//��l��
	void NewGame(int player);

	// �C���ӧQ
	void WinGame();
	//�x�s�C��
	bool StoreGame();
	//��Log������
	void turnLogPage(int);
	// ����
	bool Regret();
	//Ū���ɮ�
	int LoadGame(string fileName);


	void init();
	void AIChessMove();
	void NextPlayer();


	// ���ʿﶵ�W�����(�ǤJ�W�U���k)
	void MoveMenuOption(Key input, bool musicplay = true);
	// ���ʹ�߿��W�����(�ǤJ�W�U���k)
	void MoveSolidMenuOption(Key input);
	// ���ʴѽL�W�����(�ǤJ�W�U���k)
	void MoveBoardCursor(Key input);
	// �q����|���_�C�������A�^�k�C��
	void Resume();

	//���o��e��Ƨ����Ҧ�.txt�� by Hans
	void getTXT();
	//½Ū�J�ɮת��� byHans
	void turnSaveDataPage(int directon, bool musicplay = true);
	//��½SaveData�����g��
	void MoveSolidDataOption(Key input, int num, bool musicplay = true);

	void NewMake();
	void MoveMakeCursor(Key);
	bool checkMake();

};




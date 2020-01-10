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
	/****主選單的狀態****/
	/******************/

	Beginning, //
	SelectMode, //選擇模式(單人/雙人)
	SinglePlayerMenu, // 選擇先攻 or 後攻
	SelectSinglePlayer,
	DuoPlayerMenu, //開始新遊戲or讀取舊檔
	SelectPlayer, //選擇黑方 or 紅方
	Read, //讀檔案
	Read_Error, //檔案讀取錯誤
	Option, //系統設定
	Sound,

	/******************/
	/****遊戲內的狀態****/
	/******************/

	SelectChess, //選擇棋子
	MoveChess, //移動棋子
	help, //幫助清單
	regret, //是否悔棋
	pause, //暫停狀態
	pause_restart, //確定重新開始?
	Win, //獲勝
	Store, //儲存遊戲
	Cannot_regret, //無法悔棋
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

	Coordinate BoardCursor; //棋盤的游標(以棋盤9*10紀錄)
	Screen screen; //現在在哪個畫面
	Status nowStatus; //現在遊戲在甚麼狀態
	Music::MusicMode musicMode; //遊戲音效模式

	int SelectedIndex; //現在選擇的表單選項(如暫停遊戲、悔棋)
	int player; //1為紅方
	pair<int, Coordinate> SelectedChess; //現在選擇的棋子(pair第一個參數為棋子index，第二個參數為座標)
	vector<pair<int, Coordinate>> AvailableMove;
	string FileName;
	int LogPage; //Log總共有幾頁
	int nowLogPage; //現在Log在哪頁
	int GameMode; //遊戲模式(1：單人遊戲,2：雙人遊戲)

	vector<string> TXTFiles; //紀錄所有檔案名稱 byHans
	int nowDataPage;//現在Data在第幾頁
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

	//初始化
	void NewGame(int player);

	// 遊戲勝利
	void WinGame();
	//儲存遊戲
	bool StoreGame();
	//換Log的頁數
	void turnLogPage(int);
	// 悔棋
	bool Regret();
	//讀取檔案
	int LoadGame(string fileName);


	void init();
	void AIChessMove();
	void NextPlayer();


	// 移動選項上的游標(傳入上下左右)
	void MoveMenuOption(Key input, bool musicplay = true);
	// 移動實心選單上的游標(傳入上下左右)
	void MoveSolidMenuOption(Key input);
	// 移動棋盤上的游標(傳入上下左右)
	void MoveBoardCursor(Key input);
	// 從任何會中斷遊戲的狀態回歸遊戲
	void Resume();

	//取得當前資料夾內所有.txt檔 by Hans
	void getTXT();
	//翻讀入檔案的頁 byHans
	void turnSaveDataPage(int directon, bool musicplay = true);
	//為翻SaveData的頁寫的
	void MoveSolidDataOption(Key input, int num, bool musicplay = true);

	void NewMake();
	void MoveMakeCursor(Key);
	bool checkMake();

};




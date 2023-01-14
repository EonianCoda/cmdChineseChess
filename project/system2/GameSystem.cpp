#include "GameSystem.h"
//處理自定義時先攻後攻問題
GameSystem* GameSystem::instance;

namespace {

	map<pair<Screen, Status>, vector<pair<wstring, Coordinate>> > MenuList = {
		{make_pair(Screen::Playing,Status::pause) ,{ make_pair(L"繼續遊戲",make_pair(50, 7)),make_pair(L"重新開始",make_pair(50, 9)),make_pair(L"回主選單",make_pair(50, 11)),make_pair(L"儲存遊戲",make_pair(50, 13)),make_pair(L"離開遊戲",make_pair(50, 15))}}
		,{make_pair(Screen::Playing,Status::regret) ,{ make_pair(L"是",make_pair(48, 13)),make_pair(L"否",make_pair(56, 13)) }}
		,{make_pair(Screen::Playing,Status::pause_restart) ,{ make_pair(L"是",make_pair(49, 13)),make_pair(L"否",make_pair(57, 13)) }}
		,{make_pair(Screen::MainMenu,Status::Beginning) ,{ make_pair(L"開始遊戲",make_pair(47, 13)),make_pair(L"選項",make_pair(49, 17)),make_pair(L"離開遊戲",make_pair(47, 21))}}
		,{make_pair(Screen::MainMenu,Status::DuoPlayerMenu) ,{ make_pair(L"開始新遊戲",make_pair(46, 14)),make_pair(L"讀取舊紀錄",make_pair(46, 20))}}
		,{make_pair(Screen::MainMenu,Status::SelectPlayer) ,{ make_pair(L"紅方先攻",make_pair(47, 14)),make_pair(L"黑方先攻",make_pair(47, 20))}}
		,{make_pair(Screen::MainMenu,Status::SinglePlayerMenu) ,{ make_pair(L"開始新遊戲",make_pair(46, 14)),make_pair(L"讀取舊紀錄",make_pair(46, 20))}}
		,{make_pair(Screen::MainMenu,Status::SelectSinglePlayer) ,{ make_pair(L"玩家先攻",make_pair(47, 14)),make_pair(L"電腦先攻",make_pair(47, 20))}}
		,{make_pair(Screen::MainMenu,Status::SelectMode) ,{ make_pair(L"單人遊戲",make_pair(47, 14)),make_pair(L"雙人遊戲",make_pair(47, 20))}}
		,{make_pair(Screen::MainMenu,Status::Option) ,{ make_pair(L"系統音效",make_pair(47, 14)),make_pair(L"自定義棋盤",make_pair(46, 20))}}
		,{make_pair(Screen::MainMenu,Status::Sound) ,{ make_pair(L"靜音模式",make_pair(47, 13)),make_pair(L"一般音效",make_pair(47, 17)),make_pair(L"特殊音效",make_pair(47, 21))}}
		,{make_pair(Screen::Making,Status::SelectChess) ,{ make_pair(L"　",make_pair(67, 5)),make_pair(L"將",make_pair(67, 7)),make_pair(L"士",make_pair(71, 7)),make_pair(L"象",make_pair(75, 7)),make_pair(L"車",make_pair(79, 7)),make_pair(L"馬",make_pair(83, 7)),make_pair(L"包",make_pair(87, 7)),make_pair(L"卒",make_pair(91, 7)),
															make_pair(L"帥",make_pair(67, 9)),make_pair(L"仕",make_pair(71, 9)),make_pair(L"相",make_pair(75, 9)),make_pair(L"車",make_pair(79, 9)),make_pair(L"傌",make_pair(83, 9)),make_pair(L"炮",make_pair(87, 9)),make_pair(L"兵",make_pair(91, 9))}}
		,{make_pair(Screen::Making,Status::pause) ,{ make_pair(L"繼續定義",make_pair(50, 7)),make_pair(L"重新開始",make_pair(50, 9)),make_pair(L"回主選單",make_pair(50, 11)),make_pair(L"儲存棋盤",make_pair(50, 13)),make_pair(L"離開遊戲",make_pair(50, 15))}}
		,{make_pair(Screen::Making,Status::pause_restart) ,{ make_pair(L"是",make_pair(49, 13)),make_pair(L"否",make_pair(57, 13)) }}
		,{make_pair(Screen::Making,Status::SelectPlayer) ,{ make_pair(L"黑",make_pair(49, 13)),make_pair(L"紅",make_pair(57, 13)) }}

	};

	map<pair<Screen, Status>, pair<Coordinate, vector<Coordinate> > > SolidMenuList = {
		{make_pair(Screen::MainMenu,Status::Beginning) , make_pair(make_pair(20,3) , vector<Coordinate>{make_pair(41, 12),make_pair(41, 16),make_pair(41, 20)}) }
		,{make_pair(Screen::MainMenu,Status::DuoPlayerMenu) , make_pair(make_pair(20,5) , vector<Coordinate>{make_pair(41, 12),make_pair(41, 18)}) }
		,{make_pair(Screen::MainMenu,Status::SelectMode)  , make_pair(make_pair(20,5) , vector<Coordinate>{make_pair(41, 12),make_pair(41, 18)}) }
		,{make_pair(Screen::MainMenu,Status::SinglePlayerMenu) , make_pair(make_pair(20,5) , vector<Coordinate>{make_pair(41, 12),make_pair(41, 18)})  }
		,{make_pair(Screen::MainMenu,Status::SelectPlayer) , make_pair(make_pair(20,5) , vector<Coordinate>{make_pair(41, 12),make_pair(41, 18)}) }
		,{make_pair(Screen::MainMenu,Status::SelectSinglePlayer) , make_pair(make_pair(20,5) , vector<Coordinate>{make_pair(41, 12),make_pair(41, 18)}) }
		,{make_pair(Screen::MainMenu,Status::Option) , make_pair(make_pair(20,5) , vector<Coordinate>{make_pair(41, 12),make_pair(41, 18)}) }
		,{make_pair(Screen::MainMenu,Status::Sound) , make_pair(make_pair(20,3) , vector<Coordinate>{make_pair(41, 12),make_pair(41, 16),make_pair(41, 20)}) }
		,{make_pair(Screen::Making,Status::SelectChess) , make_pair(make_pair(1,1) , vector<Coordinate>{make_pair(67, 6),make_pair(71, 6),make_pair(75, 6),make_pair(79, 6),make_pair(83, 6),make_pair(87, 6),make_pair(91, 6),make_pair(67, 9),make_pair(71, 9),make_pair(75, 9),make_pair(79, 9),make_pair(83, 9),make_pair(87, 9),make_pair(91, 9)}) }
	};

	vector<pair<Coordinate, vector<Coordinate> > > SolidDataList = {
		{make_pair(make_pair(20,1) , vector<Coordinate>{make_pair(41, 15)})}
		,{make_pair(make_pair(20,1) , vector<Coordinate>{make_pair(41, 15),make_pair(41, 17)}) }
		,{make_pair(make_pair(20,1) , vector<Coordinate>{make_pair(41, 15),make_pair(41, 17),make_pair(41, 19)}) }
	};
}

//建構式：
GameSystem::GameSystem() : screen(Screen::MainMenu), BoardCursor({ 0, 9 }), SelectedChess({ 0,{0,0} }), LogPage(1), nowLogPage(1), SelectedIndex(0)
{
	screen = Screen::MainMenu;
	nowStatus = Status::Beginning;
	musicMode = Music::MusicMode::normal;
}

//解構式：無作用
GameSystem::~GameSystem()
{

}

//設置當前玩家
void GameSystem::setPlayer(int player)
{
	if (player != 0 && player != 1) {
		cout << "GameSystem::setPlayer：錯誤" << player;
	}
	else {
		this->player = player;
	}
}

//設置當前畫面
void GameSystem::setMode(Screen screen)
{
	this->screen = screen;
}

// 移動棋盤上的游標(傳入上下左右)
void GameSystem::MoveBoardCursor(Key direction)
{
	static map<Key, Coordinate> Table{
		{Key::UP,{0,-1}},
		{Key::DOWN,{0,1}},
		{Key::LEFT,{-1,0}},
		{Key::RIGHT,{1,0}},
	};
	auto item = Table[direction];
	//沒有超出範圍
	if ((BoardCursor.first + item.first >= 0) && (BoardCursor.first + item.first <= 8) &&
		(BoardCursor.second + item.second >= 0) && (BoardCursor.second + item.second <= 9)) {
		BoardCursor.first += item.first;
		BoardCursor.second += item.second;
		UI::Instance->gotoBoardXY(BoardCursor);
	}
	else {
		cout << '\a';
	}
}

//接受使用者按鍵輸入，並根據目前所在畫面與模式，進行相對應的動作
void GameSystem::keyInput()
{
	static char tmp;
	static Key input;
	tmp = _getch();
	bool flag = false;

	if (tmp == -32) {
		flag = true;
		//若tmp==-32，代表使用者輸入上下左右
		tmp = _getch();
	}


	//將輸入轉為Enum(列舉)
	switch (tmp) {
	case 72://方向鍵上
		input = Key::UP;
		break;
	case 75: //方向鍵左
		input = Key::LEFT;
		break;
	case 80: //方向鍵下
		input = Key::DOWN;
		break;
	case 77: //方向鍵右
		input = Key::RIGHT;
		break;
	case 27: //Esc鍵
		input = Key::ESC;
		break;
	case 13: //enter鍵
		input = Key::ENTER;
		break;
	case 104: //h鍵
	//case 90: //H鍵
		input = Key::H;
		break;
	case 122: //z鍵
	case 90: //Z鍵
		input = Key::Z;
		break;
	case 46: //>鍵
		input = Key::LogRight;
		break;
	case 44:
		input = Key::LogLeft;
		break;
	case 115:
	case 83:
		input = Key::Save;
		break;
	default:
		input = Key::invalid;
		break;
	}

	//讀取舊檔
	if (nowStatus == Status::Read) {
		if (TXTFiles.empty()) {
			nowStatus = Status::DuoPlayerMenu;
			SelectedIndex = 0;
			UI::Instance->showBlock(screen, Setting::Block::DuoPlayerMenu);
			return;
		}
		else {
			switch (input) {
			case Key::LEFT:
				turnSaveDataPage(-1);
				break;
			case Key::RIGHT:
				turnSaveDataPage(1);
				break;

				//移動實心選項
			case Key::UP:
			case Key::DOWN:
				if (nowDataPage <= TXTFiles.size() / 3 || TXTFiles.size() % 3 == 0)
					MoveSolidDataOption(input, 3);
				else
					MoveSolidDataOption(input, TXTFiles.size() % 3);
				break;

			case Key::ESC:
				if (GameMode == 1) {
					nowStatus = Status::SinglePlayerMenu;
					SelectedIndex = 0;
					UI::Instance->showBlock(screen, Setting::Block::SinglePlayerMenu);
				}
				else if (GameMode == 2) {
					nowStatus = Status::DuoPlayerMenu;
					SelectedIndex = 0;
					UI::Instance->showBlock(screen, Setting::Block::DuoPlayerMenu);
				}
				break;

			case Key::ENTER:
				FileName = TXTFiles[(nowDataPage - 1) * 3 + SelectedIndex];
				int statusCode = LoadGame(FileName);
				if (statusCode == 2) {
					screen = Screen::Playing;
					NewGame(player);
				}
				else {
					//檔案格式錯誤
					if (statusCode == 1) {
						ChessBoard::Instance->init();
					}
					//開啟異常
					else if (statusCode == 0) {

					}
					nowStatus = Status::Read_Error;
					playMusic(musicMode, Music::Error);
					UI::Instance->showBlock(screen, Setting::Block::Read_Error);
				}
				break;
			}
			return;
		}
	}
	//若狀態為檔案讀取錯誤(請按下任意鍵繼續...)
	else if (nowStatus == Status::Read_Error) {
		nowStatus = Status::DuoPlayerMenu;
		UI::Instance->showBlock(screen, Setting::Block::DuoPlayerMenu);
		return;
	}
	//若狀態為勝利(請按下任意鍵繼續...)
	else if (nowStatus == Status::Win) {
		ChessBoard::Instance->init();
		NewGame(1);
		return;
	}
	else if (nowStatus == Status::Cannot_regret) {
		UI::Instance->DrawBoard();
		//代表現在在移動棋子模式
		if (SelectedChess.first != 0) {
			nowStatus = Status::MoveChess;
			ChessSelect(SelectedChess.second);
		}
		//代表現在在選擇棋子模式
		else {
			nowStatus = Status::SelectChess;
		}
		//游標回到原本的位置
		UI::Instance->gotoBoardXY(BoardCursor);
		return;
	}
	//輸入儲存名稱
	else if (nowStatus == Status::Store) {
		//取消儲存
		if (input == Key::ESC) {
			if (screen == Screen::Playing) {
				//重畫棋盤
				UI::Instance->DrawBoard();
				//代表現在在移動棋子模式
				if (SelectedChess.first != 0) {
					nowStatus = Status::MoveChess;
					ChessSelect(SelectedChess.second);
				}
				//代表現在在選擇棋子模式
				else {
					nowStatus = Status::SelectChess;
				}
				//游標回到原本的位置
				UI::Instance->gotoBoardXY(BoardCursor);
				return;
			}
			else if (screen == Screen::Making) {
				UI::Instance->DrawBoard();
				nowStatus = Status::SelectPlayer;
				UI::Instance->showBlock(Screen::Making, Setting::Block::SelectPlayer);
				SelectedIndex = 0;
				//讓游標移到黑
				UI::Instance->gotoXY(MenuList[make_pair(screen, nowStatus)][0].second);
				return;
			}
		}
		//Enter鍵，檢查是否有輸入任何一個字元
		else if (input == Key::ENTER && FileName.size() != 0) //enter
		{
			//儲存遊戲成功
			if (StoreGame()) {
				//重畫棋盤
				UI::Instance->DrawBoard();
				if (screen == Screen::Playing) {
					//代表現在在移動棋子模式
					if (SelectedChess.first != 0) {
						nowStatus = Status::MoveChess;
						ChessSelect(SelectedChess.second);
					}
					//代表現在在選擇棋子模式
					else {
						nowStatus = Status::SelectChess;
					}
					//游標回到原本的位置
					UI::Instance->gotoBoardXY(BoardCursor);
				}
				else if (screen == Screen::Making) {
					if (HansMem == Status::SelectChess || HansMem == Status::pause) {
						UI::Instance->gotoXY(MenuList[make_pair(Screen::Making, Status::SelectChess)][SelectedChess.first].second);
						SelectedIndex = SelectedChess.first;
						nowStatus = SelectChess;
					}
					else if (HansMem == Status::MoveChess) {
						nowStatus = Status::MoveChess;
						SelectedIndex = SelectedChess.first;
						UI::Instance->gotoBoardXY(BoardCursor);
					}
				}
				return;
			}
		}
		//BackSpace鍵
		else if (tmp == 8 && !FileName.empty()) {
			UI::Instance->gotoXY(33 + 2 * (int)(FileName.size()), 13);
			cout << " ";
			UI::Instance->gotoXY(33 + 2 * FileName.size(), 13);
			FileName.pop_back();
		}
		//若為合法輸入
		else if (!flag && (isdigit(tmp) || isalpha(tmp)) && FileName.size() < 12) {
			FileName.push_back(tmp);
			cout << tmp;
			if (FileName.size() != 12) {
				UI::Instance->gotoXY(33 + 2 * (FileName.size() + 1), 13);
			}
			else {
				UI::Instance->gotoXY(33 + 2 * FileName.size(), 13);
			}
		}
		else {
			cout << '\a';
		}
		return;
	}
	else if (nowStatus == Status::Warning) {
		nowStatus = HansMem;
		if (nowStatus == Status::pause) {
			SelectedIndex = 0;
			UI::Instance->showBlock(screen, Setting::Block::Pause);
			for (int i : { 0, 1, 2 }) {
				MoveMenuOption(Key::DOWN, false);
			}
		}

		else if (nowStatus == Status::SelectChess) {
			UI::Instance->DrawBoard();
			UI::Instance->gotoXY(MenuList[make_pair(Screen::Making, Status::SelectChess)][SelectedChess.first].second);
		}

		else if (nowStatus == Status::MoveChess) {
			UI::Instance->DrawBoard();
			UI::Instance->gotoBoardXY(BoardCursor);
		}

		return;
	}
	// 若輸入的鍵無效則結束函式
	if (input == Key::invalid) return;

	//若畫面位於 (一開始)主選單
	if (screen == Screen::MainMenu) {
		if (nowStatus == Status::Beginning) {
			switch (input) {
				//移動實心選項
			case Key::LEFT:
			case Key::UP:
			case Key::RIGHT:
			case Key::DOWN:
				MoveSolidMenuOption(input);
				break;

			case Key::ENTER:
				//開始遊戲
				if (SelectedIndex == 0) {
					nowStatus = Status::SelectMode;
					SelectedIndex = 0;
					UI::Instance->showBlock(screen, Setting::Block::SelectMode);
				}
				//系統選項
				else if (SelectedIndex == 1) {
					nowStatus = Status::Option;
					SelectedIndex = 0;
					UI::Instance->showBlock(screen, Setting::Block::Option);
				}
				//離開遊戲
				else if (SelectedIndex == 2) {
					UI::Instance->CleanScreen();
					exit(1);
				}
				break;
			}
		}
		//選擇遊戲模式(單人/雙人)
		else if (nowStatus == Status::SelectMode) {
			switch (input) {
				//移動實心選項
			case Key::LEFT:
			case Key::UP:
			case Key::RIGHT:
			case Key::DOWN:
				MoveSolidMenuOption(input);
				break;

			case Key::ENTER:
				//單人遊戲
				if (SelectedIndex == 0) {
					nowStatus = Status::SinglePlayerMenu;
					SelectedIndex = 0;
					GameMode = 1; //單人模式
					UI::Instance->showBlock(screen, Setting::Block::SinglePlayerMenu);
				}
				//雙人遊戲
				else if (SelectedIndex == 1) {
					nowStatus = Status::DuoPlayerMenu;
					SelectedIndex = 0;
					GameMode = 2; //雙人模式
					UI::Instance->showBlock(screen, Setting::Block::DuoPlayerMenu);
				}
				//返回上一頁
				else if (SelectedIndex == 2) {
					nowStatus = Status::Beginning;
					SelectedIndex = 0;
					UI::Instance->showBlock(screen, Setting::Block::Main);
				}
				break;

			case Key::ESC:
				nowStatus = Status::Beginning;
				SelectedIndex = 0;
				UI::Instance->showBlock(screen, Setting::Block::Main);
				break;
			}
		}
		//單人遊戲清單(先攻/後攻)
		else if (nowStatus == Status::SinglePlayerMenu) {
			switch (input) {
				//移動實心選項
			case Key::LEFT:
			case Key::UP:
			case Key::RIGHT:
			case Key::DOWN:
				MoveSolidMenuOption(input);
				break;

			case Key::ENTER:
				//開始新遊戲
				if (SelectedIndex == 0) {
					nowStatus = Status::SelectSinglePlayer;
					SelectedIndex = 0;
					UI::Instance->showBlock(screen, Setting::Block::SelectSinglePlayer);
				}
				//讀取舊紀錄
				else if (SelectedIndex == 1) {
					nowStatus = Status::Read;
					SelectedIndex = 0;
					nowDataPage = 1;
					FileName = "";
					getTXT();
					UI::Instance->showBlock(screen, Setting::Block::Read);
					UI::Instance->showSaveData(TXTFiles, nowDataPage);
				}
				//返回上一頁
				else if (SelectedIndex == 2) {
					nowStatus = Status::SelectMode;
					SelectedIndex = 0;
					UI::Instance->showBlock(screen, Setting::Block::SelectMode);
				}
				break;

			case Key::ESC:
				nowStatus = Status::SelectMode;
				SelectedIndex = 0;
				UI::Instance->showBlock(screen, Setting::Block::SelectMode);
				break;
			}
		}
		//單人遊戲選單
		else if (nowStatus == Status::SelectSinglePlayer) {
			switch (input) {
				//移動實心選項
			case Key::LEFT:
			case Key::UP:
			case Key::RIGHT:
			case Key::DOWN:
				MoveSolidMenuOption(input);
				break;

			case Key::ENTER:
				//玩家先攻
				if (SelectedIndex == 0) {
					ChessBoard::Instance->init();
					screen = Screen::Playing;
					NewGame(1);
				}
				//電腦先攻
				else if (SelectedIndex == 1) {
					ChessBoard::Instance->init();
					screen = Screen::Playing;
					NewGame(0);
				}
				break;

			case Key::ESC:
				nowStatus = Status::SinglePlayerMenu;
				SelectedIndex = 0;
				UI::Instance->showBlock(screen, Setting::Block::SinglePlayerMenu);
				break;
			}
		}
		//雙人遊戲選單(開始新遊戲 or 讀取舊檔)
		else if (nowStatus == Status::DuoPlayerMenu) {
			switch (input) {
				//移動實心選項
			case Key::LEFT:
			case Key::UP:
			case Key::RIGHT:
			case Key::DOWN:
				MoveSolidMenuOption(input);
				break;

			case Key::ENTER:
				//開始新遊戲
				if (SelectedIndex == 0) {
					nowStatus = Status::SelectPlayer;
					SelectedIndex = 0;
					UI::Instance->showBlock(screen, Setting::Block::SelectPlayer);
				}
				//讀取舊紀錄
				else if (SelectedIndex == 1) {
					nowStatus = Status::Read;
					SelectedIndex = 0;
					nowDataPage = 1;
					FileName = "";
					getTXT();
					UI::Instance->showBlock(screen, Setting::Block::Read);
					UI::Instance->showSaveData(TXTFiles, nowDataPage);
				}
				//返回上一頁
				else if (SelectedIndex == 2) {
					nowStatus = Status::SelectMode;
					SelectedIndex = 0;
					UI::Instance->showBlock(screen, Setting::Block::SelectMode);
				}
				break;

			case Key::ESC:
				nowStatus = Status::SelectMode;
				SelectedIndex = 0;
				UI::Instance->showBlock(screen, Setting::Block::SelectMode);
				break;
			}
		}
		//雙人遊戲->選擇哪方先攻
		else if (nowStatus == Status::SelectPlayer) {
			switch (input) {
				//移動實心選項
			case Key::LEFT:
			case Key::UP:
			case Key::RIGHT:
			case Key::DOWN:
				MoveSolidMenuOption(input);
				break;

			case Key::ENTER:
				ChessBoard::Instance->init();
				screen = Screen::Playing;
				//紅方先攻
				if (SelectedIndex == 0) {
					NewGame(1);
				}
				//黑方先攻
				else if (SelectedIndex == 1) {
					NewGame(0);
				}
				break;

			case Key::ESC:
				nowStatus = Status::DuoPlayerMenu;
				SelectedIndex = 0;
				UI::Instance->showBlock(screen, Setting::Block::DuoPlayerMenu);
				break;
			}
		}
		//系統選項
		else if (nowStatus == Status::Option) {
			switch (input) {
				//移動實心選項
			case Key::LEFT:
			case Key::UP:
			case Key::RIGHT:
			case Key::DOWN:
				MoveSolidMenuOption(input);
				break;

			case Key::ENTER:
				//系統音效
				if (SelectedIndex == 0) {
					nowStatus = Status::Sound;
					SelectedIndex = 0;
					UI::Instance->showBlock(screen, Setting::Block::Sound);
				}
				//自定義棋盤
				else if (SelectedIndex == 1) {
					ChessBoard::Instance->clear();
					screen = Screen::Making;
					nowStatus = Status::SelectChess;
					NewMake();
					break;
				}
				//返回上一頁
				else if (SelectedIndex == 2) {
					nowStatus = Status::Beginning;
					SelectedIndex = 0;
					UI::Instance->showBlock(screen, Setting::Block::Main);
				}
				break;

			case Key::ESC:
				nowStatus = Status::Beginning;
				SelectedIndex = 0;
				UI::Instance->showBlock(screen, Setting::Block::Main);
				break;
			}
		}
		//音效設定
		else if (nowStatus == Status::Sound) {
			switch (input) {
				//移動實心選項
			case Key::LEFT:
			case Key::UP:
			case Key::RIGHT:
			case Key::DOWN:
				MoveSolidMenuOption(input);
				break;

			case Key::ENTER:
				//無音效
				if (SelectedIndex == 0) {
					musicMode = Music::quiet;
				}
				//一般音效
				else if (SelectedIndex == 1) {
					musicMode = Music::normal;
					playMusic(musicMode, Music::Chess);
				}
				//特殊音效
				else if (SelectedIndex == 2) {
					musicMode = Music::noise;
					playMusic(musicMode, Music::Chess_People);
				}
				SelectedIndex = 0;
				nowStatus = Status::Beginning;
				UI::Instance->showBlock(screen, Setting::Block::Main);
				break;
			case Key::ESC:
				nowStatus = Status::Option;
				SelectedIndex = 0;
				UI::Instance->showBlock(screen, Setting::Block::Option);
				break;
			}
		}
	}
	//若畫面位於 雙人對戰
	else if (screen == Screen::Playing) {
		//選棋模式
		if (nowStatus == Status::SelectChess) {
			switch (input) {
				//移動游標位置
			case Key::LEFT:
			case Key::RIGHT:
			case Key::DOWN:
			case Key::UP:
				//呼叫移動棋盤座標
				MoveBoardCursor(input);
				break;

			case Key::ENTER:
				//選棋成功
				if (ChessSelect(BoardCursor)) {
					nowStatus = Status::MoveChess;
					UI::Instance->showSelectedChess(SelectedChess.first);

					playMusic(musicMode, Music::Sound::Select);
					//游標回到原本的位置
					UI::Instance->gotoBoardXY(BoardCursor);
				}
				else {
					cout << '\a';
				}
				break;

				//暫停遊戲
			case Key::ESC:
				nowStatus = Status::pause;
				UI::Instance->showBlock(screen, Setting::Block::Pause);
				SelectedIndex = 0;
				//游標移動到繼續遊戲的地方
				UI::Instance->gotoXY(MenuList[make_pair(screen, nowStatus)][0].second);
				playMusic(musicMode, Music::Sound::Select);
				break;
				//儲存遊戲
			case Key::Save:
				nowStatus = Status::Store;
				UI::Instance->showBlock(screen, Setting::Block::Store);
				//將儲存用的字串清空
				FileName.clear();
				//讓游標回到第一個字的位置
				UI::Instance->gotoXY(35, 13);
				break;
				//呼叫幫助
			case Key::H:
				nowStatus = Status::help;
				UI::Instance->showBlock(screen, Setting::Block::Help);
				playMusic(musicMode, Music::Select);
				UI::Instance->gotoXY(0, 0);
				break;
				//悔棋
			case Key::Z:
				nowStatus = Status::regret;
				UI::Instance->showBlock(screen, Setting::Block::Regret);
				SelectedIndex = 0;
				//游標移動到「是」
				UI::Instance->gotoXY(MenuList[make_pair(screen, nowStatus)][0].second);
				playMusic(musicMode, Music::Sound::Select);
				break;
			case Key::LogLeft:
				turnLogPage(-1);
				break;
			case Key::LogRight:
				turnLogPage(1);
				break;
			}
		}
		//移動棋子模式
		else if (nowStatus == Status::MoveChess) {
			switch (input) {
				//移動游標位置
			case Key::LEFT:
			case Key::RIGHT:
			case Key::DOWN:
			case Key::UP:
				//呼叫移動棋盤座標
				MoveBoardCursor(input);
				break;

			case Key::ENTER:
				//取消選棋
				if (BoardCursor.first == SelectedChess.second.first && BoardCursor.second == SelectedChess.second.second) {
					SelectedChess.first = 0;
					nowStatus = Status::SelectChess;
					UI::Instance->showSelectedChess(0); //將現在選哪顆棋的顯示關閉
					//未完成
					UI::Instance->DrawBoard(); //先偷懶
					//將游標移回
					UI::Instance->gotoBoardXY(BoardCursor);
				}
				else {
					int result = ChessMove(BoardCursor);
					//遊戲勝利
					if (result == 2) {
						//中斷函式
						return;
					}
					//正確移動
					else if (result == 1) {
						nowStatus = Status::SelectChess;
						UI::Instance->DrawBoard();
						//將現在選哪顆棋的顯示關閉
						UI::Instance->showSelectedChess(0);
						//將游標移動回來
						UI::Instance->gotoBoardXY(BoardCursor);
						NextPlayer();
					}
					//移動失敗
					else if (result == 0) {
						cout << '\a';
					}

				}
				break;
			case Key::Save:
				nowStatus = Status::Store;
				UI::Instance->showBlock(screen, Setting::Block::Store);
				//將儲存用的字串清空
				FileName.clear();
				//讓游標回到第一個字的位置
				UI::Instance->gotoXY(35, 13);
				break;
			case Key::H:
				nowStatus = Status::help;
				UI::Instance->showBlock(screen, Setting::Block::Help);
				playMusic(musicMode, Music::Select);
				break;

			case Key::Z:
				nowStatus = Status::regret;
				UI::Instance->showBlock(screen, Setting::Block::Regret);

				SelectedIndex = 0; //選項設為0
				UI::Instance->gotoXY(MenuList[make_pair(screen, nowStatus)][0].second);
				playMusic(musicMode, Music::Sound::Select);
				break;

			case Key::ESC:
				nowStatus = Status::pause;
				//顯示暫停區塊
				UI::Instance->showBlock(screen, Setting::Block::Pause);

				SelectedIndex = 0; //選項設為0
				//將游標移到繼續遊戲
				UI::Instance->gotoXY(MenuList[make_pair(screen, nowStatus)][0].second);
				playMusic(musicMode, Music::Sound::Select);
				break;
			case Key::LogLeft:
				turnLogPage(-1);
				break;
			case Key::LogRight:
				turnLogPage(1);
				break;
			}
		}
		//悔棋模式
		else if (nowStatus == Status::regret) {
			switch (input) {
				//移動選項
			case Key::LEFT:
			case Key::UP:
			case Key::RIGHT:
			case Key::DOWN:
				MoveMenuOption(input);
				break;

			case Key::ENTER:

				//是
				if (SelectedIndex == 0) {
					if (Regret()) {
						nowStatus = Status::SelectChess;
						//避免現在在移動棋子模式而造成錯誤
						SelectedChess.first = 0;
						//游標回到原本的位置
						UI::Instance->gotoBoardXY(BoardCursor);
					}
					//無法悔棋
					else {
						//播放音效
						playMusic(musicMode, Music::CannotRegret);
						//將"你沒有什麼好後悔"叫出來
						UI::Instance->showBlock(Screen::Playing, Setting::Block::CannotRegret);
						nowStatus = Status::Cannot_regret;
					}
				}
				//否
				else if (SelectedIndex == 1) {
					//未完成，偷懶，先這樣
					UI::Instance->DrawBoard();
					//代表現在在移動棋子模式
					if (SelectedChess.first != 0) {
						nowStatus = Status::MoveChess;
						ChessSelect(SelectedChess.second);
					}
					//代表現在在選擇棋子模式
					else {
						nowStatus = Status::SelectChess;
					}
					//游標回到原本的位置
					UI::Instance->gotoBoardXY(BoardCursor);
				}

				break;

			case Key::Z:
			case Key::ESC:

				UI::Instance->DrawBoard();
				//代表現在在移動棋子模式
				if (SelectedChess.first != 0) {
					nowStatus = Status::MoveChess;
					ChessSelect(SelectedChess.second);
				}
				//代表現在在選擇棋子模式
				else {
					nowStatus = Status::SelectChess;
				}
				//游標回到原本的位置
				UI::Instance->gotoBoardXY(BoardCursor);
				//播放選取棋子的音效
				playMusic(musicMode, Music::Sound::Select);
				break;
			}
		}
		//暫停(選單)
		else if (nowStatus == Status::pause) {
			switch (input) {
				//移動選項
			case Key::LEFT:
			case Key::UP:
			case Key::RIGHT:
			case Key::DOWN:
				MoveMenuOption(input);
				break;

			case Key::ENTER:
				//選取繼續遊戲
				if (SelectedIndex == 0) {
					Resume();
				}
				//選取重新開始
				else if (SelectedIndex == 1) {
					nowStatus = Status::pause_restart;
					UI::Instance->showBlock(Screen::Playing, Setting::Block::Restart);
					SelectedIndex = 0;
					//游標移到是
					UI::Instance->gotoXY(MenuList[make_pair(screen, nowStatus)][0].second);

				}
				//回主選單
				else if (SelectedIndex == 2) {
					screen = Screen::MainMenu;
					nowStatus = Status::Beginning;
					SelectedIndex = 0;
					UI::Instance->showScreen(screen);
					UI::Instance->gotoXY(47, 13);
				}
				//儲存遊戲
				else if (SelectedIndex == 3) {
					nowStatus = Status::Store;
					UI::Instance->showBlock(screen, Setting::Block::Store);
					//將儲存用的字串清空
					FileName.clear();
					//讓游標回到第一個字的位置
					UI::Instance->gotoXY(35, 13);
				}
				//離開遊戲
				else if (SelectedIndex == 4) {
					UI::Instance->CleanScreen();
					UI::Instance->gotoXY(0, 0);
					exit(1);
				}
				break;

			case Key::ESC:
				Resume();
				//播放音效
				playMusic(musicMode, Music::Sound::Select);
				break;
			}
		}
		//幫助
		else if (nowStatus == Status::help) {
			switch (input) {
			case Key::ESC:
			case Key::H:
				Resume();
				break;
			}

		}
		//確定重新開始?
		else if (nowStatus == Status::pause_restart) {
			switch (input) {
				//移動選項
			case Key::LEFT:
			case Key::UP:
			case Key::RIGHT:
			case Key::DOWN:
				MoveMenuOption(input);
				break;

			case Key::ESC:
				nowStatus = Status::pause;
				//顯示暫停區塊
				UI::Instance->showBlock(Screen::Playing, Setting::Block::Pause);

				//游標回到重新開始
				SelectedIndex = 0;
				MoveMenuOption(Key::DOWN, false);
				break;
			case Key::ENTER:
				//選取是
				if (SelectedIndex == 0) {
					//棋盤進行初始化
					auto history = ChessBoard::Instance->CheckHistory();
					if (history.first) {
						ChessBoard::Instance->load(history.second.first, history.second.second);
						NewGame(history.second.first);//重新新遊戲
					}
					else {
						ChessBoard::Instance->init();
						NewGame(1);//重新新遊戲
					}

				}
				//選取否
				else if (SelectedIndex == 1) {
					nowStatus = Status::pause;
					//顯示暫停區塊
					UI::Instance->showBlock(Screen::Playing, Setting::Block::Pause);

					//游標回到重新開始
					SelectedIndex = 0;
					MoveMenuOption(Key::DOWN, false);
				}
				break;
			}
		}
	}
	else if (screen == Screen::Making) {
		//選要放的棋子
		if (nowStatus == Status::SelectChess) {
			switch (input) {
				//移動實心選項
			case Key::LEFT:
			case Key::UP:
			case Key::RIGHT:
			case Key::DOWN:
				MoveMakeCursor(input);
				SelectedChess.first = SelectedIndex;
				break;

			case Key::ENTER:
				nowStatus = Status::MoveChess;
				SelectedChess.first = SelectedIndex;
				UI::Instance->gotoBoardXY(BoardCursor);
				playMusic(musicMode, Music::Sound::Select);
				break;
			case Key::ESC:
				nowStatus = Status::pause;
				UI::Instance->showBlock(screen, Setting::Block::Pause);
				SelectedIndex = 0;
				//游標移動到繼續遊戲的地方
				UI::Instance->gotoXY(MenuList[make_pair(screen, nowStatus)][0].second);
				playMusic(musicMode, Music::Sound::Select);
				break;
			case Key::H:
				HansMem = Status::SelectChess;
				nowStatus = Status::help;
				UI::Instance->showBlock(screen, Setting::Block::Help);
				playMusic(musicMode, Music::Select);
				UI::Instance->gotoXY(0, 0);
				break;
			case Key::Save:
				HansMem = Status::SelectChess;
				if (ChessBoard::Instance->getChessNum(1) == 0 || ChessBoard::Instance->getChessNum(8) == 0) {
					UI::Instance->showBlock(screen, Setting::Block::Warning);
					nowStatus = Status::Warning;
					playMusic(musicMode, Music::Error);
					return;
				}
				nowStatus = Status::SelectPlayer;
				UI::Instance->showBlock(Screen::Making, Setting::Block::SelectPlayer);
				SelectedIndex = 0;
				//讓游標移到黑
				UI::Instance->gotoXY(MenuList[make_pair(screen, nowStatus)][0].second);
				break;
			}
		}
		else if (nowStatus == Status::MoveChess) {
			switch (input) {
				//移動游標位置
			case Key::LEFT:
			case Key::RIGHT:
			case Key::DOWN:
			case Key::UP:
				//呼叫移動棋盤座標
				MoveBoardCursor(input);
				break;

			case Key::ENTER:
				if (checkMake()) {
					if (ChessBoard::Instance->check(make_pair(BoardCursor.second, BoardCursor.first)))
						ChessBoard::Instance->modify(ChessBoard::Instance->check(make_pair(BoardCursor.second, BoardCursor.first)), make_pair(BoardCursor.second, BoardCursor.first), make_pair(-1, -1));
					if (SelectedChess.first)
						ChessBoard::Instance->modify(SelectedChess.first, make_pair(-1, -1), make_pair(BoardCursor.second, BoardCursor.first));

					UI::Instance->showBlock(screen, Setting::Block::ChessNums);
					UI::Instance->DrawBoard();
					//將游標移動回來
					UI::Instance->gotoBoardXY(BoardCursor);
					playChessSound(musicMode, SelectedChess.first);
				}
				else {
					cout << '\a';
				}
				break;
			case Key::H:
				HansMem = Status::MoveChess;
				nowStatus = Status::help;
				UI::Instance->showBlock(screen, Setting::Block::Help);
				playMusic(musicMode, Music::Select);
				UI::Instance->gotoXY(0, 0);
				break;
			case Key::Save:
				HansMem = Status::MoveChess;
				if (ChessBoard::Instance->getChessNum(1) == 0 || ChessBoard::Instance->getChessNum(8) == 0) {
					UI::Instance->showBlock(screen, Setting::Block::Warning);
					nowStatus = Status::Warning;
					playMusic(musicMode, Music::Error);
					return;
				}
				nowStatus = Status::SelectPlayer;
				UI::Instance->showBlock(Screen::Making, Setting::Block::SelectPlayer);
				SelectedIndex = 0;
				//讓游標移到黑
				UI::Instance->gotoXY(MenuList[make_pair(screen, nowStatus)][0].second);
				break;
			case Key::ESC:
				UI::Instance->gotoXY(MenuList[make_pair(Screen::Making, Status::SelectChess)][SelectedChess.first].second);
				nowStatus = SelectChess;
				break;
			}
		}
		else if (nowStatus == Status::pause) {
			switch (input) {
				//移動選項
			case Key::LEFT:
			case Key::UP:
			case Key::RIGHT:
			case Key::DOWN:
				MoveMenuOption(input);
				break;

			case Key::ENTER:
				//選取繼續遊戲
				if (SelectedIndex == 0) {
					UI::Instance->DrawBoard();
					UI::Instance->gotoXY(MenuList[make_pair(Screen::Making, Status::SelectChess)][SelectedChess.first].second);
					SelectedIndex = SelectedChess.first;
					nowStatus = SelectChess;
				}
				//選取重新開始
				else if (SelectedIndex == 1) {
					nowStatus = Status::pause_restart;
					UI::Instance->showBlock(Screen::Playing, Setting::Block::Restart);
					SelectedIndex = 0;
					//游標移到是
					UI::Instance->gotoXY(MenuList[make_pair(screen, nowStatus)][0].second);

				}
				//回主選單
				else if (SelectedIndex == 2) {
					screen = Screen::MainMenu;
					nowStatus = Status::Beginning;
					SelectedIndex = 0;
					UI::Instance->showScreen(screen);
					UI::Instance->gotoXY(47, 13);
				}
				//儲存遊戲 選擇先攻顏色
				else if (SelectedIndex == 3) {
					HansMem = Status::pause;
					if (ChessBoard::Instance->getChessNum(1) == 0 || ChessBoard::Instance->getChessNum(8) == 0) {
						UI::Instance->showBlock(screen, Setting::Block::Warning);
						nowStatus = Status::Warning;
						playMusic(musicMode, Music::Error);
						return;
					}
					nowStatus = Status::SelectPlayer;
					UI::Instance->showBlock(Screen::Making, Setting::Block::SelectPlayer);
					SelectedIndex = 0;
					//讓游標移到黑
					UI::Instance->gotoXY(MenuList[make_pair(screen, nowStatus)][0].second);
				}
				//離開遊戲
				else if (SelectedIndex == 4) {
					UI::Instance->CleanScreen();
					UI::Instance->gotoXY(0, 0);
					exit(1);
				}
				break;

			case Key::ESC:
				UI::Instance->DrawBoard();
				UI::Instance->gotoXY(MenuList[make_pair(Screen::Making, Status::SelectChess)][SelectedChess.first].second);
				SelectedIndex = SelectedChess.first;
				nowStatus = SelectChess;
				playMusic(musicMode, Music::Sound::Select);
				break;
			}
		}
		else if (nowStatus == Status::pause_restart) {
			switch (input) {
				//移動選項
			case Key::LEFT:
			case Key::UP:
			case Key::RIGHT:
			case Key::DOWN:
				MoveMenuOption(input);
				break;

			case Key::ESC:
				nowStatus = Status::pause;
				//顯示暫停區塊
				UI::Instance->showBlock(Screen::Making, Setting::Block::Pause);

				//游標回到重新開始
				SelectedIndex = 0;
				MoveMenuOption(Key::DOWN, false);
				break;
			case Key::ENTER:
				//選取是
				if (SelectedIndex == 0) {
					//棋盤進行初始化
					ChessBoard::Instance->clear();
					NewMake();//重新定義
				}
				//選取否
				else if (SelectedIndex == 1) {
					nowStatus = Status::pause;
					//顯示暫停區塊
					UI::Instance->showBlock(Screen::Making, Setting::Block::Pause);

					//游標回到重新開始
					SelectedIndex = 0;
					MoveMenuOption(Key::DOWN, false);
				}
				break;
			}
		}
		else if (nowStatus == Status::SelectPlayer) {
			switch (input) {
				//移動選項
			case Key::LEFT:
			case Key::UP:
			case Key::RIGHT:
			case Key::DOWN:
				MoveMenuOption(input);
				break;

			case Key::ESC:
				if (HansMem == Status::SelectChess) {
					UI::Instance->DrawBoard();
					UI::Instance->gotoXY(MenuList[make_pair(Screen::Making, Status::SelectChess)][SelectedChess.first].second);
					SelectedIndex = SelectedChess.first;
					nowStatus = SelectChess;
				}
				else if (HansMem == Status::MoveChess) {
					UI::Instance->DrawBoard();
					nowStatus = Status::MoveChess;
					SelectedIndex = SelectedChess.first;
					UI::Instance->gotoBoardXY(BoardCursor);
				}
				else if (HansMem == Status::pause) {
					nowStatus = Status::pause;
					//顯示暫停區塊
					UI::Instance->showBlock(Screen::Making, Setting::Block::Pause);

					//游標回到重新開始
					SelectedIndex = 0;
					MoveMenuOption(Key::DOWN, false);
					MoveMenuOption(Key::DOWN, false);
					MoveMenuOption(Key::DOWN, false);
				}
				break;
			case Key::ENTER:
				player = SelectedIndex;
				nowStatus = Status::Store;
				UI::Instance->showBlock(Screen::Playing, Setting::Block::Store);
				//將儲存用的字串清空
				FileName.clear();
				//讓游標回到第一個字的位置
				UI::Instance->gotoXY(35, 13);
				break;
			}
		}
		else if (nowStatus == Status::help) {
			switch (input) {
			case Key::LEFT:
			case Key::UP:
				cout << '\a';
				break;
			case Key::RIGHT:
			case Key::DOWN:
				nowStatus = Status::help_2;
				playMusic(musicMode, Music::Sound::Select);
				UI::Instance->showBlock(screen, Setting::Block::Help_2);
				UI::Instance->gotoXY(0, 0);
				break;
			case Key::ESC:
			case Key::H:
				UI::Instance->DrawBoard();
				if (HansMem == Status::SelectChess) {
					UI::Instance->gotoXY(MenuList[make_pair(Screen::Making, Status::SelectChess)][SelectedChess.first].second);
					SelectedIndex = SelectedChess.first;
					nowStatus = SelectChess;
				}
				else if (HansMem == Status::MoveChess) {
					nowStatus = Status::MoveChess;
					SelectedIndex = SelectedChess.first;
					UI::Instance->gotoBoardXY(BoardCursor);
				}
				break;
			}
		}
		else if (nowStatus == Status::help_2) {
			switch (input) {
			case Key::LEFT:
			case Key::UP:
				nowStatus = Status::help;
				playMusic(musicMode, Music::Sound::Select);
				UI::Instance->showBlock(screen, Setting::Block::Help);
				UI::Instance->gotoXY(0, 0);
				break;
			case Key::RIGHT:
			case Key::DOWN:
				cout << '\a';
				break;
			case Key::ESC:
			case Key::H:
				UI::Instance->DrawBoard();
				if (HansMem == Status::SelectChess) {
					UI::Instance->gotoXY(MenuList[make_pair(Screen::Making, Status::SelectChess)][SelectedChess.first].second);
					SelectedIndex = SelectedChess.first;
					nowStatus = SelectChess;
				}
				else if (HansMem == Status::MoveChess) {
					nowStatus = Status::MoveChess;
					SelectedIndex = SelectedChess.first;
					UI::Instance->gotoBoardXY(BoardCursor);
				}
				break;
			}
		}
	}
}


//選取棋子
//傳入一個棋盤座標(9*10)
bool GameSystem::ChessSelect(Coordinate co)
{
	static const wchar_t list[] = L"　將士象車馬包卒帥仕相車傌炮兵";
	int chess = ChessBoard::Instance->check(make_pair(co.second, co.first));
	if (chess == 0) {
		return false;
	}
	//選到對方的棋子
	else if ((player == 0 && chess > 7) || (player == 1 && chess <= 7)) {
		return false;
	}
	auto available = ChessBoard::Instance->filter(make_pair(co.second, co.first));
	if (available->size() == 0) {
		return false;
	}

	AvailableMove.clear();
	SelectedChess.first = chess;
	SelectedChess.second = co; //選的那顆棋的座標

	for (auto item : *available) {
		UI::Instance->gotoBoardXY(make_pair(item.second.second, item.second.first));
		//空格子：將背景設為灰底
		if (item.first == 0) {
			UI::Instance->SetTextColor(Setting::Color::gray, Setting::Color::white);
			cout << "　";
		}
		//有敵方棋子
		else {
			UI::Instance->SetTextColor(Setting::Color::black, Setting::Color::purple, false, true);
			wcout << list[item.first];
		}
		//將座標轉為UI棋盤(->X,向下為y)的格式
		AvailableMove.push_back(make_pair(item.first, make_pair(item.second.second, item.second.first)));
	}
	delete available;
	return true;
}

//重置遊戲
//傳入參數player，決定第一顆棋子誰下
void GameSystem::NewGame(int player)
{
	//狀態設為選取旗子
	nowStatus = Status::SelectChess;
	SelectedIndex = 0;
	SelectedChess.first = 0;
	AvailableMove.clear();

	//重繪畫面
	UI::Instance->showScreen(Screen::Playing);

	//設置現在玩家
	this->player = player;
	UI::Instance->showPlayer(player);

	FileName = "";
	//清除Log
	log.clear();
	LogPage = 1;
	nowLogPage = 1;




	bool result = ChessBoard::Instance->ifCheckmate(player % 2);
	//下一手可能會將軍
	if (result) {
		UI::Instance->showGeneral(true, player % 2);
		//播放將軍音效
		playMusic(musicMode, Music::Sound::General);
	}
	else {
		bool result = ChessBoard::Instance->ifCheckmate((player + 1) % 2);
		if (result) {
			UI::Instance->showGeneral(true, (player + 1) % 2);
			//播放將軍音效
			playMusic(musicMode, Music::Sound::General);
		}
		else {
			UI::Instance->showGeneral(false);
		}
	}

	//重新設置棋盤游標
	BoardCursor = make_pair(0, 0);
	UI::Instance->gotoBoardXY(BoardCursor);
	//單人遊戲且電腦先攻
	if (GameMode == 1 && player == 0) {
		Sleep(500);
		UI::Instance->showAdditionText(L"Brandon思考中...");
		AIChessMove();

		NextPlayer();
	}



}

void GameSystem::WinGame()
{
	if (musicMode == Music::MusicMode::noise) {
		//播放將或帥死亡的音效(塔里克)
		playMusic(musicMode, Music::Sound::Dead);
		//讓音效放完
		Sleep(2500);
	}
	//顯示Victory區塊
	UI::Instance->showBlock(screen, Setting::Block::Victory);
	UI::Instance->gotoXY(43, 12);
	//紅方獲勝
	if (player == 1) {
		UI::Instance->SetTextColor(Setting::Color::red, Setting::Color::black, true);
		cout << "紅　方";
	}
	//黑方獲勝
	else if (player == 0) {
		UI::Instance->SetTextColor(Setting::Color::white, Setting::Color::black);
		cout << "黑　方";
	}
	//游標回到"請按任意鍵繼續..."
	UI::Instance->gotoXY(63, 15);
	//播放勝利音效
	if (musicMode != Music::MusicMode::quiet) {
		//播放勝利音效
		playMusic(musicMode, Music::Sound::Victory);
	}
	Sleep(1200);
	nowStatus = Status::Win;
	//清除緩衝區，避免使用者在電腦思考時，誤觸按鍵

	Sleep(100);
	while (_kbhit()) {
		char c = _getch();
	}
}

//移動棋子：回傳 0：移動有誤、1：正確移動、2：遊戲勝利
int GameSystem::ChessMove(Coordinate destination)
{
	//搜尋可走的位置有沒有傳入的座標
	for (auto item : AvailableMove) {
		if (item.second == destination) {
			//呼叫log紀錄
			log.push(SelectedChess.first, make_pair(SelectedChess.second.second, SelectedChess.second.first), make_pair(destination.second, destination.first));
			//有吃掉別人的棋
			if (item.first != 0) {
				//將被吃掉的那顆棋移到(-1,-1) (即移除)
				ChessBoard::Instance->modify(item.first, make_pair(item.second.second, item.second.first), make_pair(-1, -1));
				//吃掉帥或將

				if ((item.first == 1 && ChessBoard::Instance->getChessNum(1) == 0) || (item.first == 8 && ChessBoard::Instance->getChessNum(8) == 0)) {
					//播放下棋音效
					playChessSound(musicMode, SelectedChess.first);
					//由於這裡直接return，因此為了使視覺效果接上，故直接修改並呼叫UI
					ChessBoard::Instance->modify(SelectedChess.first, make_pair(SelectedChess.second.second, SelectedChess.second.first), make_pair(destination.second, destination.first));
					UI::Instance->DrawBoard();
					//為了使視覺效果顯現，故停止0.5秒
					Sleep(500);

					UI::Instance->gotoBoardXY(BoardCursor);
					//呼叫勝利函式
					UI::Instance->showGeneral(false);
					WinGame();
					return 2;
				}
			}

			//多一頁
			if ((log.getLength() - 1) % 17 == 0) {
				if ((log.getLength() - 1) != 0) {
					LogPage++;
					turnLogPage(1);
					UI::Instance->showLogPage(nowLogPage, LogPage);
				}
			}
			if (nowLogPage == LogPage) {
				UI::Instance->showLog((log.getLength() - 1), log.getchingChongLog(log.getLength() - 1));
			}

			ChessBoard::Instance->modify(SelectedChess.first, make_pair(SelectedChess.second.second, SelectedChess.second.first), make_pair(destination.second, destination.first));

			//播放下棋音效
			playChessSound(musicMode, SelectedChess.first);

			//回歸預設狀態
			SelectedChess.first = 0;


			bool result = ChessBoard::Instance->ifCheckmate((player + 1) % 2);
			//下一手可能會將軍
			if (result) {
				UI::Instance->showGeneral(true, (player + 1) % 2);
				//播放將軍音效
				playMusic(musicMode, Music::Sound::General);
			}
			else {
				bool result = ChessBoard::Instance->ifCheckmate((player + 2) % 2);
				if (result) {
					UI::Instance->showGeneral(true, (player + 2) % 2);
					//播放將軍音效
					playMusic(musicMode, Music::Sound::General);
				}
				else {
					UI::Instance->showGeneral(false);
				}
			}


			return 1;
		}
	}


	return 0;
}

//儲存遊戲
bool GameSystem::StoreGame()
{
	ofstream file;
	string fileName = "SaveData//" + FileName + ".txt";
	file.open(fileName, ios::out);
	//開啟檔案失敗
	if (!file) {
		return false;
	}
	auto board = ChessBoard::Instance->getBoard();
	for (auto row : board) {
		for (int i = 0; i < row.size(); i++) {
			if (i != 0) file << " ";
			file << row[i];
		}
		file << endl;
	}
	file << player;
	file.close();
	return true;
}

//移動Log的頁面
//參數：+1為向後翻，-1為向前翻
void GameSystem::turnLogPage(int directon)
{
	nowLogPage += directon;
	if (nowLogPage <= 0) {
		nowLogPage = 1;
		cout << '\a';
		return;
	}
	else if (nowLogPage > LogPage) {
		nowLogPage--;
		cout << '\a';
		return;
	}

	UI::Instance->clearLog();
	for (int i = (nowLogPage - 1) * 17; i < nowLogPage * 17 && i < log.getLength(); i++) {
		UI::Instance->showLog(i, log.getchingChongLog(i));
	}
	UI::Instance->showLogPage(nowLogPage, LogPage);

	//游標回到原本的位置
	UI::Instance->gotoBoardXY(BoardCursor);
}

// 悔棋
bool GameSystem::Regret()
{
	//若紀錄少於兩個則不能進行悔棋
	if (log.getLength() < 2) {
		return false;
	}
	auto record = log.pop();
	for (auto item : record) {
		ChessBoard::Instance->modify(item.first, item.second.second, item.second.first);
	}

	//少一頁
	if (ceil((double)log.getLength() / 17) < LogPage) {
		if (LogPage != 1)LogPage--;
	}
	//自動翻到更新的那一頁
	nowLogPage = LogPage - 1;
	turnLogPage(1);
	//顯示頁數
	UI::Instance->showLogPage(nowLogPage, LogPage);
	//重畫棋盤
	UI::Instance->DrawBoard();

	//下一手可能會將軍

	bool result = ChessBoard::Instance->ifCheckmate((player + 1) % 2);
	//下一手可能會將軍
	if (result) {
		UI::Instance->showGeneral(true, (player + 1) % 2);
		//播放將軍音效
		playMusic(musicMode, Music::Sound::General);
	}
	else {
		bool result = ChessBoard::Instance->ifCheckmate((player + 2) % 2);
		if (result) {
			UI::Instance->showGeneral(true, (player + 2) % 2);
			//播放將軍音效
			playMusic(musicMode, Music::Sound::General);
		}
		else {
			UI::Instance->showGeneral(false);
		}
	}

	return true;
}

//讀取檔案
//參數：傳入欲開啟的檔案名稱(含附檔名)
//回傳代碼： 0：檔案開啟異常 1：檔案格式錯誤 2：成功讀取
int GameSystem::LoadGame(string fileName)
{
	ifstream file;
	string tmp = "SaveData//" + fileName + ".txt";
	file.open(tmp, ios::in);
	//檔案開啟成功
	if (file) {
		tmp = "";
		int chessNum, firstPlayer;
		vector<vector<int>> board(10, vector<int>(9));
		for (int row = 0; row < 10; row++) {
			for (int column = 0; column < 9; column++) {
				//若莫名的到達檔案底部，代表該文件錯誤
				if (file.eof()) {
					file.close();
					return 1;
				}
				file >> tmp;

				//若檔案格式錯誤，則回傳1
				for (auto c : tmp) {
					if (!isdigit(c)) {
						file.close();
						return 1;
					}
				}
				chessNum = stoi(tmp);
				//若輸入格式錯誤
				if (chessNum > 14) {
					file.close();
					return 1;
				}
				board[row][column] = chessNum;
			}
		}
		if (!file.eof()) {
			file >> tmp;
			//最後一行應只有一個數字
			if (tmp.size() != 1 || !isdigit(tmp[0])) {
				file.close();
				return 1;
			}
			this->player = stoi(tmp);
		}
		else {
			file.close();
			return 1;
		}
		ChessBoard::Instance->load(this->player, board);
		file.close();
		return 2;
	}
	else {
		file.close();
		return 0;
	}

}

//移動選項
//參數：+1為向下或右，-1為向上或左
void GameSystem::MoveMenuOption(Key input, bool musicplay)
{
	int direction;
	switch (input) {
	case UP:
	case LEFT:
		direction = -1;
		break;

	case DOWN:
	case RIGHT:
		direction = 1;
		break;

	default:
		return;
	}

	auto nowMenu = MenuList[make_pair(screen, nowStatus)];

	//移到原本的選項改顏色
	UI::Instance->SetTextColor(Setting::Color::white, Setting::Color::black);
	UI::Instance->gotoXY(nowMenu[SelectedIndex].second);
	wcout << nowMenu[SelectedIndex].first;

	//移到下個選項
	SelectedIndex += direction;
	if (SelectedIndex < 0) {
		SelectedIndex = (int)(nowMenu.size() - 1);
	}
	else if (SelectedIndex >= nowMenu.size()) {
		SelectedIndex %= nowMenu.size();
	}

	//輸出下個選項移動游標
	UI::Instance->SetTextColor(Setting::Color::black, Setting::Color::white, false, true);
	UI::Instance->gotoXY(nowMenu[SelectedIndex].second);
	wcout << nowMenu[SelectedIndex].first;
	//播放音效
	if (musicplay) {
		playMusic(musicMode, Music::MoveCursor);
	}

	//游標回到前方(輸出完上方字會位移到)
	UI::Instance->gotoXY(nowMenu[SelectedIndex].second);
}

// 移動實心選單上的游標(傳入上下左右)
void GameSystem::MoveSolidMenuOption(Key input)
{
	int direction;
	switch (input) {
	case UP:
	case LEFT:
		direction = -1;
		break;

	case DOWN:
	case RIGHT:
		direction = 1;
		break;

	default:
		return;
	}

	auto nowMenu = SolidMenuList[make_pair(screen, nowStatus)];
	int length = nowMenu.first.first, width = nowMenu.first.second;

	//移到原本的選項改顏色
	UI::Instance->SetTextColor(Setting::Color::white, Setting::Color::black);
	for (int x = nowMenu.second[SelectedIndex].first, y = nowMenu.second[SelectedIndex].second, i = 0; i < width; i++) {
		UI::Instance->DrawHorizontalLine(make_pair(x, y + i), length, L' ');
	}

	//選項前進
	int tmp = SelectedIndex + direction;
	if (tmp < 0) {
		tmp = (int)(nowMenu.second.size() - 1);
	}
	else if (tmp >= nowMenu.second.size()) {
		tmp %= nowMenu.second.size();
	}

	UI::Instance->SetTextColor(Setting::Color::black, Setting::Color::white, false, true);
	for (int x = nowMenu.second[tmp].first, y = nowMenu.second[tmp].second, i = 0; i < width; i++) {
		UI::Instance->DrawHorizontalLine(make_pair(x, y + i), length, L' ');
	}

	MoveMenuOption(input);
}


void GameSystem::AIChessMove()
{
	auto step = AI::getInstance()->getBest();

	ChessSelect(make_pair(step.second.first.second, step.second.first.first));

	int result = ChessMove(make_pair(step.second.second.second, step.second.second.first));
	if (result != 2) {
		UI::Instance->DrawBoard();
		nowStatus = Status::SelectChess;
		//將現在選哪顆棋的顯示關閉
		UI::Instance->showSelectedChess(0);
		UI::Instance->gotoBoardXY(BoardCursor);
		UI::Instance->showGeneral(false);
		/*bool result = ChessBoard::Instance->ifCheckmate((player + 1) % 2);
		//下一手可能會將軍
		if (result) {
			UI::Instance->showGeneral(true, (player + 1) % 2);
			//播放將軍音效
			playMusic(musicMode, Music::Sound::General);
		}*/
	}
	while (_kbhit()) {
		_getch();
	}
}

//換到下個玩家
void GameSystem::NextPlayer()
{
	player = (player + 1) % 2;
	bool result = ChessBoard::Instance->ifCheckmate(player);
	/*//下一手可能會將軍
	if (result) {
		UI::Instance->showGeneral(true, player);
		//播放將軍音效
		playMusic(musicMode, Music::Sound::General);
	}*/

	//若為單人遊戲且輪到電腦
	if (GameMode == 1 && player == 0) {

		UI::Instance->showPlayer(player);
		UI::Instance->showAdditionText(L"Brandon思考中...");

		AIChessMove();
		//電腦勝利
		if (nowStatus == Status::Win) {
			return;
		}
		player = 1;
	}

	UI::Instance->showPlayer(player);
	UI::Instance->gotoBoardXY(BoardCursor);
}


// 從任何會中斷遊戲的狀態回歸遊戲
void GameSystem::Resume()
{
	//重畫棋盤
	UI::Instance->DrawBoard();

	//代表現在為移動棋子模式
	if (SelectedChess.first != 0) {
		nowStatus = Status::MoveChess;
		ChessSelect(SelectedChess.second);
	}
	//代表現在為選擇棋子模式
	else {
		nowStatus = Status::SelectChess;
	}
	//游標回到原本的位置
	UI::Instance->gotoBoardXY(BoardCursor);
}

//byHans
void GameSystem::getTXT()
{
	TXTFiles.clear();
	system("dir .\\SaveData\\*.txt /b > temp.rec");
	fstream fs;
	fs.open("temp.rec", ios::in);
	string input;
	while (fs >> input) {
		input.erase(input.end() - 4, input.end());
		TXTFiles.push_back(input);
	}
	sort(TXTFiles.begin(), TXTFiles.end());
}
//byHans
void GameSystem::turnSaveDataPage(int directon, bool musicplay)
{
	nowDataPage += directon;
	if (nowDataPage <= 0) {
		nowDataPage = 1;
		cout << '\a';
		return;
	}
	else if (nowDataPage > (TXTFiles.size() + 2) / 3) {
		nowDataPage--;
		cout << '\a';
		return;
	}
	UI::Instance->clearData();
	UI::Instance->showSaveData(TXTFiles, nowDataPage);
	SelectedIndex = 0;
	if (musicplay) {
		playMusic(musicMode, Music::MoveCursor);
	}
}

//byHans
void GameSystem::MoveSolidDataOption(Key input, int num, bool musicplay)
{
	int direction;
	switch (input) {
	case UP:
		direction = -1;
		break;

	case DOWN:
		direction = 1;
		break;

	default:
		return;
	}

	auto nowData = SolidDataList[num - 1];
	int length = nowData.first.first, width = nowData.first.second;

	//移到原本的選項改顏色
	UI::Instance->SetTextColor(Setting::Color::white, Setting::Color::black);
	UI::Instance->DrawHorizontalLine(make_pair(nowData.second[SelectedIndex].first, nowData.second[SelectedIndex].second), length, L' ');
	UI::Instance->gotoXY(nowData.second[SelectedIndex].first, nowData.second[SelectedIndex].second);
	cout << TXTFiles[(nowDataPage - 1) * 3 + SelectedIndex];

	//選項前進
	SelectedIndex = SelectedIndex + direction;
	if (SelectedIndex < 0) {
		SelectedIndex = (int)(nowData.second.size() - 1);
	}
	else if (SelectedIndex >= nowData.second.size()) {
		SelectedIndex %= nowData.second.size();
	}

	UI::Instance->SetTextColor(Setting::Color::black, Setting::Color::white, false, true);
	UI::Instance->DrawHorizontalLine(make_pair(nowData.second[SelectedIndex].first, nowData.second[SelectedIndex].second), length, L' ');
	UI::Instance->gotoXY(nowData.second[SelectedIndex].first, nowData.second[SelectedIndex].second);
	cout << TXTFiles[(nowDataPage - 1) * 3 + SelectedIndex];
	UI::Instance->gotoXY(nowData.second[SelectedIndex].first, nowData.second[SelectedIndex].second);
	if (musicplay) {
		playMusic(musicMode, Music::MoveCursor);
	}
}

//byHans
void GameSystem::NewMake()
{
	//狀態設為選取旗子
	nowStatus = Status::SelectChess;
	SelectedIndex = 0;
	SelectedChess.first = 0;

	//重繪畫面
	UI::Instance->showScreen(Screen::Making);

	//重新設置棋盤游標
	BoardCursor = make_pair(0, 0);
	UI::Instance->gotoXY(67, 6);
}

//byHans
void GameSystem::MoveMakeCursor(Key input)
{
	auto nowMenu = MenuList[make_pair(screen, nowStatus)];

	//移到原本的選項改顏色
	if (SelectedIndex < 8)
		UI::Instance->SetTextColor(Setting::Color::black, Setting::Color::gray);
	else
		UI::Instance->SetTextColor(Setting::Color::red, Setting::Color::gray);
	UI::Instance->gotoXY(nowMenu[SelectedIndex].second);
	wcout << nowMenu[SelectedIndex].first;

	//移到下個選項
	switch (input) {
	case UP:
		if (SelectedIndex > 1 && SelectedIndex <= 7)
			SelectedIndex += 7;
		else if (SelectedIndex >= 8 && SelectedIndex <= 14)
			SelectedIndex -= 7;
		else if (SelectedIndex == 1)
			SelectedIndex = 0;
		else
			SelectedIndex = 8;
		break;

	case LEFT:
		if (SelectedIndex)
			SelectedIndex -= 1;
		else
			SelectedIndex = 14;
		break;

	case DOWN:
		if (SelectedIndex >= 1 && SelectedIndex <= 7)
			SelectedIndex += 7;
		else if (SelectedIndex > 8 && SelectedIndex <= 14)
			SelectedIndex -= 7;
		else if (SelectedIndex == 8)
			SelectedIndex = 0;
		else
			SelectedIndex = 1;
		break;

	case RIGHT:
		if (SelectedIndex == 14)
			SelectedIndex = 0;
		else
			SelectedIndex += 1;
		break;

	default:
		return;
	}

	//輸出下個選項移動游標
	if (SelectedIndex < 8)
		UI::Instance->SetTextColor(Setting::Color::black, Setting::Color::white, 0, 1);
	else
		UI::Instance->SetTextColor(Setting::Color::red, Setting::Color::white, 1, 1);
	UI::Instance->gotoXY(nowMenu[SelectedIndex].second);
	wcout << nowMenu[SelectedIndex].first;

	//游標回到前方(輸出完上方字會位移到)
	UI::Instance->gotoXY(nowMenu[SelectedIndex].second);
}

bool GameSystem::checkMake()
{
	if (SelectedChess.first == 1 || SelectedChess.first == 2) {
		if (BoardCursor.second < 3 && BoardCursor.first>2 && BoardCursor.first < 6)return 1;
		else return 0;
	}
	else if (SelectedChess.first == 3) {
		if (BoardCursor.second < 5)return 1;
		else return 0;
	}
	else if (SelectedChess.first == 8 || SelectedChess.first == 9) {
		if (BoardCursor.second > 6 && BoardCursor.first > 2 && BoardCursor.first < 6)return 1;
		else return 0;
	}
	else if (SelectedChess.first == 10) {
		if (BoardCursor.second > 4)return 1;
		else return 0;
	}
	else return 1;
}
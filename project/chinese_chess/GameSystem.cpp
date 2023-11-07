#include "GameSystem.h"
//�B�z�۩w�q�ɥ�������D
GameSystem* GameSystem::instance;

namespace {

	map<pair<Screen, Status>, vector<pair<wstring, Coordinate>> > MenuList = {
		{make_pair(Screen::Playing,Status::pause) ,{ make_pair(L"�~��C��",make_pair(50, 7)),make_pair(L"���s�}�l",make_pair(50, 9)),make_pair(L"�^�D���",make_pair(50, 11)),make_pair(L"�x�s�C��",make_pair(50, 13)),make_pair(L"���}�C��",make_pair(50, 15))}}
		,{make_pair(Screen::Playing,Status::regret) ,{ make_pair(L"�O",make_pair(48, 13)),make_pair(L"�_",make_pair(56, 13)) }}
		,{make_pair(Screen::Playing,Status::pause_restart) ,{ make_pair(L"�O",make_pair(49, 13)),make_pair(L"�_",make_pair(57, 13)) }}
		,{make_pair(Screen::MainMenu,Status::Beginning) ,{ make_pair(L"�}�l�C��",make_pair(47, 13)),make_pair(L"�ﶵ",make_pair(49, 17)),make_pair(L"���}�C��",make_pair(47, 21))}}
		,{make_pair(Screen::MainMenu,Status::DuoPlayerMenu) ,{ make_pair(L"�}�l�s�C��",make_pair(46, 14)),make_pair(L"Ū���¬���",make_pair(46, 20))}}
		,{make_pair(Screen::MainMenu,Status::SelectPlayer) ,{ make_pair(L"�������",make_pair(47, 14)),make_pair(L"�¤����",make_pair(47, 20))}}
		,{make_pair(Screen::MainMenu,Status::SinglePlayerMenu) ,{ make_pair(L"�}�l�s�C��",make_pair(46, 14)),make_pair(L"Ū���¬���",make_pair(46, 20))}}
		,{make_pair(Screen::MainMenu,Status::SelectSinglePlayer) ,{ make_pair(L"���a����",make_pair(47, 14)),make_pair(L"�q������",make_pair(47, 20))}}
		,{make_pair(Screen::MainMenu,Status::SelectMode) ,{ make_pair(L"��H�C��",make_pair(47, 14)),make_pair(L"���H�C��",make_pair(47, 20))}}
		,{make_pair(Screen::MainMenu,Status::Option) ,{ make_pair(L"�t�έ���",make_pair(47, 14)),make_pair(L"�۩w�q�ѽL",make_pair(46, 20))}}
		,{make_pair(Screen::MainMenu,Status::Sound) ,{ make_pair(L"�R���Ҧ�",make_pair(47, 13)),make_pair(L"�@�뭵��",make_pair(47, 17)),make_pair(L"�S����",make_pair(47, 21))}}
		,{make_pair(Screen::Making,Status::SelectChess) ,{ make_pair(L"�@",make_pair(67, 5)),make_pair(L"�N",make_pair(67, 7)),make_pair(L"�h",make_pair(71, 7)),make_pair(L"�H",make_pair(75, 7)),make_pair(L"��",make_pair(79, 7)),make_pair(L"��",make_pair(83, 7)),make_pair(L"�]",make_pair(87, 7)),make_pair(L"��",make_pair(91, 7)),
															make_pair(L"��",make_pair(67, 9)),make_pair(L"�K",make_pair(71, 9)),make_pair(L"��",make_pair(75, 9)),make_pair(L"��",make_pair(79, 9)),make_pair(L"�X",make_pair(83, 9)),make_pair(L"��",make_pair(87, 9)),make_pair(L"�L",make_pair(91, 9))}}
		,{make_pair(Screen::Making,Status::pause) ,{ make_pair(L"�~��w�q",make_pair(50, 7)),make_pair(L"���s�}�l",make_pair(50, 9)),make_pair(L"�^�D���",make_pair(50, 11)),make_pair(L"�x�s�ѽL",make_pair(50, 13)),make_pair(L"���}�C��",make_pair(50, 15))}}
		,{make_pair(Screen::Making,Status::pause_restart) ,{ make_pair(L"�O",make_pair(49, 13)),make_pair(L"�_",make_pair(57, 13)) }}
		,{make_pair(Screen::Making,Status::SelectPlayer) ,{ make_pair(L"��",make_pair(49, 13)),make_pair(L"��",make_pair(57, 13)) }}

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

//�غc���G
GameSystem::GameSystem() : screen(Screen::MainMenu), BoardCursor({ 0, 9 }), SelectedChess({ 0,{0,0} }), LogPage(1), nowLogPage(1), SelectedIndex(0)
{
	screen = Screen::MainMenu;
	nowStatus = Status::Beginning;
	musicMode = Music::MusicMode::normal;
}

//�Ѻc���G�L�@��
GameSystem::~GameSystem()
{

}

//�]�m��e���a
void GameSystem::setPlayer(int player)
{
	if (player != 0 && player != 1) {
		cout << "GameSystem::setPlayer�G���~" << player;
	}
	else {
		this->player = player;
	}
}

//�]�m��e�e��
void GameSystem::setMode(Screen screen)
{
	this->screen = screen;
}

// ���ʴѽL�W�����(�ǤJ�W�U���k)
void GameSystem::MoveBoardCursor(Key direction)
{
	static map<Key, Coordinate> Table{
		{Key::UP,{0,-1}},
		{Key::DOWN,{0,1}},
		{Key::LEFT,{-1,0}},
		{Key::RIGHT,{1,0}},
	};
	auto item = Table[direction];
	//�S���W�X�d��
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

//�����ϥΪ̫����J�A�îھڥثe�Ҧb�e���P�Ҧ��A�i��۹������ʧ@
void GameSystem::keyInput()
{
	static char tmp;
	static Key input;
	tmp = _getch();
	bool flag = false;

	if (tmp == -32) {
		flag = true;
		//�Ytmp==-32�A�N��ϥΪ̿�J�W�U���k
		tmp = _getch();
	}


	//�N��J�ରEnum(�C�|)
	switch (tmp) {
	case 72://��V��W
		input = Key::UP;
		break;
	case 75: //��V�䥪
		input = Key::LEFT;
		break;
	case 80: //��V��U
		input = Key::DOWN;
		break;
	case 77: //��V��k
		input = Key::RIGHT;
		break;
	case 27: //Esc��
		input = Key::ESC;
		break;
	case 13: //enter��
		input = Key::ENTER;
		break;
	case 104: //h��
	//case 90: //H��
		input = Key::H;
		break;
	case 122: //z��
	case 90: //Z��
		input = Key::Z;
		break;
	case 46: //>��
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

	//Ū������
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

				//���ʹ�߿ﶵ
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
					//�ɮ׮榡���~
					if (statusCode == 1) {
						ChessBoard::Instance->init();
					}
					//�}�Ҳ��`
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
	//�Y���A���ɮ�Ū�����~(�Ы��U���N���~��...)
	else if (nowStatus == Status::Read_Error) {
		nowStatus = Status::DuoPlayerMenu;
		UI::Instance->showBlock(screen, Setting::Block::DuoPlayerMenu);
		return;
	}
	//�Y���A���ӧQ(�Ы��U���N���~��...)
	else if (nowStatus == Status::Win) {
		ChessBoard::Instance->init();
		NewGame(1);
		return;
	}
	else if (nowStatus == Status::Cannot_regret) {
		UI::Instance->DrawBoard();
		//�N��{�b�b���ʴѤl�Ҧ�
		if (SelectedChess.first != 0) {
			nowStatus = Status::MoveChess;
			ChessSelect(SelectedChess.second);
		}
		//�N��{�b�b��ܴѤl�Ҧ�
		else {
			nowStatus = Status::SelectChess;
		}
		//��Ц^��쥻����m
		UI::Instance->gotoBoardXY(BoardCursor);
		return;
	}
	//��J�x�s�W��
	else if (nowStatus == Status::Store) {
		//�����x�s
		if (input == Key::ESC) {
			if (screen == Screen::Playing) {
				//���e�ѽL
				UI::Instance->DrawBoard();
				//�N��{�b�b���ʴѤl�Ҧ�
				if (SelectedChess.first != 0) {
					nowStatus = Status::MoveChess;
					ChessSelect(SelectedChess.second);
				}
				//�N��{�b�b��ܴѤl�Ҧ�
				else {
					nowStatus = Status::SelectChess;
				}
				//��Ц^��쥻����m
				UI::Instance->gotoBoardXY(BoardCursor);
				return;
			}
			else if (screen == Screen::Making) {
				UI::Instance->DrawBoard();
				nowStatus = Status::SelectPlayer;
				UI::Instance->showBlock(Screen::Making, Setting::Block::SelectPlayer);
				SelectedIndex = 0;
				//����в����
				UI::Instance->gotoXY(MenuList[make_pair(screen, nowStatus)][0].second);
				return;
			}
		}
		//Enter��A�ˬd�O�_����J����@�Ӧr��
		else if (input == Key::ENTER && FileName.size() != 0) //enter
		{
			//�x�s�C�����\
			if (StoreGame()) {
				//���e�ѽL
				UI::Instance->DrawBoard();
				if (screen == Screen::Playing) {
					//�N��{�b�b���ʴѤl�Ҧ�
					if (SelectedChess.first != 0) {
						nowStatus = Status::MoveChess;
						ChessSelect(SelectedChess.second);
					}
					//�N��{�b�b��ܴѤl�Ҧ�
					else {
						nowStatus = Status::SelectChess;
					}
					//��Ц^��쥻����m
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
		//BackSpace��
		else if (tmp == 8 && !FileName.empty()) {
			UI::Instance->gotoXY(33 + 2 * (int)(FileName.size()), 13);
			cout << " ";
			UI::Instance->gotoXY(33 + 2 * FileName.size(), 13);
			FileName.pop_back();
		}
		//�Y���X�k��J
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
	// �Y��J����L�īh�����禡
	if (input == Key::invalid) return;

	//�Y�e����� (�@�}�l)�D���
	if (screen == Screen::MainMenu) {
		if (nowStatus == Status::Beginning) {
			switch (input) {
				//���ʹ�߿ﶵ
			case Key::LEFT:
			case Key::UP:
			case Key::RIGHT:
			case Key::DOWN:
				MoveSolidMenuOption(input);
				break;

			case Key::ENTER:
				//�}�l�C��
				if (SelectedIndex == 0) {
					nowStatus = Status::SelectMode;
					SelectedIndex = 0;
					UI::Instance->showBlock(screen, Setting::Block::SelectMode);
				}
				//�t�οﶵ
				else if (SelectedIndex == 1) {
					nowStatus = Status::Option;
					SelectedIndex = 0;
					UI::Instance->showBlock(screen, Setting::Block::Option);
				}
				//���}�C��
				else if (SelectedIndex == 2) {
					UI::Instance->CleanScreen();
					exit(1);
				}
				break;
			}
		}
		//��ܹC���Ҧ�(��H/���H)
		else if (nowStatus == Status::SelectMode) {
			switch (input) {
				//���ʹ�߿ﶵ
			case Key::LEFT:
			case Key::UP:
			case Key::RIGHT:
			case Key::DOWN:
				MoveSolidMenuOption(input);
				break;

			case Key::ENTER:
				//��H�C��
				if (SelectedIndex == 0) {
					nowStatus = Status::SinglePlayerMenu;
					SelectedIndex = 0;
					GameMode = 1; //��H�Ҧ�
					UI::Instance->showBlock(screen, Setting::Block::SinglePlayerMenu);
				}
				//���H�C��
				else if (SelectedIndex == 1) {
					nowStatus = Status::DuoPlayerMenu;
					SelectedIndex = 0;
					GameMode = 2; //���H�Ҧ�
					UI::Instance->showBlock(screen, Setting::Block::DuoPlayerMenu);
				}
				//��^�W�@��
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
		//��H�C���M��(����/���)
		else if (nowStatus == Status::SinglePlayerMenu) {
			switch (input) {
				//���ʹ�߿ﶵ
			case Key::LEFT:
			case Key::UP:
			case Key::RIGHT:
			case Key::DOWN:
				MoveSolidMenuOption(input);
				break;

			case Key::ENTER:
				//�}�l�s�C��
				if (SelectedIndex == 0) {
					nowStatus = Status::SelectSinglePlayer;
					SelectedIndex = 0;
					UI::Instance->showBlock(screen, Setting::Block::SelectSinglePlayer);
				}
				//Ū���¬���
				else if (SelectedIndex == 1) {
					nowStatus = Status::Read;
					SelectedIndex = 0;
					nowDataPage = 1;
					FileName = "";
					getTXT();
					UI::Instance->showBlock(screen, Setting::Block::Read);
					UI::Instance->showSaveData(TXTFiles, nowDataPage);
				}
				//��^�W�@��
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
		//��H�C�����
		else if (nowStatus == Status::SelectSinglePlayer) {
			switch (input) {
				//���ʹ�߿ﶵ
			case Key::LEFT:
			case Key::UP:
			case Key::RIGHT:
			case Key::DOWN:
				MoveSolidMenuOption(input);
				break;

			case Key::ENTER:
				//���a����
				if (SelectedIndex == 0) {
					ChessBoard::Instance->init();
					screen = Screen::Playing;
					NewGame(1);
				}
				//�q������
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
		//���H�C�����(�}�l�s�C�� or Ū������)
		else if (nowStatus == Status::DuoPlayerMenu) {
			switch (input) {
				//���ʹ�߿ﶵ
			case Key::LEFT:
			case Key::UP:
			case Key::RIGHT:
			case Key::DOWN:
				MoveSolidMenuOption(input);
				break;

			case Key::ENTER:
				//�}�l�s�C��
				if (SelectedIndex == 0) {
					nowStatus = Status::SelectPlayer;
					SelectedIndex = 0;
					UI::Instance->showBlock(screen, Setting::Block::SelectPlayer);
				}
				//Ū���¬���
				else if (SelectedIndex == 1) {
					nowStatus = Status::Read;
					SelectedIndex = 0;
					nowDataPage = 1;
					FileName = "";
					getTXT();
					UI::Instance->showBlock(screen, Setting::Block::Read);
					UI::Instance->showSaveData(TXTFiles, nowDataPage);
				}
				//��^�W�@��
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
		//���H�C��->��ܭ������
		else if (nowStatus == Status::SelectPlayer) {
			switch (input) {
				//���ʹ�߿ﶵ
			case Key::LEFT:
			case Key::UP:
			case Key::RIGHT:
			case Key::DOWN:
				MoveSolidMenuOption(input);
				break;

			case Key::ENTER:
				ChessBoard::Instance->init();
				screen = Screen::Playing;
				//�������
				if (SelectedIndex == 0) {
					NewGame(1);
				}
				//�¤����
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
		//�t�οﶵ
		else if (nowStatus == Status::Option) {
			switch (input) {
				//���ʹ�߿ﶵ
			case Key::LEFT:
			case Key::UP:
			case Key::RIGHT:
			case Key::DOWN:
				MoveSolidMenuOption(input);
				break;

			case Key::ENTER:
				//�t�έ���
				if (SelectedIndex == 0) {
					nowStatus = Status::Sound;
					SelectedIndex = 0;
					UI::Instance->showBlock(screen, Setting::Block::Sound);
				}
				//�۩w�q�ѽL
				else if (SelectedIndex == 1) {
					ChessBoard::Instance->clear();
					screen = Screen::Making;
					nowStatus = Status::SelectChess;
					NewMake();
					break;
				}
				//��^�W�@��
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
		//���ĳ]�w
		else if (nowStatus == Status::Sound) {
			switch (input) {
				//���ʹ�߿ﶵ
			case Key::LEFT:
			case Key::UP:
			case Key::RIGHT:
			case Key::DOWN:
				MoveSolidMenuOption(input);
				break;

			case Key::ENTER:
				//�L����
				if (SelectedIndex == 0) {
					musicMode = Music::quiet;
				}
				//�@�뭵��
				else if (SelectedIndex == 1) {
					musicMode = Music::normal;
					playMusic(musicMode, Music::Chess);
				}
				//�S����
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
	//�Y�e����� ���H���
	else if (screen == Screen::Playing) {
		//��ѼҦ�
		if (nowStatus == Status::SelectChess) {
			switch (input) {
				//���ʴ�Ц�m
			case Key::LEFT:
			case Key::RIGHT:
			case Key::DOWN:
			case Key::UP:
				//�I�s���ʴѽL�y��
				MoveBoardCursor(input);
				break;

			case Key::ENTER:
				//��Ѧ��\
				if (ChessSelect(BoardCursor)) {
					nowStatus = Status::MoveChess;
					UI::Instance->showSelectedChess(SelectedChess.first);

					playMusic(musicMode, Music::Sound::Select);
					//��Ц^��쥻����m
					UI::Instance->gotoBoardXY(BoardCursor);
				}
				else {
					cout << '\a';
				}
				break;

				//�Ȱ��C��
			case Key::ESC:
				nowStatus = Status::pause;
				UI::Instance->showBlock(screen, Setting::Block::Pause);
				SelectedIndex = 0;
				//��в��ʨ��~��C�����a��
				UI::Instance->gotoXY(MenuList[make_pair(screen, nowStatus)][0].second);
				playMusic(musicMode, Music::Sound::Select);
				break;
				//�x�s�C��
			case Key::Save:
				nowStatus = Status::Store;
				UI::Instance->showBlock(screen, Setting::Block::Store);
				//�N�x�s�Ϊ��r��M��
				FileName.clear();
				//����Ц^��Ĥ@�Ӧr����m
				UI::Instance->gotoXY(35, 13);
				break;
				//�I�s���U
			case Key::H:
				nowStatus = Status::help;
				UI::Instance->showBlock(screen, Setting::Block::Help);
				playMusic(musicMode, Music::Select);
				UI::Instance->gotoXY(0, 0);
				break;
				//����
			case Key::Z:
				nowStatus = Status::regret;
				UI::Instance->showBlock(screen, Setting::Block::Regret);
				SelectedIndex = 0;
				//��в��ʨ�u�O�v
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
		//���ʴѤl�Ҧ�
		else if (nowStatus == Status::MoveChess) {
			switch (input) {
				//���ʴ�Ц�m
			case Key::LEFT:
			case Key::RIGHT:
			case Key::DOWN:
			case Key::UP:
				//�I�s���ʴѽL�y��
				MoveBoardCursor(input);
				break;

			case Key::ENTER:
				//�������
				if (BoardCursor.first == SelectedChess.second.first && BoardCursor.second == SelectedChess.second.second) {
					SelectedChess.first = 0;
					nowStatus = Status::SelectChess;
					UI::Instance->showSelectedChess(0); //�N�{�b������Ѫ��������
					//������
					UI::Instance->DrawBoard(); //�����i
					//�N��в��^
					UI::Instance->gotoBoardXY(BoardCursor);
				}
				else {
					int result = ChessMove(BoardCursor);
					//�C���ӧQ
					if (result == 2) {
						//���_�禡
						return;
					}
					//���T����
					else if (result == 1) {
						nowStatus = Status::SelectChess;
						UI::Instance->DrawBoard();
						//�N�{�b������Ѫ��������
						UI::Instance->showSelectedChess(0);
						//�N��в��ʦ^��
						UI::Instance->gotoBoardXY(BoardCursor);
						NextPlayer();
					}
					//���ʥ���
					else if (result == 0) {
						cout << '\a';
					}

				}
				break;
			case Key::Save:
				nowStatus = Status::Store;
				UI::Instance->showBlock(screen, Setting::Block::Store);
				//�N�x�s�Ϊ��r��M��
				FileName.clear();
				//����Ц^��Ĥ@�Ӧr����m
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

				SelectedIndex = 0; //�ﶵ�]��0
				UI::Instance->gotoXY(MenuList[make_pair(screen, nowStatus)][0].second);
				playMusic(musicMode, Music::Sound::Select);
				break;

			case Key::ESC:
				nowStatus = Status::pause;
				//��ܼȰ��϶�
				UI::Instance->showBlock(screen, Setting::Block::Pause);

				SelectedIndex = 0; //�ﶵ�]��0
				//�N��в����~��C��
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
		//���ѼҦ�
		else if (nowStatus == Status::regret) {
			switch (input) {
				//���ʿﶵ
			case Key::LEFT:
			case Key::UP:
			case Key::RIGHT:
			case Key::DOWN:
				MoveMenuOption(input);
				break;

			case Key::ENTER:

				//�O
				if (SelectedIndex == 0) {
					if (Regret()) {
						nowStatus = Status::SelectChess;
						//�קK�{�b�b���ʴѤl�Ҧ��ӳy�����~
						SelectedChess.first = 0;
						//��Ц^��쥻����m
						UI::Instance->gotoBoardXY(BoardCursor);
					}
					//�L�k����
					else {
						//���񭵮�
						playMusic(musicMode, Music::CannotRegret);
						//�N"�A�S������n�ᮬ"�s�X��
						UI::Instance->showBlock(Screen::Playing, Setting::Block::CannotRegret);
						nowStatus = Status::Cannot_regret;
					}
				}
				//�_
				else if (SelectedIndex == 1) {
					//�������A���i�A���o��
					UI::Instance->DrawBoard();
					//�N��{�b�b���ʴѤl�Ҧ�
					if (SelectedChess.first != 0) {
						nowStatus = Status::MoveChess;
						ChessSelect(SelectedChess.second);
					}
					//�N��{�b�b��ܴѤl�Ҧ�
					else {
						nowStatus = Status::SelectChess;
					}
					//��Ц^��쥻����m
					UI::Instance->gotoBoardXY(BoardCursor);
				}

				break;

			case Key::Z:
			case Key::ESC:

				UI::Instance->DrawBoard();
				//�N��{�b�b���ʴѤl�Ҧ�
				if (SelectedChess.first != 0) {
					nowStatus = Status::MoveChess;
					ChessSelect(SelectedChess.second);
				}
				//�N��{�b�b��ܴѤl�Ҧ�
				else {
					nowStatus = Status::SelectChess;
				}
				//��Ц^��쥻����m
				UI::Instance->gotoBoardXY(BoardCursor);
				//�������Ѥl������
				playMusic(musicMode, Music::Sound::Select);
				break;
			}
		}
		//�Ȱ�(���)
		else if (nowStatus == Status::pause) {
			switch (input) {
				//���ʿﶵ
			case Key::LEFT:
			case Key::UP:
			case Key::RIGHT:
			case Key::DOWN:
				MoveMenuOption(input);
				break;

			case Key::ENTER:
				//����~��C��
				if (SelectedIndex == 0) {
					Resume();
				}
				//������s�}�l
				else if (SelectedIndex == 1) {
					nowStatus = Status::pause_restart;
					UI::Instance->showBlock(Screen::Playing, Setting::Block::Restart);
					SelectedIndex = 0;
					//��в���O
					UI::Instance->gotoXY(MenuList[make_pair(screen, nowStatus)][0].second);

				}
				//�^�D���
				else if (SelectedIndex == 2) {
					screen = Screen::MainMenu;
					nowStatus = Status::Beginning;
					SelectedIndex = 0;
					UI::Instance->showScreen(screen);
					UI::Instance->gotoXY(47, 13);
				}
				//�x�s�C��
				else if (SelectedIndex == 3) {
					nowStatus = Status::Store;
					UI::Instance->showBlock(screen, Setting::Block::Store);
					//�N�x�s�Ϊ��r��M��
					FileName.clear();
					//����Ц^��Ĥ@�Ӧr����m
					UI::Instance->gotoXY(35, 13);
				}
				//���}�C��
				else if (SelectedIndex == 4) {
					UI::Instance->CleanScreen();
					UI::Instance->gotoXY(0, 0);
					exit(1);
				}
				break;

			case Key::ESC:
				Resume();
				//���񭵮�
				playMusic(musicMode, Music::Sound::Select);
				break;
			}
		}
		//���U
		else if (nowStatus == Status::help) {
			switch (input) {
			case Key::ESC:
			case Key::H:
				Resume();
				break;
			}

		}
		//�T�w���s�}�l?
		else if (nowStatus == Status::pause_restart) {
			switch (input) {
				//���ʿﶵ
			case Key::LEFT:
			case Key::UP:
			case Key::RIGHT:
			case Key::DOWN:
				MoveMenuOption(input);
				break;

			case Key::ESC:
				nowStatus = Status::pause;
				//��ܼȰ��϶�
				UI::Instance->showBlock(Screen::Playing, Setting::Block::Pause);

				//��Ц^�쭫�s�}�l
				SelectedIndex = 0;
				MoveMenuOption(Key::DOWN, false);
				break;
			case Key::ENTER:
				//����O
				if (SelectedIndex == 0) {
					//�ѽL�i���l��
					auto history = ChessBoard::Instance->CheckHistory();
					if (history.first) {
						ChessBoard::Instance->load(history.second.first, history.second.second);
						NewGame(history.second.first);//���s�s�C��
					}
					else {
						ChessBoard::Instance->init();
						NewGame(1);//���s�s�C��
					}

				}
				//����_
				else if (SelectedIndex == 1) {
					nowStatus = Status::pause;
					//��ܼȰ��϶�
					UI::Instance->showBlock(Screen::Playing, Setting::Block::Pause);

					//��Ц^�쭫�s�}�l
					SelectedIndex = 0;
					MoveMenuOption(Key::DOWN, false);
				}
				break;
			}
		}
	}
	else if (screen == Screen::Making) {
		//��n�񪺴Ѥl
		if (nowStatus == Status::SelectChess) {
			switch (input) {
				//���ʹ�߿ﶵ
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
				//��в��ʨ��~��C�����a��
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
				//����в����
				UI::Instance->gotoXY(MenuList[make_pair(screen, nowStatus)][0].second);
				break;
			}
		}
		else if (nowStatus == Status::MoveChess) {
			switch (input) {
				//���ʴ�Ц�m
			case Key::LEFT:
			case Key::RIGHT:
			case Key::DOWN:
			case Key::UP:
				//�I�s���ʴѽL�y��
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
					//�N��в��ʦ^��
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
				//����в����
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
				//���ʿﶵ
			case Key::LEFT:
			case Key::UP:
			case Key::RIGHT:
			case Key::DOWN:
				MoveMenuOption(input);
				break;

			case Key::ENTER:
				//����~��C��
				if (SelectedIndex == 0) {
					UI::Instance->DrawBoard();
					UI::Instance->gotoXY(MenuList[make_pair(Screen::Making, Status::SelectChess)][SelectedChess.first].second);
					SelectedIndex = SelectedChess.first;
					nowStatus = SelectChess;
				}
				//������s�}�l
				else if (SelectedIndex == 1) {
					nowStatus = Status::pause_restart;
					UI::Instance->showBlock(Screen::Playing, Setting::Block::Restart);
					SelectedIndex = 0;
					//��в���O
					UI::Instance->gotoXY(MenuList[make_pair(screen, nowStatus)][0].second);

				}
				//�^�D���
				else if (SelectedIndex == 2) {
					screen = Screen::MainMenu;
					nowStatus = Status::Beginning;
					SelectedIndex = 0;
					UI::Instance->showScreen(screen);
					UI::Instance->gotoXY(47, 13);
				}
				//�x�s�C�� ��ܥ����C��
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
					//����в����
					UI::Instance->gotoXY(MenuList[make_pair(screen, nowStatus)][0].second);
				}
				//���}�C��
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
				//���ʿﶵ
			case Key::LEFT:
			case Key::UP:
			case Key::RIGHT:
			case Key::DOWN:
				MoveMenuOption(input);
				break;

			case Key::ESC:
				nowStatus = Status::pause;
				//��ܼȰ��϶�
				UI::Instance->showBlock(Screen::Making, Setting::Block::Pause);

				//��Ц^�쭫�s�}�l
				SelectedIndex = 0;
				MoveMenuOption(Key::DOWN, false);
				break;
			case Key::ENTER:
				//����O
				if (SelectedIndex == 0) {
					//�ѽL�i���l��
					ChessBoard::Instance->clear();
					NewMake();//���s�w�q
				}
				//����_
				else if (SelectedIndex == 1) {
					nowStatus = Status::pause;
					//��ܼȰ��϶�
					UI::Instance->showBlock(Screen::Making, Setting::Block::Pause);

					//��Ц^�쭫�s�}�l
					SelectedIndex = 0;
					MoveMenuOption(Key::DOWN, false);
				}
				break;
			}
		}
		else if (nowStatus == Status::SelectPlayer) {
			switch (input) {
				//���ʿﶵ
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
					//��ܼȰ��϶�
					UI::Instance->showBlock(Screen::Making, Setting::Block::Pause);

					//��Ц^�쭫�s�}�l
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
				//�N�x�s�Ϊ��r��M��
				FileName.clear();
				//����Ц^��Ĥ@�Ӧr����m
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


//����Ѥl
//�ǤJ�@�ӴѽL�y��(9*10)
bool GameSystem::ChessSelect(Coordinate co)
{
	static const wchar_t list[] = L"�@�N�h�H�����]��ӥK�ۨ��X���L";
	int chess = ChessBoard::Instance->check(make_pair(co.second, co.first));
	if (chess == 0) {
		return false;
	}
	//����誺�Ѥl
	else if ((player == 0 && chess > 7) || (player == 1 && chess <= 7)) {
		return false;
	}
	auto available = ChessBoard::Instance->filter(make_pair(co.second, co.first));
	if (available->size() == 0) {
		return false;
	}

	AvailableMove.clear();
	SelectedChess.first = chess;
	SelectedChess.second = co; //�諸�����Ѫ��y��

	for (auto item : *available) {
		UI::Instance->gotoBoardXY(make_pair(item.second.second, item.second.first));
		//�Ů�l�G�N�I���]���ǩ�
		if (item.first == 0) {
			UI::Instance->SetTextColor(Setting::Color::gray, Setting::Color::white);
			cout << "�@";
		}
		//���Ĥ�Ѥl
		else {
			UI::Instance->SetTextColor(Setting::Color::black, Setting::Color::purple, false, true);
			wcout << list[item.first];
		}
		//�N�y���ରUI�ѽL(->X,�V�U��y)���榡
		AvailableMove.push_back(make_pair(item.first, make_pair(item.second.second, item.second.first)));
	}
	delete available;
	return true;
}

//���m�C��
//�ǤJ�Ѽ�player�A�M�w�Ĥ@���Ѥl�֤U
void GameSystem::NewGame(int player)
{
	//���A�]������X�l
	nowStatus = Status::SelectChess;
	SelectedIndex = 0;
	SelectedChess.first = 0;
	AvailableMove.clear();

	//��ø�e��
	UI::Instance->showScreen(Screen::Playing);

	//�]�m�{�b���a
	this->player = player;
	UI::Instance->showPlayer(player);

	FileName = "";
	//�M��Log
	log.clear();
	LogPage = 1;
	nowLogPage = 1;




	bool result = ChessBoard::Instance->ifCheckmate(player % 2);
	//�U�@��i��|�N�x
	if (result) {
		UI::Instance->showGeneral(true, player % 2);
		//����N�x����
		playMusic(musicMode, Music::Sound::General);
	}
	else {
		bool result = ChessBoard::Instance->ifCheckmate((player + 1) % 2);
		if (result) {
			UI::Instance->showGeneral(true, (player + 1) % 2);
			//����N�x����
			playMusic(musicMode, Music::Sound::General);
		}
		else {
			UI::Instance->showGeneral(false);
		}
	}

	//���s�]�m�ѽL���
	BoardCursor = make_pair(0, 0);
	UI::Instance->gotoBoardXY(BoardCursor);
	//��H�C���B�q������
	if (GameMode == 1 && player == 0) {
		Sleep(500);
		UI::Instance->showAdditionText(L"Brandon��Ҥ�...");
		AIChessMove();

		NextPlayer();
	}



}

void GameSystem::WinGame()
{
	if (musicMode == Music::MusicMode::noise) {
		//����N�ΫӦ��`������(�𨽧J)
		playMusic(musicMode, Music::Sound::Dead);
		//�����ĩ�
		Sleep(2500);
	}
	//���Victory�϶�
	UI::Instance->showBlock(screen, Setting::Block::Victory);
	UI::Instance->gotoXY(43, 12);
	//�������
	if (player == 1) {
		UI::Instance->SetTextColor(Setting::Color::red, Setting::Color::black, true);
		cout << "���@��";
	}
	//�¤����
	else if (player == 0) {
		UI::Instance->SetTextColor(Setting::Color::white, Setting::Color::black);
		cout << "�¡@��";
	}
	//��Ц^��"�Ы����N���~��..."
	UI::Instance->gotoXY(63, 15);
	//����ӧQ����
	if (musicMode != Music::MusicMode::quiet) {
		//����ӧQ����
		playMusic(musicMode, Music::Sound::Victory);
	}
	Sleep(1200);
	nowStatus = Status::Win;
	//�M���w�İϡA�קK�ϥΪ̦b�q����ҮɡA�~Ĳ����

	Sleep(100);
	while (_kbhit()) {
		char c = _getch();
	}
}

//���ʴѤl�G�^�� 0�G���ʦ��~�B1�G���T���ʡB2�G�C���ӧQ
int GameSystem::ChessMove(Coordinate destination)
{
	//�j�M�i������m���S���ǤJ���y��
	for (auto item : AvailableMove) {
		if (item.second == destination) {
			//�I�slog����
			log.push(SelectedChess.first, make_pair(SelectedChess.second.second, SelectedChess.second.first), make_pair(destination.second, destination.first));
			//���Y���O�H����
			if (item.first != 0) {
				//�N�Q�Y���������Ѳ���(-1,-1) (�Y����)
				ChessBoard::Instance->modify(item.first, make_pair(item.second.second, item.second.first), make_pair(-1, -1));
				//�Y���өαN

				if ((item.first == 1 && ChessBoard::Instance->getChessNum(1) == 0) || (item.first == 8 && ChessBoard::Instance->getChessNum(8) == 0)) {
					//����U�ѭ���
					playChessSound(musicMode, SelectedChess.first);
					//�ѩ�o�̪���return�A�]�����F�ϵ�ı�ĪG���W�A�G�����ק�éI�sUI
					ChessBoard::Instance->modify(SelectedChess.first, make_pair(SelectedChess.second.second, SelectedChess.second.first), make_pair(destination.second, destination.first));
					UI::Instance->DrawBoard();
					//���F�ϵ�ı�ĪG��{�A�G����0.5��
					Sleep(500);

					UI::Instance->gotoBoardXY(BoardCursor);
					//�I�s�ӧQ�禡
					UI::Instance->showGeneral(false);
					WinGame();
					return 2;
				}
			}

			//�h�@��
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

			//����U�ѭ���
			playChessSound(musicMode, SelectedChess.first);

			//�^�k�w�]���A
			SelectedChess.first = 0;


			bool result = ChessBoard::Instance->ifCheckmate((player + 1) % 2);
			//�U�@��i��|�N�x
			if (result) {
				UI::Instance->showGeneral(true, (player + 1) % 2);
				//����N�x����
				playMusic(musicMode, Music::Sound::General);
			}
			else {
				bool result = ChessBoard::Instance->ifCheckmate((player + 2) % 2);
				if (result) {
					UI::Instance->showGeneral(true, (player + 2) % 2);
					//����N�x����
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

//�x�s�C��
bool GameSystem::StoreGame()
{
	ofstream file;
	string fileName = "SaveData//" + FileName + ".txt";
	file.open(fileName, ios::out);
	//�}���ɮץ���
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

//����Log������
//�ѼơG+1���V��½�A-1���V�e½
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

	//��Ц^��쥻����m
	UI::Instance->gotoBoardXY(BoardCursor);
}

// ����
bool GameSystem::Regret()
{
	//�Y�����֩��ӫh����i�殬��
	if (log.getLength() < 2) {
		return false;
	}
	auto record = log.pop();
	for (auto item : record) {
		ChessBoard::Instance->modify(item.first, item.second.second, item.second.first);
	}

	//�֤@��
	if (ceil((double)log.getLength() / 17) < LogPage) {
		if (LogPage != 1)LogPage--;
	}
	//�۰�½���s�����@��
	nowLogPage = LogPage - 1;
	turnLogPage(1);
	//��ܭ���
	UI::Instance->showLogPage(nowLogPage, LogPage);
	//���e�ѽL
	UI::Instance->DrawBoard();

	//�U�@��i��|�N�x

	bool result = ChessBoard::Instance->ifCheckmate((player + 1) % 2);
	//�U�@��i��|�N�x
	if (result) {
		UI::Instance->showGeneral(true, (player + 1) % 2);
		//����N�x����
		playMusic(musicMode, Music::Sound::General);
	}
	else {
		bool result = ChessBoard::Instance->ifCheckmate((player + 2) % 2);
		if (result) {
			UI::Instance->showGeneral(true, (player + 2) % 2);
			//����N�x����
			playMusic(musicMode, Music::Sound::General);
		}
		else {
			UI::Instance->showGeneral(false);
		}
	}

	return true;
}

//Ū���ɮ�
//�ѼơG�ǤJ���}�Ҫ��ɮצW��(�t���ɦW)
//�^�ǥN�X�G 0�G�ɮ׶}�Ҳ��` 1�G�ɮ׮榡���~ 2�G���\Ū��
int GameSystem::LoadGame(string fileName)
{
	ifstream file;
	string tmp = "SaveData//" + fileName + ".txt";
	file.open(tmp, ios::in);
	//�ɮ׶}�Ҧ��\
	if (file) {
		tmp = "";
		int chessNum, firstPlayer;
		vector<vector<int>> board(10, vector<int>(9));
		for (int row = 0; row < 10; row++) {
			for (int column = 0; column < 9; column++) {
				//�Y���W����F�ɮש����A�N��Ӥ����~
				if (file.eof()) {
					file.close();
					return 1;
				}
				file >> tmp;

				//�Y�ɮ׮榡���~�A�h�^��1
				for (auto c : tmp) {
					if (!isdigit(c)) {
						file.close();
						return 1;
					}
				}
				chessNum = stoi(tmp);
				//�Y��J�榡���~
				if (chessNum > 14) {
					file.close();
					return 1;
				}
				board[row][column] = chessNum;
			}
		}
		if (!file.eof()) {
			file >> tmp;
			//�̫�@�����u���@�ӼƦr
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

//���ʿﶵ
//�ѼơG+1���V�U�Υk�A-1���V�W�Υ�
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

	//����쥻���ﶵ���C��
	UI::Instance->SetTextColor(Setting::Color::white, Setting::Color::black);
	UI::Instance->gotoXY(nowMenu[SelectedIndex].second);
	wcout << nowMenu[SelectedIndex].first;

	//����U�ӿﶵ
	SelectedIndex += direction;
	if (SelectedIndex < 0) {
		SelectedIndex = (int)(nowMenu.size() - 1);
	}
	else if (SelectedIndex >= nowMenu.size()) {
		SelectedIndex %= nowMenu.size();
	}

	//��X�U�ӿﶵ���ʴ��
	UI::Instance->SetTextColor(Setting::Color::black, Setting::Color::white, false, true);
	UI::Instance->gotoXY(nowMenu[SelectedIndex].second);
	wcout << nowMenu[SelectedIndex].first;
	//���񭵮�
	if (musicplay) {
		playMusic(musicMode, Music::MoveCursor);
	}

	//��Ц^��e��(��X���W��r�|�첾��)
	UI::Instance->gotoXY(nowMenu[SelectedIndex].second);
}

// ���ʹ�߿��W�����(�ǤJ�W�U���k)
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

	//����쥻���ﶵ���C��
	UI::Instance->SetTextColor(Setting::Color::white, Setting::Color::black);
	for (int x = nowMenu.second[SelectedIndex].first, y = nowMenu.second[SelectedIndex].second, i = 0; i < width; i++) {
		UI::Instance->DrawHorizontalLine(make_pair(x, y + i), length, L' ');
	}

	//�ﶵ�e�i
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
		//�N�{�b������Ѫ��������
		UI::Instance->showSelectedChess(0);
		UI::Instance->gotoBoardXY(BoardCursor);
		UI::Instance->showGeneral(false);
		/*bool result = ChessBoard::Instance->ifCheckmate((player + 1) % 2);
		//�U�@��i��|�N�x
		if (result) {
			UI::Instance->showGeneral(true, (player + 1) % 2);
			//����N�x����
			playMusic(musicMode, Music::Sound::General);
		}*/
	}
	while (_kbhit()) {
		_getch();
	}
}

//����U�Ӫ��a
void GameSystem::NextPlayer()
{
	player = (player + 1) % 2;
	bool result = ChessBoard::Instance->ifCheckmate(player);
	/*//�U�@��i��|�N�x
	if (result) {
		UI::Instance->showGeneral(true, player);
		//����N�x����
		playMusic(musicMode, Music::Sound::General);
	}*/

	//�Y����H�C���B����q��
	if (GameMode == 1 && player == 0) {

		UI::Instance->showPlayer(player);
		UI::Instance->showAdditionText(L"Brandon��Ҥ�...");

		AIChessMove();
		//�q���ӧQ
		if (nowStatus == Status::Win) {
			return;
		}
		player = 1;
	}

	UI::Instance->showPlayer(player);
	UI::Instance->gotoBoardXY(BoardCursor);
}


// �q����|���_�C�������A�^�k�C��
void GameSystem::Resume()
{
	//���e�ѽL
	UI::Instance->DrawBoard();

	//�N��{�b�����ʴѤl�Ҧ�
	if (SelectedChess.first != 0) {
		nowStatus = Status::MoveChess;
		ChessSelect(SelectedChess.second);
	}
	//�N��{�b����ܴѤl�Ҧ�
	else {
		nowStatus = Status::SelectChess;
	}
	//��Ц^��쥻����m
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

	//����쥻���ﶵ���C��
	UI::Instance->SetTextColor(Setting::Color::white, Setting::Color::black);
	UI::Instance->DrawHorizontalLine(make_pair(nowData.second[SelectedIndex].first, nowData.second[SelectedIndex].second), length, L' ');
	UI::Instance->gotoXY(nowData.second[SelectedIndex].first, nowData.second[SelectedIndex].second);
	cout << TXTFiles[(nowDataPage - 1) * 3 + SelectedIndex];

	//�ﶵ�e�i
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
	//���A�]������X�l
	nowStatus = Status::SelectChess;
	SelectedIndex = 0;
	SelectedChess.first = 0;

	//��ø�e��
	UI::Instance->showScreen(Screen::Making);

	//���s�]�m�ѽL���
	BoardCursor = make_pair(0, 0);
	UI::Instance->gotoXY(67, 6);
}

//byHans
void GameSystem::MoveMakeCursor(Key input)
{
	auto nowMenu = MenuList[make_pair(screen, nowStatus)];

	//����쥻���ﶵ���C��
	if (SelectedIndex < 8)
		UI::Instance->SetTextColor(Setting::Color::black, Setting::Color::gray);
	else
		UI::Instance->SetTextColor(Setting::Color::red, Setting::Color::gray);
	UI::Instance->gotoXY(nowMenu[SelectedIndex].second);
	wcout << nowMenu[SelectedIndex].first;

	//����U�ӿﶵ
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

	//��X�U�ӿﶵ���ʴ��
	if (SelectedIndex < 8)
		UI::Instance->SetTextColor(Setting::Color::black, Setting::Color::white, 0, 1);
	else
		UI::Instance->SetTextColor(Setting::Color::red, Setting::Color::white, 1, 1);
	UI::Instance->gotoXY(nowMenu[SelectedIndex].second);
	wcout << nowMenu[SelectedIndex].first;

	//��Ц^��e��(��X���W��r�|�첾��)
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
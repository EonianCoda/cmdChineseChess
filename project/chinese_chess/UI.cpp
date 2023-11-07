#include "UI.h"

namespace {
	const wchar_t list[] = L"　將士象車馬包卒帥仕相車傌炮兵";
}

UI* UI::Instance;

//建構式：將游標座標設為(0,0)、並將字設為黑底白字
UI::UI() :handle(GetStdHandle(STD_OUTPUT_HANDLE)), CursorPos({ 0,0 })
{
	//將字設為黑底白字
	SetTextColor(Setting::Color::white, Setting::Color::black);

	//讓中文字可以正常輸出
	std::locale loc("");
	std::wcout.imbue(loc);
}

//解構式
UI::~UI()
{
}

//清除畫面，並將字設為黑底白字
void UI::CleanScreen()
{
	SetTextColor(Setting::Color::white, Setting::Color::black);
	system("CLS");
}

//設置字的顏色
//輸入： front：字的顏色 back：背景顏色 frontLight：字是否加亮(預設否) backLight：背景是否加亮(預設否)
void UI::SetTextColor(Setting::Color front, Setting::Color back, bool frontLight, bool backLight)
{
	colorCode = back * 16 + front;
	if (front != Setting::Color::gray && frontLight) {
		colorCode += 8;
	}
	if (back != Setting::Color::gray && backLight) {
		colorCode += 128;
	}
	SetConsoleTextAttribute(handle, colorCode);
}

void UI::SetTextColor(int colorCode)
{
	this->colorCode = colorCode;
	SetConsoleTextAttribute(handle, colorCode);
}

//設置游標位置：左上角為(0,0)，向右為+X軸 向下為+Y軸
//參數： (x,y)
void UI::gotoXY(int x, int y)
{
	if (x >= 0 && y >= 0) {
		CursorPos.X = x;
		CursorPos.Y = y;
		SetConsoleCursorPosition(handle, CursorPos);
	}
}

//設置游標位置：左上角為(0,0)，向右為+X軸 向下為+Y軸
//參數： 一個pair<int,int>
void UI::gotoXY(Coordinate pos)
{
	if (pos.first >= 0 && pos.second >= 0) {
		CursorPos.X = pos.first;
		CursorPos.Y = pos.second;
		SetConsoleCursorPosition(handle, CursorPos);
	}
}

//設置游標位置到棋盤上：棋盤X：0~8，棋盤Y：0~9
//參數： Coordinate：在棋盤上(9*10)的座標
void UI::gotoBoardXY(Coordinate co)
{
	if (co.first >= 0 && co.first <= 8 && co.second >= 0 && co.second <= 9) {
		gotoXY(co.first * 4 + 29, 3 + co.second * 2);
	}
	//若輸入不合法，則輸出錯誤訊息
	else {
		cout << "(" << co.first << "," << co.first << ")";
		cout << "超出範圍" << endl;
	}
}

//獲取游標位置
//回傳一個Coordinate (pair<int,int>)
Coordinate UI::getXY()
{
	return make_pair<int, int>((int)CursorPos.X, (int)CursorPos.Y);
}

//更新特定畫面
//參數：一個Screen
void UI::showScreen(Screen screen)
{
	//先清除畫面
	CleanScreen();
	switch (screen) {

	case MainMenu:
		SetTextColor(Setting::Color::white, Setting::Color::black, true);
		DrawFrame(make_pair(0, 0), 97, 25);
		gotoXY(0, 24);
		cout << "微軟注音 半 :";
		ShowstartingScreen();
		showBlock(screen, Setting::Block::Main);
		break;

	case Playing:

		SetTextColor(Setting::Color::white, Setting::Color::black, true);
		DrawFrame(make_pair(0, 0), 97, 25);
		gotoXY(0, 24);
		cout << "微軟注音 半 :";


		showBlock(screen, Setting::Block::Log);
		showBlock(screen, Setting::Block::Status);

		gotoXY(0, 24);
		SetTextColor(Setting::Color::white, Setting::Color::black);
		//畫棋盤
		DrawBoard();
		break;

	case Making:
		SetTextColor(Setting::Color::white, Setting::Color::black, true);
		DrawFrame(make_pair(0, 0), 97, 25);
		gotoXY(0, 24);
		cout << "微軟注音 半 :";

		showBlock(screen, Setting::Block::ChessNums);
		showBlock(screen, Setting::Block::Selecting);

		gotoXY(0, 24);

		SetTextColor(Setting::Color::white, Setting::Color::black);
		//畫棋盤
		DrawBoard();
		break;
	};
}

//顯示特定區塊
//參數： (畫面(Screen),區塊(Block))
void UI::showBlock(Screen screen, Setting::Block block)
{
	if (screen == Screen::MainMenu) {
		if (block == Setting::Block::Main) {

			SetTextColor(Setting::Color::white, Setting::Color::black, true);
			DrawFrame(make_pair(39, 11), 23, 13);

			SetTextColor(Setting::Color::black, Setting::Color::white, false, true);
			DrawHorizontalLine(make_pair(41, 12), 20, L' ');
			DrawHorizontalLine(make_pair(41, 13), 20, L' ');
			DrawHorizontalLine(make_pair(41, 14), 20, L' ');
			gotoXY(47, 13);
			cout << "開始遊戲";


			SetTextColor(Setting::Color::white, Setting::Color::black, true);
			DrawHorizontalLine(make_pair(40, 15), 21);
			gotoXY(49, 17);
			cout << "選項";
			DrawHorizontalLine(make_pair(40, 19), 21);
			gotoXY(47, 21);
			cout << "離開遊戲";

			//游標回到雙人遊戲
			gotoXY(47, 13);
		}
		//選擇遊戲模式(單人/雙人)
		else if (block == Setting::Block::SelectMode) {
			SetTextColor(Setting::Color::white, Setting::Color::black, true);
			DrawFrame(make_pair(39, 11), 23, 13);
			DrawHorizontalLine(make_pair(40, 17), 21);

			SetTextColor(Setting::Color::black, Setting::Color::white, false, true);
			DrawHorizontalLine(make_pair(41, 12), 20, L' ');
			DrawHorizontalLine(make_pair(41, 13), 20, L' ');
			DrawHorizontalLine(make_pair(41, 14), 20, L' ');
			DrawHorizontalLine(make_pair(41, 15), 20, L' ');
			DrawHorizontalLine(make_pair(41, 16), 20, L' ');
			gotoXY(47, 14);

			cout << "單人遊戲";
			SetTextColor(Setting::Color::white, Setting::Color::black, true);
			gotoXY(47, 20);
			cout << "雙人遊戲";
			//游標回到單人遊戲
			gotoXY(47, 14);
		}
		//單人遊戲清單(先攻 or 後攻)
		else if (block == Setting::Block::SelectSinglePlayer) {
			SetTextColor(Setting::Color::blue, Setting::Color::black, true);
			DrawFrame(make_pair(39, 11), 23, 13);
			DrawHorizontalLine(make_pair(40, 17), 21);

			SetTextColor(Setting::Color::black, Setting::Color::white, false, true);
			DrawHorizontalLine(make_pair(41, 12), 20, L' ');
			DrawHorizontalLine(make_pair(41, 13), 20, L' ');
			DrawHorizontalLine(make_pair(41, 14), 20, L' ');
			DrawHorizontalLine(make_pair(41, 15), 20, L' ');
			DrawHorizontalLine(make_pair(41, 16), 20, L' ');
			gotoXY(47, 14);

			cout << "玩家先攻";
			SetTextColor(Setting::Color::white, Setting::Color::black, true);
			gotoXY(47, 20);
			cout << "電腦先攻";
			//游標回到玩家先攻
			gotoXY(47, 14);
		}
		//雙人遊戲清單(新遊戲、讀取舊紀錄、返回上一頁)
		else if (block == Setting::Block::DuoPlayerMenu || block == Setting::Block::SinglePlayerMenu) {
			SetTextColor(Setting::Color::green, Setting::Color::black);
			DrawFrame(make_pair(39, 11), 23, 13);
			DrawHorizontalLine(make_pair(40, 17), 21);

			SetTextColor(Setting::Color::black, Setting::Color::white, false, true);
			DrawHorizontalLine(make_pair(41, 12), 20, L' ');
			DrawHorizontalLine(make_pair(41, 13), 20, L' ');
			DrawHorizontalLine(make_pair(41, 14), 20, L' ');
			DrawHorizontalLine(make_pair(41, 15), 20, L' ');
			DrawHorizontalLine(make_pair(41, 16), 20, L' ');


			gotoXY(46, 14);
			cout << "開始新遊戲";
			SetTextColor(Setting::Color::white, Setting::Color::black, true);
			gotoXY(46, 20);
			cout << "讀取舊紀錄";
			//游標回到開始新遊戲
			gotoXY(47, 14);
		}
		//選擇紅方/黑方
		else if (block == Setting::Block::SelectPlayer) {
			SetTextColor(Setting::Color::blue, Setting::Color::black, true);
			DrawFrame(make_pair(39, 11), 23, 13);
			DrawHorizontalLine(make_pair(40, 17), 21);

			SetTextColor(Setting::Color::black, Setting::Color::white, false, true);
			DrawHorizontalLine(make_pair(41, 12), 20, L' ');
			DrawHorizontalLine(make_pair(41, 13), 20, L' ');
			DrawHorizontalLine(make_pair(41, 14), 20, L' ');
			DrawHorizontalLine(make_pair(41, 15), 20, L' ');
			DrawHorizontalLine(make_pair(41, 16), 20, L' ');
			gotoXY(47, 14);

			cout << "紅方先攻";
			SetTextColor(Setting::Color::white, Setting::Color::black, true);
			gotoXY(47, 20);
			cout << "黑方先攻";
			//游標回到紅方先攻
			gotoXY(47, 14);
		}
		//讀取舊檔案
		else if (block == Setting::Block::Read) {
			SetTextColor(Setting::Color::yellow, Setting::Color::black, true);
			DrawFrame(make_pair(39, 11), 23, 13);

			SetTextColor(Setting::Color::white, Setting::Color::black, true);
			gotoXY(44, 12);
			cout << "請選擇存檔名稱";
		}
		//檔案讀取錯誤
		else if (block == Setting::Block::Read_Error) {
			SetTextColor(Setting::Color::red, Setting::Color::black, true);
			DrawFrame(make_pair(39, 11), 23, 13);

			gotoXY(44, 13);
			cout << "檔案讀取錯誤!!";
			SetTextColor(Setting::Color::white, Setting::Color::black, true);
			gotoXY(42, 15);
			cout << "可能為以下原因：";
			gotoXY(45, 17);
			cout << "1.名稱錯誤";
			gotoXY(45, 18);
			cout << "2.誤加了副檔名";
			gotoXY(45, 19);
			cout << "3.紀錄格式有誤";
			SetTextColor(Setting::Color::gray, Setting::Color::black);
			gotoXY(45, 22);
			cout << "請按任意鍵繼續..";
			gotoXY(60, 22);
		}
		else if (block == Setting::Block::Option) {
			SetTextColor(Setting::Color::white, Setting::Color::black, true);
			DrawFrame(make_pair(39, 11), 23, 13);
			DrawHorizontalLine(make_pair(40, 17), 21);

			SetTextColor(Setting::Color::black, Setting::Color::white, false, true);
			DrawHorizontalLine(make_pair(41, 12), 20, L' ');
			DrawHorizontalLine(make_pair(41, 13), 20, L' ');
			DrawHorizontalLine(make_pair(41, 14), 20, L' ');
			DrawHorizontalLine(make_pair(41, 15), 20, L' ');
			DrawHorizontalLine(make_pair(41, 16), 20, L' ');
			gotoXY(47, 14);
			cout << "系統音效";

			SetTextColor(Setting::Color::white, Setting::Color::black, true);
			gotoXY(46, 20);
			cout << "自定義棋盤";
			
			//游標回到系統音效
			gotoXY(47, 14);
		}
		else if (block == Setting::Block::Sound) {
			SetTextColor(Setting::Color::white, Setting::Color::black, true);
			DrawFrame(make_pair(39, 11), 23, 13);
			DrawHorizontalLine(make_pair(40, 15), 21);
			DrawHorizontalLine(make_pair(40, 19), 21);
			SetTextColor(Setting::Color::black, Setting::Color::white, false, true);
			DrawHorizontalLine(make_pair(41, 12), 20, L' ');
			DrawHorizontalLine(make_pair(41, 13), 20, L' ');
			DrawHorizontalLine(make_pair(41, 14), 20, L' ');
			gotoXY(47, 13);
			cout << "靜音模式";

			SetTextColor(Setting::Color::white, Setting::Color::black, true);
			gotoXY(47, 17);
			cout << "一般音效";
			gotoXY(47, 21);
			cout << "特殊音效";
			//游標回到開始新遊戲
			gotoXY(47, 13);
		}
	}
	else if (screen == Screen::Playing) {
		//戰況顯示
		if (block == Setting::Block::Log) {
			SetTextColor(Setting::Color::white, Setting::Color::black);
			DrawFrame(make_pair(2, 1), 24, 23);
			gotoXY(5, 1);
			cout << "　 戰　況　顯　示　";

			DrawHorizontalLine(make_pair(3, 21), 22);
			gotoXY(4, 22);
			cout << "← 第 ";
			gotoXY(12, 22);
			cout << "頁/共";
			gotoXY(20, 22);
			cout << "頁 →";
			showLogPage(1, 1);

		}
		//棋盤
		else if (block == Setting::Block::ChessBoard) {
			DrawBoard();
		}
		//狀態顯示
		else if (block == Setting::Block::Status) {
			SetTextColor(Setting::Color::white, Setting::Color::black);
			DrawFrame(make_pair(64, 1), 31, 23);
			DrawHorizontalLine(make_pair(65, 13), 29);

			SetTextColor(Setting::Color::green, Setting::Color::black, true);
			gotoXY(70, 4);
			cout << "現在輪到";
			gotoXY(86, 4);
			cout << "下棋";


			SetTextColor(Setting::Color::white, Setting::Color::black);
			gotoXY(68, 14);
			cout << "Esc 選單         h 幫助";
			gotoXY(68, 16);
			cout << "Enter 選取棋子   z 悔棋";
			gotoXY(71, 19);
			cout << "↑";
			gotoXY(69, 20);
			cout << "←  → 方向鍵控制游標";
			gotoXY(71, 21);
			cout << "↓";
		}
		//快捷鍵清單
		else if (block == Setting::Block::Help) {
			SetTextColor(Setting::Color::yellow, Setting::Color::black, true);
			DrawFrame(make_pair(29, 2), 33, 21);
			SetTextColor(Setting::Color::green, Setting::Color::black, true);
			gotoXY(41, 3);
			cout << "快捷鍵清單";


			gotoXY(31, 5);
			SetTextColor(Setting::Color::green, Setting::Color::black, true);
			cout << "Esc";
			SetTextColor(Setting::Color::white, Setting::Color::black, true);
			cout << "：開啟主選單/關閉任何的選單";

			gotoXY(31, 7);
			SetTextColor(Setting::Color::purple, Setting::Color::black, true);
			cout << "h";
			SetTextColor(Setting::Color::white, Setting::Color::black, true);
			cout << "：呼叫/關閉幫助清單";
			gotoXY(31, 9);
			SetTextColor(Setting::Color::green, Setting::Color::black, true);
			cout << "Enter";
			SetTextColor(Setting::Color::white, Setting::Color::black, true);
			cout << "：選取/放棄選取/放置棋子";
			gotoXY(31, 11);
			SetTextColor(Setting::Color::purple, Setting::Color::black, true);
			cout << "z";
			SetTextColor(Setting::Color::white, Setting::Color::black, true);
			cout << "：呼叫/關閉悔棋選單";

			gotoXY(31, 13);
			SetTextColor(Setting::Color::purple, Setting::Color::black, true);
			cout << "s";
			SetTextColor(Setting::Color::white, Setting::Color::black, true);
			cout << "：儲存遊戲";
			gotoXY(31, 15);
			SetTextColor(Setting::Color::green, Setting::Color::black, true);
			cout << "< >";
			SetTextColor(Setting::Color::white, Setting::Color::black, true);
			cout << "：調整戰況顯示頁數";


			gotoXY(33, 19);
			cout << "↑";
			gotoXY(31, 20);
			cout << "←  → 方向鍵控制游標";
			gotoXY(33, 21);
			cout << "↓";
		}
		//暫停(選單)
		else if (block == Setting::Block::Pause) {
			SetTextColor(Setting::Color::blue, Setting::Color::black, true);
			DrawFrame(make_pair(43, 6), 20, 11);
			DrawHorizontalLine(make_pair(44, 8), 18);
			DrawHorizontalLine(make_pair(44, 10), 18);
			DrawHorizontalLine(make_pair(44, 12), 18);
			DrawHorizontalLine(make_pair(44, 14), 18);

			SetTextColor(Setting::Color::black, Setting::Color::white, false, true);
			gotoXY(50, 7);
			cout << "繼續遊戲";

			SetTextColor(Setting::Color::white, Setting::Color::black);

			gotoXY(50, 9);
			cout << "重新開始";
			gotoXY(50, 11);
			cout << "回主選單";
			gotoXY(50, 13);
			cout << "儲存遊戲";
			gotoXY(50, 15);
			cout << "離開遊戲";
			//繼續遊戲的座標
			//gotoXY(50, 8);
			//重新開始的座標
			//gotoXY(51, 9);
			//回主選單的座標
			//gotoXY(51, 11);
			//離開遊戲的座標
			//gotoXY(51, 13);
		}
		//悔棋
		else if (block == Setting::Block::Regret) {
			SetTextColor(Setting::Color::red, Setting::Color::black);
			DrawFrame(make_pair(43, 8), 20, 8);

			gotoXY(49, 11);
			SetTextColor(Setting::Color::white, Setting::Color::black);
			cout << "確定悔棋?";
			gotoXY(48, 13);
			SetTextColor(Setting::Color::black, Setting::Color::white, false, true);
			cout << "是";
			SetTextColor(Setting::Color::white, Setting::Color::black);
			gotoXY(56, 13);
			cout << "否";
			//「是」的座標
			//gotoXY(49, 13);
			//「否」的座標
			//gotoXY(57, 13);
		}
		//確定重新開始?
		else if (block == Setting::Block::Restart) {
			SetTextColor(Setting::Color::red, Setting::Color::black);
			DrawFrame(make_pair(43, 6), 20, 11);

			gotoXY(47, 9);
			SetTextColor(Setting::Color::white, Setting::Color::black);
			cout << "確定重新開始?";
			gotoXY(49, 13);
			SetTextColor(Setting::Color::black, Setting::Color::white, false, true);
			cout << "是";
			SetTextColor(Setting::Color::white, Setting::Color::black);
			gotoXY(57, 13);
			cout << "否";
		}
		//勝利區塊
		else if (block == Setting::Block::Victory) {
			SetTextColor(Setting::Color::red, Setting::Color::black, true);
			DrawFrame(make_pair(33, 7), 33, 10);
			SetTextColor(Setting::Color::white, Setting::Color::black, true);
			gotoXY(36, 9);
			cout << " Ｖ　Ｉ　Ｃ　Ｔ　Ｏ　Ｒ　Ｙ";
			SetTextColor(Setting::Color::white, Setting::Color::black, true);
			gotoXY(49, 12);
			cout << "　獲　勝";

			gotoXY(46, 15);
			SetTextColor(Setting::Color::gray, Setting::Color::black, true);
			cout << "請按任意鍵繼續...";
		}
		//儲存區塊
		else if (block == Setting::Block::Store) {
			SetTextColor(Setting::Color::red, Setting::Color::black);
			DrawFrame(make_pair(30, 6), 33, 12);


			gotoXY(39, 8);
			SetTextColor(Setting::Color::white, Setting::Color::black);
			cout << "請輸入存檔名稱";
			SetTextColor(Setting::Color::gray, Setting::Color::black);
			gotoXY(32, 10);
			cout << "(名稱須為字母與數字,最多12字)";

			gotoXY(35, 13);
			SetTextColor(Setting::Color::white, Setting::Color::black);
			SetConsoleTextAttribute(handle, colorCode | COMMON_LVB_UNDERSCORE);
			for (int i = 0; i < 12; i++) {
				SetConsoleTextAttribute(handle, colorCode | COMMON_LVB_UNDERSCORE);
				cout << " ";
				SetConsoleTextAttribute(handle, colorCode);
				cout << " ";
			}
			SetTextColor(Setting::Color::gray, Setting::Color::black);
			gotoXY(32, 16);
			cout << "Esc 取消儲存  /  按下Enter儲存";

			SetTextColor(Setting::Color::white, Setting::Color::black);
			//設置輸出字有底線
			SetConsoleTextAttribute(handle, colorCode | COMMON_LVB_UNDERSCORE);
		}
		//你沒什麼好後悔的
		else if (block == Setting::Block::CannotRegret) {
			SetTextColor(Setting::Color::blue, Setting::Color::black, true);
			DrawFrame(make_pair(35, 7), 28, 10);
			gotoXY(41, 11);
			SetTextColor(Setting::Color::white, Setting::Color::black);
			cout << "你沒什麼好後悔的!!";

			gotoXY(45, 15);
			SetTextColor(Setting::Color::gray, Setting::Color::black);
			cout << "請按任意鍵繼續..";
		}
	}
	else if (screen == Screen::Making) {
		if (block == Setting::Block::ChessNums) {
			SetTextColor(Setting::Color::white, Setting::Color::black);
			DrawFrame(make_pair(2, 1), 24, 23);
			gotoXY(5, 1);
			cout << "　 棋　數　統　計　";
			DrawVerticalLine(make_pair(13, 3), 20);
			gotoXY(5, 3);
			SetTextColor(Setting::Color::black, Setting::Color::gray);
			cout << "將";
			SetTextColor(Setting::Color::white, Setting::Color::black);
			cout << "： " << ChessBoard::Instance->getChessNum(1);
			gotoXY(5, 6);
			SetTextColor(Setting::Color::black, Setting::Color::gray);
			cout << "士";
			SetTextColor(Setting::Color::white, Setting::Color::black);
			cout << "： " << ChessBoard::Instance->getChessNum(2);
			gotoXY(5, 9);
			SetTextColor(Setting::Color::black, Setting::Color::gray);
			cout << "象";
			SetTextColor(Setting::Color::white, Setting::Color::black);
			cout << "： " << ChessBoard::Instance->getChessNum(3);
			gotoXY(5, 12);
			SetTextColor(Setting::Color::black, Setting::Color::gray);
			cout << "車";
			SetTextColor(Setting::Color::white, Setting::Color::black);
			cout << "： " << ChessBoard::Instance->getChessNum(4);
			gotoXY(5, 15);
			SetTextColor(Setting::Color::black, Setting::Color::gray);
			cout << "馬";
			SetTextColor(Setting::Color::white, Setting::Color::black);
			cout << "： " << ChessBoard::Instance->getChessNum(5);
			gotoXY(5, 18);
			SetTextColor(Setting::Color::black, Setting::Color::gray);
			cout << "包";
			SetTextColor(Setting::Color::white, Setting::Color::black);
			cout << "： " << ChessBoard::Instance->getChessNum(6);
			gotoXY(5, 21);
			SetTextColor(Setting::Color::black, Setting::Color::gray);
			cout << "卒";
			SetTextColor(Setting::Color::white, Setting::Color::black);
			cout << "： " << ChessBoard::Instance->getChessNum(7);

			gotoXY(16, 3);
			SetTextColor(Setting::Color::red, Setting::Color::gray);
			cout << "帥";
			SetTextColor(Setting::Color::white, Setting::Color::black);
			cout << "： " << ChessBoard::Instance->getChessNum(8);
			gotoXY(16, 6);
			SetTextColor(Setting::Color::red, Setting::Color::gray);
			cout << "仕";
			SetTextColor(Setting::Color::white, Setting::Color::black);
			cout << "： " << ChessBoard::Instance->getChessNum(9);
			gotoXY(16, 9);
			SetTextColor(Setting::Color::red, Setting::Color::gray);
			cout << "相";
			SetTextColor(Setting::Color::white, Setting::Color::black);
			cout << "： " << ChessBoard::Instance->getChessNum(10);
			gotoXY(16, 12);
			SetTextColor(Setting::Color::red, Setting::Color::gray);
			cout << "車";
			SetTextColor(Setting::Color::white, Setting::Color::black);
			cout << "： " << ChessBoard::Instance->getChessNum(11);
			gotoXY(16, 15);
			SetTextColor(Setting::Color::red, Setting::Color::gray);
			cout << "傌";
			SetTextColor(Setting::Color::white, Setting::Color::black);
			cout << "： " << ChessBoard::Instance->getChessNum(12);
			gotoXY(16, 18);
			SetTextColor(Setting::Color::red, Setting::Color::gray);
			cout << "炮";
			SetTextColor(Setting::Color::white, Setting::Color::black);
			cout << "： " << ChessBoard::Instance->getChessNum(13);
			gotoXY(16, 21);
			SetTextColor(Setting::Color::red, Setting::Color::gray);
			cout << "兵";
			SetTextColor(Setting::Color::white, Setting::Color::black);
			cout << "： " << ChessBoard::Instance->getChessNum(14);
		}
		else if (block == Setting::Block::Selecting) {
			SetTextColor(Setting::Color::white, Setting::Color::black);
			DrawFrame(make_pair(64, 1), 31, 23);
			DrawHorizontalLine(make_pair(65, 12), 29);
			gotoXY(72, 3);
			cout << "請選擇要放的棋子";
			gotoXY(67, 5);
			SetTextColor(Setting::Color::black, Setting::Color::gray);
			cout << "　";
			gotoXY(67, 7);
			cout << "將";
			gotoXY(71, 7);
			cout << "士";
			gotoXY(75, 7);
			cout << "象";
			gotoXY(79, 7);
			cout << "車";
			gotoXY(83, 7);
			cout << "馬";
			gotoXY(87, 7);
			cout << "包";
			gotoXY(91, 7);
			cout << "卒";
			SetTextColor(Setting::Color::red, Setting::Color::gray);
			gotoXY(67, 9);
			cout << "帥";
			gotoXY(71, 9);
			cout << "仕";
			gotoXY(75, 9);
			cout << "相";
			gotoXY(79, 9);
			cout << "車";
			gotoXY(83, 9);
			cout << "傌";
			gotoXY(87, 9);
			cout << "炮";
			gotoXY(91, 9);
			cout << "兵";

			SetTextColor(Setting::Color::white, Setting::Color::black);
			gotoXY(68, 14);
			cout << "Esc 選單         h 幫助";
			gotoXY(68, 16);
			cout << "Enter 選取棋子";
			gotoXY(71, 19);
			cout << "↑";
			gotoXY(69, 20);
			cout << "←  → 方向鍵控制游標";
			gotoXY(71, 21);
			cout << "↓";
		}
		else if (block == Setting::Block::Pause) {
			SetTextColor(Setting::Color::blue, Setting::Color::black, true);
			DrawFrame(make_pair(43, 6), 20, 11);
			DrawHorizontalLine(make_pair(44, 8), 18);
			DrawHorizontalLine(make_pair(44, 10), 18);
			DrawHorizontalLine(make_pair(44, 12), 18);
			DrawHorizontalLine(make_pair(44, 14), 18);

			SetTextColor(Setting::Color::black, Setting::Color::white, false, true);
			gotoXY(50, 7);
			cout << "繼續定義";

			SetTextColor(Setting::Color::white, Setting::Color::black);

			gotoXY(50, 9);
			cout << "重新開始";
			gotoXY(50, 11);
			cout << "回主選單";
			gotoXY(50, 13);
			cout << "儲存棋盤";
			gotoXY(50, 15);
			cout << "離開遊戲";
		}
		else if (block == Setting::Block::SelectPlayer) {
			SetTextColor(Setting::Color::red, Setting::Color::black);
			DrawFrame(make_pair(43, 6), 20, 11);

			gotoXY(47, 9);
			SetTextColor(Setting::Color::white, Setting::Color::black);
			cout << "請選擇先攻顏色";
			gotoXY(49, 13);
			SetTextColor(Setting::Color::black, Setting::Color::white, false, true);
			cout << "黑";
			SetTextColor(Setting::Color::white, Setting::Color::black);
			gotoXY(57, 13);
			cout << "紅";
		}
		else if (block == Setting::Block::Help) {
			SetTextColor(Setting::Color::yellow, Setting::Color::black, true);
			DrawFrame(make_pair(29, 2), 33, 21);
			SetTextColor(Setting::Color::green, Setting::Color::black, true);
			gotoXY(41, 3);
			cout << "快捷鍵清單";


			gotoXY(31, 5);
			SetTextColor(Setting::Color::green, Setting::Color::black, true);
			cout << "Esc";
			SetTextColor(Setting::Color::white, Setting::Color::black, true);
			cout << "：開啟主選單/返回上一步";

			gotoXY(31, 7);
			SetTextColor(Setting::Color::purple, Setting::Color::black, true);
			cout << "h";
			SetTextColor(Setting::Color::white, Setting::Color::black, true);
			cout << "：呼叫/關閉幫助清單";
			gotoXY(31, 9);
			SetTextColor(Setting::Color::green, Setting::Color::black, true);
			cout << "Enter";
			SetTextColor(Setting::Color::white, Setting::Color::black, true);
			cout << "：選取/放置棋子";
			gotoXY(31, 11);
			SetTextColor(Setting::Color::purple, Setting::Color::black, true);
			cout << "s";
			SetTextColor(Setting::Color::white, Setting::Color::black, true);
			cout << "：儲存遊戲";

			SetTextColor(Setting::Color::white, Setting::Color::black, true);
			gotoXY(33, 14);
			cout << "↑";
			gotoXY(31, 15);
			cout << "←  → 方向鍵控制游標";
			gotoXY(33, 16);
			cout << "↓";

			gotoXY(31, 21);
			cout << "                       翻頁→";
		}
		else if (block == Setting::Block::Help_2) {
			SetTextColor(Setting::Color::yellow, Setting::Color::black, true);
			DrawFrame(make_pair(29, 2), 33, 21);
			SetTextColor(Setting::Color::green, Setting::Color::black, true);
			gotoXY(41, 3);
			cout << "自定義規則";

			SetTextColor(Setting::Color::white, Setting::Color::black, true);
			gotoXY(31, 5);
			cout << "一、將帥至少各一";
			gotoXY(31, 7);
			cout << "二、將（帥）士（仕）不可超出";
			gotoXY(31, 8);
			cout << "    各自的九宮格";
			gotoXY(31, 10);
			cout << "三、象（相）不可過河";
			gotoXY(31, 12);
			cout << "其餘棋數、位置等沒有硬性規定";


			gotoXY(31, 15);
			cout << "從右方選單選取愈放置的棋子";
			gotoXY(31, 17);
			cout << "再到中間棋盤放置（可連續放置）";
			gotoXY(31, 19);
			cout << "放置空白可消除棋子";
			gotoXY(32, 21);
			cout << "                       ←翻頁";
		}
		else if (block == Setting::Block::Warning) {
			SetTextColor(Setting::Color::red, Setting::Color::black, true);
			DrawFrame(make_pair(43, 6), 20, 11);

			SetTextColor(Setting::Color::white, Setting::Color::black);
			gotoXY(46, 10);
			cout << "將帥至少各一!!!";

			gotoXY(45, 15);
			SetTextColor(Setting::Color::gray, Setting::Color::black, true);
			cout << "請按任意鍵繼續..";
			gotoXY(61, 15);

		}
	}
}

//顯示誰被將軍
//參數： bool on：若為false，則表示要關閉顯示；player：誰被將軍
void  UI::showGeneral(bool on, int player)
{
	//被將軍
	if (on) {
		SetTextColor(Setting::Color::black, Setting::Color::red, false, true);
		DrawHorizontalLine(make_pair(66, 9), 28, L' ');
		DrawHorizontalLine(make_pair(66, 11), 28, L' ');
		DrawHorizontalLine(make_pair(66, 10), 5, L' ');
		DrawHorizontalLine(make_pair(89, 10), 5, L' ');
		gotoXY(71, 10);

		SetTextColor(Setting::Color::white, Setting::Color::black);
		wcout << L"！  ";
		//紅方
		if (player == 1) {
			SetTextColor(Setting::Color::red, Setting::Color::black, true);
			cout << "紅方";
		}
		//黑方
		else {
			SetTextColor(Setting::Color::white, Setting::Color::black);
			cout << "黑方";
		}
		SetTextColor(Setting::Color::white, Setting::Color::black);
		wcout << L" 被將軍  ！";
	}
	else {
		SetTextColor(Setting::Color::white, Setting::Color::black);
		DrawHorizontalLine(make_pair(66, 9), 28, L' ');
		DrawHorizontalLine(make_pair(66, 10), 28, L' ');
		DrawHorizontalLine(make_pair(66, 11), 28, L' ');
	}
}

//設置狀態板：顯示輪到誰
//參數：player：0為黑方,1為紅方
void UI::showPlayer(int player)
{
	gotoXY(79, 4);
	if (player == 0) {
		SetTextColor(Setting::Color::white, Setting::Color::black);
		cout << "黑色方";
	}
	else {
		SetTextColor(Setting::Color::red, Setting::Color::black, true);
		cout << "紅色方";
	}
}

//設置選擇哪個棋：
//參數：chessNum，若傳入0，則代表清除該行
void UI::showSelectedChess(int chessNum)
{
	if (chessNum < 0 || chessNum >14) {
		cout << "UI::showSelectedChess錯誤：" << chessNum;
	}
	else if (chessNum == 0) {
		SetTextColor(Setting::Color::white, Setting::Color::black);
		gotoXY(72, 7);
		cout << "                ";
	}
	else {
		SetTextColor(Setting::Color::green, Setting::Color::black, true);
		gotoXY(74, 7);
		cout << "您選擇了 ";

		gotoXY(84, 7);
		//紅方
		if (chessNum > 7) {
			SetTextColor(Setting::Color::red, Setting::Color::white, true);
		}
		//黑方
		else {
			SetTextColor(Setting::Color::black, Setting::Color::white);
		}
		wcout << list[chessNum];
	}


}

//畫棋盤
void UI::DrawBoard()
{
	auto board = ChessBoard::Instance->getBoard();
	int LUX = 28;
	int Y = 1;
	typedef struct {
		const char* start;
		const char* end;
		const char* space;
		const char* interval;
	}row;
	row table[5] = { {"╔ ","╗ ","╤ ","══"},
					 {"║─","║ ","┼ ","──"},
					 {"║─", "║ ", "┴─", "──"},
					 {"║─", "║ ", "┬─", "──"},
					 {"╚ ", "╝ ","╧ ","══"} };

	gotoXY(LUX, Y++);
	SetTextColor(Setting::Color::black, Setting::Color::white, false, true);
	cout << "                                    ";
	gotoXY(LUX, Y++);
	SetTextColor(Setting::Color::purple, Setting::Color::white, false, true);
	cout << " １　２　３　４　５　６　７　８　９ " << endl;


	for (int y = 0, symbol = 0; y < 10; y++) {
		gotoXY(LUX, Y++);
		if (y == 9) {
			symbol = 4;
		}
		else if (y == 4) {
			symbol = 2;
		}
		else if (y == 5) {
			symbol = 3;
		}
		else if (y != 0) {
			symbol = 1;
		}

		SetTextColor(Setting::Color::black, Setting::Color::white, false, true);
		cout << " ";
		for (int x = 0; x < 9; x++) {

			if (board[y][x] == 0) {
				SetTextColor(Setting::Color::black, Setting::Color::white, false, true);
				if (x == 0) cout << table[symbol].start;
				else if (x == 8) cout << table[symbol].end;
				else {
					cout << table[symbol].space;
				}
			}
			else {
				if (board[y][x] >= 8) {
					SetTextColor(Setting::Color::red, Setting::Color::white, true);
				}
				else {
					SetTextColor(Setting::Color::black, Setting::Color::white);
				}


				wcout << list[board[y][x]];
			}
			if (x != 8) {
				SetTextColor(Setting::Color::black, Setting::Color::white, false, true);
				cout << table[symbol].interval;
			}

		}
		SetTextColor(Setting::Color::black, Setting::Color::white, false, true);
		cout << " ";
		if (y != 9) {
			gotoXY(LUX, Y++);

			SetTextColor(Setting::Color::black, Setting::Color::white, false, true);
			int column = y;
			cout << " ║   ";
			if (column == 4) {
				cout << "   楚河            漢界     ";
			}
			else {
				for (int i = 0; i < 7; i++) {
					cout << "│";
					if ((column == 0 && i == 2) || (column == 1 && i == 3) || (column == 7 && i == 2) || (column == 8 && i == 3)) {
						cout << " ＼";
					}
					else if ((column == 0 && i == 3) || (column == 1 && i == 2) || (column == 7 && i == 3) || (column == 8 && i == 2)) {
						cout << " ／";
					}
					else {
						cout << "   ";
					}
				}
			}
			cout << "║  " << endl;
		}
	}
	gotoXY(LUX, Y++);
	SetTextColor(Setting::Color::purple, Setting::Color::white, false, true);
	cout << " 九　八　七　六　五　四　三　二　一 " << endl;
	gotoXY(LUX, Y++);
	SetTextColor(Setting::Color::black, Setting::Color::white, false, true);
	cout << "                                    ";
}

//畫一個格子：注意!由於元素為wchar_t，故長(->)每一單位為2bytes，而寬(向下)每一單位為1byte
void UI::DrawFrame(Coordinate Start, int length, int width)
{
	gotoXY(Start);

	//上面的直線
	cout << "╔";
	DrawHorizontalLine(make_pair(Start.first + 1, Start.second), length - 2);
	cout << "╗ ";

	//下面的直線
	gotoXY(Start.first, Start.second + width - 1);
	cout << "╚";
	DrawHorizontalLine(make_pair(Start.first + 1, Start.second + width - 1), length - 2);
	cout << "╝ ";

	//左邊垂直線
	DrawVerticalLine(make_pair(Start.first, Start.second + 1), width - 2);
	//右邊垂直線
	DrawVerticalLine(make_pair(Start.first + length - 1, Start.second + 1), width - 2);

	//暫存現在的顏色
	int colorCode = this->colorCode;

	SetTextColor(Setting::Color::white, Setting::Color::black);
	for (int y = Start.second + 1; y < Start.second + width - 1; y++) {
		DrawHorizontalLine(make_pair(Start.first + 2, y), length - 3, L' ');
	}

	//變回原本的顏色
	SetTextColor(colorCode);
}

//畫一條直線：注意!由於元素為wchar_t，故每長度為2byte(全形)
void UI::DrawHorizontalLine(Coordinate Start, int length, wchar_t element)
{
	gotoXY(Start);
	for (int i = 0; i < length; i++) {
		wcout << element;
	}
}

//畫一條垂直線：注意!由於元素為wchar_t，故每長度為2byte(全形)
void UI::DrawVerticalLine(Coordinate Start, int length, wchar_t element)
{
	for (int i = 0, y = Start.second; i < length; i++, y++) {
		gotoXY(Start.first, y);
		wcout << element;
		cout << " ";
	}
}

//顯示戰況
//注意：傳入的index表第幾個(由0開始)
void UI::showLog(int index, wstring & output)
{
	SetTextColor(Setting::Color::white, Setting::Color::black);

	gotoXY(6 - (output.size() - 11), 3 + (index % 17));

	for (int i = 0; i < 2 + (output.size() - 11); i++) {
		wcout << output[i];
	}
	;
	if (output[2 + (output.size() - 11)] == L'紅') {
		SetTextColor(Setting::Color::red, Setting::Color::black, true);
	}
	wcout << output[2 + (output.size() - 11)];

	SetTextColor(Setting::Color::white, Setting::Color::black);
	for (int i = 3 + (output.size() - 11); i < output.size(); i++) {
		wcout << output[i];
	}

}

//清除歷史戰況
void UI::clearLog()
{
	SetTextColor(Setting::Color::white, Setting::Color::black);
	for (int y = 2; y < 21; y++) {
		DrawHorizontalLine(make_pair(4, y), 21, L' ');
	}
}

//顯示現在Log在第幾頁
void UI::showLogPage(int now, int sum)
{
	SetTextColor(Setting::Color::green, Setting::Color::black, true);

	gotoXY(10, 22);
	wcout << now;

	SetTextColor(Setting::Color::purple, Setting::Color::black, true);

	gotoXY(18, 22);
	wcout << sum;
}

//顯示開頭的CHESS BOARD大字
void UI::ShowstartingScreen()
{
	SetTextColor(Setting::Color::purple, Setting::Color::black, true);
	gotoXY(8, 3);
	cout << " _____        _    _       _____       _   _       ______        _____       ______";
	gotoXY(8, 4);
	cout << "/ ____|      | |  | |     |_   _|     | \\ | |     |  ____|      / ____|     |  ____|";
	gotoXY(8, 5);
	cout << "| |          | |__| |       | |       |  \\| |     | |____      | (___       | |____";
	gotoXY(8, 6);
	cout << "| |          |  __  |       | |       | . ` |     |  ____|      \\___ \\      |  ____|";
	gotoXY(8, 7);
	cout << "| |___       | |  | |      _| |_      | |\\  |     | |____       ____) |     | |____";
	gotoXY(8, 8);
	cout << "\\_____|      |_|  |_|     |_____|     |_| \\_|     |______|     |_____/      |______|";

	SetTextColor(Setting::Color::green, Setting::Color::black, true);
	gotoXY(4, 14);
	cout << " _____       _    _       ______                                 _____         _____";
	gotoXY(4, 15);
	cout << "/ ____|     | |  | |     |  ____|                               / ____|       / ____|";
	gotoXY(4, 16);
	cout << "| |         | |__| |     | |____                               | (___        | (___";
	gotoXY(4, 17);
	cout << "| |         |  __  |     |  ____|                               \\___ \\        \\___ \\";
	gotoXY(4, 18);
	cout << "| |___      | |  | |     | |____                                ____) |       ____) |";
	gotoXY(4, 19);
	cout << "\\_____|     |_|  |_|     |______|                              |_____/       |_____/";

}

//在狀況顯示的地方加入一些字
void UI::showAdditionText(wstring text)
{
	SetTextColor(Setting::Color::purple, Setting::Color::black, true);
	gotoXY(72, 7);
	wcout << text;
}


//輸出讀入檔案選項
void UI::showSaveData(vector<string>TXTFiles, int nowDataPage)
{
	if (TXTFiles.empty()) {
		SetTextColor(Setting::Color::white, Setting::Color::black, true);
		gotoXY(44, 15);
		cout << "你沒有任何存檔";
		SetTextColor(Setting::Color::gray, Setting::Color::black);
		gotoXY(41, 22);
		cout << "←第 0 頁/共 0 頁→";
		gotoXY(41, 15);
	}
	else {
		SetTextColor(Setting::Color::white, Setting::Color::black);
		SetConsoleTextAttribute(handle, colorCode);

		SetTextColor(Setting::Color::black, Setting::Color::white, false, true);
		DrawHorizontalLine(make_pair(41, 15), 20, L' ');
		gotoXY(41, 15);
		cout << TXTFiles[(nowDataPage - 1) * 3];

		SetTextColor(Setting::Color::white, Setting::Color::black, true);
		if ((nowDataPage - 1) * 3 + 1 < TXTFiles.size()) {
			gotoXY(41, 17);
			cout << TXTFiles[(nowDataPage - 1) * 3 + 1];
		}
		if ((nowDataPage - 1) * 3 + 2 < TXTFiles.size()) {
			gotoXY(41, 19);
			cout << TXTFiles[(nowDataPage - 1) * 3 + 2];
		}

		SetTextColor(Setting::Color::gray, Setting::Color::black);
		gotoXY(41, 22);
		cout << "←第   頁/共   頁→";
		showDataPage(nowDataPage, (TXTFiles.size() + 2) / 3);
		gotoXY(41, 15);
	}
}
void UI::clearData()
{
	SetTextColor(Setting::Color::white, Setting::Color::black);
	for (int y = 15; y < 20; y += 2) {
		DrawHorizontalLine(make_pair(41, y), 20, ' ');
	}
}
void UI::showDataPage(int now, int sum)
{
	SetTextColor(Setting::Color::green, Setting::Color::black, true);

	gotoXY(46, 22);
	wcout << now;

	SetTextColor(Setting::Color::purple, Setting::Color::black, true);

	gotoXY(54, 22);
	wcout << sum;
}
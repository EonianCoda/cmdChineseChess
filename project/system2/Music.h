#pragma once
#include<Windows.h>
#include<mmsystem.h>
#include<map>
using std::map;
using std::make_pair;


namespace Music {
	enum MusicMode {
		quiet, //靜音
		normal, //正常
		noise, //吵雜
		special
	};
	
	enum Sound {
		Victory, //勝利音效
		Chess, //下棋的聲音
		Select, //選棋的聲音
		General, //將軍的音效
		Chess_Gun, //砲移動的音效
		Chess_Elephant,
		Chess_horse,
		Chess_soldier,
		Chess_Car,
		Chess_King,
		Chess_People, //士
		CannotRegret, //沒有甚麼好後悔的
		Dead, //帥或將死亡
		Error, //錯誤
		MoveCursor, //移動選項
	};

	extern map<Sound, const wchar_t*> list;
}

void playMusic(Music::MusicMode mode,Music::Sound file);
void playChessSound(Music::MusicMode mode, int chessNum = 0);
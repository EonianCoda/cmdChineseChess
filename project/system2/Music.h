#pragma once
#include<Windows.h>
#include<mmsystem.h>
#include<map>
using std::map;
using std::make_pair;


namespace Music {
	enum MusicMode {
		quiet, //�R��
		normal, //���`
		noise, //�n��
		special
	};
	
	enum Sound {
		Victory, //�ӧQ����
		Chess, //�U�Ѫ��n��
		Select, //��Ѫ��n��
		General, //�N�x������
		Chess_Gun, //�����ʪ�����
		Chess_Elephant,
		Chess_horse,
		Chess_soldier,
		Chess_Car,
		Chess_King,
		Chess_People, //�h
		CannotRegret, //�S���ƻ�n�ᮬ��
		Dead, //�өαN���`
		Error, //���~
		MoveCursor, //���ʿﶵ
	};

	extern map<Sound, const wchar_t*> list;
}

void playMusic(Music::MusicMode mode,Music::Sound file);
void playChessSound(Music::MusicMode mode, int chessNum = 0);
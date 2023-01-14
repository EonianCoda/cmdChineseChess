#include"Music.h"

namespace {

}
map<Music::Sound, const wchar_t*> Music::list = {
	   {Music::Sound::Victory, L"Sound\\Victory.wav"},
	   { Music::Sound::Chess,L"Sound\\Chess.wav" },
	   { Music::Sound::Select,L"Sound\\Select.wav" },
	   { Music::Sound::General,L"Sound\\General.wav" },
	   { Music::Sound::Chess_Gun,L"Sound\\Chess_Gun.wav" },
	{Music::Sound::Chess_Elephant,L"Sound\\Chess_Elephant.wav" },
	 {Music::Sound::Chess_horse,L"Sound\\Chess_horse.wav" },
	 {Music::Sound::Chess_soldier,L"Sound\\Chess_soldier.wav" },
	{Music::Sound::Chess_Car,L"Sound\\Chess_Car2.wav" },
	{Music::Sound::Dead,L"Sound\\Dead.wav" },
	{Music::Sound::Chess_King,L"Sound\\Chess_king.wav" },
	{Music::Sound::Chess_People,L"Sound\\Chess_people.wav" },
	{Music::Sound::CannotRegret,L"Sound\\CannotRegret.wav" },
	{Music::Sound::Error,L"Sound\\Error.wav" },
	{Music::Sound::MoveCursor,L"Sound\\MoveCursor.wav" },
};

//播放音樂
void playMusic(Music::MusicMode mode, Music::Sound file)
{
	if (mode == Music::MusicMode::quiet)
	{
		return;
	}
	else if (file == Music::Dead && mode != Music::MusicMode::noise)
	{
		return;
	}
	else
	{
		PlaySound(Music::list[file], NULL, SND_FILENAME | SND_ASYNC);
	}

}

void playChessSound(Music::MusicMode mode, int chessNum)
{
	if (mode == Music::MusicMode::normal)
	{
		playMusic(mode,Music::Sound::Chess);
		return;
	}
	else if (mode == Music::MusicMode::noise)
	{
		switch (chessNum)
		{
			//砲
		case 6:
		case 13:
			playMusic(mode,Music::Sound::Chess_Gun);
			break;
			//馬
		case 5:
		case 12:
			playMusic(mode,Music::Sound::Chess_horse);
			break;
			//象
		case 3:
		case 10:
			playMusic(mode,Music::Sound::Chess_Elephant);
			break;
			//車
		case 4:
		case 11:
			playMusic(mode,Music::Sound::Chess_Car);
			break;
			//兵
		case 7:
		case 14:
			playMusic(mode,Music::Sound::Chess_soldier);
			break;
		case 1:
		case 8:
			playMusic(mode,Music::Sound::Chess_King);
			break;
		case 2:
		case 9:
			playMusic(mode,Music::Sound::Chess_People);
			break;

		default:
			playMusic(mode,Music::Sound::Chess);
			break;
		}
	}

}
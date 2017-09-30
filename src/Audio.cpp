#include "Audio.h"

Audio Audio::audio_;

Audio::Audio()
{
	if (!BASS_Init(-1, 22050, BASS_DEVICE_3D, 0, nullptr)) {
		printf_s("init Bass fault!");
	};
    //��ɫ�⣬δ���
}


Audio::~Audio()
{
    for (auto& i : music_)
    {
        BASS_StreamFree(i);
    }
    for (auto& i : asound_)
    {
        BASS_SampleFree(i);
    }
    for (auto& i : esound_)
    {
        BASS_SampleFree(i);
    }
    BASS_Free();
}

//δ���
void Audio::init()
{
    auto flag = BASS_SAMPLE_3D | BASS_SAMPLE_MONO;
	char music_path[50];
	char asound_path[50];
	char esound_path[50];
    for (int i = 0; i < 100; i++)
    {
		sprintf_s(music_path, "%s%d%s", "../game/music/", i, ".mp3");
		sprintf_s(asound_path, "%s%02d%s", "../game/sound/atk", i, ".wav");
		sprintf_s(esound_path, "%s%02d%s", "../game/sound/e", i, ".wav");
        auto m = BASS_StreamCreateFile(false, music_path, 0, 0, flag);
//		int error_t = BASS_ErrorGetCode();
        music_.push_back(m);
        auto a = BASS_StreamCreateFile(false, asound_path, 0, 0, flag);
        asound_.push_back(a);
        auto e = BASS_StreamCreateFile(false, esound_path, 0, 0, flag);
        esound_.push_back(e);
    }
}

void Audio::playMusic(int num)
{
	BASS_ChannelStop(current_music_);
	BASS_ChannelPlay(music_[num], true);
	current_music_ = music_[num];
}

void Audio::playASound(int num)
{
	BASS_ChannelStop(current_sound_);
	BASS_ChannelPlay(asound_[num], true);
	current_sound_ = asound_[num];
}

void Audio::playESound(int num)
{
	BASS_ChannelStop(current_sound_);
	BASS_ChannelPlay(esound_[num], true);
	current_sound_ = esound_[num];
}

void Audio::PauseMusic()
{
	BASS_ChannelPause(current_music_);
}

void Audio::ContinueMusic()
{
	BASS_ChannelPlay(current_music_,false);
}

void Audio::StopMusic()
{
	BASS_ChannelStop(current_music_);
}



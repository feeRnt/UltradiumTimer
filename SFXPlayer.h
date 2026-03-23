/*#ifndef SFXPLAYER_H
#define SFXPLAYER_H*/

#include <QMediaPlayer>
#include <QAudioOutput>

/*
class SFXPlayer : public QMediaPlayer
{

public:*/

/* QMediaPlayer sfxPlayer;
 * QAudioOutput sfxOutput; */

/*
}
#endif // SFXPLAYER_H
*/

// It's probably best to have two different instances running since there might be race
// conditions otherwise with concurrent EyeTimer and TimerManager

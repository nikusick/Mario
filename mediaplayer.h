#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include <QMediaPlayer>
#include <QAudioOutput>
#include <QSoundEffect>

class MediaPlayer
{
public:
    MediaPlayer() {
        _jump = new QSoundEffect;
        _coin = new QSoundEffect;
        _death = new QSoundEffect;

        _player = new QMediaPlayer;
        _audioOutput = new QAudioOutput;

        _jump->setSource(QUrl("qrc:/audio/audio/audio_jump.wav"));
        _coin->setSource(QUrl("qrc:/audio/audio/audio_coin.wav"));
        _death->setSource(QUrl("qrc:/audio/audio/audio_death.wav"));

        _jump->setLoopCount(0);
        _coin->setLoopCount(0);
        _death->setLoopCount(0);

        _jump->setVolume(.25f);
        _coin->setVolume(.25f);
        _death->setVolume(.25f);

        _player->setAudioOutput(_audioOutput);
        _player->setSource(QUrl("qrc:/audio/audio/intro.mp3"));
        _audioOutput->setVolume(50);
        _player->play();
    };

    ~MediaPlayer() {
        delete _jump;
        delete _coin;
        delete _death;
        delete _player;
        delete _audioOutput;
    }
    void startGame() {
        if (!isMuted) {
            _player->stop();
            _player->setSource(QUrl("qrc:/audio/audio/main_theme.mp3"));
            _player->play();
        }
    }
    void endGame() {
        if (!isMuted) {
            _player->stop();
            _player->setSource(QUrl("qrc:/audio/audio/intro.mp3"));
            _player->play();
        }
    }
    void jump() {
        if (!isMuted) {
            _jump->play();
        }
    }
    void coin() {
        if (!isMuted) {
            _coin->play();
        }
    }
    void death() {
        if (!isMuted) {
            _death->play();
        }
    }
    void setMute(bool i) {
        isMuted = i;
        if (!isMuted) {
            _player->stop();
        }
        else {
            _player->play();
        }
    }
private:
    bool isMuted = false;

    QSoundEffect* _jump;
    QSoundEffect* _coin;
    QSoundEffect* _death;

    QMediaPlayer* _player;
    QAudioOutput* _audioOutput;
};

#endif // MEDIAPLAYER_H

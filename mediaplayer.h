#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QAudioOutput>
#include <QSoundEffect>

class MediaPlayer
{
public:
    MediaPlayer() {
        _player = new QMediaPlayer;
        _effects = new QMediaPlayer;
        _audioOutput = new QAudioOutput;
        _audioEffectsOutput = new QAudioOutput;

        _player->setAudioOutput(_audioOutput);
        _effects->setAudioOutput(_audioEffectsOutput);
        _player->setSource(QUrl("qrc:/audio/audio/intro.mp3"));
        _audioOutput->setVolume(50);
        _player->play();
    };

    ~MediaPlayer() {
        delete _effects;
        delete _player;
        delete _audioOutput;
        delete _audioEffectsOutput;
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
            _effects->setSource(QUrl("qrc:/audio/audio/audio_jump.wav"));
            _effects->play();

        }
    }
    void coin() {
        if (!isMuted) {
            _effects->setSource(QUrl("qrc:/audio/audio/audio_coin.wav"));
            _effects->play();
        }
    }
    void setMute(bool i) {
        isMuted = i;
        if (!isMuted) {
            _player->play();
        }
        else {
            _player->pause();
        }
    }
private:
    bool isMuted = false;

    QMediaPlayer* _player;
    QMediaPlayer* _effects;
    QAudioOutput* _audioOutput;
    QAudioOutput* _audioEffectsOutput;
};

#endif // MEDIAPLAYER_H

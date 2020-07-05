#ifndef AUDIODIALOG_H
#define AUDIODIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QHBoxLayout>
#include <QAudioInput>
#include <QAudioOutput>
#include <QBuffer>

class AudioDialog : public QDialog
{
    Q_OBJECT

public:
    AudioDialog(QWidget *parent = 0);
    ~AudioDialog();


    QPushButton * m_startBtn;
    QPushButton * m_endBtn;
    QPushButton * m_playBtn;


    QAudioInput* m_audioInput;
    QAudioOutput* m_audiOutput;

    QBuffer bufDevice;
    QByteArray voiceData;


protected slots:
    void finishedPlaying(QAudio::State);

};

#endif // AUDIODIALOG_H

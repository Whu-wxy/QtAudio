#include "audiodialog.h"

AudioDialog::AudioDialog(QWidget *parent)
    : QDialog(parent)
{
    m_startBtn = new QPushButton("开始录音",this);
    m_endBtn = new QPushButton("结束录音",this);
    m_playBtn = new QPushButton("播放",this);
    QHBoxLayout *hBoxLayout = new QHBoxLayout(this);
    hBoxLayout->addWidget(m_startBtn);
    hBoxLayout->addWidget(m_endBtn);
    hBoxLayout->addWidget(m_playBtn);


    QAudioFormat format;

    format.setSampleRate(48000);
    format.setChannelCount(2);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);
    QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
    if (!info.isFormatSupported(format))
    {
        format = info.nearestFormat(format);
    }

    m_audioInput = new QAudioInput(info, format, this);
    m_audiOutput = new QAudioOutput(info, format, this);
    bufDevice.setBuffer(&voiceData);

    bufDevice.open(QIODevice::WriteOnly | QIODevice::Truncate);

    connect(m_startBtn,&QPushButton::clicked,[&]()->void{
                bufDevice.open(QIODevice::WriteOnly | QIODevice::Truncate);
                m_audioInput->start(&bufDevice);});

    connect(m_endBtn,&QPushButton::clicked,[&]()->void{
                m_audioInput->stop();
                bufDevice.close();} );

    connect(m_audiOutput,SIGNAL(stateChanged(QAudio::State)),SLOT(finishedPlaying(QAudio::State)));
    connect(m_playBtn,&QPushButton::clicked,[&]()->void{
                bufDevice.open(QIODevice::ReadOnly);
                m_audiOutput->start(&bufDevice);});
}

AudioDialog::~AudioDialog()
{
    m_audioInput->stop();
    bufDevice.close();
}


void AudioDialog::finishedPlaying(QAudio::State state)
 {
   if(state == QAudio::IdleState) {
     m_audiOutput->stop();
     bufDevice.close();
   }
 }

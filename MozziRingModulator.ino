//AudioInputの設定
#include <MozziConfigValues.h>
#define MOZZI_AUDIO_INPUT MOZZI_AUDIO_INPUT_STANDARD
#define MOZZI_AUDIO_INPUT_PIN 0

//必要なファイルをインクルード
#include <Mozzi.h>
#include <Oscil.h>
#include <tables/sin2048_int8.h> //正弦波
#include <tables/square_no_alias_2048_int8.h> //矩形波

#define OSCIL_NUM_CELLS 2048


Oscil <OSCIL_NUM_CELLS, MOZZI_AUDIO_RATE> osc; //モジュレータ
Oscil <OSCIL_NUM_CELLS, MOZZI_AUDIO_RATE> lfo; //モジュレータを周波数変調させるLFO

bool wave; //モジュレータの波形(0なら正弦波、1なら矩形波)
UFix<0,8> modulatorModDepth; //モジュレータの周波数変調のDepth(0-1)
byte mix; //キャリア原音とリングモジュレータを通した音とのMIX

void setup() {

  //モジュレータの初期設定
  wave = digitalRead(2);
  if(wave){
    osc.setTable(SIN2048_DATA);
  }else{
    osc.setTable(SQUARE_NO_ALIAS_2048_DATA);
  }

  //LFOの初期設定
  lfo.setTable(SIN2048_DATA);

  startMozzi();
  //Serial.begin(9600); //デバッグ用
}

//各変数に関わる処理
void updateControl(){

  //モジュレータの周波数の設定
  int modulatorFreq;

  bool freqHL = digitalRead(3);
  if(freqHL){
    modulatorFreq = map(mozziAnalogRead(2),0,1023,1,1000);
  }else{
    modulatorFreq = map(mozziAnalogRead(2),0,1023,1000,4000);
  }

  osc.setFreq(modulatorFreq);

  //モジュレータの波形の設定
  bool waveForm = digitalRead(2);
  if(waveForm!=wave){
    if(waveForm){
      osc.setTable(SIN2048_DATA);
    }else{
      osc.setTable(SQUARE_NO_ALIAS_2048_DATA);
    }
    wave = waveForm;
  }

  //モジュレータの周波数変調の設定
  float modulatorModRate = map(mozziAnalogRead(4),0,1023,0,250) / 10.00;
  lfo.setFreq(modulatorModRate);

  modulatorModDepth = map(mozziAnalogRead(3),0,1023,0,8) / 10.00;

  //キャリア原音とのMIXの設定
  int mix_before = map(mozziAnalogRead(1),0,1023,0,127);
  if(mix_before < 0){
    mix = 0;
  }else if(mix_before > 127){
    mix = 127;
  }else{
    mix = mix_before;
  }

}

//音声信号に関わる処理
AudioOutput updateAudio(){

  //モジュレータの信号処理
  auto vibrato = modulatorModDepth * toSFraction(lfo.next());
  int8_t mod = osc.phMod(vibrato)*mix>>8; //モジュレータの周波数変調
  auto coeff = UFix<8,0>(128+mod);

  //キャリアの信号処理
  int8_t carrier = (getAudioInput()-512)>>2; //-512~511→-128~127

  //出力音声の信号処理
  return MonoOutput::fromSFix(coeff*toSFraction(carrier)); //fromSFix()の括弧内でキャリアとモジュレータを乗算
}

void loop() {
  audioHook();
}


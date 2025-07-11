# MozziRingModulator
Arduino, Mozziライブラリを用いて作成したリングモジュレータ(エフェクタ)

## 使用技術
Arduino, 回路

## 制作時期
2025年夏

## 概要
Arduinoで作るリングモジュレータ

## 使用例
以下のリンクからご覧いただけます。
→https://drive.google.com/file/d/11DZitelYskoXJ6-sfnhDtl5odZjtNiXv/view?usp=sharing

## 特徴
1. Moogのリングモジュレータ「MF-102」をマイコンで再現
2. モジュレータに正弦波と矩形派を搭載、LFOでモジュレータの周波数変調が可能
3. 原音(キャリア)とリングモジュレータを通した音のMIX機能を搭載

## 機構
MozziRingModulator.pdfを参照
1. A0ピン：AudioInput(キャリアの信号)
2. A1ピン：原音とリングモジュレータを通した音のMIX
3. A2ピン：モジュレータの周波数
4. A3ピン：モジュレータの周波数変調のDepth
5. A4ピン：モジュレータの周波数変調のRate
6. D2ピン：モジュレータの波形選択(正弦波・矩形波)
7. D3ピン：モジュレータの周波数の変更範囲の選択(HIは1-1000Hz,LOは1000-4000Hz)
8. D9ピン：AudioOutput

## 参照
1. Mozzi Documentation: https://sensorium.github.io/Mozzi/doc/html/
2. Mozzi Examples: https://sensorium.github.io/Mozzi/examples/
3. FixMath https://github.com/tomcombriat/FixMath
4. MF-102 Manual: https://www.korg-kid.com/moog/pdf/MF-102_Manual_J.pdf

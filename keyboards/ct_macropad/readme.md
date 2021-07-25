# ct_macropad

<img width="700" alt="ct_macropad overview" src="https://github.com/3araht/qmk_firmware/tree/add_ct_macropad/keyboards/ct_macropad/pictures/ct_macropad.jpeg">

This macropad keyboard was made as a prototype of chromatonemini, in order to check the layout of the glissando keys on top of the chromatone keyboard.  
Since it was just boring to make one board as a prototype, the board was considered to be used as a macropad.

* Keyboard Maintainer: [3araht](https://github.com/3araht)
* Hardware Supported: ct_macropad keyboard.

## 必要なもの：　

||個数|備考|
|----|----|------|
|[Pro Micro](https://shop.yushakobo.jp/products/promicro-spring-pinheader)|x1||
|USB ケーブル|x1|Pro Micro のコネクタ形状にあったものを。また、充電専用ケーブルでは通信ができませんので、使用しないようにご注意ください。|
|キースイッチ|x7|Cherry MX系|
|キーキャップ|x7|Cherry MX系|
|[タクトスイッチ](https://akizukidenshi.com/catalog/g/gP-09824/)|x5|グリッサンド用|
|[リセットスイッチ](https://shop.yushakobo.jp/products/a1600ed-01-1?_pos=2&_sid=c2c6ab923&_ss=r)|x1|Pro Micro にリセットをかけるとき用|
|M2スペーサー|x6|背面のPro Micro の分浮かせるために使用します。8（参考）Pro Micro のコンスルーが 2.5 mm タイプの場合、5.5 mm 以上の高さのものを使っています。|
|M2ネジ|x6|スペーサー固定用|
|LED|x7|(任意) キースイッチのバックライトを使用したい場合。この基板では、SK6812mini か SK6812mini-E が任意の配合で使用可能になっています。|

※ このキーボードではキースイッチ部分にダイオードは不要です。  

## 手順
- スペーサーを基板に固定
- Pro Micro にコンスルーを半田付け
- Pro Micro にファームウェアを書き込み
- この基板を 12キーのマクロパッドとして使う場合は "macropad" のジャンパー 5つをショート。この基板を 7キーのクロマトーンとして使う場合は "default" のジャンパー 5つをショート。"macropad" か ”default" どちらか一方のみをショートします
- (LEDをつける場合) LED 信号線をジャンパーショート
- (LEDをつける場合) LEDの半田付け
- タクトスイッチの半田付け
- キースイッチの半田付け
- キーキャップ嵌め込み
- (任意) REMAP でキーレイアウトのカスタマイズ（この場合、viaに対応したファームウェアをお使いください）。

以上で完成です！！！  

## ファームウェアの違い
基本的に、一番汎用性の高い [ct_macropad_via_macropad.hex](https://github.com/3araht/qmk_firmware/tree/add_ct_macropad/keyboards/ct_macropad/ct_macropad_via_macropad_hex.zip) をお使いください。  

|ファームウェア|説明|
|----|----|
|ct_macropad_default.hex|キー数は7つ、chromatone のプロトタイプとして使ったときのファームウェア。"default" のジャンパー 5つをショートして使います。|
|ct_macropad_macropad.hex|キー数は12こ、グリッサンド用のキーを独立して認識します。12キーのマクロパッドとして使うためのファームウェア。"macropad" のジャンパー 5つをショートして使います。|
|ct_macropad_via.hex|キー数は7つ、chromatone のプロトタイプとして使ったときのファームウェア。"default" のジャンパー 5つをショートして使います。via に対応。[REMAP](https://remap-keys.app/) でキーレイアウト変更が可能。|
|ct_macropad_via_macropad.hex|キー数は12こ、グリッサンド用のキーを独立して認識します。12キーのマクロパッドとして使うためのファームウェア。"macropad" のジャンパー 5つをショートして使います。via に対応。[REMAP](https://remap-keys.app/) でキーレイアウト変更が可能。|


Make example for this keyboard (after setting up your build environment):

    make ct_macropad:default

Flashing example for this keyboard:

    make ct_macropad:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## 1日目
### 開発環境のセットアップ
 - macOS用の開発環境の準備
 - sandaiさんがmacOS用の開発環境をGitHubに公開されているのでこれをベースに作成
   - git cloneしたレポジトリのbin/install.shを環境に合わせて改変する。
   - Q.appは使わないのでMakefileとinstall.shをそれに併せて修正

```sh
$ git clone https://github.com/sandai/30nichideosjisaku 
$ cd 30nichideosjisaku/bin
$ sh install.sh
```

 - 必要なツールをhomebrewでインストール
```sh
$ brew cask install 0xED
$ brew install qemu
```
### helloos0の作成
 - バイナリエディタの0xEDでべた書きする
  - bzと違い垂直方向の番地が異なるので合わせる
```sh
 $ make run
```

### helloos1の作成
- さすがにDBで書くのは面倒だったので、サポートディスクのデータをコピーして実行

### helloos2の作成
- hellos2のバージョンは、まともな記述になっているのでこれは実際に写経した。



## 2日目
### テキストエディタの紹介
 - テラパッドが紹介されているが、VS Codeを利用しているのでスキップ。

### さて開発再開
- 1日目で作成したhelloos3の`helloos.nas`をもう少しアセンブリっぽく書き直す。

- アセンブリの命令である、`MOV`,`JMP`, `JE`, `CMP`等の説明。アセンブリ命令については省略する。

- 8bit, 16bit, 32bitレジスタの紹介
  - レジスタは基本的にどれを利用しても同じように計算が可能だが、用途に合わせてレジスタを選択すると効率のよい記述ができる。

**16bitレジスタ**
|レジスタ|名称|
|:----|:----|
|AX|Accumlator|
|CX|Counter|
|DX|Data|
|BX|Base|
|SP|StackPointer|
|BP|BasePointer|
|SI|SourceIndex|
|DI|DestinationIndex|

**8bitレジスタ**
|レジスタ|名称||
|:----|:----|:----|
|AL|AccumlatorLow|AXの下位8bit|
|CL|CounterLow|CXの下位8bit|
|DL|DataLow|DXの下位8bit|
|AH|AccumlatorHigh|AXの上位8bit|
|CH|CounterHigh|CXの上位8bit|
|DH|DataHigh|DXの上位98it|

**32bitレジスタ**
- EAX, ECX, EDX, EBX, ESP, EBP, ESI, EDI
- 32ビットレジスタはたとえばEAXは下位16bitがAXそのもの。ほかも同様
- 上下に分割できるが、上位16bitにはレジスタ番号がないためそのままでは利用できない。

### ブートセクタが作れるように整理
- helloos3の内容をコピーし、ブートセクタ以外の部分のところを削除して、ブートセクタのみ作成するように`helloos.nas`を修正する
- ついでに`Makefile`も修正


### 今後のためのMakefile導入
- Makefileを拡充して`helloos5`を作成

## 3日目
### さぁ本当のIPLを作ろう
- harib00a
- ブートローダーの構築 

新出命令 __JC__ キャリーフラグが1である時にジャンプする。
- [OSDEV](http://oswiki.osask.jp/)
- フロッピーディスクの構造の説明

### エラーになったらやり直そう
- harib00b
- habi00aにリトライ処理を追加

### 18セクタまで読んでみる
- harib00c
- habi00bに18セクター先までの読み込み処理を追加

### 10シリンダ分読み込み
- harib00d
- habi00cに10シリンダー分の読み込み処理を追加

### OS本体の書き込み
- harib00e
- habi00dからOSとなる部分を新規に作成し、haribote.imgのディスクイメージに保存する

### ブートセクタからOS本体を起動させてみる
- harib00f
- habi00eを修正し、ipl.nasの最後の処理に0xc200番地へジャンプする処理を追加
  - ディスクイメージの開始アドレスが0x004200でブートセクターの先頭アドレスが0x8000のため0x4200+0x8000=0xc200 であるので

### OS本体の動作を確認してみる

- harib00g

- harib00eで作成したOSイメージに対して、画面モードの切り替えを実装

- ビデオモード設定は以下の通り

  - AH=0x00

  - AL=モード

    - 0x13　VGAグラフィックス 320x200x8bitカラー　バックドピクセル

- 画面が真っ黒になったのでOK

### 32ビットモードへの準備 

- harib00h

- ブート関連の情報として以下の情報を定数に追加（後々使うっぽい）

  - 色数
  - 横方向の解像度
  - 縦方向の解像度
  - グラフィックバッファの開始位置

- キーボードのLED情報を取得する

  

### ついにC言語導入へ

- haribo00i

- この章の山場だと思う

- `bootpack.c`を新規作成しOSのエントリポイントとする

  - HariMainがエントリとなる（gocc1の仕様？）

- 以下の手順でCのソースからコンパイルする

  - `gocc1`を使って、`bootpack.c`から`bootpack.gas`を生成する
  - `gas2nask`を使って、`bootpack.gas`を`bootpack.nas`に変換する
  - `bootpack.nas`を`nask`でコンパイルし、`bootpack.obj`を生成する
  - `obj2bim`を使って、`bootkpack.obj`から`bootpack.bim`を生成する
  - 最後に`bim2hrb`を使って、`bootpack.bim`から`bootpack.hrb`を生成する
  - 生成した`bootpack.hrb`と`asmhead.bin`をcatコマンドで連結させて `haribote.sys`を作成する

- 上記の手順が踏めるように、`Makefile`をゴリゴリ修正した

- 以前と同じように画面真っ黒になったのでOK

  

### とにかくHLTがしたい

- harib00j
- HLTの関数をアセンブリで記述し、gocc1のコンパイラにリンクするのみ

​      
## 4日目
### C言語からメモリを書き込みたい
- harib01a
- アセンブラーでVRAMの番地に書き込む命令write_mem8を実装する。
  - 実際にはC言語でもポインターを使えば実現できるので実装する必要はないのだが、本に沿って進める。
- 命令セットが486系であることを示すために、`INSTRSET`命令を追加

![](./images/04days/01.png)

#### しましま模様

- ビット論理積演算をつかう

- 実行結果

  ![](./images/04days/02.png)

#### ポインタに挑戦

- harib01bの内容をポインタを使った書き方に書き直す

- これにあわせて、`naskfunc.nas`から`write_mem8`関数を削除

- 実行結果は、harib01bと同じなので割愛

  

#### ポインタの応用（１）

- harib01cの内容をC言語の別の構文で書き換えるだけ
- 実行結果はharib01bと同じなので割愛



#### ポインタの応用（２）

- habi01cの内容をC言語の別の構文で書き換えるだけ
- 実行結果はharib01bと同じなので割愛


#### 色番号設定

- 現在使用している320x200の8bitカラーモードは、8bitしか使用できない。

- この8bitの色番号に対応する色はプログラマで自由に決めてよい

  - 色番号と色を対応づけたものを__パレット__と呼ぶ

- ビデオDAコンバータのカラーパレットへのアクセス手順からカラーパレットの初期化と設定を行う

- 新出命令

  - `CLI`命令は、__Clear Interrupt Flag__で割り込みフラグをリセットする
  - `STI`命令は、__Set Interrupt Flag__で割り込みフラグをセットする
  - `PUSHFD`は、__Push Flag Double-Word__でフラグをDoubleWordでプッシュする
  - `POPHFD`は、__POP Flag Double-Word__でフラグをDoubleWordでポップする

  ![](./images/04days/03.png)

  #### 四角形を描く
  
  - VRAMに矩形を書き込む計算は`OxaOOOO+x+y*320`
  
    - 0xa0000は開始番地で、y軸のサイズだけ異なるが基本的には同じ
  
  - VRAMに矩形を描画する関数`boxfill8`を`bootpack.c`に追加してビルド
  
  - 以下のようになった
  
    ![](./images/04days/04.png)


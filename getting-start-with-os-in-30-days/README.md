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

#### 今日の仕上げ

- boxfillの呼び出しを少し調整し、Windowsのタスクバーっぽい表示に調整

  ![](./images/04days/05.png)

### 5日目 構造体と文字表示とGDT/IDT初期化

#### 起動情報の受け取り

- VRAMの位置情報と、スクリーンサイズをbootinfoから取得するように修正
- 画面は、harib01hと同じのため省略



#### 構造体を使ってみる

- 起動情報の受け取り方を構造体に変更
  - アロー演算子の記法は使わない実装
- 画面は、harib01hと同じのため省略



#### 矢印表記を使ってみる

- 構造体への変数アクセスをアロー演算子に書き換えて実装
- 画面は、harib01hと同じのため省略


#### とにかく文字を出したい
- harib02d
- harib02cで作成した画面表示をinit_screen関数として関数に切り出し
- フォントを表示する関数`putfont8`関数を作成
- 本筋と外れるが、macOS 10.15に更新してしまったので、32bitアプリケーションが動かなくなってしまった。
   - nask, gocc1, edimageが使えなくなった。
   - [『30日でできる！OS自作入門』を macOS Catalina で実行する](https://qiita.com/noanoa07/items/8828c37c2e286522c7ee)を参照して、一般的なアプリケーションを用いて再構築した。
      - brewを使ってnasmとmtools、i386-elf-gccをインストール
      - 上記の記事とツールを提供してくれた人に感謝
```sh
$brew install nasm
$brew install mtools
```

   - 標準のHomebrewの環境では、i386-elf-gccの代わりに、x86_64-elf-gccが提供されているが、これを用いてリンクとコンパイルを実行するとエラーが発生する。

```sh
❯ make
make -r img
make -r haribote.img
x86_64-elf-gcc -march=i486 -m32 -nostdlib -T hrb.ld -g bootpack.c naskfunc.o -o bootpack.hrb
/usr/local/opt/x86_64-elf-binutils/bin/x86_64-elf-ld: i386 architecture of input file `/var/folders/z0/45fcm1sj5ll87b57m00xgb4w0000gn/T//ccYaGdlV.o' is incompatible with i386:x86-64 output
/usr/local/opt/x86_64-elf-binutils/bin/x86_64-elf-ld: i386 architecture of input file `naskfunc.o' is incompatible with i386:x86-64 output
collect2: error: ld returned 1 exit status
make[2]: *** [bootpack.hrb] Error 1
make[1]: *** [img] Error 2
make: *** [default] Error 2
```
  - なので、[StakcOverflowの記事](https://stackoverflow.com/questions/40655204/cant-brew-install-gcci386-elf-gcc)を参考に、brew tapして、i386-elf-gccをインストールする

```sh
$brew tap nativeos/si386-elf-toolchain 
$brew install i386-elf-binutils i386-elf-gcc
```

 - これでビルドすると次の結果が得られる。
 ![](./images/05days/01.png)

#### フォントを増やしたい
- harib02e
- OSASKのサイトからフォント作成のプログラムがWikiに提供されていたので、これをコンパイルして`makefont`を作成
- 作成したmakefontプログラムと`hankaku.txt`からバイナリデータを生成した。
- 生成したバイナリデータは`binutils`に含まれている`objcopy`を使ってobjファイルに変換し、変換したobjファイルをbootpack.cのオブジェクトファイルとリンクすることで、fontデータの埋め込みを行った。
    - binutils/objcopyの使い方は以下の記事を参考にした。
    - [普通のやつらの下を行け: objcopy で実行ファイルにデータを埋め込む](http://0xcc.net/blog/archives/000076.html)
- 実行結果は以下の通り
  ![](./images/05days/02.png)


#### 文字列を表示したい
- harib02f
- harib02eで作成した文字表示の部分をまとめて、文字列を表示する関数`putfont8_asc`を記述するのみ
- 実行結果は、前回と同様のなので省略する

#### 変数の値の表示
- harib02g
- `sprintf`で作成した文字列を、先に作った`putfont8_asc`に渡すだけ・・のはずだが、macOS上で`i386-elf-gcc`を使ってクロスコンパイルしているせいか、リンク時に`crt0.o`がないとエラーメッセージと`-lc`が見つからないエラーが表示される。
  - [このあたり](http://www.ertl.jp/~takayuki/readings/c/no03.html)を参考にすると`crt0.o`自体はmainを呼び出すためのもののよう
  - 同様に`-lc`が見つからないのもlibcがないからと思われる（ビルドしてないし）
  - なので、`crt0.c`を自作してlibcをビルドしてリンクすれば動くと思われるが、必要なのはsprintfだけなので今回は[ここの記事のコード](http://bttb.s1.valueserver.jp/wordpress/blog/2017/12/17/makeos-5-2/)を拝借させいていただいた
  - 今後困ることも考えられるので、また環境を再構築した方がいいかもしれない。
- 実行結果は次の通り

![](images/05days/03.png)
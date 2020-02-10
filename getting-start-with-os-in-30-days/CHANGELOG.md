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
- さすがにDBデ格のは面倒だったので、サポートディスクのデータをコピーして実行

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


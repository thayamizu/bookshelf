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




計算機プログラムの構造と解釈
====

## 環境の準備
- Visual Studio Code / WSL
- vscode-schemeをインストールしておく
- Scheme処理系として､`Gauche`をインストール
    - WSL上にLinuxbrewをインストールしておけば，brewコマンドからインストールできる．

```sh
$brew install gauche
```

## 手続きによる抽象の構築
計算プロセス(computational process)は計算機における抽象的な存在．このプロセスは，進行しながらもう一つの抽象であるデータ(data)を操作する．プロセスの進行は，プログラムの指示に従う．

プロセスに仕事をさせるため，我々はプログラム言語の記号式で注意深く構成する．

### Lispによるプログラム
- Lispは1950年代の終わり頃，再起方程式（recursion equation）という論理表現についての推論の形式化として __Jhon McCarthy__ によって発明された．

#### 1.1 プログラムの要素
プログラム言語について語るとき，単純が概念を統合して複雑な概念を構成する要素に注意する．これには，次の3つの大きなメカニズムがある．

- 基本式・・・言語が関わる最も単純なもの
- 組合わせ法・・・より単純なものから合成物をつくる
- 抽象化法・・・合成物に名をつけ，単一のものとして扱う

#### 1.1.1 式

SchemeのREPLの導入節

式の並びを括弧で囲んで手続きの作用を表現する式を**組み合わせ**という，並びの左端の要素を*演算子*，他の要素を**被演算子**と呼ぶ

演算子の左側に置く記法を**前置記法**と呼ぶ．前置記法ではその自然な拡張として，**入れ子**を許す．

被演算子が，縦に整列するような記法のことを**清書系**と呼ぶ．


#### 1.1.2 名前と環境

プログラム言語の重要な点は，名前を使って計算オブジェクトを指す手段を用意することである．オブジェクトを値とする変数を識別するものが**名前**となる．

LispのScheme方言では，defineを使って名前をつける

```scheme
(define size 2)
```

そのほかのdefineの例

```scheme
(define pi 3.14159)

(define radius 10)

(* pi 
   (* radius radius))
```

演算の結果を指すのにも，単純な名前を使うことが出来るので我々の言語の最も単純な抽象手段である．

解釈系は，名前とオブジェクトの対を保持するために，何らかの形で記憶している．この記憶を**環境**と呼ぶ．

#### 1.1.3 組み合わせの評価


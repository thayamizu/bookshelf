;naskfunc
;

[FORMAT "WCOFF"]    ;オブジェクトファイルを作るためのモード
[INSTRSET "i486p"]
[BITS 32]           ;32ビットモード用の機械語を作らせる

;オブジェクトファイルのための情報
[FILE "naskfunc.nas"]
    GLOBAL  _io_hlt

;　以下は実際の関数
[SECTION .text]
_io_hlt:    ;void io_hlt(void);
    HLT
    RET
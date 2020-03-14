;naskfunc
;

[FORMAT "WCOFF"]    ;オブジェクトファイルを作るためのモード
[INSTRSET "i486p"]
[BITS 32]           ;32ビットモード用の機械語を作らせる

;オブジェクトファイルのための情報
[FILE "naskfunc.nas"]
    GLOBAL  _io_hlt, _write_mem8

;　以下は実際の関数
[SECTION .text]
_io_hlt:    ;void io_hlt(void);
    HLT
    RET

_write_mem8: ;void write_mem8(int addr, int data);
    MOV ECX, [ESP+4]
    MOV AL, [ESP+8]
    MOV [ECX], AL
    RET
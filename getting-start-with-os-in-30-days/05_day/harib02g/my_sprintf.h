#ifndef MY_SPRINTF_H_
#define MY_SPRINTF_H_

//10進数からASCIIコードに変換
extern int dec2asc(char *str, int dec);

//16進数からASCIIコードに変換
extern int hex2asc(char *str, int dec);

//sprintf
extern void my_sprintf(char *str, char *fmt, ...);

#endif
#ifndef MY_SPRINTF_H_
#define MY_SPRINTF_H_

/**
 * 10進数からASCIIコードに変換
 * @param char *str
 * @param int  dec
 * @return int
 */
extern int dec2asc(char *str, int dec);

/**
 * 16進数からASCIIコードに変換
 * @param char *str
 * @param int dec
 * @return int
 */
extern int hex2asc(char *str, int dec);

/**
 * sprintf
 * @param char *str
 * @param char *fmt
 */
extern void my_sprintf(char *str, char *fmt, ...);

#endif
/**
 * ref sprintfを実装する | OS自作入門 5日目-2 【Linux】
 * http://bttb.s1.valueserver.jp/wordpress/blog/2017/12/17/makeos-5-2/
 * 上記の記事からコードを拝借した。
 */
#include <stdarg.h>
#include "sprintf.h"

//10進数からASCIIコードに変換
int dec2asc(char *str, int dec)
{
    int len = 0, len_buf; //桁数
    int buf[10];
    int flag = (dec >= 0) ? 0 : 1;
    int tmp;
    while (1)
    { //10で割れた回数（つまり桁数）をlenに、各桁をbufに格納

        tmp = (dec % 10);
        buf[len++] = tmp >= 0 ? tmp : -tmp;
        if (dec < 10)
            break;
        dec /= 10;
    }

    len_buf = len;
    //負数対応
    if (flag)
    {
        *(str++) = '-';
        len_buf++;
    }
    while (len)
    {
        *(str++) = buf[--len] + 0x30;
    }
    return len_buf;
}

//16進数からASCIIコードに変換
int hex2asc(char *str, int dec)
{                         //10で割れた回数（つまり桁数）をlenに、各桁をbufに格納
    int len = 0, len_buf; //桁数
    int buf[10];
    while (1)
    {
        buf[len++] = dec % 16;
        if (dec < 16)
            break;
        dec /= 16;
    }
    len_buf = len;
    while (len)
    {
        len--;
        *(str++) = (buf[len] < 10) ? (buf[len] + 0x30) : (buf[len] - 9 + 0x60);
    }
    return len_buf;
}

void sprintf(char *str, char *fmt, ...)
{
    va_list list;
    int i, len;
    va_start(list, 2);

    while (*fmt)
    {
        if (*fmt == '%')
        {
            fmt++;
            switch (*fmt)
            {
            case 'd':
                len = dec2asc(str, va_arg(list, int));
                break;
            case 'x':
                len = hex2asc(str, va_arg(list, int));
                break;
            }
            str += len;
            fmt++;
        }
        else
        {
            *(str++) = *(fmt++);
        }
    }
    *str = 0x00; //最後にNULLを追加
    va_end(list);
}
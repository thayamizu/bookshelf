#include "mouse.h"

void init_mouse(MouseDesc *desc)
{
    desc->buf[0] = 0;
    desc->buf[1] = 0;
    desc->buf[2] = 0;
    desc->phase = 0;
    desc->x = 0;
    desc->y = 0;
    desc->btn = 0;
}

void enable_mouse(MouseDesc *desc)
{
    wait_KBC_sendready();
    io_out8(PORT_KEYCMD, KEYCMD_SENDTO_MOUSE);

    wait_KBC_sendready();
    io_out8(PORT_KEYDAT, MOUSECMD_ENABLE);

    init_mouse(desc);

    return;
}

int decode_mouse(MouseDesc *desc, unsigned char data)
{
    if (desc->phase == 0)
    {
        if (data == 0xfa)
        {
            desc->phase = 1;
        }

        return 0;
    }
    if (desc->phase == 1)
    {
        if ((data & 0xc8) == 0x08)
        {
            desc->buf[0] = data;
            desc->phase = 2;
        }
        return 0;
    }
    if (desc->phase == 2)
    {
        desc->buf[1] = data;
        desc->phase = 3;
        return 0;
    }
    else if (desc->phase == 3)
    {
        desc->buf[2] = data;
        desc->phase = 1;
        desc->x = desc->buf[1];
        desc->y = desc->buf[2];
        desc->btn = desc->buf[0] & 0x07;

        if ((desc->buf[0] & 0x10) != 0)
        {
            desc->x |= 0xffffff00;
        }
        if ((desc->buf[0] & 0x20) != 0)
        {
            desc->y |= 0xffffff00;
        }

        desc->y = -desc->y;
        return 1;
    }

    return -1;
}
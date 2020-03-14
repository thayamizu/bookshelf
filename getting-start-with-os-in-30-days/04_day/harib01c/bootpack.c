void io_hlt(void);

void HariMain(void)
{

    int i;
    for (i = 0xa0000; i <= 0xaffff; i++)
    {
        char *address = (char *)i;
        *address = i & 0xff;
    }

    for (;;)
    {
        io_hlt();
    }
}

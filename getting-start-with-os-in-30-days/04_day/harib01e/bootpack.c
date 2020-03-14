void io_hlt(void);
void write_mem8(int address, int data);

void HariMain(void)
{

    int i;
    char *p = (char *)0xa0000;
    for (i = 0; i <= 0xffff; i++)
    {
        p[i] = i & 0xff;
    }

    for (;;)
    {
        io_hlt();
    }
}

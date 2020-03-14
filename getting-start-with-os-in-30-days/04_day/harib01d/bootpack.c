void io_hlt(void);
void write_mem8(int address, int data);

void HariMain(void)
{

    int i;
    for (i = 0xa0000; i <= 0xaffff; i++)
    {
        char *p = 0xa0000;
        *(p + i) = i & 0xff;
    }

    for (;;)
    {
        io_hlt();
    }
}

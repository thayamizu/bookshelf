void io_hlt(void);
void write_mem8(int address, int data);

void HariMain(void)
{

    int i;
    for (i = 0xa0000; i <= 0xaffff; i++)
    {
        write_mem8(i, i & 0xff);
    }

    for (;;)
    {
        io_hlt();
    }
}

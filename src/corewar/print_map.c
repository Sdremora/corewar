#include "corewar.h"

void    print_octet(unsigned char p)
{
    static char base[17] = "0123456789abcdef";

    ft_putchar(base[p / 16 % 16]);
    ft_putchar(base[p % 16]);
}

void    print_mem(unsigned int n)
{
    static char base[17] = "0123456789abcdef";

    ft_putstr("0x0");
    ft_putchar(base[n / 16 / 16 % 16]);
    ft_putchar(base[n / 16 % 16]);
    ft_putchar(base[n % 16]);
    ft_putstr(" ");
}
//wide = 64
void  print_map(unsigned char *map)
{
    int i;

    i = 0;
    while (i < MEM_SIZE)
    {
        if (i % 32 == 0)
            print_mem(i);
        print_octet(map[i]);
        if (i % 32 == 31)
            ft_putchar('\n');
        else
            ft_putchar(' ');
        i++;
    }
}
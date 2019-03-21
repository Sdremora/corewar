#include "corewar.h"

void    print_octet(unsigned char p)
{
    static char base[17] = "0123456789abcdef";

    ft_putchar(base[p / 16 % 16]);
    ft_putchar(base[p % 16]);
}
//wide = 64
void  print_map(unsigned char *map)
{
    int i;

    i = 0;
    while (i < MEM_SIZE)
    {
        print_octet(map[i]);
        if (i % 64 == 63)
            ft_putchar('\n');
        else
            ft_putchar(' ');
        i++;
    }
}
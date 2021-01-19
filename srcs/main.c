#include "ft_printf.h"
#include <string.h>
#include <locale.h>
#include <stdint.h>


int main(int ac, char **av)
{
	int i;
	int j;
	char c = 0;
	void *p = NULL;	
	//printf(av[1], atoi(av[2]), av[3]);
	i = printf(av[1], atoi(av[2]));
	printf("|\n\t VS \n");
	j = ft_printf(av[1], atoi(av[2]));
	printf("|\n %d VS %d\n", i, j);
	//ft_printf(av[1], atoi(av[2]), av[3]);
	return (0);
}

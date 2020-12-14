#include "ft_printf.h"
#include <string.h>

int main(int ac, char **av)
{
	if (ac == 3)
	{
//		printf("on test  %%d");
	
		ft_printf(av[1], atoi(av[2]));
		printf("|\n\t VS \n");
		printf(av[1], atoi(av[2]));
	}
	return (0);
}
	

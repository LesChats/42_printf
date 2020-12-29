#include "ft_printf.h"
#include <string.h>

int main(int ac, char **av)
{
	if (ac == 2)
	{
		int i = 0;
		printf(av[1], &i, i);
		printf("|\n\t VS \n");
		ft_printf(av[1], &i, i);
		printf("\ni = %d\n", i);
		printf("|\n");
	}

	if (ac == 4)
	{
		ft_printf(av[1], atoi(av[2]), atoi(av[3]));
		printf("|\n\t VS \n");
		printf(av[1], atoi(av[2]), atoi(av[3]));
		printf("|\n");
	}
	if (ac == 3)
	{
//		printf("on test  %%d");
	
		ft_printf(av[1], atof(av[2]));
		printf("|\n\t VS \n");
		printf(av[1], atof(av[2]));
		printf("|\n");
	}
	/*
	wchar_t c = L'漢';
	wchar_t *s = L"abcdefgfsdfsfsfdfsdfsdfljsdhfklajhfkljdfhkldfjhgdklfjghldksjfghsdlkfjhgsdklfjhgsdklfjhgdklfjhglkdjfghldksjfghlksjdfhglksjdhfglksjdfhglkjfghlkjhh"; 
	if (ac == 3)
	{
		ft_printf(av[1], av[2]);
		printf("|\n\t VS \n");
		printf(av[1], av[2]);
		printf("|\n");
		//ft_printf("ici = |%ls|\n", s); 
		//printf("ici = |%ls|\n", s); 
	}
	else if (ac == 2)
	{
		printf("\n%p\n", s);
	}
	*/
	return (0);
}
	

#include "ft_printf.h"
#include <locale.h>

int main(void)
{
	int i;
	int j;

	setlocale(LC_ALL, "");
	
	printf("\nprintf(\"%%ls\", L\"我是一只猫。)\n");
	i = ft_printf("%ls", L"我是一只猫。");
	printf(" -> %d for my PF\n", i);
	j = printf("%ls", L"我是一只猫。");
	printf(" -> %d for LIBC PF\n", j);
	ft_printf("\nlalalalala\n");
	return (0);
}

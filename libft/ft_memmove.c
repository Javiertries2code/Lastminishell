#include "libft.h"

void	ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned int	i;
	char			*strdest;
	char			*strsrc;
	char			straux[n];
	unsigned int	j;

	i = 1;
	j = n;
	strdest = (char *)dest;
	strsrc = (char *)src;
	while (n >= i)
	{
		straux[n - 1] = strsrc[n - 1];
		n--;
	}
	while (j >= i)
	{
		strdest[j - 1] = straux[j - 1];
		j--;
	}
}

// int main()
// {
//  char strdst[] = "123456789101112";
//  char strsrc[] = "popopo";
// unsigned int num = 2;
// ft_memmove(strdst, strsrc, num);
// printf("%c\n", strdst[0]);
// printf("%c\n", strdst[1]);
// printf("%c\n", strdst[2]);
// printf("%c\n\n\n", strdst[5]);
// memmove(strdst, strsrc, 4);
// printf("%c\n", strdst[0]);
// printf("%c\n", strdst[1]);
// printf("%c\n", strdst[2]);
// printf("%c\n", strdst[5]);
// 	return (0);
// }
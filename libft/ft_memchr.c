/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbravo <jbravo@student.42urduliz.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 21:08:26 by jbravo            #+#    #+#             */
/*   Updated: 2022/12/18 21:15:26 by jbravo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	i;
	char			*str;
	unsigned char	ch;

	i = 0;
	;
	str = (char *)s;
	ch = (char)c;
	while (i < n)
	{
		if (ch == str[i])
		{
			return ((void *)&str[i]);
		}
		else
			i++;
	}
	return (NULL);
}

// int main()
// {
//  char *strdst = "x23456789101112";
//  char ch = 's';
//  char ch2 = 's';
// unsigned int num = 10;

// printf("despuesFT%p\n", ft_memchr(strdst, ch, num));
// printf("despuesFT%p\n", memchr(strdst, ch2, num));
// 	return (0);
// }
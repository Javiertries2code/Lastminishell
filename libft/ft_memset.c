/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbravo <jbravo@student.42urduliz.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 21:02:10 by jbravo            #+#    #+#             */
/*   Updated: 2022/12/18 21:16:05 by jbravo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	ch;
	char			*str2;

	str2 = (char *)s;
	ch = (unsigned char)c;
	while (n > 0)
	{
		*str2 = (char)ch;
		n--;
		str2++;
	}
	return ((void *)s);
}

// int main()
// {
//  char str[] = "SoloLosBobosBebenVinoBarato";

// unsigned char ch = '$';

// ft_memset(str + 5, (int)ch, 3);

// printf("%s\n", str);

// 	return (0);
// }
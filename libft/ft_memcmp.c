/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbravo- <jbravo-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 21:08:59 by jbravo            #+#    #+#             */
/*   Updated: 2023/01/03 19:32:20 by jbravo-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int				count;
	unsigned int	i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	count = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (i < n)
	{
		if (str1[i] != str2[i])
		{
			count = str1[i] - str2[i];
			return (count);
		}
		i++;
	}
	return (count);
}

// int	main(void)
// {
// 	const char *str1 = "022344";
// 	const char *str2 = "022344";
// 	unsigned int num = 5;

// 	printf("xx%d\n", ft_memcmp(str1, str2, num));
// 	return (0);
// }
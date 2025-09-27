/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbravo- <jbravo-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 21:08:00 by jbravo            #+#    #+#             */
/*   Updated: 2023/01/10 14:34:47 by jbravo-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	counter(long int n, unsigned int count)
{
	if (n < 0)
	{
		count++;
		n = -n;
	}
	if (n > 9)
	{
		n = n / 10;
		count++;
		count = counter(n, count);
	}
	return (count);
}

static void	last_digits(char *str, int count, int n)
{
	while (n > 9)
	{
		str[--count] = (n % 10) + '0';
		n = n / (10);
	}
	str[--count] = n + '0';
}

char	*ft_itoa(int n)
{
	char	*str;
	int		count;

	count = 1;
	count = counter(n, count);
	str = (char *)malloc((count + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[count] = '\0';
	if (n == -2147483648)
	{
		str[0] = '-';
		str[--count] = '8';
		n = 214748364;
	}
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	last_digits(str, count, n);
	return ((char *)str);
}

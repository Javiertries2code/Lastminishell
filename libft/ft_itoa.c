/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbravo <jbravo@student.42urduliz.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 21:08:00 by jbravo            #+#    #+#             */
/*   Updated: 2022/12/19 01:47:40 by jbravo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	counter(int n, unsigned int count)
{
	if (n < 0)
		n = -n;
	if (n > 9)
	{
		n = n / 10;
		count++;
		count = counter(n, count);
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		count;

	count = counter(n, 1);
	str = (char *)malloc((count + 1) * sizeof(char));
	if (!sizeof(str))
		return (NULL);
	str[count] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	else
		count--;
	while (n > 9)
	{
		str[count--] = (n % 10) + '0';
		n = n / (10);
	}
	str[count] = n + '0';
	return ((char *)str);
}

// int main()
// {
// int i =  -123456789;
// printf("counter in main%d\n", counter(i, 1));

// char *str = ft_itoa(i);

// printf("este el el numero en texto\n%s\n", str);

// return (0);
// }
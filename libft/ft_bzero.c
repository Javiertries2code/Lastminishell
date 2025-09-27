/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbravo <jbravo@student.42urduliz.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 21:06:15 by jbravo            #+#    #+#             */
/*   Updated: 2022/12/19 01:35:10 by jbravo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned int	i;
	int				*num2;

	i = 1;
	num2 = (int *)s;
	while (i++ <= n)
	{
		*num2 = 0;
		num2++;
	}
}

// int	main(void)
// {
// 	int num[12] = {12, 32, 43, 54, 65, 65, 76, 76, 87, 87, 6, 5};

// 	int i;

// 	ft_bzero(num, 3);

// 	for (i = 0; i < 11; i++)
// 	{
// 		printf("%d\n", num[i]);
// 	}

// 	return (0);
// }
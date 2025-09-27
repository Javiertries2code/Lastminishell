/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbravo- <jbravo-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 21:10:18 by jbravo            #+#    #+#             */
/*   Updated: 2023/01/03 20:39:56 by jbravo-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putchar_fd('-', fd);
		ft_putchar_fd('2', fd);
		n = 147483648;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}	
	if (n > 9)
		ft_putnbr_fd((n / 10), fd);
	ft_putchar_fd((char)(n % 10 + '0'), fd);
}

/*
 int main(void)
 {
     ft_putnum_fd(5, 1);
     return (0);
 }*/
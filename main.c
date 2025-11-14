/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havr <havr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:35:14 by havr              #+#    #+#             */
/*   Updated: 2025/11/14 18:38:25 by havr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	main(int argc, char **argv, char **envp)
{
	t_data *data;

	(void)argc;
	(void)argv;
	cut_init_data(&data, envp);
	if (isatty(STDIN_FILENO))
	{
		set_handlers();
		while (1)
			do_the_thing(data, 0);
	}
	return (leaving_program(data));
}
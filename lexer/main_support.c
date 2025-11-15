/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_support.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havr <havr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 15:03:01 by havr              #+#    #+#             */
/*   Updated: 2025/11/15 15:05:18 by havr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int			g_sig = 0;

void	cut_init_data(t_data **data, char **envp)
{
	*data = (t_data *)ft_calloc(1, sizeof(t_data));
	(*data)->env_head = (t_env *)ft_calloc(1, sizeof(t_env));
	(*data)->env_expr = NULL;
	copy_env((*data)->env_head, envp);
}

int	leaving_program(t_data *data)
{
	if (data)
		free_all_data(data, assign_sig(0));
	return (0);
}

void	error_in_red(t_data *data)
{
	if (data->error_red != NULL)
	{
		ft_putstr(SYNTAX_ERR);
		ft_putstr(data->error_red);
		write(1, "\n", 1);
		free(data->error_red);
		data->error_red = NULL;
	}
}

void	free_tokens_cut(t_data *data)
{
	if (data->tokens)
	{
		free_command_info(data);
		data->tokens = NULL;
	}
}

void	do_the_thing(t_data *data, int i)
{
	char	*line;

	line = readline("minishell$ ");
	if (!empty(&line, data))
	{
		if (*line)
			add_history(line);
		if (check_initial_errors(data, line) == 0)
		{
			data->commands = ft_split_quotes(line, '|');
			if (line != NULL)
				free(line);
			i = 0;
			while (data->commands[i])
				expand_var(i++, data);
			data->num_comands = i;
			tokenize(data);
			if (data->error_red == NULL && command_errors(data) == 0)
				manage_mini(data->tokens, data);
			error_in_red(data);
			free_split_tripoint(&data->commands);
			free_tokens_cut(data);
		}
	}
}

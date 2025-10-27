/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marregi- <marregi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 13:06:03 by marregi-          #+#    #+#             */
/*   Updated: 2025/10/27 13:07:20 by marregi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	env_len(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

int	args_len(t_token *list)
{
	int	i;

	i = 0;
	while (list && list->token_op != RED_BACKWD && list->token_op != RED_FORWD
		&& list->token_op != APPEND && list->token_op != HEREDOC)
	{
		i++;
		list = list->next;
	}
	return (i);
}

int	check_redirs(t_token *list)
{
	while (list)
	{
		if (list->token_op == RED_FORWD)
			return (1);
		else if (list->token_op == RED_BACKWD)
			return (2);
		else if (list->token_op == APPEND)
			return (3);
		else if (list->token_op == HEREDOC)
			return (4);
		list = list->next;
	}
	return (0);
}

t_token	*get_cmd_from_list(t_token *list)
{
	while (list)
	{
		if (list->token_op == COMMAND)
			return (list);
		if (list->token_op == BUILTIN)
			return (list);
		if (list->token_op == BINARY)
			return (list);
		if (list->token_op == UNDEFINED)
			return (list);
		list = list->next;
	}
	return (NULL);
}

void	setcmd(t_token ***list, t_data *data)
{
	t_token	**tmp;
	char	*cmd;
	int		i;

	i = 0;
	cmd = NULL;
	tmp = *list;
	while (i < data->num_comands)
	{
		while (tmp[i]->next)
		{
			cmd = get_cmd_path(data->env_head, tmp[i]->value);
			if (cmd && tmp[i]->token_op != BUILTIN)
				tmp[i]->token_op = COMMAND;
			free(cmd);
			tmp[i] = tmp[i]->next;
		}
		cmd = get_cmd_path(data->env_head, tmp[i]->value);
		if (cmd && tmp[i]->token_op != BUILTIN)
			tmp[i]->token_op = COMMAND;
		free(cmd);
		while (tmp[i]->prev)
		{
			tmp[i] = tmp[i]->prev;
		}
		i++;
	}
}

/*
DEBUG!!!!!!!
void	printcharptrptrnull(char **ptrptr)
{
	int	i = 0;

	while (ptrptr[i])
	{
		printf("%d   ->    %s\n", i,  ptrptr[i]);
		i++;
	}
}
 */
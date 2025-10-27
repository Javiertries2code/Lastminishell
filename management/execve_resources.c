/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_resources.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marregi- <marregi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 13:05:01 by marregi-          #+#    #+#             */
/*   Updated: 2025/10/27 13:05:54 by marregi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

static char	**get_path(t_env *env)
{
	char	**split_path;

	while (env)
	{
		if (!ft_strcmp(env->key, "PATH"))
		{
			split_path = ft_split(env->value, ':');
			break ;
		}
		env = env->next;
	}
	return (split_path);
}

char	*get_cmd_path(t_env *env, char *cmd)
{
	char	*joins;
	char	*temp;
	char	**split_path;
	int		i;

	i = 0;
	split_path = get_path(env);
	while (split_path[i])
	{
		temp = ft_strjoin(split_path[i], "/");
		joins = ft_strjoin(temp, cmd);
		free(temp);
		if (!access(joins, F_OK))
		{
			free_split(split_path);
			return (joins);
		}
		free(joins);
		i++;
	}
	free_split(split_path);
	return (NULL);
}

char	**join_all_envp(t_env *env)
{
	int		i;
	char	*joiner;
	char	**envp;

	i = 0;
	envp = NULL;
	envp = (char **) ft_calloc((env_len(env) + 1), sizeof(char *));
	if (!envp)
		return (NULL);
	while (env)
	{
		joiner = ft_strjoin(env->key, "=");
		envp[i++] = ft_strjoin(joiner, env->value);
		free(joiner);
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

char	**list_cmd_arg(t_token *list)
{
	char	**arg;
	int		i;

	i = 0;
	arg = (char **) ft_calloc(args_len(list) + 2, sizeof(char *));
	if (!arg)
		return (NULL);
	arg[i++] = ft_strdup(list->value);
	list = list->next;
	while (list && list->token_op != RED_BACKWD && list->token_op != RED_FORWD
		&& list->token_op != APPEND && list->token_op != HEREDOC)
	{
		arg[i++] = ft_strdup(list->value);
		list = list->next;
	}
	arg[i] = NULL;
	return (arg);
}

int	free_exec_resources(char *cmd_path, char **cmd_arg, char **all_env, int ret)
{
	if (cmd_path)
	{
		free(cmd_path);
		cmd_path = NULL;
	}
	if (cmd_arg)
	{
		free_split(cmd_arg);
		cmd_arg = NULL;
	}
	if (all_env)
	{
		free_split(all_env);
		all_env = NULL;
	}
	return (ret);
}

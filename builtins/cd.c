/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marregi- <marregi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:58:42 by marregi-          #+#    #+#             */
/*   Updated: 2025/10/27 13:03:10 by marregi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

static int	go_home_path(t_env *head)
{
	t_env	*home;

	home = get_env_by_key(head, "HOME");

	if (home && chdir(home->value) == 0)
		return (0);
	else
		ft_putstr_fd("minishell: cd: HOME not set\n", STDOUT_FILENO);
	return (1);
}

static int	go_old_path(t_env *head)
{
	t_env	*oldpwd;

	oldpwd = get_env_by_key(head, "OLDPWD");
	if (oldpwd && chdir(oldpwd->value) == 0)
	{
		return (0);
	}
	else
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDOUT_FILENO);
	return (1);
}

static int	count_args(t_token *list)
{
	int	i;

	i = 0;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}

static void	update_pwd_vars(t_data *data, char *old_pwd_v)
{
	t_env	*oldpwd;
	t_env	*pwd;
	char	*current_pwd;

	current_pwd = getcwd(NULL, 0);
	if (!current_pwd)
		return ;
	oldpwd = get_env_by_key(data->env_head, "OLDPWD");
	if (oldpwd)
	{
		free(oldpwd->value);
		oldpwd->value = old_pwd_v;
	}
	pwd = get_env_by_key(data->env_head, "PWD");
	if (pwd)
	{
		free(pwd->value);
		pwd->value = current_pwd;
	}
	else
		free(current_pwd);
}

int	ft_cd(t_data *data, t_token *list)
{
	char	*old_pwd_v;

	list = list->next;
	if (count_args(list) > 1)
	{
		ft_putstr_fd("cd: too many arguments\n", STDOUT_FILENO);
		return (1);
	}
	old_pwd_v = getcwd(NULL, 0);
	if (!list)
		go_home_path(data->env_head);
	else
	{
		if (!strcmp("~"	, list->value))
			go_home_path(data->env_head);
		else if (!strcmp("-", list->value))
			go_old_path(data->env_head);
		else 
			(chdir(list->value) == 0);
		update_pwd_vars(data, old_pwd_v);
	}
	return (0);
}


/*
HOME not set o home vacio
OLDPWD not set
*/
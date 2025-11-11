/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marregi- <marregi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:58:42 by marregi-          #+#    #+#             */
/*   Updated: 2025/11/11 17:22:37 by marregi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

static int	go_home_path(t_env *head)
{
	t_env	*home;

	home = get_env_by_key(head, "HOME");
	if (!home)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
		return (1);
	}
	if (chdir(home->value) != 0)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		perror(home->value);
		return (1);
	}
	return (0);
}

static int	go_old_path(t_env *head)
{
	t_env	*oldpwd;

	oldpwd = get_env_by_key(head, "OLDPWD");
	if (!oldpwd)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
		return (1);
	}
	if (chdir(oldpwd->value) != 0)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		perror(oldpwd->value);
		return (1);
	}
	ft_putendl_fd(oldpwd->value, STDOUT_FILENO);
	return (0);
}

static void	update_pwd_vars(t_data *data, char *old_pwd_v)
{
	t_env	*oldpwd;
	t_env	*pwd;
	char	*current_pwd;

	current_pwd = getcwd(NULL, 0);
	if (!current_pwd)
		return (free(old_pwd_v));
	oldpwd = get_env_by_key(data->env_head, "OLDPWD");
	if (oldpwd)
	{
		free(oldpwd->value);
		oldpwd->value = old_pwd_v;
	}
	else
		free(old_pwd_v);
	pwd = get_env_by_key(data->env_head, "PWD");
	if (pwd)
	{
		free(pwd->value);
		pwd->value = current_pwd;
	}
	else
		free(current_pwd);
}

static int	change_to_path(const char *path)
{
	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		perror(path);
		return (1);
	}
	return (0);
}

int	ft_cd(t_data *data, t_token *list)
{
	char	*old_pwd_v;
	int		ret;

	list = list->next;
	if (count_args(list) > 1)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	old_pwd_v = getcwd(NULL, 0);
	if (!list || !ft_strcmp("~", list->value))
		ret = go_home_path(data->env_head);
	else if (!ft_strcmp("-", list->value))
		ret = go_old_path(data->env_head);
	else
		ret = change_to_path(list->value);
	if (ret == 0)
		update_pwd_vars(data, old_pwd_v);
	else
		free(old_pwd_v);
	return (ret);
}

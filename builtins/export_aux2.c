/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_aux2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havr <havr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:58:10 by marregi-          #+#    #+#             */
/*   Updated: 2025/11/12 20:04:08 by havr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	free_env_cpy(t_env *nhead)
{
	t_env	*tmp;

	while (nhead)
	{
		tmp = nhead->next;
		free(nhead->key);
		free(nhead->value);
		free(nhead);
		nhead = tmp;
	}
}

static void	check_new_edit(t_env **head, char *key)
{
	t_env	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			remove_by_key(head, key);
			return ;
		}
		tmp = tmp->next;
	}
}

static void	add_export_env(t_env **head, char *key, char *value)
{
	t_env	*tmp;
	t_env	*new;

	new = (t_env *) malloc(sizeof(t_env));
	if (!new)
		return ;
	new->key = ft_strdup(key);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = ft_strdup("");
	new->next = NULL;
	tmp = *head;
	if (!tmp)
	{
		*head = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	manage_export(t_token *list, t_data *data, bool assign)
{
	char	**env;

	if (!assign)
	{
		check_new_edit(&data->env_head, list->value);
		add_export_env(&data->env_head, list->value, NULL);
		return ;
	}
	env = ft_split_env(list->value, '=');
	if (env[0])
	{
		check_new_edit(&data->env_head, env[0]);
		add_export_env(&data->env_head, env[0], env[1]);
	}
	free(env[0]);
	free(env[1]);
	free(env); 
}

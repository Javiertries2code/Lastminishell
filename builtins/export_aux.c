/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marregi- <marregi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:58:22 by marregi-          #+#    #+#             */
/*   Updated: 2025/11/11 16:32:03 by marregi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	add_export_env(t_env **head, char *argval)
{
	t_env	*new;
	t_env	*current;

	new = new_env_aux(argval);
	if (!new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new;
}

static void	add_env_cpy(t_env **nhead, t_env *new)
{
	t_env	*tmp;

	tmp = *nhead;
	if (!new)
		return ;
	if (!*nhead)
	{
		*nhead = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

static t_env	*new_env_cpy(char *key, char *value)
{
	t_env	*cpy;

	cpy = (t_env *) malloc(sizeof(t_env));
	if (!cpy)
		return (NULL);
	cpy->key = ft_strdup(key);
	if (!cpy->key)
		return (free(cpy), NULL);
	cpy->value = ft_strdup(value);
	if (!cpy->value)
		return (free(cpy->key), free(cpy), NULL);
	cpy->next = NULL;
	return (cpy);
}

t_env	*make_env_cpy(t_env *orig)
{
	t_env	*nhead;
	t_env	*new_node;

	nhead = NULL;
	while (orig)
	{
		new_node = new_env_cpy(orig->key, orig->value);
		if (!new_node)
		{
			free_env_cpy(nhead);
			return (NULL);
		}
		add_env_cpy(&nhead, new_node);
		orig = orig->next;
	}
	return (nhead);
}

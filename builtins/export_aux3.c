/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_aux3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marregi- <marregi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 16:31:38 by marregi-          #+#    #+#             */
/*   Updated: 2025/11/11 16:35:34 by marregi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

static void	free_env_node(t_env *node)
{
	if (!node)
		return ;
	if (node->key)
		free(node->key);
	if (node->value)
		free(node->value);
	free(node);
}

static t_env	*create_empty_env(void)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = NULL;
	new->value = NULL;
	new->next = NULL;
	return (new);
}

static t_env	*handle_no_equal(t_env *new, char *argval)
{
	new->key = ft_strdup(argval);
	if (!new->key)
		return (free_env_node(new), NULL);
	new->value = ft_strdup("");
	if (!new->value)
		return (free_env_node(new), NULL);
	return (new);
}

static t_env	*handle_with_equal(t_env *new, char *argval, char *equal)
{
	size_t	key_len;

	equal++;
	key_len = equal - argval;
	new->key = (char *)malloc(key_len);
	if (!new->key)
		return (free_env_node(new), NULL);
	ft_strlcpy(new->key, argval, key_len);
	new->value = ft_strdup(equal);
	if (!new->value)
		return (free_env_node(new), NULL);
	return (new);
}

t_env	*new_env_aux(char *argval)
{
	t_env	*new;
	char	*equal;

	new = create_empty_env();
	if (!new)
		return (NULL);
	equal = ft_strchr(argval, '=');
	if (!equal)
		return (handle_no_equal(new, argval));
	return (handle_with_equal(new, argval, equal));
}

#include "../mini.h"

static t_env	*new_env_aux(char *argval)
{
	size_t	l;
	char	*equal;
	t_env	*new;

	new = (t_env *) malloc(sizeof(t_env));
	new->next = NULL;
	if (!new)
		return (NULL);
	equal = ft_strchr(argval, '=');
	if (!equal)
	{
		new->key = ft_strdup(argval);
		new->value = ft_strdup("");
		return (new);
	}
	equal++;
	l = equal - argval;
	new->key = (char *) malloc(ft_strlen(argval) - l + 1);
	if (!new->key)
	{
		return (free(new->key), NULL);
	}
	ft_strlcpy(new->key, argval, ft_strlen(argval) - l + 1);
	new->value = ft_strdup(equal);
	return (new);
}

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
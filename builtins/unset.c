#include "../mini.h"

static void	remove_by_key(t_env **head, char *key)
{
    t_env *current;
    t_env *prev;

    if (!head || !*head || !key)
        return;
    current = *head;
    prev = NULL;
    while (current)
    {
        if (strcmp(current->key, key) == 0)
        {
            if (prev == NULL)
                *head = current->next;
            else
                prev->next = current->next;
	            free(current->key);
            free(current->value);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

int	ft_unset(t_token *list, t_data *data)
{
	list = list->next;
	while (list && list->next && list->next->token_op == STRING)
	{
		remove_by_key(&data->env_head, list->next->value);
		list = list->next;
	}
	remove_by_key(&data->env_head, list->value);
	return (0);
}
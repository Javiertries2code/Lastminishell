#include "../mini.h"

int	env_len(t_env *env)
{
	int	i = 0;

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
	while (list && list->token_op == STRING)
	{
		i++;
		list = list->next;
	}
	return (i);
}

int	check_redirs(t_token *list, int current)
{
	if (list->data->l_back[current] + list->data->l_ff[current] +
		list->data->l_hd[current] + list->data->l_for[current])
	{
		return (1);
	}
	return (0);
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
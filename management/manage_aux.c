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
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
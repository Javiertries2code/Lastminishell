#include "../mini.h"

int	ft_cd(t_token *list)
{
	char	*path;

	list = list->next;
	if (!list)
	{
		path = getenv("HOME");
		if (path && chdir(path) == 0)
			return (0);
	}
	else
	{
		if (chdir(list->value) == 0)
			return (0);
	}
	return (1);
}
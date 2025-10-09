#include "../mini.h"

int	builtin_manager(t_token *list)
{
	if (!ft_strcmp(list->value, "echo"))
		return (ft_echo(list));
	return (0);
}
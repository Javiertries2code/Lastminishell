#include "../mini.h"

int	builtin_manager(t_token *list, t_data *data)
{
	if (!ft_strcmp(list->value, "echo"))
		return (ft_echo(list));
	if (!ft_strcmp(list->value, "pwd"))
		return (ft_pwd());
	if (!ft_strcmp(list->value, "env"))
		return (ft_env(data));
	return (0);
}
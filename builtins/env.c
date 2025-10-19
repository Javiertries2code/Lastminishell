#include "../mini.h"

int	ft_env(t_data *data)
{
	t_env	*tmp;

	tmp = data->env_head;
	if (!tmp)
		return (-1);
	while (tmp)
	{
		ft_putstr_fd(tmp->key, STDOUT_FILENO);
		ft_putchar_fd('=', STDOUT_FILENO);
		ft_putstr_fd(tmp->value, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		tmp = tmp->next;
	}
	return (0);
}

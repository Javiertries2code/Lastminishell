#include "../mini.h"

/// @brief Hay un problema cuando envias al echo argumentos separados por espacios por quie los espacios se van en el parseo
/// Se podria solucionar cogiendo los espacios y metiendoles un t_token_op spaces y usarlos cuando sea necesario solo
/// @param list 
/// @return 
int	ft_echo(t_token *list)
{
	bool	new_line;

	new_line = true;
	list = list->next;
	if (list && !ft_strcmp("-n", list->value))
	{
		new_line = false;
		list = list->next;
	}
	while (list)
	{
		ft_putstr_fd(list->value, STDOUT_FILENO);
		list = list->next;
	}
	if (new_line)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}


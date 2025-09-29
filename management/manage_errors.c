#include "../mini.h"

int	token_with_error(char *error_msg, char *value)
{
	if (error_msg)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(error_msg, STDERR_FILENO);
		ft_putstr_fd(" `", STDERR_FILENO);
		ft_putstr_fd(value, STDERR_FILENO);
		ft_putstr_fd("\'\n", STDERR_FILENO);
	}
	return (1);
}

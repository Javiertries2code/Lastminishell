#include "../mini.h"

int	ft_exit(t_data *data)
{
	free_command_info(data, 0);
	exit(sig);
	return (0);
}
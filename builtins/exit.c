#include "../mini.h"

int	ft_exit(t_data *data)
{
	free_all_data(data);
	exit(sig);
	return (0);
}
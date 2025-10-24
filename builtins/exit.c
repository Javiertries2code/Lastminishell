#include "../mini.h"

int	ft_exit(t_data *data)
{
	free_all_data(data, sig);
	return (0);
}
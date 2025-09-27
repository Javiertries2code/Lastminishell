#include "../mini.h"

void	manage_mini(t_token **list, t_data *data)
{
	pipex(list, data, 0, -1);
}
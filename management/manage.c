#include "../mini.h"

void	manage_mini(t_token **list, t_data *data)
{
	setcmd(&list, data);
	//print_tokens(data);
	pipex(list, data, 0, -1);
	return;
}
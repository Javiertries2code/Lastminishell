#include "../mini.h"

int	ft_pwd()
{
	char	*work_dir;

	work_dir = NULL;
	work_dir = getcwd(work_dir, 0);
	if (!work_dir)
		return (-1);
	ft_putstr_fd(work_dir, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
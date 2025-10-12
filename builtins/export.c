#include "../mini.h"

static void	swap_env(t_env *e1, t_env *e2)
{
	t_env	*tmp;

	tmp = e1;
	
}

static void	sort_env(t_env **cpy)
{

}

static void	print_env_alpha(t_env *cpy)
{
	while (cpy)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(cpy->key, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		ft_putstr_fd("\"", STDOUT_FILENO);
		ft_putstr_fd(cpy->value, STDOUT_FILENO);
		ft_putstr_fd("\"", STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		cpy = cpy->next;
	}
}

int	ft_export(t_token *list, t_data *data)
{
	t_env	*cpy;

	cpy = data->env_head;
	list = list->next;
	if (!list)
	{
		sort_env(&cpy);
		print_env_alpha(cpy);
		return (0);
	}
	
}
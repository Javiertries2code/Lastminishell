#include "../mini.h"

void	swap_env(t_env *a, t_env *b)
{
	char	*tmp_key;
	char	*tmp_value;

	if (!a || !b)
		return ;
	tmp_key = a->key;
	tmp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = tmp_key;
	b->value = tmp_value;
}

static bool	is_sorted(t_env *tmp)
{
	char	*all;
	char	*alln;
	char	*temp;

	while (tmp && tmp->next)
	{
		temp = ft_strjoin(tmp->key, "=");
		all = ft_strjoin(temp, tmp->value);
		free(temp);
		temp = ft_strjoin(tmp->next->key, "=");
		alln = ft_strjoin(temp, tmp->next->value);
		free(temp);
		if (ft_strcmp(all, alln) > 0)
		{
			free(all);
			free(alln);
			return (false);
		}
		free(all);
		free(alln);
		tmp = tmp->next;
	}
	return (true);
}

static void	sort_env(t_env **cpy)
{
	t_env	*current;
	char	*all;
	char	*alln;
	char	*temp;

	while (!is_sorted(*cpy))
	{
		current = *cpy;
		while (current && current->next)
		{
			temp = ft_strjoin(current->key, "=");
			all = ft_strjoin(temp, current->value);
			free(temp);
			temp = ft_strjoin(current->next->key, "=");
			alln = ft_strjoin(temp, current->next->value);
			free(temp);
			if (ft_strcmp(all, alln) > 0)
			{
				swap_env(current, current->next);
			}
			free(all);
			free(alln);
			current = current->next;
		}
	}
}

static void	print_env_alpha(t_env *cpy)
{
	while (cpy)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(cpy->key, STDOUT_FILENO);
		if (ft_strlen(cpy->value) != 0)
		{
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
			ft_putstr_fd(cpy->value, STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
		cpy = cpy->next;
	}
}

int	ft_export(t_token *list, t_data *data)
{
	t_env	*cpy;

	cpy = data->env_head;
	if (!list->next)
	{
		sort_env(&cpy);
		print_env_alpha(cpy);
		return (0);
	}
	list = list->next;
	while (list)
	{
		add_export_env(&data->env_head, list->value);
		list = list->next;
	}
	return (0);
}
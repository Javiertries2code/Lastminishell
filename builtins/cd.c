#include "../mini.h"

t_env	*get_pwd(t_data *data)
{
	char	*awd;
	t_env	*tmp;

	awd = NULL;
	tmp = data->env_head;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "PWD"))
			return (tmp);
		tmp = tmp->next;
	}
}

t_env	*get_oldpwd(t_data *data)
{
	char	*awd;
	t_env	*tmp;

	awd = NULL;
	tmp = data->env_head;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "OLDPWD"))
			return (tmp);
		tmp = tmp->next;
	}
}

int	ft_cd(t_data *data, t_token *list)
{
	t_env	*pwd;
	t_env	*oldpwd;

	pwd = get_pwd(data);
	oldpwd = get_oldpwd(data);
	list = list->next;
	while (list)
	{
		if (!list)
		{
			free(pwd->value);
			pwd->value = ft_strdup(oldpwd->value);
		}
		else if (list && list->next == STRING)
		{
			
		}
		
	}
	
}
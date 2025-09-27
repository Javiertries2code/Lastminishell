#include "../mini.h"

static char	**get_path(t_env *env)
{
	char	**split_path;

	while (env)
	{
		if (!ft_strcmp(env->key, "PATH"))
		{
			split_path = ft_split(env->value, ':');
			break ;
		}
		env = env->next;
	}
	return (split_path);
}

char	*get_cmd_path(t_env *env, char *cmd)
{
	char	*joins;
	char	**split_path;
	int		i;

	i = 0;
	split_path = get_path(env);
	while (split_path[i])
	{
		joins = ft_strjoin(split_path[i], "/");
		joins = ft_strjoin(joins, cmd);
		if (!access(joins, F_OK))
		{
			free_split(split_path);
			return (joins);
		}
		i++;
	}
	free_split(split_path);
	return (NULL);
}

char	**join_all_envp(t_env *env)
{
	int		i;
	char	*joiner;
	char	**envp;

	i = 0;
	envp = NULL;
	envp = (char **) ft_calloc((env_len(env) + 1), sizeof(char *));
	if (!envp)
		return (NULL);
	while (env)
	{
		joiner = ft_strjoin(env->key, "=");
		envp[i++] = ft_strjoin(joiner, env->value);
		free(joiner);
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

char	**list_cmd_arg(t_token *list)
{
	char	**arg;
	int		i;

	i = 0;
	arg = (char **) ft_calloc(args_len(list) + 2, sizeof(char *));
	if (!arg)
		return (NULL);
	arg[i++] = ft_strdup(list->value);
	list = list->next; 
	while (list && list->token_op == STRING)
	{
		arg[i++] = ft_strdup(list->value);
		list = list->next;
	}
	arg[i] = NULL;
	return (arg);
}

void	free_exec_resources(char *cmd_path, char **cmd_arg, char **all_env)
{
	int	i;

	i = 0;
	if (cmd_path)
		free(cmd_path);
	while (cmd_arg[i])
	{
		free(cmd_arg[i]);
		i++;
	}
	i = 0;
	while (all_env[i])
	{
		free(all_env[i]);
		i++;
	}
}

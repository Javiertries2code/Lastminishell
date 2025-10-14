#include "../mini.h"

static size_t	counter_env(const char *s, char c)
{
	size_t	counter;
	size_t	i;

	counter = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			counter++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (counter);
}

char	*new_str_value(const char *s, char c)
{
	size_t	len;
	char	*ptr;

	len = ft_strlen(s);
	ptr = (char *)ft_calloc(len + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s, len + 1);
	return (ptr);
}

char	*new_str_key(const char *s, char c)
{
	size_t	len;
	char	*ptr;

	len = get_len(s, c);
	ptr = (char *)ft_calloc(len + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s, len + 1);
	return (ptr);
}


char	**ft_split_env(const char *s, char c)
{
	char	**ptr;
	size_t	i;
	size_t	j;
	size_t len;
	if (!s)
		return (NULL);
	len = counter_env(s, c);
    if(len >1)
        len = 1;
	ptr = (char **)ft_calloc(len + 1, sizeof(char *));
	if (!ptr)
		return (NULL);
	i = 0;
	j = 0;
	while (s[j] && i <= 1)
	{
		if (s[j] != c && i > 0)
			ptr[i++] = new_str_value(&(s[j]), c);
		else if (s[j] != c && i < 1)
		{
			ptr[i++] = new_str_key(&(s[j]), c);
			while (s[j] && s[j] != c)
				j++;
		}
		else
			j++;
	}
	return (ptr);
}

static void	add_env_element(t_env *env_head, char *envp)
{
    t_env	*new_element;
    t_env	*tmp;
    char	**key_value;

    tmp = env_head;
    while (tmp->next)
        tmp = tmp->next;
    key_value = ft_split_env(envp, '=');
	free(envp);
	envp = NULL;
    if (!key_value || !key_value[0])
    {
        if (key_value)
             free_split_tripoint(&key_value);
        return ;
    }
    if (!env_head->key)
    {
        env_head->key = key_value[0];
        env_head->value = key_value[1];
        free(key_value);
    }
    else
    {
        new_element = ft_calloc(1, sizeof(t_env));
        new_element->key = key_value[0];
        new_element->value = key_value[1];
        tmp->next = new_element;
        free(key_value);
    }
    
}

/**
 * @brief Copies the system environment into a linked list.
 *
 * Iterates over the `envp` array and adds each entry to the `env_head` list.
 *
 * @param env_head Pointer to the head of the environment list.
 * @param envp Array of environment strings ("KEY=VALUE").
 */
// void	copy_env(t_env *env_head, char **envp)
// {
//      char **next_line;
    
//     *next_line = ft_strdup(*envp);
// 	while (*envp)
// 	{
// 		add_env_element(env_head, *next_line);
//        free(*next_line);
//         //free_str_safe(&next_line);
// 		envp++;
// 	}
//     free(next_line);
// }
void	copy_env(t_env *env_head, char **envp)
{
	while (*envp)
	{
		add_env_element(env_head, ft_strdup(*envp));
     		envp++;
	}
}

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

static bool  init_split_env(const char **s, char c, size_t *i, size_t *j, char ***ptr)
{
	
	size_t	len;

	if (!s || !*s)
        return (false);
	len = counter_env(*s, c);
	if (len > 1)
		len = 1;
	*ptr = (char **)ft_calloc(len + 1, sizeof(char *));
	if (*ptr == NULL)
		return (false);
	*i = 0;
	*j = 0;
	return (true);
}

char	**ft_split_env(const char *s, char c)
{
	char	**ptr;
	size_t	i;
	size_t	j;

	
	if (!init_split_env(&s, c, &i, &j, &ptr))
		return (NULL);
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

/**
 * @brief Add environment variable element to the linked list
 *
 * MODIFICADO: Ahora libera correctamente el envp duplicado después de usarlo
 * porque add_env_element hace ft_split_env internamente que crea memoria nueva.
 * El envp duplicado original ya no se necesita después del split.
 *
 * @param env_head Head of environment list
 * @param envp Environment string in format "KEY=VALUE"
 */
static void	add_env_element(t_env *env_head, char *envp)
{
	t_env	*new_element;
	t_env	*tmp;
	char	**split;

	// CAMBIO: Hacer split PRIMERO
	split = ft_split_env(envp, '=');
	// CAMBIO: Liberar envp INMEDIATAMENTE después del split
	// porque ft_split_env ya creó copias nuevas de key y value
	free(envp);
	if (!split || !split[0])
	{
		if (split)
			free_split(split);
		return ;
	}
	new_element = ft_calloc(1, sizeof(t_env));
	if (!new_element)
	{
		free_split(split);
		return ;
	}
	new_element->key = split[0];
	new_element->value = split[1];
	new_element->next = NULL;
	free(split);
		// Liberar el array pero NO los strings (los usamos en new_element)
	if (!env_head->key)
	{
		env_head->key = new_element->key;
		env_head->value = new_element->value;
		free(new_element);
		return ;
	}
	tmp = env_head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_element;
}

/**
 * @brief Copy environment variables to internal structure
 *
 * @param env_head Head of environment list to populate
 * @param envp Environment array from main
 */
void	copy_env(t_env *env_head, char **envp)
{
	if (!envp || !*envp)
		return ;
	while (*envp)
	{
		// CAMBIO: El ft_strdup se libera dentro de add_env_element ahora
		add_env_element(env_head, ft_strdup(*envp));
		envp++;
	}
}
#include "../mini.h"

/**
 * @brief Creates a new string containing the value part of an env variable
 *
 * @param s Source string to copy from
 * @param c Delimiter character (not used but kept for consistency)
 * @return char* Newly allocated string with full content,
	NULL if allocation fails
 */
char	*new_str_value(const char *s, char c)
{
	size_t	len;
	char	*ptr;

	len = ft_strlen(s);
	// if(NULL == s);
	// 	return(ft_strdup("VACIOVACIOVACIO"));
			// print_debug("new str value---s[len]"); 
			// print_debug(s); 

	ptr = (char *)ft_calloc(len + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	
	ft_strlcpy(ptr, s, len + 1);
	return (ptr);
}

/**
 * @brief Creates a new string containing the key part of an env variable
 *
 * @param s Source string to copy from
 * @param c Delimiter character to stop at
 * @return char* Newly allocated string with key part, NULL if allocation fails
 */
char	*new_str_key(const char *s, char c)
{
	size_t	len;
	char	*ptr;

	len = get_len(s, c);
		// print_debug("\nnew str Key -- "); 
		// 	print_debug(s); 
	ptr = (char *)ft_calloc(len + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s, len + 1);
	return (ptr);
}

/**
 * @brief Splits environment string and prepares new element structure
 *
 * @param split Pointer to store split result
 * @param new_element Pointer to store newly allocated env element
 * @param envp Pointer to environment string (will be freed)
 * @return bool true if successful, false if split failed or empty key
 */
bool	cut_add_env(char ***split, t_env **new_element, char **envp)
{
	*split = ft_split_env(*envp, '=');
	//print_debug("\nnextenv");
	//print_debug(*envp); //
	////
	// print_debug((*split)[0]);
	// printf(" ps plit[0] %p ->", &(split)[0]);
	// print_debug((*split)[1]);

		//(*split)[1] == ft_strdup("thos should be and empty space"); 
		//print_debug("\nnextenv");
		//print_debug(*envp); 
//
		//print_debug((*split)[0]);
		//print_debug((*split)[1]);
	
	///////
	free(*envp);
	if (!(*split) || !(*split)[0] || !(*split)[0][0])
	{
		if (*split)
			free_split(*split);
		return (false);
	}
	*new_element = ft_calloc(1, sizeof(t_env));
	if (!(*new_element))
	{
		free_split(*split);
		return (false);
	}
	return (true);
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
void	add_env_element(t_env *env_head, char *envp)
{
	t_env	*new_element;
	t_env	*tmp;
	char	**split;

	if (cut_add_env(&split, &new_element, &envp) == false)
		return ;
	new_element->key = split[0];
	new_element->value = split[1];
	new_element->next = NULL;
	free(split);
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
		add_env_element(env_head, ft_strdup(*envp));
		envp++;
	}
}
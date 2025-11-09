#include "../mini.h"

/**
 * @brief Counts the number of segments separated by delimiter character
 *
 * @param s String to analyze
 * @param c Delimiter character
 * @return size_t Number of segments found
 */
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

/**
 * @brief Initializes variables and allocates memory for split operation
 *
 * @param s Pointer to source string
 * @param c Delimiter character
 * @param i Pointer to index counter (initialized to 0)
 * @param j Pointer to position counter (initialized to 0)
 * @param ptr Pointer to store allocated array
 * @return bool true if initialization successful, false otherwise
 */
static bool	init_split_env(const char **s, char c, size_t *i, size_t *j,
		char ***ptr)
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

/**
 * @brief Splits environment string into key and value at first delimiter
 *
 * Creates array with max 2 elements: first is key, second is value.
 * Stops at first occurrence of delimiter character.
 *
 * @param s String to split (format: "KEY=VALUE")
 * @param c Delimiter character (typically '=')
 * @return char** Array with key and value, NULL if allocation fails
 */
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
			if (s[j + 1] == 0)
			{
				ptr[i++] = ft_strdup("");
				return (ptr);
			}
		}
		else
			j++;
	}
	return (ptr);
}

/**
 * @brief Processes export command for environment variables
 *
 * @param env_head Head of environment list
 * @param envp Environment string to process
 * @return char* Processed result (implementation pending)
 */
char	*process_export(t_env *env_head, char *envp)
{
	add_env_element(env_head, envp);
	return (NULL);
}
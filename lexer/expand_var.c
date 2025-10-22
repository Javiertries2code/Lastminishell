#include "../mini.h"
#include "libft.h" // si usas ft_strlen, ft_memcpy, etc.
#include <stdlib.h>

/**
 * @brief Check if character is a whitespace.
 *
 * @param c Character to check.
 * @return 1 if whitespace, 0 otherwise.
 */
static int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

/**
 * @brief Calculates the length of a variable name starting after '$'.
 *
 * Stops at space, quote or end of string.
 *
 * @param s Pointer to the variable name (after '$').
 * @param quotes Current quote context (' or " or 0).
 * @return Length of variable name.
 */
static int	ft_var_len(const char *s, char quotes)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	// while (s[i]  && !is_space(s[i]))
	// 	i++;
	while (s[i] && quotes != s[i] && !is_space(s[i]))
		i++;
	return (i);
}
/**
 * @brief Checks if a character is valid.
 *
 * This function determines whether the given character meets the criteria
 * for being considered valid. The specific definition of "valid" depends
 * on the implementation, such as being alphanumeric, printable, or matching
 * a certain set of allowed characters.
 *
 * @param c The character to check.
 * @return true if the character is valid, false otherwise.
 */
static int	is_valid_char(char c)
{
	return (ft_isalpha(c) || ft_isdigit(c) || c == '?');
}

/**
 * @brief Duplicates a substring until quote, space or '$'.
 *
 * @param s String to copy from.
 * @param quotes Quote character context.
 * @return Newly allocated string with extracted name.
 */
static char	*ft_struntil(const char *s, char quotes)
{
	int		i;
	char	*ret;

	i = 0;
	if (!s)
		return (NULL);
	//////
	// if (s[0] == '?')
	// {
	//     ret = (char *)malloc(sizeof(char) * 2);
	//     if (!ret)
	//         return (NULL);
	//     ret[0] = '?';
	//     ret[1] = '\0';
	//     return (ret);
	// }
	////
	while (s[i] && quotes != s[i] && !is_space(s[i]) && is_valid_char(s[i]))
		i++;
	if (i == 0)
		return (NULL);
	ret = (char *)malloc(sizeof(char) * (i + 1));
	if (!ret)
		return (NULL);
	ft_memcpy(ret, s, i);
	ret[i] = '\0';
	// if (DEBUG)
	// 	printf("ft_struntil-> ret %s \t \n", ret);
	return (ret);
}

/**
 * @brief Compares two strings for equality.
 *
 * @param s1 First string.
 * @param s2 Second string.
 * @return 0 if equal, non-zero otherwise.
 */
/*
static int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	n;

	n = ft_strlen(s1);
	while ((n > 0) && (*s1 == *s2) && *s1)
	{
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
*/
/**
 * @brief Searches environment list for a variable name.
 *
 * Sets `data->tmp_var_expanded` if match is found.
 *
 * @param data Pointer to shell data struct.
 */
static void	data_find_in_list(t_data *data)
{
	t_env	*head;

	if (!ft_strcmp(data->tmp_var_name, "?"))
	{
		data->tmp_var_expanded = ft_itoa(sig);
		return ;
	}
	head = data->env_head;
	while (head)
	{
		if (!ft_strcmp(data->tmp_var_name, head->key))
		{
			data->tmp_var_expanded = head->value;
			return ;
		}
		head = head->next;
	}
}

/**
 * @brief Extracts variable name and finds its value in the environment.
 *
 * @param str String starting at '$'.
 * @param quotes Current quote context.
 * @param data Pointer to shell data struct.
 */
void	data_find_var(char *str, int quotes, t_data *data)
{
	(data->tmp_var_name = ft_struntil(&str[1], quotes));
	// str[1 as to avoid the $
	if (data->tmp_var_name == NULL)
		return ;
	data->tmp_var_len = ft_strlen(data->tmp_var_name);
	data_find_in_list(data);
	if (!data->tmp_var_expanded)
	{
		free_null_vars(NULL, data);
	}
}

void	free_null_vars(char *str, t_data *data)
{
	if (str != NULL)
	{
		free(str);
		str = NULL;
	}
	if (data->tmp_var_expanded != NULL)
	{
		if (data->tmp_var_name && !ft_strcmp(data->tmp_var_name, "?"))
		{
			free(data->tmp_var_expanded);
		}
		data->tmp_var_expanded = NULL;
	}
	if (data->tmp_var_name != NULL)
	{
		free(data->tmp_var_name);
		data->tmp_var_name = NULL;
	}
	data->tmp_var_len = 0;
}
static void	*cut_substitute(char **prefix, char **suffix, char **str,
		char **tmp, t_data *data)
{
	if (prefix && *prefix)
		free(*prefix);
	if (suffix && *suffix)
		free(*suffix);
	if (tmp && *tmp)
		free(*tmp);
	free_null_vars(*str, data);
	return (NULL);
}

/**
 * @brief Substitutes a variable occurrence in a command string.
 *
 * Builds new string from prefix + expanded value + suffix.
 *
 * @param str Original command string (to free).
 * @param data Pointer to shell data struct.
 * @param quotes Current quote context.
 * @param i Index of '$' in original string.
 * @return New command string with variable expanded.
 */
char	*data_substitute_var(char *str, t_data *data, int i)
{
	char	*prefix;
	char	*suffix;
	char	*tmp;
	char	*ret;

	prefix = ft_substr(str, 0, i);
	suffix = ft_strdup(&str[i + data->tmp_var_len + 1]);
	if (!prefix || !suffix)
		return (cut_substitute(&prefix, &suffix, &str, NULL, data));
	if (data->tmp_var_expanded)
		tmp = ft_strjoin(prefix, data->tmp_var_expanded);
	else
		tmp = ft_strjoin(prefix, "");
	if (!tmp)
		return (cut_substitute(&prefix, &suffix, &str, NULL, data));
	ret = ft_strjoin(tmp, suffix);
	if (!ret)
		return (cut_substitute(&prefix, &suffix, &str, &tmp, data));
	cut_substitute(&prefix, &suffix, &str, &tmp, data);
	return (ret);
}

/**
 * @brief Expands all environment variables in a command.
 *
 * Handles quote context and replaces variables like $VAR with their values.
 *
 * @param j Index of command in command array.
 * @param data Pointer to shell data struct.
 */
void	expand_var(int j, t_data *data)
{
	int		i;
	char	quotes;

	i = 0;
	quotes = 0;
	while (data->commands[j][i])
	{
		quotes = check_quotes(quotes, data->commands[j][i]);
		if (data->commands[j][i] == '$' && quotes != '\'')
		{
			free_null_vars(NULL, data);
			data->tmp_var_len = ft_var_len(&data->commands[j][i], quotes);
			data_find_var(&data->commands[j][i], quotes, data);
			if (data->tmp_var_expanded)
			{
				data->commands[j] = data_substitute_var(data->commands[j], data,
						i);
				free_null_vars(NULL, data);
				quotes = 0;
				i = -1;
			}
		}
		i++;
	}
}

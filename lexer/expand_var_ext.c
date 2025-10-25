#include "../mini.h"

/**
 * @brief Check if character is a whitespace.
 *
 * @param c Character to check.
 * @return 1 if whitespace, 0 otherwise.
 */
int	is_space(char c)
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
int	ft_var_len(const char *s, char quotes)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
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
 int	is_valid_char(char c)
{
	return (ft_isalpha(c) || ft_isdigit(c) || c == '?');
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


/**
 * @brief Duplicates a substring until quote, space or '$'.
 *
 * @param s String to copy from.
 * @param quotes Quote character context.
 * @return Newly allocated string with extracted name.
 */
 char	*ft_struntil(const char *s, char quotes)
{
	int		i;
	char	*ret;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] && quotes != s[i] && !is_space(s[i]) && is_valid_char(s[i]))
		i++;
	if (i == 0)
		return (NULL);
	ret = (char *)malloc(sizeof(char) * (i + 1));
	if (!ret)
		return (NULL);
	ft_memcpy(ret, s, i);
	ret[i] = '\0';
	return (ret);
}
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
#include "../mini.h"

t_token	*lexer(char *input)
{
	(void)input;
	return (NULL);
}

/**
 * @brief Counter variable for tracking iterations or occurrences
 *
 * This variable is used to maintain a count of events, iterations,
 * or other countable operations within the program.
 *
 * @var counter
 * @type int
 * @initial 0
 * @note Should be initialized to 0 before use
 * @warning Ensure proper bounds checking to prevent overflow
 */
size_t	counter(const char *s, char c)
{
	size_t i;
	size_t count;
	char in_quotes;

	i = 0;
	count = 0;
	in_quotes = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && (in_quotes || s[i] != c))
		{
			in_quotes = check_quotes(in_quotes, s[i]);
			i++;
		}
	}
	return (count);
}
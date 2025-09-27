#include "../mini.h"

/**
 * @brief Checks if quotes are balanced in the given string
 * @param str The input string to check for balanced quotes
 * @return 1 if quotes are balanced, 0 otherwise
 * 
 * This function verifies that single quotes (') and double quotes (") 
 * are properly paired and closed in the input string. It tracks the 
 * state of quote parsing to ensure syntactic correctness.
 */
char	check_quotes(char quotes, char c)
{
	if (c == '\'' || c == '\"')
	{
		if (!quotes)
			return (c);
		if (quotes == c)
			return (0);
	}
	return (quotes);
}

/**
 * @brief Checks if quotes are balanced in a given string
 * 
 * This function verifies that all opening quotes have corresponding closing quotes
 * in the input string. It handles both single quotes (') and double quotes (").
 * 
 * @param str The input string to check for balanced quotes
 * @return true if all quotes are properly balanced, false otherwise
 * 
 * @note The function considers a quote balanced when every opening quote
 *       has a matching closing quote of the same type
 * @note Escaped quotes (preceded by backslash) may be handled differently
 *       depending on implementation
 * 
 * @example
 * quotes_balanced("Hello 'world'") returns true
 * quotes_balanced("Hello \"world\"") returns true
 * quotes_balanced("Hello 'world\"") returns false
 */
int	quotes_balanced(char *str)
{
	int		i;
	char	quotes;

	i = 0;
	quotes = 0;
	while (str[i])
	{
		quotes = check_quotes(quotes, str[i]);
		i++;
	}
	return (!quotes);
}
/**
 * @brief Gets the length of the data structure
 * 
 * This function returns the current length or size of the data structure.
 * 
 * @return The length/size of the data structure as an integer value
 */
static size_t	get_len(const char *s, char c)
{
	size_t	len;
	char	in_quotes;

	len = 0;
	in_quotes = 0;
	while (s[len] && (in_quotes || s[len] != c))
	{
		in_quotes = check_quotes(in_quotes, s[len]);
		len++;
	}
	return (len);
}
/**
 * @brief Creates a new dynamically allocated string by concatenating multiple strings
 * 
 * This function takes a variable number of string arguments and concatenates them
 * into a single newly allocated string. The caller is responsible for freeing
 * the returned memory.
 * 
 * @param count The number of strings to concatenate
 * @param ... Variable number of const char* string arguments to concatenate
 * 
 * @return char* Pointer to the newly allocated concatenated string, or NULL on failure
 * 
 * @note The caller must free the returned pointer using free() to avoid memory leaks
 * @warning All string arguments must be valid null-terminated strings
 * 
 * @example
 * char* result = new_str(3, "Hello", " ", "World");
 * // result contains "Hello World"
 * free(result);
 */
static char	*new_str(const char *s, char c)
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
static size_t	counter(const char *s, char c)
{
	size_t	i;
	size_t	count;
	char	in_quotes;

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
/**
 * @brief Splits a string into an array of substrings based on delimiters while preserving quoted sections
 * 
 * This function parses a string and splits it into tokens using the specified delimiter,
 * but treats content within quotes as a single token regardless of delimiters inside.
 * Quotes can be single (') or double (") quotes.
 * 
 * @param str The input string to be split
 * @param delimiter The character used as delimiter for splitting
 * 
 * @return char** A null-terminated array of strings containing the split tokens,
 *         or NULL if allocation fails or input is invalid
 * 
 * @note The returned array and all strings within it are dynamically allocated
 *       and must be freed by the caller
 * @note Empty tokens between consecutive delimiters are typically ignored
 * @note Escaped quotes within quoted sections may be handled depending on implementation
 * 
 * @warning Caller is responsible for freeing the returned array and all its elements
 */
char	**ft_split_quotes(const char *s, char c)
{
	char	**ptr;
	size_t	i;
	size_t	j;
	size_t	words;

	if (!s)
		return (NULL);
	words = counter(s, c);
	ptr = (char **)ft_calloc(words + 1, sizeof(char *));
	if (!ptr)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			ptr[j++] = new_str(&s[i], c);
			i += get_len(&s[i], c);
		}
	}
	return (ptr);
}

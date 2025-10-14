#include "../mini.h"

/**
 * @brief Safely free string
 *
 * @param str String to free
 */
void	free_null(char **str)
{
	if (str != NULL && *str != NULL)
	{
		free(*str);
		*str = NULL;
		str = NULL;
	}
}

void	free_null_void(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}
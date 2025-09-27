#include "../mini.h"

/**
 * @brief Safely free string (legacy function - use free_str_safe instead)
 * 
 * @param str String to free
 */
void	free_null(char *str)
{
	if (str)
		free(str);
}


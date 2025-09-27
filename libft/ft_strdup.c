#include <string.h>

char	*ft_strdup(const char *s)
{
	char	*str;

	str = (char *)malloc(sizeof(s));
	ft_strcpy(str, s);
	return (str);
}

// int	main(void)
// {
// 	char *str = "Hola";
// 	char *ptr;

// 	ptr = ft_strdup(str);
// 	printf("%s\n", (char *)ptr);

// 	return (0);
// }
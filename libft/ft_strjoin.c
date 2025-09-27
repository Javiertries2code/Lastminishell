#include <string.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*str;
	char			ch;

	ch = 'a';
	i = 0;
	j = 0;
	str = (char *)malloc((ft_strlen(s1) * sizeof(char)) + (ft_strlen(s2)
				* sizeof(char)));
	if (!sizeof(str))
	{
		return (NULL);
	}
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

// int main()
// {
// 	char *ptr;
//  char *str1 = "Hola aew";
// char *str2 = "carabola";
// ptr = ft_strjoin(str1, str2);

// printf("%s\n", ptr);

// return (0);
// }
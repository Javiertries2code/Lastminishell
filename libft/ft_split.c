/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbravo <jbravo@student.42urduliz.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 21:17:22 by jbravo            #+#    #+#             */
/*   Updated: 2022/12/19 01:44:33 by jbravo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;

	printf("\ninftsubstr  %s\nstart %u\n lenght %zu\n", s, start, len);
	start = (int)start;
	str = (char *)malloc(len * sizeof(char));
	if (!sizeof(str))
		return (NULL);
	str[--len] = '\0';
	while (len > 0)
	{
		len--;
		str[len] = s[--start];
	}
	return (str);
}

void	add_str(char **pstr, char const *s, size_t st, size_t len)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_substr(s, (st), len);
	while (pstr[i])
		i++;
	pstr[i] = str;
}

char	**ft_split(char const *s, char c)
{
	unsigned int	i;
	unsigned int	len;
	char			**psubstr;

	i = 0;
	len = 0;
	while (s[len])
	{
		if (s[len++] == c)
			i++;
	}
	psubstr = (char **)malloc(i * sizeof(char **));
	if (!sizeof(psubstr))
		return (NULL);
	len = 0;
	i = 0;
	while (s[i])
	{
		len++;
		if (s[i] == c && s[i + 1])
		{
			if (len > 1)
				add_str(psubstr, s, i, len);
			len = 0;
		}
		i++;
	}
	if (len != 0)
		add_str(psubstr, s, (i), len + 1);
	return (psubstr);
}

// int	main(void)
// {
// 	char ch = ' ';
// 	char *str = "El perro come         port fksdjof ffesw ";
// 	char **psubstr;
// 	psubstr = ft_split(str, ch);
// 	printf("%s\n%s\n%s\n%ste\n%s\n", psubstr[0], psubstr[1], psubstr[2],
// 			psubstr[3], psubstr[4]);

// 	return (0);
// }
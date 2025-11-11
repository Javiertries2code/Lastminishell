/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havr <havr@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 00:15:38 by havr              #+#    #+#             */
/*   Updated: 2025/11/11 14:12:42 by havr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

char	*ft_strnstr_quotes(const char *haystack, const char *needle, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	int				in_quotes;

	in_quotes = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	i = 0;
	while (haystack[i] && i < len)
	{
		in_quotes = check_quotes(in_quotes, haystack[i]);
		j = 0;
		if (haystack[i] == needle[j] && in_quotes == 0)
		{
			while (i + j < len && haystack[i + j] == needle[j])
			{
				j++;
				if (!needle[j])
					return ((char *)&haystack[i]);
			}
		}
		i++;
	}
	return (NULL);
}

void	reset_strinfo(t_strinfo *strinfo)
{
	if (strinfo)
	{
		strinfo->c = ' ';
		strinfo->pos = 0;
		strinfo->option_value = NULL;
		strinfo->advance = 1;
	}
}

char	*find_split(const char *s, t_strinfo *strinfo)
{
	unsigned int	i;
	int				in_quotes;
	char			*result;

	reset_strinfo(strinfo);
	in_quotes = 0;
	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		in_quotes = check_quotes(in_quotes, s[i]);
		if ((s[i] == '>' || s[i] == '<') && in_quotes == 0)
		{
			strinfo->pos = i;
			strinfo->c = s[i];
			handle_strinfo((char *)&s[i], strinfo);
			result = ft_substr(s, 0, i);
			return (result);
		}
		i++;
	}
	return (NULL);
}

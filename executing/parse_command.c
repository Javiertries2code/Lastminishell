
#include "../mini.h"

    static int	first_quote(char *str, char *quote)
    {
        int	i;

        i = 0;
        while (str[i])
        {
            if (str[i] == '\'' || str[i] == '"')
            {
                *quote = str[i];
                return (i);
            }
            i++;
        }
        return (-1);
    }

    static int	matching_quote(char *str, char quote, int len)
    {
        int	i;

        i = len - 1;
        while (i >= 0)
        {
            if (str[i] == quote)
                return (i);
            i--;
        }
        return (-1);
    }

    static char	*build_result(char *str, int start, int end, int len)
    {
        char	*before;
        char	*middle;
        char	*after;
        char	*temp;
        char	*result;

        before = ft_substr(str, 0, start);
        middle = ft_substr(str, start + 1, end - start - 1);
        after = ft_substr(str, end + 1, len - end - 1);
        temp = ft_strjoin(before, middle);
        result = ft_strjoin(temp, after);
        free(before);
        free(middle);
        free(after);
        free(temp);
        return (result);
    }

    char	*remove_outer_quotes(char *str)
    {
        int		start;
        int		end;
        int		len;
        char	quote;

        if (!str)
            return (NULL);
        len = ft_strlen(str);
        if (len < 2)
            return (ft_strdup(str));
        quote = 0;
        start = first_quote(str, &quote);
        if (start == -1)
            return (ft_strdup(str));
        end = matching_quote(str, quote, len);
        if (start == end || end == -1)
            return (ft_strdup(str));
        return (build_result(str, start, end, len));
    }

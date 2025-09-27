#include "../mini.h"

//CAN MAKE IT A WAY EASIER BY JOUST GOING FORWARD, REMOVING FIRST FOUND, AND THEN BACKWARDS WITH THAT SAME FOUND


char    *remove_outer_quotes(char *str)
{
    char *result;
    int len;
    int i, j;
    char quote_char;
    int quote_count;
    
    if (!str)
        return (NULL);
    
    len = strlen(str);
    if (len == 0)
        return (strdup(str));
    
    // Find the first quote
    quote_char = 0;
    for (i = 0; i < len; i++)
    {
        if (str[i] == '"' || str[i] == '\'')
        {
            quote_char = str[i];
            break;
        }
    }
    
    if (quote_char == 0)
        return (strdup(str));
    
    // Count quotes of the same type
    quote_count = 0;
    for (i = 0; i < len; i++)
    {
        if (str[i] == quote_char)
            quote_count++;
    }
    
    if (quote_count < 2)
        return (strdup(str));
    
    result = malloc(len - 1);
    if (!result)
        return (NULL);
    
    j = 0;
    int first_quote_removed = 0;
    int last_quote_pos = -1;
    
    // Find last occurrence of the quote
    for (i = len - 1; i >= 0; i--)
    {
        if (str[i] == quote_char)
        {
            last_quote_pos = i;
            break;
        }
    }
    
    for (i = 0; i < len; i++)
    {
        if (str[i] == quote_char && !first_quote_removed)
        {
            first_quote_removed = 1;
            continue;
        }
        if (str[i] == quote_char && i == last_quote_pos && first_quote_removed)
        {
            continue;
        }
        result[j++] = str[i];
    }
    result[j] = '\0';
    return (result);
}

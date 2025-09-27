 #include "../mini.h"


void __attribute__((unused)) print_list(t_env *list){

    t_env *tmp = list;
    while(tmp)
    {
        printf("%s = %s\n", tmp->key, tmp->value);
        tmp=tmp->next;
    } 
}

void __attribute__((unused)) print_tokens(t_data *data)
{
    int row = 0;
    
    if (!data || !data->tokens)
        return;
    
    while (data->tokens[row])
    {
        printf("\nRow %d:\n", row);
        t_token *current = data->tokens[row];
       
        
        while (current)
        {
           print_token_values(current);
           current = current->next;
        }
        row++;
    }
}

void __attribute__((unused)) print_token_values(t_token *token)
{
    if (!token)
        return;
    
    printf("\nToken values:\n");
    if (token->value)
    { 
        char *temp_unquoted = remove_outer_quotes(token->value);
        printf("\t\tvalue saved:\t%s\n", token->value);
        printf("\t\tval unquoted:\t%s\n", temp_unquoted);
        free(temp_unquoted);
    } 
        printf("\t\trow: %d\n", token->row);
        printf("\t\tpos: %d\n", token->pos);
    printf("\t\ttoken_op: %d\n", token->token_op);

}
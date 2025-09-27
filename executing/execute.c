#include "../mini.h"


/**
 * @brief Important, i am ponting from nre value, to word, so when freein memory, gotta keep it in mind
 * better just copy
 * 
 * passing i as to keep track of row
 * 
 * @param data 
 * @param i 
 * @param word 
 * @return t_token* 
 */
 static t_token  __attribute__((unused)) *add_token(t_data *data, int i, char *word){
(void) data; //while testing
(void) word; //while testing
(void) i; //while testing
t_token *new;
//new = check_head_empty(data, i);
new = ft_calloc(1, sizeof(t_token));
return new;
}

/**
 * @brief Adds a new token to the end of the linked list
 * 
 * @param data 
 * @param new 
 */
static void __attribute__((unused)) add_token_to_list(t_data *data, t_token *new) {

	
	int row = new->row;
	// If this is the first token in the row
	if (data->tokens[row] == NULL) {
		data->tokens[row] = new;
		new->next = NULL;
		new->prev = NULL;
	} else {
		// Find the last token in the list
		t_token *current = data->tokens[row];
		while (current->next != NULL) {
			current = current->next;
		}
		// Add new token at the end
		current->next = new;
		new->prev = current;
		new->next = NULL;
	}
}

/**
 * @brief Gets the whole line of command, splits in each every word respecting quotes, and send the  word
 * add_token() to be evaluated
 * 
 * @param data 
 * @param i 
 */
static void get_tokens(t_data *data, int j){
int i;
i = 0;

printf("linea commands[%d]-%s\n",j, data->commands[j]);

char **words = ft_split_quotes(data->commands[j], ' ');

while(words[i] != NULL)
{
parse_word(data,j, words[i]);
i++;
}


}
 t_token *new_empty_token(){
 t_token *new_token = ft_calloc(1, sizeof(t_token));
 if(new_token->prev == NULL)
	{new_token->pos = 0;
	new_token->token_op = UNDEFINED;
	}

 return new_token;
}

 void build_data_info( t_data *data){
int i;
i = 0;
data->command_set = ft_calloc(data->num_comands, sizeof(int ));
data->l_back = ft_calloc(data->num_comands, sizeof(int ));
data->l_ff = ft_calloc(data->num_comands, sizeof(int ));
data->l_for = ft_calloc(data->num_comands, sizeof(int ));
data->l_hd = ft_calloc(data->num_comands, sizeof(int ));


	while( i < data->num_comands)
		{
			data->tokens[i] = new_empty_token();
			data->tokens[i]->row =i;
			i++;
		}
		data->tokens[i] = NULL;

 }

/**
 * @brief builds the first element of the token list, as
 * to have where to start
 * 
 * @param data 
 */
void build_list_heads( t_data *data){
int i;
i = 0;
data->tokens = ft_calloc(data->num_comands +1, sizeof(t_token *));

	while( i < data->num_comands)
		{
			data->tokens[i] = new_empty_token();
			data->tokens[i]->row =i;
			i++;
		}
		data->tokens[i] = NULL;

};
/**
 * @brief
 * creates the heads, and for every lone of commands, calls get tokens to load the list
 * 
 * @param data 
 */
void tokenize( t_data *data){
int i;
i = 0;
 build_list_heads(data);
 build_data_info(data);
	while(i < data->num_comands)
		{
			get_tokens(data, i);
			i++;
		}


};



// void execute(t_data *data, int i){



// }


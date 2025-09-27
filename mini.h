#ifndef MINI_H
# define MINI_H

# include "./libft/libft.h"
# include <errno.h> // errno
# include <fcntl.h> // open
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h> // signal, sigaction, kill
# include <signal.h> // to handle signals
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>     // perror, printf (aunque mejor usar dprintf)
# include <stdlib.h>    // malloc, free, exit, getenv
# include <string.h>    // strcmp, strdup, strtok, strlen, etc.
# include <sys/types.h> // pid_t, wait
# include <sys/types.h>
# include <sys/wait.h> // wait, waitpid
# include <termios.h>  // para controlar terminal
# include <unistd.h>   // fork, execve, pipe, dup, dup2, read, write, close

static volatile int		SIG = 0;

# define DEBUG 1
/**

	* @brief Markers (non printable) as to get the env variables apart from each other if those are
 * expanded without any spaceinbetween
 *
 */

# define VAR_START_MARKER "\x02"
# define VAR_END_MARKER "\x03"
# define VAR_ST_CH_MARKER '\x02'
# define VAR_END_CH_MARKER '\x03'

typedef struct s_data	t_data;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef enum e_token_op
{
	STRING,
	RED_FORWD,  // >
	RED_BACKWD, // <
	APPEND,     // >>
	HEREDOC,    // <<
	BUILTIN,
	COMMAND,
	UNDEFINED,

}						t_token_op;

typedef struct s_strinfo
{
	size_t				advance;
	// advancing 1 or 2 depending on the redireccion option
	size_t pos;                // pos of the firt found occurrence,
								// so to make the subtring
	unsigned int next_str_pos; // pointer to what will be the next
	char *option_value;        // the option word to be saved in the token
	t_token_op token_op;       // type of token, obvious
	char				*new_str;
	char c; // chararacter found
}						t_strinfo;

/**
 * @brief token values, it got a bidireccional linked list
 *
 * it keeps a pointer to all data.
 *
 */
typedef struct s_token
{
	t_token_op			token_op;
	struct s_token		*arg;

	char				*value;
	struct s_token		*next;
	struct s_token		*prev;
	int					**l_for;
	int					**l_back;
	int					**l_ff;
	int					**l_hd;
	struct s_token		*arg_red_back;

	int *pipe_in; // pointer to commom fd (either pipe or redirections)
	int					*pipe_out;
	int					pos;
	int					row;
	struct s_env		*env;
	t_data				*data;
}						t_token;

typedef struct s_data
{
	char				*str;
	t_token				**tokens;
	char				**commands;
	// char			**expanded;
	t_env				*env_head;
	int					tmp_var_len;
	char				*tmp_var_name;
	char				*tmp_var_expanded;
	int					num_comands;
	// usefull info for token
	int					p_pipe_in;
	int					p_pipe_out;
	int					nxt_pipe_out;
	int					nxt_pipe_in;

	int					*l_for;
	int					*l_back;
	int					*l_ff;
	int					*l_hd;
	bool				*command_set;
}						t_data;

// functions to copy env and lexer
char					**ft_split_quotes(const char *s, char c);
char					*ft_strnstr_quotes(const char *haystack,
							const char *needle, size_t len);

char					**ft_split(const char *s, char c);
void					*ft_calloc(size_t count, size_t size);
void					copy_env(t_env *env_head, char **envp);
size_t					ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t					ft_strlen(const char *s);
char					check_quotes(char quotes, char c);
void					expand_var(int i, t_data *data);
void					data_find_var(char *str, int quotes, t_data *data);
char					*data_substitute_var(char *str, t_data *data,
							int quotes, int i);

void					free_null_vars(char *str, t_data *data);

// errors
void					check_initial_errors(t_data *data, char *line);
int						check_pipes_reds(t_token *current);
void					command_errors(t_data *data);
bool					check_comands(t_data *data, t_token *token);

// parser
int						quotes_balanced(char *str);
char					*remove_outer_quotes(char *str);
void					handle_strinfo(char *s, t_strinfo *strinfo);
char					*find_split(const char *s, t_strinfo *strinfo);
int						parse_word(t_data *data, int row, char *word);

// exexution
void					execute(t_data *data, int i);

// error handling and cleanup
int						exit_with_error(t_data *data, char *error_msg);
void					free_all_data(t_data *data);

// legacy functions for compatibility
void					parse_input(void);

// freeing utilities
void					free_split(char **arr);
void					free_str_array(char **arr);
void					free_str_safe(char **str);
void					free_null(char *str);

// support
void					print_list(t_env *list);
void					print_tokens(t_data *data);
void					print_token_values(t_token *token);

// tokenize
int						parse_word(t_data *data, int row, char *word);
void					tokenize(t_data *data);
void					build_list_heads(t_data *data);
t_token					*new_empty_token(void);
t_token					*check_head_empty(t_data *data, int i);
void					create_token(t_data *data, int row, char *word,
							t_token_op token);
int						eval_red(t_data *data, t_token *token, char *word);
bool					eval_builtin(t_data *data, t_token *token, char *word);
bool					check_prev(t_data *data, t_token *token, char *word);
bool					eval_command(t_data *data, t_token *token, char *word);
void					load_data(t_data *data, int row, char *word,
							t_token_op token_op);
void					reassign_value(char **old, char *new);

#endif
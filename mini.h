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

# ifndef SYNTAX_ERR
#  define SYNTAX_ERR "syntax error near unexpected token"
# endif

# ifndef NO_SUCH
#  define NO_SUCH "No such file or directory"
# endif
extern int				sig;

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

typedef enum e_red_checck
{
	ALL,
	NO_HEREDOC,
	LEFT_RIGHT,

}						t_red_checck;

typedef enum e_type_error
{
	OK_SYNTAX,
	WRONG_SYNTAX,

}						t_type_error;
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
	BINARY,

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
	t_env				*env_expr;
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
char					*data_substitute_var(char *str, t_data *data, int i);

void					free_null_vars(char *str, t_data *data);

// errors
int						check_initial_errors(t_data *data, char *line);
int						check_pipes_reds(t_token *current);
int						command_errors(t_data *data);
// bool					check_tokens_comands(t_data *data, t_token *token);
int						return_error(int i, char *caller, t_data *data);

// parser
int						quotes_balanced(char *str);
char					*remove_outer_quotes(char *str);
void					handle_strinfo(char *s, t_strinfo *strinfo);
char					*find_split(const char *s, t_strinfo *strinfo);
int						parse_word(t_data *data, int row, char *word);
size_t					get_len(const char *s, char c);
char					*new_str_key(const char *s, char c);
char					*new_str_value(const char *s, char c);
char					**ft_split_env(const char *s, char c);
int						ft_var_len(const char *s, char quotes);
int						is_space(char c);
int						is_valid_char(char c);
char					*ft_struntil(const char *s, char quotes);
size_t					counter(const char *s, char c);

// exexution
void					execute(t_data *data, int i);
int						assign_sig(int code);

// signals
void					set_handlers(void);

// error handling and cleanup
int						exit_with_error(t_data *data, char *error_msg);
int						exit_with_token_error(t_data *data, t_token *tok,
							char *error_msg);
int						token_with_error(char *error_msg, char *value);
int						token_with_no_path(char *value);
void					free_all_data(t_data *data, int sig);
void					free_split(char **command);
void					free_split_tripoint(char ***command);

void					free_null_void(void **ptr);

void					free_command_info(t_data *data, int code);

// error control
bool					empty(char **line, t_data *data);

int						check_tokens_comands(t_data *data, t_token *token);
int						check_pipes_reds(t_token *current);

// legacy functions for compatibility
void					parse_input(void);

// freeing utilities
void					free_str_safe(char **str);
void					free_null(char **str);
void					free_tokens(t_token **tokens);
void					free_all_tokens(t_data *data);

// support
void					print_list(t_env *list);
void					print_tokens(t_data *data);
void					print_token_values(t_token *token);

// just print
void					print(char *str);
void					ft_putstr(char *str);
void					print_debug(char *str);

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
bool					is_binary(t_data *data, t_token *token, char *word);

// management

typedef struct s_symbols
{
	int					forwd;
	int					backwd;
	int					append;
	int					heredoc;
}						t_symbols;

void					free_exec_resources(char *cmd_path, char **cmd_arg,
							char **all_env);
char					**list_cmd_arg(t_token *list);
char					**join_all_envp(t_env *env);
char					*get_cmd_path(t_env *env, char *cmd);

int						env_len(t_env *env);
int						args_len(t_token *list);
int						check_redirs(t_token *list);

int						pipex(t_token **list, t_data *data, int current,
							int prev_pipe);

void					manage_mini(t_token **list, t_data *data);

int						create_redir(t_token *list);
t_symbols				count_symbols(t_token *list);
t_token					*get_cmd_from_list(t_token *list);
int						execute_execve(t_token *list, t_data *data);

void					setcmd(t_token ***list, t_data *data);
t_token_op				is_builtin(char *cmd);

// Builtins
int						builtin_manager(t_token *list, t_data *data);
int						ft_echo(t_token *list);
int						ft_pwd(void);
int						ft_env(t_data *data);
int						ft_unset(t_token *list, t_data *data);
int						ft_cd(t_token *list);
int						ft_export(t_token *list, t_data *data);
int						ft_exit(t_data *data);
void					add_export_env(t_env **head, char *argval);
void					free_env_cpy(t_env *nhead);
t_env					*make_env_cpy(t_env *orig);
void					add_env_element(t_env *env_head, char *envp);
bool					cut_add_env(char ***split, t_env **new_element,
							char **envp);

#endif
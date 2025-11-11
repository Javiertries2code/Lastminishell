NAME := minishell

# Directorios
DIR_LEXER := lexer/
DIR_HANDLERS := handlers/
DIR_PARSERS := parsers/
DIR_EXITING := exiting/
DIR_SUPPORT := support/
DIR_EXECUTING := executing/
DIR_MANAGE := management/
DIR_BUILTINS := builtins/

# Archivos fuente
LEXER_FILES = copy_env.c kloc.c lexer.c main.c split_quotes.c expand_var.c expand_var_ext.c copy_env_ext.c 
HANDLERS_FILES = set_handlers.c
PARSERS_FILES = parser.c split.c strinfo.c token_creator.c eval_words.c eval_ext.c token_creator_ext.c
EXITING_FILES = exiting.c errors.c input_errors.c exiting_ext.c
SUPPORT_FILES = support.c
EXECUTING_FILES = execute.c execute_ext.c parse_command.c
MANAGE_FILES = execve_resources.c manage_aux.c manage.c pipes.c redirs.c redirs_aux.c manage_errors.c manage_aux2.c builtin.c pipes_manager.c pipes_aux.c heredoc_aux.c
BUILTINS_FILES = echo.c cd.c env.c exit.c export.c pwd.c unset.c export_aux.c export_aux2.c export_aux3.c builtin_aux.c aux.c

LEXER := $(addprefix $(DIR_LEXER), $(LEXER_FILES))
HANDLERS := $(addprefix $(DIR_HANDLERS), $(HANDLERS_FILES))
PARSERS := $(addprefix $(DIR_PARSERS), $(PARSERS_FILES))
EXITING := $(addprefix $(DIR_EXITING), $(EXITING_FILES))
SUPPORT := $(addprefix $(DIR_SUPPORT), $(SUPPORT_FILES))
EXECUTING := $(addprefix $(DIR_EXECUTING), $(EXECUTING_FILES))
MANAGEMENT := $(addprefix $(DIR_MANAGE), $(MANAGE_FILES))
BUILTINS := $(addprefix $(DIR_BUILTINS), $(BUILTINS_FILES))

SRC := $(LEXER) $(HANDLERS) $(PARSERS) $(EXITING) $(SUPPORT) $(EXECUTING) $(MANAGEMENT) $(BUILTINS)
OBJECTS := $(SRC:.c=.o)

# Libft
LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a
INCLUDES = -I$(LIBFT_DIR)

# Compilador
CC = cc
CFLAGS = -Wall -Wextra  $(INCLUDES)  #-Werror

ifeq ($(DEBUG), 1)
	CFLAGS += -g -O0
endif

all: $(LIBFT_A) $(NAME)

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIBFT_A) -lreadline

clean:
	rm -f $(OBJECTS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

debug_leaks:
	$(MAKE) fclean
	$(MAKE) DEBUG=1
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) $(ARGS)

debug_races:
	$(MAKE) fclean
	$(MAKE) DEBUG=1
	valgrind --tool=helgrind --tool=drd ./$(NAME) $(ARGS)

.PHONY: all clean fclean re debug_leaks debug_races


NAME := minishell

# Directorios
DIR_LEXER := lexer/
DIR_HANDLERS := handlers/
DIR_PARSERS := parsers/
DIR_EXITING := exiting/
DIR_SUPPORT := support/
DIR_EXECUTING :=executing/

# Archivos fuente
LEXER_FILES = copy_env.c kloc.c lexer.c main.c split_quotes.c expand_var.c
HANDLERS_FILES = handler.c
PARSERS_FILES = parser.c split.c strinfo.c token_creator.c eval_words.c
EXITING_FILES = exiting.c errors.c input_errors.c
SUPPORT_FILES = support.c
EXECUTING_FILES = execute.c parse_command.c

LEXER := $(addprefix $(DIR_LEXER), $(LEXER_FILES))
HANDLERS := $(addprefix $(DIR_HANDLERS), $(HANDLERS_FILES))
PARSERS := $(addprefix $(DIR_PARSERS), $(PARSERS_FILES))
EXITING := $(addprefix $(DIR_EXITING), $(EXITING_FILES))
SUPPORT := $(addprefix $(DIR_SUPPORT), $(SUPPORT_FILES))
EXECUTING := $(addprefix $(DIR_EXECUTING), $(EXECUTING_FILES))

SRC := $(LEXER) $(HANDLERS) $(PARSERS) $(EXITING) $(SUPPORT) $(EXECUTING)
OBJECTS := $(SRC:.c=.o)

# Libft
LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a
INCLUDES = -I$(LIBFT_DIR)

# Compilador
CC = cc
CFLAGS = -Wall -Wextra -Werror $(INCLUDES)

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
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(NAME) $(ARGS)

debug_races:
	$(MAKE) fclean
	$(MAKE) DEBUG=1
	valgrind --tool=helgrind --tool=drd ./$(NAME) $(ARGS)

.PHONY: all clean fclean re debug_leaks debug_races


NAME = libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SOURCE = $(shell find . -name "*.c")

OBJ = $(SOURCE:.c=.o)

LIB = ar rc $(NAME)

RANLIB = ranlib $(NAME)

RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
    @$(CC) $(CFLAGS) -c $(SOURCE)
    @$(LIB) $(OBJ)
    @$(RANLIB) $(NAME)

clean:
    @$(RM) $(OBJ)

fclean: clean
        @$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

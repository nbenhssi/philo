NAME = philo

CC = cc 

CFLAGS = -Wall -Wextra -Werror 

RM = rm -f

SRC = 	philo.c \
		libft.c \
		init.c \
		utils.c

OBJ	=$(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all
.PHONY: clean

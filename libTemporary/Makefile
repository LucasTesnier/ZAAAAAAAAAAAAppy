##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## makefile
##

SRC     =   src/temporary_lib.c

OBJ     =	$(SRC:.c=.o)

NAME    =	libzappy_ai_api.so

LDFLAGS	= -shared -lm

CFLAGS	=	-Wall -Werror -Wextra -Wshadow -fPIC -I includes

CC	=	gcc

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean  all

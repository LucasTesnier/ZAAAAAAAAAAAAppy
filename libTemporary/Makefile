##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## makefile
##

SRC     =   src/temporary_lib.c

OBJ     =	$(SRC:.c=.o)

NAME    =	libmy_temporary.so

LDFLAGS	= -shared -lm

CFLAGS	=	-Wall -Werror -Wextra -Wshadow -fPIC

CC	=	gcc

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean  all

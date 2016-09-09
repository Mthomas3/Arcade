##
## Makefile for  in /home/mart_4/rendu/cpp_arcade/lib_games
##
## Made by Thomas Martins
## Login   <mart_4@epitech.net>
##
## Started on  Mon Mar 28 13:51:43 2016 Thomas Martins
## Last update Mon Mar 28 16:30:23 2016 Nicolas Gascon
##

SRC = 	src/Snake.cpp\
	src/Mouli.cpp\
	src/Factory.cpp

OBJ = $(SRC:.cpp=.o)

NAME  = ../../games/lib_snake_games.so

RM = rm -f

CFLAGS	+= -fPIC -std=c++11
LDFLAGS	+= -shared

CC = g++

all: $(NAME)

$(NAME): $(OBJ)
	mkdir -p ../../games
	$(CC) -o $(NAME) $(LDFLAGS) $(OBJ)

%.o : %.cpp
	$(CC) -c $(CFLAGS) -o $@ $^

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

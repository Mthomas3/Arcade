##
## Makefile for  in /home/mart_4/rendu/cpp_arcade/lib_games
##
## Made by Thomas Martins
## Login   <mart_4@epitech.net>
##
## Started on  Mon Mar 28 13:51:43 2016 Thomas Martins
## Last update Mon Apr 11 11:13:46 2016 Thomas Martins
##

SRC = 	src/ArcadeCurses.cpp\

OBJ = $(SRC:.cpp=.o)

NAME  = ../../lib/lib_arcade_ncurses.so

RM = rm -f

INC_DIR = ../../include

CFLAGS	+= -fPIC -std=c++11 -I$(INC_DIR)
LDFLAGS	+= -shared

CC = g++

all: $(NAME)

$(NAME): $(OBJ)
	mkdir -p ../../lib
	$(CC) -o $(NAME) $(LDFLAGS) $(OBJ) -lncursesw

%.o : %.cpp
	$(CC) -c $(CFLAGS) -o $@ $^

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

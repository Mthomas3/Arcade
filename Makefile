##
## Makefile for  in /home/mart_4/rendu/new_cpp/cpp_arcade
##
## Made by Thomas Martins
## Login   <mart_4@epitech.net>
##
## Started on  Mon Mar 28 15:26:21 2016 Thomas Martins
## Last update Tue May  3 19:32:27 2016 Thomas Martins
##

SRC = 	main.cpp\
	src/Core/Core.cpp \
	src/Core/Time.cpp

OBJ = $(SRC:.cpp=.o)

NAME  = arcade

RM = rm -f

INC_DIR = include

CFLAGS	+= -fPIC -std=c++11 -I$(INC_DIR)

CC = g++

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) -ldl
	make -C lib_games/snake
	make -C lib_games/pacman
	make -C lib_arcade/sfml
	make -C lib_arcade/lncurses
	make -C lib_arcade/ogre

%.o : %.cpp
	$(CC) -c $(CFLAGS) -o $@ $^

Ogre:
	make -C lib_arcade/ogre

clean:
	$(RM) $(OBJ)
	make -C lib_games/snake clean
	make -C lib_games/pacman clean
	make -C lib_arcade/sfml clean
	make -C lib_arcade/lncurses clean
	make -C lib_arcade/ogre clean

fclean: clean
	$(RM) $(NAME)
	make -C lib_games/snake fclean
	make -C lib_games/pacman fclean
	make -C lib_arcade/sfml fclean
	make -C lib_arcade/lncurses fclean
	make -C lib_arcade/ogre fclean

re: fclean all

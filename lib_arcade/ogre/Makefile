##
## Makefile for  in /home/mart_4/rendu/cpp_arcade/lib_games
##
## Made by Thomas Martins
## Login   <mart_4@epitech.net>
##
## Started on  Mon Mar 28 13:51:43 2016 Thomas Martins
## Last update Wed Mar 30 14:32:39 2016 Nicolas Gascon
##

SRC = 	src/ArcadeOgre.cpp \
	src/Factory.cpp

OBJ = $(SRC:.cpp=.o)

NAME  = ../../lib/lib_arcade_ogre.so

RM = rm -f

INC_DIR = ../../include

CFLAGS	+= -fPIC -std=c++11 -I$(INC_DIR) -I$(INC_DIR)/Ogre
LDFLAGS	+= -shared

CC = g++

all: $(NAME)

$(NAME): $(OBJ)
	mkdir -p ../../lib
	$(CC) -o $(NAME) $(LDFLAGS) $(OBJ) -L../../lib -lOgreMain -lOIS

%.o : %.cpp
	$(CC) -c $(CFLAGS) -o $@ $^ -L../../lib -lOgreMain -lOIS

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

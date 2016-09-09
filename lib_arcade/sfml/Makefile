##
## Makefile for  in /home/mart_4/rendu/cpp_arcade/lib_games
##
## Made by Thomas Martins
## Login   <mart_4@epitech.net>
##
## Started on  Mon Mar 28 13:51:43 2016 Thomas Martins
## Last update Tue Mar 29 08:48:33 2016 Nicolas Gascon
##

SRC = 	src/ArcadeSFML.cpp \
	src/Factory.cpp \
	src/ShapeFactory.cpp

OBJ = $(SRC:.cpp=.o)

NAME  = ../../lib/lib_arcade_sfml.so

RM = rm -f

INC_DIR = ../../include

CFLAGS	+= -fPIC -std=c++11 -I$(INC_DIR)
LDFLAGS	+= -shared

CC = g++

all: $(NAME)

$(NAME): $(OBJ)
	mkdir -p ../../lib
	$(CC) -o $(NAME) $(LDFLAGS) $(OBJ) -L../../lib -lsfml-window -lsfml-graphics -lsfml-system

%.o : %.cpp
	$(CC) -c $(CFLAGS) -o $@ $^ -L../../lib -lsfml-window -lsfml-graphics -lsfml-system

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

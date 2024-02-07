# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/04 12:42:33 by lzipp             #+#    #+#              #
#    Updated: 2024/02/07 14:18:07 by lzipp            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo

CC := cc
CFLAGS := -Wextra -Wall -Werror
# DBFLAGS := $(CFLAGS) -fsanitize=address

SOURCES := $(addprefix src/, create_data.c create_forks.c create_philos.c \
helpers.c main.c messages.c philo_routine.c philosophize.c)
OBJECTS := $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(NAME)
	
# memcheck: $(SOURCES)
# 	$(CC) $(DBFLAGS) $(SOURCES) -o $(NAME)

clean:
	rm -f $(OBJECTS)
	
fclean: clean
	rm -f $(NAME)

re: fclean all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re

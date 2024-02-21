# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/04 12:42:33 by lzipp             #+#    #+#              #
#    Updated: 2024/02/21 11:56:30 by lzipp            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo

CC := cc
CFLAGS := -Wextra -Wall -Werror -pthread

SOURCES := $(addprefix src/, create_data.c create_forks.c create_philos.c \
free_functions.c helpers.c main.c messages.c monitor_routine.c philo_routine.c \
philosophize.c)
OBJECTS := $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

clean:
	rm -f $(OBJECTS)
	
fclean: clean
	rm -f $(NAME)

re: fclean all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re

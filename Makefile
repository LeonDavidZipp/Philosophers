# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lzipp <lzipp@student.42heilbronn.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/04 12:42:33 by lzipp             #+#    #+#              #
#    Updated: 2024/02/04 14:49:09 by lzipp            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo

CC := cc
CFLAGS = -Wextra -Wall -Werror

SOURCES = $(addprefix src/, \
input_parsing.c \
messages.c \
main.c) 
OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	ar -rc $(NAME) $(OBJECTS)

clean:
	rm -f $(OBJECTS) $(BONUS_OBJECTS)
	
fclean: clean
	rm -f $(NAME)

re: fclean all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re
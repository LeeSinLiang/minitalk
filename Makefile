# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sinlee <sinlee@student42.fr>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/02 08:15:57 by sinlee            #+#    #+#              #
#    Updated: 2023/06/02 17:06:00 by sinlee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = server client

SRCS = client.c server.c

FTPRINTFDIR = ./ft_printf/
FTPRINTF = ./ft_printf/libftprintf.a

RM = rm -rf

all: ${NAME}

bonus: ${NAME}

server: server.c ${FTPRINTF}
	@$(CC) $(CFLAGS) server.c -I ft_printf/include -I ft_printf/libft ${FTPRINTF} -o server 

client: client.c ${FTPRINTF}
	@$(CC) $(CFLAGS) client.c -I ft_printf/include -I ft_printf/libft ${FTPRINTF} -o client

${FTPRINTF}:
	@make all -C ${FTPRINTFDIR}
	@make clean -C ${FTPRINTFDIR}

clean: 
	@make -C ./ft_printf clean

fclean: clean
	@make -C ./ft_printf fclean
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
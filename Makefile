# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/22 15:27:44 by jmatheis          #+#    #+#              #
#    Updated: 2023/01/08 15:35:16 by amechain         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Werror -Wextra -pthread

NAME =  philo

M_SRC = main.c \
		philosophers.c \
		end_sim.c \
		error_free.c \
		init.c \
		parsing.c \
		supervisor.c \
		one_philos.c \
		utils.c \
		utils2.c \
		ft_split.c

M_SRCS = $(addprefix ./sources/, $(M_SRC))

M_OBJS = $(M_SRCS:.c=.o)

all: $(NAME)

bonus : $(BONUS)

$(NAME): $(M_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(M_OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

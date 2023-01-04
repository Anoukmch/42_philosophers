# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anoukmechain <anoukmechain@student.42.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/22 15:27:44 by jmatheis          #+#    #+#              #
#    Updated: 2023/01/03 17:36:24 by anoukmechai      ###   ########.fr        #
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
		utils.c 
		
M_SRCS = $(addprefix ./sources/, $(M_SRC))

M_OBJS = $(M_SRCS:.c=.o)

LIBS_DIR = ./includes/libs

LIBS_NAME = libs.a

all: $(NAME)

bonus : $(BONUS)

$(NAME): $(M_OBJS) $(LIBS_DIR)/$(LIBS_NAME)
	$(CC) $(CFLAGS) $^ -o $@ 

$(LIBS_DIR)/$(LIBS_NAME):
	make -sC $(LIBS_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C $(LIBS_DIR)
	@rm -f $(M_OBJS)

fclean: clean
	make fclean -C $(LIBS_DIR)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/16 10:00:00 by                   #+#    #+#              #
#    Updated: 2025/02/16 14:37:05 by jbrol-ca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

SRCS		= main.c init.c philo_actions.c utils.c monitor.c

OBJS		= $(SRCS:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -pthread

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
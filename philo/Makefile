.DEFAULT_GOAL := all

NAME	= philo

CC		= cc
CFLAGS	= -Wall -Wextra -Werror # -g -fsanitize=thread

ifdef DEBUG_FLAG
	CFLAGS += -g -fsanitize=address
endif
# -g -fsanitize=thread
# -g -fsanitize=address
#INC		= philo.h

SRCS	= main.c \
	ft_function.c utils.c init.c thread_philo.c thread_utils.c solo_philo.c monitoring.c make_philo.c

OBJS	= $(SRCS:.c=.o)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(NAME) 
#-I $(INC)

all : $(NAME)

clean :
	rm -f $(OBJS)

fclean :
	rm -f $(OBJS) $(NAME)

re :
	make fclean
	make all

.PHONY : all bonus clean fclean re
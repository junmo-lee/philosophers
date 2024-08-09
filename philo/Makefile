.DEFAULT_GOAL := all

NAME	= philo

CC		= cc
CFLAGS	= -Wall -Wextra -Werror  -g3 # -fsanitize=thread

ifdef DEBUG_FLAG
	CFLAGS += -g -fsanitize=address
endif
# -g -fsanitize=thread
# -g -fsanitize=leak
#INC		= philo.h

SRCS	= main.c \
	atoi_check_num.c ft_function.c utils.c init.c thread_philo.c

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
NAME = philosopher
NAME_B = philo_bonus
SRCS = $(wildcard mandatory/*.c)
SRCS_B = $(wildcard philo_bonus/*.c)

HEADER = mandatory/philo.h
HEADER_B = philo_bonus/philo.h

RM = rm
FLAGS = -Werror -Wall -Wextra

OBJS = $(SRCS:.c=.o)
OBJS_B = $(SRCS_B:.c=.o)

$(NAME) : $(OBJS) $(HEADER)
	gcc $(OBJS) -o $(NAME)

$(NAME_B) : $(OBJS_B) $(HEADER_B)
	gcc $(OBJS_B) -o $(NAME_B)

%.o : %.c
	gcc $(FLAGS) -o $@ -c $< -g

all : $(NAME)

bonus : $(NAME_B)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: clean all
.PHONY: clean fclean all bonus

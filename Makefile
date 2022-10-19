NAME = philo
NAME_B = philo_bonus
SRCS = $(wildcard mandatory/*.c)
SRCS_B = $(wildcard bonus/*.c)

HEADER = mandatory/philo.h
HEADER_B = bonus/philo_bonus.h
RM = rm -f
FLAGS = -Werror -Wall -Wextra

OBJS = $(SRCS:.c=.o)
OBJS_B = $(SRCS_B:.c=.o)	

$(NAME) : $(OBJS) $(HEADER)
	gcc $(OBJS) -o $(NAME)

$(NAME_B) : $(OBJS_B) $(HEADER_B)
	gcc $(OBJS_B) -o $(NAME_B)

%.o : %.c
	gcc $(FLAGS) -o $@ -c $<

all : $(NAME)

bonus : $(NAME_B)

clean:
	$(RM) $(OBJS) $(OBJS_B)

fclean: clean
	$(RM) $(NAME) $(NAME_B)

re: fclean all

.PHONY: clean fclean all re

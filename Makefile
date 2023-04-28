CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -pthread -g3 -fsanitize=address
RM			= rm -f
SRCD		= ./src/
SRC			= utils.c main.c init.c philo.c
SRCF		= $(addprefix $(SRCD),$(SRC))
OBJD		= ./objs/
OBJF		= $(SRCF:$(SRCD)%.c=$(OBJD)%.o)
BUILD		= $(OBJF:$(OBJD)%.o)

NAME		= philo
HEADD		= ./inc/
HEADF		= philo.h


$(OBJD)%.o: $(SRCD)%.c
	@mkdir -p $(OBJD)
	$(CC) $(CFLAGS) -I ${HEADD} -c -o $@ $<

$(NAME):	${OBJF}
			$(CC) $(CFLAGS) $(SRCF) -o $(NAME) $(HEADD)$(HEADF)

all:		${NAME}

clean:
			${RM} ${OBJF}

fclean:		clean
			${RM} ${NAME}
			${RM} ${HEADD}philo.h.gch

re:			fclean all

.PHONY:		all clean fclean re

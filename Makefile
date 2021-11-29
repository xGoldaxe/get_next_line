SRCS	=	get_next_line.c get_next_line_utils.c

BONUSSRCS	=	

HEADERS	= 

OBJS	= ${SRCS:.c=.o}

BONUSOBJS	= ${BONUSSRCS:.c=.o}

NAME	= get-next-line.a

CC		= gcc

LIBC	= ar -rc

RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror


%.o:		%.c	
				${CC} ${CFLAGS} -I. -o $@ -c $? 

${NAME}:	${OBJS}
				${LIBC} ${NAME} ${OBJS}
				@echo 'Libft compiled succcessfully'

bonus:	${BONUSOBJS}
				${LIBC} ${NAME} ${BONUSOBJS}
				@echo 'Bonus well added'

all:		${NAME}
				@echo '✔️✔️✔️[ALL] - libft with bonus has been created!✔️✔️✔️'

clean:
				${RM} ${OBJS} ${BONUSOBJS}
				@echo '✔️✔️✔️[clean] - folder is now clean!✔️✔️✔️'

fclean:		clean
					${RM} ${NAME}
					@echo '✔️✔️✔️[fclean] - folder is now clean!✔️✔️✔️'

re:				fclean all

PHONY:		all clean fclean re
NAME	= pipex

SDIR	= src
ODIR	= obj
LDIR	= libft

SRCS_P	= pipex.c

SRCS_B	= pipex_bonus.c

SRCS_U	= pipex_utils.c

SRCS_L	= ft_strlen.c ft_strslen.c ft_strjoin.c ft_split.c ft_substr.c ft_freestrs.c \
		  ft_open.c ft_print_error.c ft_freestrarrs.c \
		  ft_strchr.c ft_strdup.c ft_strncmp.c ft_strtrimchr.c ft_strupdate.c

OBJS_P	= ${addprefix ${ODIR}/, ${SRCS_P:.c=.o}}

OBJS_B	= ${addprefix ${ODIR}/, ${SRCS_B:.c=.o}}

OBJS_U	= ${addprefix ${ODIR}/, ${SRCS_U:.c=.o}}

OBJS_L	= ${addprefix ${LDIR}/, ${SRCS_L:.c=.o}}

GCC		= gcc
RM		= rm -f

LIBFT	= libft.a

CFLAGS	= -Wall -Wextra -Werror

all:	${NAME}

${ODIR}/%.o:	${SDIR}/%.c
	${GCC} ${CFLAGS} -c $< -o $@

${LIBFT}:
	make re -C ${LDIR}

${NAME}:	${LIBFT} ${OBJS_P} ${OBJS_U} ${OBJS_L}
	${GCC} -o ${NAME} ${OBJS_P} ${OBJS_U} ${LDIR}/${LIBFT}

bonus:	${LIBFT} ${OBJS_B} ${OBJS_U} ${OBJS_L}
	${GCC} -o ${NAME} ${OBJS_B} ${OBJS_U} ${LDIR}/${LIBFT}

clean:
	${RM} ${OBJS_P} ${OBJS_B} ${OBJS_U}
	make clean -C ${LDIR}

fclean:
	${RM} ${NAME}
	${RM} ${OBJS_P} ${OBJS_B} ${OBJS_U}
	make fclean -C ${LDIR}

re:	fclean all

.PHONY:	all bonus clean fclean re
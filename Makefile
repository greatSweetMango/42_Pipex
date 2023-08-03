NAME		= pipex

LIBFT		= libft
LIBS		= libs

INCLUDE    	= include
INCLUDE_BN	= include_bonus

MANDATORYDIR= mandatory/
BONUSDIR	= bonus/

CC			= gcc
CFLAGS		= -g -Wall -Werror -Wextra
FWS			= -framework OpenGL -framework AppKit
RM			= rm -rf
AR			= ar rcs

FILES 		= pipex.c \
				pipex_util.c \
				task_error.c

FILES_BN	= pipex_bonus.c \
				pipex_util_bonus.c \
				task_error_bonus.c

SRCS		= $(addprefix $(MANDATORYDIR), $(FILES))
SRCS_BN		= $(addprefix $(BONUSDIR), $(FILES_BN))

OBJS		= $(SRCS:.c=.o)
OBJS_BN		= $(SRCS_BN:.c=.o)

$(MANDATORYDIR)%.o: $(MANDATORYDIR)%.c
			$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDE)

$(BONUSDIR)%.o: $(BONUSDIR)%.c
			$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDE_BN)

all		: $(NAME)

bonus	: $(NAME)

ifeq ($(MAKECMDGOALS), bonus)
$(NAME) : $(OBJS_BN)
			make -C $(LIBFT)
			cp libft/libft.a $(LIBS)
			$(CC) $(CFLAGS) $(OBJS_BN) -o $(NAME) -L$(LIBS) -lft -I $(INCLUDE_BN)
else
$(NAME) : $(OBJS)
			make -C $(LIBFT)
			cp libft/libft.a $(LIBS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(LIBS) -lft -I $(INCLUDE)
endif

clean	:
			$(RM) $(OBJS) $(OBJS_BN)
			make clean -C $(LIBFT)

fclean	: clean
			$(RM) $(NAME) $(NAME_BN)
			$(RM) $(LIBFT)/libft.a
			$(RM) $(LIBS)/*

re		: fclean all

rebn	: fclean
			$(MAKE) bonus

.PHONY:		all clean fclean re rebn
NAME	=	fractol

SRCS	=	main.c \
			events.c \
			draw_1.c \
			draw_2.c \
			init.c \
			utils.c

OBJS	=	$(SRCS:.c=.o)

INCLUDES	=	fractol.h \
				mlx.h

CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra -O3
MLXFLAGS	=	-lmlx -framework OpenGL -framework AppKit

$(NAME)	:	$(OBJS)
			$(CC) $(CFLAGS) $(MLXFLAGS) $(OBJS) -o $(NAME)

all		:	$(NAME)

clean	:
			rm -f $(OBJS)

fclean	:	clean
			rm -f $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re

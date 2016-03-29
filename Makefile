CC      =	gcc
CFLAGS  =	-Wall -Wextra -Werror
NAME    =	ft_ls
INCLUDE =	include libft/include
SRCS    =	main.c

vpath %.o objs

help:
	@echo "+------------+"
	@echo "| all        |"
	@echo "| clean      |"
	@echo "| fclean     |"
	@echo "| re         |"
	@echo "| renolibft  |"
	@echo "+------------+"

all: libft.a $(NAME)

libft.a:
	make -c libft re

$(NAME):
	cd srcs;\
	$(CC) -o ../$(NAME) $(CFLAGS) $(addprefix -I ,$(INCLUDE)) $(SRCS)

clean:
	make -C libft/clean

fclean: clean
	rm -f $(NAME)
	make -C libft/fclean

re: fclean all

renolibft:
	rm -f $(NAME)
	make $(NAME)

.PHONY: all clean fclean re

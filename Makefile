CC      =	gcc
CFLAGS  =	-Wall -Wextra -Werror
NAME    =	ft_ls
INCLUDE =	include libft/include
SRCS    =	main.c listing.c helpers.c print.c extras.c

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
	make -C libft re

$(NAME):
	cd srcs;\
	$(CC) -o ../$(NAME) $(CFLAGS) $(addprefix -I ../,$(INCLUDE)) $(SRCS) ../libft/libft.a

clean:
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

renolibft:
	rm -f $(NAME)
	make $(NAME)

.PHONY: all clean fclean re

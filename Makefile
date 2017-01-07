SRCS = main.c \
	   setup.c \
	   input.c \
	   process.c \
	   env.c \
	   termcaps.c \
	   utl.c \
	   execute.c \
	   signal.c \
	   tabs.c \
	   cd.c 

OBJS = $(addprefix srcs/,$(SRCS:.c=.o))

NAME = minishell
CC = gcc
FLAGS = -Wall -Wextra
INCS = includes

all: $(NAME)

$(NAME): $(OBJS)
	@echo "[libft]"
	@make -C libft
	@echo "[$(NAME)]"
	@gcc $(FLAGS) -o $(NAME) $(OBJS) libft/libft.a -l termcap

srcs/%.o: srcs/%.c
	@$(CC) $(FLAGS) -I $(INCS) -I libft/includes -o $@ -c $<
	@echo "[$@]"

clean:
	@make clean -C libft
	@rm -f $(OBJS)
	@echo "[objs removed]"

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)
	@echo "[workspace clean]"

re: fclean all

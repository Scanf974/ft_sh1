CC = gcc
SRC = main.c \
	  ft_prompt.c \
	  ft_disable_sig.c \
	  ft_getpath.c \
	  ft_cmd.c \
	  ft_cd.c \
	  ft_onlyesp.c \
	  ft_pwd.c \
	  ft_get_id_var.c \
	  ft_setenv.c \
	  ft_unsetenv.c \
	  ft_cmd_is_in_path.c \
	  ft_getcmd.c \
	  ft_strsplit_white_space.c \
	  ft_fuckit.c \
	  ft_exec.c \
	  ft_strtrim_new.c \
	  ft_getdir.c \
	  ft_getpath_pwd.c \
	  ft_nb_env.c \
	  ft_env.c
OBJ = $(SRC:.c=.o)
NAME = ft_minishell1
FLAGS = -Wall -Wextra -Werror
LIB = -L./libft -lft

all: $(NAME)

$(NAME):
	@make -C libft/
	@echo "Dat Shell -> Maked"
	@$(CC) $(FLAGS) -I libft/includes/ -c $(SRC)
	@$(CC) -o $(NAME) $(OBJ) $(LIB)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

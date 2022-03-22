NAME 	=	minishell

FILES	=	main builtin env find_exe parse parse_utils debug file_edit functions

SRC		=	$(addprefix src/, $(FILES:$(FILE_EXTENSION)=.c))
OBJ		= $(addprefix objs/, ${FILES:$(FILE_EXTENSION)=.o})
INC		=	-I. -I./libft -I$(HOME)/.brew/opt/readline/include -lreadline -L$(HOME)/.brew/opt/readline/lib
#INC		=	-I. -I./libft -I/opt/homebrew/opt/readline/include -lreadline -L/opt/homebrew/opt/readline/lib
CC		=	gcc

RM		=	rm -f

GREEN       =   \e[38;5;118m
YELLOW      =   \e[38;5;226m
RESET       =   \e[0m
_SUCCESS    =   [$(GREEN)SUCCESS$(RESET)]
_INFO       =   [$(YELLOW)INFO$(RESET)]

all:	header $(NAME)

objs/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) -Wall -Wextra -Werror -g -c $< -o $@
	@printf "$(_INFO) OBJ $@ compiled.\n"

$(NAME): $(OBJ)
	@printf "$(_INFO) Preparing libft\n"
	@$(MAKE) bonus -C ./libft
	@$(CC) $(OBJ) ./libft/libft.a $(INC) -o $(NAME)
	@printf "$(_SUCCESS) $(NAME) ready.\n"

clean:
	@ $(RM) $(OBJ)
	@printf "$(_INFO) $(OBJ) removed.\n"
	@ $(MAKE) -C ./libft clean
fclean: clean
	@ $(MAKE) fclean -C libft
	@ $(RM) $(NAME)
	@printf "$(_INFO) $(NAME) removed.\n"
re: fclean all

bonus: $(NAME)

.PHONY: all clean fclean re

header:
	@printf "$(GREEN)"
	@echo " __   __  _______  ___   _  _______ "
	@echo "|  |_|  ||   _   ||   | | ||       |"
	@echo "|       ||  |_|  ||   |_| ||    ___|"
	@echo "|       ||       ||      _||   |___ "
	@echo "|       ||       ||     |_ |    ___|"
	@echo "| ||_|| ||   _   ||    _  ||   |___ "
	@echo "|_|   |_||__| |__||___| |_||_______|"
	@printf "Project $(NAME)\n"
	@printf "Last commit : "
	@echo $$(git log -1 --format=%cd --date=relative)
	@printf "              "
	@echo  $$(git log -1 --format=%B --date=relative)
	@printf "$(RESET)"
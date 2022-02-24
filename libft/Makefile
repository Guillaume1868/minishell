ifneq ($(words $(MAKECMDGOALS)),1) # if no argument was given to make...
.DEFAULT_GOAL = all # set the default goal to all
%:                   # define a last resort default rule
		@$(MAKE) $@ --no-print-directory -rRf $(firstword $(MAKEFILE_LIST)) # recursive make call,
else
ifndef ECHO
T := $(shell $(MAKE) $(MAKECMDGOALS) --no-print-directory \
      -nrRf $(firstword $(MAKEFILE_LIST)) \
      ECHO="COUNTTHIS" | grep -c "COUNTTHIS")
N := x
C = $(words $N)$(eval N := x $N)
ECHO = printf "$(_INFO) Building libft [`expr $C '*' 100 / $T`%%]\\r"
endif
FLAG = -Wall -Wextra -Werror
NAME = libft.a

SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c  ft_isalpha.c ft_isascii.c \
ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
ft_memmove.c ft_memset.c   ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlcat.c \
ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c  ft_strnstr.c  ft_strrchr.c \
ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_striteri.c

OBJ = $(SRC:.c=.o)

BONUS			=	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c  ft_lstlast.c \
					ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
					ft_lstmap.c
BONUS_OBJS		= $(BONUS:.c=.o)

GREEN       =   \e[38;5;118m
YELLOW      =   \e[38;5;226m
RESET       =   \e[0m
_SUCCESS    =   [$(GREEN)SUCCESS$(RESET)]
_INFO       =   [$(YELLOW)INFO$(RESET)]

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@printf "\n$(_SUCCESS) libft ready.\n"

%.o: %.c
	@gcc $(FLAG) -c $< -o $@
	@$(ECHO)
# @printf "."

clean:
	@rm -f $(OBJ) $(BONUS_OBJS)
	@printf "$(_INFO) libft OBJ removed.\n"

fclean:
	@rm -f $(NAME)
	@printf "$(_INFO) LIBFT removed.\n"

re:
	@$(MAKE) fclean
	@$(MAKE)

bonus: $(OBJ) $(BONUS_OBJS)
	@ar rcs $(NAME) $(OBJ) $(BONUS_OBJS)
	@printf "\n$(_SUCCESS) BONUS libft ready.\n"

.PHONY: all, clean, fclean, re, bonus
endif
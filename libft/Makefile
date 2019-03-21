NAME := libft.a
INCLUDES := includes/
PRINTF_DIR := ft_printf/

SRCS := $(wildcard *.c)
PRINTF_SRCS := $(wildcard $(PRINTF_DIR)*.c)

FLAGS := -Wall -Wextra -Werror
DEBUG_FLAGS := -g -O0

GREEN=\033[0;32m
YELLOW=\033[0;33m
NC=\033[0m # No Color

.PHONY: clean re all fclean add_flags debug

OBJ = $(patsubst %.c, %.o, $(SRCS) $(PRINTF_SRCS))

all: $(NAME)

debug: fclean add_flags all

add_flags:
	$(eval FLAGS += $(DEBUG_FLAGS))

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@printf "\r$(NAME) $(GREEN)✔                                    $(NC)\n"

%.o: %.c
	@printf "\rCompiling $<                 "
	@gcc $(FLAGS) -c $(addprefix -I,$(INCLUDES)) $< -o $@

clean:
	@/bin/rm -f $(OBJ)
	@printf "$(NAME) clean: $(YELLOW)✔$(NC)\n"

fclean: clean
	@/bin/rm -f $(NAME)
	@printf "$(NAME) fclean: $(YELLOW)✔$(NC)\n"

re: fclean all

echo:
	@echo $(SRCS)
	@echo $(PRINTF_SRCS)
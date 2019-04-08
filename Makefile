NAME := asm corewar
INCLUDES := include/ libft/includes/
SRC_DIR := src/
SRC_ASM_DIR := $(SRC_DIR)asm/
SRC_COREWAR_DIR := $(SRC_DIR)corewar/
SRC_ASM := $(patsubst src/%, %, $(wildcard $(SRC_ASM_DIR)*.c))
SRC_COREWAR := $(patsubst src/%, %, $(wildcard $(SRC_COREWAR_DIR)*.c))

LIB_DIR := libft/
LIB := $(LIB_DIR)libft.a
CURS := -lncurses

OBJ_DIR := out/
OBJ_ASM := $(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(SRC_ASM)))
OBJ_COREWAR := $(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(SRC_COREWAR)))
FLAGS := -Wall -Wextra -Werror
DEBUG_FLAGS := -g -O0

GREEN=\033[0;32m
YELLOW=\033[0;33m
NC=\033[0m # No Color

.PHONY: all run debug add_dflags clean fclean re echo

all: corewar asm

asm: $(LIB) $(OBJ_ASM)
	@gcc $(OBJ_ASM) $(LIB) $(addprefix -I,$(INCLUDES)) -o $@
	@printf "$@ $(GREEN)✔$(NC)                                        \n"

corewar: $(LIB) $(OBJ_COREWAR)
	@gcc $(OBJ_COREWAR) $(LIB) $(addprefix -I,$(INCLUDES)) $(CURS) -o $@
	@printf "$@ $(GREEN)✔$(NC)                                        \n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	gcc $(FLAGS) -c $(addprefix -I,$(INCLUDES)) $< -o $@

$(LIB):
	@$(MAKE) -C $(LIB_DIR) all

debug: add_dflags asm corewar

add_dflags:
	$(eval FLAGS = $(DEBUG_FLAGS))

clean:
	@$(MAKE) -C $(LIB_DIR) clean
	@/bin/rm -f $(OBJ_ASM)
	@/bin/rm -f $(OBJ_COREWAR)
	@printf "$(NAME) clean: $(YELLOW)✔$(NC)\n"

fclean: clean
	@$(MAKE) -C $(LIB_DIR) fclean
	@/bin/rm -f $(NAME)
	@rm -rf $(OBJ_DIR)
	@printf "$(NAME) fclean: $(YELLOW)✔$(NC)\n"

re: fclean all

echo:
	@echo $(SRC_ASM)
	@echo $(OBJ_ASM)

run:
	./42asm super_champ.s
	./corewar -vis super_champ.cor

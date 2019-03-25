#include "corewar.h"

t_op	g_op_tab[16] =
{
	{"live", 1, {T_DIR}, 10, 0, 4, op_live},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 5, 1, 4, op_load},
	{"st", 2, {T_REG, T_IND | T_REG}, 5, 1, 4, op_store},
	{"add", 3, {T_REG, T_REG, T_REG}, 10, 1, 4},
	{"sub", 3, {T_REG, T_REG, T_REG}, 10, 1, 4},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 1, 4},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 6, 1, 4},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 6, 1, 4},
	{"zjmp", 1, {T_DIR}, 20, 0, 2},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 25, 1, 2},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 25, 1, 2},
	{"fork", 1, {T_DIR}, 800, 0, 2},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 10, 1, 4},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 50, 1, 2},
	{"lfork", 1, {T_DIR}, 1000, 0, 2},
	{"aff", 1, {T_REG}, 2, 1, 4},
};

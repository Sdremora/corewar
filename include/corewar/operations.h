
#ifndef OPERATIONS_H
# define OPERATIONS_H
# include "corewar.h"

typedef enum	e_oper
{
	LIVE,
	LD,
	ST,
	ADD,
	SUB,
	AND,
	OR,
	XOR,
	ZJMP,
	LDI,
	STI,
	FORK,
	LLD,
	LLDI,
	LFORK,
	AFF,
	INVALID
}				t_oper;

typedef struct	s_op
{
	char			name[10];
	int				var_count;
	unsigned char	args[3];
	int				cost;
	int				kod_tipov_argumenta;
	int				dir_size;
	void			(*op_handler)(t_carriage *carg, t_arena *arena);
}				t_op;

extern t_op		g_op_tab[16];

#endif

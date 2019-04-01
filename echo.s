.name "zork"
.comment "I'M ALIIIIVE"

l2:		#live 9223372036854775808
		sti r0, %:live, %9223372036854775808
		and r1, %0, r1
live:	live 9223372036854775808
		zjmp %:live

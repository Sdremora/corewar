.name "zork"
.comment "I'M ALIIIIVE"

l2:		sti r1      ,      %li:ve,          %1
		and r1, %0, r1

live:	st r1, r12
		zjmp %:live

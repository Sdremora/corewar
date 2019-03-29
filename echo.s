.name "zork"
.comment "I'M ALIIIIVE"

l2:		sti r4, %:live, %1
		and r1, %0, r1

live:	live %2000000000008888888888888855555555555555555555555
		zjmp %:live

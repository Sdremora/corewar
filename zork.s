.name "zork"
.comment "I'M ALIIIIVE"

l2:		sti r1, %:live, %1 #ksjhdg 
		and r1, %:l2, r1  

live:	live %1
		zjmp %:l2 

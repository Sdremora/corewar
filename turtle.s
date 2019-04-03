.name 		"turtle"
.comment	"TURTLE FFS U LAMA"

entry:
	sti			r1, %:zork, %1
	sti			r1, %:ardef, %1
	sti			r1, %:entry_l1, %1
	ld			%0, r16
	fork		%:zork

entry_l1:
	live		%42
	ld			%43, r2
	ld			%0, r16
	
################################################################################

ardef:
	live		%42
	st			r2, 4
	zjmp		%:ardef

################################################################################

zork:
	live		%42
	zjmp		%:zork

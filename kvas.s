.name "kvas"
.comment "xD"

	fork %:side2

side1:
	st r1, 49
	ld %-400, r3
	ld %72, r2
	ld %4, r4
begin1:
	ldi r2, %-30, r5
	sti r5, r3, %0
	sub r3, r4, r3
	sub r2, r4, r2
	live %0
	zjmp %:out1
	ld %0, r10
	zjmp %:begin1
out1:
	zjmp %-500

side2:
	st r1, 49
	ld %480, r3
	ld %72, r2
	ld %4, r4
begin2:
	ldi r2, %-30, r5
	sti r5, r3, %0
	sub r3, r4, r3
	sub r2, r4, r2
	live %0
	zjmp %:out2
	ld %0, r10
	zjmp %:begin2
out2:
	zjmp %350


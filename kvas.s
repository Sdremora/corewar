.name "kvas"
.comment "Попей кваску, разгони тоску! 
		И квас есть, да не про вашу честь! 
		Не коси глаз на чужой квас!"

	add r2, r3, r4
	zjmp %:core

side1:
s1_number1:
	live %0
	fork %:s1_number2
	live %0
	fork %:s1_number4
	live %0
	ld %1, r1	# 01
	ld %-12, r2
	ld %0, r16
	zjmp %:s1_fight

s1_number2:
	live %0
	fork %:s1_number3
	live %0
	ld %777, r2 	# fake
	ld %-8, r2
	ld %0, r16
	zjmp %:s1_fight

s1_number3:
	live %0
	ld %190054658, r1	# 0b 58 01 02
	ld %-4, r2
	ld %0, r16
	zjmp %:s1_fight

s1_number4:
	live %0
	ld %50986977, r1	# 03 09 ff e1
	ld %0, r2
	ld %0, r16
	zjmp %:s1_fight

s1_fight:
	ld %-17, r3
	ld %0, r16
	sti r1, r2, %-250
	zjmp %-300

core:						#core
	live %0
	fork %:side2
	live %0
	fork %:side1
	zjmp %:core


side2:
s2_number1:
	live %0
	fork %:s2_number2
	live %0
	fork %:s2_number4
	live %0
	ld %1, r1	# 01
	ld %0, r2
	ld %0, r16
	zjmp %:s2_fight

s2_number2:
	live %0
	fork %:s2_number3
	live %0
	ld %777, r2 	# fake
	ld %4, r2
	ld %0, r16
	zjmp %:s2_fight

s2_number3:
	live %0
	ld %190054658, r1	# 0b 58 01 02
	ld %8, r2
	ld %0, r16
	zjmp %:s2_fight

s2_number4:
	live %0
	ld %50921483, r1	# 03 09 00 19
	ld %12, r2
	ld %0, r16
	zjmp %:s2_fight

s2_fight:
	ld %13, r3
	ld %0, r16
	sti r1, r2, %124
	zjmp %100

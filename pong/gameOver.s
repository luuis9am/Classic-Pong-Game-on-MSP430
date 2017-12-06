		.data
counter:.word 0; counter = 0

		.text
JT:	.word case0
		.word case1
		.word case2
		.word case3
		.word case4
		.word case5
		.word case6
		.word case7
		.word case8
		.word case9
		.word case10

		.global gameOverSong
gameOver:
		mov &counter, r12
		add #1, r12
		mov JT(r12), r0

case0:
		mov #300, r12
		call #buzzer_set_period; buzzer_set_period(300)
		mov #900, r12
		call #buzzer_set_period; buzzer_set_period(900)
		add #1, &counter; counter++
		jmp break

case1:
		mov #400, r12
		call #buzzer_set_period; buzzer_set_period(400)
		mov #800, r12
		call #buzzer_set_period; buzzer_set_period(800)
		add #1, &counter; counter++
		jmp break
case2:
		mov #500, r12
		call #buzzer_set_period ;buzzer_set_period(500)
		mov #700, r12
		call #buzzer_set_period ;buzzer_set_period(700)
		add #1, &counter	;counter++
		jmp break
case3:
		mov #600, r12
		call #buzzer_set_period ;buzzer_set_period(600)
		mov #500, r12
		call #buzzer_set_period ;buzzer_set_period(500)
		add #1, &counter	;counter++
		jmp break

case4:
		mov #700, r12
		call #buzzer_set_period ;buzzer_set_period(700)
		mov #400, r12
		call #buzzer_set_period ;buzzer_set_period(400)
		add #1, &counter	;counter++
		jmp break
case5:
		mov #800, r12
		call #buzzer_set_period ;buzzer_set_period(800)
		mov #300, r12
		call #buzzer_set_period ;buzzer_set_period(300)
		add #1, &counter	;counter++
		jmp break
case6:
		mov #900, r12
		call #buzzer_set_period ;buzzer_set_period(900)
		mov #200, r12
		call #buzzer_set_period ;buzzer_set_period(200)
		add #1, &counter	;counter++
		jmp break
case7:
		mov #300, r12
		call #buzzer_set_period ;buzzer_set_period(300)
		mov #400, r12
		call #buzzer_set_period ;buzzer_set_period(400)
		add #1, &counter	;counter++
		jmp break

case8:
		mov #600, r12
		call #buzzer_set_period ;buzzer_set_period(600)
		mov #500, r12
		call #buzzer_set_period ;buzzer_set_period(500)
		add #1, &counter	;counter++
		jmp break
case9:
		mov #700, r12
		call #buzzer_set_period ;buzzer_set_period(700)
		mov #600, r12
		call #buzzer_set_period ;buzzer_set_period(600)
		add #1, &counter	;counter++
		jmp break
case10:
		mov #0, r12
		call #buzzer_set_period ;buzzer_set_period(0)
		add #1, &counter	;counter++
		jmp break
break:
		pop r0

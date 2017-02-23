DATA SEGMENT  
	C4 DB 50 DUP  ? 
	C DB  ? 
	Hello DD 12 DUP  ? 
	Val2 DD  ? 
	Val1 DD  ? 
DATA ENDS ; fin de declaration 

PILE SEGMENT  
 	stack DW 100 dup (?) 
PILE ENDS 

CODE SEGMENT
	ASSUME SS:pile
 	MOV AX,pile
 	MOV SS, AX

BEGIN:  
		MOV AX, '8' 
		MOV Bonjour, AX 
		MOV AX, 2 
		CMP AX, 0 
		JE etiq_13 
		MOV AX, 8 
		CMP AX, 0 
		JE etiq_13 
		MOV AX, 1 
		PUSH AX
		JMP etiq_14 
etiq_13 :
		MOV AX, 0 
		PUSH AX
etiq_14 :
		POP AX 
		MUL AX,1 
		PUSH AX
		POP AX 
		CMP AX, 0 
		JE etiq_19 
		MOV AX, 12 
		CMP AX, 0 
		JE etiq_19 
		MOV AX, 1 
		PUSH AX
		JMP etiq_20 
etiq_19 :
		MOV AX, 0 
		PUSH AX
etiq_20 :
		POP AX 
		CMP AX, 0 
		JNE etiq_24 
		MOV AX, 15 
		CMP AX, 0 
		JNE etiq_24 
		MOV AX, 0 
		PUSH AX
		JMP etiq_25 
etiq_24 :
		MOV AX, 1 
		PUSH AX
etiq_25 :
		POP AX 
		CMP AX, 0 
		JE etiq_46 
		MOV AX,Hello[5] 
		ADD AX,12 
		PUSH AX
		POP AX 
		SUB AX,12 
		PUSH AX
		POP AX 
		MOV Hello[1], AX
		MOV AX,Hello[2] 
		SUB AX,12 
		PUSH AX
		POP AX 
		CMP AX, 0 
		JL etiq_33 
		MOV AX, 0 
		PUSH AX
		JMP etiq_34 
etiq_33 :
		MOV AX, 1 
		PUSH AX
etiq_34 :
		POP AX 
		CMP AX, 0 
		JE etiq_38 
		MOV AX, Val1 
		CMP AX, 0 
		JE etiq_38 
		MOV AX, 1 
		PUSH AX
		JMP etiq_39 
etiq_38 :
		MOV AX, 0 
		PUSH AX
etiq_39 :
		POP AX 
		CMP AX, 0 
		JNE etiq_43 
		MOV AX, 12.0 
		CMP AX, 0 
		JNE etiq_43 
		MOV AX, 0 
		PUSH AX
		JMP etiq_44 
etiq_43 :
		MOV AX, 1 
		PUSH AX
etiq_44 :
		POP AX 
		MOV Val2, AX
		JMP etiq_107 
etiq_46 :
		MOV AX,5 
		DIV AX,12 
		PUSH AX
		POP AX 
		SUB AX,Val1 
		PUSH AX
		POP AX 
		CMP AX, 0 
		JE etiq_107 
		MOV AX, '2' 
		MOV C, AX 
		MOV AX, 2 
		CMP AX, 0 
		JE etiq_54 
		MOV AX, 8 
		CMP AX, 0 
		JE etiq_54 
		MOV AX, 1 
		PUSH AX
		JMP etiq_55 
etiq_54 :
		MOV AX, 0 
		PUSH AX
etiq_55 :
		POP AX 
		MUL AX,1 
		PUSH AX
		POP AX 
		CMP AX, 0 
		JE etiq_60 
		MOV AX, 12 
		CMP AX, 0 
		JE etiq_60 
		MOV AX, 1 
		PUSH AX
		JMP etiq_61 
etiq_60 :
		MOV AX, 0 
		PUSH AX
etiq_61 :
		POP AX 
		CMP AX, 0 
		JNE etiq_65 
		MOV AX, 0. 
		CMP AX, 0 
		JNE etiq_65 
		MOV AX, 0 
		PUSH AX
		JMP etiq_66 
etiq_65 :
		MOV AX, 1 
		PUSH AX
etiq_66 :
		POP AX 
		CMP AX, 0 
		JE etiq_87 
		MOV AX,Hello[5] 
		ADD AX,12 
		PUSH AX
		POP AX 
		SUB AX,25 
		PUSH AX
		POP AX 
		MOV Hello[1], AX
		MOV AX,Hello[2] 
		SUB AX,12 
		PUSH AX
		POP AX 
		CMP AX, 0 
		JL etiq_74 
		MOV AX, 0 
		PUSH AX
		JMP etiq_75 
etiq_74 :
		MOV AX, 1 
		PUSH AX
etiq_75 :
		POP AX 
		CMP AX, 0 
		JE etiq_79 
		MOV AX, Val1 
		CMP AX, 0 
		JE etiq_79 
		MOV AX, 1 
		PUSH AX
		JMP etiq_80 
etiq_79 :
		MOV AX, 0 
		PUSH AX
etiq_80 :
		POP AX 
		CMP AX, 0 
		JNE etiq_84 
		MOV AX, 00.16432 
		CMP AX, 0 
		JNE etiq_84 
		MOV AX, 0 
		PUSH AX
		JMP etiq_85 
etiq_84 :
		MOV AX, 1 
		PUSH AX
etiq_85 :
		POP AX 
		MOV Val2, AX
		JMP etiq_104 
etiq_87 :
		MOV AX,4 
		MUL AX,12 
		PUSH AX
		POP AX 
		SUB AX,Val1 
		PUSH AX
		POP AX 
		CMP AX, 0 
		JE etiq_104 
		MOV AX, C4[10] 
		MOV C, AX 
etiq_91 :
		MOV AX,Val1 
		SUB AX,65 
		PUSH AX
		POP AX 
		CMP AX, 0 
		JL etiq_95 
		MOV AX, 0 
		PUSH AX
		JMP etiq_96 
etiq_95 :
		MOV AX, 1 
		PUSH AX
etiq_96 :
		POP AX 
		CMP AX, 0 
		JE etiq_101 
		MOV AX,Hello[2] 
		DIV AX,12 
		PUSH AX
		POP AX 
		MOV Val2, AX
		MOV AX,1 
		ADD AX,Val1 
		PUSH AX
		JMP etiq_91 
etiq_101 :
		MOV AX,Val1 
		DIV AX,2 
		PUSH AX
		POP AX 
		MOV Val1, AX
		JMP etiq_87 
etiq_104 :
		MOV AX,Val1 
		DIV AX,2 
		PUSH AX
		POP AX 
		MOV Val2, AX
		JMP etiq_46 
		

MOV ah, 4ch
int 21h ; fin prog principale
CODE ENDS 
END BEGIN 

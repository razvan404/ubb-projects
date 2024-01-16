bits 32
global start

extern exit
import exit msvcrt.dll
extern scanf
import scanf msvcrt.dll
extern printf
import printf msvcrt.dll

segment data use32 class=data
	a		RESD		1
	b		RESD		1
	str1	DB		'Enter the numbers: ', 0
	str2	DB		'%d%d', 0
	res		RESD		1
	str3	DB		'The result of (%d * (%d + %d) - %d * (%d + %d)) / %d + %d * %d / %d is %d!', 10, 'Extra operation: 5 + 3 = %d :D', 10, 0
	tmp		RESD		10

segment data use32 class=code
	start:
	; a = 0
		MOV		EAX,		0
		MOV		[a],		EAX

	; b = 0
		MOV		EAX,		0
		MOV		[b],		EAX

	; output statement
		PUSH	DWORD		str1
		CALL	[printf]
		ADD		ESP,		4 * 1

	; input statement
		PUSH	DWORD		b
		PUSH	DWORD		a
		PUSH	DWORD		str2
		CALL	[scanf]
		ADD		ESP,		4 * 3

	; [tmp + 0] = [a] + 1
		MOV		EAX,		[a]
		ADD		EAX,		1
		MOV		[tmp + 0],		EAX
	; [tmp + 4] = [a] * [tmp + 0]
		MOV		EBX,		[a]
		MOV		EAX,		[tmp + 0]
		IMUL	EBX
		MOV		[tmp + 4],		EAX
	; [tmp + 8] = [b] + 1
		MOV		EAX,		[b]
		ADD		EAX,		1
		MOV		[tmp + 8],		EAX
	; [tmp + 12] = [b] * [tmp + 8]
		MOV		EBX,		[b]
		MOV		EAX,		[tmp + 8]
		IMUL	EBX
		MOV		[tmp + 12],		EAX
	; [tmp + 16] = [tmp + 4] - [tmp + 12]
		MOV		EAX,		[tmp + 4]
		SUB		EAX,		[tmp + 12]
		MOV		[tmp + 16],		EAX
	; [tmp + 20] = [tmp + 16] / [b]
		MOV		EDX,		0
		MOV		EAX,		[tmp + 16]
		MOV		EBX,		[b]
		IDIV	EBX
		MOV		[tmp + 20],		EAX
	; [tmp + 24] = 4 * [b]
		MOV		EBX,		4
		MOV		EAX,		[b]
		IMUL	EBX
		MOV		[tmp + 24],		EAX
	; [tmp + 28] = [tmp + 24] / [a]
		MOV		EDX,		0
		MOV		EAX,		[tmp + 24]
		MOV		EBX,		[a]
		IDIV	EBX
		MOV		[tmp + 28],		EAX
	; [tmp + 32] = [tmp + 20] + [tmp + 28]
		MOV		EAX,		[tmp + 20]
		ADD		EAX,		[tmp + 28]
		MOV		[tmp + 32],		EAX
	; res = [tmp + 32]
		MOV		EAX,		[tmp + 32]
		MOV		[res],		EAX

	; output statement
	; [tmp + 36] = 5 + 3
		MOV		EAX,		5
		ADD		EAX,		3
		MOV		[tmp + 36],		EAX
		PUSH	DWORD		[tmp + 36]
		PUSH	DWORD		[res]
		PUSH	DWORD		[a]
		PUSH	DWORD		[b]
		PUSH	DWORD		4
		PUSH	DWORD		[b]
		PUSH	DWORD		1
		PUSH	DWORD		[b]
		PUSH	DWORD		[b]
		PUSH	DWORD		1
		PUSH	DWORD		[a]
		PUSH	DWORD		[a]
		PUSH	DWORD		str3
		CALL	[printf]
		ADD		ESP,		4 * 13

	;exit
		PUSH		DWORD		0
		CALL		[exit]

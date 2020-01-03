include Irvine32.inc

retrievePrice PROTO C
getQuantity PROTO C
addToTotal PROTO C, value:SDWORD
grandTotal PROTO C, value:SDWORD

.data
	;define variables here
	;price DWORD ?
	quantity DWORD ?
	subTotal DWORD ?
	total DWORD ?
	divisionTotal DWORD ?
	numOfPerson DWORD ?
.code

calcSubTotal PROC C, price:real8

	mov ebx, price
	INVOKE getQuantity
	mul ebx
	mov subTotal, eax
	INVOKE addToTotal, subTotal
	ret

	Exit
calcSubTotal ENDP

calcTotal PROC C

	INVOKE calcSubTotal
	mov ebx, total
	add ebx, eax
	mov total, ebx
	INVOKE grandTotal, total
	
	ret
	Exit
calcTotal ENDP

calcDivision PROC C, value1:SDWORD, value2:SDWORD
	mov eax, value1
	mov ebx, value2
    xor edx, edx
	div ebx
	ret
	Exit
calcDivision ENDP

END

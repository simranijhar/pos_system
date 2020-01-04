include Irvine32.inc

;define functions here
;retrievePrice PROTO C
;getQuantity PROTO C
;addToTotal PROTO C, value:SDWORD
;grandTotal PROTO C, value:SDWORD

.data
	;define variables here
	;price DWORD ?
	;quantity DWORD ?
	;subTotal DWORD ?
	;total DWORD ?
.code

calcSubTotal PROC C, price:SDWORD, quantity:SDWORD
	mov eax, price
	mov ebx, quantity
	mul ebx
	ret
	Exit
calcSubTotal ENDP

calcTotal PROC C, subTotal:SDWORD, total:SDWORD
	mov eax, subTotal
	mov ebx, total
	add eax, ebx
	ret
	Exit
calcTotal ENDP

calcDivision PROC C, total:SDWORD, numOfPerson:SDWORD
	mov eax, total
	mov ebx, numOfPerson
    xor edx, edx
	div ebx
	ret
	Exit
calcDivision ENDP
END

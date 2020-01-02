include Irvine32.inc

retrievePrice PROTO C
getQuantity PROTO C
addToTotal PROTO C, value:SDWORD
grandTotal PROTO C, value:SDWORD

.data
	;define variables here
	price DWORD ?
	quantity DWORD ?
	subTotal DWORD ?
	total DWORD ?
.code

calcSubTotal PROC C

	;write assembly code here

	INVOKE retrievePrice
	mov price, eax
	INVOKE getQuantity
	mul price
	mov subTotal, eax
	INVOKE addToTotal, subTotal
	ret

	Exit
calcSubTotal ENDP

calcTotal PROC C

	;write assembly code here

	INVOKE calcSubTotal
	mov ebx, total
	add ebx, eax
	mov total, ebx
	INVOKE grandTotal, total
	
	ret
	Exit
calcTotal ENDP


END

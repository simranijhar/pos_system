include Irvine32.inc

;define functions here
displaySubTotal PROTO C, subTotal:real8
displayTotal PROTO C,total:real8

.data
	;define variables here
	splitAmount real8 ?
	aSubTotal real8 ?
	aTotal real8 ?
.code

calcSubTotal PROC C, price:real8, quantity:real8
	fld price
	fld quantity
	fmul
	fstp aSubTotal
	INVOKE displaySubTotal, aSubTotal
	ret
	Exit
calcSubTotal ENDP

calcTotal PROC C, subTotal:real8, total:real8
	fld subTotal
	fld total
	fadd
	fstp aTotal
	INVOKE displayTotal, aTotal

	ret
	Exit
calcTotal ENDP

splitBill PROC C, total:SDWORD, numOfPerson:SDWORD
	fld total
	fld numOfPerson
	fdiv
	fstp splitAmount

	ret
	Exit
splitBill ENDP
END

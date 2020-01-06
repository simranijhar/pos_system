include Irvine32.inc

;define functions here
displaySubTotal PROTO C, subTotal:real8
displayTotal PROTO C,total:real8
displaySplitAmount PROTO C, amount:real8
displaySST PROTO C, total:real8
displayCST PROTO C, total:real8
displayGrandTotal PROTO C, grandTotal:real8

.data
	;define variables here
	splitAmount real8 ?
	aSubTotal real8 ?
	aTotal real8 ?
	_cst real8 0.10
	_sst real8 0.06
	cst real8 ?
	sst real8 ?
	grandTotal real8 ?
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

splitBill PROC C, total:real8, numOfPerson:real8
	fld total
	fld numOfPerson
	fdiv
	fstp splitAmount
	INVOKE displaySplitAmount, splitAmount
	ret
	Exit
splitBill ENDP

calcCST PROC C, total:real8
	fld total
	fld _cst
	fmul
	fstp cst
	INVOKE displayCST, cst
	ret
	Exit
calcCST ENDP

calcSST PROC C, total:real8
	fld total
	fld _sst
	fmul
	fstp sst
	INVOKE displaySST, sst
	ret
	Exit
calcSST ENDP

calcGrandTotal PROC C, total:real8, value1:real8, value2:real8
	fld total
	fld cst
	fadd
	fld sst
	fadd
	fstp grandTotal
	INVOKE displayGrandTotal, grandTotal
	ret
	Exit
calcGrandTotal ENDP
	
END

.ORIG x3000



;; CODE HERE  JAMAL KHARRAT
LDI R0, P ;set the value of r0 to p
LDI R1, X ;set the value of r1 to x

AND R0, R0, 0 ;set p (in r0 to 1)
ADD R0, R0, 1 ; increment r0
LD    R1, N ; load the value of R1 into N
BRZ done ;branch of zero

;; loop to 2^n
loop	ADD R0, R0, R0  ; P=P+1
	ADD R1, R1, -1  ;x= x-1
	BRP loop ;goes back to loop in casse x>0


done	ST R0, result   ;store the result
HALT
	N   .FILL 2  ;;filling N to 2
	P   .FILL 0
	X   .FILL 0
	result .BLKW 1 ;;

.END






.ORIG x3000

;; CODE HERE
LDI R0, P ;
LDI R1, X ;

AND R0 R0 0 ;set p (in r0 to 1)
ADD R0 R0 1 
LD    R1 N
BRZ done

loop	ADD R0 R0 R0  ; P=P+1
	ADD R1 R1 -1  ;x= x-1
	BRP loop ;goes back to loop in casse x>0


done	ST R0 result   ;store the result
	N   .FILL 2
	result .BLKW 1 ;;

.END











.END
PRINT "Calculating the first 10 Fibonacci numbers:"
LET a = 0
LET b = 1
FOR i = 1 TO 10
    PRINT a
    LET next = a + b
    LET a = b
    LET b = next
NEXT

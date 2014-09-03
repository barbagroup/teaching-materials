PROGRAM main
USE funcs
IMPLICIT NONE
REAL(KIND=8):: A(2, 2), B(2), x(2)
CHARACTER(LEN=72):: var1 = "Hello World!"   

    A(1, 1) = 2
    A(1, 2) = 3
    A(2, 1) = 5
    A(2, 2) = 2
    
    B(1) = 7
    B(2) = 6

    CALL display(var1)
    CALL linSolve(2, A, B, x)
    
    WRITE(*, *) x
    
END PROGRAM main
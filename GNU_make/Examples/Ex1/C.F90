MODULE funcs
IMPLICIT NONE
CONTAINS
   
!======================================================================
!----------------------------------------------------------------------
! Subroutine linSolve
!----------------------------------------------------------------------
    SUBROUTINE linSolve(N, A, b, x)
    IMPLICIT NONE
    INTEGER(KIND=4):: N, INFO
    INTEGER(KIND=4):: IPIV(N)
    REAL(KIND=8):: A(N, N), B(N, 1), x(N, 1)
        
        CALL DGESV(N, 1, A, N, IPIV, B, N, INFO)
        x = B
    
    END SUBROUTINE linSolve

END MODULE funcs
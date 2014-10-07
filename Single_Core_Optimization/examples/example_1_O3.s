	.file	"example_2.c"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC1:
	.string	"Work took %f micro-sec\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB13:
	.cfi_startproc
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	call	omp_get_wtime
	movsd	%xmm0, 8(%rsp)
	call	omp_get_wtime
	subsd	8(%rsp), %xmm0
	movl	$.LC1, %esi
	movl	$1, %edi
	movl	$1, %eax
	mulsd	.LC0(%rip), %xmm0
	call	__printf_chk
	xorl	%eax, %eax
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE13:
	.size	main, .-main
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC0:
	.long	0
	.long	1093567616
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits

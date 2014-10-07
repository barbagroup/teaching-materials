	.file	"example_2.c"
	.section	.rodata
.LC4:
	.string	"Work took %f micro-sec\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$1264, %rsp
	call	omp_get_wtime
	movsd	%xmm0, -1256(%rbp)
	movq	-1256(%rbp), %rax
	movq	%rax, -1216(%rbp)
	leaq	-1200(%rbp), %rsi
	movl	$0, %eax
	movl	$50, %edx
	movq	%rsi, %rdi
	movq	%rdx, %rcx
	rep stosq
	leaq	-800(%rbp), %rsi
	movl	$0, %eax
	movl	$50, %edx
	movq	%rsi, %rdi
	movq	%rdx, %rcx
	rep stosq
	movl	.LC0(%rip), %eax
	movl	%eax, -1228(%rbp)
	movl	.LC1(%rip), %eax
	movl	%eax, -1224(%rbp)
	movl	$0, -1236(%rbp)
	jmp	.L2
.L3:
	cvtsi2sd	-1236(%rbp), %xmm0
	addsd	%xmm0, %xmm0
	unpcklpd	%xmm0, %xmm0
	cvtpd2ps	%xmm0, %xmm0
	movl	-1236(%rbp), %eax
	cltq
	movss	%xmm0, -1200(%rbp,%rax,4)
	cvtsi2sd	-1236(%rbp), %xmm0
	movsd	.LC2(%rip), %xmm1
	mulsd	%xmm1, %xmm0
	unpcklpd	%xmm0, %xmm0
	cvtpd2ps	%xmm0, %xmm0
	movl	-1236(%rbp), %eax
	cltq
	movss	%xmm0, -800(%rbp,%rax,4)
	addl	$1, -1236(%rbp)
.L2:
	cmpl	$99, -1236(%rbp)
	jle	.L3
	leaq	-400(%rbp), %rsi
	movl	$0, %eax
	movl	$50, %edx
	movq	%rsi, %rdi
	movq	%rdx, %rcx
	rep stosq
	movl	$0, -1232(%rbp)
	jmp	.L4
.L5:
	movl	-1232(%rbp), %eax
	cltq
	movss	-1200(%rbp,%rax,4), %xmm0
	movaps	%xmm0, %xmm1
	mulss	-1228(%rbp), %xmm1
	movl	-1232(%rbp), %eax
	cltq
	movss	-800(%rbp,%rax,4), %xmm0
	mulss	-1224(%rbp), %xmm0
	addss	%xmm1, %xmm0
	movl	-1232(%rbp), %eax
	cltq
	movss	%xmm0, -400(%rbp,%rax,4)
	movl	-1232(%rbp), %eax
	cltq
	movl	-800(%rbp,%rax,4), %eax
	movl	%eax, -1220(%rbp)
	addl	$1, -1232(%rbp)
.L4:
	cmpl	$99, -1232(%rbp)
	jle	.L5
	call	omp_get_wtime
	subsd	-1216(%rbp), %xmm0
	movsd	.LC3(%rip), %xmm1
	mulsd	%xmm1, %xmm0
	movsd	%xmm0, -1208(%rbp)
	movq	-1208(%rbp), %rax
	movq	%rax, -1256(%rbp)
	movsd	-1256(%rbp), %xmm0
	movl	$.LC4, %edi
	movl	$1, %eax
	call	printf
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.section	.rodata
	.align 4
.LC0:
	.long	1073741824
	.align 4
.LC1:
	.long	1077936128
	.align 8
.LC2:
	.long	0
	.long	1074266112
	.align 8
.LC3:
	.long	0
	.long	1093567616
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits

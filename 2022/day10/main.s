	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 13, 0	sdk_version 13, 0
	.globl	_doPart1                        ## -- Begin function doPart1
	.p2align	4, 0x90
_doPart1:                               ## @doPart1
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, -28(%rbp)
	cmpl	$20, -28(%rbp)
	je	LBB0_6
## %bb.1:
	cmpl	$60, -28(%rbp)
	je	LBB0_6
## %bb.2:
	cmpl	$100, -28(%rbp)
	je	LBB0_6
## %bb.3:
	cmpl	$140, -28(%rbp)
	je	LBB0_6
## %bb.4:
	cmpl	$180, -28(%rbp)
	je	LBB0_6
## %bb.5:
	cmpl	$220, -28(%rbp)
	jne	LBB0_7
LBB0_6:
	movq	-8(%rbp), %rax
	movl	(%rax), %ecx
	movq	-24(%rbp), %rax
	imull	(%rax), %ecx
	movq	-16(%rbp), %rax
	addl	(%rax), %ecx
	movl	%ecx, (%rax)
LBB0_7:
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_drawCRT                        ## -- Begin function drawCRT
	.p2align	4, 0x90
_drawCRT:                               ## @drawCRT
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, -20(%rbp)
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, -24(%rbp)
	movl	-24(%rbp), %eax
	subl	$1, %eax
	cmpl	-20(%rbp), %eax
	jg	LBB1_3
## %bb.1:
	movl	-24(%rbp), %eax
	addl	$1, %eax
	cmpl	-20(%rbp), %eax
	jl	LBB1_3
## %bb.2:
	leaq	L_.str(%rip), %rdi
	movb	$0, %al
	callq	_printf
	jmp	LBB1_4
LBB1_3:
	leaq	L_.str.1(%rip), %rdi
	movb	$0, %al
	callq	_printf
LBB1_4:
	movq	-8(%rbp), %rax
	movl	(%rax), %ecx
	addl	$1, %ecx
	movq	-8(%rbp), %rax
	movl	%ecx, (%rax)
	movq	-8(%rbp), %rax
	cmpl	$40, (%rax)
	jne	LBB1_6
## %bb.5:
	leaq	L_.str.2(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movq	-8(%rbp), %rax
	movl	$0, (%rax)
LBB1_6:
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_main                           ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$64, %rsp
	movq	___stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	movl	$0, -24(%rbp)
	leaq	L_.str.3(%rip), %rdi
	leaq	L_.str.4(%rip), %rsi
	callq	_fopen
	movq	%rax, -32(%rbp)
	movl	$0, -36(%rbp)
	movl	$0, -40(%rbp)
	movl	$1, -44(%rbp)
	movl	$2147483647, -48(%rbp)          ## imm = 0x7FFFFFFF
	movl	$2147483647, -52(%rbp)          ## imm = 0x7FFFFFFF
	movl	$0, -56(%rbp)
	leaq	L_.str.5(%rip), %rdi
	movb	$0, %al
	callq	_printf
LBB2_1:                                 ## =>This Inner Loop Header: Depth=1
	movl	-40(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -40(%rbp)
	leaq	-40(%rbp), %rdi
	leaq	-36(%rbp), %rsi
	leaq	-44(%rbp), %rdx
	callq	_doPart1
	leaq	-56(%rbp), %rdi
	leaq	-44(%rbp), %rsi
	callq	_drawCRT
	movl	-52(%rbp), %eax
	movl	%eax, -48(%rbp)
	movl	$2147483647, -52(%rbp)          ## imm = 0x7FFFFFFF
	cmpl	$2147483647, -48(%rbp)          ## imm = 0x7FFFFFFF
	je	LBB2_3
## %bb.2:                               ##   in Loop: Header=BB2_1 Depth=1
	movl	-48(%rbp), %eax
	addl	-44(%rbp), %eax
	movl	%eax, -44(%rbp)
	jmp	LBB2_4
LBB2_3:                                 ##   in Loop: Header=BB2_1 Depth=1
	leaq	-18(%rbp), %rdi
	movq	-32(%rbp), %rdx
	movl	$10, %esi
	callq	_fgets
LBB2_4:                                 ##   in Loop: Header=BB2_1 Depth=1
	movsbl	-18(%rbp), %eax
	cmpl	$97, %eax
	jne	LBB2_6
## %bb.5:                               ##   in Loop: Header=BB2_1 Depth=1
	leaq	-18(%rbp), %rdi
	leaq	L_.str.6(%rip), %rsi
	leaq	-60(%rbp), %rdx
	movb	$0, %al
	callq	_sscanf
	movl	-60(%rbp), %eax
	movl	%eax, -52(%rbp)
	jmp	LBB2_11
LBB2_6:                                 ##   in Loop: Header=BB2_1 Depth=1
	movsbl	-18(%rbp), %eax
	cmpl	$110, %eax
	je	LBB2_10
## %bb.7:                               ##   in Loop: Header=BB2_1 Depth=1
	cmpl	$2147483647, -48(%rbp)          ## imm = 0x7FFFFFFF
	jne	LBB2_10
## %bb.8:                               ##   in Loop: Header=BB2_1 Depth=1
	cmpl	$2147483647, -52(%rbp)          ## imm = 0x7FFFFFFF
	jne	LBB2_10
## %bb.9:
	jmp	LBB2_12
LBB2_10:                                ##   in Loop: Header=BB2_1 Depth=1
	jmp	LBB2_11
LBB2_11:                                ##   in Loop: Header=BB2_1 Depth=1
	leaq	-18(%rbp), %rdi
	xorl	%esi, %esi
	movl	$10, %edx
	callq	_memset
	jmp	LBB2_1
LBB2_12:
	movq	-32(%rbp), %rdi
	callq	_fclose
	movl	-36(%rbp), %esi
	leaq	L_.str.7(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	-24(%rbp), %eax
	movl	%eax, -64(%rbp)                 ## 4-byte Spill
	movq	___stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rax
	movq	-8(%rbp), %rcx
	cmpq	%rcx, %rax
	jne	LBB2_14
## %bb.13:
	movl	-64(%rbp), %eax                 ## 4-byte Reload
	addq	$64, %rsp
	popq	%rbp
	retq
LBB2_14:
	callq	___stack_chk_fail
	ud2
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"\342\226\210"

L_.str.1:                               ## @.str.1
	.asciz	" "

L_.str.2:                               ## @.str.2
	.asciz	"\n"

L_.str.3:                               ## @.str.3
	.asciz	"input"

L_.str.4:                               ## @.str.4
	.asciz	"r"

L_.str.5:                               ## @.str.5
	.asciz	"Part 2:\n"

L_.str.6:                               ## @.str.6
	.asciz	"%*s %d"

L_.str.7:                               ## @.str.7
	.asciz	"Part 1: %d \n"

.subsections_via_symbols

	.file	"PerformanceTests.cpp"
	.section .rdata,"dr"
__ZStL19piecewise_construct:
	.space 1
	.section	.text$_ZnwjPv,"x"
	.linkonce discard
	.globl	__ZnwjPv
	.def	__ZnwjPv;	.scl	2;	.type	32;	.endef
__ZnwjPv:
LFB737:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	12(%ebp), %eax
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE737:
	.section .rdata,"dr"
__ZStL13allocator_arg:
	.space 1
__ZStL6ignore:
	.space 1
	.section	.text$_ZNSt9_Any_data9_M_accessEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZNSt9_Any_data9_M_accessEv
	.def	__ZNSt9_Any_data9_M_accessEv;	.scl	2;	.type	32;	.endef
__ZNSt9_Any_data9_M_accessEv:
LFB2169:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2169:
	.section	.text$_ZNKSt9_Any_data9_M_accessEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZNKSt9_Any_data9_M_accessEv
	.def	__ZNKSt9_Any_data9_M_accessEv;	.scl	2;	.type	32;	.endef
__ZNKSt9_Any_data9_M_accessEv:
LFB2170:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2170:
	.section	.text$_ZNSt14_Function_baseC2Ev,"x"
	.linkonce discard
	.align 2
	.globl	__ZNSt14_Function_baseC2Ev
	.def	__ZNSt14_Function_baseC2Ev;	.scl	2;	.type	32;	.endef
__ZNSt14_Function_baseC2Ev:
LFB2195:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	$0, 8(%eax)
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2195:
	.section	.text$_ZNSt14_Function_baseD2Ev,"x"
	.linkonce discard
	.align 2
	.globl	__ZNSt14_Function_baseD2Ev
	.def	__ZNSt14_Function_baseD2Ev;	.scl	2;	.type	32;	.endef
__ZNSt14_Function_baseD2Ev:
LFB2198:
	.cfi_startproc
	.cfi_personality 0,___gxx_personality_v0
	.cfi_lsda 0,LLSDA2198
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	8(%eax), %eax
	testl	%eax, %eax
	je	L10
	movl	-12(%ebp), %eax
	movl	8(%eax), %eax
	movl	-12(%ebp), %ecx
	movl	-12(%ebp), %edx
	movl	$3, 8(%esp)
	movl	%ecx, 4(%esp)
	movl	%edx, (%esp)
	call	*%eax
L10:
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2198:
	.def	___gxx_personality_v0;	.scl	2;	.type	32;	.endef
	.section	.gcc_except_table,"w"
LLSDA2198:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 LLSDACSE2198-LLSDACSB2198
LLSDACSB2198:
LLSDACSE2198:
	.section	.text$_ZNSt14_Function_baseD2Ev,"x"
	.linkonce discard
	.text
	.globl	__Z5voidFv
	.def	__Z5voidFv;	.scl	2;	.type	32;	.endef
__Z5voidFv:
LFB2395:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	nop
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2395:
	.section	.text$_ZNSt7__cxx114listIdSaIdEED1Ev,"x"
	.linkonce discard
	.align 2
	.globl	__ZNSt7__cxx114listIdSaIdEED1Ev
	.def	__ZNSt7__cxx114listIdSaIdEED1Ev;	.scl	2;	.type	32;	.endef
__ZNSt7__cxx114listIdSaIdEED1Ev:
LFB2400:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNSt7__cxx1110_List_baseIdSaIdEED2Ev
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2400:
	.section	.text$_ZN12TestTemplateD1Ev,"x"
	.linkonce discard
	.align 2
	.globl	__ZN12TestTemplateD1Ev
	.def	__ZN12TestTemplateD1Ev;	.scl	2;	.type	32;	.endef
__ZN12TestTemplateD1Ev:
LFB2402:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	addl	$28, %eax
	movl	%eax, %ecx
	call	__ZNSt14basic_ofstreamIcSt11char_traitsIcEED1Ev
	movl	-12(%ebp), %eax
	addl	$16, %eax
	movl	%eax, %ecx
	call	__ZNSt7__cxx114listIdSaIdEED1Ev
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2402:
	.text
	.align 2
	.def	__ZZ4mainENKUlvE_clEv;	.scl	3;	.type	32;	.endef
__ZZ4mainENKUlvE_clEv:
LFB2403:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$20, %esp
	movl	%ecx, -20(%ebp)
	movl	$0, -4(%ebp)
L17:
	cmpl	$9999999, -4(%ebp)
	jg	L18
	addl	$1, -4(%ebp)
	jmp	L17
L18:
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2403:
	.section	.text$_ZNSt8functionIFvvEED1Ev,"x"
	.linkonce discard
	.align 2
	.globl	__ZNSt8functionIFvvEED1Ev
	.def	__ZNSt8functionIFvvEED1Ev;	.scl	2;	.type	32;	.endef
__ZNSt8functionIFvvEED1Ev:
LFB2408:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNSt14_Function_baseD2Ev
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2408:
	.text
	.align 2
	.def	__ZZ4mainENKUlvE0_clEv;	.scl	3;	.type	32;	.endef
__ZZ4mainENKUlvE0_clEv:
LFB2409:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$20, %esp
	movl	%ecx, -20(%ebp)
	movl	$0, -4(%ebp)
L22:
	cmpl	$9999999, -4(%ebp)
	jg	L23
	addl	$1, -4(%ebp)
	jmp	L22
L23:
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2409:
	.align 2
	.def	__ZZ4mainENKUlvE1_clEv;	.scl	3;	.type	32;	.endef
__ZZ4mainENKUlvE1_clEv:
LFB2412:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$20, %esp
	movl	%ecx, -20(%ebp)
	movl	$0, -4(%ebp)
L26:
	cmpl	$9999999, -4(%ebp)
	jg	L27
	movl	-20(%ebp), %eax
	movl	(%eax), %eax
	movl	-4(%ebp), %edx
	movl	%edx, (%eax)
	addl	$1, -4(%ebp)
	jmp	L26
L27:
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2412:
	.align 2
	.def	__ZZ4mainENKUlvE2_clEv;	.scl	3;	.type	32;	.endef
__ZZ4mainENKUlvE2_clEv:
LFB2413:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$20, %esp
	movl	%ecx, -20(%ebp)
	movl	$0, -4(%ebp)
L30:
	cmpl	$9999999, -4(%ebp)
	jg	L31
	call	__Z5voidFv
	addl	$1, -4(%ebp)
	jmp	L30
L31:
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2413:
	.align 2
	.def	__ZZ4mainENKUlvE3_clEv;	.scl	3;	.type	32;	.endef
__ZZ4mainENKUlvE3_clEv:
LFB2416:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$36, %esp
	.cfi_offset 3, -12
	movl	%ecx, -28(%ebp)
	movl	$0, -12(%ebp)
L34:
	cmpl	$9999999, -12(%ebp)
	jg	L35
	movl	-28(%ebp), %eax
	movl	(%eax), %ebx
	call	_rand
	movl	%eax, (%ebx)
	addl	$1, -12(%ebp)
	jmp	L34
L35:
	nop
	addl	$36, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2416:
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC0:
	.ascii "bin/PerformanceResults.txt\0"
	.align 4
LC1:
	.ascii "----------------------------------------------------\12|\0"
	.align 4
LC2:
	.ascii "Void For 10000000 Loop with I++\0"
LC3:
	.ascii "01\0"
	.align 4
LC4:
	.ascii "| L15:\12|  cmpl\11$9999999, -4(%ebp)\12|  jg\11L16\12|  addl\11$1, -4(%ebp)\12|  jmp\11L15\12|\12|\0"
	.align 4
LC5:
	.ascii "Void For 10000000 Loop with ++I\0"
LC6:
	.ascii "02\0"
	.align 4
LC7:
	.ascii "| L20:\12|  cmpl\11$9999999, -4(%ebp)\12|  jg\11L21\12|  addl\11$1, -4(%ebp)\12|  jmp\11L20\12|\12|\0"
	.align 4
LC8:
	.ascii "Averaged cost of 20000000 MOVL - Simple assignment (=)\0"
LC9:
	.ascii "03\0"
	.align 4
LC10:
	.ascii "| L24:\12|  cmpl\11$9999999, -4(%ebp)\12|  jg\11L25\12|  movl\11-4(%ebp), %eax\12|  movl\11%eax, -8(%ebp)\12|  addl\11$1, -4(%ebp)\12|  jmp\11L24\12|\12|\0"
LC11:
	.ascii "Cost of calling void function\0"
LC12:
	.ascii "04\0"
	.align 4
LC13:
	.ascii "| L30:\12|  cmpl\11$9999999, -4(%ebp)\12|  jg\11L31\12|  call\11__Z5voidFv\12|  addl\11$1, -4(%ebp)\12|  jmp\11L30\12|\12|\0"
LC14:
	.ascii "Cost of calling rand()\0"
LC15:
	.ascii "05\0"
	.align 4
LC16:
	.ascii "\12| L34:\12|  cmpl\11$9999999, -12(%ebp)\12|  jg\11L35\12|  movl\11-28(%ebp), %eax\12|  movl\11(%eax), %ebx\12|  call\11_rand\12|  movl\11%eax, (%ebx)\12|  addl\11$1, -12(%ebp)\12|  jmp\11L34\0"
	.align 4
LC17:
	.ascii "----------------------------------------------------\0"
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
LFB2396:
	.cfi_startproc
	.cfi_personality 0,___gxx_personality_v0
	.cfi_lsda 0,LLSDA2396
	leal	4(%esp), %ecx
	.cfi_def_cfa 1, 0
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%ecx
	.cfi_escape 0xf,0x3,0x75,0x78,0x6
	.cfi_escape 0x10,0x3,0x2,0x75,0x7c
	subl	$432, %esp
	call	___main
	movb	$1, -9(%ebp)
	leal	-392(%ebp), %eax
	movl	$LC0, (%esp)
	movl	%eax, %ecx
LEHB0:
	call	__ZN12TestTemplateC1EPKc
LEHE0:
	subl	$4, %esp
	leal	-392(%ebp), %eax
	movl	$1, 4(%esp)
	movl	$LC1, (%esp)
	movl	%eax, %ecx
LEHB1:
	call	__ZN12TestTemplate29WriteMessageIntoScreenAndFileEPKcb
	subl	$8, %esp
	leal	-112(%ebp), %eax
	movzbl	-414(%ebp), %edx
	movb	%dl, (%esp)
	movl	%eax, %ecx
	call	__ZNSt8functionIFvvEEC1IZ4mainEUlvE_vvEET_
LEHE1:
	subl	$4, %esp
	leal	-392(%ebp), %eax
	leal	-112(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
LEHB2:
	call	__ZN12TestTemplate11ExecuteTestESt8functionIFvvEE
LEHE2:
	subl	$4, %esp
	leal	-112(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNSt8functionIFvvEED1Ev
	leal	-392(%ebp), %eax
	movl	%eax, %ecx
LEHB3:
	call	__ZN12TestTemplate20CalculateAverageTimeEv
	fstps	-16(%ebp)
	leal	-392(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN12TestTemplate20CalculateAverageTimeEv
	leal	-392(%ebp), %eax
	fstpl	8(%esp)
	movl	$LC2, 4(%esp)
	movl	$LC3, (%esp)
	movl	%eax, %ecx
	call	__ZN12TestTemplate33WriteTestResultsIntoScreenAndFileEPKcS1_d
	subl	$16, %esp
	movzbl	-9(%ebp), %edx
	leal	-392(%ebp), %eax
	movl	%edx, 4(%esp)
	movl	$LC4, (%esp)
	movl	%eax, %ecx
	call	__ZN12TestTemplate29WriteMessageIntoScreenAndFileEPKcb
	subl	$8, %esp
	leal	-92(%ebp), %eax
	movzbl	-413(%ebp), %edx
	movb	%dl, (%esp)
	movl	%eax, %ecx
	call	__ZNSt8functionIFvvEEC1IZ4mainEUlvE0_vvEET_
LEHE3:
	subl	$4, %esp
	leal	-392(%ebp), %eax
	leal	-92(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
LEHB4:
	call	__ZN12TestTemplate11ExecuteTestESt8functionIFvvEE
LEHE4:
	subl	$4, %esp
	leal	-92(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNSt8functionIFvvEED1Ev
	leal	-392(%ebp), %eax
	movl	%eax, %ecx
LEHB5:
	call	__ZN12TestTemplate20CalculateAverageTimeEv
	leal	-392(%ebp), %eax
	fstpl	8(%esp)
	movl	$LC5, 4(%esp)
	movl	$LC6, (%esp)
	movl	%eax, %ecx
	call	__ZN12TestTemplate33WriteTestResultsIntoScreenAndFileEPKcS1_d
	subl	$16, %esp
	movzbl	-9(%ebp), %edx
	leal	-392(%ebp), %eax
	movl	%edx, 4(%esp)
	movl	$LC7, (%esp)
	movl	%eax, %ecx
	call	__ZN12TestTemplate29WriteMessageIntoScreenAndFileEPKcb
	subl	$8, %esp
	leal	-396(%ebp), %eax
	movl	%eax, %edx
	leal	-72(%ebp), %eax
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZNSt8functionIFvvEEC1IZ4mainEUlvE1_vvEET_
LEHE5:
	subl	$4, %esp
	leal	-392(%ebp), %eax
	leal	-72(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
LEHB6:
	call	__ZN12TestTemplate11ExecuteTestESt8functionIFvvEE
LEHE6:
	subl	$4, %esp
	leal	-72(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNSt8functionIFvvEED1Ev
	leal	-392(%ebp), %eax
	movl	%eax, %ecx
LEHB7:
	call	__ZN12TestTemplate20CalculateAverageTimeEv
	flds	-16(%ebp)
	fsubrp	%st, %st(1)
	fstps	-20(%ebp)
	flds	-20(%ebp)
	leal	-392(%ebp), %eax
	fstpl	8(%esp)
	movl	$LC8, 4(%esp)
	movl	$LC9, (%esp)
	movl	%eax, %ecx
	call	__ZN12TestTemplate33WriteTestResultsIntoScreenAndFileEPKcS1_d
	subl	$16, %esp
	movzbl	-9(%ebp), %edx
	leal	-392(%ebp), %eax
	movl	%edx, 4(%esp)
	movl	$LC10, (%esp)
	movl	%eax, %ecx
	call	__ZN12TestTemplate29WriteMessageIntoScreenAndFileEPKcb
	subl	$8, %esp
	leal	-56(%ebp), %eax
	movb	%bl, (%esp)
	movl	%eax, %ecx
	call	__ZNSt8functionIFvvEEC1IZ4mainEUlvE2_vvEET_
LEHE7:
	subl	$4, %esp
	leal	-392(%ebp), %eax
	leal	-56(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
LEHB8:
	call	__ZN12TestTemplate11ExecuteTestESt8functionIFvvEE
LEHE8:
	subl	$4, %esp
	leal	-56(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNSt8functionIFvvEED1Ev
	leal	-392(%ebp), %eax
	movl	%eax, %ecx
LEHB9:
	call	__ZN12TestTemplate20CalculateAverageTimeEv
	flds	-16(%ebp)
	fsubrp	%st, %st(1)
	leal	-392(%ebp), %eax
	fstpl	8(%esp)
	movl	$LC11, 4(%esp)
	movl	$LC12, (%esp)
	movl	%eax, %ecx
	call	__ZN12TestTemplate33WriteTestResultsIntoScreenAndFileEPKcS1_d
	subl	$16, %esp
	movzbl	-9(%ebp), %edx
	leal	-392(%ebp), %eax
	movl	%edx, 4(%esp)
	movl	$LC13, (%esp)
	movl	%eax, %ecx
	call	__ZN12TestTemplate29WriteMessageIntoScreenAndFileEPKcb
	subl	$8, %esp
	leal	-396(%ebp), %eax
	movl	%eax, %edx
	leal	-36(%ebp), %eax
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZNSt8functionIFvvEEC1IZ4mainEUlvE3_vvEET_
LEHE9:
	subl	$4, %esp
	leal	-392(%ebp), %eax
	leal	-36(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
LEHB10:
	call	__ZN12TestTemplate11ExecuteTestESt8functionIFvvEE
LEHE10:
	subl	$4, %esp
	leal	-36(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNSt8functionIFvvEED1Ev
	leal	-392(%ebp), %eax
	movl	%eax, %ecx
LEHB11:
	call	__ZN12TestTemplate20CalculateAverageTimeEv
	flds	-16(%ebp)
	fsubrp	%st, %st(1)
	flds	-20(%ebp)
	fsubrp	%st, %st(1)
	leal	-392(%ebp), %eax
	fstpl	8(%esp)
	movl	$LC14, 4(%esp)
	movl	$LC15, (%esp)
	movl	%eax, %ecx
	call	__ZN12TestTemplate33WriteTestResultsIntoScreenAndFileEPKcS1_d
	subl	$16, %esp
	movzbl	-9(%ebp), %edx
	leal	-392(%ebp), %eax
	movl	%edx, 4(%esp)
	movl	$LC16, (%esp)
	movl	%eax, %ecx
	call	__ZN12TestTemplate29WriteMessageIntoScreenAndFileEPKcb
	subl	$8, %esp
	leal	-392(%ebp), %eax
	movl	$1, 4(%esp)
	movl	$LC17, (%esp)
	movl	%eax, %ecx
	call	__ZN12TestTemplate29WriteMessageIntoScreenAndFileEPKcb
LEHE11:
	subl	$8, %esp
	movl	$0, %ebx
	leal	-392(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN12TestTemplateD1Ev
	movl	%ebx, %eax
	jmp	L50
L45:
	movl	%eax, %ebx
	leal	-112(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNSt8functionIFvvEED1Ev
	jmp	L39
L46:
	movl	%eax, %ebx
	leal	-92(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNSt8functionIFvvEED1Ev
	jmp	L39
L47:
	movl	%eax, %ebx
	leal	-72(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNSt8functionIFvvEED1Ev
	jmp	L39
L48:
	movl	%eax, %ebx
	leal	-56(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNSt8functionIFvvEED1Ev
	jmp	L39
L49:
	movl	%eax, %ebx
	leal	-36(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNSt8functionIFvvEED1Ev
	jmp	L39
L44:
	movl	%eax, %ebx
L39:
	leal	-392(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN12TestTemplateD1Ev
	movl	%ebx, %eax
	movl	%eax, (%esp)
LEHB12:
	call	__Unwind_Resume
LEHE12:
L50:
	leal	-8(%ebp), %esp
	popl	%ecx
	.cfi_restore 1
	.cfi_def_cfa 1, 0
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	leal	-4(%ecx), %esp
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2396:
	.section	.gcc_except_table,"w"
LLSDA2396:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 LLSDACSE2396-LLSDACSB2396
LLSDACSB2396:
	.uleb128 LEHB0-LFB2396
	.uleb128 LEHE0-LEHB0
	.uleb128 0
	.uleb128 0
	.uleb128 LEHB1-LFB2396
	.uleb128 LEHE1-LEHB1
	.uleb128 L44-LFB2396
	.uleb128 0
	.uleb128 LEHB2-LFB2396
	.uleb128 LEHE2-LEHB2
	.uleb128 L45-LFB2396
	.uleb128 0
	.uleb128 LEHB3-LFB2396
	.uleb128 LEHE3-LEHB3
	.uleb128 L44-LFB2396
	.uleb128 0
	.uleb128 LEHB4-LFB2396
	.uleb128 LEHE4-LEHB4
	.uleb128 L46-LFB2396
	.uleb128 0
	.uleb128 LEHB5-LFB2396
	.uleb128 LEHE5-LEHB5
	.uleb128 L44-LFB2396
	.uleb128 0
	.uleb128 LEHB6-LFB2396
	.uleb128 LEHE6-LEHB6
	.uleb128 L47-LFB2396
	.uleb128 0
	.uleb128 LEHB7-LFB2396
	.uleb128 LEHE7-LEHB7
	.uleb128 L44-LFB2396
	.uleb128 0
	.uleb128 LEHB8-LFB2396
	.uleb128 LEHE8-LEHB8
	.uleb128 L48-LFB2396
	.uleb128 0
	.uleb128 LEHB9-LFB2396
	.uleb128 LEHE9-LEHB9
	.uleb128 L44-LFB2396
	.uleb128 0
	.uleb128 LEHB10-LFB2396
	.uleb128 LEHE10-LEHB10
	.uleb128 L49-LFB2396
	.uleb128 0
	.uleb128 LEHB11-LFB2396
	.uleb128 LEHE11-LEHB11
	.uleb128 L44-LFB2396
	.uleb128 0
	.uleb128 LEHB12-LFB2396
	.uleb128 LEHE12-LEHB12
	.uleb128 0
	.uleb128 0
LLSDACSE2396:
	.text
	.section	.text$_ZNSt7__cxx1110_List_baseIdSaIdEE10_List_implD1Ev,"x"
	.linkonce discard
	.align 2
	.globl	__ZNSt7__cxx1110_List_baseIdSaIdEE10_List_implD1Ev
	.def	__ZNSt7__cxx1110_List_baseIdSaIdEE10_List_implD1Ev;	.scl	2;	.type	32;	.endef
__ZNSt7__cxx1110_List_baseIdSaIdEE10_List_implD1Ev:
LFB2648:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNSaISt10_List_nodeIdEED2Ev
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2648:
	.section	.text$_ZNSt7__cxx1110_List_baseIdSaIdEED2Ev,"x"
	.linkonce discard
	.align 2
	.globl	__ZNSt7__cxx1110_List_baseIdSaIdEED2Ev
	.def	__ZNSt7__cxx1110_List_baseIdSaIdEED2Ev;	.scl	2;	.type	32;	.endef
__ZNSt7__cxx1110_List_baseIdSaIdEED2Ev:
LFB2649:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNSt7__cxx1110_List_baseIdSaIdEE8_M_clearEv
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNSt7__cxx1110_List_baseIdSaIdEE10_List_implD1Ev
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2649:
	.section	.text$_ZNSt31_Maybe_unary_or_binary_functionIvJEEC2Ev,"x"
	.linkonce discard
	.align 2
	.globl	__ZNSt31_Maybe_unary_or_binary_functionIvJEEC2Ev
	.def	__ZNSt31_Maybe_unary_or_binary_functionIvJEEC2Ev;	.scl	2;	.type	32;	.endef
__ZNSt31_Maybe_unary_or_binary_functionIvJEEC2Ev:
LFB2657:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2657:
	.text
	.def	__ZSt4moveIRZ4mainEUlvE_EONSt16remove_referenceIT_E4typeEOS3_;	.scl	3;	.type	32;	.endef
__ZSt4moveIRZ4mainEUlvE_EONSt16remove_referenceIT_E4typeEOS3_:
LFB2659:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	8(%ebp), %eax
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2659:
	.align 2
	.def	__ZNSt8functionIFvvEEC2IZ4mainEUlvE_vvEET_;	.scl	3;	.type	32;	.endef
__ZNSt8functionIFvvEEC2IZ4mainEUlvE_vvEET_:
LFB2660:
	.cfi_startproc
	.cfi_personality 0,___gxx_personality_v0
	.cfi_lsda 0,LLSDA2660
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$36, %esp
	.cfi_offset 3, -12
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNSt31_Maybe_unary_or_binary_functionIvJEEC2Ev
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNSt14_Function_baseC2Ev
	leal	8(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE_E21_M_not_empty_functionIS1_EEbRKT_
	testb	%al, %al
	je	L60
	leal	8(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZSt4moveIRZ4mainEUlvE_EONSt16remove_referenceIT_E4typeEOS3_
	movl	%eax, %edx
	movl	-12(%ebp), %eax
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
LEHB13:
	call	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE_E15_M_init_functorERSt9_Any_dataOS1_
LEHE13:
	movl	-12(%ebp), %eax
	movl	$__ZNSt17_Function_handlerIFvvEZ4mainEUlvE_E9_M_invokeERKSt9_Any_data, 12(%eax)
	movl	-12(%ebp), %eax
	movl	$__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE_E10_M_managerERSt9_Any_dataRKS3_St18_Manager_operation, 8(%eax)
	jmp	L60
L59:
	movl	%eax, %ebx
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNSt14_Function_baseD2Ev
	movl	%ebx, %eax
	movl	%eax, (%esp)
LEHB14:
	call	__Unwind_Resume
LEHE14:
L60:
	nop
	addl	$36, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	$4
	.cfi_endproc
LFE2660:
	.section	.gcc_except_table,"w"
LLSDA2660:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 LLSDACSE2660-LLSDACSB2660
LLSDACSB2660:
	.uleb128 LEHB13-LFB2660
	.uleb128 LEHE13-LEHB13
	.uleb128 L59-LFB2660
	.uleb128 0
	.uleb128 LEHB14-LFB2660
	.uleb128 LEHE14-LEHB14
	.uleb128 0
	.uleb128 0
LLSDACSE2660:
	.text
	.def	__ZNSt8functionIFvvEEC1IZ4mainEUlvE_vvEET_;	.scl	3;	.type	32;	.endef
	.set	__ZNSt8functionIFvvEEC1IZ4mainEUlvE_vvEET_,__ZNSt8functionIFvvEEC2IZ4mainEUlvE_vvEET_
	.def	__ZSt4moveIRZ4mainEUlvE0_EONSt16remove_referenceIT_E4typeEOS3_;	.scl	3;	.type	32;	.endef
__ZSt4moveIRZ4mainEUlvE0_EONSt16remove_referenceIT_E4typeEOS3_:
LFB2666:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	8(%ebp), %eax
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2666:
	.align 2
	.def	__ZNSt8functionIFvvEEC2IZ4mainEUlvE0_vvEET_;	.scl	3;	.type	32;	.endef
__ZNSt8functionIFvvEEC2IZ4mainEUlvE0_vvEET_:
LFB2667:
	.cfi_startproc
	.cfi_personality 0,___gxx_personality_v0
	.cfi_lsda 0,LLSDA2667
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$36, %esp
	.cfi_offset 3, -12
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNSt31_Maybe_unary_or_binary_functionIvJEEC2Ev
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNSt14_Function_baseC2Ev
	leal	8(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE0_E21_M_not_empty_functionIS1_EEbRKT_
	testb	%al, %al
	je	L67
	leal	8(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZSt4moveIRZ4mainEUlvE0_EONSt16remove_referenceIT_E4typeEOS3_
	movl	%eax, %edx
	movl	-12(%ebp), %eax
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
LEHB15:
	call	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE0_E15_M_init_functorERSt9_Any_dataOS1_
LEHE15:
	movl	-12(%ebp), %eax
	movl	$__ZNSt17_Function_handlerIFvvEZ4mainEUlvE0_E9_M_invokeERKSt9_Any_data, 12(%eax)
	movl	-12(%ebp), %eax
	movl	$__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE0_E10_M_managerERSt9_Any_dataRKS3_St18_Manager_operation, 8(%eax)
	jmp	L67
L66:
	movl	%eax, %ebx
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNSt14_Function_baseD2Ev
	movl	%ebx, %eax
	movl	%eax, (%esp)
LEHB16:
	call	__Unwind_Resume
LEHE16:
L67:
	nop
	addl	$36, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	$4
	.cfi_endproc
LFE2667:
	.section	.gcc_except_table,"w"
LLSDA2667:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 LLSDACSE2667-LLSDACSB2667
LLSDACSB2667:
	.uleb128 LEHB15-LFB2667
	.uleb128 LEHE15-LEHB15
	.uleb128 L66-LFB2667
	.uleb128 0
	.uleb128 LEHB16-LFB2667
	.uleb128 LEHE16-LEHB16
	.uleb128 0
	.uleb128 0
LLSDACSE2667:
	.text
	.def	__ZNSt8functionIFvvEEC1IZ4mainEUlvE0_vvEET_;	.scl	3;	.type	32;	.endef
	.set	__ZNSt8functionIFvvEEC1IZ4mainEUlvE0_vvEET_,__ZNSt8functionIFvvEEC2IZ4mainEUlvE0_vvEET_
	.def	__ZSt4moveIRZ4mainEUlvE1_EONSt16remove_referenceIT_E4typeEOS3_;	.scl	3;	.type	32;	.endef
__ZSt4moveIRZ4mainEUlvE1_EONSt16remove_referenceIT_E4typeEOS3_:
LFB2670:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	8(%ebp), %eax
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2670:
	.align 2
	.def	__ZNSt8functionIFvvEEC2IZ4mainEUlvE1_vvEET_;	.scl	3;	.type	32;	.endef
__ZNSt8functionIFvvEEC2IZ4mainEUlvE1_vvEET_:
LFB2671:
	.cfi_startproc
	.cfi_personality 0,___gxx_personality_v0
	.cfi_lsda 0,LLSDA2671
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$36, %esp
	.cfi_offset 3, -12
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNSt31_Maybe_unary_or_binary_functionIvJEEC2Ev
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNSt14_Function_baseC2Ev
	leal	8(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE1_E21_M_not_empty_functionIS1_EEbRKT_
	testb	%al, %al
	je	L74
	leal	8(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZSt4moveIRZ4mainEUlvE1_EONSt16remove_referenceIT_E4typeEOS3_
	movl	%eax, %edx
	movl	-12(%ebp), %eax
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
LEHB17:
	call	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE1_E15_M_init_functorERSt9_Any_dataOS1_
LEHE17:
	movl	-12(%ebp), %eax
	movl	$__ZNSt17_Function_handlerIFvvEZ4mainEUlvE1_E9_M_invokeERKSt9_Any_data, 12(%eax)
	movl	-12(%ebp), %eax
	movl	$__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE1_E10_M_managerERSt9_Any_dataRKS3_St18_Manager_operation, 8(%eax)
	jmp	L74
L73:
	movl	%eax, %ebx
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNSt14_Function_baseD2Ev
	movl	%ebx, %eax
	movl	%eax, (%esp)
LEHB18:
	call	__Unwind_Resume
LEHE18:
L74:
	nop
	addl	$36, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	$4
	.cfi_endproc
LFE2671:
	.section	.gcc_except_table,"w"
LLSDA2671:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 LLSDACSE2671-LLSDACSB2671
LLSDACSB2671:
	.uleb128 LEHB17-LFB2671
	.uleb128 LEHE17-LEHB17
	.uleb128 L73-LFB2671
	.uleb128 0
	.uleb128 LEHB18-LFB2671
	.uleb128 LEHE18-LEHB18
	.uleb128 0
	.uleb128 0
LLSDACSE2671:
	.text
	.def	__ZNSt8functionIFvvEEC1IZ4mainEUlvE1_vvEET_;	.scl	3;	.type	32;	.endef
	.set	__ZNSt8functionIFvvEEC1IZ4mainEUlvE1_vvEET_,__ZNSt8functionIFvvEEC2IZ4mainEUlvE1_vvEET_
	.def	__ZSt4moveIRZ4mainEUlvE2_EONSt16remove_referenceIT_E4typeEOS3_;	.scl	3;	.type	32;	.endef
__ZSt4moveIRZ4mainEUlvE2_EONSt16remove_referenceIT_E4typeEOS3_:
LFB2674:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	8(%ebp), %eax
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2674:
	.align 2
	.def	__ZNSt8functionIFvvEEC2IZ4mainEUlvE2_vvEET_;	.scl	3;	.type	32;	.endef
__ZNSt8functionIFvvEEC2IZ4mainEUlvE2_vvEET_:
LFB2675:
	.cfi_startproc
	.cfi_personality 0,___gxx_personality_v0
	.cfi_lsda 0,LLSDA2675
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$36, %esp
	.cfi_offset 3, -12
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNSt31_Maybe_unary_or_binary_functionIvJEEC2Ev
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNSt14_Function_baseC2Ev
	leal	8(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE2_E21_M_not_empty_functionIS1_EEbRKT_
	testb	%al, %al
	je	L81
	leal	8(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZSt4moveIRZ4mainEUlvE2_EONSt16remove_referenceIT_E4typeEOS3_
	movl	%eax, %edx
	movl	-12(%ebp), %eax
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
LEHB19:
	call	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE2_E15_M_init_functorERSt9_Any_dataOS1_
LEHE19:
	movl	-12(%ebp), %eax
	movl	$__ZNSt17_Function_handlerIFvvEZ4mainEUlvE2_E9_M_invokeERKSt9_Any_data, 12(%eax)
	movl	-12(%ebp), %eax
	movl	$__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE2_E10_M_managerERSt9_Any_dataRKS3_St18_Manager_operation, 8(%eax)
	jmp	L81
L80:
	movl	%eax, %ebx
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNSt14_Function_baseD2Ev
	movl	%ebx, %eax
	movl	%eax, (%esp)
LEHB20:
	call	__Unwind_Resume
LEHE20:
L81:
	nop
	addl	$36, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	$4
	.cfi_endproc
LFE2675:
	.section	.gcc_except_table,"w"
LLSDA2675:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 LLSDACSE2675-LLSDACSB2675
LLSDACSB2675:
	.uleb128 LEHB19-LFB2675
	.uleb128 LEHE19-LEHB19
	.uleb128 L80-LFB2675
	.uleb128 0
	.uleb128 LEHB20-LFB2675
	.uleb128 LEHE20-LEHB20
	.uleb128 0
	.uleb128 0
LLSDACSE2675:
	.text
	.def	__ZNSt8functionIFvvEEC1IZ4mainEUlvE2_vvEET_;	.scl	3;	.type	32;	.endef
	.set	__ZNSt8functionIFvvEEC1IZ4mainEUlvE2_vvEET_,__ZNSt8functionIFvvEEC2IZ4mainEUlvE2_vvEET_
	.def	__ZSt4moveIRZ4mainEUlvE3_EONSt16remove_referenceIT_E4typeEOS3_;	.scl	3;	.type	32;	.endef
__ZSt4moveIRZ4mainEUlvE3_EONSt16remove_referenceIT_E4typeEOS3_:
LFB2678:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	8(%ebp), %eax
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2678:
	.align 2
	.def	__ZNSt8functionIFvvEEC2IZ4mainEUlvE3_vvEET_;	.scl	3;	.type	32;	.endef
__ZNSt8functionIFvvEEC2IZ4mainEUlvE3_vvEET_:
LFB2679:
	.cfi_startproc
	.cfi_personality 0,___gxx_personality_v0
	.cfi_lsda 0,LLSDA2679
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$36, %esp
	.cfi_offset 3, -12
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNSt31_Maybe_unary_or_binary_functionIvJEEC2Ev
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNSt14_Function_baseC2Ev
	leal	8(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE3_E21_M_not_empty_functionIS1_EEbRKT_
	testb	%al, %al
	je	L88
	leal	8(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZSt4moveIRZ4mainEUlvE3_EONSt16remove_referenceIT_E4typeEOS3_
	movl	%eax, %edx
	movl	-12(%ebp), %eax
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
LEHB21:
	call	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE3_E15_M_init_functorERSt9_Any_dataOS1_
LEHE21:
	movl	-12(%ebp), %eax
	movl	$__ZNSt17_Function_handlerIFvvEZ4mainEUlvE3_E9_M_invokeERKSt9_Any_data, 12(%eax)
	movl	-12(%ebp), %eax
	movl	$__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE3_E10_M_managerERSt9_Any_dataRKS3_St18_Manager_operation, 8(%eax)
	jmp	L88
L87:
	movl	%eax, %ebx
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNSt14_Function_baseD2Ev
	movl	%ebx, %eax
	movl	%eax, (%esp)
LEHB22:
	call	__Unwind_Resume
LEHE22:
L88:
	nop
	addl	$36, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	$4
	.cfi_endproc
LFE2679:
	.section	.gcc_except_table,"w"
LLSDA2679:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 LLSDACSE2679-LLSDACSB2679
LLSDACSB2679:
	.uleb128 LEHB21-LFB2679
	.uleb128 LEHE21-LEHB21
	.uleb128 L87-LFB2679
	.uleb128 0
	.uleb128 LEHB22-LFB2679
	.uleb128 LEHE22-LEHB22
	.uleb128 0
	.uleb128 0
LLSDACSE2679:
	.text
	.def	__ZNSt8functionIFvvEEC1IZ4mainEUlvE3_vvEET_;	.scl	3;	.type	32;	.endef
	.set	__ZNSt8functionIFvvEEC1IZ4mainEUlvE3_vvEET_,__ZNSt8functionIFvvEEC2IZ4mainEUlvE3_vvEET_
	.section	.text$_ZNSaISt10_List_nodeIdEED2Ev,"x"
	.linkonce discard
	.align 2
	.globl	__ZNSaISt10_List_nodeIdEED2Ev
	.def	__ZNSaISt10_List_nodeIdEED2Ev;	.scl	2;	.type	32;	.endef
__ZNSaISt10_List_nodeIdEED2Ev:
LFB2770:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN9__gnu_cxx13new_allocatorISt10_List_nodeIdEED2Ev
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2770:
	.section	.text$_ZNSt7__cxx1110_List_baseIdSaIdEE8_M_clearEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZNSt7__cxx1110_List_baseIdSaIdEE8_M_clearEv
	.def	__ZNSt7__cxx1110_List_baseIdSaIdEE8_M_clearEv;	.scl	2;	.type	32;	.endef
__ZNSt7__cxx1110_List_baseIdSaIdEE8_M_clearEv:
LFB2772:
	.cfi_startproc
	.cfi_personality 0,___gxx_personality_v0
	.cfi_lsda 0,LLSDA2772
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$56, %esp
	movl	%ecx, -28(%ebp)
	movl	-28(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -12(%ebp)
L92:
	movl	-28(%ebp), %eax
	cmpl	-12(%ebp), %eax
	je	L93
	movl	-12(%ebp), %eax
	movl	%eax, -16(%ebp)
	movl	-16(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -12(%ebp)
	movl	-16(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNSt10_List_nodeIdE9_M_valptrEv
	movl	%eax, -20(%ebp)
	movl	-28(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNSt7__cxx1110_List_baseIdSaIdEE21_M_get_Node_allocatorEv
	movl	%eax, %edx
	movl	-20(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	__ZNSt16allocator_traitsISaISt10_List_nodeIdEEE7destroyIdEEvRS2_PT_
	movl	-28(%ebp), %eax
	movl	-16(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZNSt7__cxx1110_List_baseIdSaIdEE11_M_put_nodeEPSt10_List_nodeIdE
	subl	$4, %esp
	jmp	L92
L93:
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2772:
	.section	.gcc_except_table,"w"
LLSDA2772:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 LLSDACSE2772-LLSDACSB2772
LLSDACSB2772:
LLSDACSE2772:
	.section	.text$_ZNSt7__cxx1110_List_baseIdSaIdEE8_M_clearEv,"x"
	.linkonce discard
	.text
	.def	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE_E21_M_not_empty_functionIS1_EEbRKT_;	.scl	3;	.type	32;	.endef
__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE_E21_M_not_empty_functionIS1_EEbRKT_:
LFB2785:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	$1, %eax
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2785:
	.def	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE_E15_M_init_functorERSt9_Any_dataOS1_;	.scl	3;	.type	32;	.endef
__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE_E15_M_init_functorERSt9_Any_dataOS1_:
LFB2786:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$36, %esp
	.cfi_offset 3, -12
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZSt4moveIRZ4mainEUlvE_EONSt16remove_referenceIT_E4typeEOS3_
	movb	%bl, 8(%esp)
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE_E15_M_init_functorERSt9_Any_dataOS1_St17integral_constantIbLb1EE
	nop
	addl	$36, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2786:
	.def	__ZNSt17_Function_handlerIFvvEZ4mainEUlvE_E9_M_invokeERKSt9_Any_data;	.scl	3;	.type	32;	.endef
__ZNSt17_Function_handlerIFvvEZ4mainEUlvE_E9_M_invokeERKSt9_Any_data:
LFB2787:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE_E14_M_get_pointerERKSt9_Any_data
	movl	%eax, %ecx
	call	__ZZ4mainENKUlvE_clEv
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2787:
	.def	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE_E10_M_managerERSt9_Any_dataRKS3_St18_Manager_operation;	.scl	3;	.type	32;	.endef
__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE_E10_M_managerERSt9_Any_dataRKS3_St18_Manager_operation:
LFB2788:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$36, %esp
	.cfi_offset 3, -12
	movl	16(%ebp), %eax
	cmpl	$1, %eax
	je	L100
	cmpl	$1, %eax
	jg	L101
	testl	%eax, %eax
	je	L102
	jmp	L99
L101:
	cmpl	$2, %eax
	je	L103
	cmpl	$3, %eax
	je	L104
	jmp	L99
L102:
	movl	8(%ebp), %ecx
	call	__ZNSt9_Any_data9_M_accessIPKSt9type_infoEERT_v
	movl	$__ZTIZ4mainEUlvE_, (%eax)
	jmp	L99
L100:
	movl	8(%ebp), %ecx
	call	__ZNSt9_Any_data9_M_accessIPZ4mainEUlvE_EERT_v
	movl	%eax, %ebx
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE_E14_M_get_pointerERKSt9_Any_data
	movl	%eax, (%ebx)
	jmp	L99
L103:
	movb	%cl, 8(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE_E8_M_cloneERSt9_Any_dataRKS3_St17integral_constantIbLb1EE
	jmp	L99
L104:
	movb	%dl, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE_E10_M_destroyERSt9_Any_dataSt17integral_constantIbLb1EE
	nop
L99:
	movl	$0, %eax
	addl	$36, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2788:
	.def	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE0_E21_M_not_empty_functionIS1_EEbRKT_;	.scl	3;	.type	32;	.endef
__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE0_E21_M_not_empty_functionIS1_EEbRKT_:
LFB2790:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	$1, %eax
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2790:
	.def	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE0_E15_M_init_functorERSt9_Any_dataOS1_;	.scl	3;	.type	32;	.endef
__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE0_E15_M_init_functorERSt9_Any_dataOS1_:
LFB2791:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$36, %esp
	.cfi_offset 3, -12
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZSt4moveIRZ4mainEUlvE0_EONSt16remove_referenceIT_E4typeEOS3_
	movb	%bl, 8(%esp)
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE0_E15_M_init_functorERSt9_Any_dataOS1_St17integral_constantIbLb1EE
	nop
	addl	$36, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2791:
	.def	__ZNSt17_Function_handlerIFvvEZ4mainEUlvE0_E9_M_invokeERKSt9_Any_data;	.scl	3;	.type	32;	.endef
__ZNSt17_Function_handlerIFvvEZ4mainEUlvE0_E9_M_invokeERKSt9_Any_data:
LFB2792:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE0_E14_M_get_pointerERKSt9_Any_data
	movl	%eax, %ecx
	call	__ZZ4mainENKUlvE0_clEv
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2792:
	.def	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE0_E10_M_managerERSt9_Any_dataRKS3_St18_Manager_operation;	.scl	3;	.type	32;	.endef
__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE0_E10_M_managerERSt9_Any_dataRKS3_St18_Manager_operation:
LFB2793:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$36, %esp
	.cfi_offset 3, -12
	movl	16(%ebp), %eax
	cmpl	$1, %eax
	je	L112
	cmpl	$1, %eax
	jg	L113
	testl	%eax, %eax
	je	L114
	jmp	L111
L113:
	cmpl	$2, %eax
	je	L115
	cmpl	$3, %eax
	je	L116
	jmp	L111
L114:
	movl	8(%ebp), %ecx
	call	__ZNSt9_Any_data9_M_accessIPKSt9type_infoEERT_v
	movl	$__ZTIZ4mainEUlvE0_, (%eax)
	jmp	L111
L112:
	movl	8(%ebp), %ecx
	call	__ZNSt9_Any_data9_M_accessIPZ4mainEUlvE0_EERT_v
	movl	%eax, %ebx
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE0_E14_M_get_pointerERKSt9_Any_data
	movl	%eax, (%ebx)
	jmp	L111
L115:
	movb	%cl, 8(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE0_E8_M_cloneERSt9_Any_dataRKS3_St17integral_constantIbLb1EE
	jmp	L111
L116:
	movb	%dl, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE0_E10_M_destroyERSt9_Any_dataSt17integral_constantIbLb1EE
	nop
L111:
	movl	$0, %eax
	addl	$36, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2793:
	.def	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE1_E21_M_not_empty_functionIS1_EEbRKT_;	.scl	3;	.type	32;	.endef
__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE1_E21_M_not_empty_functionIS1_EEbRKT_:
LFB2794:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	$1, %eax
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2794:
	.def	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE1_E15_M_init_functorERSt9_Any_dataOS1_;	.scl	3;	.type	32;	.endef
__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE1_E15_M_init_functorERSt9_Any_dataOS1_:
LFB2795:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$36, %esp
	.cfi_offset 3, -12
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZSt4moveIRZ4mainEUlvE1_EONSt16remove_referenceIT_E4typeEOS3_
	movb	%bl, 8(%esp)
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE1_E15_M_init_functorERSt9_Any_dataOS1_St17integral_constantIbLb1EE
	nop
	addl	$36, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2795:
	.def	__ZNSt17_Function_handlerIFvvEZ4mainEUlvE1_E9_M_invokeERKSt9_Any_data;	.scl	3;	.type	32;	.endef
__ZNSt17_Function_handlerIFvvEZ4mainEUlvE1_E9_M_invokeERKSt9_Any_data:
LFB2796:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE1_E14_M_get_pointerERKSt9_Any_data
	movl	%eax, %ecx
	call	__ZZ4mainENKUlvE1_clEv
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2796:
	.def	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE1_E10_M_managerERSt9_Any_dataRKS3_St18_Manager_operation;	.scl	3;	.type	32;	.endef
__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE1_E10_M_managerERSt9_Any_dataRKS3_St18_Manager_operation:
LFB2797:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$36, %esp
	.cfi_offset 3, -12
	movl	16(%ebp), %eax
	cmpl	$1, %eax
	je	L124
	cmpl	$1, %eax
	jg	L125
	testl	%eax, %eax
	je	L126
	jmp	L123
L125:
	cmpl	$2, %eax
	je	L127
	cmpl	$3, %eax
	je	L128
	jmp	L123
L126:
	movl	8(%ebp), %ecx
	call	__ZNSt9_Any_data9_M_accessIPKSt9type_infoEERT_v
	movl	$__ZTIZ4mainEUlvE1_, (%eax)
	jmp	L123
L124:
	movl	8(%ebp), %ecx
	call	__ZNSt9_Any_data9_M_accessIPZ4mainEUlvE1_EERT_v
	movl	%eax, %ebx
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE1_E14_M_get_pointerERKSt9_Any_data
	movl	%eax, (%ebx)
	jmp	L123
L127:
	movb	%cl, 8(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE1_E8_M_cloneERSt9_Any_dataRKS3_St17integral_constantIbLb1EE
	jmp	L123
L128:
	movb	%dl, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE1_E10_M_destroyERSt9_Any_dataSt17integral_constantIbLb1EE
	nop
L123:
	movl	$0, %eax
	addl	$36, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2797:
	.def	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE2_E21_M_not_empty_functionIS1_EEbRKT_;	.scl	3;	.type	32;	.endef
__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE2_E21_M_not_empty_functionIS1_EEbRKT_:
LFB2798:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	$1, %eax
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2798:
	.def	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE2_E15_M_init_functorERSt9_Any_dataOS1_;	.scl	3;	.type	32;	.endef
__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE2_E15_M_init_functorERSt9_Any_dataOS1_:
LFB2799:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$36, %esp
	.cfi_offset 3, -12
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZSt4moveIRZ4mainEUlvE2_EONSt16remove_referenceIT_E4typeEOS3_
	movb	%bl, 8(%esp)
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE2_E15_M_init_functorERSt9_Any_dataOS1_St17integral_constantIbLb1EE
	nop
	addl	$36, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2799:
	.def	__ZNSt17_Function_handlerIFvvEZ4mainEUlvE2_E9_M_invokeERKSt9_Any_data;	.scl	3;	.type	32;	.endef
__ZNSt17_Function_handlerIFvvEZ4mainEUlvE2_E9_M_invokeERKSt9_Any_data:
LFB2800:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE2_E14_M_get_pointerERKSt9_Any_data
	movl	%eax, %ecx
	call	__ZZ4mainENKUlvE2_clEv
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2800:
	.def	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE2_E10_M_managerERSt9_Any_dataRKS3_St18_Manager_operation;	.scl	3;	.type	32;	.endef
__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE2_E10_M_managerERSt9_Any_dataRKS3_St18_Manager_operation:
LFB2801:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$36, %esp
	.cfi_offset 3, -12
	movl	16(%ebp), %eax
	cmpl	$1, %eax
	je	L136
	cmpl	$1, %eax
	jg	L137
	testl	%eax, %eax
	je	L138
	jmp	L135
L137:
	cmpl	$2, %eax
	je	L139
	cmpl	$3, %eax
	je	L140
	jmp	L135
L138:
	movl	8(%ebp), %ecx
	call	__ZNSt9_Any_data9_M_accessIPKSt9type_infoEERT_v
	movl	$__ZTIZ4mainEUlvE2_, (%eax)
	jmp	L135
L136:
	movl	8(%ebp), %ecx
	call	__ZNSt9_Any_data9_M_accessIPZ4mainEUlvE2_EERT_v
	movl	%eax, %ebx
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE2_E14_M_get_pointerERKSt9_Any_data
	movl	%eax, (%ebx)
	jmp	L135
L139:
	movb	%cl, 8(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE2_E8_M_cloneERSt9_Any_dataRKS3_St17integral_constantIbLb1EE
	jmp	L135
L140:
	movb	%dl, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE2_E10_M_destroyERSt9_Any_dataSt17integral_constantIbLb1EE
	nop
L135:
	movl	$0, %eax
	addl	$36, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2801:
	.def	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE3_E21_M_not_empty_functionIS1_EEbRKT_;	.scl	3;	.type	32;	.endef
__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE3_E21_M_not_empty_functionIS1_EEbRKT_:
LFB2802:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	$1, %eax
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2802:
	.def	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE3_E15_M_init_functorERSt9_Any_dataOS1_;	.scl	3;	.type	32;	.endef
__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE3_E15_M_init_functorERSt9_Any_dataOS1_:
LFB2803:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$36, %esp
	.cfi_offset 3, -12
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZSt4moveIRZ4mainEUlvE3_EONSt16remove_referenceIT_E4typeEOS3_
	movb	%bl, 8(%esp)
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE3_E15_M_init_functorERSt9_Any_dataOS1_St17integral_constantIbLb1EE
	nop
	addl	$36, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2803:
	.def	__ZNSt17_Function_handlerIFvvEZ4mainEUlvE3_E9_M_invokeERKSt9_Any_data;	.scl	3;	.type	32;	.endef
__ZNSt17_Function_handlerIFvvEZ4mainEUlvE3_E9_M_invokeERKSt9_Any_data:
LFB2804:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE3_E14_M_get_pointerERKSt9_Any_data
	movl	%eax, %ecx
	call	__ZZ4mainENKUlvE3_clEv
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2804:
	.def	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE3_E10_M_managerERSt9_Any_dataRKS3_St18_Manager_operation;	.scl	3;	.type	32;	.endef
__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE3_E10_M_managerERSt9_Any_dataRKS3_St18_Manager_operation:
LFB2805:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$36, %esp
	.cfi_offset 3, -12
	movl	16(%ebp), %eax
	cmpl	$1, %eax
	je	L148
	cmpl	$1, %eax
	jg	L149
	testl	%eax, %eax
	je	L150
	jmp	L147
L149:
	cmpl	$2, %eax
	je	L151
	cmpl	$3, %eax
	je	L152
	jmp	L147
L150:
	movl	8(%ebp), %ecx
	call	__ZNSt9_Any_data9_M_accessIPKSt9type_infoEERT_v
	movl	$__ZTIZ4mainEUlvE3_, (%eax)
	jmp	L147
L148:
	movl	8(%ebp), %ecx
	call	__ZNSt9_Any_data9_M_accessIPZ4mainEUlvE3_EERT_v
	movl	%eax, %ebx
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE3_E14_M_get_pointerERKSt9_Any_data
	movl	%eax, (%ebx)
	jmp	L147
L151:
	movb	%cl, 8(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE3_E8_M_cloneERSt9_Any_dataRKS3_St17integral_constantIbLb1EE
	jmp	L147
L152:
	movb	%dl, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE3_E10_M_destroyERSt9_Any_dataSt17integral_constantIbLb1EE
	nop
L147:
	movl	$0, %eax
	addl	$36, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2805:
	.section	.text$_ZN9__gnu_cxx13new_allocatorISt10_List_nodeIdEED2Ev,"x"
	.linkonce discard
	.align 2
	.globl	__ZN9__gnu_cxx13new_allocatorISt10_List_nodeIdEED2Ev
	.def	__ZN9__gnu_cxx13new_allocatorISt10_List_nodeIdEED2Ev;	.scl	2;	.type	32;	.endef
__ZN9__gnu_cxx13new_allocatorISt10_List_nodeIdEED2Ev:
LFB2840:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2840:
	.section	.text$_ZNSt10_List_nodeIdE9_M_valptrEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZNSt10_List_nodeIdE9_M_valptrEv
	.def	__ZNSt10_List_nodeIdE9_M_valptrEv;	.scl	2;	.type	32;	.endef
__ZNSt10_List_nodeIdE9_M_valptrEv:
LFB2842:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	addl	$8, %eax
	movl	%eax, %ecx
	call	__ZN9__gnu_cxx16__aligned_membufIdE6_M_ptrEv
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2842:
	.section	.text$_ZNSt7__cxx1110_List_baseIdSaIdEE21_M_get_Node_allocatorEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZNSt7__cxx1110_List_baseIdSaIdEE21_M_get_Node_allocatorEv
	.def	__ZNSt7__cxx1110_List_baseIdSaIdEE21_M_get_Node_allocatorEv;	.scl	2;	.type	32;	.endef
__ZNSt7__cxx1110_List_baseIdSaIdEE21_M_get_Node_allocatorEv:
LFB2843:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2843:
	.section	.text$_ZNSt16allocator_traitsISaISt10_List_nodeIdEEE7destroyIdEEvRS2_PT_,"x"
	.linkonce discard
	.globl	__ZNSt16allocator_traitsISaISt10_List_nodeIdEEE7destroyIdEEvRS2_PT_
	.def	__ZNSt16allocator_traitsISaISt10_List_nodeIdEEE7destroyIdEEvRS2_PT_;	.scl	2;	.type	32;	.endef
__ZNSt16allocator_traitsISaISt10_List_nodeIdEEE7destroyIdEEvRS2_PT_:
LFB2844:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	movl	8(%ebp), %ecx
	call	__ZN9__gnu_cxx13new_allocatorISt10_List_nodeIdEE7destroyIdEEvPT_
	subl	$4, %esp
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2844:
	.section	.text$_ZNSt7__cxx1110_List_baseIdSaIdEE11_M_put_nodeEPSt10_List_nodeIdE,"x"
	.linkonce discard
	.align 2
	.globl	__ZNSt7__cxx1110_List_baseIdSaIdEE11_M_put_nodeEPSt10_List_nodeIdE
	.def	__ZNSt7__cxx1110_List_baseIdSaIdEE11_M_put_nodeEPSt10_List_nodeIdE;	.scl	2;	.type	32;	.endef
__ZNSt7__cxx1110_List_baseIdSaIdEE11_M_put_nodeEPSt10_List_nodeIdE:
LFB2845:
	.cfi_startproc
	.cfi_personality 0,___gxx_personality_v0
	.cfi_lsda 0,LLSDA2845
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	$1, 8(%esp)
	movl	8(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	__ZNSt16allocator_traitsISaISt10_List_nodeIdEEE10deallocateERS2_PS1_j
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	$4
	.cfi_endproc
LFE2845:
	.section	.gcc_except_table,"w"
LLSDA2845:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 LLSDACSE2845-LLSDACSB2845
LLSDACSB2845:
LLSDACSE2845:
	.section	.text$_ZNSt7__cxx1110_List_baseIdSaIdEE11_M_put_nodeEPSt10_List_nodeIdE,"x"
	.linkonce discard
	.text
	.def	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE_E15_M_init_functorERSt9_Any_dataOS1_St17integral_constantIbLb1EE;	.scl	3;	.type	32;	.endef
__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE_E15_M_init_functorERSt9_Any_dataOS1_St17integral_constantIbLb1EE:
LFB2850:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZSt4moveIRZ4mainEUlvE_EONSt16remove_referenceIT_E4typeEOS3_
	movl	8(%ebp), %ecx
	call	__ZNSt9_Any_data9_M_accessEv
	movl	%eax, 4(%esp)
	movl	$1, (%esp)
	call	__ZnwjPv
	testl	%eax, %eax
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2850:
	.def	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE_E14_M_get_pointerERKSt9_Any_data;	.scl	3;	.type	32;	.endef
__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE_E14_M_get_pointerERKSt9_Any_data:
LFB2851:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movl	8(%ebp), %ecx
	call	__ZNKSt9_Any_data9_M_accessIZ4mainEUlvE_EERKT_v
	movl	%eax, (%esp)
	call	__ZSt11__addressofIKZ4mainEUlvE_EPT_RS2_
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2851:
	.section	.text$_ZNSt9_Any_data9_M_accessIPKSt9type_infoEERT_v,"x"
	.linkonce discard
	.align 2
	.globl	__ZNSt9_Any_data9_M_accessIPKSt9type_infoEERT_v
	.def	__ZNSt9_Any_data9_M_accessIPKSt9type_infoEERT_v;	.scl	2;	.type	32;	.endef
__ZNSt9_Any_data9_M_accessIPKSt9type_infoEERT_v:
LFB2852:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNSt9_Any_data9_M_accessEv
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2852:
	.text
	.align 2
	.def	__ZNSt9_Any_data9_M_accessIPZ4mainEUlvE_EERT_v;	.scl	3;	.type	32;	.endef
__ZNSt9_Any_data9_M_accessIPZ4mainEUlvE_EERT_v:
LFB2853:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNSt9_Any_data9_M_accessEv
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2853:
	.def	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE_E8_M_cloneERSt9_Any_dataRKS3_St17integral_constantIbLb1EE;	.scl	3;	.type	32;	.endef
__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE_E8_M_cloneERSt9_Any_dataRKS3_St17integral_constantIbLb1EE:
LFB2854:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNKSt9_Any_data9_M_accessIZ4mainEUlvE_EERKT_v
	movl	8(%ebp), %ecx
	call	__ZNSt9_Any_data9_M_accessEv
	movl	%eax, 4(%esp)
	movl	$1, (%esp)
	call	__ZnwjPv
	testl	%eax, %eax
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2854:
	.def	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE_E10_M_destroyERSt9_Any_dataSt17integral_constantIbLb1EE;	.scl	3;	.type	32;	.endef
__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE_E10_M_destroyERSt9_Any_dataSt17integral_constantIbLb1EE:
LFB2855:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	movl	8(%ebp), %ecx
	call	__ZNSt9_Any_data9_M_accessIZ4mainEUlvE_EERT_v
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2855:
	.def	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE0_E15_M_init_functorERSt9_Any_dataOS1_St17integral_constantIbLb1EE;	.scl	3;	.type	32;	.endef
__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE0_E15_M_init_functorERSt9_Any_dataOS1_St17integral_constantIbLb1EE:
LFB2862:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZSt4moveIRZ4mainEUlvE0_EONSt16remove_referenceIT_E4typeEOS3_
	movl	8(%ebp), %ecx
	call	__ZNSt9_Any_data9_M_accessEv
	movl	%eax, 4(%esp)
	movl	$1, (%esp)
	call	__ZnwjPv
	testl	%eax, %eax
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2862:
	.def	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE0_E14_M_get_pointerERKSt9_Any_data;	.scl	3;	.type	32;	.endef
__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE0_E14_M_get_pointerERKSt9_Any_data:
LFB2863:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movl	8(%ebp), %ecx
	call	__ZNKSt9_Any_data9_M_accessIZ4mainEUlvE0_EERKT_v
	movl	%eax, (%esp)
	call	__ZSt11__addressofIKZ4mainEUlvE0_EPT_RS2_
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2863:
	.align 2
	.def	__ZNSt9_Any_data9_M_accessIPZ4mainEUlvE0_EERT_v;	.scl	3;	.type	32;	.endef
__ZNSt9_Any_data9_M_accessIPZ4mainEUlvE0_EERT_v:
LFB2864:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNSt9_Any_data9_M_accessEv
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2864:
	.def	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE0_E8_M_cloneERSt9_Any_dataRKS3_St17integral_constantIbLb1EE;	.scl	3;	.type	32;	.endef
__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE0_E8_M_cloneERSt9_Any_dataRKS3_St17integral_constantIbLb1EE:
LFB2865:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNKSt9_Any_data9_M_accessIZ4mainEUlvE0_EERKT_v
	movl	8(%ebp), %ecx
	call	__ZNSt9_Any_data9_M_accessEv
	movl	%eax, 4(%esp)
	movl	$1, (%esp)
	call	__ZnwjPv
	testl	%eax, %eax
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2865:
	.def	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE0_E10_M_destroyERSt9_Any_dataSt17integral_constantIbLb1EE;	.scl	3;	.type	32;	.endef
__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE0_E10_M_destroyERSt9_Any_dataSt17integral_constantIbLb1EE:
LFB2866:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	movl	8(%ebp), %ecx
	call	__ZNSt9_Any_data9_M_accessIZ4mainEUlvE0_EERT_v
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2866:
	.def	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE1_E15_M_init_functorERSt9_Any_dataOS1_St17integral_constantIbLb1EE;	.scl	3;	.type	32;	.endef
__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE1_E15_M_init_functorERSt9_Any_dataOS1_St17integral_constantIbLb1EE:
LFB2867:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$20, %esp
	.cfi_offset 3, -12
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZSt4moveIRZ4mainEUlvE1_EONSt16remove_referenceIT_E4typeEOS3_
	movl	%eax, %ebx
	movl	8(%ebp), %ecx
	call	__ZNSt9_Any_data9_M_accessEv
	movl	%eax, 4(%esp)
	movl	$4, (%esp)
	call	__ZnwjPv
	testl	%eax, %eax
	je	L188
	movl	(%ebx), %edx
	movl	%edx, (%eax)
L188:
	nop
	addl	$20, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2867:
	.def	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE1_E14_M_get_pointerERKSt9_Any_data;	.scl	3;	.type	32;	.endef
__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE1_E14_M_get_pointerERKSt9_Any_data:
LFB2868:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movl	8(%ebp), %ecx
	call	__ZNKSt9_Any_data9_M_accessIZ4mainEUlvE1_EERKT_v
	movl	%eax, (%esp)
	call	__ZSt11__addressofIKZ4mainEUlvE1_EPT_RS2_
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2868:
	.align 2
	.def	__ZNSt9_Any_data9_M_accessIPZ4mainEUlvE1_EERT_v;	.scl	3;	.type	32;	.endef
__ZNSt9_Any_data9_M_accessIPZ4mainEUlvE1_EERT_v:
LFB2869:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNSt9_Any_data9_M_accessEv
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2869:
	.def	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE1_E8_M_cloneERSt9_Any_dataRKS3_St17integral_constantIbLb1EE;	.scl	3;	.type	32;	.endef
__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE1_E8_M_cloneERSt9_Any_dataRKS3_St17integral_constantIbLb1EE:
LFB2870:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$20, %esp
	.cfi_offset 3, -12
	movl	12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNKSt9_Any_data9_M_accessIZ4mainEUlvE1_EERKT_v
	movl	%eax, %ebx
	movl	8(%ebp), %ecx
	call	__ZNSt9_Any_data9_M_accessEv
	movl	%eax, 4(%esp)
	movl	$4, (%esp)
	call	__ZnwjPv
	testl	%eax, %eax
	je	L196
	movl	(%ebx), %edx
	movl	%edx, (%eax)
L196:
	nop
	addl	$20, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2870:
	.def	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE1_E10_M_destroyERSt9_Any_dataSt17integral_constantIbLb1EE;	.scl	3;	.type	32;	.endef
__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE1_E10_M_destroyERSt9_Any_dataSt17integral_constantIbLb1EE:
LFB2871:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	movl	8(%ebp), %ecx
	call	__ZNSt9_Any_data9_M_accessIZ4mainEUlvE1_EERT_v
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2871:
	.def	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE2_E15_M_init_functorERSt9_Any_dataOS1_St17integral_constantIbLb1EE;	.scl	3;	.type	32;	.endef
__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE2_E15_M_init_functorERSt9_Any_dataOS1_St17integral_constantIbLb1EE:
LFB2872:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZSt4moveIRZ4mainEUlvE2_EONSt16remove_referenceIT_E4typeEOS3_
	movl	8(%ebp), %ecx
	call	__ZNSt9_Any_data9_M_accessEv
	movl	%eax, 4(%esp)
	movl	$1, (%esp)
	call	__ZnwjPv
	testl	%eax, %eax
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2872:
	.def	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE2_E14_M_get_pointerERKSt9_Any_data;	.scl	3;	.type	32;	.endef
__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE2_E14_M_get_pointerERKSt9_Any_data:
LFB2873:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movl	8(%ebp), %ecx
	call	__ZNKSt9_Any_data9_M_accessIZ4mainEUlvE2_EERKT_v
	movl	%eax, (%esp)
	call	__ZSt11__addressofIKZ4mainEUlvE2_EPT_RS2_
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2873:
	.align 2
	.def	__ZNSt9_Any_data9_M_accessIPZ4mainEUlvE2_EERT_v;	.scl	3;	.type	32;	.endef
__ZNSt9_Any_data9_M_accessIPZ4mainEUlvE2_EERT_v:
LFB2874:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNSt9_Any_data9_M_accessEv
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2874:
	.def	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE2_E8_M_cloneERSt9_Any_dataRKS3_St17integral_constantIbLb1EE;	.scl	3;	.type	32;	.endef
__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE2_E8_M_cloneERSt9_Any_dataRKS3_St17integral_constantIbLb1EE:
LFB2875:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNKSt9_Any_data9_M_accessIZ4mainEUlvE2_EERKT_v
	movl	8(%ebp), %ecx
	call	__ZNSt9_Any_data9_M_accessEv
	movl	%eax, 4(%esp)
	movl	$1, (%esp)
	call	__ZnwjPv
	testl	%eax, %eax
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2875:
	.def	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE2_E10_M_destroyERSt9_Any_dataSt17integral_constantIbLb1EE;	.scl	3;	.type	32;	.endef
__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE2_E10_M_destroyERSt9_Any_dataSt17integral_constantIbLb1EE:
LFB2876:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	movl	8(%ebp), %ecx
	call	__ZNSt9_Any_data9_M_accessIZ4mainEUlvE2_EERT_v
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2876:
	.def	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE3_E15_M_init_functorERSt9_Any_dataOS1_St17integral_constantIbLb1EE;	.scl	3;	.type	32;	.endef
__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE3_E15_M_init_functorERSt9_Any_dataOS1_St17integral_constantIbLb1EE:
LFB2877:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$20, %esp
	.cfi_offset 3, -12
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZSt4moveIRZ4mainEUlvE3_EONSt16remove_referenceIT_E4typeEOS3_
	movl	%eax, %ebx
	movl	8(%ebp), %ecx
	call	__ZNSt9_Any_data9_M_accessEv
	movl	%eax, 4(%esp)
	movl	$4, (%esp)
	call	__ZnwjPv
	testl	%eax, %eax
	je	L212
	movl	(%ebx), %edx
	movl	%edx, (%eax)
L212:
	nop
	addl	$20, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2877:
	.def	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE3_E14_M_get_pointerERKSt9_Any_data;	.scl	3;	.type	32;	.endef
__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE3_E14_M_get_pointerERKSt9_Any_data:
LFB2878:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movl	8(%ebp), %ecx
	call	__ZNKSt9_Any_data9_M_accessIZ4mainEUlvE3_EERKT_v
	movl	%eax, (%esp)
	call	__ZSt11__addressofIKZ4mainEUlvE3_EPT_RS2_
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2878:
	.align 2
	.def	__ZNSt9_Any_data9_M_accessIPZ4mainEUlvE3_EERT_v;	.scl	3;	.type	32;	.endef
__ZNSt9_Any_data9_M_accessIPZ4mainEUlvE3_EERT_v:
LFB2879:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNSt9_Any_data9_M_accessEv
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2879:
	.def	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE3_E8_M_cloneERSt9_Any_dataRKS3_St17integral_constantIbLb1EE;	.scl	3;	.type	32;	.endef
__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE3_E8_M_cloneERSt9_Any_dataRKS3_St17integral_constantIbLb1EE:
LFB2880:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$20, %esp
	.cfi_offset 3, -12
	movl	12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNKSt9_Any_data9_M_accessIZ4mainEUlvE3_EERKT_v
	movl	%eax, %ebx
	movl	8(%ebp), %ecx
	call	__ZNSt9_Any_data9_M_accessEv
	movl	%eax, 4(%esp)
	movl	$4, (%esp)
	call	__ZnwjPv
	testl	%eax, %eax
	je	L220
	movl	(%ebx), %edx
	movl	%edx, (%eax)
L220:
	nop
	addl	$20, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2880:
	.def	__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE3_E10_M_destroyERSt9_Any_dataSt17integral_constantIbLb1EE;	.scl	3;	.type	32;	.endef
__ZNSt14_Function_base13_Base_managerIZ4mainEUlvE3_E10_M_destroyERSt9_Any_dataSt17integral_constantIbLb1EE:
LFB2881:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	movl	8(%ebp), %ecx
	call	__ZNSt9_Any_data9_M_accessIZ4mainEUlvE3_EERT_v
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2881:
	.section	.text$_ZN9__gnu_cxx16__aligned_membufIdE6_M_ptrEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZN9__gnu_cxx16__aligned_membufIdE6_M_ptrEv
	.def	__ZN9__gnu_cxx16__aligned_membufIdE6_M_ptrEv;	.scl	2;	.type	32;	.endef
__ZN9__gnu_cxx16__aligned_membufIdE6_M_ptrEv:
LFB2915:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN9__gnu_cxx16__aligned_membufIdE7_M_addrEv
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2915:
	.section	.text$_ZN9__gnu_cxx13new_allocatorISt10_List_nodeIdEE7destroyIdEEvPT_,"x"
	.linkonce discard
	.align 2
	.globl	__ZN9__gnu_cxx13new_allocatorISt10_List_nodeIdEE7destroyIdEEvPT_
	.def	__ZN9__gnu_cxx13new_allocatorISt10_List_nodeIdEE7destroyIdEEvPT_;	.scl	2;	.type	32;	.endef
__ZN9__gnu_cxx13new_allocatorISt10_List_nodeIdEE7destroyIdEEvPT_:
LFB2916:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	$4
	.cfi_endproc
LFE2916:
	.section	.text$_ZNSt16allocator_traitsISaISt10_List_nodeIdEEE10deallocateERS2_PS1_j,"x"
	.linkonce discard
	.globl	__ZNSt16allocator_traitsISaISt10_List_nodeIdEEE10deallocateERS2_PS1_j
	.def	__ZNSt16allocator_traitsISaISt10_List_nodeIdEEE10deallocateERS2_PS1_j;	.scl	2;	.type	32;	.endef
__ZNSt16allocator_traitsISaISt10_List_nodeIdEEE10deallocateERS2_PS1_j:
LFB2917:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	movl	8(%ebp), %ecx
	call	__ZN9__gnu_cxx13new_allocatorISt10_List_nodeIdEE10deallocateEPS2_j
	subl	$8, %esp
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2917:
	.text
	.align 2
	.def	__ZNKSt9_Any_data9_M_accessIZ4mainEUlvE_EERKT_v;	.scl	3;	.type	32;	.endef
__ZNKSt9_Any_data9_M_accessIZ4mainEUlvE_EERKT_v:
LFB2918:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNKSt9_Any_data9_M_accessEv
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2918:
	.def	__ZSt11__addressofIKZ4mainEUlvE_EPT_RS2_;	.scl	3;	.type	32;	.endef
__ZSt11__addressofIKZ4mainEUlvE_EPT_RS2_:
LFB2919:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	8(%ebp), %eax
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2919:
	.align 2
	.def	__ZNSt9_Any_data9_M_accessIZ4mainEUlvE_EERT_v;	.scl	3;	.type	32;	.endef
__ZNSt9_Any_data9_M_accessIZ4mainEUlvE_EERT_v:
LFB2921:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNSt9_Any_data9_M_accessEv
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2921:
	.align 2
	.def	__ZNKSt9_Any_data9_M_accessIZ4mainEUlvE0_EERKT_v;	.scl	3;	.type	32;	.endef
__ZNKSt9_Any_data9_M_accessIZ4mainEUlvE0_EERKT_v:
LFB2922:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNKSt9_Any_data9_M_accessEv
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2922:
	.def	__ZSt11__addressofIKZ4mainEUlvE0_EPT_RS2_;	.scl	3;	.type	32;	.endef
__ZSt11__addressofIKZ4mainEUlvE0_EPT_RS2_:
LFB2923:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	8(%ebp), %eax
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2923:
	.align 2
	.def	__ZNSt9_Any_data9_M_accessIZ4mainEUlvE0_EERT_v;	.scl	3;	.type	32;	.endef
__ZNSt9_Any_data9_M_accessIZ4mainEUlvE0_EERT_v:
LFB2925:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNSt9_Any_data9_M_accessEv
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2925:
	.align 2
	.def	__ZNKSt9_Any_data9_M_accessIZ4mainEUlvE1_EERKT_v;	.scl	3;	.type	32;	.endef
__ZNKSt9_Any_data9_M_accessIZ4mainEUlvE1_EERKT_v:
LFB2926:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNKSt9_Any_data9_M_accessEv
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2926:
	.def	__ZSt11__addressofIKZ4mainEUlvE1_EPT_RS2_;	.scl	3;	.type	32;	.endef
__ZSt11__addressofIKZ4mainEUlvE1_EPT_RS2_:
LFB2927:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	8(%ebp), %eax
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2927:
	.align 2
	.def	__ZNSt9_Any_data9_M_accessIZ4mainEUlvE1_EERT_v;	.scl	3;	.type	32;	.endef
__ZNSt9_Any_data9_M_accessIZ4mainEUlvE1_EERT_v:
LFB2929:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNSt9_Any_data9_M_accessEv
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2929:
	.align 2
	.def	__ZNKSt9_Any_data9_M_accessIZ4mainEUlvE2_EERKT_v;	.scl	3;	.type	32;	.endef
__ZNKSt9_Any_data9_M_accessIZ4mainEUlvE2_EERKT_v:
LFB2930:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNKSt9_Any_data9_M_accessEv
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2930:
	.def	__ZSt11__addressofIKZ4mainEUlvE2_EPT_RS2_;	.scl	3;	.type	32;	.endef
__ZSt11__addressofIKZ4mainEUlvE2_EPT_RS2_:
LFB2931:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	8(%ebp), %eax
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2931:
	.align 2
	.def	__ZNSt9_Any_data9_M_accessIZ4mainEUlvE2_EERT_v;	.scl	3;	.type	32;	.endef
__ZNSt9_Any_data9_M_accessIZ4mainEUlvE2_EERT_v:
LFB2933:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNSt9_Any_data9_M_accessEv
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2933:
	.align 2
	.def	__ZNKSt9_Any_data9_M_accessIZ4mainEUlvE3_EERKT_v;	.scl	3;	.type	32;	.endef
__ZNKSt9_Any_data9_M_accessIZ4mainEUlvE3_EERKT_v:
LFB2934:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNKSt9_Any_data9_M_accessEv
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2934:
	.def	__ZSt11__addressofIKZ4mainEUlvE3_EPT_RS2_;	.scl	3;	.type	32;	.endef
__ZSt11__addressofIKZ4mainEUlvE3_EPT_RS2_:
LFB2935:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	8(%ebp), %eax
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2935:
	.align 2
	.def	__ZNSt9_Any_data9_M_accessIZ4mainEUlvE3_EERT_v;	.scl	3;	.type	32;	.endef
__ZNSt9_Any_data9_M_accessIZ4mainEUlvE3_EERT_v:
LFB2937:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZNSt9_Any_data9_M_accessEv
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2937:
	.section	.text$_ZN9__gnu_cxx16__aligned_membufIdE7_M_addrEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZN9__gnu_cxx16__aligned_membufIdE7_M_addrEv
	.def	__ZN9__gnu_cxx16__aligned_membufIdE7_M_addrEv;	.scl	2;	.type	32;	.endef
__ZN9__gnu_cxx16__aligned_membufIdE7_M_addrEv:
LFB2966:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2966:
	.section	.text$_ZN9__gnu_cxx13new_allocatorISt10_List_nodeIdEE10deallocateEPS2_j,"x"
	.linkonce discard
	.align 2
	.globl	__ZN9__gnu_cxx13new_allocatorISt10_List_nodeIdEE10deallocateEPS2_j
	.def	__ZN9__gnu_cxx13new_allocatorISt10_List_nodeIdEE10deallocateEPS2_j;	.scl	2;	.type	32;	.endef
__ZN9__gnu_cxx13new_allocatorISt10_List_nodeIdEE10deallocateEPS2_j:
LFB2967:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movl	%ecx, -12(%ebp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZdlPv
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	$8
	.cfi_endproc
LFE2967:
	.section .rdata,"dr"
	.align 4
__ZTSZ4mainEUlvE3_:
	.ascii "*Z4mainEUlvE3_\0"
	.align 4
__ZTIZ4mainEUlvE3_:
	.long	__ZTVN10__cxxabiv117__class_type_infoE+8
	.long	__ZTSZ4mainEUlvE3_
	.align 4
__ZTSZ4mainEUlvE2_:
	.ascii "*Z4mainEUlvE2_\0"
	.align 4
__ZTIZ4mainEUlvE2_:
	.long	__ZTVN10__cxxabiv117__class_type_infoE+8
	.long	__ZTSZ4mainEUlvE2_
	.align 4
__ZTSZ4mainEUlvE1_:
	.ascii "*Z4mainEUlvE1_\0"
	.align 4
__ZTIZ4mainEUlvE1_:
	.long	__ZTVN10__cxxabiv117__class_type_infoE+8
	.long	__ZTSZ4mainEUlvE1_
	.align 4
__ZTSZ4mainEUlvE0_:
	.ascii "*Z4mainEUlvE0_\0"
	.align 4
__ZTIZ4mainEUlvE0_:
	.long	__ZTVN10__cxxabiv117__class_type_infoE+8
	.long	__ZTSZ4mainEUlvE0_
	.align 4
__ZTSZ4mainEUlvE_:
	.ascii "*Z4mainEUlvE_\0"
	.align 4
__ZTIZ4mainEUlvE_:
	.long	__ZTVN10__cxxabiv117__class_type_infoE+8
	.long	__ZTSZ4mainEUlvE_
	.ident	"GCC: (MinGW.org GCC-6.3.0-1) 6.3.0"
	.def	__ZNSt14basic_ofstreamIcSt11char_traitsIcEED1Ev;	.scl	2;	.type	32;	.endef
	.def	_rand;	.scl	2;	.type	32;	.endef
	.def	__ZN12TestTemplateC1EPKc;	.scl	2;	.type	32;	.endef
	.def	__ZN12TestTemplate29WriteMessageIntoScreenAndFileEPKcb;	.scl	2;	.type	32;	.endef
	.def	__ZN12TestTemplate11ExecuteTestESt8functionIFvvEE;	.scl	2;	.type	32;	.endef
	.def	__ZN12TestTemplate20CalculateAverageTimeEv;	.scl	2;	.type	32;	.endef
	.def	__ZN12TestTemplate33WriteTestResultsIntoScreenAndFileEPKcS1_d;	.scl	2;	.type	32;	.endef
	.def	__Unwind_Resume;	.scl	2;	.type	32;	.endef
	.def	__ZdlPv;	.scl	2;	.type	32;	.endef

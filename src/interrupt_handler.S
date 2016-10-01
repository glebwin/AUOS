.code64
.global handlers

.macro HANDLER n
    handler\n:
        PUSH_REG
        movq $\n, %rdi
        cld
        call handle_interrupt
        POP_REG
        iretq
.endm

.macro HANDLER_ERR n
    handler\n:
        PUSH_REG
        movq $\n, %rdi
        movq 120(%rsp), %rsi
        cld
        call handle_interrupt
        POP_REG
        addq $8, %rsp
        iretq
.endm

.macro PUSH_REG
    pushq %rax
    pushq %rbx
    pushq %rcx
    pushq %rdx
    pushq %rsi
    pushq %rdi
    pushq %rbp
    pushq %r8
    pushq %r9
    pushq %r10
    pushq %r11
    pushq %r12
    pushq %r13
    pushq %r14
    pushq %r15
.endm

.macro POP_REG
    popq %r15
    popq %r14
    popq %r13
    popq %r12
    popq %r11
    popq %r10
    popq %r9
    popq %r8
    popq %rbp
    popq %rdi
    popq %rsi
    popq %rdx
    popq %rcx
    popq %rbx
    popq %rax
.endm


HANDLER 0
HANDLER 1
HANDLER 2
HANDLER 3
HANDLER 4
HANDLER 5
HANDLER 6
HANDLER 7
HANDLER_ERR 8
HANDLER 9
HANDLER_ERR 10
HANDLER_ERR 11
HANDLER_ERR 12
HANDLER_ERR 13
HANDLER_ERR 14
HANDLER 15
HANDLER 16
HANDLER_ERR 17
HANDLER 18
HANDLER 19
HANDLER 20
HANDLER 21
HANDLER 22
HANDLER 23
HANDLER 24
HANDLER 25
HANDLER 26
HANDLER 27
HANDLER 28
HANDLER 29
HANDLER 30
HANDLER 31
HANDLER 32
HANDLER 33
HANDLER 34
HANDLER 35
HANDLER 36
HANDLER 37
HANDLER 38
HANDLER 39
HANDLER 40
HANDLER 41
HANDLER 42
HANDLER 43
HANDLER 44
HANDLER 45
HANDLER 46
HANDLER 47
handlers:
    .quad handler0
    .quad handler1
    .quad handler2
    .quad handler3
    .quad handler4
    .quad handler5
    .quad handler6
    .quad handler7
    .quad handler8
    .quad handler9
    .quad handler10
    .quad handler11
    .quad handler12
    .quad handler13
    .quad handler14
    .quad handler15
    .quad handler16
    .quad handler17
    .quad handler18
    .quad handler19
    .quad handler20
    .quad handler21
    .quad handler22
    .quad handler23
    .quad handler24
    .quad handler25
    .quad handler26
    .quad handler27
    .quad handler28
    .quad handler29
    .quad handler30
    .quad handler31
    .quad handler32
    .quad handler33
    .quad handler34
    .quad handler35
    .quad handler36
    .quad handler37
    .quad handler38
    .quad handler39
    .quad handler40
    .quad handler41
    .quad handler42
    .quad handler43
    .quad handler44
    .quad handler45
    .quad handler46
    .quad handler47

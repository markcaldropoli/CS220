.intel_syntax noprefix

.text
.global get_rbp

get_rbp:
mov rax, rbp
ret

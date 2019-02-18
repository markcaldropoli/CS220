.intel_syntax noprefix

.text
.global toggle_bit

toggle_bit:
mov rax, rdi
mov rdx, 1
mov rcx, rsi
shl rdx, cl
xor rax, rdx
ret

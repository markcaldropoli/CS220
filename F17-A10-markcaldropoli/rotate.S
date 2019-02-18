.intel_syntax noprefix

.text
.global rotate

rotate:
push rbx
xor cx, cx
mov rax, rdi
cmp rdx, 0
je right
cmp rdx, 1
je left
jmp ret

right:
mov rbx, rax
shl rbx, 63
shr rax, 1
or rax, rbx
inc cx
cmp cx, si
jl right
jmp ret

left:
mov rbx, rax
shr rbx, 63
shl rax, 1
or rax, rbx
inc cx
cmp cx, si
jl left
jmp ret

ret:
pop rbx
ret

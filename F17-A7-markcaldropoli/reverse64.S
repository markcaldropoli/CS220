.intel_syntax noprefix		#indicates we are using Intel Syntax
.text				#lets assembler know code is in .text segment
.global reverse_asm_64		#declares a function accessible in the global context

reverse_asm_64:
push rbx			#rbx headptr, rcx nextptr, rdx new_head_ptr
mov rax, 0x0			#headptr = nextptr = new_headptr = NULL
mov rbx, rax
mov rcx, rax
mov rdx, rax
mov rax, rdi			#if(head == NULL) return NULL
cmp rax, 0
je null_ret
add rax, rsi			#rax contains headptr, this adds rsi to reach ptr field
mov rbx, rax

while_start:			#while(headptr)
cmp rbx, 0x0
je while_done
mov rcx, [rbx]			#nextptr = (void *)(*((unsigned long *)headptr))
mov [rbx], rdx			#*(unsigned long *)headptr = (unsigned long) new_headptr
mov rdx, rbx			#new_headptr = headptr
mov rbx, rcx			#headptr = nextptr
jmp while_start			#next iteration

while_done:			#continue here after while loop
mov rax, rdx			#set rax to the beginning of the new head Node
sub rax, rsi

null_ret:
pop rbx
ret

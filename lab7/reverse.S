.intel_syntax noprefix 		#indicates we are using Intel Syntax
.text 				#lets assembler know code is in .text segment
.global reverse_asm		#declares a function accessible in the global context

reverse_asm:
push ebx			#ebx  headptr, ecx nextptr, edx newhead_ptr
mov eax, 0x0			#headptr = nextptr = new_headptr = NULL
mov ebx, eax
mov ecx, eax
mov edx, eax
mov eax, [esp + 0x8]		#if(head == NULL) return NULL
cmp eax, 0
je null_ret
add eax, [esp + 0xC]		#eax contains headptr, this adds offset to reach ptr field
mov ebx, eax

while_start:			#while(headptr)
cmp ebx, 0x0
je while_done
mov ecx, [ebx]			#nextptr = (void *)(*((unsigned long *)headptr))
mov [ebx], edx			#*(unsigned long *)headptr = (unsigned long) new_headptr
mov edx, ebx			#new_headptr = headptr
mov ebx, ecx			#headptr = nextptr
jmp while_start			#next iteration

while_done:			#continue here after while loop
mov eax, edx			#set eax to the beginning of the new head Node
sub eax, [esp + 0xC]

null_ret:
pop ebx
ret

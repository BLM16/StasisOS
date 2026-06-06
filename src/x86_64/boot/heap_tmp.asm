bits 64

global liballoc_lock, liballoc_unlock, liballoc_alloc, liballoc_free

section .text

%macro pusha 0
    push rax
    push rcx
    push rdx
    push rbx
    push rsp
    push rbp
    push rsi
    push rdi
%endmacro
%macro popa 0
    pop rdi
    pop rsi
    pop rbp
    pop rsp
    pop rbx
    pop rdx
    pop rcx
    pop rax
%endmacro

; Look at linux impl for ideas:
; https://github.com/blanham/liballoc/blob/master/linux.c

; int liballoc_lock()
;   returns 0 if lock was acquired successfully
liballoc_lock:


; int liballoc_unlock()
;   returns 0 if lock was successfully released
liballoc_unlock:


; void* liballoc_alloc(rdi <- u64 pages)
;   returns a pointer to the allocated memory or 0 if allocation fails
liballoc_alloc:


; int liballoc_free(rdi <- void* ptr, rsi <- u64 pages)
;   returns 0 if memory was successfully freed
liballoc_free:

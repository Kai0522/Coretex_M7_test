.syntax unified

/*implement system call*/
.global syscall
syscall:
	nop
	svc 0
	nop
	bx lr

.PHONY:name_fifo name_fifo_clean name_pc name_pc_clean
CC:=gcc

system:system.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

fork:fork.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

fork_fd:fork_fd.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

execve:execve.c erlou
	-$(CC) -o $@ $<
	-./$@
	-rm ./$@ ./$(word 2,$^)

fork_execve:fork_execve.c erlou
	-$(CC) -o $@ $(firstword $^)
	-./$@
	-rm ./$@ ./$(lastword $^)

wait:wait.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@


perror:perror.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

errno:errno.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

noname_pipe:noname_pipe.c
	-$(CC) -o $@ $^
	-./$@ 'test'
	-rm ./$@

fifo_write:fifo_write.c
	$(CC) -o $@ $<

fifo_read:fifo_read.c
	$(CC) -o $@ $<

name_fifo:fifo_write fifo_read

name_fifo_clean:
	rm ./fifo_write ./fifo_read

share:share.c
	-$(CC) -o $@ $< -lrt #用共享内存要链接实时库
	-./$@ 
	-rm ./$@

share_memory:share_memory.c
	-$(CC) -o $@ $< -lrt #用共享内存要链接实时库
	-./$@ 
	-rm ./$@

fa_son_mq:fa_son_mq.c
	-$(CC) -o $@ $< -lrt #用消息队列要链接实时库
	-./$@ 
	-rm ./$@

producter:producter.c
	$(CC) -o $@ $< -lrt

consumer:consumer.c 
	$(CC) -o $@ $< -lrt

name_pc:producter consumer

name_pc_clean:
	-rm ./producter ./consumer

signal:signal.c
	-$(CC) -o $@ $^
	-./$@ 
	-rm ./$@

clean:
	-rm io.txt

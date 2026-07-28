CC:=gcc

num_convert:num_convert.c
	-$(CC) -o $@ $<
	-./$@
	-rm ./$@

inet_convert:inet_convert.c
	-$(CC) -o $@ $<
	-./$@
	-rm ./$@

server:server.c
	-$(CC) -o $@ $< -pthread

consumer:consumer.c
	-$(CC) -o $@ $< -pthread

# 调用tcp图形界面
# xhost +SI:localuser:root
# sudo wireshark

without_buf:without_buf.c
	-$(CC) -o $@ $<
	-./$@
	-rm ./$@

multi_thread_server:multi_thread_server.c
	-$(CC) -o $@ $< -pthread

multi_thread_consumer:multi_thread_consumer.c
	-$(CC) -o $@ $< -pthread


multi_process_server:multi_process_server.c
	-$(CC) -o $@ $< -pthread

multi_process_consumer:multi_process_consumer.c
	-$(CC) -o $@ $< -pthread

udp_server:udp_server.c
	-$(CC) -o $@ $< -pthread

udp_consumer:udp_consumer.c
	-$(CC) -o $@ $< -pthread
clean:
	-rm ./udp_server ./udp_consumer

ipc:ipc.c
	-$(CC) -o $@ $< -pthread
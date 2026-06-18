# 通用规则（匹配任意 .c 文件）
%: %.c
	gcc -o $@ $^ -pthread
	./$@
	rm $@

# 通用 .out 规则（也加 -pthread）
%.out: %.c
	gcc -o $@ $^ -pthread
	./$@
	rm $@

# 特定规则：file_copy.out 依赖 src.txt
file_copy.out: file_copy.c src.txt
	gcc -o $@ file_copy.c -pthread
	./$@
	rm $@

src.txt:
	echo "hello linux" > src.txt
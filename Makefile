# 通用规则：编译 .c 文件生成可执行文件
%.out: %.c
	gcc -o $@ $^
	./$@
	rm $@

# 特定规则：file_copy.out 依赖 src.txt，但 src.txt 不能作为编译输入
# 所以这里的依赖只用于确保 src.txt 存在，不参与 gcc 编译
file_copy.out: file_copy.c src.txt
	gcc -o $@ file_copy.c
	./$@
	rm $@

src.txt:
	echo "hello linux" > src.txt
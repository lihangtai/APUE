CC := gcc
CFLAGS := -Wall -Wextra -std=c99

# 获取目录名，可以通过 make 命令传递参数指定
DIR :=

# 通过 wildcard 函数获取指定目录下的所有 .c 文件
SRC := $(wildcard $(DIR)/*.c)

# 通过 patsubst 函数将 .c 文件替换成对应的可执行文件名
TARGETS := $(patsubst %.c, %, $(SRC))

# 默认目标，编译生成所有可执行文件
all: $(TARGETS)

# 模式规则，生成可执行文件
%: %.c
	$(CC) $(CFLAGS) -o $@ $<

# 清理目标，删除生成的所有可执行文件
.PHONY: clean
clean:
	rm -f $(TARGETS)


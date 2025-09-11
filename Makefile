CC = gcc
CFLAGS = -Wall -Wextra -fPIC -shared -Iinclude
SRC_DIR = src
LIB_DIR = lib

$(LIB_DIR)/my_mem_alloc.so: $(SRC_DIR)/my_mem_alloc.c
	$(CC) $(CFLAGS) $(SRC_DIR)/my_mem_alloc.c -o $(LIB_DIR)/my_mem_alloc.so
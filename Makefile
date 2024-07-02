NAME := miniRT

CC := gcc
CFLAGS := -Wall -Wextra -Werror

# ls src/**/*.c >> Makefile
FILES := main.c \
	argb.c \
	minirt.c

FILES := $(addprefix src/, $(FILES))
OFILES := $(patsubst src/%.c, build/%.o, $(FILES))

# debugmake:
# 	@echo $(FILES)
# 	@echo $(OFILES)

MLX_STT := lib/minilibx-linux/libmlx.a

FT_STT := lib/libft/lib/libft.a

# .SILENT:

all: $(NAME)

$(NAME): $(OFILES)
	@$(CC) $(CFLAGS) -o $@ $(OFILES) $(MLX_STT) -lXext -lX11 -lm -lz
	@echo "\033[0;32m\n>>> ./$@\n\033[0m"

build/%.o: src/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -o $@ -c $^
	@echo "\033[0;32m* $^\033[0m"

clean:
	rm -rf build

fclean: clean
	rm -rf $(NAME)

re: fclean all

debug: CFLAGS := -g
debug: re

.PHONY: all, clean, fclean, re, debug


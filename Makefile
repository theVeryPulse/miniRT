NAME := miniRT

CC := gcc
CFLAGS := -Wall -Wextra -Werror -O3

# ls src/**/*.c >> Makefile
FILES := src/color/alpha_component.c \
	src/color/argb.c \
	src/color/blue_component.c \
	src/color/color_add.c \
	src/color/color_mult.c \
	src/color/green_component.c \
	src/color/red_component.c \
	src/geometry/matrix/mx_mult.c \
	src/geometry/matrix/mx_mult_mx.c \
	src/geometry/matrix/mx_transpose.c \
	src/geometry/vector/vec_add.c \
	src/geometry/vector/vec_div.c \
	src/geometry/vector/vec_dot.c \
	src/geometry/vector/vec_len.c \
	src/geometry/vector/vec_minus.c \
	src/geometry/vector/vec_mult.c \
	src/geometry/vector/vec_normalized.c \
	src/handle_keypress_event.c \
	src/main.c \
	src/minirt.c

# FILES := $(addprefix src/, $(FILES))
OFILES := $(patsubst src/%.c, build/%.o, $(FILES))

# debugmake:
# 	@echo $(FILES)
# 	@echo $(OFILES)

MLX_STT := lib/minilibx-linux/libmlx.a

FT_STT := lib/libft/lib/libft.a

# .SILENT:

all: git_submodules $(NAME)

git_submodules:
	@git submodule init
	@git submodule update

$(NAME): $(OFILES) $(FT_STT) $(MLX_STT)
	@$(CC) $(CFLAGS) -o $@ $(OFILES) $(FT_STT) $(MLX_STT) -lXext -lX11 -lm -lz
	@echo "\033[0;32m\n>>> ./$@\n\033[0m"

$(FT_STT):
	$(MAKE) -C lib/libft all

$(MLX_STT):
	$(MAKE) -C lib/minilibx-linux

build/%.o: src/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -o $@ -c $^
	@echo "\033[0;32m* $^\033[0m"

clean:
	rm -rf build

fclean: clean
	rm -rf $(NAME)

re: fclean all

debug: CFLAGS := -g -Wall -Wextra
debug: re

.PHONY: all, clean, fclean, re, debug


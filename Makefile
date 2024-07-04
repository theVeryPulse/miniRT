NAME := miniRT

CC := gcc
CFLAGS := -Wall -Wextra -Werror -O3

# ls src/**/*.c >> Makefile
FILES := main.c \
	argb.c \
	handle_keypress_event.c \
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


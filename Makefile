NAME := miniRT

CC := gcc
# CFLAGS := -Wall -Wextra -Werror
CFLAGS := -Wall -Wextra -g

# ls src/**/*.c >> Makefile
FILES := \
	src/camera/camera.c \
	src/cast_ray/cast_ray.c \
	src/color/alpha_component.c \
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
	src/geometry/vector/vec_cross.c \
	src/geometry/vector/vec_div.c \
	src/geometry/vector/vec_dot.c \
	src/geometry/vector/vec_len.c \
	src/geometry/vector/vec_minus.c \
	src/geometry/vector/vec_mult.c \
	src/geometry/vector/vec_normalize.c \
	src/geometry/vector/vec_normalized.c \
	src/geometry/vector/vec_squared.c \
	src/key_press/handle_keypress_event.c \
	src/key_press/switch_focus.c \
	src/load_file/basic_check.c \
	src/load_file/line_check/check_ambient_light_line.c \
	src/load_file/line_check/check_camera_line.c \
	src/load_file/line_check/check_cylinder_line.c \
	src/load_file/line_check/check_line.c \
	src/load_file/line_check/check_plane_line.c \
	src/load_file/line_check/check_point_light_line.c \
	src/load_file/line_check/check_sphere_line.c \
	src/load_file/load_from_line/load_camera_from_line.c \
	src/load_file/load_from_line/load_cylinder_from_line.c \
	src/load_file/load_from_line/load_light_from_line.c \
	src/load_file/load_from_line/load_object_from_line.c \
	src/load_file/load_from_line/load_rgb.c \
	src/load_file/load_from_line/load_vector.c \
	src/load_file/load_scene_from_file.c \
	src/load_file/skip/skip_coordinate.c \
	src/load_file/skip/skip_number.c \
	src/load_file/skip/skip_rgb.c \
	src/load_file/skip/skip_spaces.c \
	src/main.c \
	src/maths/equals.c \
	src/maths/sign.c \
	src/minirt.c \
	src/minirt_init.c \
	src/object/light/ambient_light.c \
	src/object/light/directional_light.c \
	src/object/light/point_light.c \
	src/object/objects/checkerboard_sphere.c \
	src/object/objects/colored_sphere.c \
	src/object/objects/cylinder.c \
	src/object/objects/disk.c \
	src/object/objects/plane.c \
	src/scene/allocate_lights.c \
	src/scene/allocate_objects.c \
	src/shader/calculate_light_intensity.c \
	src/shader/checkerboard_sphere_color.c \
	src/shader/normal_on_surface.c \
	src/shader/reflect_ray.c \
	src/shader/shade.c \
	src/tracer/ray_cylinder_intersect.c \
	src/tracer/ray_disk_intersect.c \
	src/tracer/ray_plane_intersect.c \
	src/tracer/ray_sphere_intersect.c \
	src/tracer/trace.c

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


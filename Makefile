NAME = cub3D

MAKEFLAGS	+= --quiet

OS			= $(shell uname -s)

LIBFT 		= libft_ext/libft.a
LIBMLX 		= libraries/minilibx-linux/libmlx.a
CFLAGS 		= -g -Wall -Wextra -Werror
# CFLAGS 		= -I/usr/include -Imlx_linux -O3 -g
IFLAGS		= -I libraries/minilibx-linux -Ilmlx -I/includes -Imath
LFLAGS		= -L libraries/minilibx-linux -lmlx -lXext -lX11 -lm
IFLAGS_D	= -I libraries/minilibx_opengl -Ilmlx -I/includes
LFLAGS_D	= -L libraries/minilibx_opengl -lmlx -framework OpenGL -framework AppKit
FFLAGS		= -fsanitize=address
# LFLAGS		= -I ./mlx_linux -L ./mlx_linux -lmlx -Ilmlx -lXext -lX11
AR = ar rcsv
OBJ_DIR = obj
SRC_DIR = src
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

HEADER =	cube3d.h\
			mlx.h\

SRC =		main.c\
			parse.c\
			check.c\
			play.c\
			draw.c\
			draw_utils.c\
			error.c\
			player.c\
			map.c\
			bresenham.c\
			math.c\
			dda.c\
			
all: $(NAME)

$(NAME): $(OBJ)
ifeq ($(OS),Darwin)
	$(MAKE) all -C libft_ext
	$(MAKE) -C libraries/minilibx_opengl
	@echo $(ANSI_RESET) ""
	@echo $(ANSI_B_BGREEN) "compile executable" $(ANSI_RESET)$(ANSI_F_BBLACK)
	clang $(CFLAGS) $(IFLAGS_D) $(OBJ) $(LIBFT) $(LFLAGS_D) -o $(NAME)
	@echo $(ANSI_RESET) ""
endif
ifeq ($(OS),Linux)
	@echo $(ANSI_B_BGREEN) "compile libft_ext" $(ANSI_RESET)$(ANSI_F_BBLACK)
	$(MAKE) all -C libft_ext
	@echo $(ANSI_B_BGREEN) "compile libmlx" $(ANSI_RESET)$(ANSI_F_BBLACK)
	$(MAKE) -C libraries/minilibx-linux
	@echo $(ANSI_RESET) ""
	@echo $(ANSI_B_BGREEN) "compile executable" $(ANSI_RESET)$(ANSI_F_BBLACK)
	clang $(CFLAGS) $(IFLAGS) $(OBJ) $(LIBFT) $(LFLAGS) -o $(NAME)
	@echo $(ANSI_RESET) ""
endif

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(addprefix includes/,$(HEADER))
	@echo $(ANSI_B_BGREEN) "compile $(NAME) objects" $(ANSI_RESET)$(ANSI_F_BBLACK)
	mkdir -p $(dir $@)
	clang $(CFLAGS) -Iincludes -c $< -o $@
	@echo $(ANSI_RESET)

clean:
	@echo $(ANSI_B_RED) "clean" $(ANSI_RESET)$(ANSI_F_BRED)
	$(MAKE) clean -C libft_ext
	rm -rf $(OBJ_DIR)
	@echo $(ANSI_RESET) ""

fclean: clean
	@echo $(ANSI_B_RED) "fclean" $(ANSI_RESET)$(ANSI_F_BRED)
	$(MAKE) fclean -C libft_ext
	rm -f $(NAME)
	@echo $(ANSI_RESET) ""

re: fclean all

.PHONY: all clean fclean

# colors
ANSI_RESET = "\033[0m"
ANSI_B_RED = "\033[41m"
ANSI_B_BGREEN = "\033[42;1m"
ANSI_F_BRED = "\033[31;1m"
ANSI_F_BBLACK = "\033[30;1m"


lib:
	$(MAKE) -C libft_ext

norm:
	@echo $(ANSI_B_RED) "norminette v3" $(ANSI_RESET)
	$(MAKE) norm -C libft_ext
	@norminette $(addprefix inc/,$(HEADER)) \
		$(addprefix src/,$(SRC))

libnorm:
	@echo $(ANSI_B_RED) "libft norminette" $(ANSI_RESET)
	$(MAKE) norm -C libft_ext

run: all
	@echo $(ANSI_B_RED) "Running Game" $(ANSI_RESET)
	./$(NAME) $(MAP)
	# @./$(NAME)

runv: all
	@echo $(ANSI_B_RED) "Valgrind RESULT" $(ANSI_RESET)
	#valgrind -q --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(NAME)
	valgrind --leak-check=full --show-leak-kinds=all -s ./$(NAME) maps/map.cub

fsan: all
	@echo $(ANSI_B_RED) "fsanitize=address" $(ANSI_RESET)
	./$(NAME) 

test: all
	@echo $(ANSI_B_RED) "Running test" $(ANSI_RESET)
	clang -I ./libraries/mlx_linux -L ./libraries/mlx_linux -lmlx -Ilmlx -lXext -lX11 libraries/mlx_linux/libmlx.a test.c libft_ext/libft.a libraries/mlx_linux/libmlx.a -o windows_test
	./windows_test
NAME=scop

VPATH=src

#FLAGS=-Wall -Wextra -Werror -I libft -I includes -lGL -lGLU -lGLEW -lglut -lm -g
FLAGS=-Wall -Wextra -Werror -I libft -I includes -g
ifeq ($(shell uname -s),Darwin)
	#FLAGS+=-I ~/.brew/include
	FLAGS+=-I ~/Library/Frameworks/SDL2.framework/Headers
	FLAGS+=-I libglew/include/ 
	FLAGS+=-F ~/Library/Frameworks
	LINKER_FLAGS=-F ~/Library/Frameworks -framework OpenGL -framework SDL2
 	LINKER_FLAGS+=-L $(shell pwd)/libglew/lib -lGLEW
 	# LINKER_FLAGS+=libglew/lib/libGLEW.a
	CC=clang
else
	LINKER_FLAGS=-lGL -lGLU -lGLEW -lSDL2 -lm
	CC=gcc
endif


all: $(NAME)

SRC=main.c							\
	parser/reader.c					\
	parser/parser.c					\
	parser/face_parser.c			\
	parser/flatten_vectors.c		\
	parser/material_parser.c		\
	bmp_loader/bmp_loader.c			\
	graphics/sdl_init.c				\
	graphics/sdl_callbacks.c		\
	graphics/load_shaders.c			\
	graphics/sdl_main_loop.c		\
	matrix/matrix_utils.c			\
	matrix/special_matrices.c		\
	vertex/vertex_math.c			\
	object/object.c					\

BINDIR=bin

BINS=$(addprefix $(BINDIR)/, $(SRC:.c=.o))

LIBFT=libft/libft.a

$(BINDIR)/%.o: %.c
	@mkdir -p $(shell dirname $@)
	$(CC) -c -o $@ $< $(FLAGS)

$(LIBFT):
	make -C libft

$(NAME): $(BINS) $(LIBFT)
	$(CC) -o $(NAME) $(BINS) $(LIBFT) $(LINKER_FLAGS)

clean:
	rm -f $(BINS)
	#make -C libft clean

fclean: clean
	rm -f $(NAME)
	#make -C libft fclean

re: fclean all

NAME=scop

VPATH=src

FLAGS=-Wall -Wextra -Werror -I libft -I includes -lGL -lGLU -lGLEW -lglut -lm -g

all: $(NAME)

SRC=main.c							\
	parser/reader.c					\
	parser/parser.c					\
	parser/face_parser.c			\
	parser/flatten_vectors.c		\
	parser/material_parser.c		\
	bmp_loader/bmp_loader.c			\
	graphics/glut.c					\
	graphics/glut_callbacks.c		\
	graphics/load_shaders.c			\
	matrix/matrix_utils.c			\
	matrix/special_matrices.c		\
	vertex/vertex_math.c			\
	object/object.c					\

BINDIR=bin

BINS=$(addprefix $(BINDIR)/, $(SRC:.c=.o))

LIBFT=libft/libft.a

$(BINDIR)/%.o: %.c
	@mkdir -p $(shell dirname $@)
	gcc -c -o $@ $< $(FLAGS)

$(LIBFT):
	make -C libft

$(NAME): $(BINS) $(LIBFT)
	gcc -o $(NAME) $(BINS) $(LIBFT) $(FLAGS)

clean:
	rm -f $(BINS)
	#make -C libft clean

fclean: clean
	rm -f $(NAME)
	#make -C libft fclean

re: fclean all

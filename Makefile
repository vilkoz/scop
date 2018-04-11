NAME=scop

VPATH=src

FLAGS=-Wall -Wextra -Werror -I libft -I includes -g -O3
ifeq ($(shell uname -s),Darwin)
	FLAGS+=-I ~/Library/Frameworks/SDL2.framework/Headers
	FLAGS+=-I ~/.brew/include
	FLAGS+=-F ~/Library/Frameworks
	LINKER_FLAGS=-F ~/Library/Frameworks -framework OpenGL -framework SDL2
 	LINKER_FLAGS+=-L ~/.brew/lib/ -lGLEW
	CC=clang
else
	LINKER_FLAGS=-lGL -lGLU -lGLEW -lSDL2 -lm
	CC=gcc
endif


all: $(NAME)

SRC=main.c								\
	parser/reader.c						\
	parser/parser.c						\
	parser/face_parser.c				\
	parser/flatten_vectors.c			\
	parser/material_parser.c			\
	parser/material_parser_callbacks.c	\
	parser/progress_visualizer.c		\
	bmp_loader/bmp_loader.c				\
	graphics/sdl_init.c					\
	graphics/sdl_callbacks.c			\
	graphics/load_shaders.c				\
	graphics/sdl_main_loop.c			\
	graphics/sdl_keyboard.c				\
	graphics/check_gl_error.c			\
	matrix/matrix_utils.c				\
	matrix/special_matrices.c			\
	vertex/vertex_math.c				\
	object/object.c						\
	object/generate_arrays.c			\
	object/object_create_vao.c			\
	object/object_material.c			\
	object/object_fit_to_screen.c		\
	object/skybox/skybox.c				\
	object/skybox/cubemap_loader.c		\

BINDIR=bin

BINS=$(addprefix $(BINDIR)/, $(SRC:.c=.o))

LIBFT=libft/libft.a

$(BINDIR)/%.o: %.c
	@mkdir -p $(shell dirname $@)
	$(CC) -c -o $@ $< $(FLAGS)

$(LIBFT):
	make -C libft

SKYBOX_FOLDER=res/skybox

SKYBOX_ARCHIEVE_FOLDER=$(SKYBOX_FOLDER)/archieve

SKYBOX_ARCHIEVE=skyboxes.tar.gz

SKYBOX_FILENAMES=bk.bmp		\
				 dn.bmp		\
				 ft.bmp		\
				 lf.bmp		\
				 rt.bmp		\
				 up.bmp		\

SKYBOXES=lake_skybox space_skybox

SKYBOX_FILES=$(foreach x,$(SKYBOXES),$(addprefix $(SKYBOX_FOLDER)/$x/,$(SKYBOX_FILENAMES)))

SKYBOX_ARCHIVED_FILES=$(foreach x,$(SKYBOX_FILES),$(subst $(SKYBOX_FOLDER),$(SKYBOX_ARCHIEVE_FOLDER),$(x:.bmp=.bmp.gz)))

# $(SKYBOX_ARCHIEVE_FOLDER)/lake_skybox/%.bmp.gz: $(SKYBOX_FOLDER)/lake_skybox/%.bmp
# 	@echo $<
# 	@echo $@
# 	@mkdir -p $(shell dirname $@)
# 	cat $< | gzip -n > $@

# $(SKYBOX_ARCHIEVE_FOLDER)/space_skybox/%.bmp.gz: $(SKYBOX_FOLDER)/space_skybox/%.bmp
# 	@echo $<
# 	@echo $@
# 	@mkdir -p $(shell dirname $@)
# 	cat $< | gzip -n > $@

$(SKYBOX_FOLDER)/lake_skybox/%.bmp: $(SKYBOX_ARCHIEVE_FOLDER)/lake_skybox/%.bmp.gz
	@mkdir -p $(shell dirname $@)
	gunzip -c $< > $@

$(SKYBOX_FOLDER)/space_skybox/%.bmp: $(SKYBOX_ARCHIEVE_FOLDER)/space_skybox/%.bmp.gz
	@mkdir -p $(shell dirname $@)
	gunzip -c $< > $@

archieve: $(SKYBOX_ARCHIVED_FILES)

$(NAME): $(BINS) $(LIBFT) | $(SKYBOX_FILES)
	$(CC) -o $(NAME) $(BINS) $(LIBFT) $(LINKER_FLAGS)

clean:
	rm -f $(BINS)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	rm -f $(SKYBOX_FILES)
	make -C libft fclean

re: fclean all

.PHONY: re fclean clean archieve

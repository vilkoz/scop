NAME=scop

VPATH=src

FLAGS=-Wall -Wextra -Werror -I libft -I includes -g

all: $(NAME)

SRC=main.c					\
	parser/parser.c

BINDIR=bin

BINS=$(addprefix $(BINDIR)/, $(SRC:.c=.o))

LIBFT=libft/libft.a

$(BINDIR)/%.o: %.c
	@mkdir -p $(shell dirname $@)
	gcc $(FLAGS) -c -o $@ $<

$(LIBFT):
	make -C libft

$(NAME): $(BINS) $(LIBFT)
	gcc $(FLAGS) -o $(NAME) $(BINS) $(LIBFT)

clean:
	rm -f $(BINS)
	#make -C libft clean

fclean: clean
	rm -f $(NAME)
	#make -C libft fclean

re: fclean all

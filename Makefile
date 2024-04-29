NAME = minishell

CC = cc
CFLAGS = -Wall -Werror -Wextra -I/usr/local/opt/readline/8.2.1/include
LDFLAGS = -Llibft -lft -L/usr/local/opt/readline/8.2.1/lib -lreadline 

SRCS = main.c inits.c signals_ctrl.c\
		 free_and_error/free_methods_1.c\
		 free_and_error/free_methods.c\
		 free_and_error/error.c \
		 env/ft_envlst.c\
		 env/ft_listutils.c\
		 parsing/utils/parse_utils.c\
		 parsing/utils/array_utils.c\
		 parsing/utils/space_utils.c\
		 parsing/tokenisation/splits_delim.c\
		 parsing/tokenisation/token.c \
		 parsing/tokenisation/token1.c \
		 parsing/tokenisation/expansion_utils.c \
		 parsing/tokenisation/expansion_utils1.c \
		 parsing/tokenisation/expansion.c \
		 parsing/tokenisation/wild_card.c \
		 parsing/tokenisation/syntax.c \
		 parsing/commands_redir/compound.c\
		 parsing/commands_redir/pipeline.c\
		 parsing/commands_redir/redirection.c\
		 execution/process_handling/1_excecution.c\
		 execution/process_handling/exec_utils.c\
		 execution/process_handling/2_cmd_execution.c\
		 execution/process_handling/3_cmd_execution.c\
		 execution/redirction/redir_proc.c\
		 execution/redirction/redir_proc1.c\
		 execution/redirction/heredoc.c\
		 execution/builtins/ft_cd.c\
		 execution/builtins/ft_export_utils.c\
		 execution/builtins/ft_builtins.c\
		 execution/builtins/ft_export.c\
		 execution/builtins/builtin_utils.c\
		

		

OBJS = $(SRCS:.c=.o)

all: $(NAME)

# Compile Libft library if necessary
libft/libft.a:
	$(MAKE) -C Libft

# Build the executable
$(NAME): $(OBJS) libft/libft.a
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) -o $(NAME)

# Rule to compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files and executable
clean:
	rm -f $(OBJS)
	$(MAKE) -C Libft clean

# Clean object files, executable, and Libft library
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C Libft fclean

# Run Norminette
norm:
	norminette 
	norminette includes/*.h
	
# Rebuild the project
re: fclean all

.PHONY: all clean fclean re norm

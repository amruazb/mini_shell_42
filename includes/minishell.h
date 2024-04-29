/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmuhamm <shmuhamm@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:57:14 by aabashee          #+#    #+#             */
/*   Updated: 2024/04/23 15:52:46 by shmuhamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "colors.h"
# include "libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <stdbool.h>
# include <dirent.h>
# include <limits.h>
# include <sys/wait.h>

// Your other includes here
extern int				g_exit_code;
typedef struct s_quote
{
	bool				single_q;
	bool				double_q;
}						t_quote;

/*Tokens Struct*/
typedef enum s_token_type
{
	WORD,
	REDIR,
	PIPE,
	AND,
	OR,
	OPEN_PAREN,
	CLOSE_PAREN,
}						t_token_type;

typedef enum s_redir_type
{
	INPUT,
	OUTPUT,
	APPEND,
	HEREDOC,
}						t_redir_type;

typedef struct s_char
{
	char				**array;
	bool				is_expanded;
	bool				isfreed;
}						t_char;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	bool				isfreed;
	struct s_token		*next;
}						t_token;

/*Simple Command and Redirections Struct*/
typedef struct s_redir
{
	t_redir_type		type;
	char				*filename;
	bool				isfreed;
	struct s_redir		*next;
}						t_redir;

typedef struct s_command
{
	char				*cmd;
	int					cmd_len;
	int					args_len;
	t_char				*args;
	int					total_redirs;
	t_redir				*redirs;
	bool				isfreed;
}						t_command;

typedef enum s_paren_type
{
	AFTER_OPEN_PAREN,
	BEFORE_CLOSE_PAREN,
	NOT_PAREN,
}						t_paren_type;

typedef struct s_compound
{
	t_command			**s_commands;
	t_token_type		split_on;
	int					cmd_len;
	t_paren_type		paren;
	bool				isfreed;
}	t_compound;

typedef struct s_shell
{
	t_compound			**cmpd_node;
	t_char				*env_vars;
	t_list				*env_list;
	int					error_no;
	int					total_pipes;
	char				pwd[1024];
	int					fd[256][2];
	int					pid1;
	int					pid2;
	int					middle_scommand;
	int					index;
	int					counter;
	int					process_id;
	int					process_id1;
	char				*line;
	t_token				*tokenlist;
	t_list				*temp_list;
	int					flag;
	int					flag_out;
	int					flag_in;
	int					check;
	int					x;
	int					dont;
	unsigned long long	copy;
	bool				isfreed;
	int					cmd_len;
	unsigned long long	*res_atoi;
	unsigned long long	*copy_atoi;
	char				*path;
	char				*result;
	char				**path_split;
	bool				is_heredoc;
	int					i;
	t_token_type		split_on;
	t_paren_type		paren;

}	t_shell;

typedef struct s_exp_var
{
	char				*cp;
	char				*tmp;
	char				*tmp_ex;
	int					x;
	int					y;
	int					start;
	int					flag_sq;
	int					flag_dq;
	int					flag_pwd;
	int					flag_shlvl;
	int					flag_oldpwd;
	int					flag;
	int					last_index;
	int					last_pos;
	t_list				*tmp_list;

}						t_exp_var;
typedef struct s_heredoc_var
{
	int					file1;
	char				*tmp;
	char				*delimiter;
	int					ret;
}	t_heredoc_var;

/*norms*/
void			ft_writing(t_command **pipe, t_shell *proc);

// environment variables handling
void			create_envlist(t_shell *proc, char **env);
char			*ft_getenv(t_list *head, char *str);
void			ft_env_print_linked(t_shell *proc);

// error handling
void			checkenv(char **envp);
t_shell			*allocateshell(void);
void			checkargs(int ac, char **av);
int				ft_token_count(char **str);

//array_utils
char			**append_array(char **s1, char **s2);
int				ft_array_len(char **str);

// free methods
void			safe_free(void *ptr);
void			free_and_exit(t_shell *sea_shell, char *message);
void			garbage_collector(t_shell **sea_shell);
void			free_array(char **array);
void			parsing_garbage_collector(t_shell **sea_shell);
void			free_env_list(t_list **head);
void			free_token_list(t_token **tokenlist);
void			free_t_char(t_char **char_struct);
void			free_short(char *path, char **path_split);
void			free_compoundlist(t_compound ***nodes);

//inits
void			init_sea_shell(t_shell *sea_shell);
void			init_prompt(t_shell *sea_shell);
void			init_sea_shell_exec(int ac, t_shell *bash);
void			init_parsing(t_shell *proc);
void			init_vars(t_exp_var *var);

// parsing
bool			check_line(char *str);
bool			array_strchr(char *s, char c);
char			**ft_split_on_delims(char *str);
char			**append_array(char **s1, char **s2);

// parsing/space_utils.c
char			**ft_space(char *s);
void			set_quote_flag(t_quote *value, char c);

// tokenisation
bool			needs_expansion(char *str);
bool			ft_tokenise(t_shell *sea_shell, char **str_tokens);
char			*final_expanded_str(t_shell *sea_shell, char *str);
void			expand_token(t_token **tokenlist, char *str, t_shell *seashell);
void			token_quote_removal(t_token *tokenlist);
bool			token_syntax_check(t_token *headtoken);
char			*remove_quotes(char *str, int in);
t_token			*new_token_node(char *arg);
t_token_type	assign_t_token_type(char *arg);

// commands and redirections
void			create_compound_array(t_shell *sea_shell, t_token *headtoken);
void			create_compound_node(t_token *start, t_token *end,
					t_shell	*sea_shell, t_compound *node);
// expansion
void			add_token_node(t_token **tokenlist, t_token *tokenNode);
char			*new_expanded_str(t_shell *sea_shell, char *str);
int				get_search_var_end(char *str, int start);
int				get_end_index_expan(char *str, int start);
int				get_end_index(char *s, char *metachars, int start);
int				get_end_index_sp(char *s, char *white_spaces, int start);

// redirection
int				count_redirs(t_redir *redirs);
int				count_pipes(t_token *start, t_token *end);
void			fill_redirs(t_command *scommand,
					t_token *redir, t_token *filename);
void			red_one_cmd(t_command **av, t_shell *proc);
void			red_first_proc(t_command **av, int *flag, t_shell *proc);
void			red_last_proc(t_command **av, int *flag, t_shell *proc);
void			red_middle(t_command **av, int *flag_out,
					int *flag_in, t_shell *proc);
int				red_output(t_redir *redir, t_shell *proc);
int				red_infile(t_redir *redir, t_shell *proc);
int				red_append_mode(t_redir *redir, t_shell *proc);

// execution
bool			start_execution(t_compound *cpmd_node, t_shell *sea_shell);
void			check_and_execute(t_shell *proc,
					t_command **av, char **envp, char *tmp);
int				search(char **envp);

void			terminate(char *display, t_shell *sea_shell);
int				check_and_update_heredoc(t_compound *cpmd_node,
					t_shell *sea_shell);
//builtins
int				check_and_replace(t_list *head, char *replace);
void			do_operation(t_shell *proc, t_command **av);
int				ft_cd(t_command **pipe, t_shell *proc);
void			ft_pwd(t_shell *data);
void			ft_exit(t_command **pipe, t_shell *proc);
void			ft_echo(t_command **pipe, t_shell *proc);
void			print_and_set_flag(t_command **pipe, t_shell *proc);
int				ft_check_builtin(char *cmd);
void			check_built_ins_and_exexute_one_cmd(t_shell *proc,
					t_command **av);
int				ft_export_print_linked(t_command **pipe, t_shell *prc);
void			check_built_ins_and_exexute(t_shell *proc, t_command **av);
void			check_built_ins_and_exexute_one_cmd(t_shell *proc,
					t_command **av);
int				ft_unset(t_command **pipe, t_shell *proc);
unsigned char	ft_small_atoi(const char *str);

// execution/process_handling
int				first_process(t_shell *proc, t_command **av, char **envp);
int				last_process(t_shell *proc, t_command **av, char **envp);
void			terminate(char *display, t_shell *sea_shell);
void			close_pipes(t_shell *proc);
int				pipex_three_cmd(t_command **av, t_shell *proc, char **envp);
int				pipex_two_cmd(t_command **av, t_shell *proc, char **envp);
char			*get_command(t_shell *proc, char **envp, char *s);
void			free_func_one_cmd(t_command **av, t_shell *proc);
void			cmd_not_found(t_command **av, t_shell *proc, int counter);

// list_utils
int				remove_element(t_list **head, int index);
void			re_index(t_list *head);
void			sort_list(t_list *head);
t_char			*linked_to_array(t_list *head);
int				pipex_two_cmd(t_command **av, t_shell *proc, char **envp);

/*wild_card*/
bool			filename_expansion(t_token **tokenlist, char *str_token);
int				process_parens(t_compound **nodes, int start, t_shell *bash);
bool			should_execute(t_compound *node);

/*signals*/
void			init_signals(void);
void			sig_handler(int num);
void			child_sig_handler(int num);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 18:33:28 by arahmoun          #+#    #+#             */
/*   Updated: 2023/05/26 14:01:03 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define GREEN "\033[0;32m"
# define RED "\033[0;31m"
# define YOLLOW "\033[0;33m"
# define DEF "\033[0m"

typedef struct s_redir
{
	enum
	{
		in,
		out,
		append,	
		herdoc,
	}	e_rtype;
	int				type;
	int				fd;
	char			*file;
	struct s_redir	*next;
}					t_redir;

typedef struct s_sps
{
	int		i;
	int		len;
	int		sp;
	char	*ret;
	char	cot;
}			t_sps;

typedef struct s_spl
{
	int	i;
	int	j;
	int	a;
	int	skip;
	int	cot;
}		t_spl;

typedef struct s_all
{
	int				pipe[2];
	int				i;
	int				permission;
	int				redii;
	int				flag;
	int				word;
	char			*text;
	char			**cmd;
	char			**command;
	t_redir			*rdr;
	char			*path;
	struct s_all	*next;
}					t_all;

typedef struct s_env_s
{
	int		i;
	int		a;
	char	**ret;
	char	**s;
}			t_env_s;

typedef struct s_hex
{
	int		i;
	int		slen;
	int		len;
	char	*re;
}			t_hex;
typedef struct s_var
{
	int		i;
	int		j;
	int		x;
	int		len;
	int		slen;
	char	*dst;
	t_all	*temp;
	t_redir	*red;
}			t_var;
typedef struct s_export
{
	char	**new_environ;
	size_t	total_len;
	size_t	value_len;
	size_t	name_len;
	size_t	env_count;
	char	*new_var;
	size_t	i;
}			t_export;

typedef struct s_cmds
{
	int				fd[2];
	int				i;
	int				j;
	int				x;
	int				n;
	char			***cmd;
	int				fdd;
	pid_t			pid;
}					t_cmds;

typedef struct s_exp
{
	char			*var;
	char			*val;
	struct s_exp	*next;
}					t_exp;

typedef struct s_ex
{
	char	*msg;
	char	**env;
	t_exp	*exp;
	int		env_counter;
	int		i;
	int		exit_status;
	int		sig;
	int		herdoc_flag;
	char	**n_env;
	char	*ppp;
	char	*old;
}			t_ex;

typedef struct t_exec
{
	int	i;
	int	id;
	int	status;
	int	number_cmd;
	int	permission;
	int	fdpipe[2];
	int	*fd;
}	t_exec;

typedef struct s_he
{
	int		i;
	t_ex	pp;
	int		j;
	t_ex	n;
	t_ex	st_ref;
}			t_he;

t_ex	g_tmp;
//      error
void	error_arg(void);
void	ft_error(void);

// linked list
t_all	*ft_lstnew(void);
void	ft_lstadd_back(t_all **lst, t_all *new_);
void	ft_lstadd_back_rdr(t_redir **lst, t_redir *new_);

//      tools
char	*ft_strdup(const char *s1);
char	**ft_ddup(char **str);
int		ft_strlen(char const *str);
char	*ft_itoa(int n);
void	*ft_calloc(int count, int size);
int		check_str(char *str, const char *ch);
void	handle_c(void);
void	skip_spaces(char *str, int *i);
void	double_free(char **str);
void	freero(t_all *lexer);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	**ft_sp_var(char *str, char c);
void	lexer_text(t_all *lexer);
int		big_check(t_all *lexer);
void	init_lexer(t_all *lexer, char **env);
int		check_pip(t_all *lexer);

// parser functions
char	**ft_split(char const *s, char *c);
char	*sp_split(char *str);
void	remove_dq(t_all *lexer);
void	expand_var(t_all *lexer, char **envp);
void	check_ex(t_all *lexer);
char	*handle_ex(char *str, char *pid);
char	*fix_var(char *str, char **envp);
char	*cpy_var(char *s, char *str, int j);
char	*not_var(char *s, int i);
int		index_dollar(char *s1, char *s2, int i);
int		skip_alpha(char *s2, int i);
int		ft_strcmp(char *s1, char *s2, int i);
int		redir(t_all *lexer, char **env);
int		ft_isalnum(int c);
char	*on_env(char **env, char *name);
void	ft_herdog(t_all *lexer, int i, char **env);

// executer functions
char	**get_path(char **env);
void	ft_exec(t_all *lexer, char **env);
char	**alloc_join(t_all *lexer);
char	*fft_strjoin(char const *s1, char const *s2);
void	closeanddup(int i, int j, int pipefd[2]);
char	*ft_strcpy(char *dst, const char *src);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_input_redirection(t_all *lexer, t_redir *redi);
int		check_out(char *cmd);
int		check_in(char *cmd);
int		ft_my_strcmp(char *s1, char *s2);

// builtins
void	ft_echo(t_all *lexer, int *fd);
void	ft_putstr_fd(char *s, int fd);
int		ft_pwd(t_all *lexer, int *fd);
int		ft_cd(char **str);
char	**ft_export(char **str, char **env, int *fd);
int		ft_redirection_input(t_all *lexer, t_redir *redi);
int		ft_redirection_output(t_all *lexer, t_redir *redi);
int		ft_redirection_append(t_all *lexer, t_redir *redi);
int		ft_herdoc(t_all *lexer, t_redir *redi, t_exec exec);
int		*ft_check_redirections(t_all *lexer, t_redir *redi, t_exec exec);
int		*check_redi(t_all *lexer, t_redir *redi, t_exec exec);
int		ft_size_of_lexer(t_all *lexer);
void	ft_exit(char **str);
int		my_env(char **s, int *c);
char	**ft_my_split(char *s, char c);
int		ft_counter(char **str);
int		compare_strings(const void *a, const void *b);
char	*ft_strchr(const char *s, int c);
char	**ft_unset(char **str, char **env);
int		ft_equal_counter(char *str);
int		double_pointer_counter(char **str);
int		check_exist_var(t_exp *node, char *str);
t_exp	*ft_stock(char **env);
void	env_back(t_exp **lst, t_exp *new_);
t_exp	*ft_lstenv_new(char *val, char *var);
int		ft_pass(t_he *var);
void	ft_cas(t_he *var);
void	ft_free(t_he *var);
t_he	*var_init(t_he *var);
int		ft_check(char *str);
char	**env_stock(char **env, char *var);
int		ft_find_word(char *str, char **env);
char	*set_cwd(char *str, const char *name);
int		check_inval(char *str);
char	**ft_edit_env(char **env, char *var, char *val);
char	*ft_mix(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, size_t n);
int		calcul_equal(char *str);
void	ft_else_condition(char ***env, t_ex *pp, char **s);
int		exist_var(char **env, char *var);
char	**ft_ch_env(char **env, char *var, char *val);
void	ft_if_condition(char ***env, char **s, char **str, int i);
int		ft_my_strncmp(char *s1, char *s2, size_t n);
int		check_old_pwd(char *str, char *name);
int		get_pwd(char **env);
void	child_dup_2(t_exec exec);
int		ft_liste_size(t_all *lexer);
void	norm_execution(t_exec exec, t_all *tmp);
void	initial(t_all *lexer);
t_exec	ft_init_exec(t_all *lexer);
int		*check_files(t_all *lexer, t_exec exec);
void	ft_builtins(t_all *lexer, int *fd, char **env);
t_exec	execution_of_child(t_all *lexer, t_exec exec, char **env);
t_exec	ft_run_cmd(t_all *lexer, t_exec exec, char **env);
int		ft_exit_status(t_all *lexer);
t_exec	check_if_cmd_ready(t_all *lexer, t_exec exec, char **env);
void	close_parent_rdr(t_redir *redir);
void	parent_close(t_all *tmp);
int		ft_herdoc(t_all *lexer, t_redir *redi, t_exec exec);
void	flag_permi(int flag, int permi, int code);
void	check_builtins(t_all *lexer, int i, int *fd, char **env);
int		check_if_builtins(char **args);
int		ft_tolower(int c);
char	*ft_convert(char *arg);
void	set_path(t_all *lexer, char **env);
void	dup_and_close(int tmp_in, int tmp_out);
void	wait_and_exit(t_exec exec);
void	only_export(int *fd);
void	ft_incr(t_he *var);
void	var_j(t_var	*var);
void	ft_hhelp(t_var *var, char *s);
void	ft_pop(int *a, int *i);
void	ft_plata(int *a, int *i);
void	set_redir(t_all *lexer, int i, int type, char *file);
int		ft_small_else(t_var *var, t_all *lexer);
int		ft_small_if(t_var *var, t_all *lexer, char **env);
int		check_empty(char *file);
int		cmp_sep(char c, char *sep);
int		ft_count_words(char *s, char *c);
void	ft_alocate(char **tab, char *s, char *c, int w);
void	ft_func_while(t_sps *sp, char *str);
char	*ft_dollar_interog_case(char *str, t_hex *hx, char *pid);
void	ft_pid_case(char *str, t_hex *hx);
char	*ft_pid_return(t_hex *hx, char *str, char *pid);
void	ft_case_34(char *str, int *i);
void	ft_case_i_34(t_hex *hx, char *str);
void	ft_last_init(int *j, int *i);
char	*set_old(char **env, int x, int fr, const char *name);
void	old_pwd(char **env);
char	**pwd_env(char **env, char *pwd);
// void	rl_replace_line(char *str, int i);

#endif
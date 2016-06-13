/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgatibel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 16:36:21 by lgatibel          #+#    #+#             */
/*   Updated: 2016/04/19 15:03:15 by lgatibel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBLS_H
# define LIBLS_H
# define BUFF_SIZE_LS 1024
# include <libft.h>
# include <stdio.h>
# include <dirent.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <sys/types.h>

typedef struct stat		t_stat;
typedef struct dirent	t_dirent;
typedef struct mode_t	t_mode;
typedef struct passwd	t_passwd;

typedef struct	s_ls_dir
{
	char			*name;
	char			*right;
	char			*link;
	char			*usr;
	char			*grp;
	char			*size;
	char			*hour;
	long long int	time;
	int				maxlink;
	int				maxusr;
	int				maxgrp;
	int				maxsize;
	int				block;
	int				total;
	t_stat			stat;
	char			*path;
	struct s_ls_dir	*next;
	struct s_ls_dir	*deep;
}				t_ls_dir;

typedef struct	s_ls_args
{
	char				*path;
	t_stat				stat;
	char				*right;
	char				*error;
	int					ok;
	struct s_ls_args	*next;
}				t_ls_args;

typedef struct	s_ls_func
{
	t_ls_dir	*(*sort)(t_dirent *, t_ls_dir **, char *path);
	void		(*display)(t_ls_dir **);
	t_ls_args	*(*args)(char *, t_ls_args **);
	void		(*stat)(char *, t_ls_dir **, struct s_ls_func *);
	int			name;
	int			ok;
	int			more_stat;
}				t_ls_func;

void			ft_ls_type(t_ls_dir **lst_files);
void			ft_ls_type_args(t_ls_args **args);
void			ft_ls_display(t_ls_dir **lst_files);
void			ft_ls_display_l(t_ls_dir **lst_files);
void			ft_ls_display_a(t_ls_dir **lst_files);
void			ft_ls_display_la(t_ls_dir **lst_files);
void			ft_ls_stat(char *old_file, t_ls_dir **lst_files,
		t_ls_func *ft_ls);
void			ft_ls_stat_recursive(char *old_file, t_ls_dir **lst_files,
		t_ls_func *ft_ls);

int				ft_ls_verif_options(char *options);
int				ft_ls_verif_param(char **av, int ac, t_ls_func *ft_ls);
void			ft_ls_verif_args(t_ls_args **args, t_ls_func *ft_ls);
int				ft_ls_verif_path(const char *current_path);

int				ft_ls_parse(char *path, t_ls_func *ft_ls, int index);

t_ls_dir		*ft_ls_sort(t_dirent *file, t_ls_dir **lst_files, char *path);
void			ft_ls_sort_args_type(t_ls_args **args, t_ls_func *ft_ls);
t_ls_dir		*ft_ls_sort_time(t_dirent *file, t_ls_dir **lst_files,
		char *path);
t_ls_dir		*ft_ls_sort_time_reverse(t_dirent *file, t_ls_dir **lst_files,
		char *path);
t_ls_dir		*ft_ls_sort_reverse(t_dirent *file, t_ls_dir **lst_files,
		char *path);
t_ls_args		*ft_ls_sort_args(char *path, t_ls_args **lst_args);
t_ls_args		*ft_ls_sort_directory(t_ls_args **lst_args);
t_ls_args		*ft_ls_sort_args_reverse(char *path, t_ls_args **lst_args);

t_ls_dir		*ft_ls_place_link(t_ls_dir *first, t_ls_dir *second,
int choice);
t_ls_args		*ft_ls_place_link_args(t_ls_args *first, t_ls_args *second,
int choice);

t_ls_dir		*ft_ls_set_link(const char *file_name, char *path);
t_ls_func		ft_ls_set_function(char *option, t_ls_func *ft_ls);
void			ft_ls_set(t_ls_func *ft_ls);
t_ls_args		*ft_ls_set_args(char **av, int cpt, int ac, t_ls_func *ft_ls);
t_ls_args		*ft_ls_set_link_args(const char *path);
int				ft_ls_set_padding(t_ls_dir **lst_args);

#endif

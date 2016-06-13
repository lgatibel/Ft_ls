/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_right.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgatibel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 13:58:47 by lgatibel          #+#    #+#             */
/*   Updated: 2016/04/19 15:22:54 by lgatibel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libls.h>

static void		ft_ls_more_annexe(t_ls_dir **lst_files, t_stat *right)
{
	char *minor;

	(*lst_files)->size = ft_strdup(ft_itoa(major(right->st_rdev)));
	minor = ft_strdup(ft_itoa(minor(right->st_rdev)));
	(*lst_files)->size = ft_strjoin((*lst_files)->size, ",");
	(*lst_files)->size = ft_strjoin((*lst_files)->size,
			ft_strjoin(ft_strndupchr(' ', 4 - ft_strlen(minor)), minor));
	(*lst_files)->maxsize = (int)ft_strlen((*lst_files)->size);
}

static char		*ft_ls_calc_time(t_stat *right)
{
	time_t			epoch;
	char			*hour;

	epoch = time(&epoch);
	hour = " ";
	if (right->st_mtime - epoch > -15724800 &&
			right->st_mtime - epoch < 0)
	{
		hour = ft_strjoin(ft_strsub(ctime(&right->st_mtime), 4, 12), hour);
		return (hour);
	}
	hour = ft_strjoin(ft_strsub(ctime(&right->st_mtime), 19, 5), hour);
	hour = ft_strjoin(ft_strsub(ctime(&right->st_mtime), 4, 7), hour);
	return (hour);
}

static void		ft_ls_more(t_ls_dir **lst_files)
{
	struct passwd	*user;
	struct group	*groupe;
	t_stat			*right;

	right = &(*lst_files)->stat;
	user = getpwuid(right->st_uid);
	groupe = getgrgid(right->st_gid);
	(*lst_files)->time = right->st_ctime;
	(*lst_files)->link = ft_strdup(ft_itoa(right->st_nlink));
	(*lst_files)->block = right->st_blocks;
	(*lst_files)->maxlink = (int)ft_strlen((*lst_files)->link);
	(*lst_files)->link = ft_strjoin((*lst_files)->link, " ");
	(*lst_files)->usr = ft_strdup(user->pw_name);
	(*lst_files)->maxusr = (int)ft_strlen((*lst_files)->usr);
	(*lst_files)->grp = ft_strdup(groupe->gr_name);
	(*lst_files)->maxgrp = (int)ft_strlen((*lst_files)->grp);
	(*lst_files)->size = ft_strdup(ft_itoa(right->st_size));
	(*lst_files)->maxsize = (int)ft_strlen((*lst_files)->size);
	if ((*lst_files)->right[0] == 'c' || (*lst_files)->right[0] == 'b')
		ft_ls_more_annexe(lst_files, right);
	(*lst_files)->size = ft_strjoin((*lst_files)->size, " ");
	(*lst_files)->hour = ft_ls_calc_time(right);
}

static char		*ft_ls_right(t_ls_dir **lst_files)
{
	mode_t		type;

	type = (*lst_files)->stat.st_mode;
	if ((type & S_IRUSR) == S_IRUSR)
		(*lst_files)->right[1] = 'r';
	if ((type & S_IWUSR) == S_IWUSR)
		(*lst_files)->right[2] = 'w';
	if ((type & S_IXUSR) == S_IXUSR)
		(*lst_files)->right[3] = 'x';
	if ((type & S_IRGRP) == S_IRGRP)
		(*lst_files)->right[4] = 'r';
	if ((type & S_IWGRP) == S_IWGRP)
		(*lst_files)->right[5] = 'w';
	if ((type & S_IXGRP) == S_IXGRP)
		(*lst_files)->right[6] = 'x';
	if ((type & S_IROTH) == S_IROTH)
		(*lst_files)->right[7] = 'r';
	if ((type & S_IWOTH) == S_IWOTH)
		(*lst_files)->right[8] = 'w';
	if ((type & S_IXOTH) == S_IXOTH)
		(*lst_files)->right[9] = 'x';
	ft_ls_more(lst_files);
	return (NULL);
}

void			ft_ls_type(t_ls_dir **lst_files)
{
	mode_t		type;
	char		*res;

	type = (*lst_files)->stat.st_mode;
	if (S_ISREG(type))
		res = ft_strdup("----------");
	else if (S_ISDIR(type))
		res = ft_strdup("d---------");
	else if (S_ISCHR(type))
		res = ft_strdup("c---------");
	else if (S_ISBLK(type))
		res = ft_strdup("b---------");
	else if (S_ISFIFO(type))
		res = ft_strdup("p---------");
	else if (S_ISLNK(type))
		res = ft_strdup("l---------");
	else if (S_ISSOCK(type))
		res = ft_strdup("s---------");
	else
		res = ft_strdup("x---------");
	(*lst_files)->right = ft_strdup(res);
	ft_ls_right(lst_files);
}

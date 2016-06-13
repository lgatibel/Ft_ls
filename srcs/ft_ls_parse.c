/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgatibel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 16:38:31 by lgatibel          #+#    #+#             */
/*   Updated: 2016/04/19 15:20:00 by lgatibel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libls.h>

static int			ft_ls_is_link(char *path, t_ls_func *ft_ls, t_stat *stats)
{
	mode_t		type;

	lstat(path, stats);
	type = stats->st_mode;
	if ((S_ISLNK(type) && (ft_ls->display == ft_ls_display_l || ft_ls->display
		== ft_ls_display_la)))
		return (0);
	return (1);
}

static int			ft_ls_error(t_ls_dir *lst_files, t_ls_func *ft_ls,
		int index)
{
	char	*error;

	if (lst_files->right[0] != 'd')
		return (0);
	if (index > 1)
		ft_putchar('\n');
	if (ft_ls->name > 1)
		ft_putendl(ft_strjoin(lst_files->name, ":"));
	error = ft_strjoin("ft_ls: ", lst_files->name);
	error = ft_strjoin(error, ": Permision denied");
	ft_putendl(error);
	return (1);
}

int					ft_ls_parse(char *path, t_ls_func *ft_ls, int index)
{
	DIR			*dirp;
	t_dirent	*file;
	t_stat		stats;
	t_ls_dir	*lst_files;

	lst_files = NULL;
	if (ft_ls_is_link(path, ft_ls, &stats) && (dirp = opendir(path)))
	{
		while ((file = readdir(dirp)))
			lst_files = ft_ls->sort(file, &lst_files, path);
		closedir(dirp);
		ft_ls->stat(path, &lst_files, ft_ls);
	}
	else
	{
		lst_files = ft_ls_set_link(path, "");
		lstat(path, &lst_files->stat);
		ft_ls_type(&lst_files);
		if (lst_files->right[1] == '-' && ft_ls_error(lst_files, ft_ls, index))
			return (0);
		ft_ls->display(&lst_files);
	}
	return (0);
}

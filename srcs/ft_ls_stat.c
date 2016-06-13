/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_stat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgatibel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 16:16:23 by lgatibel          #+#    #+#             */
/*   Updated: 2016/04/19 15:20:46 by lgatibel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libls.h>

static void		ft_ls_stat_annexe(t_ls_func *ft_ls, char *old_file, int *index)
{
	if (ft_ls->name > 1)
	{
		if (++*index == 1)
		{
			if (++ft_ls->name > 3)
				write(1, "\n", 1);
			ft_putendl(ft_strjoin(old_file, ":"));
		}
	}
}

void			ft_ls_stat(char *old_file, t_ls_dir **lst_files,
		t_ls_func *ft_ls)
{
	t_stat		stat;
	int			index;
	t_ls_dir	*tmp;

	index = 0;
	tmp = *lst_files;
	while (tmp)
	{
		tmp->total = 0;
		if (ft_ls->more_stat)
			ft_ls_type(&tmp);
		tmp->path = ft_strjoin(old_file, "/");
		if ((ft_ls->display == ft_ls_display_a || ft_ls->display ==
		ft_ls_display_la) || tmp->name[0] != '.')
			(*lst_files)->total += tmp->block;
		if (!lstat(ft_strjoin(old_file, "/"), &stat) && ft_ls->name > 1)
			ft_ls_stat_annexe(ft_ls, old_file, &index);
		tmp = tmp->next;
	}
	ft_ls->display(lst_files);
}

static void		ft_ls_stat_recursive_annexe(t_ls_dir *tmp, char *old_file,
		t_ls_func *ft_ls)
{
	while (tmp)
	{
		if (tmp->right[0] == 'd' && ft_ls_verif_path(ft_strjoin(
						tmp->name, "/")))
		{
			ft_ls->name += 1;
			ft_ls_parse(ft_strjoin(ft_strjoin(old_file, "/"), tmp->name),
					ft_ls, 0);
		}
		tmp = tmp->next;
	}
}

void			ft_ls_stat_recursive(char *old_file, t_ls_dir **lst_files,
		t_ls_func *ft_ls)
{
	t_ls_dir	*tmp;
	int			index;

	index = 0;
	tmp = *lst_files;
	while (tmp)
	{
		tmp->total = 0;
		if (ft_ls->more_stat)
			ft_ls_type(&tmp);
		tmp->path = ft_strjoin(old_file, "/");
		if ((ft_ls->display == ft_ls_display_a || ft_ls->display ==
		ft_ls_display_la) || tmp->name[0] != '.')
			(*lst_files)->total += tmp->block;
		tmp = tmp->next;
	}
	if (((ft_ls->display != ft_ls_display_a && ft_ls->display !=
		ft_ls_display_la) && (!ft_strstr(old_file, "/."))) ||
		(ft_ls->display == ft_ls_display_a) || (ft_ls->display ==
			ft_ls_display_la))
	{
		ft_ls_stat_annexe(ft_ls, old_file, &index);
		ft_ls->display(lst_files);
		ft_ls_stat_recursive_annexe(*lst_files, old_file, ft_ls);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgatibel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 14:43:34 by lgatibel          #+#    #+#             */
/*   Updated: 2016/04/19 15:26:53 by lgatibel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libls.h>

static void		ft_ls_set_padding_annexe2(t_ls_dir **lst_files)
{
	t_ls_dir	*tmp;
	int			link;

	tmp = *lst_files;
	link = ((*lst_files)->maxlink + 1 - (ft_strlen(tmp->link)));
	tmp->link = ft_strjoin(ft_strndupchr(' ', link), tmp->link);
	tmp->usr = ft_strjoin(tmp->usr,
		ft_strndupchr(' ', (*lst_files)->maxusr - ft_strlen(tmp->usr) + 2));
	tmp->grp = ft_strjoin(tmp->grp,
		ft_strndupchr(' ', (*lst_files)->maxgrp - ft_strlen(tmp->grp) + 2));
	tmp->size = ft_strjoin(
		ft_strndupchr(' ', (*lst_files)->maxsize - ft_strlen(tmp->size) + 1),
			tmp->size);
}

static void		ft_ls_set_padding_annexe(t_ls_dir **lst_files)
{
	t_ls_dir	*tmp;
	int			index;

	index = 0;
	tmp = *lst_files;
	(*lst_files)->maxlink += 2;
	while (tmp)
	{
		if (++index == 1)
			ft_ls_set_padding_annexe2(&tmp);
		else
		{
			tmp->link = ft_strjoin(ft_strndupchr(' ',
				(*lst_files)->maxlink - tmp->maxlink), tmp->link);
			tmp->usr = ft_strjoin(tmp->usr,
					ft_strndupchr(' ', (*lst_files)->maxusr - tmp->maxusr + 2));
			tmp->grp = ft_strjoin(tmp->grp,
					ft_strndupchr(' ', (*lst_files)->maxgrp - tmp->maxgrp + 2));
			tmp->size = ft_strjoin(
					ft_strndupchr(' ', (*lst_files)->maxsize - tmp->maxsize),
					tmp->size);
		}
		tmp = tmp->next;
	}
}

int				ft_ls_set_padding(t_ls_dir **lst_files)
{
	t_ls_dir	*tmp;
	int			total;

	total = 0;
	tmp = *lst_files;
	while (tmp)
	{
		if ((*lst_files)->maxlink < tmp->maxlink)
			(*lst_files)->maxlink = tmp->maxlink;
		if ((*lst_files)->maxusr < tmp->maxusr)
			(*lst_files)->maxusr = tmp->maxusr;
		if ((*lst_files)->maxgrp < tmp->maxgrp)
			(*lst_files)->maxgrp = tmp->maxgrp;
		if ((*lst_files)->maxsize < tmp->maxsize)
			(*lst_files)->maxsize = tmp->maxsize;
		total += (*lst_files)->block;
		tmp = tmp->next;
	}
	ft_ls_set_padding_annexe(lst_files);
	return (total);
}

t_ls_func		ft_ls_set_function(char *option, t_ls_func *ft_ls)
{
	if (!option)
		return (*ft_ls);
	if (ft_strchr(option, 'a'))
		ft_ls->display = &ft_ls_display_a;
	if (ft_strchr(option, 't'))
		ft_ls->sort = &ft_ls_sort_time;
	if (ft_strchr(option, (int)'l') && ++ft_ls->more_stat > 0)
	{
		ft_ls->display = &ft_ls_display_l;
		if (ft_strchr(option, 'a'))
			ft_ls->display = &ft_ls_display_la;
	}
	if (ft_strchr(option, 'r'))
	{
		ft_ls->sort = &ft_ls_sort_reverse;
		if (ft_strchr(option, 't'))
			ft_ls->sort = &ft_ls_sort_time_reverse;
		ft_ls->args = &ft_ls_sort_args_reverse;
	}
	if (ft_strchr(option, 'R') && ++ft_ls->more_stat > 0)
		ft_ls->stat = &ft_ls_stat_recursive;
	return (*ft_ls);
}

void			ft_ls_set(t_ls_func *ft_ls)
{
	ft_ls->sort = &ft_ls_sort;
	ft_ls->args = &ft_ls_sort_args;
	ft_ls->display = &ft_ls_display;
	ft_ls->more_stat = 0;
	ft_ls->stat = &ft_ls_stat;
	ft_ls->name = 0;
}

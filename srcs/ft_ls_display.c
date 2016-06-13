/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgatibel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 13:14:09 by lgatibel          #+#    #+#             */
/*   Updated: 2016/04/19 15:09:01 by lgatibel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libls.h>

static void		ft_display_total(t_ls_dir *lst_files)
{
	if (!ft_strlen(lst_files->path))
		return ;
	if (!strcmp(lst_files->path, lst_files->name))
		return ;
	write(1, "total ", 6);
	ft_putnbr(lst_files->total);
	write(1, "\n", 1);
}

static void		ft_ls_display_link(t_ls_dir *tmp, char *display)
{
	char	buff[BUFF_SIZE_LS + 1];
	int		i;

	i = 0;
	ft_putstr(display);
	if (tmp->right[0] == 'l')
	{
		ft_putstr(tmp->name);
		if ((i = readlink(ft_strjoin(tmp->path, tmp->name), buff, 1024)) == -1)
			i = readlink(tmp->name, buff, BUFF_SIZE_LS);
		buff[i] = '\0';
		ft_putendl(ft_strjoin(" -> ", buff));
	}
	else
		ft_putendl(tmp->name);
}

void			ft_ls_display_la(t_ls_dir **lst_files)
{
	t_ls_dir	*tmp;
	char		*display;
	int			index;

	index = 0;
	tmp = *lst_files;
	ft_ls_set_padding(lst_files);
	while (tmp)
	{
		if (++index == 1)
			ft_display_total(*lst_files);
		display = ft_strjoin(tmp->right, tmp->link);
		display = ft_strjoin(display, tmp->usr);
		display = ft_strjoin(display, tmp->grp);
		display = ft_strjoin(display, tmp->size);
		display = ft_strjoin(display, tmp->hour);
		ft_ls_display_link(tmp, display);
		tmp = tmp->next;
	}
}

void			ft_ls_display_error(char *name)
{
	char	*error;

	error = ft_strjoin("ft_ls: ", name);
	error = ft_strjoin(error, " : permision denied");
	ft_putendl(error);
}

void			ft_ls_display_l(t_ls_dir **lst_files)
{
	t_ls_dir	*tmp;
	char		*display;
	int			index;

	index = 0;
	tmp = *lst_files;
	ft_ls_set_padding(lst_files);
	while (tmp)
	{
		if ((tmp->name[0] != '.' || !ft_strlen(tmp->path)) && tmp->right[0]
				!= 'x')
		{
			if (++index == 1)
				ft_display_total(*lst_files);
			display = ft_strjoin(tmp->right, tmp->link);
			display = ft_strjoin(display, tmp->usr);
			display = ft_strjoin(display, tmp->grp);
			display = ft_strjoin(display, tmp->size);
			display = ft_strjoin(display, tmp->hour);
			ft_ls_display_link(tmp, display);
		}
		else if (tmp->name[0] != '.')
			ft_ls_display_error(tmp->name);
		tmp = tmp->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_display_annexe.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgatibel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 14:59:08 by lgatibel          #+#    #+#             */
/*   Updated: 2016/04/19 15:04:46 by lgatibel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libls.h>

void			ft_ls_display(t_ls_dir **lst_files)
{
	t_ls_dir *tmp;

	tmp = *lst_files;
	while (tmp)
	{
		if (tmp->name[0] != '.' || !ft_strlen(tmp->path))
			ft_putendl(tmp->name);
		tmp = tmp->next;
	}
}

void			ft_ls_display_a(t_ls_dir **lst_files)
{
	t_ls_dir	*tmp;

	tmp = *lst_files;
	while (tmp)
	{
		ft_putendl(tmp->name);
		tmp = tmp->next;
	}
}

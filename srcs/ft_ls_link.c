/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_link.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgatibel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 16:07:12 by lgatibel          #+#    #+#             */
/*   Updated: 2016/04/16 15:57:03 by lgatibel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libls.h>

static void			ft_ls_link_stat(const char *file, t_ls_dir **new_link,
char *path)
{
	char	*path_file;

	path_file = ft_strjoin(path, "/");
	path_file = ft_strjoin(path_file, file);
	if (!lstat(path_file, &(*new_link)->stat))
		return ;
	path_file = ft_strjoin(path_file, "/");
	lstat(path_file, &(*new_link)->stat);
}

t_ls_dir			*ft_ls_set_link(const char *file_name, char *path)
{
	t_ls_dir *new_link;

	new_link = (t_ls_dir *)malloc(sizeof(t_ls_dir));
	new_link->next = NULL;
	new_link->name = ft_strdup(file_name);
	new_link->path = ft_strdup(path);
	new_link->deep = NULL;
	ft_ls_link_stat(file_name, &new_link, path);
	return (new_link);
}

t_ls_args			*ft_ls_set_link_args(const char *path)
{
	t_ls_args *new_link;

	new_link = (t_ls_args *)malloc(sizeof(t_ls_args));
	new_link->next = NULL;
	new_link->path = ft_strdup(path);
	return (new_link);
}

t_ls_dir			*ft_ls_place_link(t_ls_dir *first, t_ls_dir *second,
int choice)
{
	if (choice == 1)
	{
		first->next = second;
	}
	return (first);
}

t_ls_args			*ft_ls_place_link_args(t_ls_args *first, t_ls_args *second,
int choice)
{
	if (choice == 1)
	{
		first->next = second;
	}
	return (first);
}

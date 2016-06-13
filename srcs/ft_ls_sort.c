/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgatibel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 13:51:29 by lgatibel          #+#    #+#             */
/*   Updated: 2016/04/08 16:37:02 by lgatibel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libls.h>

t_ls_dir		*ft_ls_sort_reverse(t_dirent *file, t_ls_dir **lst_files,
		char *path)
{
	t_ls_dir		*current;
	t_ls_dir		*previous;
	t_ls_dir		*new_link;

	current = *lst_files;
	previous = *lst_files;
	new_link = ft_ls_set_link(file->d_name, path);
	if (*lst_files == NULL)
		return (new_link);
	if (*lst_files)
		while (current && (ft_strcmp(file->d_name, current->name) < 0))
		{
			previous = current;
			current = current->next;
		}
	if (previous != current)
		previous->next = ft_ls_place_link(new_link, current, 1);
	else
		*lst_files = ft_ls_place_link(new_link, previous, 1);
	return (*lst_files);
}

t_ls_dir		*ft_ls_sort(t_dirent *file, t_ls_dir **lst_files, char *path)
{
	t_ls_dir		*current;
	t_ls_dir		*previous;
	t_ls_dir		*new_link;

	current = *lst_files;
	previous = *lst_files;
	new_link = ft_ls_set_link(file->d_name, path);
	if (*lst_files == NULL)
		return (new_link);
	if (*lst_files)
		while (current && (ft_strcmp(file->d_name, current->name) > 0))
		{
			previous = current;
			current = current->next;
		}
	if (previous != current)
		previous->next = ft_ls_place_link(new_link, current, 1);
	else
		*lst_files = ft_ls_place_link(new_link, previous, 1);
	return (*lst_files);
}

static int		ft_ls_time_verif(t_ls_dir **new_link, t_ls_dir **current,
		int choice)
{
	if ((*new_link)->stat.st_mtimespec.tv_sec ==
			(*current)->stat.st_mtimespec.tv_sec && choice == 0)
	{
		if ((*new_link)->stat.st_mtimespec.tv_nsec >
				(*current)->stat.st_mtimespec.tv_nsec)
			return (1);
		if ((*new_link)->stat.st_mtimespec.tv_nsec ==
				(*current)->stat.st_mtimespec.tv_nsec)
			if ((ft_strcmp((*new_link)->name, (*current)->name)) < 0)
				return (1);
	}
	else if ((*new_link)->stat.st_mtimespec.tv_sec ==
			(*current)->stat.st_mtimespec.tv_sec && choice == 1)
	{
		if ((*new_link)->stat.st_mtimespec.tv_nsec <
				(*current)->stat.st_mtimespec.tv_nsec)
			return (1);
		if ((*new_link)->stat.st_mtimespec.tv_nsec ==
				(*current)->stat.st_mtimespec.tv_nsec)
			if ((ft_strcmp((*new_link)->name, (*current)->name)) > 0)
				return (1);
	}
	return (0);
}

t_ls_dir		*ft_ls_sort_time(t_dirent *file, t_ls_dir **lst_files,
		char *path)
{
	t_ls_dir		*current;
	t_ls_dir		*previous;
	t_ls_dir		*new_link;

	current = *lst_files;
	previous = *lst_files;
	new_link = ft_ls_set_link(file->d_name, path);
	if (*lst_files == NULL)
		return (new_link);
	while (current && ((new_link->stat.st_mtimespec.tv_sec) <=
				(current->stat.st_mtimespec.tv_sec)))
	{
		if (ft_ls_time_verif(&new_link, &current, 0))
			break ;
		previous = current;
		current = current->next;
	}
	if (previous != current)
		previous->next = ft_ls_place_link(new_link, current, 1);
	else
		*lst_files = ft_ls_place_link(new_link, previous, 1);
	return (*lst_files);
}

t_ls_dir		*ft_ls_sort_time_reverse(t_dirent *file, t_ls_dir **lst_files,
		char *path)
{
	t_ls_dir		*current;
	t_ls_dir		*previous;
	t_ls_dir		*new_link;

	current = *lst_files;
	previous = *lst_files;
	new_link = ft_ls_set_link(file->d_name, path);
	if (*lst_files == NULL)
		return (new_link);
	while (current && ((new_link->stat.st_mtimespec.tv_sec) >=
				(current->stat.st_mtimespec.tv_sec)))
	{
		if (ft_ls_time_verif(&new_link, &current, 1))
			break ;
		previous = current;
		current = current->next;
	}
	if (previous != current)
		previous->next = ft_ls_place_link(new_link, current, 1);
	else
		*lst_files = ft_ls_place_link(new_link, previous, 1);
	return (*lst_files);
}

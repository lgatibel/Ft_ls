/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_sort_annexe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgatibel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 11:54:40 by lgatibel          #+#    #+#             */
/*   Updated: 2016/04/19 13:54:45 by lgatibel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libls.h>

static t_ls_args	*ft_is_sort(t_ls_args *args, t_ls_args **previous,
		t_ls_args **tmp)
{
	while (args && args->right[0] != 'd')
	{
		*previous = args;
		args = args->next;
	}
	while (args && args->right[0] == 'd')
	{
		*tmp = *previous;
		*previous = args;
		args = args->next;
	}
	return (args);
}

t_ls_args			*ft_ls_sort_directory(t_ls_args **lst_args)
{
	t_ls_args	*current;
	t_ls_args	*previous;
	t_ls_args	*tmp;

	current = *lst_args;
	previous = *lst_args;
	tmp = NULL;
	while ((current = ft_is_sort(*lst_args, &previous, &tmp)))
	{
		if (previous == *lst_args)
		{
			previous->next = current->next;
			current->next = previous;
			return (current);
		}
		else
		{
			tmp->next = current;
			previous->next = current->next;
			current->next = previous;
		}
	}
	return (*lst_args);
}

t_ls_args			*ft_ls_sort_args(char *path, t_ls_args **lst_args)
{
	t_ls_args		*current;
	t_ls_args		*previous;
	t_ls_args		*new_link;

	(void)stat;
	current = *lst_args;
	previous = *lst_args;
	new_link = ft_ls_set_link_args(path);
	if (*lst_args == NULL)
		return (new_link);
	if (*lst_args)
	{
		while (current && (ft_strcmp(path, current->path) > 0))
		{
			previous = current;
			current = current->next;
		}
	}
	if (previous != current)
		previous->next = ft_ls_place_link_args(new_link, current, 1);
	else
		*lst_args = ft_ls_place_link_args(new_link, previous, 1);
	return (*lst_args);
}

t_ls_args			*ft_ls_sort_args_reverse(char *path, t_ls_args **lst_args)
{
	t_ls_args		*current;
	t_ls_args		*previous;
	t_ls_args		*new_link;

	current = *lst_args;
	previous = *lst_args;
	new_link = ft_ls_set_link_args(path);
	if (*lst_args == NULL)
		return (new_link);
	if (*lst_args)
		while (current && (ft_strcmp(path, current->path) < 0))
		{
			previous = current;
			current = current->next;
		}
	if (previous != current)
		previous->next = ft_ls_place_link_args(new_link, current, 1);
	else
		*lst_args = ft_ls_place_link_args(new_link, previous, 1);
	return (*lst_args);
}

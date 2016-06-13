/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgatibel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 15:14:10 by lgatibel          #+#    #+#             */
/*   Updated: 2016/04/19 15:26:58 by lgatibel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libls.h>

void			ft_ls_type_args(t_ls_args **args)
{
	mode_t		type;
	char		*res;

	type = (*args)->stat.st_mode;
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
		res = ft_strdup("X---------");
	(*args)->right = ft_strdup(res);
}

t_ls_args		*ft_ls_set_args(char **av, int cpt, int ac, t_ls_func *ft_ls)
{
	t_ls_args		*lst_args;
	char			**path;

	lst_args = NULL;
	path = NULL;
	if (cpt >= 1)
		while (cpt < ac)
		{
			lst_args = ft_ls->args(av[cpt], &lst_args);
			cpt++;
		}
	else
		lst_args = ft_ls->args(".", &lst_args);
	return (lst_args);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_verif.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgatibel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 16:18:53 by lgatibel          #+#    #+#             */
/*   Updated: 2016/04/19 15:36:58 by lgatibel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libls.h>

int				ft_ls_verif_path(const char *current_path)
{
	if (ft_strnstr(current_path, "../", 3) || ft_strnstr(current_path, "./", 2))
	{
		if (ft_strstr(&current_path[2], "../") ||
				ft_strstr(&current_path[2], "./"))
			return (0);
	}
	else
	{
		if (ft_strstr(current_path, "../") || ft_strstr(current_path, "./"))
			return (0);
	}
	return (1);
}

static int		ft_ls_verif_option_true(const char *av)
{
	int		i;
	int		cpt;
	char	tab[5];

	i = -1;
	cpt = 0;
	tab[0] = 'l';
	tab[1] = 'r';
	tab[2] = 'a';
	tab[3] = 'R';
	tab[4] = 't';
	while (av[++i])
	{
		while (tab[cpt] && tab[cpt] != av[i])
			++cpt;
		if (!tab[cpt])
		{
			if (ft_strlen(av) == 1 && av[i] == '-')
				return (-1);
			return ((char)av[i]);
		}
		cpt = 0;
	}
	return (0);
}

int				ft_ls_illegal(int index, t_ls_func *ft_ls)
{
	if (index == -1)
		return (1);
	ft_ls->ok = -1;
	ft_putstr("ft_ls: illegal option -- ");
	ft_putchar(index);
	ft_putstr("\nusage: ft_ls [-Ralrt] [file ...]\n");
	exit(2);
	return (0);
}

int				ft_ls_verif_param(char **av, int ac, t_ls_func *ft_ls)
{
	int		index;
	int		i;
	char	*options;

	i = 0;
	ft_ls_set(ft_ls);
	index = 0;
	options = "";
	while (++i < ac && av[i][0] == '-' && ft_strlen(av[i]) > 1)
	{
		if (!(index = ft_ls_verif_option_true(&av[i][1])))
			options = ft_strjoin(options, &av[i][1]);
		else
		{
			if (index == -1 && ft_ls_illegal(index, ft_ls))
				break ;
		}
	}
	*ft_ls = ft_ls_set_function(options, ft_ls);
	if (index == -1)
		i -= -1;
	if (i < (ac))
		return (ac - i);
	return (i);
}

void			ft_ls_verif_args(t_ls_args **args, t_ls_func *ft_ls)
{
	t_ls_args	*tmp;
	int			error;

	error = 0;
	tmp = *args;
	while (tmp)
	{
		if (lstat(tmp->path, &tmp->stat))
		{
			perror(ft_strjoin("./ft_ls: ", tmp->path));
			++error;
			tmp->ok = -1;
		}
		else
		{
			ft_ls->name += 1;
			tmp->ok = 0;
		}
		ft_ls_type_args(&tmp);
		tmp = tmp->next;
	}
	if (error)
		ft_ls->name = 2;
	*args = ft_ls_sort_directory(args);
}

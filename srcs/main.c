/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgatibel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 16:58:32 by lgatibel          #+#    #+#             */
/*   Updated: 2016/04/19 10:28:51 by lgatibel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libls.h>

int				main(int ac, char **av)
{
	t_ls_args		*args;
	t_ls_func		ft_ls;
	int				cpt;
	int				index;

	ft_ls.ok = 0;
	index = 0;
	cpt = ft_ls_verif_param(av, ac, &ft_ls);
	cpt = ((ac - cpt) >= 1) ? (ac - cpt) : -1;
	args = ft_ls_set_args(av, cpt, ac, &ft_ls);
	ft_ls_verif_args(&args, &ft_ls);
	while (args)
	{
		if (!args->ok && ++index)
			ft_ls_parse(args->path, &ft_ls, index);
		args = args->next;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebarguil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 18:00:11 by ebarguil          #+#    #+#             */
/*   Updated: 2021/12/20 10:17:23 by ebarguil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static int	path_check_exe1(t_pip *p)
{
	char	*tmp;

	p->cmd1 = ft_strjoin_lib(p->pth[p->i], p->exe1[0]);
	if (p->cmd1 == NULL)
		return (1);
	if (!access(p->cmd1, F_OK) && !access(p->cmd1, X_OK))
	{
		free(p->cmd1);
		tmp = p->exe1[0];
		p->exe1[0] = ft_strjoin_lib(p->pth[p->i], tmp);
		free(tmp);
		return (0);
	}
	free(p->cmd1);
	return (-1);
}

static int	path_check_exe2(t_pip *p)
{
	char	*tmp;

	p->cmd2 = ft_strjoin_lib(p->pth[p->i], p->exe2[0]);
	if (p->cmd2 == NULL)
		return (1);
	if (!access(p->cmd2, F_OK) && !access(p->cmd2, X_OK))
	{
		free(p->cmd2);
		tmp = p->exe2[0];
		p->exe2[0] = ft_strjoin_lib(p->pth[p->i], tmp);
		free(tmp);
		return (0);
	}
	free(p->cmd2);
	return (-1);
}

int	ft_get_path_cmd(t_pip *p)
{
	int	x;

	p->exe1 = ft_split(p->av[2], " ");
	p->exe2 = ft_split(p->av[3], " ");
	if (p->exe1 == NULL || p->exe2 == NULL)
		return (1);
	p->i = -1;
	x = -1;
	while (p->pth[++p->i] && x == -1)
		x = path_check_exe1(&*p);
	if (x == 1 || x == -1)
		return (1);
	p->i = -1;
	x = -1;
	while (p->pth[++p->i] && x == -1)
		x = path_check_exe2(&*p);
	if (x == 1 || x == -1)
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebarguil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 17:06:24 by ebarguil          #+#    #+#             */
/*   Updated: 2021/12/18 21:49:41 by ebarguil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_free(t_pip *p, int x)
{
	int	i;

	i = -1;
	while (p->pth[++i])
		free(p->pth[i]);
	free(p->pth);
	i = -1;
	if (p->exe1)
	{
		while (p->exe1[++i])
			free(p->exe1[i]);
		free(p->exe1);
	}
	i = -1;
	if (p->exe2)
	{
		while (p->exe2[++i])
			free(p->exe2[i]);
		free(p->exe2);
	}
	return (x);
}

void	ft_child2(t_pip *p)
{
	if (access(p->av[4], F_OK) != 0
		|| (access(p->av[4], R_OK | W_OK) != 0 && !unlink(p->av[4])))
		p->fdo[1] = open(p->av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	else
		p->fdo[1] = open(p->av[4], O_RDWR | O_TRUNC);
	dup2(p->end[0], 0);
	dup2(p->fdo[1], 1);
	close(p->fdo[1]);
	close(p->end[1]);
	close(p->end[0]);
	execve(p->exe2[0], p->exe2, p->ev);
}

int	ft_fork_cmd(t_pip *p)
{
	p->pid[0] = fork();
	if (p->pid[0] < 0)
		return (1);
	if (p->pid[0] == 0)
	{
		p->fdo[0] = open(p->av[1], O_RDONLY);
		dup2(p->fdo[0], 0);
		dup2(p->end[1], 1);
		close(p->fdo[0]);
		close(p->end[0]);
		close(p->end[1]);
		execve(p->exe1[0], p->exe1, p->ev);
	}
	p->pid[1] = fork();
	if (p->pid[1] < 0)
		return (1);
	if (p->pid[1] == 0)
		ft_child2(&*p);
	close(p->end[0]);
	close(p->end[1]);
	waitpid(p->pid[0], NULL, 0);
	waitpid(p->pid[1], NULL, 0);
	return (0);
}

int	main(int ac, char **av, char **ev)
{
	t_pip	p;

	p.av = av;
	p.ev = ev;
	if (ac != 5 || (access(av[1], F_OK) || access(av[1], R_OK | W_OK)))
		return (1);
	p.i = -1;
	while (ev[++p.i])
		if (ev[p.i][0] == 'P' && ev[p.i][1] == 'A' && ev[p.i][2] == 'T'
			&& ev[p.i][3] == 'H' && ev[p.i][4] == '=')
			p.pth = ft_split_add(&ev[p.i][5], ":");
	if (p.pth == NULL)
		return (1);
	if (ft_get_path_cmd(&p) || pipe(p.end) == -1 || ft_fork_cmd(&p))
		return (ft_free(&p, 1));
	return (ft_free(&p, 0));
}

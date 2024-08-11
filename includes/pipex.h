/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dani <dani@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:41:39 by dani              #+#    #+#             */
/*   Updated: 2024/08/11 18:48:07 by dani             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include "../libft/libft.h"

//main
void		exec(char *cmd, char **env);
void		child(char **av, int *p_fd, char **env);
void		parent(char **av, int *p_fd, char **env);

//utils
void		exit_handler(int n_exit);
int			open_file(char *file, int in_or_out);
void		ft_free_tab(char **tab);
char		*my_getenv(char *name, char **env);
char		*get_path(char *cmd, char **env);

#endif

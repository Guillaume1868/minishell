/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:42:38 by gaubert           #+#    #+#             */
/*   Updated: 2022/03/21 14:36:12 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

int		ft_cd(char *args, char **envp);
int		ft_help(void);
void	ft_exit(void);
void	ft_env(char	**envp);
char	**check_builtin(char *cmd, char *args, char **envp);
int		check_builtin_forked(char *cmd, char *args, char **envp);

#endif
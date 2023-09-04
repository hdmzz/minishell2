/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_sh.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:13:41 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/04 12:13:42 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_SH_H
#define SIGNALSH_H

# include <signal.h>
# include "../libft/libft.h"
# include <readline/readline.h>

void	signal_reset_prompt(int signo);
void	set_signals_interactive(void);
void	signal_print_newline(int signal);
void	set_signals_noninteractive(void);
void	ignore_sigquit(void);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchan <vchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 17:58:18 by lseiller          #+#    #+#             */
/*   Updated: 2022/07/23 17:41:06 by vchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# define _END "\e[0m"
# define _RED "\e[31m"
# define _GREY "\e[30m"
# define _YELLOW "\e[33m"
# define _GREEN "\e[32m"
# define SYSCALLFAIL -1

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

# define EAT_MSG _GREEN "is eating 🍝"_END
# define FORK_MSG _YELLOW "has taken a fork 🍴" _END

typedef struct s_param_philo
{
	int				nb_philo;
	unsigned long	tt_die;
	unsigned long	tt_eat;
	unsigned long	tt_sleep;
	int				rounds;
	pthread_t		alive;
	pthread_mutex_t	*mutex_fork;
	pthread_mutex_t	*mutex_state;
	unsigned long	start_t;
	unsigned long	end_t;
	bool			*fork_state;
	// bool			is_over;
	// unsigned long	time_to_think;
	pthread_mutex_t	*mutex_print;
}	t_param_philo;

typedef struct s_philo
{
	int				id;
	int				state;
	unsigned long	start_t;
	unsigned long	end_t;
	pthread_t		thread_id;
	t_param_philo	*data;
}	t_philo;

void	*ft_calloc(size_t nmemb, size_t size);

/**************************************************************************** */
/*								TIME										  */
/**************************************************************************** */
unsigned long	get_time(t_philo *data);
unsigned long	diff_time(t_philo *data);

/**************************************************************************** */
/*								INIT										  */
/**************************************************************************** */

void	init_tab_philo(t_philo *tab_philo, t_param_philo *data);
void	init_mutex(t_param_philo *data);
void	init_data(t_param_philo *data);
void	lock_state(t_philo *philos, int i);
void	unlock_state(t_philo *philos, int i);
void	change_state(t_philo *philos, int i);
void	lock_fork(t_philo *philos, int i);
void	unlock_fork(t_philo *philos, int i);

#endif

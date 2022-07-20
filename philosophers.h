/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchan <vchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 17:58:18 by lseiller          #+#    #+#             */
/*   Updated: 2022/07/19 17:12:25 by vchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# define _END "\e[0m"
# define _RED "\e[31m"
# define _GREY "\e[30m"
# define SYSCALLFAIL -1

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_param_philo
{
	int				nb_of_philo;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				nb_round;
	pthread_t		is_alive;
	// t_fork			*mutex_fork;
	pthread_mutex_t	*mutex_fork;
	unsigned long	start_time;
	unsigned long	end_time;
	bool			is_it_over;
	// unsigned long	time_to_think;
	// pthread_mutex_t	*mutex_print;
}	t_param_philo;

// typedef struct s_fork
// {
// 	pthread_mutex_t	fork;
// 	int				is_taken;
// }	t_fork;

typedef struct s_philo
{
	int				philo_id;
	int				fork;
	int				state;
	unsigned long	start_time;
	unsigned long	end_time;
	pthread_t		threads_id;
	t_param_philo	*param_philo;
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

#endif

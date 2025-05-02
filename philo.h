/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhssi <nbenhssi@student.1337.ma>        #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-19 18:16:39 by nbenhssi          #+#    #+#             */
/*   Updated: 2025-04-19 18:16:39 by nbenhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>


// typedef struct data {
// 	int nb_ph;
//     int ttd;
//     int tte;
//     int tts;
// 	int flag;
//     int n_o_t_e_ph_m_e;
// 	pthread_mutex_t *forks;
// 	pthread_mutex_t *write;
// 	pthread_mutex_t *meal;
// }data;

// typedef struct philo {
// //start of eat
// 	int *thread_id;
// 	int meal_count;
// 	//pthread_t *thr;
// 	pthread_mutex_t l_fork;
// 	pthread_mutex_t r_fork;
// }philo;

typedef struct s_data t_data;

typedef struct s_philo
{
	int             id;
	int             meal_count;
	long long       last_meal;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	t_data          *data;
} t_philo;

typedef struct s_data
{
	int             nb_ph;
	int             ttd;
	int             tte;
	int             tts;
	int             n_o_t_e_ph_m_e;
	int             stop;
	long long       start_time;
	t_philo         *philos;
	pthread_t       *thread;
	pthread_mutex_t *forks;
	pthread_mutex_t print_mutex;
} t_data;



int	ft_atoi(char *nptr);
int init_philo(t_data *data);
int init_data(t_data *a, char **argv, int argc);

#endif
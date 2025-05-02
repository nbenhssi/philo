/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhssi <nbenhssi@student.1337.ma>        #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-02 08:44:43 by nbenhssi          #+#    #+#             */
/*   Updated: 2025-05-02 08:44:43 by nbenhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int init_philo(t_data *data)
{
	int i = 0;
    while (i < data->nb_ph)
    {
        data->philos[i].id = i;
		data->philos[i].meal_count = 0;
		data->philos[i].last_meal = data->start_time;
		data->philos[i].data = data;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->nb_ph];
		i++;
    }
    return (0);
}

int init_data(t_data *a, char **argv, int argc)
{
    if (argc == 5 || argc == 6)
    {
        a->nb_ph = ft_atoi(argv[1]);
        a->ttd  = ft_atoi(argv[2]);
        a->tte =  ft_atoi(argv[3]);
        a->tts = ft_atoi(argv[4]);
    }
    if (argc == 6)
    	a->n_o_t_e_ph_m_e = ft_atoi(argv[5]);
    a->stop = 0;
	//a->start_time = get_time_ms();
	a->philos = malloc(sizeof(t_philo) * a->nb_ph);
	a->forks = malloc(sizeof(pthread_mutex_t) * a->nb_ph);
	if (!a->philos || !a->forks)
		return (1);
    return (0);
}

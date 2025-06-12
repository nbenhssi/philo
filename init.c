#include "philo.h"

int init_data(t_data *a, char **argv, int argc)
{
    a->nb_ph = ft_atoi(argv[1]);
    a->ttd  = ft_atoi(argv[2]);
    a->tte =  ft_atoi(argv[3]);
    a->tts = ft_atoi(argv[4]);
    a->n_o_t_e_ph_m_e = -1;
    if (argc == 6)
    	a->n_o_t_e_ph_m_e = ft_atoi(argv[5]);
    a->stop = 0;
	a->start_time = get_time_ms();//
	a->philos = malloc(sizeof(t_philo) * a->nb_ph);
	a->forks = malloc(sizeof(pthread_mutex_t) * a->nb_ph);
    a->threads = malloc(sizeof(pthread_t) * a->nb_ph);
    
    if (!a->philos || !a->forks || !a->threads)
        return (1);
    return (0);
}


int init_mutex(t_data *a)
{
    int i;
    i = 0;
    if (pthread_mutex_init(&a->print_mutex, NULL) != 0)
        return (1);
    if (pthread_mutex_init(&a->philos->mael_count, NULL) != 0)
        return (1);
    if (pthread_mutex_init(&a->philos->mael, NULL) != 0)
        return (1);
    while (i < a->nb_ph)
    {
        if (pthread_mutex_init(&a->forks[i], NULL) != 0)
            return (1);
        i++;
    }
    return(0);
}


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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhssi <nbenhssi@student.1337.ma>        #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-19 18:16:30 by nbenhssi          #+#    #+#             */
/*   Updated: 2025-04-19 18:16:30 by nbenhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *thread_function(void *p)
{
    static int j;
	t_data *l;
	int i;
	l = (t_data *)p;
    //routine
    i = 0;
    while(l)
    {
        if (l->nb_ph%2 == 0)
        {
            pthread_mutex_lock(&l->forks[i]);
            //pthread_mutex_lock(l->meal);
            pthread_mutex_lock(&l->forks[i+1]);
        }
        i++;
    }
    printf("Hii im thread nbr %d\n", j);
    j++;
    return(NULL);
}

void create_mutex(t_data *a)
{
    int i;
    pthread_mutex_t	mutex[a->nb_ph];
    i = 0;
    while (i < a->nb_ph)
    {
        pthread_mutex_init(&mutex[i], NULL);
        i++;
    }
}

int create_philo(t_data *a)
{
    int i = 0;
    while (i < a->nb_ph)
    {
       // a->philos = malloc(sizeof(int));
        *(a->philos->id) = i++;
        if (pthread_create(&a->thread[i], NULL, thread_function, (void*)a) != 0)
        {
            perror("pthread_create failed");
            //free(a->philos->id[i]);
            return 1;
        }
        i++;
    }
    i = 0;
    while (i < a->nb_ph)
    {
        pthread_join(a->thread[i], NULL);
        i++;
    }
    return (0);
}

int main(int argc, char **argv)
{
    t_data a;


    if (argc != 5 && argc != 6)
    {
        printf("nbr of arg not valid");
        return (0);
    }
	init_data(&a, argv, argc);
	create_mutex(&a);
	init_philo(&a);
	create_philo(&a);
    //free();
}

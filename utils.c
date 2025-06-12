#include "philo.h"


long long get_time_ms(void)
{
    struct timeval tv;
    
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void print_status(t_data *data, int id, char *status)
{
    pthread_mutex_lock(&data->print_mutex);
    if (data->stop == 1)
    {
        pthread_mutex_unlock(&data->print_mutex);
        return;
    }
    printf("%lld ", get_time_ms() - data->start_time);
    printf("Philosopher %d %s\n", id + 1, status);
    pthread_mutex_unlock(&data->print_mutex);
}

void smart_sleep(long long duration, t_data *data)
{
    // long long start;
    // (void)data;

    long start = get_time_ms();
    while (!data->stop)
    {
        if (get_time_ms() - start >= duration)
            break;
        usleep(200);
    }
    //     usleep(500);
    // while (!data->stop && get_time_ms() - start < duration)
    //     usleep(500);
    // start = get_time_ms();
    // while (1)
    // {
    //     if (get_time_ms() - start >= duration)
    //         break;
    //     usleep(100);
    // }
}

void free_data(t_data *data)
{
    int i;

    i = 0;
    while (i < data->nb_ph)
    {
        pthread_mutex_destroy(&data->forks[i]);
        i++;
    }
    pthread_mutex_destroy(&data->print_mutex);
    free(data->philos);
    free(data->forks);
    free(data->threads);
}

void ft_usleep(long ms, t_data *data)
{
    long start;
    long sleep_interval;
    int should_continue;

    start = get_time_ms();
    if (data->nb_ph > 100)
        sleep_interval = 500;
    else if (data->nb_ph > 50)
        sleep_interval = 100;
    else
        sleep_interval = 50;

    while ((get_time_ms() - start) < ms)
    {
        pthread_mutex_lock(&data->death_mutex);
        should_continue = !data->stop;
        pthread_mutex_unlock(&data->death_mutex);
        if (!should_continue)
            break;
        usleep(sleep_interval);
    }
}

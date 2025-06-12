#include "philo.h"

void *thread_function(void *p)
{
    t_philo *philo;
    t_data *data;
    
    philo = (t_philo *)p;
    data = philo->data;

    if (philo->id % 2 != 0)
        usleep(100);
    while(1)
    {
        if (philo->data->stop == 1)
            return NULL;
        if (philo->id % 2 == 0)
        {
            pthread_mutex_lock(philo->left_fork);
            print_status(data, philo->id, "get left fork");
            pthread_mutex_lock(philo->right_fork);
            print_status(data, philo->id, "get right fork");
        }
        else
        {
            pthread_mutex_lock(philo->right_fork);
            print_status(data, philo->id, "get right fork");
            pthread_mutex_lock(philo->left_fork);
            print_status(data, philo->id, "get left fork");
        }
        pthread_mutex_lock(&philo->mael);
        print_status(data, philo->id, "is eating");
        philo->last_meal = get_time_ms();
        pthread_mutex_unlock(&philo->mael);

        smart_sleep(data->tte, data);
        pthread_mutex_lock(&philo->mael_count);
        philo->meal_count++;
        pthread_mutex_unlock(&philo->mael_count);
        
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);
        print_status(data, philo->id, "is sleeping");
        smart_sleep(data->tts, data);
        // print_status(data, philo->id, "is thinking");
        // usleep(500);
        if (philo->data->nb_ph % 2 == 1)
            ft_usleep((philo->data->tte * 2) - philo->data->tts, philo->data);
    }
    return(NULL);
}


void *monitor_routine(void *arg)
{
    t_data *data;
    int i;
    int all_ate;

    data = (t_data *)arg;
    while (1)
    {
        i = 0;
        all_ate = 1;
        while (i < data->nb_ph)
        {
            if (get_time_ms() - data->philos[i].last_meal > data->ttd)
            {
                print_status(data, data->philos[i].id, "died");
                data->stop = 1;
                return (NULL);
            }

            if (data->n_o_t_e_ph_m_e != -1 && 
                data->philos[i].meal_count < data->n_o_t_e_ph_m_e)
                all_ate = 0;
            i++;
        }
        if (data->n_o_t_e_ph_m_e != -1 && all_ate)
        {
            pthread_mutex_lock(&data->print_mutex);
            data->stop = 1;
            printf("All philosophers have eaten!\n");
            pthread_mutex_unlock(&data->print_mutex);
            return (NULL);
        }
        usleep(1000);
    }
    return (NULL);
}

int create_philo(t_data *a)
{
    int i = 0;
	pthread_t monitor;

    while (i < a->nb_ph)
    {
        if (pthread_create(&a->threads[i], NULL, thread_function, &a->philos[i]) != 0)
        {
            perror("pthread_create failed");
            return 1;
        }
        i++;
    }
	if (pthread_create(&monitor, NULL, monitor_routine, a) != 0)
    {
        printf("Error: Failed to create monitor thread\n");
        return (1);
    }
    i = 0;
    while (i < a->nb_ph)
    {
        pthread_join(a->threads[i], NULL);
        i++;
    }
	pthread_join(monitor, NULL);
    return (0);
}

int main(int argc, char **argv)
{
    t_data a;

    if (argc != 5 && argc != 6)
    {
        printf("nbr of arg not valid");
        return (1);
    }
	if (init_data(&a, argv, argc) != 0)
    {
        printf("Error: Failed to initialize data\n");
        return (1);
    }
	if (init_mutex(&a) != 0)
    {
        printf("Error: Failed to initialize mutexes\n");
        free_data(&a);
        return (1);
    }
	init_philo(&a);
	if (create_philo(&a) != 0)
    {
        free_data(&a);
        return (1);
    }
    free_data(&a);
}

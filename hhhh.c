// Dans le fichier utils.c - fonction print_status corrigée
void print_status(t_data *data, int id, char *status)
{
    pthread_mutex_lock(&data->stop_mutex);
    if (data->stop == 1)
    {
        pthread_mutex_unlock(&data->stop_mutex);
        return;
    }
    pthread_mutex_unlock(&data->stop_mutex);
    
    pthread_mutex_lock(&data->print_mutex);
    // Double vérification après avoir pris le mutex print
    if (data->stop == 1)
    {
        pthread_mutex_unlock(&data->print_mutex);
        return;
    }
    printf("%lld ", get_time_ms() - data->start_time);
    printf("Philosopher %d %s\n", id + 1, status);
    pthread_mutex_unlock(&data->print_mutex);
}

// Dans le fichier principal - fonction thread_function corrigée
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
        // Vérification du stop au début de chaque itération
        pthread_mutex_lock(&data->stop_mutex);
        if (data->stop == 1) 
        {
            pthread_mutex_unlock(&data->stop_mutex);
            return NULL;
        }
        pthread_mutex_unlock(&data->stop_mutex);
        
        // Prendre les fourchettes
        if (philo->id % 2 == 0)
        {
            pthread_mutex_lock(philo->left_fork);
            // Vérifier stop après avoir pris une fourchette
            pthread_mutex_lock(&data->stop_mutex);
            if (data->stop == 1) 
            {
                pthread_mutex_unlock(philo->left_fork);
                pthread_mutex_unlock(&data->stop_mutex);
                return NULL;
            }
            pthread_mutex_unlock(&data->stop_mutex);
            
            print_status(data, philo->id, "get left fork");
            
            pthread_mutex_lock(philo->right_fork);
            // Vérifier stop après avoir pris la deuxième fourchette
            pthread_mutex_lock(&data->stop_mutex);
            if (data->stop == 1) 
            {
                pthread_mutex_unlock(philo->right_fork);
                pthread_mutex_unlock(philo->left_fork);
                pthread_mutex_unlock(&data->stop_mutex);
                return NULL;
            }
            pthread_mutex_unlock(&data->stop_mutex);
            
            print_status(data, philo->id, "get right fork");
        }
        else
        {
            pthread_mutex_lock(philo->right_fork);
            // Vérifier stop après avoir pris une fourchette
            pthread_mutex_lock(&data->stop_mutex);
            if (data->stop == 1) 
            {
                pthread_mutex_unlock(philo->right_fork);
                pthread_mutex_unlock(&data->stop_mutex);
                return NULL;
            }
            pthread_mutex_unlock(&data->stop_mutex);
            
            print_status(data, philo->id, "get right fork");
            
            pthread_mutex_lock(philo->left_fork);
            // Vérifier stop après avoir pris la deuxième fourchette
            pthread_mutex_lock(&data->stop_mutex);
            if (data->stop == 1) 
            {
                pthread_mutex_unlock(philo->left_fork);
                pthread_mutex_unlock(philo->right_fork);
                pthread_mutex_unlock(&data->stop_mutex);
                return NULL;
            }
            pthread_mutex_unlock(&data->stop_mutex);
            
            print_status(data, philo->id, "get left fork");
        }
        
        // Manger
        pthread_mutex_lock(&philo->meal);
        print_status(data, philo->id, "is eating");
        philo->last_meal = get_time_ms();
        pthread_mutex_unlock(&philo->meal);
        
        smart_sleep(data->tte, data);
        
        pthread_mutex_lock(&philo->meal_count);
        philo->count++;
        pthread_mutex_unlock(&philo->meal_count);
        
        // Libérer les fourchettes
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);
        
        // Vérifier stop avant de dormir
        pthread_mutex_lock(&data->stop_mutex);
        if (data->stop == 1) 
        {
            pthread_mutex_unlock(&data->stop_mutex);
            return NULL;
        }
        pthread_mutex_unlock(&data->stop_mutex);
        
        print_status(data, philo->id, "is sleeping");
        smart_sleep(data->tts, data);
        
        // Vérifier stop avant de penser
        pthread_mutex_lock(&data->stop_mutex);
        if (data->stop == 1) 
        {
            pthread_mutex_unlock(&data->stop_mutex);
            return NULL;
        }
        pthread_mutex_unlock(&data->stop_mutex);
        
        print_status(data, philo->id, "is thinking");
        
        if (philo->data->nb_ph % 2 == 1)
            ft_usleep((philo->data->tte * 2) - philo->data->tts, philo->data);
    }
    return(NULL);
}

// Fonction monitor_routine corrigée
void *monitor_routine(void *arg)
{
    t_data *data;
    int i;
    int all_ate;
    long long last_meal_time;
    int meal_count;

    data = (t_data *)arg;
    while (1)
    {
        i = 0;
        all_ate = 1;
        while (i < data->nb_ph)
        {
            pthread_mutex_lock(&data->philos[i].meal);
            last_meal_time = data->philos[i].last_meal;
            pthread_mutex_unlock(&data->philos[i].meal);
            
            if (get_time_ms() - last_meal_time > data->ttd)
            {
                pthread_mutex_lock(&data->stop_mutex);
                data->stop = 1;
                pthread_mutex_unlock(&data->stop_mutex);
                
                pthread_mutex_lock(&data->print_mutex);
                printf("%lld ", get_time_ms() - data->start_time);
                printf("Philosopher %d died\n", data->philos[i].id + 1);
                pthread_mutex_unlock(&data->print_mutex);
                return (NULL);
            }
            
            pthread_mutex_lock(&data->philos[i].meal_count);
            meal_count = data->philos[i].count;
            pthread_mutex_unlock(&data->philos[i].meal_count);
        
            if (data->n_o_t_e_ph_m_e != -1 && meal_count < data->n_o_t_e_ph_m_e)
                all_ate = 0;
            i++;
        }
        
        if (data->n_o_t_e_ph_m_e != -1 && all_ate)
        {
            pthread_mutex_lock(&data->stop_mutex);
            data->stop = 1;
            pthread_mutex_unlock(&data->stop_mutex);
            
            pthread_mutex_lock(&data->print_mutex);
            printf("All philosophers have eaten!\n");
            pthread_mutex_unlock(&data->print_mutex);
            return (NULL);
        }
        usleep(1000);
    }
    return (NULL);
}

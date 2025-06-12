#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>


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
	pthread_mutex_t mael;
	pthread_mutex_t mael_count;
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
	pthread_t       *threads;
	pthread_mutex_t *forks;
	pthread_mutex_t print_mutex;
} t_data;



int	ft_atoi(char *nptr);
int init_philo(t_data *data);
int init_data(t_data *a, char **argv, int argc);
void free_data(t_data *data);
void smart_sleep(long long duration, t_data *data);
void print_status(t_data *data, int id, char *status);
long long get_time_ms(void);
int init_mutex(t_data *a);


#endif

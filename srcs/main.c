#include "philosophers.h"


// rajouter un seul philo
int main(int argc, char **argv)
{
	t_param_philo	data;
	t_philo			*philos;

	if (init_data(&data))
		return (0);
	if (init_mutex(&data))
		return (0);
	philos = malloc(sizeof(t_philo) * (data.nb_philo + 1));
	if (!philos)
		return (destroy_mutex(&data, data.nb_philo - 1, 1), 0);
	init_tab_philo(philos, &data);
	philo_can_live(&data, philos);
	return (0);
}

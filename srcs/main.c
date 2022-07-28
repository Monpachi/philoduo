#include "philosophers.h"

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
	// if (data.nb_philo == 1)
	// 	routine_solo(philos);
	philo_can_live(&data, philos);
	// philo_can_live(&data, philos);

	return (0);
}
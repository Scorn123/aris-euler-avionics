/*
 * task_fsm.h
 *
 *  Created on: May 24, 2020
 *      Author: Jonas
 */

#ifndef INC_TASKS_TASK_FSM_H_
#define INC_TASKS_TASK_FSM_H_

/* Includes */
#include "Sim_Con/env.h"
#include "Sim_Con/flight_phase_detection.h"
#include "Util/util.h"
#include "stm32f7xx_hal.h"
#include "cmsis_os.h"
#include "main.h"

/* Constants */
#define FSM_SAMPLING_FREQ 20

/* Parameters */

/* Commands */

/* Extern */


/* FSM Mutex */
extern osMutexId_t fsm_mutex;
extern osMutexId_t environment_mutex;

extern env_t global_env;
extern flight_phase_detection_t global_flight_phase_detection;

/* State Estimation Mutex */
extern osMutexId_t state_est_mutex;
extern state_est_data_t state_est_data_global;

/* Tasks */
void vTaskFSM(void *argument);


#endif /* INC_TASKS_TASK_FSM_H_ */

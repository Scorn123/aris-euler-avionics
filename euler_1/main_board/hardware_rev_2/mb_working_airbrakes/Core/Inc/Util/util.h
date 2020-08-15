/*
 * util.h
 *
 *  Created on: Feb 24, 2020
 *      Author: stoja
 */

#ifndef INC_UTIL_UTIL_H_
#define INC_UTIL_UTIL_H_

#include "cmsis_os.h"

/** BASIC TYPES **/

/* Timestamp */
typedef uint32_t timestamp_t;

/* Board ID */
typedef uint8_t board_id_t;

/** ENUMS **/

typedef enum {
	IDLE_COMMAND = 155, CALIBRATE_SENSORS, AIRBRAKE_TEST_COMMAND
} command_e;

typedef struct {
	command_e command[4];
} command_xbee_t;

/* Rocket state */
typedef enum {
	IDLE = 1, AIRBRAKE_TEST, THRUSTING, COASTING, DESCENT, RECOVERY
} flight_phase_e;

/* Mach Regime */
typedef enum {
	SUBSONIC = 1, TRANSONIC, SUPERSONIC
} mach_regime_e;

/* Sensor type */
typedef enum {
	BARO = 1, IMU, GPS
} sensor_type_e;

/* Log entry */
typedef enum {
	SENSOR = 1, STATE, ESTIMATOR_VAR, CONTROLLER_OUTPUT, MOTOR_POSITION, MSG
} log_entry_type_e;


/** SENSOR DATA TYPES **/

/* IMU data */
typedef struct {
	int16_t gyro_x, gyro_y, gyro_z;
	int16_t acc_x, acc_y, acc_z;
	timestamp_t ts;
} imu_data_t;

/* Barometer data */
typedef struct {
	int32_t pressure;
	int32_t temperature;
	timestamp_t ts;
} baro_data_t;

typedef struct {
	baro_data_t baro;
	imu_data_t imu;
	uint8_t checksum;
} sb_data_t;

/* GPS data */
typedef struct {
	/* add more */
	timestamp_t ts;
} gps_data_t;

/** CONTROL DATA TYPES **/

/* State Estimation Output */
typedef struct {
	int32_t position_world[3];
	int32_t velocity_rocket[3];
	int32_t acceleration_rocket[3];
	int32_t velocity_world[3];
	int32_t acceleration_world[3];
} state_est_data_t;

/* FSM States */
typedef struct {
	flight_phase_e flight_phase;
	mach_regime_e mach_regime;
	float mach_number;
	int8_t num_samples_positive;
} flight_phase_detection_t;

/** XBEE SUPER STRUCT **/

typedef struct {
	sb_data_t sb1;
	sb_data_t sb2;
	sb_data_t sb3;
	int32_t height;
	int32_t velocity;
	timestamp_t ts;
	flight_phase_e flight_phase;
	mach_regime_e mach_regime;
} telemetry_t;

/* Sensor Board Mutexes */
typedef struct{
	osMutexId_t mutex;
	uint32_t counter;
} custom_mutex_t;


static const command_xbee_t IDLE_XBEE_DATA = { IDLE_COMMAND, IDLE_COMMAND, IDLE_COMMAND, IDLE_COMMAND };

static const imu_data_t EMPTY_IMU = { 0 };

/** LOGGING **/

#define LOG_BUFFER_LEN 150

#define LOG_QUEUE_SIZE 128
extern osMessageQueueId_t log_queue;

typedef struct {
	char str[LOG_BUFFER_LEN];
} log_entry_t;

osStatus_t logSensor(timestamp_t ts, board_id_t sensor_board_id,
		sensor_type_e sens_type, void *sensor_data);
osStatus_t logRocketState(timestamp_t ts, flight_phase_detection_t flight_phase_detection);
/* TODO [nstojosk] - this signature & implementation should be adjusted */
osStatus_t logEstimatorVar(timestamp_t ts, state_est_data_t estimator_data);
osStatus_t logControllerOutput(timestamp_t ts, int32_t controller_output, int32_t reference_error,
		int32_t integrated_error);
osStatus_t logMotor(timestamp_t ts, int32_t desired_position, int32_t actual_position);
osStatus_t logMsg(timestamp_t ts, char *msg);

/* USB Fake data insert */

#define USB_DATA_ENABLE 0


/** USB DEBUGGING **/

/* Debug flag */
#ifdef DEBUG
#undef DEBUG
#endif
/* Comment the next line in order to disable debug mode */
//#define DEBUG

#ifdef DEBUG
osMutexId_t print_mutex;
#define PRINT_BUFFER_LEN 200
char print_buffer[PRINT_BUFFER_LEN];
#endif

uint8_t UsbPrint(const char *format, ...);

#endif /* INC_UTIL_UTIL_H_ */

//
// Created by imrek on 20.09.2020.
//

#ifndef ARIS_REED_SOLOMON_RS_H
#define ARIS_REED_SOLOMON_RS_H

#include <stdio.h>
#include <stdint.h>


#define mm  8           /* RS code over GF(2**mm) - change to suit */
#define nn  255         /* nn=2**mm -1   length of codeword */
#define tt  55          /* number of errors that can be corrected */
#define kk  145         /* kk = nn-2*tt  */

int alpha_to[nn + 1], index_of[nn + 1], gg[nn - kk + 1];
int pp[mm + 1], recd[nn], bb[nn - kk];
uint8_t data[kk];


void set_irr_poly();
void generate_gf();
void gen_poly();
void encode_rs();
void decode_rs();

/* Rocket state */
typedef enum {
    IDLE = 1,
    AIRBRAKE_TEST,
    THRUSTING,
    COASTING,
    DESCENT,
    RECOVERY
} flight_phase_e;

/* GPS data */
typedef struct {
    uint32_t hour;
    uint32_t minute;
    uint32_t second;
    uint32_t lat_decimal;
    uint32_t lon_decimal;
    uint16_t HDOP;
    uint16_t altitude;
    uint8_t satellite;
    uint8_t lat_deg;
    uint8_t lon_deg;
    uint8_t fix;
} gps_data_t;

/* Battery Data */
typedef struct {
    uint16_t battery;
    uint16_t current;
    uint16_t consumption;
} telemetry_battery_data_t;

/* SB Data */
typedef struct {
    int32_t pressure;
    int32_t temperature;
    int16_t gyro_x, gyro_y, gyro_z;
    int16_t acc_x, acc_y, acc_z;
} telemetry_sb_data_t;

typedef struct {
    telemetry_sb_data_t sb_data;
    telemetry_battery_data_t battery;
    gps_data_t gps;
    int32_t height;
    int32_t velocity;
    int32_t airbrake_extension;
    flight_phase_e flight_phase;
} telemetry_t;

#endif //ARIS_REED_SOLOMON_RS_H

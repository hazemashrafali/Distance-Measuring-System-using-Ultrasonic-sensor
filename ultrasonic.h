/*
 * ultrasonic.h
 *
 *  Created on: Mar 4, 2022
 *      Author: HAZEM-PC
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "icu.h"

#define HIGH 1
#define LOW 0

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description : Function to initialize the ultrasonic driver
 * 1-initialize ICU driver
 * 2-set callback function
 * 3- //setup trigger pin direction as output
 */
void Ultrasonic_init(void);

// function to read distance of from the sensor

uint16 Ultrasonic_readDistance(void);

#endif /* ULTRASONIC_H_ */

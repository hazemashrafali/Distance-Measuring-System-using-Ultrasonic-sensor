/*
 * ultrasonic.c
 *
 *  Created on: Mar 4, 2022
 *      Author: HAZEM-PC
 */

#include "gpio.h"
#include "ultrasonic.h"
#include "util/delay.h"

static uint8 g_edgeCount = 0;   //to count number of edges
static uint16 g_timeHigh = 0;   //to hold time of generated pulse

/* Create configuration structure for ICU driver */

static Icu_ConfigType icu_config={F_CPU_8,RISING};

void Ultrasonic_edgeProcessing(void)
{
	g_edgeCount++;
	if(g_edgeCount==1)
	{
	Icu_clearTimerValue();
	Icu_setEdgeDetectionType(FALLING);
	}
	else if(g_edgeCount==2)
	{
		g_timeHigh=Icu_getInputCaptureValue();
		Icu_clearTimerValue();
		Icu_setEdgeDetectionType(RISING);
	}
}

void Ultrasonic_init(void)
{
	Icu_init(&icu_config);
	Icu_setCallBack(Ultrasonic_edgeProcessing);
	GPIO_setupPinDirection(PORTB_ID, PIN5_ID,PIN_OUTPUT);    //setup trigger pin direction as output
	GPIO_writePin(PORTB_ID, PIN5_ID,LOW);
}

void Ultrasonic_Trigger(void)
{
	GPIO_writePin(PORTB_ID, PIN5_ID,HIGH);
	_delay_us(10);
	GPIO_writePin(PORTB_ID, PIN5_ID,LOW);
}

uint16 Ultrasonic_readDistance(void)
{
	uint16 value=0;
	Ultrasonic_Trigger();
	while(g_edgeCount != 2);   //wait until ultrasonic sound to travel towards the object and return.
	value=((uint16)g_timeHigh/58)+1;
	g_edgeCount=0;            //clear edge count to be ready for new read
	return value;
}



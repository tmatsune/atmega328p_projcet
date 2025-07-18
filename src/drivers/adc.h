#ifndef ADC_H
#define ADC_H 
#include <Arduino.h>

#define ADC_COUNT 4
typedef int adc_input_values[ADC_COUNT];

void adc_init(void);
void get_adc_input_values(adc_input_values vals);

/*
    adc_input_values adc_vals;
    get_adc_input_values(adc_vals);
    int front_left = adc_vals[2];
    
    val[0] = pin A3
    val[1] = pin A0 
    val[2] = pin A1
    val[3] = pin A2
*/

#endif
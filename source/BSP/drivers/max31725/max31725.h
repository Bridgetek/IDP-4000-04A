/**
 *  @file max31725.c Temperature sensor device driver
 *
 *  @brief
 *   Temperature sensor device driver
 **/

#ifndef __MAX31725_H__
#define __MAX31725_H__

int	  max31725_init(void);
float max31725_deg_C(void);

#endif /* __MAX31725_H__ */
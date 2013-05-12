#ifndef __EECS461_H__
#define __EECS461_H__

#include <mpc5553.h>
#include <typedefs.h>

/* define 24-bit type, for etpu use */
typedef int32_t int24_t;

void init_EECS461();

uint32_t get_sys_freq(void);

void init_speed(long mhz);

void init_fp(void);


#endif /* __EECS461_H__ */

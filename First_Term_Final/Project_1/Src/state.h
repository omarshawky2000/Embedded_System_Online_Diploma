//Protection from multiple declarations 
#ifndef STATE_H_
#define STATE_H_

#include "driver.h"

// Prototypes
#define STATE_define(_stateFUN_) void ST_##_stateFUN_()
#define STATE(_stateFUN_) ST_##_stateFUN_

// States connections
void setPressureVal(int s);
void alarmON (void);
void alarmOFF (void);

extern int AlarmFlag;

#endif /*STATE_H_*/

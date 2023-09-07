//Protection from multiple declarations 
#ifndef STATE_H_
#define STATE_H_

// Prototypes
#define STATE_define(_stateFUN_) void ST_##_stateFUN_()
#define STATE(_stateFUN_) ST_##_stateFUN_

// States connections
void DC_motor(int s);
void US_Set_distance (int d);


#endif /*STATE_H_*/

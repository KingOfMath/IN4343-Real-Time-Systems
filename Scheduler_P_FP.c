#include "Scheduler.h"
#include "Led.h"
#include "TimeTracking.h"

static void ExecuteTask (Taskp t)
{
  /* ----------------------- INSERT CODE HERE ----------------------- */
	  t->Invoked++;

	  t->Taskf(t->Remaining_Time); // execute task

	  t->Remaining_Time = 0;

  /* ---------------------------------------------------------------- */

}

void Scheduler_P_FP (Task Tasks[])
{ 
  /* ----------------------- INSERT CODE HERE ----------------------- */

  uint8_t i,j;
  int sorted[NUMTASKS];
  int index[NUMTASKS];
  for(i = 0; i < NUMTASKS; i++){
	 index[i] = i;
  }
  for(i = 0; i < NUMTASKS; i++){
	 for(j = i+1; j < NUMTASKS; j++){
		 Taskp tj = &Tasks[j];
		 Taskp ti = &Tasks[i];
		 if(tj->Prio < ti->Prio){
			 int temp = tj->Prio;
			 tj->Prio = ti->Prio;
			 ti->Prio = temp;

			 temp = index[i];
			 index[i] = index[j];
			 index[j] = temp;
		 }
	 }
  }

  for(i = 0; i < NUMTASKS; i++){
	  Taskp t = &Tasks[index[i]];
	  if (t->Activated != t->Invoked && t->Remaining_Time > 0)
	  {
	      _EINT();
		StartTracking(1);
		ExecuteTask(t);
		StopTracking(1);
		PrintResults();
		_DINT();
	  }
  }
	
  /* ---------------------------------------------------------------- */
}

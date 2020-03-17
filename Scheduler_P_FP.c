#include "Scheduler.h"
#include "Led.h"
#include "TimeTracking.h"

static void ExecuteTask (Taskp t)
{
  /* ----------------------- INSERT CODE HERE ----------------------- */
	if(t->Flags & TRIGGERED){
	  t->Invoked++;
	  t->Taskf(t->ExecutionTime); // execute task
	}
	else
	  t->Invoked = t->Activated;

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
	  if (t->Activated != t->Invoked)
	  {
		StartTracking(1);
		ExecuteTask(t);
		StopTracking(1);
		PrintResults();
	  }
  }
	
  /* ---------------------------------------------------------------- */
}

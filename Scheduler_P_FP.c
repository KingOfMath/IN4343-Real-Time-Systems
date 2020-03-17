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

  uint8_t i = NUMTASKS-1; 
  do {	
	  Taskp t = &Tasks[i];
	  if (t->Activated != t->Invoked)
	  {
		//StartTracking(0);
		//StartTracking(1);
		ExecuteTask(t);
		//StopTracking(1);
		//StopTracking(0);
		//PrintResults();
	  }
  } while (i--);
	
  /* ---------------------------------------------------------------- */
}

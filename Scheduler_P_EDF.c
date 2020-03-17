#include "Scheduler.h"
#include "Led.h"

static void ExecuteTask (Taskp t)
{
  /* insert code */
  	if(t->Flags & TRIGGERED){
	  t->Invoked++;
	  t->Taskf(t->ExecutionTime); // execute task
	}
	else
	  t->Invoked = t->Activated;
  /* insert code */
}

void Scheduler_P_EDF (Task Tasks[])
{ 
  /* insert code */
  
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
		 if(tj->NextPendingDeadline < ti->NextPendingDeadline){
			 int temp = tj->NextPendingDeadline;
			 tj->NextPendingDeadline = ti->NextPendingDeadline;
			 ti->NextPendingDeadline = temp;
			 
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
  
  /* insert code */
}

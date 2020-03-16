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

void Scheduler_P_RM (Task Tasks[])
{ 
  /* insert code */
  
  uint8_t i,j; 
  int index[NUMTASKS];
  for(i = 0; i < NUMTASKS; i++){
	 index[i] = i;
	 Taskp t = &Tasks[i];
	 t->Prio = (uint8_t)(1 / t->Period);
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
		ExecuteTask(t);
	  }
  }
  
  /* insert code */
}

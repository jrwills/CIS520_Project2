//hw2_test = process_scheduling.c
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "dyn_array.h"
#include "processing_scheduling.h"


// You might find this handy.  I put it around unused parameters, but you should
// remove it before you submit. Just allows things to compile initially.
#define UNUSED(x) (void)(x)

// private function
void virtual_cpu(ProcessControlBlock_t *process_control_block) 
{
    // decrement the burst time of the pcb
    --process_control_block->remaining_burst_time;
}

//https://www.edureka.co/blog/first-come-first-serve-scheduling/#:~:text=First%20Come%20First%20Serve%20is,are%20requested%20by%20the%20processor.
bool first_come_first_serve(dyn_array_t *ready_queue, ScheduleResult_t *result) 
{
    //UNUSED(ready_queue);
    //UNUSED(result);

    //size_t n = 0; //number of blocks?
    /*size_t bt = 0; //burst
    size_t wt = 0; //wait
    size_t at = 0; //arrival
    size_t tt = 0; //turnaround*/
    
    if(ready_queue == NULL || result == NULL)
    {
        return false;
    }

    //n = dyn_array_size(ready_queue); //0 on error, need to cast as (size_T)???

    return true;
}

bool shortest_job_first(dyn_array_t *ready_queue, ScheduleResult_t *result) 
{
    UNUSED(ready_queue);
    UNUSED(result);
    return false;   
}

bool priority(dyn_array_t *ready_queue, ScheduleResult_t *result) 
{
    UNUSED(ready_queue);
    UNUSED(result);
    return false;   
}

bool round_robin(dyn_array_t *ready_queue, ScheduleResult_t *result, size_t quantum) 
{
    UNUSED(ready_queue);
    UNUSED(result);
    UNUSED(quantum);
    return false;
}

dyn_array_t *load_process_control_blocks(const char *input_file) 
{
    UNUSED(input_file);
    return NULL;
}

bool shortest_remaining_time_first(dyn_array_t *ready_queue, ScheduleResult_t *result) 
{
    UNUSED(ready_queue);
    UNUSED(result);
    return false;
}

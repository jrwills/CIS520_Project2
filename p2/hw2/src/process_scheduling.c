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
    //UNUSED(input_file);
    //return NULL;
    // Ensure parameters are valid
    if (input_file == NULL){
        return NULL;
    }
    
    // Try to open the file to read, return null if unsuccessful
    int file = open(input_file, O_RDONLY);
    if (file <= 0){
        close(file);
        return NULL;
    }
    
    // Read the total number of processes in the file
    // return null if read is unsuccessful
    uint32_t length;
    int readFile = read(file, &length, sizeof(uint32_t));
    if (readFile <= 0){
        return NULL;
    }
    
    // Allocate memory to a process control block struct
    ProcessControlBlock_t* pcb = malloc(sizeof(ProcessControlBlock_t)*length);
    
    // From file, read in burst time, priority, and arrival time into pcb struct
    for(uint32_t i = 0; i < length; i++){
        readFile = read(file, &pcb[i].remaining_burst_time, sizeof(uint32_t));
        readFile = read(file, &pcb[i].priority, sizeof(uint32_t));
        readFile = read(file, &pcb[i].arrival, sizeof(unint32_t));
    }
    
    // Create dynamic array from pcb
    dyn_array_t* dynArr = dyn_array_import((void*)pcb, sizeof(length), sizeof(ProcessControlBlock_t), NULL);
    
    // Cleanup
    close(file);
    free(pcb);
    
    // Return dynamic array
    return dynArr;
}

bool shortest_remaining_time_first(dyn_array_t *ready_queue, ScheduleResult_t *result) 
{
    UNUSED(ready_queue);
    UNUSED(result);
    return false;
}

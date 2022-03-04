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

//https://www.edureka.co/blog/first-come-first-serve-scheduling/#:~:text=First+Come+First+Serve+is,are+requested+by+the+processor.
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
    if((input_file == NULL) || (*input_file == '\n') || (*input_file == '\0')){
        return false;
    }
    int fd;
    // open input file for read-only access
    if((fd = open(input_file, O_RDONLY)) == -1){
        printf("fd: %d\n", fd);
        return false;
    }
    
    uint32_t n = 0;
    // read first 4 bytes of pcb file into int storing number of pcbs
    if (read(fd, &n, 4) == -1){
        return false;
    }
    printf("n: %d\n", n);
    
    // create an array of process control blocks to be used as the ready queue
    ProcessControlBlock_t * pcb_arr = malloc(n*sizeof(ProcessControlBlock_t));

    // loop through each pcb in the binary file and store the burst time, 
    // priority, and arrival time parameters in the pcb array
    for(uint32_t i = 0; i < n; i++){
        read(fd, &pcb_arr[i].remaining_burst_time, 4);
        read(fd, &pcb_arr[i].priority, 4);
        read(fd, &pcb_arr[i].arrival, 4);
    
        printf("Burst time %d: %d\n", i, pcb_arr[i].remaining_burst_time);
        printf("Priority %d: %d\n", i, pcb_arr[i].priority);
        printf("Arrival time %d: %d\n\n", i, pcb_arr[i].arrival);
    }
    
    // create a dynamic array to store the pcb array
    struct dyn_array *dyn_arr = dyn_array_create(n, sizeof(ProcessControlBlock_t), NULL);
    
    // import the pcb array to a new dynamic array
    dyn_arr = dyn_array_import(pcb_arr, n, sizeof(ProcessControlBlock_t), NULL);
    
    return dyn_arr;
}

bool shortest_remaining_time_first(dyn_array_t *ready_queue, ScheduleResult_t *result) 
{
    UNUSED(ready_queue);
    UNUSED(result);
    return false;
}

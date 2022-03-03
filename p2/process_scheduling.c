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
/*
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
        readFile = read(file, &pcb[i].arrival_time);
    }
    
    // Create dynamic array from pcb
    dyn_array_t* dynArr = dyn_array_import((void*)pcb, sizeof(length), sizeof(ProcessControlBlock_t), NULL);
    
    // Cleanup
    close(file);
    free(pcb);
    
    // Return dynamic array
    return dynArr;
}*/


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
    
    //int32_t *n = malloc(sizeof(int32_t));
    uint32_t n = 0;
    // read first 2 bytes of pcb file into int storing number of pcbs
    if (read(fd, &n, 2) == -1){
        printf("fd: %d\n", fd);
        return false;
    }
    printf("n: %d\n", n);
    printf("\n\nTest\n\n");
    //change the location of the file descriptor to the 2 bytes into the input file
    lseek (fd, 2, SEEK_CUR);
    //dyn_array_t *dyn_arr = dyn_array_create(*n, sizeof(ProcessControlBlock_t), NULL);
    //struct dyn_array *dyn_arr = dyn_array_create(*n, sizeof(ProcessControlBlock_t), NULL);
    
    //struct dyn_array *dyn_arr = dyn_array_create(0, sizeof(ProcessControlBlock_t), NULL);
    
    /*for(int i = 0; i < *n; i++){
        ProcessControlBlock_t pcb;
        int* burst_time = malloc(sizeof(int32_t));
        int* priority = malloc(sizeof(int32_t));
        int* arrival = malloc(sizeof(int32_t));
        read(fd, burst_time, 4);
        //add another 4 bytes(size of a 32-bit int) to the offset
        lseek (fd, 4, SEEK_CUR);
        
        //printf("Pcb #%d burst time: %d\n", i, *burst_time);
        printf("\n\nTest\n\n");
        
        read(fd, priority, 4);
        //add another 4 bytes(size of a 32-bit int) to the offset
        lseek (fd, 4, SEEK_CUR);
        
        read(fd, arrival, 4);
        //add another 4 bytes(size of a 32-bit int) to the offset
        lseek (fd, 4, SEEK_CUR);
        
        // initialize values of current pcb struct
        pcb.remaining_burst_time = * burst_time;
        pcb.priority = * priority;
        pcb.arrival = * arrival;
        pcb.started = false;
        
        //dyn_arr->array[i] = pcb;
        //dyn_array_insert(dyn_arr, i, pcb);
        //ProcessControlBlock_t *indexPtr = *(ProcessControlBlock_t*)dyn_array_at(dyn_arr, i);
        //indexPtr = pcb;
        
        // put the current pcb object at the back of the array
        const void *const pcbPtr = &pcb;
        dyn_array_push_back(dyn_arr, pcbPtr);
    }*/
    return NULL;
    
    //return dyn_arr;
}

bool shortest_remaining_time_first(dyn_array_t *ready_queue, ScheduleResult_t *result) 
{
    UNUSED(ready_queue);
    UNUSED(result);
    return false;
}

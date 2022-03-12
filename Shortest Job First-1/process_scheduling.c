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

bool sort_arrival_times(dyn_array_t *ready_queue){
    if(ready_queue == NULL){
        return false;
    }
    int numProcesses = dyn_array_size(ready_queue);
    ProcessControlBlock_t *tempPcb = malloc(sizeof(ProcessControlBlock_t));
    
    // at the end of the nested for loop, the ready queue should be sorted by arrival time
    for(int i = 0; i < numProcesses; i++){
        // allocate memory for temporary pcb that will be modified on each iteration of the for loop
        //ProcessControlBlock_t *tempPcb = malloc(sizeof(ProcessControlBlock_t));
        int minArrivalTime = -1;
        int minArrivalIndex = -1;
    
        // loop to find the minimum arrival time of any process and the corresponding index
        // in the ready queue array of this process
        // iterate up to numProcesses-i because the pcb with the lowest arrival
        // time will be pushed to the back of the array
        for(int j = 0; j < numProcesses-i; j++){
            //tempPcb = (ProcessControlBlock_t*)dyn_array_export(ready_queue);
            // get pcb at index j
            tempPcb = dyn_array_at(ready_queue, j);
            int arrivalTime = tempPcb->arrival;
        
            // initialize arrival time and index if this is the first loop through the array
            if((minArrivalTime == -1) || (minArrivalIndex == -1)){
                minArrivalTime = arrivalTime;
                minArrivalIndex = j;
            }
            else if(arrivalTime < minArrivalTime){
                minArrivalTime = arrivalTime;
                minArrivalIndex = j;
                }
                
            }// inner for loop
            
            // extract the min arrival time element and push to the back of the queue
            void  *const voidPcbPtr = malloc(sizeof(ProcessControlBlock_t));
            dyn_array_extract(ready_queue, minArrivalIndex , voidPcbPtr);
            dyn_array_push_back(ready_queue, voidPcbPtr);
            
    }// outer for loop
    return true;
}

bool sort_burst_times(dyn_array_t *ready_queue){
    if(ready_queue == NULL){
        return false;
    }
    int numProcesses = dyn_array_size(ready_queue);
    ProcessControlBlock_t *tempPcb = malloc(sizeof(ProcessControlBlock_t));
    
    // at the end of the nested for loop, the ready queue should be sorted by arrival time
    for(int i = 0; i < numProcesses; i++){
        // allocate memory for temporary pcb that will be modified on each iteration of the for loop
        //ProcessControlBlock_t *tempPcb = malloc(sizeof(ProcessControlBlock_t));
        int minBurstTime = -1;
        int minBurstIndex = -1;
    
        // loop to find the minimum burst time of any process and the corresponding index
        // in the ready queue array of this process
        // iterate up to numProcesses-i because the pcb with the lowest burst
        // time will be pushed to the back of the array
        for(int j = 0; j < numProcesses-i; j++){
            //tempPcb = (ProcessControlBlock_t*)dyn_array_export(ready_queue);
            // get pcb at index j
            tempPcb = dyn_array_at(ready_queue, j);
            int burstTime = tempPcb->remaining_burst_time;
        
            // initialize arrival time and index if this is the first loop through the array
            if((minBurstTime == -1) || (minBurstIndex == -1)){
                minBurstTime = burstTime;
                minBurstIndex = j;
            }
            else if(burstTime < minBurstTime){
                minBurstTime = burstTime;
                minBurstIndex = j;
                }
                
            }// inner for loop
            
            // extract the min arrival time element and push to the back of the queue
            void  *const voidPcbPtr = malloc(sizeof(ProcessControlBlock_t));
            dyn_array_extract(ready_queue, minBurstIndex , voidPcbPtr);
            dyn_array_push_back(ready_queue, voidPcbPtr);
            
    }// outer for loop
    return true;
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

    int numProcesses = dyn_array_size(ready_queue);
    ProcessControlBlock_t *tempPcb = malloc(sizeof(ProcessControlBlock_t));
    
    // put the first pcb to the end of the array so the array is out of order
    void  *const voidPcbPtr = malloc(sizeof(ProcessControlBlock_t));
    dyn_array_extract_front(ready_queue, voidPcbPtr);
    dyn_array_push_back(ready_queue, voidPcbPtr);
    
    // sort the ready queue based on arrival times, from lowest to highest
    if(!sort_arrival_times(ready_queue)){
        return false;
    }
    
    // populate array of burst times
    int bt[numProcesses];
    for(int i = 0; i < numProcesses; i++){
        tempPcb = dyn_array_at(ready_queue, i);
        bt[i] = tempPcb->remaining_burst_time;
    }
    
    // create an array to store the waiting time of each process
    int wt[numProcesses];
    wt[0] = 0;
    
    // the waiting time of each process is the sum of the previous process's burst times
    for(int i = 1; i < numProcesses; i++){
        wt[i] = 0;
        for(int j = 0; j<i; j++){
            wt[i] += bt[j];
        }
    }
    
    // array to hold the turn around time for each process
    int tat[numProcesses];
    // average waiting time
    float avwt = 0;
    // average turn around time
    float avtat = 0;
    // total run time
    unsigned long trt = 0;
    
    // calculate average waiting time and average turnaround time
    for(int i = 0; i< numProcesses; i++){
        // turnaround time equals sum of waiting and burst times
        tat[i] = wt[i] + bt[i];
        avwt += wt[i];
        //printf("Waiting Time[%d]: %d\n", i, wt[i]);
        avtat+=tat[i];
        // total run time is the sum of the burst times
        trt += bt[i];
    }
    avwt /= numProcesses;
    avtat /= numProcesses;
    printf("Average Waiting Time: %f\n",avwt);
    printf("Average Turnaround Time: %f\n",avtat);
    printf("Total Run Time: %ld\n",trt);
    
    result->average_waiting_time = avwt;
    result->average_turnaround_time = avtat;
    result->total_run_time = trt;
    
    //dyn_array_extract(dyn_array_t *const dyn_array, const size_t index, void *const object)
    

    //n = dyn_array_size(ready_queue); //0 on error, need to cast as (size_T)???

    return true;
}

bool shortest_job_first(dyn_array_t *ready_queue, ScheduleResult_t *result) 
{
    //UNUSED(ready_queue);
    //UNUSED(result);
    
    if(ready_queue == NULL || result == NULL)
    {
        return false;
    }
    
    int numProcesses = dyn_array_size(ready_queue);
    ProcessControlBlock_t *tempPcb = malloc(sizeof(ProcessControlBlock_t));
    
    // Should you sort by arrival time first, or only sort based on burst time?
    
    // sort the ready queue based on arrival times, from lowest to highest
    //if(!sort_arrival_times(ready_queue)){
    //    return false;
    //}
    
    // sort based on burst times, from lowest to highest
    if(!sort_burst_times(ready_queue)){
        return false;
    }
    
 // populate array of burst times
    int bt[numProcesses];
    for(int i = 0; i < numProcesses; i++){
        tempPcb = dyn_array_at(ready_queue, i);
        bt[i] = tempPcb->remaining_burst_time;
        printf("Process #%d burst time: %d\n", i, tempPcb->remaining_burst_time);
    }
    
    // create an array to store the waiting time of each process
    int wt[numProcesses];
    wt[0] = 0;
    
    // the waiting time of each process is the sum of the previous process's burst times
    for(int i = 1; i < numProcesses; i++){
        wt[i] = 0;
        for(int j = 0; j<i; j++){
            wt[i] += bt[j];
        }
    }
    
    // array to hold the turn around time for each process
    int tat[numProcesses];
    // average waiting time
    float avwt = 0;
    // average turn around time
    float avtat = 0;
    // total run time
    unsigned long trt = 0;
    
    // calculate average waiting time and average turnaround time
    for(int i = 0; i< numProcesses; i++){
        // turnaround time equals sum of waiting and burst times
        tat[i] = wt[i] + bt[i];
        avwt += wt[i];
        //printf("Waiting Time[%d]: %d\n", i, wt[i]);
        avtat+=tat[i];
        // total run time is the sum of the burst times
        trt += bt[i];
    }
    avwt /= numProcesses;
    avtat /= numProcesses;
    printf("Average Waiting Time: %f\n",avwt);
    printf("Average Turnaround Time: %f\n",avtat);
    printf("Total Run Time: %ld\n",trt);
    
    result->average_waiting_time = avwt;
    result->average_turnaround_time = avtat;
    result->total_run_time = trt;
    
    return true;   
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
    //printf("n: %d\n", n);
    
    // create an array of process control blocks to be used as the ready queue
    ProcessControlBlock_t * pcb_arr = malloc(n*sizeof(ProcessControlBlock_t));

    // loop through each pcb in the binary file and store the burst time, 
    // priority, and arrival time parameters in the pcb array
    for(uint32_t i = 0; i < n; i++){
        read(fd, &pcb_arr[i].remaining_burst_time, 4);
        read(fd, &pcb_arr[i].priority, 4);
        read(fd, &pcb_arr[i].arrival, 4);
    
        //printf("Burst time %d: %d\n", i, pcb_arr[i].remaining_burst_time);
        //printf("Priority %d: %d\n", i, pcb_arr[i].priority);
        //printf("Arrival time %d: %d\n\n", i, pcb_arr[i].arrival);
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

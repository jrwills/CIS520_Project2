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

/*******************************************************************************
    HELPER FUNCTION BLOCK
*******************************************************************************/

// HELPER function to help sort arrival times
// \param ready_queue the queue to be sorted
// \return a boolean indicating whether sort was successful
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

// HELPER function to help sort burst times
// \param ready_queue the queue to be sorted
// \return a boolean indicating whether sort was successful
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

/*******************************************************************************
    END HELPER FUNCTION BLOCK
*******************************************************************************/

/*******************************************************************************
    FCFS BLOCK
*******************************************************************************/

// Source: https://www.edureka.co/blog/first-come-first-serve-scheduling/#:~:text=First+Come+First+Serve+is,are+requested+by+the+processor.
// Runs the First Come First Served Process Scheduling algorithm over the incoming ready_queue
// \param ready queue a dyn_array of type ProcessControlBlock_t that contain be up to N elements
// \param result used for first come first served stat tracking \ref ScheduleResult_t
// \return true if function ran successful else false for an error
bool first_come_first_serve(dyn_array_t *ready_queue, ScheduleResult_t *result) 
{
    //Error Handling    
    if(ready_queue == NULL || result == NULL)
    {
        return false;
    }

    int numProcesses = dyn_array_size(ready_queue);
    ProcessControlBlock_t *tempPcb = malloc(sizeof(ProcessControlBlock_t));
    
    // put the first pcb to the end of the array so the array is out of order
    //void  *const voidPcbPtr = malloc(sizeof(ProcessControlBlock_t));
    //dyn_array_extract_front(ready_queue, voidPcbPtr);
    //dyn_array_push_back(ready_queue, voidPcbPtr);
    
    // sort the ready queue based on arrival times, from lowest to highest
    if(!sort_arrival_times(ready_queue)){
        return false;
    }
    
    // populate array of burst times and arrival times
    int bt[numProcesses];
    int at[numProcesses];
    for(int i = 0; i < numProcesses; i++){
        tempPcb = dyn_array_at(ready_queue, i);
        bt[i] = tempPcb->remaining_burst_time;
        at[i] = tempPcb->arrival;
    }
    
    // create an array to store the waiting time of each process
    int wt[numProcesses];
    wt[0] = 0;
    
    // the waiting time of each process is the sum of the previous process's burst times
    for(int i = 1; i < numProcesses; i++){
        wt[i] = 0;
        for(int j = 0; j<i; j++){
            //wt[i] = wt[i] + bt[j];
            wt[i] += bt[j];
        }
        wt[i] -= at[i];
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
    //printf("Average Waiting Time: %f\n",avwt);
    //printf("Average Turnaround Time: %f\n",avtat);
    //printf("Total Run Time: %ld\n",trt);
    
    //VALUES to be a part of result set, what we see in analysis.exec
    result->average_waiting_time = avwt;
    result->average_turnaround_time = avtat;
    result->total_run_time = trt;

    return true;
}

/*******************************************************************************
    END FCFS BLOCK
*******************************************************************************/

/*******************************************************************************
    SJF BLOCK
*******************************************************************************/

//Orig (John), then Will | SJF
// Runs the Shortest Job First Scheduling algorithm over the incoming ready_queue
// \param ready queue a dyn_array of type ProcessControlBlock_t that contain be up to N elements
// \param result used for shortest job first stat tracking \ref ScheduleResult_t
// \return true if function ran successful else false for an error
bool shortest_job_first(dyn_array_t *ready_queue, ScheduleResult_t *result) 
{
    //Error handling   
    if(ready_queue == NULL || result == NULL)
    {
        return false;
    }
    
    int numProcesses = dyn_array_size(ready_queue);
    int origNumProcesses = numProcesses;
    ProcessControlBlock_t *tempPcb = malloc(sizeof(ProcessControlBlock_t));
    
    // sort based on burst times, from lowest to highest
    if(!sort_arrival_times(ready_queue)){
        return false;
    }
    unsigned long trt = 0;                                                      // total run time
    float totalWaitTime = 0;
    tempPcb = dyn_array_at(ready_queue, 0);
    trt += tempPcb->arrival;                                                    // add the first arrival time to the total run time in case the first arrival time is not zero

    for(int i = 0; i < origNumProcesses; i++){                                  // loop through each element of the ready queue and run its process
        tempPcb = dyn_array_at(ready_queue, 0);
        uint32_t minBurstTime = tempPcb->remaining_burst_time;
        uint32_t minBurstIndex = 0;
        for(int j = 0; j < numProcesses; j++){
            tempPcb = dyn_array_at(ready_queue, j);
            if(tempPcb->arrival <= (uint32_t)trt){                              // find the process with the lowest burst time from among the processes that have already arrived
                if(tempPcb->remaining_burst_time < minBurstTime){
                    minBurstTime = tempPcb->remaining_burst_time;
                    minBurstIndex = j;
                }
            }
        }// for loop to find min burst time process
        
        dyn_array_erase(ready_queue, minBurstIndex);                            // remove the process that just ran from the ready queue
        numProcesses = numProcesses-1;
        
        for(unsigned int n = 0; n<minBurstTime; n++){                           // outer loop increments the total run time by the min burst time just found
            for(int m = 0; m<numProcesses; m++){                                // The inner loop increments the total wait time. The waiting time for each process that has arrived
                tempPcb = dyn_array_at(ready_queue, m);                         // but is not running is counted in the waiting time.
                if(tempPcb->arrival <= trt){
                    totalWaitTime++;
                }
            }
            trt++;
        }
        
    }// outer for loop
    
    float avwt = totalWaitTime/origNumProcesses;
    float avtat = (totalWaitTime + trt)/origNumProcesses;
    
    result->average_waiting_time = avwt;
    result->average_turnaround_time = avtat;
    result->total_run_time = trt;
    
    return true;   
}

/*******************************************************************************
    END SJF BLOCK
*******************************************************************************/

//Leave me alone??
bool priority(dyn_array_t *ready_queue, ScheduleResult_t *result) 
{
    UNUSED(ready_queue);
    UNUSED(result);
    return false;   
}

/*******************************************************************************
    ROUND ROBIN BLOCK
*******************************************************************************/

// https://www.geeksforgeeks.org/program-round-robin-scheduling-set-1/
// Runs the Round Robin Process Scheduling algorithm over the incoming ready_queue
// \param ready queue a dyn_array of type ProcessControlBlock_t that contain be up to N elements
// \param result used for round robin stat tracking \ref ScheduleResult_t
// \param the quantum
// \return true if function ran successful else false for an error
bool round_robin(dyn_array_t *ready_queue, ScheduleResult_t *result, size_t quantum) 
{
    if(ready_queue == NULL || result == NULL || quantum <= 0){                  // Ensure params are good
        return false;
    }
    
    float avg_wait = 0;                                                         // Average wait
    float avg_turn = 0;                                                         // Average turnaround time
    unsigned long total_rt = 0;                                                 // Total run time
    
    int numProcesses = dyn_array_size(ready_queue);                             // Get number of processes
    ProcessControlBlock_t *tempPcb = malloc(sizeof(ProcessControlBlock_t));     // Create tempPCB to use in for loop later
    
    int arrival_time[numProcesses];                                             // Array to hold arrival times
    int burst_time[numProcesses];                                               // Array to hold burst times
    int wait_time[numProcesses];                                                // Array to hold wait times
    int turnaround_time[numProcesses];                                          // Array to hold turnaround times
    int trt = 0;                                                                // Temp total runtime variable
    bool done = false;                                                          // Flag to check if all processes are done

    //void  *const voidPcbPtr = malloc(sizeof(ProcessControlBlock_t));            // put the first pcb to the end of the array so the array is out of order
    //dyn_array_extract_front(ready_queue, voidPcbPtr);
    //dyn_array_push_back(ready_queue, voidPcbPtr);
    
    if(!sort_arrival_times(ready_queue)){                                       // sort the ready queue based on arrival times, from lowest to highest
        return false;
    }
    
    for(int i = 0; i < numProcesses; i++){                                      // Populate burst and arrival time arrays
        tempPcb = dyn_array_at(ready_queue, i);
        burst_time[i] = tempPcb->remaining_burst_time;
        arrival_time[i] = tempPcb->arrival;
    }
    
    while (trt < arrival_time[0]) { trt++; }                                    // Increment timer until first process is ready
    
    while (!done) {                                                             // While there are PCBs left to process                                                                  
        for (int i = 0; i < numProcesses; i++){                                 // Loop through each PCB in ready_queue
            tempPcb = dyn_array_at(ready_queue, i);
            if (arrival_time[i] <= trt){                                        // If the process has actually arrived
                if (tempPcb->remaining_burst_time > 0) {                        // If the process has time left
                    for (size_t j = 0; j < quantum; j++){                       // Run the process for the amount of time specified by the quantum
                        virtual_cpu(tempPcb);
                        trt++;                                                  // Increment clock
                        if (tempPcb->remaining_burst_time == 0){                // If the process is finished
                            turnaround_time[i] = trt - arrival_time[i];         // Calculate turnaround time
                        }
                    }
                }
            }
            else {                                                              // If the next process to be ran has not arrived yet,
                trt++;                                                          // Increment time
                break;                                                          // Restart outermost for loop
            }
        }
        done = true;
        for (int i = 0; i < numProcesses; i++){                                 // Check if there are any processes left to be run
            tempPcb = dyn_array_at(ready_queue, i);
            if (tempPcb->remaining_burst_time > 0){
                done = false;
                break;
            }
        }
    }
    
    total_rt = (unsigned long)trt;
    
    for (int i = 0; i < numProcesses; i++){                                     // Populate wait time arrays
        wait_time[i] = turnaround_time[i] - burst_time[i];
    }
    
    for (int i = 0; i < numProcesses; i++){                                     // Sum the wait and turnaround times
        avg_wait += wait_time[i];
        avg_turn += turnaround_time[i];
    }
    
    avg_wait /= numProcesses;                                                   // Calculate and report the averages
    avg_turn /= numProcesses;
    //printf("Average Waiting Time: %f\n",avg_wait);
    //printf("Average Turnaround Time: %f\n",avg_turn);
    //printf("Total Run Time: %ld\n",total_rt);
    
    //VALUES to be a part of the result set
    result->average_waiting_time = avg_wait;
    result->average_turnaround_time = avg_turn;
    result->total_run_time = total_rt;
    
    return true;                                                                // Report successful round robin
    
}

/*******************************************************************************
    END ROUND ROBIN BLOCK
*******************************************************************************/

/*******************************************************************************
    LOAD PCB BLOCK
*******************************************************************************/

// Reads the PCB burst time values from the binary file into ProcessControlBlock_t remaining_burst_time field
// for N number of PCB burst time stored in the file.
// \param input_file the file containing the PCB burst times
// \return a populated dyn_array of ProcessControlBlocks if function ran successful else NULL for an error
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

/*******************************************************************************
    END LOAD PCB BLOCK
*******************************************************************************/

/*******************************************************************************
    SRTF BLOCK
*******************************************************************************/

// Source: https://www.studytonight.com/operating-system/shortest-remaining-time-first-scheduling-algorithm
// Runs the Shortest Remaining Time First Process Scheduling algorithm over the incoming ready_queue
// \param ready queue a dyn_array of type ProcessControlBlock_t that contain be up to N elements
// \param result used for shortest job first stat tracking \ref ScheduleResult_t
// \return true if function ran successful else false for an error
bool shortest_remaining_time_first(dyn_array_t *ready_queue, ScheduleResult_t *result) 
{
    //Error handling   
    if(ready_queue == NULL || result == NULL)
    {
        return false;
    }
    
    int numProcesses = dyn_array_size(ready_queue);
    int origNumProcesses = numProcesses;
    ProcessControlBlock_t *tempPcb = malloc(sizeof(ProcessControlBlock_t));
    ProcessControlBlock_t *minPcb = malloc(sizeof(ProcessControlBlock_t));
    
    // sort based on burst times, from lowest to highest
    if(!sort_arrival_times(ready_queue)){
        return false;
    }
    unsigned long trt = 0;                                                      // total run time
    float totalWaitTime = 0;
    tempPcb = dyn_array_at(ready_queue, 0);
    trt += tempPcb->arrival;                                                    // add the first arrival time to the total run time in case the first arrival time is not zero

    int i = 0;
    //for(int i = 0; i < origNumProcesses; i++){                                  // loop through each element of the ready queue and run its process
    while(numProcesses > 0){
    //for(int i = 0; i < 100; i++){
        tempPcb = dyn_array_at(ready_queue, 0);
        uint32_t minBurstTime = tempPcb->remaining_burst_time;
        uint32_t minBurstIndex = 0;
        for(int j = 0; j < numProcesses; j++){
            tempPcb = dyn_array_at(ready_queue, j);
            if(tempPcb->arrival <= (uint32_t)trt){                              // find the process with the lowest burst time from among the processes that have already arrived
                //if(i == 0){
                //    printf("priority: %d\n", tempPcb->priority);
                //}
                if(tempPcb->remaining_burst_time < minBurstTime){
                    minBurstTime = tempPcb->remaining_burst_time;
                    minBurstIndex = j;
                }
            }
        }// for loop to find min burst time process
        //if(i == 0){
        //    printf("min burst index: %d\n", minBurstIndex);
       //}
        dyn_array_extract(ready_queue, minBurstIndex, minPcb);                  // remove the pcb with the lowest remaining burst time and assign it to min pcb, but don't destroy the pcb, in case we need to
                                                                                // add it back into the queue to continue decrementing its burst time later
        numProcesses = numProcesses-1;
        
        for(int m = 0; m<numProcesses; m++){                                    // increment waiting time for each process that has arrived but is not running
            tempPcb = dyn_array_at(ready_queue, m);
            if(tempPcb->arrival <= trt){
                totalWaitTime++;
            }
        }
        trt++;
        minPcb->remaining_burst_time--;                                         // decrement the minPcb burst time by one on each iteration of the loop, then we will go back and check if a 
                                                                                // pcb with a lower burst time has arrived
        if(minPcb->remaining_burst_time > 0){                                  // insert the pcb with the lowest burst time back into the ready queue if the process hasn't finished running
            dyn_array_insert(ready_queue, minBurstIndex, minPcb);
            numProcesses = numProcesses+1;
        }
        //printf("Num Processes: %d\n", numProcesses);                          // print statements used for debugging
        //printf("Min Process Priority: %d\n", minPcb->priority);
        i++;
    }// outer for loop
    
    float avwt = totalWaitTime/origNumProcesses;
    float avtat = (totalWaitTime + trt)/origNumProcesses;
    
    //printf("SRTF total time: %ld\n", trt);
    //printf("SRTF average turnaround time: %f\n", avtat);
    //printf("SRTF average wait time: %f\n", avwt);
    
    result->average_waiting_time = avwt;
    result->average_turnaround_time = avtat;
    result->total_run_time = trt;
    
    return true;   
}

/*******************************************************************************
    END SRTF BLOCK
*******************************************************************************/

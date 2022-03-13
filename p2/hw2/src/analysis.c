#include <stdio.h>
#include <stdlib.h>

#include "dyn_array.h"
#include "processing_scheduling.h"

#define FCFS "FCFS"
#define SRTF "SRTF"
#define RR "RR"
#define SJF "SJF"

// Add and comment your analysis code in this function.
// THIS IS NOT FINISHED.
int main(int argc, char **argv) 
{
    if (argc < 3) 
    {
        printf("%s <pcb file> <schedule algorithm> [quantum]\n", argv[0]);
        return EXIT_FAILURE;
    }

    dyn_array_t* ready_queue = load_process_control_blocks(argv[1]);                // Populate the ready queue
    
    ScheduleResult_t* result = (ScheduleResult_t*)malloc(sizeof(ScheduleResult_t)); // Perpare results struct
    
    if(strcmp("FCFS", argv[2]) == 0){                                               // Run FCFS if requested
        printf("FCFS running...\n");
        first_come_first_serve(ready_queue, result);
    }
    else if(strcmp("SRTF", argv[2]) == 0){                                          // Run SRTF if requested
        printf("SRTF running...\n");
        shortest_remaining_time_first(ready_queue, result);
    }
    else if(strcmp("RR", argv[2]) == 0){                                            // Run round robin if requested
        if(strlen(argv[3]) > 0){
            printf("RR running...\n");
            round_robin(ready_queue, result, atoi(argv[3]));
        }
        else{
            printf("Must provide quantum to run round robin.\n");
            return EXIT_FAILURE;
        }
    }
    else if(strcmp("SJF", argv[2]) == 0){                                           // Run SJF if requested
        printf("SJF running...\n");
        shortest_job_first(ready_queue, result);
    }
    else{                                                                           // Fail if incorrect params
        printf("Incorrect parameters.\n");
        return EXIT_FAILURE;
    }
    
    printf("\nAverage waiting time: %f\n", result->average_waiting_time);           // Report results
    printf("Average turnaround time: %f\n", result->average_turnaround_time);
    printf("Total run time: %ld\n", result->total_run_time);
    
    dyn_array_destroy(ready_queue);                                                 // Free allocations
    free(result);
    
    return EXIT_SUCCESS;                                                            // Report success
}

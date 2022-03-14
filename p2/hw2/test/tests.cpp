#include <fcntl.h>
#include <stdio.h>
#include "gtest/gtest.h"
#include <pthread.h>
#include "../include/processing_scheduling.h"

// Using a C library requires extern "C" to prevent function managling
extern "C" 
{
#include <dyn_array.h>
}


#define NUM_PCB 30
#define QUANTUM 5 // Used for Robin Round for process as the run time limit

unsigned int score;
unsigned int total;

class GradeEnvironment : public testing::Environment 
{
    public:
        virtual void SetUp() 
        {
            score = 0;
            total = 210;
        }

        virtual void TearDown()
        {
            ::testing::Test::RecordProperty("points_given", score);
            ::testing::Test::RecordProperty("points_total", total);
            std::cout << "SCORE: " << score << '/' << total << std::endl;
        }
};

/*******************************************************************************
    FCFS TESTING BLOCK
*******************************************************************************/

//First written TEST (11:40ish on video)
TEST(first_come_first_serve, NullParams)
{
    bool ret = first_come_first_serve(NULL,NULL);
    bool expected = false;
    EXPECT_EQ(ret,expected);
    if(ret == expected)
    {
        score = score + 10;
    }
}

// Ensures FCFS works with good parameters
TEST(first_come_first_serve, GoodParams)
{
    // create necessary structs
    dyn_array_t * dyn_arr = load_process_control_blocks("pcb.bin");
    ScheduleResult_t *stats = (ScheduleResult_t*)malloc(sizeof(ScheduleResult_t));
    
    // run fcfs and check if it was successful
    bool ret = first_come_first_serve(dyn_arr ,stats);
    bool expected = true;
    EXPECT_EQ(ret,expected);
    
    // Hand-calculated values
    unsigned long expectedRunTime = 50;
    float expectedAvgWait = 16;
    float expectedAvgTurnaround = 28.5;
    
    // check values are as expected
    EXPECT_EQ(stats->total_run_time, expectedRunTime);
    EXPECT_EQ(stats->average_waiting_time, expectedAvgWait);
    EXPECT_EQ(stats->average_turnaround_time, expectedAvgTurnaround);
    
    if(ret == expected)
    {
        score = score + 10;
    }
}

/*******************************************************************************
    END OF FCFS TESTING BLOCK
*******************************************************************************/

/*******************************************************************************
    SJF TESTING BLOCK
*******************************************************************************/

// Ensure SJF returns false with null params
TEST(shortest_job_first, BadParams){
    bool ret = shortest_job_first(NULL,NULL);
    bool expected = false;
    EXPECT_EQ(ret,expected);
    if(ret == expected)
    {
        score = score + 10;
    }
}

// Ensure SJF works with good params
TEST(shortest_job_first, GoodParams)
{
    int numProcesses = 4;
    // create a pcb array to store the queue of processes to be tested
    ProcessControlBlock_t * pcb_arr = (ProcessControlBlock_t*)malloc(numProcesses*sizeof(ProcessControlBlock_t));
    ScheduleResult_t *stats = (ScheduleResult_t*)malloc(sizeof(ScheduleResult_t));
    
    // populate the pcb array with the same values from the pcb.bin file 
    pcb_arr[0].remaining_burst_time = 15;
    pcb_arr[0].priority = 0;
    pcb_arr[0].arrival = 0;
    
    pcb_arr[1].remaining_burst_time =10;
    pcb_arr[1].priority = 0;
    pcb_arr[1].arrival = 1;
    
    pcb_arr[2].remaining_burst_time =5;
    pcb_arr[2].priority = 0;
    pcb_arr[2].arrival = 2;
    
    pcb_arr[3].remaining_burst_time =20;
    pcb_arr[3].priority = 0;
    pcb_arr[3].arrival = 3;
    
    // create a dynamic array to store the pcb array
    struct dyn_array *dyn_arr = dyn_array_create(numProcesses, sizeof(ProcessControlBlock_t), NULL);
    
    // import the pcb array to a new dynamic array
    dyn_arr = dyn_array_import(pcb_arr, numProcesses, sizeof(ProcessControlBlock_t), NULL);
    
    // run the shortest job first algorithm
    bool ret = shortest_job_first(dyn_arr, stats);
    bool expected = true;
    EXPECT_EQ(ret,expected);
    
    // Hand-calculated values
    unsigned long expectedRunTime = 50;
    float expectedAvgWait = 14.75;
    float expectedAvgTurnaround = 27.25;
    
    // check that the statistic of the total run time match the expected values
    EXPECT_EQ(stats->total_run_time, expectedRunTime);
    EXPECT_EQ(stats->average_waiting_time, expectedAvgWait);
    EXPECT_EQ(stats->average_turnaround_time, expectedAvgTurnaround);
    if(ret == expected)
    {
        score = score + 10;
    }
}

/*******************************************************************************
    END OF SJF TESTING BLOCK
*******************************************************************************/

/*******************************************************************************
    ROUND ROBIN TESTING BLOCK
*******************************************************************************/

// Ensure round robin returns false with bad params
TEST (round_robin, BadParams) {
    bool result = round_robin(NULL, NULL, -1);
    bool expected = false;
    EXPECT_EQ(result,expected);
    if (result == expected) {
        score += 10;
    }
}

// Ensure round robin works with good params
TEST (round_robin, GoodParams) {
    // create necessary structs
    dyn_array_t * dyn_arr = load_process_control_blocks("pcb.bin");
    ScheduleResult_t *stats = (ScheduleResult_t*)malloc(sizeof(ScheduleResult_t));
    
    // run RR and check if successful
    bool ret = round_robin(dyn_arr, stats, QUANTUM);
    bool expected = true;
    EXPECT_EQ(ret,expected);
    
    // Check to make sure queue is in ascending order by arrival times
    int arrSize = dyn_array_size(dyn_arr);
    void  *const voidPcbPtr = malloc(sizeof(ProcessControlBlock_t));
    ProcessControlBlock_t* pcbPtr;
    int prevArrivalTime = 0;
    
    for(int i = 0; i < arrSize; i++){
        dyn_array_extract_front(dyn_arr, voidPcbPtr);
        pcbPtr = (ProcessControlBlock_t*)voidPcbPtr;
        const int arrivalTime = pcbPtr->arrival;
        //printf("Arrival time %d: %d\n", i, arrivalTime);
        // check queue is sorted in order of arrival times
        EXPECT_EQ((arrivalTime >= prevArrivalTime) ,1);
    }
    
    // Hand-calculated values
    unsigned long expectedRunTime = 50;
    float expectedAvgWait = 19.75;
    float expectedAvgTurnaround = 32.25;
    
    // check that values are as expected
    EXPECT_EQ(stats->total_run_time, expectedRunTime);
    EXPECT_EQ(stats->average_waiting_time, expectedAvgWait);
    EXPECT_EQ(stats->average_turnaround_time, expectedAvgTurnaround);
    
    if(ret == expected)
    {
        score = score + 10;
    }
}

/*******************************************************************************
    END OF ROUND ROBIN TESTING BLOCK
*******************************************************************************/

/*******************************************************************************
    LOAD PCB TESTING BLOCK
*******************************************************************************/

// Ensure load_process_control_blocks returns null for null parameters
TEST (load_process_control_blocks, nullParameters) {
    dyn_array_t* dynArr = load_process_control_blocks(NULL);
    ASSERT_EQ(dynArr,(dyn_array_t*) NULL);
    
    score += 10;
}

// Ensure load pcb works with good params
TEST(load_proccess_control_block, GoodParams)
{
    // run load_pcb
    dyn_array_t * dyn_arr = load_process_control_blocks("pcb.bin");
    
    void  *const voidPcbPtr = malloc(sizeof(ProcessControlBlock_t));
    dyn_array_extract_front(dyn_arr, voidPcbPtr);
    ProcessControlBlock_t* pcbPtr = (ProcessControlBlock_t*)voidPcbPtr;

    // check that first process loaded as expected
    const int a = pcbPtr->remaining_burst_time;
    const int b = pcbPtr->priority;
    const int c = pcbPtr->arrival;
    EXPECT_EQ(a, 15);
    EXPECT_EQ(b, 0);
    EXPECT_EQ(c, 0);
    
    dyn_array_extract_front(dyn_arr, voidPcbPtr);
    pcbPtr = (ProcessControlBlock_t*)voidPcbPtr;
    
    // check that second process loaded as expected
    const int a1 = pcbPtr->remaining_burst_time;
    const int b1 = pcbPtr->priority;
    const int c1 = pcbPtr->arrival;
    EXPECT_EQ(a1, 10);
    EXPECT_EQ(b1, 0);
    EXPECT_EQ(c1, 1);
    
    dyn_array_extract_front(dyn_arr, voidPcbPtr);
    pcbPtr = (ProcessControlBlock_t*)voidPcbPtr;
    
    // check that third process loaded as expected
    const int a2 = pcbPtr->remaining_burst_time;
    const int b2 = pcbPtr->priority;
    const int c2 = pcbPtr->arrival;
    EXPECT_EQ(a2, 5);
    EXPECT_EQ(b2, 0);
    EXPECT_EQ(c2, 2);
    
    dyn_array_extract_front(dyn_arr, voidPcbPtr);
    pcbPtr = (ProcessControlBlock_t*)voidPcbPtr;
    
    // check that fourth process loaded as expected
    const int a3 = pcbPtr->remaining_burst_time;
    const int b3 = pcbPtr->priority;
    const int c3 = pcbPtr->arrival;
    EXPECT_EQ(a3, 20);
    EXPECT_EQ(b3, 0);
    EXPECT_EQ(c3, 3);

    score = score + 10;
}

/*******************************************************************************
    END OF LOAD PCB TESTING BLOCK
*******************************************************************************/

/*******************************************************************************
    SRTF TESTING BLOCK
*******************************************************************************/

// Ensure srtf returns false with null params
TEST(shortest_remaining_time_first, NullParams)
{
    bool ret = shortest_remaining_time_first(NULL,NULL);
    bool expected = false;
    EXPECT_EQ(ret, expected);
    if(ret == expected)
    {
        score += 10;
    }
}

// Ensure srtf returns false with null ready queue
TEST(shortest_remaining_time_first, NullReadyQ)
{
    dyn_array_t* d = NULL;
    ScheduleResult_t *s = new ScheduleResult_t;
    bool ret = shortest_remaining_time_first(d,s);
    bool expected = false;
    EXPECT_EQ(ret, expected);
    if(ret == expected)
    {
        score += 10;
    }
}

// Ensure srtf returns false with null result
TEST(shortest_remaining_time_first, NullResult)
{
    dyn_array_t* d = dyn_array_create(0,sizeof(ProcessControlBlock_t),NULL);
    ScheduleResult_t *s = NULL;
    bool ret = shortest_remaining_time_first(d,s);
    bool expected = false;
    EXPECT_EQ(ret, expected);
    if(ret == expected)
    {
        score += 10;
    }
}

TEST(shortest_remaining_time_first, GoodParams){
    int numProcesses = 4;
    // create a pcb array to store the queue of processes to be tested
    ProcessControlBlock_t * pcb_arr = (ProcessControlBlock_t*)malloc(numProcesses*sizeof(ProcessControlBlock_t));
    ScheduleResult_t *stats = (ScheduleResult_t*)malloc(sizeof(ScheduleResult_t));
    
    // populate the pcb array with the same values from the pcb.bin file 
    pcb_arr[0].remaining_burst_time = 15;
    pcb_arr[0].priority = 0;
    pcb_arr[0].arrival = 0;
    
    pcb_arr[1].remaining_burst_time =10;
    pcb_arr[1].priority = 1;
    pcb_arr[1].arrival = 1;
    
    pcb_arr[2].remaining_burst_time =5;
    pcb_arr[2].priority = 2;
    pcb_arr[2].arrival = 2;
    
    pcb_arr[3].remaining_burst_time =20;
    pcb_arr[3].priority = 3;
    pcb_arr[3].arrival = 3;
    
    // create a dynamic array to store the pcb array
    struct dyn_array *dyn_arr = dyn_array_create(numProcesses, sizeof(ProcessControlBlock_t), NULL);
    
    // import the pcb array to a new dynamic array
    dyn_arr = dyn_array_import(pcb_arr, numProcesses, sizeof(ProcessControlBlock_t), NULL);
    
    bool ret = shortest_remaining_time_first(dyn_arr ,stats);
    bool expected = true;
    EXPECT_EQ(ret,expected);
    
    unsigned long expectedRunTime = 50;
    float expectedAvgWait = 11.75;
    float expectedAvgTurnaround = 24.25;
    
    EXPECT_EQ(stats->total_run_time, expectedRunTime);
    EXPECT_EQ(stats->average_waiting_time, expectedAvgWait);
    EXPECT_EQ(stats->average_turnaround_time, expectedAvgTurnaround);
    
    if(ret == expected)
    {
        score += 10;
    }
}

/*******************************************************************************
    END OF SRTF TESTING BLOCK
*******************************************************************************/


int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::AddGlobalTestEnvironment(new GradeEnvironment);
    return RUN_ALL_TESTS();
}

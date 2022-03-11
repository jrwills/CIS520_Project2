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

TEST(first_come_first_serve, GoodParams)
{
    dyn_array_t * dyn_arr = load_process_control_blocks("pcb.bin");
    ScheduleResult_t *stats = (ScheduleResult_t*)malloc(sizeof(ScheduleResult_t));
    
    bool ret = first_come_first_serve(dyn_arr ,stats);
    bool expected = true;
    EXPECT_EQ(ret,expected);
    
    int arrSize = dyn_array_size(dyn_arr);
    void  *const voidPcbPtr = malloc(sizeof(ProcessControlBlock_t));
    ProcessControlBlock_t* pcbPtr;
    int prevArrivalTime = 0;
    
    for(int i = 0; i < arrSize; i++){
        dyn_array_extract_front(dyn_arr, voidPcbPtr);
        pcbPtr = (ProcessControlBlock_t*)voidPcbPtr;
        const int arrivalTime = pcbPtr->arrival;
        printf("Arrival time %d: %d\n", i, arrivalTime);
        // check queue is sorted in order of arrival times
        EXPECT_EQ((arrivalTime >= prevArrivalTime) ,1);
    }
    
    // Hand-calculated values
    unsigned long expectedRunTime = 50;
    float expectedAvgWait = 17.5;
    float expectedAvgTurnaround = 30;
    
    EXPECT_EQ(stats->total_run_time, expectedRunTime);
    EXPECT_EQ(stats->average_waiting_time, expectedAvgWait);
    EXPECT_EQ(stats->average_turnaround_time, expectedAvgTurnaround);
    
    if(ret == expected)
    {
        score = score + 10;
    }
}

TEST(load_proccess_control_block, GoodParams)
{
    dyn_array_t * dyn_arr = load_process_control_blocks("pcb.bin");
    
    int arrSize = dyn_array_size(dyn_arr);
    int capacity = dyn_array_capacity(dyn_arr);
    printf("dyn arr size: %d\n", arrSize);
    printf("dyn arr capacity: %d\n", capacity);
    
    //printf("Burst time 0: %d", dyn_arr->array[0]->remaining_burst_time);
    void  *const voidPcbPtr = malloc(sizeof(ProcessControlBlock_t));
    dyn_array_extract_front(dyn_arr, voidPcbPtr);
    ProcessControlBlock_t* pcbPtr = (ProcessControlBlock_t*)voidPcbPtr;
    //printf("Burst Time 0: %d\n",pcbPtr->remaining_burst_time);
    const int a = pcbPtr->remaining_burst_time;
    const int b = pcbPtr->priority;
    const int c = pcbPtr->arrival;
    EXPECT_EQ(a, 15);
    EXPECT_EQ(b, 0);
    EXPECT_EQ(c, 0);
    
    arrSize = dyn_array_size(dyn_arr);
    printf("dyn arr size: %d\n", arrSize);
    
    dyn_array_extract_front(dyn_arr, voidPcbPtr);
    pcbPtr = (ProcessControlBlock_t*)voidPcbPtr;
    
    const int a1 = pcbPtr->remaining_burst_time;
    const int b1 = pcbPtr->priority;
    const int c1 = pcbPtr->arrival;
    EXPECT_EQ(a1, 10);
    EXPECT_EQ(b1, 0);
    EXPECT_EQ(c1, 1);
    
    dyn_array_extract_front(dyn_arr, voidPcbPtr);
    pcbPtr = (ProcessControlBlock_t*)voidPcbPtr;
    
    const int a2 = pcbPtr->remaining_burst_time;
    const int b2 = pcbPtr->priority;
    const int c2 = pcbPtr->arrival;
    EXPECT_EQ(a2, 5);
    EXPECT_EQ(b2, 0);
    EXPECT_EQ(c2, 2);
    
    dyn_array_extract_front(dyn_arr, voidPcbPtr);
    pcbPtr = (ProcessControlBlock_t*)voidPcbPtr;
    
    const int a3 = pcbPtr->remaining_burst_time;
    const int b3 = pcbPtr->priority;
    const int c3 = pcbPtr->arrival;
    EXPECT_EQ(a3, 20);
    EXPECT_EQ(b3, 0);
    EXPECT_EQ(c3, 3);
    
    arrSize = dyn_array_size(dyn_arr);
    printf("dyn arr size: %d\n", arrSize);

    score = score + 10;
}


int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::AddGlobalTestEnvironment(new GradeEnvironment);
    return RUN_ALL_TESTS();
}

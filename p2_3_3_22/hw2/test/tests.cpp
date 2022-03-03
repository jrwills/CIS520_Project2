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
//----------------------------------------------------------------------------------------------//
//First written TEST (11:40ish on DEMO video)
TEST(first_come_first_serve, NullParams)
{
    bool ret = first_come_first_serve(NULL,NULL);
    bool expected = false;
    EXPECT_EQ(ret,expected);
    if(ret == expected)
    {
        score = score + 10; //purpose of score??
    }
}

TEST(shortest_job_first, NullParams)
{
    bool ret = shortest_job_first(NULL,NULL);
    bool expected = false;
    EXPECT_EQ(ret,expected);
    if(ret == expected)
    {
        score = score + 10; //purpose of score??
    }
}

TEST(shortest_job_first, NullReadyQ)
{
    dyn_array_t* d = NULL;
    ScheduleResult_t *s = new ScheduleResult_t;
    bool ret = shortest_job_first(d,s);
    bool expected = false;
    EXPECT_EQ(ret, expected);
    if(ret == expected)
    {
        score += 10;
    }
}
//-----------------------------------------------------------------------------------------------//
int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::AddGlobalTestEnvironment(new GradeEnvironment);
    return RUN_ALL_TESTS();
}

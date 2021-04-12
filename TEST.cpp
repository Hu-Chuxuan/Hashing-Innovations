#include <ctime>                /* For performance comparasion */
#include "hashset_f.h"
#include "hash_extend_f.h"


//
// Test Cases & Algorithm Comparisons
//  
//
//  Created by Hu Chuxuan on 21.03.21.
//

int main(){
    /******************* Put your own test here *******************/
    /* Your are expected to give adequate test to show the correctness of your implementation */
    /* Otherwise you may be deducted points */

    /**************************************************************/
    /* Check Point 1: Correctness */
    int input1[] = {1, 1, 1, 5, 2};
    int input2[] = {0, 2, 12, 3, 3, 3, 3, 4, 5, 5, 42};

    /*Checking for LCFS*/
    cout << "Below are the tests for LCFS\n ";
    HashSet_LCFS<int> test1, test2;
    //test1 deals with no collision but it eliminates the dublicates
    cout << "----------LCFS Test1---------\n ";
    for(auto i: input1){
        test1.insert(i);
    }
    test1.display();
    //test2 deals with cases with collisions
    //we can see that when collision occurs, the newly inserted element(42) goes to its hash value
    //the original data(2) goes forward for chaining search
    cout << "---------LCFS Test2----------\n ";
    for(auto i: input2){
        test2.insert(i);
    }
    test2.display();


    /*Checking for RH*/
    cout << "Below are the tests for RH\n ";
    HashSet_RH<int> test3, test4;
    //test1 deals with no collision but it eliminates the dublicates
    cout << "----------RH Test1---------\n ";
    for(auto i: input1){
        test3.insert(i);
    }

    //test2 deals with collisions
    //we can see that when collisions occur, the one that is closer from the calculated index will move on
    //specifically, 42 moves from 2 to occupy 3's space, 3 moves on to occupy 4's, 4 moves on to occupy 5's
    //the whole process ends when 5 is stored in an empty place
    cout << "----------RH Test2---------\n ";
    for (auto i:input2){
        test4.insert(i);
    }
    test4.display();



    /*Checking for Comparison to view how they function differently with collisions*/
    //in this case we have a set of numbers whose index are all the same
    //viewing below tests we can clearly see how different methods deal with collisions respectly
    int input3[] = {0, 2, 22, 42, 62, 82, 102};

    cout << "----------Comparison Test for Two Methods---------\n ";
    cout << "-----LCFS-----\n";
    HashSet_LCFS<int> test5;
    for (auto i:input3){
        test5.insert(i);
    }
    test5.display();
    cout << "-----RH-----\n";
    HashSet_RH<int> test6;
    for (auto i:input3){
        test6.insert(i);
    }
    test6.display();




    /**************************************************************/
    /* Check Point 2: Compare the performance with initial hashset as baseline */
    //since their difference mainly lies in dealing with collisions, we will look at how they deal with these
    cout << "----------Comparison Test for Three Hash Implementations---------\n ";
    cout << "------LCFS vs Initial Hashset-----\n";
    //CONCLUSION:
    //The advantage of LCFS that it is easier to check whether the newly inserted data are in the hashtable
    //as we always place the newer ones at their position
    //This is useful because typically the newly inserted data are those of interest

    //we first establish a large array
    int input4[100000];
    for(int i=0;i<100000;i++){
        input4[i]=rand();
    }

    //for initial and LCFS, we both check the newest 1000 data
    //for initial hashset, the execution time is 0.001s
    //for LCFS, execution time is 0s
    //(there might be some variations as the data are all randomly chosen)
    cout << "Initial Hashset:";
    hashset<int> test7;
    clock_t startTime,endTime;
    for (int i=0;i<100000;i++)
    {
         test7.add(input4[i]);
    }
    startTime = clock();
    for(int i=99999;i>=90000;i--){
         test7.member(input4[i]);
    }
    test7.member(input4[99999]);
    endTime = clock();
    cout << "The run time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << "\n";


    cout << "LCFS Hashset:";
    HashSet_LCFS<int> test8(100000);

    for (int i=0;i<100000;i++)
    {
         test8.add(input4[i]);
    }
    startTime = clock();

    for(int i=99999;i>=90000;i--){
    test8.member(input4[i]);
    }
    endTime = clock();
    cout << "The run time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << "\n";





    //CONCLUSION: the advantage of RH is that the average shift from a number to its initial index is smallest
    //thus, we can see that when a large number of data is inserted, on average RH do better

    cout << "-----RH vs Initial Hashset-----\n";

    //we justify our conclusion by creating a large set of data and find that on average RH do better as the data
    //were of smaller distance comparing to the initial hash set
    int input5[50000];
    for(int i=0;i<50000;i++){
        input4[i]=rand();
    }
    cout << "Initial Hashset:";
    hashset<int> test9;
    for (auto i:input5)
    {
         test9.add(i);
    }
    startTime = clock();
    for(auto i:input5){
         test9.member(i);
    }
    endTime = clock();
    cout << "The run time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << "\n";


    cout << "RH Hashset:";
    HashSet_RH<int> test10(50000);
    for (auto i:input5)
    {
         test10.insert(i);
    }
    startTime = clock();
    for (auto i:input5)
    {
         test10.member(i);
    }
    endTime = clock();
    cout << "The run time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << "\n";


    return 0; 
}
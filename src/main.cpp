#include <cstdlib>
#include <iostream>
#include <string>
#include <chrono>
#include <exception>
#include "List.h"

#define TEST_SIZE   1000000
#define REMOVE_SIZE 1000

int main(int argc, char *argv[]){
    auto Start = std::chrono::steady_clock::now();
    CList List, OtherList;
    int LastValue;
    int TestSize = TEST_SIZE;
    int RemoveSize = REMOVE_SIZE;
    
    if(2 <= argc){
        try{
            TestSize = std::stoi(argv[1]);
            if(3 <= argc){
                RemoveSize = std::stoi(argv[2]);
            }
        }
        catch(std::exception &Except){
            std::cerr<<Except.what()<<std::endl;
            return EXIT_FAILURE;
        }
    }
    if(TestSize <= RemoveSize){
        std::cerr<<"Invalid sizes, 0 < RemoveSize < TestSize"<<std::endl;
    }
    
    for(int Index = 0; Index < TestSize; Index++){
        List.PushBack(Index);   
    }
    for(int Index = 0; Index < RemoveSize; Index++){
        List.PopFront();   
    }
    if(List.Count() != TestSize - RemoveSize){
        std::cerr<<"Incorrect count "<<List.Count()<<", expected "<<(TestSize - RemoveSize)<<std::endl;
        return EXIT_FAILURE;
    }
    for(int Index = RemoveSize-1; Index >= 0; Index--){
        List.PushFront(Index);
    }
    LastValue = -1;
    for(auto Value : List){
        if(LastValue + 1 != Value){
            std::cerr<<"Incorrect value "<<Value<<", expected "<<(LastValue+1)<<std::endl;
            return EXIT_FAILURE;
        }
        LastValue = Value;
    }
    while(!List.IsEmpty()){
        OtherList.PushBack(List.Back());
        List.PopBack();
    }
    if(OtherList.Count() != TestSize){
        std::cerr<<"Incorrect count "<<OtherList.Count()<<", expected "<<TestSize<<std::endl;
        return EXIT_FAILURE;
    }
    while(!OtherList.IsEmpty()){
        OtherList.PopFront();
    }
    auto Duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now()-Start);
    std::cout<<Duration.count()<<std::endl;
        
    
    return EXIT_SUCCESS;
}

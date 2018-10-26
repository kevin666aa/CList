#include <gtest/gtest.h>
#include "List.h"

TEST(ListTest, EmptyCountTest){
    CList List;
    
    EXPECT_TRUE(List.IsEmpty());
    EXPECT_EQ(List.Count(), 0);
}

TEST(ListTest, PushNonEmptyTest){
    CList List;
    
    List.PushBack(4);
    EXPECT_FALSE(List.IsEmpty());
    EXPECT_EQ(List.Count(), 1);
    EXPECT_EQ(List.Front(), 4);
    EXPECT_EQ(List.Back(), 4);
    List.PushFront(5);
    EXPECT_FALSE(List.IsEmpty());
    EXPECT_EQ(List.Count(), 2);
    EXPECT_EQ(List.Front(), 5);
    EXPECT_EQ(List.Back(), 4);
}

TEST(ListTest, PushPopTest){
    CList List;
    
    for(int Index = 0; Index < 10; Index++){
        List.PushFront(Index);   
    }
    for(int Index = 0; Index < 10; Index++){
        EXPECT_EQ(List.Back(), Index);
        List.PopBack();
    }
    EXPECT_TRUE(List.IsEmpty());
    for(int Index = 0; Index < 10; Index++){
        List.PushBack(Index);   
    }
    for(int Index = 0; Index < 10; Index++){
        EXPECT_EQ(List.Front(), Index);
        List.PopFront();
    }
    EXPECT_TRUE(List.IsEmpty());
}

TEST(ListTest, ConstIteratorTest){
    CList List;
    int ExpectedDelta = -1;
    int LastValue = 10;
    
    for(int Index = 0; Index < 10; Index++){
        List.PushFront(Index);   
    }
    for(int Index = 1; Index < 10; Index++){
        List.PushBack(Index);   
    }
    EXPECT_EQ(List.Count(), 19);
    
    for(auto Value : List){
        EXPECT_EQ(Value, LastValue + ExpectedDelta);
        LastValue = Value;
        if(0 == Value){
            ExpectedDelta = 1;
        }
    }
}


TEST(ListTest, IteratorTest){
    CList List;
    int ExpectedDelta = -1;
    int LastValue = 10;
    
    for(int Index = 0; Index < 10; Index++){
        List.PushFront(Index);   
    }
    for(int Index = 1; Index < 10; Index++){
        List.PushBack(Index);   
    }
    EXPECT_EQ(List.Count(), 19);
    
    for(auto &Value : List){
        EXPECT_EQ(Value, LastValue + ExpectedDelta);
        LastValue = Value;
        if(0 == Value){
            ExpectedDelta = 1;
        }
        Value *= 2;
    }
    LastValue = 20;
    ExpectedDelta = -2;
    for(auto Value : List){
        EXPECT_EQ(Value, LastValue + ExpectedDelta);
        LastValue = Value;
        if(0 == Value){
            ExpectedDelta = 2;
        }
    }
    CList::iterator Iter = List.begin();
    EXPECT_EQ(*Iter, 18);
    List.PopFront();
    List.PushFront(20);
    EXPECT_EQ(*Iter, 18);
    Iter++;
    EXPECT_TRUE(Iter == List.end());
    
    Iter = List.begin() + (List.Count() - 1);
    EXPECT_EQ(*Iter, 18);
    List.PopBack();
    List.PushBack(20);
    EXPECT_EQ(*Iter, 18);
    Iter--;
    EXPECT_TRUE(Iter == List.end());
}
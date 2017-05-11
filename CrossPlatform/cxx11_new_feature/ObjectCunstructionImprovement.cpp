//
// Created by fayne on 2017/5/9.
//

#include <string>
#include <iostream>
#include <gtest/gtest.h>

// C++11 构造改良特性
class Base
{
public:
    Base(int i,const std::string &str) : i_param1(i),str_param2(str)
    {
        std::cout<<"Base(int i,const std::string &str) constructed.";
    }

    Base(const std::string &str)
    {
        std::cout<<"Base(const std::string &str) constructed.";
    }

    ~Base()
    {
        std::cout<<str_param2<<" Destroied.."<<std::endl;
    }
private:
    int i_param1;
    std::string str_param2;
};

class Drive1 : public Base
{
public:
    using Base::Base;
    Drive1() : Base(1,"Drive1")
    {
        std::cout<<"called by Drive1() : Base(1,\"Drive1\")."<<std::endl;
    }
};

class Drive2 : public Base
{
public:
    Drive2():Base("Drive2")
    {
        std::cout<<"Drive2():Base(\"Drive2\")."<<std::endl;
    }
};

TEST(cxx11_new_feature,ObjectConstructionImprovement)
{
    Drive1 d2;
    Drive1 d1(1265,"Drive1");
    Drive2 d3;
}


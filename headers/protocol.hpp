/**
 * @file protocol.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-23
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once 

#include <string>
#include <vector>

namespace zjy
{
    class Message
    {
    public:
        std::vector<std::string> msg_pool;

    public:
        Message()
        {

        }
        Message(int arg_num, char* arg_data[])
        {
            for (int i = 0; i < arg_num; i++)
            {
                msg_pool.push_back(std::string(arg_data[i]));
            }
        }
        Message(const Message& other)
        {
            msg_pool = other.msg_pool;
        }
        ~Message()
        {

        }

        Message& operator=(const Message& other)
        {
            if (this != &other)
            {
                msg_pool = other.msg_pool;
            }

            return *this;
        }
    };
}  // namespace zjy
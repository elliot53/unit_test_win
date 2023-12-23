/**
 * @file entry.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-23
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once 

#include <winsock2.h>

#include <map>
#include <string>
#include <iostream>
#include <functional>

#include "protocol.hpp"

namespace zjy
{
    int network_unit(Message& msg);
}
#pragma once

// std::bind Wrapper FUNCTION
#define BIND_EVENT_FUNCTION(UserObject, FunctionPtr) std::bind(FunctionPtr, UserObject, std::placeholders::_1)
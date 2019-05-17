#pragma once
#include "ErrorResponse.h"
#include "Communicator.h"
#include "LoginResponse.h"
#include "SignupResponse.h"
#include <vector>
std::vector<char> serializeResponse(ErrorResponse err);
std::vector<char> serializeResponse(LoginResponse login);
std::vector<char> serializeResponse(SignupResponse signup);

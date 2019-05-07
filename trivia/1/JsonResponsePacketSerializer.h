#pragma once
#include "ErrorResponse.h"
#include "Communicator.h"
#include "LoginResponse.h"
#include "SignupResponse.h"
#include <vector>
static std::vector<char> serializeResponse(ErrorResponse);
static std::vector<char> serializeResponse(LoginResponse);
static std::vector<char> serializeResponse(SignupResponse);
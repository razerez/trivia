#pragma once

#include "LoginRequest.h"
#include "SignupRequest.h"


LoginRequest deserializeLoginRequest(int x /*should return buffer*/);
SignupRequest deserializeSignupRequest(int x /*should return buffer*/);


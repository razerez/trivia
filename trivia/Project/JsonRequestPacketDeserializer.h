#pragma once

#include "LoginRequest.h"
#include "SignupRequest.h"

/*
only here this is cant be until we build buffer.
*/
static LoginRequest deserializeLoginRequest(int x /*should return buffer*/);
static SignupRequest deserializeSignupRequest(int x /*should return buffer*/);


#pragma once

#include <vector>
#include "LoginRequest.h"
#include "SignupRequest.h"

/*
only here this is cant be until we build buffer.
*/
static LoginRequest deserializeLoginRequest(std::vector<char> buffer)
{
	LoginRequest myLogin("swe", "wewe");
	return myLogin;
}

static SignupRequest deserializeSignupRequest(std::vector<char> buffer /*should return buffer*/)
{
	SignupRequest mySignup("wef", "ewe", "we");
	return mySignup;
}





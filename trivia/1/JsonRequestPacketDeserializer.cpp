#include "JsonRequestPacketDeserializer.h"

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<char> buffer)
{
	LoginRequest myLogin("swe", "wewe");
	return myLogin;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(std::vector<char> buffer)
{
	SignupRequest mySignup("wef", "ewe", "we");
	return mySignup;
}

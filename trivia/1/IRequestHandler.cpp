#include "IRequestHandler.h"

IRequestHandler::IRequestHandler() :_m_username("",0)
{
}

IRequestHandler::IRequestHandler(LoggedUser username):_m_username(username)
{
}

IRequestHandler::~IRequestHandler()
{
}

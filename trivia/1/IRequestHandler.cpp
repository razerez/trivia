#include "IRequestHandler.h"

IRequestHandler::IRequestHandler() :_m_username("")
{
}

IRequestHandler::IRequestHandler(LoggedUser username):_m_username(username)
{
}

IRequestHandler::~IRequestHandler()
{
}

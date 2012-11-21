/**
 * System for managing message passing between engine sub-systems.
 */
#include "PostMaster.h"

PostMaster::PostMaster()
{

}

PostMaster::PostMaster(const PostMaster& other)
{

}

PostMaster::~PostMaster()
{

}

bool PostMaster::Initialize()
{
	return true;
}

void PostMaster::Shutdown()
{

	return;
}

bool PostMaster::RegisterAsListener()
{
	return true;
}

bool PostMaster::RemoveAsListener()
{
	return true;
}
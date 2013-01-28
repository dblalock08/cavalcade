// VirtualFileSystem.hpp
#pragma once

class VirtualFileSystem
{
public:
	VirtualFileSystem();
	VirtualFileSystem(const VirtualFileSystem&);
	~VirtualFileSystem();

	bool Initialize();
	void Shutdown();

private:

};
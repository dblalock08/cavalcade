#pragma once
/* The post master will maintain a list of objects that are listening for messages,	*/
/* as well as what type of message they are listening for. */
/**/

class PostMaster
{
public:
	PostMaster();
	PostMaster(const PostMaster&);
	~PostMaster();

	bool Initialize();
	void Shutdown();

	bool RegisterAsListener();	// Notify the post master that the object wants to be notified of messages
	bool RemoveAsListener();	// Notify the post master that the object no longer wants to be notified of messages

private:
	// Message queue
	// List of objects listening for messages
};
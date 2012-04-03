#ifndef QLESS_H
#define QLESS_H

#include <string>
#include <vector>
#include <stdint.h>
#include <stdlib.h>
#include <hiredis/hiredis.h>

namespace qless {
	/* This is a wrapper class for the hiredis reply object.
	 * It's meant to abstract away some of the trouble with
	 * freeing the memory associated with that response object,
	 * and is meant to otherwise act exactly as if it were
	 * a response pointer. */
	class _reply_pointer {
		public:
			_reply_pointer(void * r): reply(static_cast<redisReply*>(r)) {};
			~_reply_pointer() { freeReplyObject(reply); }
			_reply_pointer(_reply_pointer& other) {
				reply = other.reply;
				other.reply = NULL;
			}
			
			redisReply& operator* () { return *reply; }
			redisReply* operator->() { return  reply; }
		private:
			const _reply_pointer& operator=(const _reply_pointer& other);
			redisReply * reply;
	};
	
	/* This is a class designed to facilitate the execution
	 * of named lua scripts. Each instance is specific to the
	 * redis instance it's associated with, as it has logic
	 * built in to ensure that the script is loaded properly
	 * on the Redis instance. */
	class lua {
		public:
			lua(redisContext* redis, const std::string& name);
			lua(const lua& other);
			const lua& operator=(const lua& other);
			~lua() {};
			
			_reply_pointer exec(const char* format, ...);
		private:
			redisContext * redis; // This is the redis context we'll use for making all of our requests
			std::string name;     // This is the name of the command
			std::string sha;      // This is the sha corresponding to the lua script that's loaded
	};
}

// Let's include everything else
#include "client.h"
#include "queue.h"

#endif

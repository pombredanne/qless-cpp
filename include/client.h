#ifndef QLESS_CLIENT_H
#define QLESS_CLIENT_H

#include <string>
#include <vector>
#include <stdint.h>
#include <stdlib.h>
#include <hiredis/hiredis.h>

namespace qless {
	/* A qless client is associated with a particular redis
	 * instantiation, and its construction accepts parameters
	 * indicative of the host to connect to. */
	class client {
		public:
			client(const std::string& host, uint32_t port);
			client(const client& other);
			const client& operator=(const client& other);
			~client();
		private:
			redisContext * redis;
	};
}

#endif

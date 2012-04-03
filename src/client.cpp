#include "client.h"

#include <string>

using namespace qless;

client::client(const std::string& host, uint32_t port) {
	// Now for the redis context
	struct timeval timeout = { 1, 500000 };
	redis = redisConnectWithTimeout(host.c_str(), port, timeout);
	if (redis->err) {
		char err[128];
		strcpy(err, redis->errstr);
		redisFree(redis);
		throw err;
	}
}

client::client(const client& other) {
	redis = other.redis;
}

const client& client::operator=(const client& other) {
	redis = other.redis;
	return *this;
}

client::~client() {
	redisFree(redis);
}

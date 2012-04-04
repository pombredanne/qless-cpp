#include "util.h"

#include <cstring>
#include <sstream>

using namespace qless;

/*******************************************
 * The lua class definition
 *******************************************/
lua::lua(redisContext* r, const std::string& n): redis(r), name(n) {
	/* Alright, based on the name, we should load the
	 * appropriate file and make sure that it's loaded
	 * into redis. The returned sha should be stored
	 * and used when invoking it */
}

lua::lua(const lua& other) {
	sha    = other.sha;
	name   = other.name;
	redis  = other.redis;
}

const lua& lua::operator=(const lua& other) {
	sha    = other.sha;
	name   = other.name;
	redis  = other.redis;
	return *this;
}

_reply_pointer lua::exec(const char* format, ...) {
	va_list ap;
	std::ostringstream os;
	
	va_start(ap, format);
	os << "evalsha " << "4cad0f9b5d1ced2d5560e5d0ff583ec86ade7905" << " " << format;
	_reply_pointer r(redisvCommand(redis, os.str().c_str(), ap));
	va_end(ap);
	return r;
}

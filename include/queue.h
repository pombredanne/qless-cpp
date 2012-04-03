#ifndef QLESS_QUEUE_H
#define QLESS_QUEUE_H

#include "qless.h"
#include "job.h"

namespace qless {
	class queue {
		public:
			queue(const std::string& n, client& c): name(n), qc(&c) {};
			queue(const queue& other);
			const queue& operator=(const queue& other);
			~queue() {};
			
			// class Queue(object):
			//     def __init__(self, name, r, worker):
			//         self.name    = name
			//         self.redis   = r
			//         self.worker  = worker
			//         self._hb     = 60
			//         # Our lua functions
			//         self._put       = lua('put'      , self.redis)
			//         self._pop       = lua('pop'      , self.redis)
			//         self._fail      = lua('fail'     , self.redis)
			//         self._peek      = lua('peek'     , self.redis)
			//         self._stats     = lua('stats'    , self.redis)
			//         self._complete  = lua('complete' , self.redis)
			//         self._heartbeat = lua('heartbeat', self.redis)
			// 
			
			
			_reply_pointer put(const std::string& data, unsigned int priority=0,
				const std::vector<std::string>& tags=std::vector<std::string>(),
				unsigned int delay=0, unsigned int retries=3);
			// _reply_pointer put(const job& j);
			
			job pop();
		private:
			std::string name;
			client* qc;
	};
}

#endif

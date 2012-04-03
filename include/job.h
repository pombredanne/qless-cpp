#ifndef QLESS_JOB_H
#define QLESS_JOB_H

#include "qless.h"

namespace qless {
	/* The history class describes when certain events happen to a
	 * job. For instance, when it was put in a queue, when it was
	 * popped, failed, completed, etc. */
	class history {
		public:
			history(const std::string& queue,
				const std::string& worker="",
				unsigned int put=0,
				unsigned int popped=0,
				unsigned int done=0,
				unsigned int failed=0): q(queue), worker(worker), put(put), popped(popped), done(done), failed(failed) {};
			history(const history& h): q(h.q), worker(h.worker), put(h.put), popped(h.popped), done(h.done), failed(h.failed) {};
			~history() {};
			
			const std::string q;
			const std::string worker;
			const unsigned int put;
			const unsigned int popped;
			const unsigned int done;
			const unsigned int failed;
		private:
			const history& operator=(const history& other);
	};
	
	/* The job represents a unit of work. It has certain pieces of
	 * user-configurable data associated with it, including a user-
	 * specified JSON blob, priority, delay, retries, etc. It also
	 * has other attributes that are set by the system. */
	class job {
		public:
			job(const std::string& data,
				unsigned int priority=0,
				const std::vector<std::string>& tags=std::vector<std::string>(),
				unsigned int delay=0,
				unsigned int retries=3): priority(priority), retries(retries), delay(delay), data(data), tags(tags) {};
			job(const job& j): priority(j.priority), retries(j.retries), delay(j.delay), data(j.data), tags(j.tags) {};
			const job& operator=(const job& j) {
				priority = j.priority;
				retries  = j.retries;
				delay    = j.delay;
				data     = j.data;
				tags     = j.tags;
				return *this;
			}
			~job() {};
			
			unsigned int priority;
			unsigned int retries;
			unsigned int delay;
			std::string data;
			std::vector<std::string> tags;
			
			// {
			//     # This is the same id as identifies it in the key. It should be
			//     # a hex value of a uuid
			//     'id'        : 'deadbeef...',
			// 
			//     # This is the priority of the job -- lower means more priority.
			//     # The default is 0
			//     'priority'  : 0,
			// 
			//     # This is the user data associated with the job. (JSON blob)
			//     'data'      : '{"hello": "how are you"}',
			// 
			//     # A JSON array of tags associated with this job
			//     'tags'      : '["testing", "experimental"]',
			// 
			//     # The worker ID of the worker that owns it. Currently the worker
			//     # id is <hostname>-<pid>
			//     'worker'    : 'ec2-...-4925',
			// 
			//     # This is the time when it must next check in
			//     'expires'   : 1352375209,
			// 
			//     # The current state of the job: 'waiting', 'pending', 'complete'
			//     'state'     : 'waiting',
			// 
			//     # The queue that it's associated with. 'null' if complete
			//     'queue'     : 'example',
			// 
			//     # The maximum number of retries this job is allowed per queue
			//     'retries'   : 3,
			//     # The number of retries remaining
			//     'remaining' : 3,
			// 
			//     # A list of all the stages that this node has gone through, and
			//     # when it was put in that queue, given to a worker, which worker,
			//     # and when it was completed. (JSON blob)
			//     'history'   : [
			//         {
			//             'q'     : 'test1',
			//             'put'   : 1352075209,
			//             'popped': 1352075300,
			//             'done'  : 1352076000,
			//             'worker': 'some-hostname-pid'
			//         }, {
			//             ...
			//         }
			//     ]
			// }
		private:
	};
}

#endif

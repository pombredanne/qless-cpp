#ifndef QLESS_JOB_H
#define QLESS_JOB_H

#include <rapidjson/document.h>

#include "util.h"

namespace qless {
	/* The history class describes when certain events happen to a
	 * job. For instance, when it was put in a queue, when it was
	 * popped, failed, completed, etc. */
	class _history {
		public:
			_history(const std::string& queue,
				const std::string& worker="",
				unsigned int put=0,
				unsigned int popped=0,
				unsigned int done=0,
				unsigned int failed=0): q(queue), worker(worker), put(put), popped(popped), done(done), failed(failed) {};
			_history(const _history& h): q(h.q), worker(h.worker), put(h.put), popped(h.popped), done(h.done), failed(h.failed) {};
			~_history() {};
			
			const std::string q;
			const std::string worker;
			const unsigned int put;
			const unsigned int popped;
			const unsigned int done;
			const unsigned int failed;
		private:
			const _history& operator=(const _history& other);
	};
	
	/* The job represents a unit of work. It has certain pieces of
	 * user-configurable data associated with it, including a user-
	 * specified JSON blob, priority, delay, retries, etc. It also
	 * has other attributes that are set by the system. */
	class job {
		public:
			job(unsigned int priority,
				unsigned int retries,
				unsigned int remaining,
				unsigned int expires,
				const std::string& id,
				const std::string& state,
				const std::string& queue,
				const std::string& worker,
				const std::vector<std::string>& tags,
				const std::vector<_history>& history,
				rapidjson::Document data): priority(priority), retries(retries), remaining(remaining), expires(expires), id(id), state(state), queue(queue), worker(worker), tags(tags), history(history), data(data) {};
			job(const job& j): priority(j.priority), retries(j.retries), remaining(j.remaining), expires(j.expires), id(j.id), state(j.state), queue(j.queue), worker(j.worker), tags(j.tags), history(j.history), data(j.data) {}
			~job() {};
			
			/* This is a helper method to parse out a JSON blob response and 
			 * return the corresponding job object */
			static job parse(const std::string& j);
			
			const unsigned int priority;         // The job's priority
			const unsigned int retries;          // The number of retries it gets per queue
			const unsigned int remaining;        // The number of retries remaining
			const unsigned int expires;          // The time when the lock expires (heartbeat-by time)
			const std::string id;                // The job's id
			const std::string state;             // The job's state
			#warning "Consider using an enum for the state"
			const std::string queue;             // The queue the job's associated with
			const std::string worker;            // The worker handling the job
			std::vector<std::string> tags;       // The tags this job has
			const std::vector<_history> history; // A history of what's happened to this job
			rapidjson::Document data;            // The JSON data associated with the job
		private:
			const job& operator=(const job& j);
	};
}

#endif

#include "job.h"

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>	// for stringify JSON
#include <rapidjson/filestream.h>	// wrapper of C stream for prettywriter as output
#include <cstdio>

using namespace qless;
using namespace rapidjson;

job job::parse(const std::string& j) {
	/* This is the representation of the job */
	Document _job;
	if (_job.Parse<0>(j.c_str()).HasParseError()) {
		throw "Invalid JSON from qless";
	}
	
	/* This is the rapidjson document for the job's data */
	Document _data;
	if (_data.Parse<0>(_job["data"].GetString()).HasParseError()) {
		throw "Job has invalid JSON data";
	}

	#warning "Need to parse tags correctly"
	#warning "Need to parse history correctly"
	return job(
		static_cast<unsigned int>(_job["priority"].GetInt()),
		static_cast<unsigned int>(_job["retries"].GetInt()),
		static_cast<unsigned int>(_job["remaining"].GetInt()),
		static_cast<unsigned int>(_job["expires"].GetInt()),
		_job["id"].GetString(),
		_job["state"].GetString(),
		_job["queue"].GetString(),
		_job["worker"].GetString(),
		std::vector<std::string>(),
		std::vector<_history>(),
		_data);
}
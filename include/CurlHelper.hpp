#ifndef CURLHELPER_HPP
#define CURLHELPER_HPP
#include <string>
#include <utility>

namespace CurlHelper
{
	extern std::string buffer;

	// Helper function store curl output in string
	size_t writeToString(void *ptr, size_t size, size_t nmemb, void *stream);
	// Simple post with parameters. Returns a pair with the response of the called url as first parameter
	// and true as its second parameter if the post was successful
	std::pair<std::string, bool> simplePost(std::string url, std::string postFields);
}

#endif // CURLHELPER_HPP

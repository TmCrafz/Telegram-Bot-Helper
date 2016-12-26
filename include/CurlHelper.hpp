#ifndef CURLHELPER_HPP
#define CURLHELPER_HPP
#include <string>

namespace CurlHelper
{
	extern std::string buffer;

	// Helper function store curl output in string
	size_t writeToString(void *ptr, size_t size, size_t nmemb, void *stream);
	// Simple post with parameters. Returns the response of the called url
	std::string simplePost(std::string url, std::string postFields);
	
	
}

#endif // CURLHELPER_HPP

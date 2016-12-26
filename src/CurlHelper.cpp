#include "../include/CurlHelper.hpp"
#include <curl/curl.h>
#include <iostream>

std::string CurlHelper::buffer;

size_t CurlHelper::writeToString(void *ptr, size_t size, size_t nmemb, void *stream)
{
	buffer.append((char*) ptr, size * nmemb);
	return size*nmemb;
}

std::string CurlHelper::simplePost(std::string url, std::string postFields)
{
	// Remove old content from buffer
	buffer.clear();

	CURL *curl;
	CURLcode res;
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	if (curl)
	{
		// Set url (http:// or https://)
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());	
		// Specify POST data
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields.c_str());
		// Use helper function to store output in std::string
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeToString);
		// Perfom request. (Store return code in res)
		res = curl_easy_perform(curl);
		if (res != CURLE_OK)
		{
			std::cerr << "curl_easy_perfom failed: " << curl_easy_strerror(res) << std::endl;
		}
		// Clean up
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
	return buffer;
}

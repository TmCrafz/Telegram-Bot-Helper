#include "../include/CurlHelper.hpp"
#include <curl/curl.h>
#include <iostream>
#include <sstream>

size_t CurlHelper::writeDataToStrStream(char *ptr, size_t size, size_t nmemb, void *userdata)
{
	std::ostringstream *stream = (std::ostringstream*) userdata;
	size_t count = size * nmemb;
	stream->write(ptr, count);
	return count;
}

std::pair<std::string, bool> CurlHelper::simplePost(const std::string &url, const std::string &postFields)
{
	bool success{ false };
	// Remove old content from buffer
	//buffer.clear();
	
	curl_global_init(CURL_GLOBAL_ALL);
	CURL *curl{ curl_easy_init() };
	// Stream where to store result data
	std::ostringstream stream;
	if (curl)
	{
		// Set url (http:// or https://)
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());	
		// Specify POST data
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields.c_str());

		// Use helper function to store output in string stream
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeDataToStrStream);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &stream);
		// Perfom request. (Store return code in res)
		CURLcode res{ curl_easy_perform(curl) };
		success = res == CURLE_OK;
		if (!success)
		{
			std::cerr << "curl_easy_perfom failed: " << curl_easy_strerror(res) << std::endl;
		}
		// Clean up
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
	return std::make_pair(stream.str(), success);
}


std::pair<std::string, bool> CurlHelper::fileFormPost(const std::string &url, const std::string &fieldName, 
		const std::string &fileName)
{
	bool success{ false };
	
	curl_global_init(CURL_GLOBAL_ALL);

	curl_httppost *formpost{ nullptr };
	curl_httppost *lastptr{ nullptr };
	// Fill file field
	curl_formadd(&formpost,
               &lastptr,
               CURLFORM_COPYNAME, fieldName.c_str(),
			   // Path to the file to upload
               CURLFORM_FILE, fileName.c_str(),
               CURLFORM_END);

	
	CURL *curl = { curl_easy_init() };
	// Stream where to store result data
	std::ostringstream stream;
	if (curl)
	{
		// Set url (http:// or https://)
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

		// Use helper function to store output in string stream
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeDataToStrStream);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &stream);
		// Set the form post data
		curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
		// Perfom request. (Store return code in res)
		CURLcode res{ curl_easy_perform(curl) };
		success = res == CURLE_OK;
		if (!success)
		{
			std::cerr << "curl_easy_perfom failed: " << curl_easy_strerror(res) << std::endl;
		}
		// Cleanup
		curl_easy_cleanup(curl);
		// Cleanup the formpost chain
		curl_formfree(formpost);
	}
	curl_global_cleanup();
	return std::make_pair(stream.str(), success);
}


bool CurlHelper::downloadAndSafeFile(const std::string &url, const std::string &fileDir)
{	
	curl_global_init(CURL_GLOBAL_ALL);
	CURL *curl{ curl_easy_init() };
	if (curl)
	{
		// Set url
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());	
		
		// Open file, so we can write the data into file later
		FILE *file{ fopen(fileDir.c_str(), "w") };
		if (!file)
		{
			std::cerr << "Error by opening file" << std::endl;
			return false;
		}
		// Store data in file
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);

		// Perfom request. (Store return code in res)
		CURLcode res{ curl_easy_perform(curl) };
		if (res != CURLE_OK)
		{
			std::cerr << "curl_easy_perfom failed: " << curl_easy_strerror(res) << std::endl;
			return false;
		}
		// Close file
		fclose(file);
		// Clean up
		curl_easy_cleanup(curl);
	}
	return true;
}

/*
std::pair<std::string, bool> CurlHelper::sendTextAndFileForm(std::string url, std::string textFieldName, 
			std::string textFieldContent, std::string fileFieldName, std::string fileFieldContent)
{
	bool success{ false };
	// Remove old content from buffer
	buffer.clear();

	CURL *curl;
	CURLcode res;
	curl_httppost *formpost = nullptr;
	curl_httppost *lastptr = nullptr;
	
	curl_global_init(CURL_GLOBAL_ALL);

	// Fill text field
	curl_formadd(&formpost,
			   &lastptr,
			   CURLFORM_COPYNAME, textFieldName.c_str(),
			   CURLFORM_COPYCONTENTS, textFieldContent.c_str(),
			   CURLFORM_END);

	// Fill file field
	curl_formadd(&formpost,
               &lastptr,
               CURLFORM_COPYNAME, fileFieldName.c_str(),
			   // Path to the file to upload
               CURLFORM_FILE, fileFieldContent.c_str(),
               CURLFORM_END);

	
	curl = curl_easy_init();
	if (curl)
	{
		// Set url (http:// or https://)
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());	
		// Specify POST data
		//curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields.c_str());
		// Use helper function to store output in std::string
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeToString);
		
		curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
		
		//curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields.c_str());
		// Perfom request. (Store return code in res)
		res = curl_easy_perform(curl);
		if (res != CURLE_OK)
		{
			std::cerr << "curl_easy_perfom failed: " << curl_easy_strerror(res) << std::endl;
		}
		else
		{
			success = true;
		}
		// Cleanup
		curl_easy_cleanup(curl);
		// Cleanup the formpost chain
		curl_formfree(formpost);
	}
	curl_global_cleanup();
	return std::make_pair(buffer, success);
}
*/

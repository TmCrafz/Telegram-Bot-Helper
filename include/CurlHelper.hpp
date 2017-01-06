#ifndef CURLHELPER_HPP
#define CURLHELPER_HPP
#include <string>
#include <utility>

namespace CurlHelper
{
	// Helper function to write data in string stream
	size_t writeDataToStrStream(char *ptr, size_t size, size_t nmemb, void *userdata);
	
	// Simple post with parameters. Returns a pair with the response of the called url as first parameter
	// and true as its second parameter 
	std::pair<std::string, bool> simplePost(const std::string &url, const std::string &postFields);
	// Send a file to a page with a file form (Field name is specified with fieldName and fileName is the path to the file)	
	std::pair<std::string, bool> fileFormPost(const std::string &url, const std::string &fieldName, 
			const std::string &fileName);
	
	// Download the specified url and safe it to the given fileDir
	bool downloadAndSafeFile(const std::string &url, const std::string &fileDir);

	// Send data to a page with a text field and a file field (post parameters can be added to the url, too)
	//std::pair<std::string, bool> sendTextAndFileForm(std::string url, std::string textFieldName, 
	//		std::string textFieldContent, std::string fileFieldName, std::string fileFieldContent);
}

#endif // CURLHELPER_HPP

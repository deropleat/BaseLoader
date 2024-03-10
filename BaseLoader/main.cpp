#include "CBase.h"

void cacheExplorer(std::string path, CBase* destination, CBase* source)
{
	NOTIFY("Waiting for the destination cache file");
	bool found = false;
	while (!found)
	{
		for (const auto& file : std::filesystem::directory_iterator(path))
		{
			if (file.file_size() == destination->getContentLength())
			{
				std::string content, string;
				std::ofstream cached(file.path(), std::ios::in | std::ios::out | std::ios::binary);
				if (cached.is_open())
				{
					cached << source->getResponse();
					NOTIFY("The destination cache file " << file.path().filename() << " has been successfully replaced to source file");
					found = true;
					cached.close();
					break;
				}
			}
		}
	}
}

int main(int argv, const char* argc[])
{
	CBase* destination = new CBase("https://www.shararam.ru/base.swf"), * source = argv > 1 ? new CBase(argc[1]) : new CBase("base.swf");
	if (source->getContentLength() <= 0) EXIT(-1, "The source file wasn't found");

	if (destination->getContentLength() != source->getContentLength())
	{
		std::cout << "bye";
		NOTIFY("Invalid content-length of the source file!");
		if (destination->getContentLength() > source->getContentLength())
		{
			source->resolveContentLength(destination->getContentLength());
			NOTIFY("The content-length of the source file has been successfully fixed");
		}
		else EXIT(-2, "The content-length of source file is more than the destination file");
	}
	
	char pAppData[MAX_PATH];
	SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, pAppData));
	std::thread cache(&cacheExplorer, std::string(pAppData) + "\\Shararam\\Cache", destination, source);
	cache.join();

	EXIT(0, "");
}
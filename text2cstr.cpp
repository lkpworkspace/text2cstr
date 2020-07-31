#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <array>

void print_usage()
{
	std::cout << "eg: text2cstr /path/to/src.txt /path/to/dst.txt" << std::endl;
}

void process_line_str(std::ofstream& wf, std::string& wline, char c)
{
	if(wline.empty())
		wline.append("\"");

	switch (c)
	{
	case '"':
		wline.append("\\\"");
		break;
	case '\n':
		wline.append("\\n\"\n");
		wf << wline;
		wline.clear();
		break;
	default:
		wline += c;
		break;
	}
}

int main(int argc, char** argv)
{
	if (argc != 3) {
		print_usage();
		return -1;
	}
	if (!std::filesystem::is_regular_file(argv[1])) {
		std::cout << "Not regular file" << std::endl;
		return -1;
	}

	std::ifstream rf(argv[1]);
	std::ofstream wf(argv[2]);
	if (rf.is_open() && wf.is_open()) {
		char ch;
		std::string wline;
		while (rf.get(ch)) {
			process_line_str(wf, wline, ch);
		}
		wf << wline;
		wf << "\"";
		rf.close();
		wf.close();
		return 0;
	}
	std::cout << "Open file failed" << std::endl;
	return -1;
}

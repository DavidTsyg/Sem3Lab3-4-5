// Sem3Lab345.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <filesystem>
#include <string>
#include <iostream>
#include <chrono>

using namespace std::experimental::filesystem::v1;

void printPerms(perms perm) {
	std::cout << "Permissions: "<< ((perm & perms::owner_read) != perms::none ? "r" : "-")
		<< ((perm & perms::owner_write) != perms::none ? "w" : "-")
		<< ((perm & perms::owner_exec) != perms::none ? "x" : "-")
		<< ((perm & perms::group_read) != perms::none ? "r" : "-")
		<< ((perm & perms::group_write) != perms::none ? "w" : "-")
		<< ((perm & perms::group_exec) != perms::none ? "x" : "-")
		<< ((perm & perms::others_read) != perms::none ? "r" : "-")
		<< ((perm & perms::others_write) != perms::none ? "w" : "-")
		<< ((perm & perms::others_exec) != perms::none ? "x" : "-");
}

void time(path p)
{
	if (is_regular_file(p))
	{
		auto ftime = last_write_time(p);

		std::time_t cftime = decltype(ftime)::clock::to_time_t(ftime); // assuming system_clock
		std::cout << " File write time: " << std::asctime(std::localtime(&cftime));
	}
	else
		std::cout << std::endl;
}

void size(path p)
{
	if (is_directory(p))
	{
		space_info a = space(p);
		std::cout << "Capacity: " << a.capacity << " Free: " << a.free << " Available: " << a.available << " ";
	}
	else if (is_regular_file(p))
		std::cout << "File size: " << file_size(p) << " ";
	else if(is_symlink(p))
		std::cout << "Link " ;
	else if (is_block_file(p))
		std::cout << "Block device ";
	else if (is_block_file(p))
		std::cout << "Character device ";
	else if (is_fifo(p))
		std::cout << "Named IPC pipe ";
	else if (is_socket(p))
		std::cout << "Named IPC socket ";
	else if (is_other(p))
		std::cout << "Some other type ";
}

void print_directory_full(path path_used)
{
	for (auto& p : directory_iterator(path_used))
	{
		size(p.path());
		std::cout << "Filename: " << p.path().filename() << " ";
		printPerms(status(p.path().filename()).permissions());
		time(p.path());
	}
}
void copy_func(path source, path destination)
{
	if (is_directory(source))
		copy(source, destination, copy_options::recursive);
	else
		copy(source, destination);
}
//Case sensitive
void search(path dir, std::string word)
{
	for (auto& p : directory_iterator(dir))
	{
		std::string buf = p.path().string();
		if (buf.find(word) != std::string::npos) {
			std::cout << buf << std::endl;
		}
	}
}
int main()
{
	path path_used;
	std::cin >> path_used;
	print_directory_full(path_used);
	path destination, source;
	std::cin >> source >> destination;
	copy_func(source, destination);
	path dir;
	std::string word;
	std::cin >> dir;
	std::cin >> word;
	search(dir, word);
	system("pause");
    return 0;
}


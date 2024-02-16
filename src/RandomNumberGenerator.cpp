#include "../inc/Colors.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <cstdlib>

void displayLoadingBar(int progress, int total)
{
    int barWidth = 70;
    float fraction = static_cast<float>(progress) / total;
    int progressWidth = static_cast<int>(barWidth * fraction);
	
    std::cout << "[" << BLUE;
    for (int i = 0; i < progressWidth; ++i)
    {
        std::cout << "|";
    }
	std::cout << RESET;
    for (int i = progressWidth; i < barWidth; ++i)
    {
        std::cout << " ";
    }
    std::cout << "] " << static_cast<int>(fraction * 100.0) << "%\r";
    std::cout.flush();
}

bool isAllDigits(const std::string &str)
{
	return std::all_of(str.begin(), str.end(), ::isdigit);
}

void fillWithDuplicates(std::vector<int> &vec, size_t n)
{
	int progress = 0;
	for (size_t i = 0; i < n; ++i)
	{
		int num = rand() % n;
		vec.push_back(num);
		progress++;
		displayLoadingBar(progress, n);
	}
}

void fillWithoutDuplicates(std::vector<int> &vec, size_t n)
{
	std::vector<int> temp;
	int randomIndex;
	int progress = 0;

	for (size_t i = 0; i < n; ++i)
	{
		temp.push_back(i);
	}
	for (size_t i = 0; i < n; ++i)
	{
		randomIndex = rand() % temp.size();
		vec.push_back(temp[randomIndex]);
		temp.erase(temp.begin() + randomIndex);
		progress++;
		displayLoadingBar(progress, n);
	}
}

int main()
{
    std::vector<int> vec;
	std::string number;
    size_t n;
    std::string duplicate;

    srand(static_cast<unsigned>(time(0)));

    std::cout << color("[========NUMBER GENERATOR========]", PURPLE_BOLD) << std::endl << std::endl;

    std::cout << color("Enter the number of random numbers you want to generate: ", CYAN);
    std::getline(std::cin, number);
	while (number.empty() || isAllDigits(number) == false)
	{
		std::cout << color("Invalid input. Please enter a number: ", RED);
		std::getline(std::cin, number);
	}
	n = std::stoi(number);

    std::cout << color("Do you want to allow duplicate numbers? (y/n): ", CYAN);
    std::cin >> duplicate;
	std::cout << std::endl;
    std::cout << color("Generating random numbers...", YELLOW) << std::endl;

    if (duplicate == "y")
	{
		fillWithDuplicates(vec, n);
    }
	else
	{
		fillWithoutDuplicates(vec, n);
    }
	std::cout << std::endl;
	std::cout << color("[SUCCESS]", GREEN) << std::endl;
	std::cout << std::endl;
	std::cout << n << color(" random numbers generated.", YELLOW) << std::endl;
	std::cout << std::endl;
	std::cout << color("Saving to numbers.txt...", YELLOW) << std::endl;

	std::ofstream outFile("numbers.txt", std::ios::out);

	if (outFile.is_open())
	{
		for (std::vector<int>::iterator it = vec.begin(); it < vec.end(); it++)
		{
			outFile << *it << " ";
			displayLoadingBar(std::distance(vec.begin(), it) + 1, vec.size());
		}
		outFile << std::endl;
		outFile.close();
		std::cout << std::endl;
		std::cout << color("[SUCCESS]", GREEN) << std::endl;
		std::cout << std::endl;
		std::cout << color("Random numbers saved to ", YELLOW);
		std::cout << color("numbers.txt", CYAN_BOLD) << std::endl;
		std::cout << std::endl;
		std::cout << color("Would you like to view the numbers? (y/n): ", CYAN);
		std::string view;
		std::cin >> view;
		if (view == "y")
			system("cat numbers.txt");
	}
	else
	{
		std::cerr << color("Error: Unable to open file.", RED) << std::endl;
		return 1;
	}

    return 0;
}

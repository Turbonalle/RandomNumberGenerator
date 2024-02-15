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

    int progress = 0;
    if (duplicate == "y")
	{
        while (vec.size() < n)
		{
            int num = rand() % n;
            vec.push_back(num);
            ++progress;
            displayLoadingBar(progress, n);
        }
    }
	else
	{
        while (vec.size() < n)
		{
            int num = rand() % n;
            if (std::find(vec.begin(), vec.end(), num) == vec.end())
			{
                vec.push_back(num);
                ++progress;
                displayLoadingBar(progress, n);
            }
        }
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

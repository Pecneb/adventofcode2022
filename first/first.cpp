#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>


std::vector< std::vector < int > > parse_calories( char* filename ) {
	std::ifstream textfile;
	textfile.open( filename, std::ios::in );

	if ( !textfile.is_open() ) { 
		std::cout << "Unable to open file." << std::endl;	
		exit(1); 
	}

	std::string line;
	int cnt = 0;

	std::vector< std::vector < int > > calories_per_bag{ std::vector < int > () };

	while ( std::getline( textfile, line ) ) {

		if ( std::strcmp( line.c_str(), "\0" ) == 0 ) {
			std::vector < int> newBag;
			calories_per_bag.push_back( newBag );	
			cnt++;
		} else {
			int cal = std::stoi( line, nullptr );
			calories_per_bag[cnt].emplace_back( cal );
		}

	}

	textfile.close();

	return calories_per_bag;
}

int sum_bag_cals( std::vector < int > bag ) {
	int sum = 0;
	for ( auto it = bag.begin(); it != bag.end(); it++ ) {
		sum += *it;
	}
	return sum;
}

int main(int argc, char** argv) {
	char flag[] = "--snacks";
	if ( std::strcmp( argv[1], flag ) != 0) {
		std::cout << "Usage: program --snacks [INPUTFILE]\n";
	}

	std::vector < std::vector < int > > bags = parse_calories ( argv[2] );
	
	size_t elf_idx = 0;
	int max_cals = 0;
	for ( size_t i = 0; i < bags.size() ; i++ ) {
		int sum_bag = sum_bag_cals( bags[i] );
		if ( sum_bag > max_cals ) {
			max_cals = sum_bag;
			elf_idx = i;
		}
	}

	std::cout << "Elf idx " << elf_idx << " has " << max_cals << " calories in its bag.\n";

	return 0;
}

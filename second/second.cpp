#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cstring>
#include <algorithm>

typedef std::vector< std::vector< char >  > rounds;

rounds parsefile( char* filename ) {
		
	std::ifstream file( filename );

	if ( !file.is_open() ) {
		std::cout << "Cant open file named " << filename << std::endl;
		exit(1);
	}

	std::string line;
	rounds retv;

	while( std::getline( file, line ) ) {
		char player1( line[0] );
		char player2( line[2] );
		std::vector< char > turn;
		turn.emplace_back( player1 );
		turn.emplace_back( player2 );
		retv.emplace_back( turn );
	} 

	file.close();

	return retv;
}

int score( std::vector< char >& turn ) {
	/* 
	 * Rock  	1
	 * Paper 	2
	 * Scissors 3
	 *
	 * arg1 turn ( int[2] )
	 * arg2 playernum ( int ): 0 or 1
	 * */

//	std::cout << turn[0] << turn[1] << std::endl; 

	// A -> Rock
	// B -> Paper
	// C -> Scissors
	std::map< char, int > choices;
	choices['A'] = 1;
	choices['B'] = 2;
	choices['C'] = 3;

	// X -> Lose
	// Y -> Draw
	// Z -> Win
	std::map< char, int > outcomes;
	outcomes['X'] = 0;
	outcomes['Y'] = 3;
	outcomes['Z'] = 6;

	std::map< std::pair< char, char >, int > scores;
	// Outcomes for Rock
	scores.emplace( std::make_pair( 'A', 'X' ), choices['C']+outcomes['X'] );
	scores.emplace( std::make_pair( 'A', 'Y' ), choices['A']+outcomes['Y'] );
	scores.emplace( std::make_pair( 'A', 'Z' ), choices['B']+outcomes['Z'] );
	// Outcomes for Paper
	scores.emplace( std::make_pair( 'B', 'X' ), choices['A']+outcomes['X'] );
	scores.emplace( std::make_pair( 'B', 'Y' ), choices['B']+outcomes['Y'] );
	scores.emplace( std::make_pair( 'B', 'Z' ), choices['C']+outcomes['Z'] );
	// Outcomes for Scissors
	scores.emplace( std::make_pair( 'C', 'X' ), choices['B']+outcomes['X'] );
	scores.emplace( std::make_pair( 'C', 'Y' ), choices['C']+outcomes['Y'] );
	scores.emplace( std::make_pair( 'C', 'Z' ), choices['A']+outcomes['Z'] );

	
	std::map< std::pair< char, char >, int >::iterator it = scores.find( std::make_pair( turn[0], turn[1] ) );
	if ( it != scores.end() ) {
	   return (*it).second;
	}
	return -1;	
	
	/*
	if ( turn[0] == turn[1] ) { 
	bool iswin = false;
		std::cout << "Tie" << std::endl;
		return turn[1] + 3;
	}
	else if ( turn[1] == 1 && turn[0] == 3 ) {
		std::cout << "Win" << std::endl;
		return turn[1] + 6;
	}
   	else if ( turn[1] == 2 && turn[0] == 1 ) {
		std::cout << "Win" << std::endl;
		return turn[1] + 6;
	}
   	else if ( turn[1] == 3 && turn[0] == 2 ) {
		std::cout << "Win" << std::endl;
		return turn[1] + 6;
	}
	std::cout << "Lose" << std::endl;
	return turn[1];
	*/
}

int main(int argc, char** argv) {

	rounds rv = parsefile( argv[1] );
	
	int scoresum = 0;

	for ( auto round : rv ) {
		std::cout << round.front() << round.back() << std::endl;
		scoresum += score( round );
	}

	std::cout << scoresum << std::endl;	

	return 0;
}

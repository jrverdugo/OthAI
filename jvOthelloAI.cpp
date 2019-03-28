//jvOthelloAI.cpp

#include <ics46/factory/DynamicFactory.hpp>
#include "jvOthelloAI.hpp"
ICS46_DYNAMIC_FACTORY_REGISTER( OthelloAI, jrverdug::jvOthelloAI, "Joey's Othello AI (Required)");

// Code Starts Here

std::pair<int, int> jrverdug::jvOthelloAI::chooseMove( const OthelloGameState& state )
{
	int hold = 0;
	std::unique_ptr<OthelloGameState> tempBoard = state.clone();
	std::vector< std::pair< int, int > > moves = availableMoves(tempBoard);

	int size = moves.size();
	for( int i = 0; i < size; i++ )
	{
		std::unique_ptr<OthelloGameState> tempClone = tempBoard->clone();
		tempClone->makeMove( moves[i].first, moves[i].second );

		if( search( tempClone, depth ) > hold )
		{
			index = i;
			hold = search( tempClone, depth );
		}


	}

	if( moves[index] != std::pair(0,0) && moves[index].first <= state.board().width() && moves[index].second <= state.board().height() )
	{
			return moves[ index ];
	}
	else
	{
		return moves[ 0 ];
	}

}




std::vector< std::pair< int, int > > jrverdug::jvOthelloAI::availableMoves( std::unique_ptr<OthelloGameState> & state )
{
	std::vector< std::pair< int, int > > temp;

	for( int j = 0; j < state->board().height(); j++ )
	{
		for( int i = 0; i < state->board().width(); i++ )
		{
			if( state->isValidMove( i, j ) )
			{
				temp.push_back( std::pair< int, int > ( i, j ) );
			}
		}
	}

	return temp;
}


int jrverdug::jvOthelloAI::eval( std::unique_ptr<OthelloGameState> & state )
{
	if( state->isBlackTurn() == true )
	{
		return state->blackScore() - state->whiteScore();
	}
	else
	{
		return state->whiteScore() - state->blackScore();
	}
}


int jrverdug::jvOthelloAI::search( std::unique_ptr<OthelloGameState> & state, int depth )
{
	if( depth == 0 )
	{
		return eval( state );
	}


	else
	{
		if( state->isBlackTurn() == true || state->isWhiteTurn() == true ) //Try for both methods at once, has to play for either B/W
		{
			std::unique_ptr<OthelloGameState> placeHolder = state->clone();
			std::vector< std::pair< int, int > > moves = availableMoves( state );

			max = eval(placeHolder);
			int size = moves.size();

			for( int i = 0; i < size; i++ )
			{
				std::unique_ptr<OthelloGameState> temp = state->clone();
				temp->makeMove( moves[i].first, moves[i].second );

				if( search( temp, depth - 1 ) > max ) //&& > max?
				{
					max = search( temp, depth - 1 );
				}
				else
				{
					if( eval( temp ) > max )
					{
						max = eval( temp );
					}
				}
			}

			return max; //Returns best case for my turn

		}

		else
		{
			std::unique_ptr<OthelloGameState> hold = state->clone();
			std::vector< std::pair< int, int > > moves = availableMoves( state );

			min = eval(hold);
			int size = moves.size();

			for( int i = 0; i < size; i++ )
			{
				std::unique_ptr<OthelloGameState> temp = state->clone();
				temp->makeMove( moves[i].first, moves[i].second );

				if( search( temp, depth - 1 ) < min )
				{
					min = search( temp, depth - 1 );
				}
				else
				{
					if( eval( temp ) < min )
					{
						min = eval( temp );
					}
				}
			}

			return min; //Return the worst case for us on the other player's turn
		}

	}
}

//jvOthelloAI.hpp

#include "OthelloAI.hpp"
#include <vector>

namespace jrverdug
{
	class jvOthelloAI: public OthelloAI
	{
		public:
			virtual std::pair< int, int > chooseMove( const OthelloGameState & state );
			int eval( std::unique_ptr<OthelloGameState> & state );
			int search( std::unique_ptr<OthelloGameState> & state, int depth );
			std::vector< std::pair< int, int > > availableMoves( std::unique_ptr<OthelloGameState> & state );
		private:
			int depth = 2;
			int max;
			int min;
			int index;


	};
}

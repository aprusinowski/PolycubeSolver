
/* 
 * File:   CubeSolver.cpp * 
 *
 * Created on April 8, 2016, 2:13 PM
 */

using namespace std;

#include "definitions.h"
#include "dlxSolver.h"
#include "cubeConfig.h"
#include "puzzlePiece.h"
long NUMGAMEPIECES;

typedef std::vector<long>    puzzlePieceIdent;

#define ONE_SOLUTION  1
#define ALL_SOLUTIONS 1000000

int main(int argc, char** argv) {
	
	long cubeDimSize;
    long numOfSolutions;
    long pieceSize;
    long pieceIdent;
	long** puzzlePiecesXYZ;
	puzzlePieceIdent* solution;
    cubeConfig* puzzleCube = new cubeConfig();
    
    if(argc == 2 && argv[1][0]=='1')
        numOfSolutions = ONE_SOLUTION;
    else if (argc == 2 && argv[1][0]=='a')
        numOfSolutions = ALL_SOLUTIONS;
    else
        numOfSolutions = ONE_SOLUTION;
    
    std::ifstream fin(argv[2]);
    if (!fin.is_open()){
        cerr<<"Could not open file"<<endl;
        exit(1); 
    }       
     
    fin >> cubeDimSize;
    cout << cubeDimSize <<endl;    
    fin >> NUMGAMEPIECES;
    cout << NUMGAMEPIECES<<endl;
    puzzlePiecesXYZ = new long*[NUMGAMEPIECES];      
    
	/*Read in all game pieces*/
    for(long piece = 0; piece < NUMGAMEPIECES;piece++){        
        fin >> pieceIdent;        
        fin >> pieceSize;   
		/*Read in unit cubes for single puzzle piece*/
        for (long row = 0; row < pieceSize; row++) {            
            puzzlePiecesXYZ[row] = new long[3];              
            fin>>(puzzlePiecesXYZ[row])[X];
            fin>>(puzzlePiecesXYZ[row])[Y];
            fin>>(puzzlePiecesXYZ[row])[Z];           
        }		
        puzzleCube->addPuzzlePiece(pieceIdent,pieceSize,puzzlePiecesXYZ);           
    }    
	   

	puzzlePiecePtr*   winningPuzzlePieces = new puzzlePiecePtr[NUMGAMEPIECES];
    PieceConfigSets* puzzlePieces = &(puzzleCube->getAllBitSets());
	dlxSolver solver(numOfSolutions,puzzlePieces);

    if (solver.findSolutions()) {
        long i = 0;
        solution = solver.getSolution(1);
		if(solution !=NULL)
        for (long ident : (*solution)) {
            winningPuzzlePieces[i] = puzzleCube->getPuzzlePieceNum(ident);
            winningPuzzlePieces[i]->printPuzzlePiece();
            i++;
        }
    }  

    delete(puzzleCube);
    return 0;
}


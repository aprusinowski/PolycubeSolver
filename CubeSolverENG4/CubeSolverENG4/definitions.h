/* 
 * File:   definitions.h
 * 
 *
 * Created on April 8, 2016, 4:43 PM
 * 
 */


#ifndef DEFINITIONS_H
#define DEFINITIONS_H

using namespace std;

#include <vector>
#include <bitset>
#include <map>
#include <unordered_map> 
#include <assert.h>
#include <fstream>
#include <iostream>
#include <string>

typedef std::vector<long>    pieceCubeIndexes;
typedef vector<vector<long>> allBitsets;

#define CUBEDIMSIZE		  4
#define CUBELEVELSIZE     16
#define MAXPIECESIZE      7 
#define CUBEVOLUME        64
#define NUM_POSSIBLE_VARS 24
#define TRUE              1
#define FALSE             0
#define X                 0
#define Y                 1
#define Z                 2

extern long NUMGAMEPIECES; 

class uCube;
class puzzlePiece;
class cubeConfig;
class dlxSolver;
class Node;


    typedef uCube*                       uCubePtr;
    typedef puzzlePiece*                puzzlePiecePtr;       
    typedef std::bitset<CUBEVOLUME>     BITSET_Cube;  
    typedef std::vector<BITSET_Cube>    VECPuzzleVarsBTS;      
    typedef std::vector<long>           VECPuzVarIndx;
    typedef vector<puzzlePiecePtr>      VECpuzzlePieceVars;
        
    /*cubeCongig class  typedef*/
    typedef std::vector<long>                        pieceCubeIndexes;
    typedef std::vector<long>                        columnVector; 
    typedef std::vector<puzzlePiecePtr>              allPuzzlePieces; 
    typedef std::multimap <long, puzzlePiecePtr>     colToPieceMap;
    typedef std::vector<long>                        xyzVect;
    typedef std::unordered_map<long, xyzVect*>       indexToCoordMap;  
    typedef std::unordered_map<long, puzzlePiecePtr> p_identToPuzzlePMAP;  
    typedef vector<vector<long>>                     PieceConfigSets;
    /*end ofcubeCongig class  typedef*/

#endif /* DEFINITIONS_H */


"""
Main program of the compiler performs the following actions:
1. Parses input file(s): "generateCallTree(sourceFiles, options)"
2. Translates to C++: "translateToCpp(callTree, sourceFiles)"

Usage:
fortran2cpp <fileName>

Arguments:
<fileName> = Name of the file to be translated. Can be in free or fixed format.

Output Files:
Translated file with a .cpp suffix.
"""

from generateCallTree import generateCallTree
from translateToCpp import translateToCpp
from utility import readInputLine
import sys

def fortran2cpp():
    """Top level function of the compiler"""
    options = []
    sourceFiles = readInputLine(sys.argv) # Read and parse input arguments
    
    callTree = generateCallTree(sourceFiles, options) # Parse input files
    translateToCpp(callTree, sourceFiles) # Translate to C++
    
fortran2cpp() # Run the translator
"""
Generates the call tree required for translation by parsing the source files.
This is the first function called by the main program "fortran2cpp"
"""

from utility import isProgram
from recognizeSourceLineAndUpdateTree import recognizeSourceLineAndUpdateTree
from Program import Program

def generateCallTree(sourceFiles, options):
    firstFile = open(sourceFiles, "r") # Open first given file for reading
    callTree = []
    while True:
        try:
            line = firstFile.next().strip() # Read next line.
        except: # End of file
            break
        if isProgram(line): # Is this a line containing "program" statement?
            callTree.append(Program(firstFile, line))
        else: # Ordinary statement
            recognizeSourceLineAndUpdateTree(callTree, line)
    
    return callTree
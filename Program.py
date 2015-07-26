"""
Fortran main program.
-> Implements ProgramPart
"""

from ProgramPart import ProgramPart
from utility import isEnd
from recognizeSourceLineAndUpdateTree import recognizeSourceLineAndUpdateTree
from End import End
from os import linesep # End of line character.

class Program(ProgramPart):
    def __init__(self, sourceFile, firstLine):
        """Contructor: Parameters:
           sourceFile = source file containing the main program
           firstLine  = first line containing the statement 'program <programName>'"""
        self.subParts = [] # List of ProgramParts contained by the main program.
        self.name     # Name of the program.
        self.parse(sourceFile, firstLine)
        
    def parse(self, sourceFile, firstLine):
        firstLineSplit = firstLine.split(" ") # Split program and <programName> on first line
        self.name = firstLineSplit[1] # Program name is the word behind "program"-keyword.
        # ENHANCEMENT: What if there is a comment right behind the program name?
        
        while True:
            line = sourceFile.next() # Read next line
            if isEnd(line):          # If end of program
                self.subParts.append(End(line))
                break;
            else:
                recognizeSourceLineAndUpdateTree(self.subParts, line)
        
    def translate(self):
        translation = "int main (int argc, char** argv)" + " // " + self.name + linesep # Main function
        translation += "{" + linesep # Opening curly brace
        for part in self.subParts: # Add translations of individual parts
            if type(part) is End:
                translation += "return 0;" + linesep # If end of program, add "return 0;" required by C++
            translation += part.translate() + linesep
            
            

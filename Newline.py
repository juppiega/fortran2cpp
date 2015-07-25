"""
Fortran source new line character
-> Implements ProgramPart.
"""

from ProgramPart import ProgramPart
from os import linesep # End of line character.

class Newline(ProgramPart):
    def __init__(self): # Constructor does nothing.
        pass
    def parse(self):   # So does parse()
        pass
    def translate(self): # translate() returns the os' newline character (usually \n)
        return linesep

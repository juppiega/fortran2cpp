"""
Fortran source new line character
-> Implements ProgramPart.
"""

from ProgramPart import ProgramPart

class Newline(ProgramPart):
    def __init__(self): # Constructor does nothing.
        pass
    def parse(self):   # So does parse()
        pass
    def translate(self): # translate() returns the os' newline character (usually \n)
        return "" # Newline is added to all lines in a higher level object translation (e.g. Program, Function etc.)

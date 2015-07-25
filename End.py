"""
Fortran End statement
-> Implements ProgramPart
"""

from ProgramPart import ProgramPart

class End(ProgramPart):
    def __init__(self, line):
        self.endIdentifier = "" # Identifier name or comment after the end statement.
        self.parse(line)
    
    def parse(self, line):
        if "!" in line: # If a line contains comment, it is preserved.
            commentInd = line.find("!")
            self.endIdentifier = line[commentInd+1:]
        else: # No comment found
            splitLine = line.split(" ")
            if len(splitLine) >= 3: # There is a name (e.g. "end if <name>")
                self.endIdentifier = splitLine[2] # Use the name as identifier
            else: # Plain end statement with no name
                self.endIdentifier = ""
        self.endIdentifier = "// " + self.endIdentifier # Add comment characters
    
    def translate(self):
        translation = "} " + self.endIdentifier
        return translation
            
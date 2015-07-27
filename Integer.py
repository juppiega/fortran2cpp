"""
Fortran Integer scalar/array type. 
-> Implements ProgramPart

This object is created by another object higher in the program hierarchy 
(e.g. a Function or a Module) and contains the variable name(s) and
possible attributes (e.g. save).
"""

from ProgramPart import ProgramPart
from utility import stripStrings, removeComment, fixComment

class Integer(ProgramPart):
    # Constructor
    def __init__(self, line):
        """Initialize class variables and parse the given line."""
        self.kind = 4   # Integer kind (default: 4-byte "int")
        self.names = [] # Names of integer variables.
        self.comment = ""
        self.parse(line)     # Parse information necessary for translation.
    
    def parse(self, line):
        """Find Integer names and kinds"""
        lineAndComment = removeComment(line) # Returns tuple with fields "lineOnly" and "comment"
        strippedLine = lineAndComment.lineOnly
        if "::" in strippedLine: # If line contains Fortran "::"-operator
            namesBegin = strippedLine.find("::") + 2 # First index after "::"
            # Variable names are the ones after "::", separated by comma
            self.names = strippedLine[namesBegin:].split(",")
        else: # One variable only
            lineParts = strippedLine.split(" ")
            self.names = lineParts[-1]
        self.comment = lineAndComment.comment
    
    def translate(self):
        self.names = stripStrings(self.names)
        # Convert from Fortran kind to C++ integer type.
        if self.kind <= 2: # 1 or 2
            typeName = "short"
        elif self.kind <= 4: # 3 or 4
            typeName = "int"
        else: # self.kind > 4
            typeName = "long long"
        
        separator = ", " # Separate variables using this string. If only one variable, join does nothing
        # TRANSLATION ---------------------------------------------
        translation = typeName + " " +  separator.join(self.names) + "; " + fixComment(self.comment)
        # ---------------------------------------------------------
        return translation
        
            

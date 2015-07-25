"""
Fortran source comment
-> Implements ProgramPart
"""

from ProgramPart import ProgramPart
from utility import fixComment

class Comment(ProgramPart):
    def __init__(self, line):
        self.comment = ""
        self.parse(line)
        
    def parse(self, line):
        self.comment = fixComment(line) # Change comment style.
        
    def translate(self):
        return self.comment # Return C++ style comment.

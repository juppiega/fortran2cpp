"""
Recognize type of source line and add to program's call tree.
Throw an error for unrecognized line.
"""
# Import recognization functions
from utility import isNewline, isComment, isImplicitNone, isInteger
# Import ProgramParts
from Newline import Newline
from Comment import Comment
from Integer import Integer

def recognizeSourceLineAndUpdateTree(subParts, line):
    """Updates the program call tree. List subParts IS MUTATED"""
    if isNewline(line):
        subParts.append(Newline())
    elif isComment(line):
        subParts.append(Comment(line))
    elif isImplicitNone(line):
        pass # Ignore "implicit none"
    elif isInteger(line):
        subParts.append(Integer(line))
    else:
        raise RuntimeError("Unknown statement: " + line + "Please first use a Fortran compiler")

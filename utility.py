"""
Utility functions.
"""

# -----------------------------------------------------------------------
def isNewline(line):
    """Test for newline character."""
    return line.strip() == "" # Line should already be empty, but strip just to be sure.

def isComment(line):
    """Test for comment"""
    strippedLine = line.strip()
    return strippedLine.find("!") == 0 # First character is "!"
    
def isProgram(line):
    """Test for program"""
    strippedLine = line.strip().lower() # Convert to lower for easier comparison.
    return strippedLine[:7] == "program"

def isImplicitNone(line):
    """Test for implicit none"""
    # Convert to lower for easier comparison and replace "!" by space
    strippedLine = line.strip().lower().replace("!", " ")
    if len(strippedLine) >= 13: # Line may contain stuff after "implicit none"
        return strippedLine[:13] == "implicit none" # Thirteen first non-space characters are "implcit none"
    else:
        return False
    # ENHANCEMENT: What if there are multiple spaces between "implicit" and "none"?
        
def isEnd(line):
    """Test for End (any) statement"""
    strippedLine = line.strip().lower() # Convert to lower for easier comparison.
    if len(strippedLine) >= 3: # Line may contain stuff after "end"
        return strippedLine[:3] == "end" # Three first non-space characters are "end"
    else:
        return False
        
def isInteger(line):
    """Test for Integer"""
    strippedLine = line.strip().lower() # Convert to lower for easier comparison.
    if len(strippedLine) >= 7: # Line contains stuff after "integer"
        return strippedLine[:7] == "integer" # Seven first non-space characters are "integer"
    else:
        return False

def isFile(fileName):
    """Check for file's existence"""
    import os.path
    return os.path.isfile(fileName)

# -----------------------------------------------------------------------
def fixComment(line):
    """Changes Fortran ! -comment to C++ // -comment."""
    newLine = line.replace("!", "//")
    return newLine

def removeComment(line):
    """Strips comment from line.
       Input "line" is modified and comment string is returned"""
    from collections import namedtuple # Multiple return values are achieved via a named tuple.
    
    commentInd = line.find("!")
    if commentInd > -1: # Line contained comment
        strippedLine = line[:commentInd].strip()
        commentStr = line[commentInd:]
    else: # No comment
        strippedLine = line.strip()
        commentStr = ""
    # Return multiple arguments
    return namedtuple("commentRemoved", ["lineOnly", "comment"])(strippedLine, commentStr)
    
def stripStrings(stringList):
    """Strips a list of strings from leading and trailing spaces."""
    newList = []
    for i in range(len(stringList)):
        newList.append(stringList[i].strip())
    return newList
# -----------------------------------------------------------------------
def readInputLine(argv):
    """Read command line arguments.
    sourceFiles and options are output"""
    if len(argv) == 1: # No arguments
        raise SyntaxError("Too few arguments.")
    if isFile(argv[1]):
        sourceFiles = argv[1]
    else:
        raise RuntimeError("File not found: " + argv[1])
    return sourceFiles

def formatOutputFiles(outputFileName):
    """Format output file using a verbose C++ coding style.
       Program "astyle" needs to be installed."""
    from subprocess import check_call
    check_call(["astyle", "--style=allman", "--indent-col1-comments", \
                "--pad-oper", "--pad-header", "--align-pointer=name", \
                "--add-brackets", "--suffix=none", "--quiet",  outputFileName])


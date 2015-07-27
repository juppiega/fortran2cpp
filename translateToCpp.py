"""
Translates the parsed call tree to C++
"""
from os import linesep # End of line character.
from utility import formatOutputFiles

def translateToCpp(callTree, sourceFiles):
    translation = ""
    # Add translations of individual parts together to an overall translation.
    for programPart in callTree:
        translation += programPart.translate() + linesep
    
    # Find filename by changing the file suffix to cpp
    fileSuffixInd = sourceFiles.rfind(".")
    fileBaseName = sourceFiles[:fileSuffixInd]
    outputName = fileBaseName + ".cpp"
    # Open output file
    outputFile = open(outputName, "w")
    # WRITE TRANSLATION -------------------------------------------------
    outputFile.write(translation)
    # -------------------------------------------------------------------
    outputFile.close()
    
    formatOutputFiles(outputName) # Format output file. Program "astyle" needs to be installed.

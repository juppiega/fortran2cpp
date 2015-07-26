"""
Translates the parsed call tree to C++
"""

def translateToCpp(callTree, sourceFiles):
    translation = ""
    # Add translations of individual parts together to an overall translation.
    for programPart in callTree:
        translation += programPart.translate()
    
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

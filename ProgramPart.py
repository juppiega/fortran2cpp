"""
The abstract class ProgramPart is the main building block of the compiler.
Every line of the Fortran program is converted into one class (e.g. Integer, 
Subroutine, Module, MainProgram), which inherits (and implements) ProgramPart.
"""

# Import Abstract Base Class (abc) module
from abc import ABCMeta, abstractmethod

class ProgramPart:
    __metaclass__ = ABCMeta # Choose ABCMeta as a class creator.
    
    @abstractmethod # Define this as an abstract method required to be implemented.
    def translate(self):
        """A method that translates the object (a part of the program, hence
           the name ProgramPart) from Fortran to C++."""
        pass
    
    @abstractmethod
    def parse(self):
        """A method, which parses the Program part into smaller components.
           In e.g. Integer, this function would discover the name of the variable
           and its possible attributes, while in e.g. Subroutine, it would
           compose the subroutine to smaller parts."""
        pass
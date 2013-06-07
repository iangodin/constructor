#
# Copyright (c) 2013 Kimball Thurston
#
# Permission is hereby granted, free of charge, to any person obtaining
# a copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included
# in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
# CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
# TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
# OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#

from .output import Debug, Error

class Dependency(object):
    """Base class for all things that represent a dependency tree.
       There are 3 types of dependencies stored in here:
       - explicit dependencies, these will appear on command lines
       - implicit dependencies, which will be used to indicate that
         even though a dependency is not explicitly used, it triggers
         the object to be out of date
       - ordering dependencies, which just causes dependencies to be built
         prior to the specified entry
    """

    def __init__( self ):
        self.dependencies = None
        self.order_only_dependencies = None
        self.implicit_dependencies = None

    def _add_to_ref( self, name, dep ):
        if not isinstance( dep, Dependency ):
            Error( "Attempt to add dependency that is not a subclass of Dependency" )
        deps = getattr( self, name )
        if deps is None:
            setattr( self, name, [ dep ] )
        else:
            found = False
            for d in deps:
                if d is dep:
                    found = True
                    break
            deps.append( dep )

    def add_dependency( self, dep ):
        self._add_to_ref( 'dependencies', dep )

    def add_implicit_dependency( self, dep ):
        self._add_to_ref( 'implicit_dependencies', dep )
            
    def add_order_dependency( self, dep ):
        self._add_to_ref( 'order_only_dependencies', dep )

class FileDependency(Dependency):
    """Simple sub-class to represent a direct file in a dependency tree"""
    def __init__( self, infile ):
        super(FileDependency, self).__init__()
        self.filename = infile


//
// Copyright (c) 2014 Kimball Thurston
//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
// OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

#include "TransformSet.h"


////////////////////////////////////////


TransformSet::TransformSet( const std::shared_ptr<Directory> &d )
		: myDirectory( d )
{
}


////////////////////////////////////////


TransformSet::~TransformSet( void )
{
}


////////////////////////////////////////


void
TransformSet::addTool( const std::shared_ptr<Tool> &t )
{
	myTools.push_back( t );
}


////////////////////////////////////////


void
TransformSet::mergeVariables( const VariableSet &vs )
{
	if ( myVars.empty() )
		myVars = vs;
	else
	{
		for ( auto i: vs )
			myVars.emplace( std::make_pair( i.first, i.second ) );
	}
}


////////////////////////////////////////


std::shared_ptr<Tool>
TransformSet::findTool( const std::string &ext ) const
{
	for ( auto &t: myTools )
		if ( t->handlesExtension( ext ) )
			return t;
	return std::shared_ptr<Tool>();
}


////////////////////////////////////////







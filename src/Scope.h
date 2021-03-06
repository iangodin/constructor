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

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Variable.h"
#include "Item.h"
#include "Pool.h"
#include "TransformSet.h"
#include "Directory.h"
#include "Toolset.h"

class Configuration;


////////////////////////////////////////


///
/// @brief Class Scope provides an abstraction around a collection of items.
///
/// This is probably most commonly at least a directory (and
/// sub-directories). It can have it's own unique config / toolsets /
/// whatever as well as "global" variables.  Variables can be
/// inherited from a parent scope or not.
///
class Scope : public std::enable_shared_from_this<Scope>
{
public:
	Scope( std::shared_ptr<Scope> parent = std::shared_ptr<Scope>() );

	inline std::shared_ptr<Scope> getParent( void ) const;
	inline void setParent( const std::shared_ptr<Scope> &p );

	std::shared_ptr<Scope> newSubScope( bool inherits );
	void removeSubScope( const std::shared_ptr<Scope> &c );
	inline const std::vector< std::shared_ptr<Scope> > &getSubScopes( void ) const;

	inline VariableSet &getVars( void );
	inline const VariableSet &getVars( void ) const;

	inline VariableSet &getOptions( void );
	inline const VariableSet &getOptions( void ) const;

	inline std::vector< std::shared_ptr<Tool> > &getTools( void );
	inline const std::vector< std::shared_ptr<Tool> > &getTools( void ) const;

	bool checkAdopt( const std::shared_ptr<Scope> &child );

	void addPool( const std::shared_ptr<Pool> &t );
	inline std::vector< std::shared_ptr<Pool> > &getPools( void );
	
	void addTool( const std::shared_ptr<Tool> &t );
	std::shared_ptr<Tool> findTool( const std::string &extension ) const;

	void addToolSet( const std::shared_ptr<Toolset> &ts );
	void useToolSet( const std::string &tset );
	std::shared_ptr<Toolset> findToolSet( const std::string &tset );

	void modifyActive( std::vector< std::shared_ptr<Toolset> > &tset ) const;

	void addItem( const ItemPtr &i );
	void removeItem( const ItemPtr &i );

	void transform( TransformSet &xform,
					const Configuration &conf ) const;

	static Scope &root( void );
	static Scope &current( void );
	static void pushScope( const std::shared_ptr<Scope> &scope );
	static void popScope( bool adopt = false );

private:
	void grabScope( const Scope &o );
	void addDefaultTools( void );

	std::weak_ptr<Scope> myParent;
	VariableSet myVariables;
	VariableSet myOptions;
	std::vector< std::shared_ptr<Scope> > mySubScopes;

	std::vector<ItemPtr> myItems;

	std::map< std::string, std::shared_ptr<Toolset> > myToolSets;

	std::map< std::string, std::vector< std::shared_ptr<Tool> > > myTagMap;
	std::vector< std::shared_ptr<Tool> > myTools;
	std::vector< std::shared_ptr<Toolset> > myEnabledToolsets;
	std::map< std::string, std::vector<std::shared_ptr<Tool> > > myExtensionMap;

	std::vector< std::shared_ptr<Pool> > myPools;
};


////////////////////////////////////////


inline const std::vector< std::shared_ptr<Scope> > &Scope::getSubScopes( void ) const
{
	return mySubScopes;
}


////////////////////////////////////////


inline std::shared_ptr<Scope> Scope::getParent( void ) const { return myParent.lock(); }
inline void Scope::setParent( const std::shared_ptr<Scope> &p ) { myParent = p; }


////////////////////////////////////////


inline VariableSet &Scope::getVars( void )
{ return myVariables; }
inline const VariableSet &Scope::getVars( void ) const
{ return myVariables; }


////////////////////////////////////////


inline VariableSet &Scope::getOptions( void )
{ return myOptions; }
inline const VariableSet &Scope::getOptions( void ) const
{ return myOptions; }


////////////////////////////////////////


inline std::vector< std::shared_ptr<Tool> > &
Scope::getTools( void )
{ return myTools; }
inline const std::vector< std::shared_ptr<Tool> > &
Scope::getTools( void ) const
{ return myTools; }


////////////////////////////////////////


inline std::vector< std::shared_ptr<Pool> > &
Scope::getPools( void )
{ return myPools; }


////////////////////////////////////////



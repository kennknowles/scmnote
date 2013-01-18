/*
  This file is part of scmnote - A scheme music system
  Copyright (C) 2002 Free Software Foundation, Inc
  
  scmnote is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.
  
  scmnote is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with scmnote; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef SCMNOTE_VAR_INT_HPP
#define SCMNOTE_VAR_INT_HPP

#include <iostream>

/*
  The largest value allowed in a midi file is
  0x0FFFFFFF - the variable representation of which is 0x7FFFFFFF
  so this doesn't have to be arbitrarily huge
*/

namespace scmnote
{
	class VarInt
	{
	public:
		VarInt();
		VarInt( const VarInt& vi );
		VarInt( const unsigned long int value );
		virtual ~VarInt();
		const VarInt& operator = ( const VarInt& vi );

		unsigned long int Get_Length() const;

		unsigned long int Get_Value() const;
		void Set_Value( unsigned long int val );
		void Emit( ostream& os ) const;

		VarInt operator + ( const VarInt& vi ) const;
		const VarInt& operator += ( const VarInt& vi );

		static const unsigned long int MaxValue = 0x0FFFFFFF;
	protected:
		unsigned long int m_Value;
	};
}

#endif

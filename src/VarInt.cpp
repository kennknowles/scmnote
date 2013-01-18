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

#include <iostream>
#include <vector>

#include "VarInt.hpp"
#include "output.hpp"
#include "debug.hpp"

using namespace scmnote;

VarInt::VarInt()
{
	m_Value = 0;
}

VarInt::VarInt( const VarInt& vi )
{
	m_Value = vi.m_Value;
}

VarInt::VarInt( const unsigned long int value )
{
	Set_Value( value );
}

VarInt::~VarInt()
{
}

const VarInt& VarInt::operator = ( const VarInt& vi )
{
	if ( this != &vi )
	{
		m_Value = vi.m_Value;
	}
	return ( *this );
}

unsigned long int VarInt::Get_Value() const
{
	return ( m_Value );
}


unsigned long int VarInt::Get_Length() const
{
	unsigned long int length=1;

	for ( unsigned long int remaining = m_Value;
          remaining > 127;
          remaining = (remaining >> 7) )
    {
		length++;
    }

	return ( length );
}


void VarInt::Set_Value( unsigned long int val )
{
	assert( val <= MaxValue );
	m_Value = val;
}

void VarInt::Emit( ostream& os ) const
{
	DEBUG_MSG( "Emitting VarInt with value: " << m_Value << endl );
	vector<unsigned char> buffer;

	// first byte has a 0 MSB
	buffer.push_back( m_Value & 0x7F );

	// all other bytes have a 1 MSB
	for ( unsigned long int remaining = (m_Value >> 7);
		  remaining > 0;
		  remaining = (remaining >> 7) )
	{
		buffer.push_back( (remaining & 0x7F) | 0x80 );
	}

	// reverse because it is most significant 7 bits first
	for ( int i = buffer.size()-1;
		  i >= 0;
		  i-- )
	{
		write8( os, buffer[i] );
	}
}

VarInt VarInt::operator + ( const VarInt& vi ) const
{
	return ( VarInt( m_Value + vi.m_Value ) );
}

const VarInt& VarInt::operator += ( const VarInt& vi )
{
	(*this) = (*this) + vi;
	return ( *this );
}

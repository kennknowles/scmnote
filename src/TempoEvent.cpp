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
#include <cassert>

#include "TempoEvent.hpp"
#include "output.hpp"
#include "debug.hpp"

using namespace scmnote;

TempoEvent::TempoEvent()
{
	m_Tempo = 120;
}

TempoEvent::TempoEvent( unsigned long tempo )
{
	Set_Tempo( tempo );
}

TempoEvent::TempoEvent( const TempoEvent& se )
{
	Set_Tempo( se.Get_Tempo() );
}

TempoEvent::~TempoEvent()
{
}

const TempoEvent& TempoEvent::operator = ( const TempoEvent& se )
{
	if ( this != &se )
	{
		Set_Tempo( se.Get_Tempo() );
	}
	return ( *this );
}

EnumMetaEvent TempoEvent::Get_Type() const
{
	return ( META_Set_Tempo );
}

void TempoEvent::Set_Tempo( unsigned long tempo )
{
	assert( tempo <= 0xFFFFFF );
	m_Tempo = tempo;
}

unsigned long TempoEvent::Get_Tempo() const
{
	return ( m_Tempo );
}

//

MidiEvent* TempoEvent::Clone() const
{
	return ( new TempoEvent( *this ) );
}

unsigned long int TempoEvent::Get_Length() const
{
	return ( 6 );
}

void TempoEvent::Emit( ostream& os ) const
{
	// (micr/quarter) = (micro/second)(second/minut)(minute/quarter)
	// = (1000000)(60)(1/tempo)

	unsigned long micros = 60 * (1000000 / Get_Tempo());

	DEBUG_MSG( "Emitting Tempo = " << Get_Tempo() << endl );
	DEBUG_MSG( "=> " << micros << " per quarter note.\n" );

	write8( os, 0xFF );
	write8( os, 0x51 );
	write8( os, 0x03 );
	write24( os, micros );
}

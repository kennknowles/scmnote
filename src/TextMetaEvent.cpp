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

#include "VarInt.hpp"
#include "TextMetaEvent.hpp"
#include "EnumMetaEvent.hpp"
#include "output.hpp"

using namespace scmnote;

TextMetaEvent::TextMetaEvent( EnumMetaEvent type)
{
	Set_Type( type );
	Set_Text( "" );
}

TextMetaEvent::TextMetaEvent( EnumMetaEvent type, string text )
{
	Set_Type( type );
	Set_Text( text );
}

TextMetaEvent::TextMetaEvent( const TextMetaEvent& tm )
{
	Set_Type( tm.Get_Type() );
	Set_Text( tm.Get_Text() );
}

TextMetaEvent::~TextMetaEvent()
{
}
	
const TextMetaEvent& TextMetaEvent::operator = ( const TextMetaEvent& tm )
{
	if ( this != &tm )
	{
		Set_Text( tm.Get_Text() );
	}
	return ( *this );
}

void TextMetaEvent::Set_Type( EnumMetaEvent type )
{
	assert( (type == META_Text_Event)
			|| (type == META_Copyright_Notice)
			|| (type == META_Sequence_Track_Name)
			|| (type == META_Instrument_Name)
			|| (type == META_Lyric)
			|| (type == META_Marker)
			|| (type == META_Cue_Point) );
	
	m_Type = type;
}

EnumMetaEvent TextMetaEvent::Get_Type() const
{
	return ( m_Type );
}

VarInt TextMetaEvent::Get_TextLength() const
{
	return ( m_Text.size() );
}
	
string TextMetaEvent::Get_Text() const
{
	return ( m_Text );
}
		
void TextMetaEvent::Set_Text( string text )
{
	m_Text = text;
}

MidiEvent* TextMetaEvent::Clone() const
{
	return ( new TextMetaEvent( (*this) ) );
}

unsigned long int TextMetaEvent::Get_Length() const
{
	return ( Get_TextLength().Get_Value() + 2 );
}

void TextMetaEvent::Emit( ostream& os ) const
{
	// for all Meta Events
	write8( os, 0xFF );

	// output type of event
	switch ( Get_Type() )
	{
	case META_Text_Event:
		write8( os, 0x01 ); break;
	case META_Copyright_Notice:
		write8( os, 0x02 ); break;
	case META_Sequence_Track_Name:
		write8( os, 0x03 ); break;
	case META_Instrument_Name:
		write8( os, 0x04 ); break;
	case META_Lyric:
		write8( os, 0x05 ); break;
	case META_Marker:
		write8( os, 0x06 ); break;
	case META_Cue_Point:
		write8( os, 0x07 ); break;
	}

	Get_TextLength().Emit( os );

	os.write( m_Text.c_str(), m_Text.size() );
}

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

#include <cassert>

#include "ProgramChangeMessage.hpp"
#include "EnumVoiceMessage.hpp"
#include "output.hpp"
#include "debug.hpp"

using namespace scmnote;
	
ProgramChangeMessage::ProgramChangeMessage( EnumVoiceMessage type,
											unsigned int channel,
											unsigned int program )
{
	Set_Program( program );
	Set_Channel( channel );
}

ProgramChangeMessage::ProgramChangeMessage( const ProgramChangeMessage& pcm )
{
	Set_Program( pcm.Get_Program() );
	Set_Channel( pcm.Get_Channel() );
}

ProgramChangeMessage::~ProgramChangeMessage()
{
	
}

const ProgramChangeMessage&
ProgramChangeMessage::operator= ( const ProgramChangeMessage& pcm )
{
	if ( this != &pcm )
	{
		Set_Program( pcm.Get_Program() );
		Set_Channel( pcm.Get_Channel() );
	}
	return ( *this );
}

//***********************************************************************
// Public Functions
//***********************************************************************

EnumVoiceMessage ProgramChangeMessage::Get_Type() const
{
	return ( m_Type );
}

void ProgramChangeMessage::Set_Type( EnumVoiceMessage type )
{
	assert( (type == VOICE_Program_Change) );

	m_Type = type;
}

unsigned int ProgramChangeMessage::Get_Channel() const
{
	return ( m_Channel );
}

void ProgramChangeMessage::Set_Channel( unsigned int channel )
{
	assert( channel <= 0x0F );
	m_Channel = channel;
}

unsigned int ProgramChangeMessage::Get_Program() const
{
	return ( m_Program );
}

void ProgramChangeMessage::Set_Program( unsigned int program )
{
	assert( program <= 0xFF );
	m_Program = program;
}


//

MidiEvent* ProgramChangeMessage::Clone() const
{
	return ( new ProgramChangeMessage( *this ) );
}

unsigned long int ProgramChangeMessage::Get_Length() const
{
	return ( 2 );
}

void ProgramChangeMessage::Emit( ostream& os ) const
{
	DEBUG_MSG( "Emiting program change = " << Get_Program() << endl
			   << "   channel = " << Get_Channel() << endl );
	
	write8( os, 0xC0 | ( Get_Channel() & 0x0F ) );
	write8( os, 0xFF & Get_Program() );
}

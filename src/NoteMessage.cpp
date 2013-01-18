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

#include "NoteMessage.hpp"
#include "EnumVoiceMessage.hpp"
#include "output.hpp"
#include "debug.hpp"

using namespace scmnote;
	
NoteMessage::NoteMessage( EnumVoiceMessage type,
						  unsigned int channel,
						  char note,
						  int accidental,
						  unsigned int octave,
						  unsigned int velocity )
{
	Set_Type( type );
	Set_Note( note );
	Set_Accidental( accidental );
	Set_Octave( octave );
	Set_Velocity( velocity );
	Set_Channel( channel );
}

NoteMessage::NoteMessage( const NoteMessage& nm )
{
	Set_Type( nm.Get_Type() );
	Set_Note( nm.Get_Note() );
	Set_Accidental( nm.Get_Accidental() );
	Set_Octave( nm.Get_Octave() );
	Set_Velocity( nm.Get_Velocity() );
	Set_Channel( nm.Get_Channel() );
}

NoteMessage::~NoteMessage()
{
	
}

const NoteMessage& NoteMessage::operator= ( const NoteMessage& nm )
{
	if ( this != &nm )
	{
		Set_Type( nm.Get_Type() );
		Set_Note( nm.Get_Note() );
		Set_Accidental( nm.Get_Accidental() );
		Set_Octave( nm.Get_Octave() );
		Set_Velocity( nm.Get_Velocity() );
		Set_Channel( nm.Get_Channel() );
	}
	return ( *this );
}

//***********************************************************************
// Public Functions
//***********************************************************************

EnumVoiceMessage NoteMessage::Get_Type() const
{
	return ( m_Type );
}

void NoteMessage::Set_Type( EnumVoiceMessage type )
{
	assert( (type == VOICE_Note_On)
			|| (type == VOICE_Note_Off)
			|| (type == VOICE_Key_Aftertouch) );

	m_Type = type;
}

unsigned int NoteMessage::Get_Channel() const
{
	return ( m_Channel );
}

void NoteMessage::Set_Channel( unsigned int channel )
{
	assert( channel <= 0x0F );
	m_Channel = channel;
}


char NoteMessage::Get_Note() const
{
	return ( m_Note );
}

void NoteMessage::Set_Note( char note )
{
	assert( (note >= 'a') && (note <= 'g') );

	m_Note = note;
}

unsigned int NoteMessage::Get_Octave() const
{
	return ( m_Octave );
}

void NoteMessage::Set_Octave( unsigned int octave )
{
	assert( octave < 11 );

	m_Octave = octave;
}

int NoteMessage::Get_Accidental() const
{
	return ( m_Accidental );
}

void NoteMessage::Set_Accidental( int accidental )
{
	assert( (accidental > -0x7f) && (accidental < 0x7f) );
	m_Accidental = accidental;
}

unsigned int NoteMessage::Get_Velocity() const
{
	return ( m_Velocity );
}

void NoteMessage::Set_Velocity( unsigned int velocity )
{
	assert( velocity <= 0x7f );
	m_Velocity = velocity;
}

//

MidiEvent* NoteMessage::Clone() const
{
	return ( new NoteMessage( *this ) );
}

unsigned long int NoteMessage::Get_Length() const
{
	return ( 3 );
}

void NoteMessage::Emit( ostream& os ) const
{
	DEBUG_MSG( "Emiting note = " << Get_Note() << endl
			   << "   octave = " << Get_Octave() << endl
			   << "   channel = " << Get_Channel() << endl
			   << "   vel = " << Get_Velocity() << endl );


	unsigned char StatusByte;

	switch ( Get_Type() )
	{
	case VOICE_Note_On:
		StatusByte = 0x90; break;
	case VOICE_Note_Off:
		StatusByte = 0x80; break;
	case VOICE_Key_Aftertouch:
		StatusByte = 0xa0; break;
	}

	StatusByte |= ( Get_Channel() & 0x0F );
    char DataByte1 = CalculateNoteNum() & 0xFF;
    char DataByte2 = Get_Velocity() & 0xFF;

	write8( os, StatusByte );
	write8( os, DataByte1 );
	write8( os, DataByte2 );
}


//***********************************************************
// Protected
//***********************************************************

unsigned int NoteMessage::CalculateNoteNum() const
{
	unsigned int noteOffset;
	
	switch ( Get_Note() )
	{
	case 'c':
		noteOffset = 0; break;
	case 'd':
		noteOffset = 2; break;
	case 'e':
		noteOffset = 4; break;
	case 'f':
		noteOffset = 5; break;
	case 'g':
		noteOffset = 7; break;
	case 'a':
		noteOffset = 9; break;
	case 'b':
		noteOffset = 11; break;
	}

	noteOffset += Get_Accidental();

	noteOffset += 12 * Get_Octave();

	assert( noteOffset <= 0x7F );

	return ( noteOffset );
}

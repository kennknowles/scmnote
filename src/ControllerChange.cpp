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

#include "ControllerChange.hpp"
#include "EnumController.hpp"
#include "EnumVoiceMessage.hpp"
#include "output.hpp"
#include "debug.hpp"

using namespace scmnote;
	
ControllerChange::ControllerChange( unsigned int channel,
									EnumController control,
									unsigned int value )
{
	Set_Controller( control );
	Set_Value( value );
	Set_Channel( channel );
}

ControllerChange::ControllerChange( const ControllerChange& cc )
{
	Set_Controller( cc.Get_Controller() );
	Set_Value( cc.Get_Value() );
	Set_Channel( cc.Get_Channel() );
}

ControllerChange::~ControllerChange()
{
	
}

const ControllerChange& 
ControllerChange::operator= ( const ControllerChange& cc )
{
	if ( this != &cc )
	{
		Set_Controller( cc.Get_Controller() );
		Set_Value( cc.Get_Value() );
		Set_Channel( cc.Get_Channel() );
	}
	return ( *this );
}

//***********************************************************************
// Public Functions
//***********************************************************************

EnumVoiceMessage ControllerChange::Get_Type() const
{
	return ( VOICE_Controller_Change );
}

EnumController ControllerChange::Get_Controller() const
{
	return ( m_Controller );
}

void ControllerChange::Set_Controller( EnumController control )
{
	m_Controller = control;
}


unsigned int ControllerChange::Get_Channel() const
{
	return ( m_Channel );
}

void ControllerChange::Set_Channel( unsigned int channel )
{
	assert( channel <= 0x0F );
	m_Channel = channel;
}


unsigned int ControllerChange::Get_Value() const
{
	return ( m_Value );
}

void ControllerChange::Set_Value( unsigned int value )
{
	assert( value <= 0x7f );
	m_Value = value;
}

void ControllerChange::Set_On()
{
	m_Value = 0x7f;
}

void ControllerChange::Set_Off()
{
	m_Value = 0;
}
//

MidiEvent* ControllerChange::Clone() const
{
	return ( new ControllerChange( *this ) );
}

unsigned long int ControllerChange::Get_Length() const
{
	return ( 3 );
}

void ControllerChange::Emit( ostream& os ) const
{
	DEBUG_MSG( "Emiting Controller Change, value = " << Get_Value() << endl );

	unsigned char ControllerByte = 0x77; // if we haven't implemented it, 0x77 

	switch ( Get_Controller() )
	{
	case CONTROLLER_Channel_Volume:
		ControllerByte = 0x07; break;
	case CONTROLLER_Damper_Pedal:
		ControllerByte = 0x40; break;
	case CONTROLLER_Pan:
		ControllerByte = 0x0a; break;
	case CONTROLLER_Balance:
		ControllerByte = 0x08; break;
	}

	write8( os, 0xb0 | (Get_Channel() & 0x0f) );
	write8( os, ControllerByte );
	write8( os, Get_Value() & 0xff );
}

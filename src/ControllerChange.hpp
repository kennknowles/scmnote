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

#ifndef SCMNOTE_CONTROLLER_CHANGE_HPP
#define SCMNOTE_CONTROLLER_CHANGE_HPP

#include <iostream>

#include "MidiEvent.hpp"
#include "ChannelVoiceMessage.hpp"
#include "EnumController.hpp"
#include "EnumVoiceMessage.hpp"

#include "HasChannel.hpp"

namespace scmnote
{
	class ControllerChange : public ChannelVoiceMessage
	{
	public:
		ControllerChange( unsigned int channel,
						  EnumController control,
						  unsigned int value );

		ControllerChange( const ControllerChange& cc );
		virtual ~ControllerChange();
		const ControllerChange& operator= ( const ControllerChange& nm );

		virtual EnumVoiceMessage Get_Type() const;

		virtual unsigned int Get_Channel() const;
		virtual void Set_Channel( unsigned int channel );

		virtual EnumController Get_Controller() const;
		virtual void Set_Controller( EnumController control );

		virtual unsigned int Get_Value() const;
		virtual void Set_Value( unsigned int val );

		// for on/off messages 127 = on, 0 = off
		virtual void Set_On();
		virtual void Set_Off();
		
		//
		
		virtual MidiEvent* Clone() const;
		virtual unsigned long int Get_Length() const;
		virtual void Emit( ostream& os ) const;

	private:
		unsigned int CalculateNoteNum() const;

		EnumVoiceMessage m_Type;
		EnumController m_Controller;
		unsigned int m_Value;
		unsigned int m_Channel;
	};
}

#endif

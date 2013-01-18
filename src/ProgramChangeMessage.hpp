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

#ifndef SCMNOTE_PROGRAM_CHANGE_MESSAGE_HPP
#define SCMNOTE_PROGRAM_CHANGE_MESSAGE_HPP

#include <iostream>

#include "MidiEvent.hpp"
#include "ChannelVoiceMessage.hpp"
#include "EnumVoiceMessage.hpp"

#include "HasChannel.hpp"

namespace scmnote
{
	class ProgramChangeMessage : public ChannelVoiceMessage
	{
	public:
		ProgramChangeMessage( EnumVoiceMessage type,
							  unsigned int channel,
							  unsigned int program );
		
		ProgramChangeMessage( const ProgramChangeMessage& pcm );
		virtual ~ProgramChangeMessage();
		const ProgramChangeMessage& 
		operator= ( const ProgramChangeMessage& pcm );

		virtual EnumVoiceMessage Get_Type() const;
		virtual void Set_Type( EnumVoiceMessage type );

		virtual unsigned int Get_Channel() const;
		virtual void Set_Channel( unsigned int channel );

		virtual unsigned int Get_Program() const;
		virtual void Set_Program( unsigned int program );

		//

		virtual MidiEvent* Clone() const;
		virtual unsigned long int Get_Length() const;
		virtual void Emit( ostream& os ) const;

	private:
		EnumVoiceMessage m_Type;
		unsigned int m_Program;
		unsigned int m_Channel;
	};
}

#endif

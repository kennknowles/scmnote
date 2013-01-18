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

#ifndef SCMNOTE_NOTE_MESSAGE_HPP
#define SCMNOTE_NOTE_MESSAGE_HPP

#include <iostream>

#include "MidiEvent.hpp"
#include "ChannelVoiceMessage.hpp"
#include "EnumVoiceMessage.hpp"

#include "HasChannel.hpp"

namespace scmnote
{
	class NoteMessage : public ChannelVoiceMessage
	{
	public:
		NoteMessage( EnumVoiceMessage type,
					 unsigned int channel,
					 char note,
					 int accidental,
					 unsigned int octave,
					 unsigned int velocity );

		NoteMessage( const NoteMessage& nm );
		virtual ~NoteMessage();
		const NoteMessage& operator= ( const NoteMessage& nm );

		virtual EnumVoiceMessage Get_Type() const;
		virtual void Set_Type( EnumVoiceMessage type );

		virtual unsigned int Get_Channel() const;
		virtual void Set_Channel( unsigned int channel );

		virtual char Get_Note() const;
		virtual void Set_Note( char note );

		virtual unsigned int Get_Octave() const;
		virtual void Set_Octave( unsigned int octave );

		virtual int Get_Accidental() const;
		virtual void Set_Accidental( int accidental );

		virtual unsigned int Get_Velocity() const;
		virtual void Set_Velocity( unsigned int velocity );
	
		//

		virtual MidiEvent* Clone() const;
		virtual unsigned long int Get_Length() const;
		virtual void Emit( ostream& os ) const;

	private:
		unsigned int CalculateNoteNum() const;

		EnumVoiceMessage m_Type;
		char m_Note;
		unsigned int m_Octave;
		int m_Accidental;
		unsigned int m_Velocity;
		unsigned int m_Channel;
	};
}

#endif

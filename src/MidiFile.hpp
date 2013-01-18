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

#ifndef SCMNOTE_MIDI_FILE_HPP
#define SCMNOTE_MIDI_FILE_HPP

#include <vector>
#include <iostream>

#include "TrackChunk.hpp"

#include "EnumMidiFormat.hpp"
#include "EnumDivType.hpp"

namespace scmnote
{
	class MidiFile
	{
	public:
		MidiFile();
		MidiFile( const MidiFile& midifile );
		virtual ~MidiFile();
		virtual const MidiFile& operator = ( const MidiFile& midifile );

		virtual EnumMidiFormat Get_Format() const;
		virtual void Set_Format( EnumMidiFormat format );

		virtual EnumDivType Get_DivType() const;
		virtual void Set_DivType( EnumDivType divType );

		virtual unsigned short int Get_TicksPerQuarter() const;
		virtual void Set_TicksPerQuarter( unsigned short int ticks );

		virtual unsigned char Get_DeltaPerSmtpFrame() const;
		virtual void Set_DeltaPerSmtpFrame( unsigned char delta );

		virtual unsigned char Get_SmtpFps() const;
		virtual void Set_SmtpFps( signed char fps );

		virtual void AppendTrackChunk( TrackChunk* chunk );
		virtual void Emit( ostream& os );

		virtual vector<TrackChunk*> Get_Tracks();

	protected:
		void EmitHeaderChunk( ostream& os );

		vector<TrackChunk*> m_TrackChunks;

        EnumDivType m_DivType;
        EnumMidiFormat m_MidiFormat;

		bool m_DropFrame;
        unsigned char m_SmtpFps;
        unsigned char m_DeltaPerSmtpFrame;
        unsigned short int m_TicksPerQuarter;
	};
}

#endif

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

#include <vector>
#include <cassert>

#include "MidiFile.hpp"
#include "TrackChunk.hpp"
#include "EnumMidiFormat.hpp"
#include "output.hpp"

using namespace scmnote;

//**************************************************************
// The Big Four
//**************************************************************

MidiFile::MidiFile() :
	m_TrackChunks()
{
	Set_DivType( DIVTYPE_QUARTER );
	Set_Format( FORMAT_MIDI_1 );
	Set_TicksPerQuarter( 96 );
}

MidiFile::MidiFile( const MidiFile& midifile )
{
	Set_DivType( midifile.Get_DivType() );
	Set_Format( midifile.Get_Format() );
	Set_TicksPerQuarter( midifile.Get_TicksPerQuarter() );

	for ( vector<TrackChunk*>::const_iterator iter 
			  = midifile.m_TrackChunks.begin();
		  iter != midifile.m_TrackChunks.end();
		  iter++ )
	{
		m_TrackChunks.push_back( new TrackChunk( **iter ) );
	}
}
	
MidiFile::~MidiFile()
{
	for ( vector<TrackChunk*>::iterator iter = m_TrackChunks.begin();
		  iter != m_TrackChunks.end();
		  iter++ )
	{
		delete (*iter);
	}
}

const MidiFile& MidiFile::operator = ( const MidiFile& midifile )
{
	if ( this != &midifile )
	{
		Set_DivType( midifile.Get_DivType() );
		Set_Format( midifile.Get_Format() );
		Set_TicksPerQuarter( midifile.Get_TicksPerQuarter() );
		
		// TODO: improve effeciency, this deletes all old track chunks, and
		// clones new ones
		for ( vector<TrackChunk*>::iterator iter = m_TrackChunks.begin();
			  iter != m_TrackChunks.end();  
			  iter++ )
		{
			delete (*iter); 
		}
		
		m_TrackChunks.clear();
		
		for ( vector<TrackChunk*>::const_iterator iter 
				  = midifile.m_TrackChunks.begin();
			  iter != midifile.m_TrackChunks.end();
			  iter++ )
		{
			m_TrackChunks.push_back( new TrackChunk( **iter ) );
		}
	}
	
	return ( *this );
}

//**********************************************************************
// public functions
//**********************************************************************

EnumMidiFormat MidiFile::Get_Format() const
{
	return ( m_MidiFormat );
}

void MidiFile::Set_Format( EnumMidiFormat format )
{
	m_MidiFormat = format;
}

EnumDivType MidiFile::Get_DivType() const
{
	return ( m_DivType );
}


void MidiFile::Set_DivType( EnumDivType divType )
{
	m_DivType = divType;
}

unsigned short int MidiFile::Get_TicksPerQuarter() const
{
	assert( m_DivType == DIVTYPE_QUARTER );
	return ( m_TicksPerQuarter );
}

void MidiFile::Set_TicksPerQuarter( unsigned short int ticks )
{
	assert( m_DivType == DIVTYPE_QUARTER );
	m_TicksPerQuarter = ticks;
}

unsigned char MidiFile::Get_DeltaPerSmtpFrame() const
{
	assert( m_DivType == DIVTYPE_FRAME );
	return ( m_DeltaPerSmtpFrame );
}

void MidiFile::Set_DeltaPerSmtpFrame( unsigned char delta )
{
	assert( m_DivType == DIVTYPE_FRAME );
	m_DeltaPerSmtpFrame = delta;
}

unsigned char MidiFile::Get_SmtpFps() const
{
	assert( m_DivType == DIVTYPE_FRAME );
	return ( m_SmtpFps );
}

void MidiFile::Set_SmtpFps( signed char fps )
{
	assert( m_DivType == DIVTYPE_FRAME );
	m_SmtpFps = fps;
}

void MidiFile::AppendTrackChunk( TrackChunk* chunk )
{
	m_TrackChunks.push_back( chunk );
}

void MidiFile::Emit( ostream& os )
{
	EmitHeaderChunk( os );
	
	for ( vector<TrackChunk*>::iterator iter = m_TrackChunks.begin();
		  iter != m_TrackChunks.end();
		  iter++ )
	{
		(*iter)->Emit( os );
	}
}

void MidiFile::EmitHeaderChunk( ostream& os )
{
	// Type, 4 bytes of text
	os << "MThd";

	// Length, is always 6 bytes
	write32( os, 6 );

	// format 16 bits
	switch( Get_Format() )
    {
    case FORMAT_MIDI_0:
        write16( os, 0 ); break;
    case FORMAT_MIDI_1:
        write16( os, 1 ); break;
    case FORMAT_MIDI_2:
		write16( os, 2 ); break;
    }

	// num tracks, 16 bits
	write16( os, m_TrackChunks.size() );

	// division, 16 bits
	switch( m_DivType )
	{
	case DIVTYPE_QUARTER:
		write16( os, m_TicksPerQuarter & 0x7F );
		break;
	case DIVTYPE_FRAME:
		unsigned char fps;
		// TODO: support Smtp Frames
		assert( (m_DeltaPerSmtpFrame == 24) ||
				(m_DeltaPerSmtpFrame == 25) ||
				(m_DeltaPerSmtpFrame == 30) );

		if ( m_DropFrame )
		{
			assert( m_DeltaPerSmtpFrame == 30 );
			fps = 29;
		}
		else
		{
			fps = m_DeltaPerSmtpFrame;
		}

		unsigned char c = 0x60 | (fps & 0x1F);
			
		write16( os, 
				 ( m_SmtpFps & 0x07 ) |
				 ( c << 8 ) );
		break;
	}
}

vector<TrackChunk*> MidiFile::Get_Tracks()
{
	return ( m_TrackChunks );
}

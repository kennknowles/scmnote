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

#include "TrackChunk.hpp"
#include "EndOfTrackEvent.hpp"
#include "output.hpp"
#include "debug.hpp"

using namespace scmnote;

//*************************************************************
// The Big Four
//*************************************************************

TrackChunk::TrackChunk()
{
}

TrackChunk::TrackChunk( const TrackChunk& tc )
{
	// TODO: improve effeciency, this deletes all old track chunks, and         
	// clones new ones                                                          
	for ( vector<MidiItem*>::iterator iter = m_Items.begin();
		  iter != m_Items.end();
		  iter++ )
	{
		delete (*iter);
	}
	
	m_Items.clear();
	
	for ( vector<MidiItem*>::const_iterator iter
			  = tc.m_Items.begin();
		  iter != tc.m_Items.end();
		  iter++ )
	{
		m_Items.push_back( new MidiItem( **iter ) );
	}
}

TrackChunk::~TrackChunk()
{
	for ( vector<MidiItem*>::iterator iter = m_Items.begin();
		  iter != m_Items.end();
		  iter++ )
	{
		delete ( *iter );
	}


}

const TrackChunk& TrackChunk::operator = ( const TrackChunk& tc )
{
	if ( this != &tc )
	{
		for ( vector<MidiItem*>::iterator iter = m_Items.begin();
			  iter != m_Items.end();
			  iter++ )
		{
			delete (*iter);
		}
		
		m_Items.clear();
		
		for ( vector<MidiItem*>::const_iterator iter
			  = tc.m_Items.begin();
			  iter != tc.m_Items.end();
			  iter++ )
		{
			assert ( *iter != NULL );
			m_Items.push_back( new MidiItem( **iter ) );
		}
	}

	return ( *this );
}

//*************************************************************
// public functions
//*************************************************************

string TrackChunk::Get_Type() const
{
	return ( "MTrk" );
}
	
unsigned long int TrackChunk::Get_Length() const
{
	unsigned long int length = 0;

	for( vector<MidiItem*>::const_iterator iter = m_Items.begin();
		 iter != m_Items.end();
		 iter++ )
	{
		assert( *iter != NULL );
		length += (*iter)->Get_Length().Get_Value();
	}

	length += VarInt(0).Get_Length();
	length += EndOfTrackEvent().Get_Length();

	
	assert ( length <= 0xFFFF );
	return ( length & 0xFFFF );
}

void TrackChunk::Emit( ostream& os ) const
{
	DEBUG_MSG( "Emiting track chunk\n" );
	os << "MTrk";
	
	write32( os, Get_Length() );

	for( vector<MidiItem*>::const_iterator iter = m_Items.begin();
		 iter != m_Items.end();
		 iter++ )
	{
		DEBUG_MSG( "Trackchunk: Item found: \n" );
		(*iter)->Emit( os );
	}

	VarInt(0).Emit( os );
	EndOfTrackEvent().Emit( os );
}

void TrackChunk::Append( MidiItem* item )
{
	m_Items.push_back( new MidiItem( *item ) );
}

vector<MidiItem*> TrackChunk::Get_Items() const
{
	return ( m_Items );
}

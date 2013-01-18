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

void write8( ostream& outfile, char unsigned val )
{
	outfile.put( val );
}

void write16( ostream& outfile, unsigned int val )
{
	outfile.put( (val & 0xFF00) >> 8 );
	outfile.put( val & 0x00FF );
}

void write24( ostream& outfile, unsigned long val )
{
	outfile.put( (val & 0xFF0000) >> 16 );
	write16( outfile, (val & 0xFFFF) );
}

void write32( ostream& outfile, unsigned long val )
{
	write16( outfile, (val & 0xFFFF0000) >> 16 );
	write16( outfile, val & 0x0000FFFF );
}

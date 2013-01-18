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

#ifndef SCMNOTE_ENUM_DIV_TYPE_HPP
#define SCMNOTE_ENUM_DIV_TYPE_HPP

namespace scmnote
{
	/*
	  DIVTYPE_QUARTER:
	  indicates that the file's division is in terms of ticks per
	  quarter note, meaning the most significant bit of the
	  division field of the header chunk is a 0

	  DIVTYPE_FRAME:
	  indicates that the division has the 2 values frames/sec and
	  ticks/frame, and that the MSB of the division field is 1
	*/ 

	enum EnumDivType
	{
		DIVTYPE_QUARTER,
		DIVTYPE_FRAME
	};
}

#endif

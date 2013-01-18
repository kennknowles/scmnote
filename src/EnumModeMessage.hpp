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

#ifndef SCMNOTE_ENUM_MODE_MESSAGE_HPP
#define SCMNOTE_ENUM_MODE_MESSAGE_HPP

namespace scmnote
{
	enum EnumModeMessage
	{
		MODE_All_Sound_Off,
		MODE_Reset_All_Controllers,
		MODE_Local_Control,
		MODE_All_Notes_Off,
		MODE_Omni_Mode_Off,
		MODE_Omni_Mode_On,
		MODE_Mono_Mode_On,
		MODE_Poly_Mode_On
	};
}

#endif

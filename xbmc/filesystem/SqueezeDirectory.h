#pragma once
/*
* Squeezebox Browsing Support for XBMC
*      Copyright (c) 2014 robweber (Rob Weber)
*      Portions taken from XSqueeze addon by bossanova808
*      Copyright (C) 2005-2013 Team XBMC
*      http://xbmc.org
*
*  This Program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2, or (at your option)
*  any later version.
*
*  This Program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with XBMC; see the file COPYING.  If not, see
*  <http://www.gnu.org/licenses/>.
*
*/

#include "IDirectory.h"

namespace XFILE
{
	typedef struct {
		int			level;
		int         label;
	} Squeeze_Node;

	class CSqueezeDirectory :

		public IDirectory
	{
	public:
		CSqueezeDirectory(void);
		virtual ~CSqueezeDirectory(void);
		virtual bool AllowAll() const { return true; }
		virtual bool GetDirectory(const CURL& url, CFileItemList &items);
		//int GetCurrLevel(const std::string &strPath);

	private:
		int GetCurrLevel(const std::string &strPath);
	};
}
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

#include "SqueezeDirectory.h"
#include "URL.h"
#include "music/tags/MusicInfoTag.h"
#include "FileItem.h"
#include "utils/log.h"
#include "utils/URIUtils.h"
#include "utils/StringUtils.h"
#include "guilib/LocalizeStrings.h"

namespace XFILE
{
	Squeeze_Node RootChildren[] = {
		{ 1, 359 },
		{ 2, 132 },
		{ 3, 133 },
		{ 4, 135 },
		{ 5, 20011 }
	};

	const char unknownArtistAlbum[] = "Unknown";

	CSqueezeDirectory::CSqueezeDirectory(void)
	{
		
	}

	CSqueezeDirectory::~CSqueezeDirectory(void)
	{
		
	}

	bool CSqueezeDirectory::GetDirectory(const CURL& url, CFileItemList &items)
	{
		std::string strRoot = url.Get();
		URIUtils::AddSlashAtEnd(strRoot);
		
		int currentLevel = GetCurrLevel(strRoot);

		// Add root directory items
		CLog::Log(LOGDEBUG, "SqueezeDirectory: Current Level is %i", currentLevel);
		
		if (currentLevel <= 0)
		{
			//root level, create the main nodes
			for (unsigned int i = 0; i < sizeof(RootChildren) / sizeof(Squeeze_Node); ++i)
			{
				//add the item to the list
				CFileItemPtr pItem(new CFileItem(g_localizeStrings.Get(RootChildren[i].label)));
				pItem->SetPath(StringUtils::Format("%s%i/", strRoot.c_str(), RootChildren[i].level));
				pItem->m_bIsFolder = true;
				items.Add(pItem);
			}
		}
		else
		{
			//set the name of the folder
			items.SetLabel(g_localizeStrings.Get(RootChildren[currentLevel - 1].label));
		}

		return true;
	}

	int CSqueezeDirectory::GetCurrLevel(const std::string &strPath)
	{
		size_t intSPos;
		size_t intEPos;
		int intLevel;
		int intCnt;
		std::string strJustPath;

		intSPos = strPath.find("://");
		if (intSPos != std::string::npos)
			strJustPath = strPath.substr(intSPos + 3);
		else
			strJustPath = strPath;

		URIUtils::RemoveSlashAtEnd(strJustPath);
		CLog::Log(LOGDEBUG, "%s", strJustPath);

		intLevel = -1;
		intSPos = strPath.length();

		intSPos = strJustPath.find("/");

		//get the first int after the /
		if(intSPos != std::string::npos)
		{
			intLevel = atoi(strJustPath.substr(intSPos + 1, 1).c_str());
		}
		
		CLog::Log(LOGDEBUG, "%i", intLevel);

		/*
		m_selectedPlaylist = "";
		m_selectedArtist = "";
		m_selectedAlbum = "";
		intCnt = intLevel;
		intEPos = (strJustPath.length() - 1);
		while (intCnt >= 0)
		{
			intSPos = strJustPath.rfind("/", intEPos);
			if (intSPos != std::string::npos)
			{
				if (intCnt == 2)  // album
				{
					m_selectedAlbum = strJustPath.substr(intSPos + 1, (intEPos - intSPos));
				}
				else if (intCnt == 1) // artist
				{
					m_selectedArtist = strJustPath.substr(intSPos + 1, (intEPos - intSPos));
				}
				else if (intCnt == 0) // playlist
				{
					m_selectedPlaylist = strJustPath.substr(intSPos + 1, (intEPos - intSPos));
				}

				intEPos = (intSPos - 1);
				intCnt--;
			}
		}
		*/

		return intLevel;
	}
}
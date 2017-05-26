/*
 * ***** BEGIN GPL LICENSE BLOCK *****
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * The Original Code is Copyright (C) 2001-2002 by NaN Holding BV.
 * All rights reserved.
 *
 * The Original Code is: all of this file.
 *
 * Contributor(s): none yet.
 *
 * ***** END GPL LICENSE BLOCK *****
 */

/** \file gameengine/GameLogic/SCA_IScene.cpp
 *  \ingroup gamelogic
 */

#include "SCA_IScene.h"
#include "SCA_IObject.h"

SCA_DebugProp::SCA_DebugProp()
	:m_obj(nullptr)
{
}

SCA_DebugProp::~SCA_DebugProp()
{
	if (m_obj) {
		m_obj->Release();
	}
}

SCA_IScene::SCA_IScene()
{
}

void SCA_IScene::RemoveAllDebugProperties()
{
	for (std::vector<SCA_DebugProp *>::iterator it = m_debugList.begin(); !(it == m_debugList.end()); ++it) {
		delete (*it);
	}
	m_debugList.clear();
}

SCA_IScene::~SCA_IScene()
{
	RemoveAllDebugProperties();
}

std::vector<SCA_DebugProp *>& SCA_IScene::GetDebugProperties()
{
	return m_debugList;
}

bool SCA_IScene::PropertyInDebugList(SCA_IObject *gameobj, const std::string &name)
{
	for (std::vector<SCA_DebugProp *>::iterator it = m_debugList.begin(); !(it == m_debugList.end()); ++it) {
		std::string debugname = (*it)->m_name;
		SCA_IObject *debugobj = (*it)->m_obj;

		if (debugobj == gameobj && debugname == name) {
			return true;
		}
	}
	return false;
}

bool SCA_IScene::ObjectInDebugList(SCA_IObject *gameobj)
{
	for (std::vector<SCA_DebugProp *>::iterator it = m_debugList.begin(); !(it == m_debugList.end()); ++it) {
		SCA_IObject *debugobj = (*it)->m_obj;

		if (debugobj == gameobj) {
			return true;
		}
	}
	return false;
}

void SCA_IScene::AddDebugProperty(SCA_IObject *debugprop, const std::string &name)
{
	if (m_debugList.size() < DEBUG_MAX_DISPLAY) {
		SCA_DebugProp *dprop = new SCA_DebugProp();
		dprop->m_obj = debugprop;
		debugprop->AddRef();
		dprop->m_name = name;
		m_debugList.push_back(dprop);
	}
}

void SCA_IScene::RemoveDebugProperty(SCA_IObject *gameobj, const std::string &name)
{
	std::vector<SCA_DebugProp *>::iterator it = m_debugList.begin();
	while (it != m_debugList.end()) {
		std::string debugname = (*it)->m_name;
		SCA_IObject *debugobj = (*it)->m_obj;

		if (debugobj == gameobj && debugname == name) {
			delete (*it);
			it = m_debugList.erase(it);
			break;
		}
		else {
			++it;
		}
	}
}

void SCA_IScene::RemoveObjectDebugProperties(SCA_IObject *gameobj)
{
	std::vector<SCA_DebugProp *>::iterator it = m_debugList.begin();
	while (it != m_debugList.end()) {
		SCA_IObject *debugobj = (*it)->m_obj;

		if (debugobj == gameobj) {
			delete (*it);
			it = m_debugList.erase(it);
			continue;
		}
		else {
			++it;
		}
	}
}

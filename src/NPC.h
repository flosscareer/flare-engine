/*
Copyright © 2011-2012 Clint Bellanger
Copyright © 2013 Henrik Andersson
Copyright © 2012-2015 Justin Jacobs

This file is part of FLARE.

FLARE is free software: you can redistribute it and/or modify it under the terms
of the GNU General Public License as published by the Free Software Foundation,
either version 3 of the License, or (at your option) any later version.

FLARE is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
FLARE.  If not, see http://www.gnu.org/licenses/
*/

/**
 * class NPC
 */

#ifndef NPC_H
#define NPC_H

#include "CommonIncludes.h"
#include "Entity.h"
#include "ItemStorage.h"
#include "Utils.h"

class NPC : public Entity {
private:
	enum {
		VOX_INTRO = 0,
		VOX_QUEST = 1,
	};

	void loadGraphics();
	int loadSound(const std::string& fname, int vox_type);
	bool isDialogType(const EVENT_COMPONENT_TYPE &event_type);
	bool playSoundQuest(int id);

	std::string gfx; // filename of sprite.

	std::vector<Event_Component> random_table;
	Point random_table_count;

	std::vector<std::string> vendor_requires_status;
	std::vector<std::string> vendor_requires_not_status;

	std::vector<std::string> portrait_filenames;

	// vocals
	std::vector<SoundID> vox_intro;
	std::vector<SoundID> vox_quests;

public:
	static const int VENDOR_MAX_STOCK = 80;

	NPC();
	~NPC();
	void load(const std::string& npc_id);
	void logic();
	bool playSoundIntro();
	void getDialogNodes(std::vector<int> &result);
	std::string getDialogTopic(unsigned int dialog_node);
	bool checkMovement(unsigned int dialog_node);
	bool checkVendor();
	bool processDialog(unsigned int dialog_node, unsigned int& event_cursor);
	void processEvent(unsigned int dialog_node, unsigned int cursor);
	virtual Renderable getRender();

	// general info
	std::string name;
	std::string filename;
	FPoint pos; // map position

	int direction;

	// talker info
	Sprite* npc_portrait;
	Sprite* hero_portrait;
	std::vector<Sprite*> portraits;
	bool talker;

	// vendor info
	bool vendor;
	bool reset_buyback;
	ItemStorage stock;

	// story and dialog options
	// outer vector is addressing the dialog and the inner vector is
	// addressing the events during one dialog
	std::vector<std::vector<Event_Component> > dialog;
};

#endif

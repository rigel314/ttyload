/*
 * windowlist.h
 *
 *  Created on: Jan 1, 2014
 *      Author: cody
 */

#ifndef WINDOWLIST_H_
#define WINDOWLIST_H_

#include "common.h"
#include "ttysys_api.h"
#include <ncurses.h>

// window information.
enum winFlags { wf_Title = 1, wf_Label = 1<<1, wf_Grid = 1<<2, wf_ExpandedTitle = 1<<3, wf_ShowMax = 1<<4, wf_Border = 1<<5 };
enum winDataType { VoidData, CPUData, MemData, NetData, UserData };

// printLine information.
enum lineDir { HORIZ, VERT };

// My window management structure.
struct windowlist
{
	struct windowlist* next;
	WINDOW* titlewin;
	WINDOW* contentwin;
	WINDOW* labelwin;
	struct arrowPointers
	{
		struct windowlist* left;
		struct windowlist* right;
		struct windowlist* up;
		struct windowlist* down;
	} surrounding;
	char title[TITLE_LEN];
	char flags;
	enum winType type;
	struct GRect frame;
	enum winDataType dataType;
	int dataSource;
	float* data;
	int dataLen;
	int validDataLen;
	float maxVal;
	int refreshPrd;
	void* plgHandle;
	struct initData plgData;
	void* plgContext;
};

// Used in determining arrow key mapping.
struct bestPtr
{
	struct windowlist* ptr;
	int diff;
};

void drawScreen(struct windowlist* win);
void remapArrows(struct windowlist* wins, struct windowlist* win);
struct GRect getContentFrame(struct windowlist* win);
void resizeWindowToFrame(struct windowlist* win);
void splitV(struct windowlist* old);
void splitH(struct windowlist* old);
void unSplit(struct windowlist** wins, struct windowlist** win);
void refreshAll(struct windowlist* wins, struct windowlist* focus);
void printLine(WINDOW* WIN, int row, int col, enum lineDir direction, int len);
struct windowlist* addWin(struct windowlist** wins);
int initializePlugin(struct windowlist* win, char* args);
void cleanupPlugin(struct windowlist* win);
void freeWin(struct windowlist** wins, struct windowlist* win);

#endif /* WINDOWLIST_H_ */

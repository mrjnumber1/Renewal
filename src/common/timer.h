/**
 * This file is part of RagEmu.
 * http://ragemu.org - https://github.com/RagEmu/Renewal
 *
 * Copyright (C) 2016  RagEmu Dev Team
 * Copyright (C) 2012-2015  Hercules Dev Team
 * Copyright (C)  Athena Dev Teams
 *
 * RagEmu is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef COMMON_TIMER_H
#define COMMON_TIMER_H

#include "common/ragemu.h"

#define DIFF_TICK(a,b) ((a)-(b))
#define DIFF_TICK32(a,b) ((int32)((a)-(b)))

#define INVALID_TIMER (-1)

// timer flags
enum {
	TIMER_ONCE_AUTODEL = 0x01,
	TIMER_INTERVAL = 0x02,
	TIMER_REMOVE_HEAP = 0x10,
};

// Struct declaration

typedef int (*TimerFunc)(int tid, int64 tick, int id, intptr_t data);

struct TimerData {
	int64 tick;
	TimerFunc func;
	unsigned char type;
	int interval;

	// general-purpose storage
	int id;
	intptr_t data;
};


/*=====================================
* Interface : timer.h
* Generated by HerculesInterfaceMaker
* created by Susu
*-------------------------------------*/
struct timer_interface {

	/* funcs */
	int64 (*gettick) (void);
	int64 (*gettick_nocache) (void);

	int (*add) (int64 tick, TimerFunc func, int id, intptr_t data);
	int (*add_interval) (int64 tick, TimerFunc func, int id, intptr_t data, int interval);
	const struct TimerData *(*get) (int tid);
	int (*delete) (int tid, TimerFunc func);

	int64 (*addtick) (int tid, int64 tick);
	int64 (*settick) (int tid, int64 tick);

	int (*add_func_list) (TimerFunc func, char* name);

	unsigned long (*get_uptime) (void);

	int (*perform) (int64 tick);
	void (*init) (void);
	void (*final) (void);
};

#ifdef RAGEMU_CORE
void timer_defaults(void);
#endif // RAGEMU_CORE

HPShared struct timer_interface *timer;

#endif /* COMMON_TIMER_H */

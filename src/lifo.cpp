/*
  MidiShareLight Project
  Copyright (C) Grame 2020

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

  Grame Research Laboratory, 11, cours de Verdun Gensoul 69002 Lyon - France
  research@grame.fr

*/

#include "lifo.h"

void lifoinit(lifo* lf)
{
	lf->top = 0;
	lf->count = 0;
}

void lifopush (lifo * lf, lifocell * cell)
{
	lf->mtx.lock();
	cell->link = lf->top;
	lf->top = cell;
	lf->count++;
	lf->mtx.unlock();
}

lifocell* lifopop (lifo * lf)
{
	lf->mtx.lock();
	lifocell * top = lf->top;
	if (top) {
		lf->top = top->link;
		lf->count--;
	}
	lf->mtx.unlock();
	return top;
}

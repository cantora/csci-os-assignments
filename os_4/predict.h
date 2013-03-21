#ifndef OSPA4_PREDICT_H
#define OSPA4_PREDICT_H

#include "phist.h"

#define MAX_PAGE_ALLOC 40
#define REALLOC_BASE 50
#define REALLOC_INTERVAL (REALLOC_BASE*100) /* ticks */

static struct phist phist_arr[MAXPROCESSES];
static int pg_alloc[MAXPROCESSES];
static int proc_faults[MAXPROCESSES];
static uint32_t proc_susp[MAXPROCESSES];
static int proc_pset[MAXPROCESSES][MAXPROCPAGES];
static int proc_last_evict[MAXPROCESSES];
static int proc_last_unsat[MAXPROCESSES];
static int proc_last_pagein[MAXPROCESSES];

#endif /* OSPA4_PREDICT_H */
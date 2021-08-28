#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <xcb/xcb.h>
#include <xcb/xcb_aux.h>

#include "arg.h"
#include "util.h"

static xcb_connection_t	*conn;
static xcb_screen_t	*scrn;



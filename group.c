#include <err.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <xcb/xcb.h>
#include <xcb/xcb_aux.h>

static xcb_connection_t *conn;

enum {
	ATTR_W = 1 << 0,
	ATTR_H = 1 << 1,
	ATTR_X = 1 << 2,
	ATTR_Y = 1 << 3,
	ATTR_M = 1 << 4,
	ATTR_I = 1 << 6,
	ATTR_MAX
}

static int get_attributes(xcb_window_t, int);

static int
get_attributes(xcb_window_t w, int attr)
{
	xcb_get_geometry_cookie_t c;
	xcb_get_geometry_reply_t *r;

	c = xcb_get_geometry(conn, w);
	r = xcb_get_geometry_reply(conn, c, NULL);

	if (r == NULL)
		errx(1, "0x%08x: no such window", w);

	switch (attr) {
		case ATTR_X: attr = r->x; break;
		case ATTR_Y: attr = r->y; break;
		case ATTR_W: attr = r->width; break;
		case ATTR_H: attr = r->height; break;
	}

	free(r);
	return attr;
				
}



int main(void)
{
	char filename[256];
	xcb_window_t w = 0;
	unsigned int winnum = 0;
	unsigned int newwin = 1;
	snprintf(filename, sizeof(filename), ".config/sxwm/win%d", newwin);
	FILE *f = fopen(filename, "w+");

	init_xcb(&conn);

	/* print text */
	const char *text = "This is a text";
	fprintf(f, "First: %s\n", text);

	/* Print X pos */
	fprintf(f, "%d\n", get_attributes(w, ATTR_X));

	/* print integers and floats */
	unsigned int i = 1;
	fprintf(f, "Group: %d\n", i);

	/* print a single character */
	char c = 'C';
	fprintf(f, "Some character: %c\n", c);

	fclose(f);
}

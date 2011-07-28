/*
   Screenruler 1.1
   Copyright (C) 2010 by Austin Beatty <doorknob60 at gmail dot com>

   (Copyright for functions to grab X and Y mouse coordinates):
   Copyright (C) 2007 by Robert Manea  <rob dot manea at gmail dot com>

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
   */

#include<stdio.h>
#include<stdlib.h>
#include<X11/Xlib.h>
#include<math.h>

int main(int argc, char *argv[])
{
	system("zenity --info --text=\"Press enter for first mouse position\"");

	XEvent e;
	Display *d = XOpenDisplay(NULL);

	if(!d)
		return EXIT_FAILURE;

	/* get info about current pointer position */
	XQueryPointer(d, RootWindow(d, DefaultScreen(d)),
			&e.xbutton.root, &e.xbutton.window,
			&e.xbutton.x_root, &e.xbutton.y_root,
			&e.xbutton.x, &e.xbutton.y,
			&e.xbutton.state);

	int x1 = e.xbutton.x;
	int y1 = e.xbutton.y;

	XCloseDisplay(d);
	
	system("zenity --info --text=\"Press enter for second mouse position\"");
	
	XEvent f;
	Display *g = XOpenDisplay(NULL);

	if(!g)
		return EXIT_FAILURE;

	/* get info about current pointer position */
	XQueryPointer(g, RootWindow(g, DefaultScreen(g)),
			&f.xbutton.root, &f.xbutton.window,
			&f.xbutton.x_root, &f.xbutton.y_root,
			&f.xbutton.x, &f.xbutton.y,
			&f.xbutton.state);

	int x2 = f.xbutton.x;
	int y2 = f.xbutton.y;

	XCloseDisplay(g);

	int xc = abs(x1-x2);
	int yc = abs(y1-y2);
	float change = sqrt(xc*xc+yc*yc);
	char command[512];
	sprintf(command, "zenity --info --text=\"X Change: %d pixels\\nY Change: %d pixels\\nTotal Change: %f pixels\"", xc, yc, change);
	system((char *)command);
	return EXIT_SUCCESS;
}

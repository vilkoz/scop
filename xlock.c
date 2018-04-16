#include <X11/keysym.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <stdio.h>
# define SCREEN_NUM 0


void		get_lock(void)
{
	Display *dpy  = XOpenDisplay(0);
	
	if (!dpy)
	{
		puts("no display");
		return ;
	}

	int nscreens = ScreenCount(dpy);

	Window root = RootWindow(dpy, SCREEN_NUM);
	XSetWindowAttributes wa;
	for (int len = 1000; len; len--)
	{
		int grab = XGrabKeyboard(
				dpy,
				root,
				True,
				GrabModeAsync,
				GrabModeAsync,
				CurrentTime
				);

		if (grab == GrabSuccess)
			break;
		usleep(1000);
	}
}

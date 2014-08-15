#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/cursorfont.h>
#include <X11/keysym.h>

#include <stdio.h>

char *busfont="-*-courier-bold-r-*-*-700-*-*-*-*-*-*-*";
char *textfont="-*-helvetica-bold-r-*-*-40-*-*-*-*-*-*-*";

#define XA_BITMAPDEPTH 1

double x1,y1,x2,y2;
double tx1,tx2,ty1,ty2;
double ar,ai,tr,ti,cr,ci;
double savex1,savex2,savey1,savey2;
int drawnx=0,drawny=0;

int depth;

Display *display;
int screen,button;

Window win,root_return,child;
int rootx,rooty,button_stats;
Cursor cursor;
unsigned int width,height;
int x = 0, y = 0;
unsigned int border_width=4;
unsigned int display_width, display_height;
char *window_name = "L:A_N:application_ID:loopbus";
char *icon_name="L:A_N:application_ID:loopbus";
Pixmap icon_pixmap;
XSizeHints size_hints;
XEvent report;
GC gc;
XGCValues gcvalues;
Colormap colormap;
Visual *visual = CopyFromParent;
char *display_name= NULL;
char *astring = "Hello World";
int slen;
char *fontname = "9x15";
int xpos,ypos,bwidth,bdepth,xpos1,ypos1,xpos2,ypos2,tx,ty;
Window root;
int var;
KeySym keysym;
char *keyptr;
char keybuffer[20];
XComposeStatus comp;

unsigned long black, white, red;
unsigned long green, blue, magenta,pink;
unsigned long AllocNamedColor();
unsigned long pick_color();

int julia=0;

/* structures for offscreen pixmap */
Pixmap offscreen;

void main(argc,argv)
int argc;
char **argv;
{
int c;


/* Connect to XServer */

if ( (display=XOpenDisplay(display_name)) == NULL)
{
	(void) fprintf( stderr,"XPlad: Doh! cant connect to XServer!");
	XDisplayName(display_name);
	exit (-1);
}

screen=DefaultScreen(display);

display_width=DisplayWidth(display,screen);
display_height=DisplayHeight(display,screen);

width = 758; 
height = 1000;

/* create the main application window */
/* (with black background instead of white) */
win = XCreateSimpleWindow(display,RootWindow(display,screen),
				x,y,width,height,border_width,
				WhitePixel(display,screen),
				BlackPixel(display,screen));

/* create offscreen pixmap */
 offscreen = XCreatePixmap(display,win,display_width,display_height,DefaultDepth(display,screen));


height = display_height;
/* initialize size hints property for window managers */
size_hints.flags = PPosition | PSize | PMinSize;
size_hints.x = 0;
size_hints.y = 0;
size_hints.width = width;
size_hints.height = height;
size_hints.min_width = 50;
size_hints.min_height = 50;

/* set properties for window manager (always before mapping) */

XSetStandardProperties(display,win,window_name,icon_name,
			icon_pixmap, argv, argc, &size_hints);

/* Select Event types wanted */

XSelectInput(display, win, ExposureMask | KeyPressMask | ButtonPressMask | ButtonReleaseMask | StructureNotifyMask);

/* create GC for text and drawing */
gcvalues.foreground = WhitePixel(display,screen);
gcvalues.background = BlackPixel(display,screen);
gc = XCreateGC(display, win,(GCForeground | GCBackground), &gcvalues);

/* define a colormap */
visual = DefaultVisual(display,screen);
colormap = DefaultColormap(display,screen);

/* define the colors */
black = BlackPixel(display, screen);
white = WhitePixel(display, screen);

/* Display window */

XMapWindow(display, win);

/* get events */
/* use first exposure event to triger displaying window muck */

XGetGeometry(display,win,&root,&xpos,&ypos,&width,&height,&bwidth,&bdepth);
 
while (1) 	{
		XFlush(display);
		XNextEvent(display, &report);
		update();
		} /* end while */
}		

int update()
{
		int minutes=random()%30;
                char wait[16]; 
		if (minutes>9)
		snprintf(wait,16,"%d",minutes); else
		snprintf(wait,16,"% d",minutes);

                        XClearWindow(display,win);
                        XSetFont(display,gc,XLoadFont(display,textfont));
                        XDrawString(display,win,gc,0,100,"The next loop bus will arrive in about",38);
                        XSetFont(display,gc,XLoadFont(display,busfont));
                        XDrawString(display,win,gc,-40,600,wait,strlen(wait));
                        XSetFont(display,gc,XLoadFont(display,textfont));
                        XDrawString(display,win,gc,550,650,"minutes.",8);
 return 0;
}

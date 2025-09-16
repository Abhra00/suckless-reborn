static const char *colorname[NUMCOLS] = {
	[INIT]   =   "#c0caf5",     /* after initialization */
	[INPUT]  =   "#9ece6a",     /* during input */
	[FAILED] =   "#ff007c",     /* wrong password */
	[CAPS]   =   "#f7768e",     /* capsLock on */

};

/* treat a cleared input like a wrong password (color) */
static const int failonclear = 1;


/* default message */
static const char * message = "Suckless: Software that sucks less.";

/* text color */
static const char * text_color = "#c0caf5";

/* text size (must be a valid size) */
static const char * font_name = "-misc-fixed-medium-r-semicondensed--13-120-75-75-c-60-iso8859-1";

/* time in seconds before the monitor shuts down */
static const int monitortime = 5;

/* insert grid pattern with scale 1:1, the size can be changed with logosize */
static const int logosize = 75;
/* grid width and height for right center alignment */
static const int logow = 12;
static const int logoh = 6;

static XRectangle rectangles[9] = {
	/* x    y       w       h */
	{ 0,    3,      1,      3 },
	{ 1,    3,      2,      1 },
	{ 0,    5,      8,      1 },
	{ 3,    0,      1,      5 },
	{ 5,    3,      1,      2 },
	{ 7,    3,      1,      2 },
	{ 8,    3,      4,      1 },
	{ 9,    4,      1,      2 },
	{ 11,   4,      1,      2 },
};

/*Enable blur*/
#define BLUR
/*Set blur radius*/
static const int blurRadius=5;
/*Enable Pixelation*/
#define PIXELATION
/*Set pixelation radius*/
static const int pixelSize=5;

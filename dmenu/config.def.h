/* See LICENSE file for copyright and license details. */
/* Default settings; can be overriden by command line. */

static int topbar 		     = 1;                      	/* -b  option; if 0, dmenu appears at bottom     */
static const int user_bh 	     = 15;              	/* add an defined amount of pixels to the bar height */
static const int vertpad 	     = 0;               	/* vertical padding of bar */
static const int sidepad 	     = 0;               	/* horizontal padding of bar */
static int centered 		     = 0;                    	/* -c option; centers dmenu on screen */
static int min_width 		     = 500;                    	/* minimum width when centered */
static const float menu_height_ratio = 4.0f;  			/* This is the ratio used in the original calculation */
static const unsigned int alpha      = 0xff;     	        /* Amount of opacity. 0xff is opaque             */
static const char *fonts[] 	     = {  	    		/* -fn option overrides fonts[0]; default X11 font or font set */
	"IosevkaTerm Nerd Font:style=Medium:size=12",
	"NotoColorEmoji:pixelsize=12:antialias=true:autohint=true"
};
static const char *prompt      		 = NULL;      /* -p  option; prompt to the left of input field */
static const char *colors[SchemeLast][2] = {
	/*                 fg         bg       */
	[SchemeNorm]   = { "#c0caf5", "#1a1b26" },
	[SchemeSel]    = { "#1a1b26", "#7aa2f7" },
	[SchemeOut]    = { "#1a1b26", "#ff007c" },
	[SchemeCursor] = { "#1a1b26", "#c0caf5" },

};

static const unsigned int alphas[SchemeLast][2] = {
	[SchemeNorm] = { OPAQUE, alpha },
	[SchemeSel] = { OPAQUE, alpha },
	[SchemeOut] = { OPAQUE, alpha },
};
/* -l option; if nonzero, dmenu uses vertical list with given number of lines */
static unsigned int lines      = 0;

/*
 * Characters not considered part of a word while deleting words
 * for example: " /?\"&[]"
 */
static const char worddelimiters[] = " ";

/*
 * -vi option; if nonzero, vi mode is always enabled and can be
 * accessed with the global_esc keysym + mod mask
 */
static unsigned int vi_mode = 1;
static unsigned int start_mode = 1;			/* mode to use when -vi is passed. 0 = insert mode, 1 = normal mode */
static Key global_esc = { XK_n, Mod1Mask };		/* escape key when vi mode is not enabled explicitly */
static Key quit_keys[] = {
	/* keysym	modifier */
	{ XK_q,		0 }
};

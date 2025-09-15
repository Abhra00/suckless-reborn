/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "st"
#define TERMCLASS "st-256color"

/* appearance */
static const unsigned int borderpx  	  = 1;       /* border pixel of windows */
static const unsigned int snap      	  = 32;      /* snap pixel */
static const unsigned int gappih    	  = 5;       /* horiz inner gap between windows */
static const unsigned int gappiv    	  = 5;       /* vert inner gap between windows */
static const unsigned int gappoh    	  = 5;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    	  = 5;       /* vert outer gap between windows and screen edge */
static       int smartgaps          	  = 0;       /* 1 means no outer gap when there is only one window */
static const int swallowfloating    	  = 0;       /* 1 means swallow floating windows by default */
static const unsigned int systraypinning  = 0;       /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft   = 0;       /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing  = 2;       /* systray spacing */
static const int systraypinningfailfirst  = 1;       /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const unsigned int systrayiconsize = 30;      /* systray icon size in px */
static const int showsystray        	  = 1;        /* 0 means no systray */
static const int user_bh            	  = 25;       /* 2 is the default spacing around the bar's font */
static const int horizpadbar        	  = 2;        /* horizontal padding for statusbar */
static const int vertpadbar         	  = 10;       /* vertical padding for statusbar */
static const int vertpad            	  = 0;        /* vertical padding of bar */
static const int sidepad            	  = 0;        /* horizontal padding of bar */
static const int showbar            	  = 1;        /* 0 means no bar */
static const int topbar             	  = 1;        /* 0 means bottom bar */
static const char buttonbar[]      	  = "󰣇 ";
static const char *fonts[]          	  = { "Iosevka:style:style=Medium:size=10", "Symbols Nerd Font:size=14" };
static const char dmenufont[]       	  = "IosevkaTerm Nerd Font:size=12";
static const char col_black[] 		  = "#1a1b26";
static const char col_gray[] 		  = "#15161e";
static const char col_blue[] 		  = "#7aa2f7";
static const char col_orange[] 		  = "#ff9e64";
static const char col_red[] 		  = "#f7768e";
static const char col_pink[] 		  = "#ff007c";
static const char col_green[] 		  = "#9ece6a";
static const char col_cyan[] 		  = "#7dcfff";
static const char col_yellow[] 		  = "#9ece6a";
static const char col_magenta[] 	  = "#bb9af7";
static const char col_white[] 	 	  = "#c0caf5";
static const char *colors[][3]      	  = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_white, col_black, col_gray },
	[SchemeBtn]  = { col_blue,  col_black, col_gray },
	[SchemeTle]  = { col_blue,  col_gray,  col_gray },
	[SchemeLt]   = { col_pink,  col_black, col_gray },
	[SchemeSel]  = { col_black, col_blue,  col_pink },
};

/* scratchpads */
typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = { TERMINAL, "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = { TERMINAL, "-n", "spfm", "-g", "144x41", "-e", "yazi", NULL };
const char *spcmd3[] = { TERMINAL, "-n", "spmus", "-g", "144x41", "-e", "rmpc", NULL};
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spranger",    spcmd2},
	{"sprmpc",   	spcmd3},
};


/* sticky indicator icon */
static const XPoint stickyicon[]    = { {0,0}, {4,0}, {4,8}, {2,6}, {0,8}, {0,0} }; /* represents the icon as an array of vertices */
static const XPoint stickyiconbb    = {4,8};	/* defines the bottom right corner of the polygon's bounding box (speeds up scaling) */

/* tagging */
static const char *tags[] = { "dev", "sys", "www", "doc", "vbox", "chat", "mus", "vid", "misc" };
static const char *alttags[] = { "[dev]", "[sys]", "[www]", "[doc]", "[vbox]", "[chat]", "[mus]", "[vid]", "[misc]" };

static const char *tagsel[][2] = {
	{ col_orange, col_gray },
	{ col_orange, col_gray },
	{ col_orange, col_gray },
	{ col_orange, col_gray },
	{ col_orange, col_gray },
	{ col_orange, col_gray },
	{ col_orange, col_gray },
	{ col_orange, col_gray },
	{ col_orange, col_gray },
};

/* underline tags settings */
static const unsigned int ulinepad	= 2;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 2;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 		= 0;	/* 1 to show underline on all tags, 0 for just the active ones */

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",     NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Chromium", NULL,     NULL,           1 << 2,    0,          0,          -1,        -1 },
	{ TERMCLASS,  NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,       NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
	{ TERMCLASS,  "spterm",	NULL,		SPTAG(0),  1,	       1,	    0,        -1 },
	{ TERMCLASS,  "spfm",	NULL,		SPTAG(1),  1,	       1,	    0,        -1 },
	{ TERMCLASS,  "sprmpc",	NULL,		SPTAG(2),  1,	       1, 	    0,        -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int refreshrate = 120;  /* refresh rate (per second) for client move/resize */

/* vanitygaps */
#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#include <X11/XF86keysym.h> /* including function keys */
/* tagging keys */
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* stacking keys */
#define STACKKEYS(MOD,ACTION) \
	{ MOD, XK_j,     ACTION##stack, {.i = INC(+1) } }, \
	{ MOD, XK_k,     ACTION##stack, {.i = INC(-1) } }, \
	{ MOD, XK_grave, ACTION##stack, {.i = 0 } }, \
/*	{ MOD, XK_q,     ACTION##stack, {.i = PREVSEL } }, \ */
/*	{ MOD, XK_a,     ACTION##stack, {.i = 1 } }, \ */
/*	{ MOD, XK_z,     ACTION##stack, {.i = 2 } }, \ */
/*	{ MOD, XK_x,     ACTION##stack, {.i = -1 } }, */

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */

/* dmenu cmd */
static char dmenumon[2] 	   = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] 	   = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_black, "-nf", col_white, "-sb", col_blue, "-sf", col_black, NULL };

/* termcmd */
static const char *termcmd[]  	   = { TERMINAL, NULL };

/* volume control */
static const char *vol_up[]   	   = { "volume", "up",   NULL };
static const char *vol_down[] 	   = { "volume", "down", NULL };
static const char *vol_mute[] 	   = { "volume", "mute", NULL };
static const char *mic_mute[]      = { "audiomicmute",   NULL };

/* brightness control */
static const char *light_up[]      = { "backlight", "up",   NULL };
static const char *light_down[]    = { "backlight", "down", NULL };

/* screenshotcmd */
static const char *sscmd[]         = { "maimshot",  NULL };

/* browsercmd */
static const char *browsercmd[]	   = { "chromium", NULL };

/* dmenuemojicmd */
static const char *emojicmd[]      = { "dmenuunicode",   NULL };

/* powermenu */
static const char *pmenucmd[]      = { "pmenu", NULL };

static const Key keys[] = {
	/* stacker keys */
	/* modifier								    function */
	STACKKEYS(MODKEY,                          		    		    focus)
	STACKKEYS(MODKEY|ShiftMask,                				    push)
	/* modifier                     key        		    function        argument */
	TAGKEYS(                        XK_1,      		                    0)
	TAGKEYS(                        XK_2,      		                    1)
	TAGKEYS(                        XK_3,      		                    2)
	TAGKEYS(                        XK_4,      		                    3)
	TAGKEYS(                        XK_5,      		                    4)
	TAGKEYS(                        XK_6,      		                    5)
	TAGKEYS(                        XK_7,      		                    6)
	TAGKEYS(                        XK_8,      		                    7)
	TAGKEYS(                        XK_9,      		                    8)
	{ MODKEY,                       XK_p,      		    spawn,          {.v = dmenucmd } },
	{ MODKEY,             		XK_Return, 		    spawn,          {.v = termcmd } },
	{ MODKEY,             		XK_w,          		    spawn,          {.v = browsercmd } },
	{ MODKEY,                       XK_e,          		    spawn,          {.v = emojicmd } },
	{ MODKEY,                       XK_Print,      		    spawn,          {.v = sscmd } },
	{ MODKEY|ALTKEY,                XK_x,          		    spawn,          {.v = pmenucmd } },
	{ MODKEY,                       XK_b,      		    togglebar,      {0} },
	{ MODKEY,                       XK_i,      		    incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      		    incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      		    setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      		    setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      		    setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,      		    setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,      		    setcfact,       {.f =  0.00} },
	{ MODKEY,                       XK_Return, 		    zoom,           {0} },
	{ MODKEY|ALTKEY,              	XK_u,      		    incrgaps,       {.i = +1 } },
	{ MODKEY|ALTKEY|ShiftMask,    	XK_u,      		    incrgaps,       {.i = -1 } },
	{ MODKEY|ALTKEY,              	XK_i,      		    incrigaps,      {.i = +1 } },
	{ MODKEY|ALTKEY|ShiftMask,    	XK_i,      		    incrigaps,      {.i = -1 } },
	{ MODKEY|ALTKEY,              	XK_o,      		    incrogaps,      {.i = +1 } },
	{ MODKEY|ALTKEY|ShiftMask,    	XK_o,      		    incrogaps,      {.i = -1 } },
	{ MODKEY|ALTKEY,              	XK_6,      		    incrihgaps,     {.i = +1 } },
	{ MODKEY|ALTKEY|ShiftMask,    	XK_6,      		    incrihgaps,     {.i = -1 } },
	{ MODKEY|ALTKEY,              	XK_7,      		    incrivgaps,     {.i = +1 } },
	{ MODKEY|ALTKEY|ShiftMask,    	XK_7,      		    incrivgaps,     {.i = -1 } },
	{ MODKEY|ALTKEY,              	XK_8,      		    incrohgaps,     {.i = +1 } },
	{ MODKEY|ALTKEY|ShiftMask,    	XK_8,      		    incrohgaps,     {.i = -1 } },
	{ MODKEY|ALTKEY,              	XK_9,      		    incrovgaps,     {.i = +1 } },
	{ MODKEY|ALTKEY|ShiftMask,    	XK_9,      		    incrovgaps,     {.i = -1 } },
	{ MODKEY|ALTKEY,              	XK_0,      		    togglegaps,     {0} },
	{ MODKEY|ALTKEY|ShiftMask,    	XK_0,      		    defaultgaps,    {0} },
	{ MODKEY,                       XK_Tab,    		    view,           {0} },
	{ MODKEY,             		XK_q,      		    killclient,     {0} },
	{ MODKEY,                       XK_t,      		    setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      		    setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      		    setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  		    setlayout,      {0} },
	{ MODKEY|ControlMask,		XK_comma,  		    cyclelayout,    {.i = -1 } },
	{ MODKEY|ALTKEY,                XK_comma, 		    cyclelayout,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_space,  		    togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      		    togglefullscr,  {0} },
	{ MODKEY,                       XK_s,      		    togglesticky,   {0} },
	{ MODKEY,                       XK_0,      		    view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      		    tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  		    focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, 		    focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  		    tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, 		    tagmon,         {.i = +1 } },
	{ MODKEY,            		XK_y,  	   		    togglescratch,  {.ui = 0 } },
	{ MODKEY,            		XK_u,	   		    togglescratch,  {.ui = 1 } },
	{ MODKEY,            		XK_x,	   		    togglescratch,  {.ui = 2 } },
	{ MODKEY|ShiftMask,             XK_q,      		    quit,           {0} },
	{ MODKEY|ALTKEY, 		XK_q,      		    quit,           {1} }, 
	{ 0,         			XF86XK_AudioMute,	    spawn,	    {.v = vol_mute } },
	{ 0,         			XF86XK_AudioRaiseVolume,    spawn,	    {.v = vol_up } },
	{ 0,         			XF86XK_AudioLowerVolume,    spawn,	    {.v = vol_down } },
	{ 0,         			XF86XK_AudioMicMute,	    spawn,	    {.v = mic_mute } },
        { 0,         			XF86XK_MonBrightnessUp,     spawn,          {.v = light_up } },
        { 0,         			XF86XK_MonBrightnessDown,   spawn,          {.v = light_down } }, 
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkButton,		0,		Button1,	spawn,		{.v = dmenucmd } },
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

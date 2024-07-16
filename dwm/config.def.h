/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int splitstatus        = 1;        /* 1 for split status items */
static const char *splitdelim       = ";";       /* Character used for separating status */
static const char *fonts[]          = {"Ubuntu Mono:size=15:weight=regular:pixelsize=22:antialias=true:autohint=true","JoyPixels:style=Bold:pixelsize=16:antialias=true:autohint=true"};
//static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#2067B0";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#ffffff";
static const char col_cyan[]        = "#005577";
static const char evening[]         = "#333333";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray4, evening, evening },
	[SchemeSel]  = { evening, col_gray3, col_gray2},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     iscentered   isfloating   monitor */
	{ "st",       "scpad",       NULL,       0,            1,           1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char  *dmenucmd[] = { "dmenu_run", "-m", dmenumon, NULL };
static const char *termcmd[]  = { "st",NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
//	{ MODKEY,                       XK_b,      spawn,          {.v = dmenucmd } },
//	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} }, /* bat off or on */
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_l,      pushup,         {0} },
	{ MODKEY|ShiftMask,             XK_k,      pushdown,       {0} },
//	{ MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = +1 } }, /*vers le master  */
//	{ MODKEY|ShiftMask,             XK_o,      incnmaster,     {.i = -1 } }, /* l*/
	{ MODKEY,                       XK_j,      setmfact,       {.f = -0.03} },
	{ MODKEY,                       XK_m,      setmfact,       {.f = +0.03} },
	{ MODKEY,                       XK_Return, zoom,           {0} }, /*changer win avec le master*/
	{ MODKEY,                       XK_Tab,    view,           {0} }, 
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
//	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[0]} },
//	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
//	{ MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[2]} }, /* monocle*/
//      { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },/*switch btwn mounitor*/
	{ MODKEY,                       XK_semicolon, focusmon,    {.i = +1 } },/*switch btwn mounitor*/
//      { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },/*envery un fentre  btwn mounitor*/
	{ MODKEY|ShiftMask,             XK_semicolon, tagmon,      {.i = +1 } },/*envery un fentre  btwn mounitor*/
	TAGKEYS(                        XK_ampersand,              0)
	TAGKEYS(                        XK_eacute,                 1)
	TAGKEYS(                        XK_quotedbl,               2)
	TAGKEYS(                        XK_apostrophe,             3)
	TAGKEYS(                        XK_parenleft,              4)
	TAGKEYS(                        XK_minus,                  5)
	TAGKEYS(                        XK_egrave,                 6)
	TAGKEYS(                        XK_underscore,             7)
	TAGKEYS(                        XK_ccedilla,               8)
	{ MODKEY|ControlMask|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
//	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
//	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
//	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
//	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
//	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
//	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
//	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};


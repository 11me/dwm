/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrains Mono:style=Medium:size=10:antialias=true:autohint=true",
                                        "Noto Color Emoji:style=Regular:pixelsize=12:antialias=true:autohint=true"
};
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#212529";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
//static const char col_cyan[]        = "#005577";
static const char text_color[]      = "#f3f4f5";
static const char bg_color1[]       = "#3399ff";
static const char bg_color2[]       = "#0d1b2a";
//static const char border_color[]    = "#0066ff";
static const char border_color[]    = "#61afef";

/* ********************* ONEDARK COLORS ****************/
static const char col_black[]         = "#282c34";
static const char col_grey[]          = "#4b5263";
static const char col_white[]         = "#f3f4f5";
static const char col_blue[]          = "#61afef";
static const char col_magenta[]       = "#c678dd";
static const char col_cyan[]          = "#56b6c2";
static const char col_light_red[]     = "#e06c75";
static const char col_dark_red[]      = "#be5046";
static const char col_green[]         = "#98c379";
static const char col_light_yellow[]  = "#e5c07b";
static const char col_dark_yellow[]   = "#d19a66";

static const char *colors[][3] = {
	/*               fg         bg         border   */
	[SchemeNorm] = { text_color, bg_color2, col_gray2 },
	[SchemeSel]  = { text_color, bg_color1, border_color  },

	[SchemeStatus]    = { col_white, col_black,  "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel]   = { col_white, col_grey,  "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
    [SchemeTagsNorm]  = { col_white, col_black,  "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
    [SchemeInfoSel]   = { col_white, col_black,  "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
    [SchemeInfoNorm]  = { col_green, col_black,  "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}

};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
    	/* class     instance  title           tags mask  isfloating  isterminal  noswallow    monitor    scratchpad*/
	{ "Gimp",                NULL,      NULL,           0,         1,          0,           0,        -1,				 0 },
	{ "Firefox",             NULL,      NULL,           0,         0,          0,          -1,        -1,				 0 },
	{ "St",                  NULL,      NULL,           0,         0,          1,           0,        -1,				 0 },
	{ "TelegramDesktop",     NULL,      NULL,           0,         1,          0,          -1,        -1,				 0 },
	{ "Pavucontrol",         NULL,      NULL,           0,         1,          0,          -1,        -1,				 0 },
	{ "Thunar",              NULL,      NULL,           0,         1,          0,          -1,        -1,				 0 },
    { "Zotero",             "Toplevel", NULL,           0,         1,          0,          -1         -1,				 0 },
	{ NULL,                  NULL,     "Event Tester",  0,         0,          0,           1,        -1,				 0 }, /* xev */
	{ NULL,                  NULL,     "scratchpad",    0,         1,          1,           0,        -1,               's'},
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "H[]",      deck },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
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
static const char *dmenucmd[] = { "dmenu_run", NULL};
static const char *termcmd[]  = { "st", NULL };

/*First arg only serves to match against key in rules*/
static const char *scratchpadcmd[] = {"s", "st", "-t", "scratchpad", NULL};

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_w,      spawn,          SHCMD("$BROWSER") },
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
/*  { MODKEY,                       XK_Return, spawn,          {.v = termcmd } }, */
	{ MODKEY,                       XK_Return, spawn,          SHCMD("$TERMINAL") },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_space,  zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_y,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_y,      setlayout,      {.v = &layouts[3]} },
    { MODKEY,                       XK_u,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY|ShiftMask,             XK_u,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY,                       XK_i,      setlayout,      {.v = &layouts[6]} },
	{ MODKEY|ShiftMask,             XK_i,      setlayout,      {.v = &layouts[7]} },
	//{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY,                       XK_apostrophe,  togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

    // vanitygaps
	{ MODKEY,                       XK_z,      incrgaps,       {.i = +3 } },
	{ MODKEY,                       XK_x,      incrgaps,       {.i = -3 } },
	{ MODKEY,                       XK_a,      togglegaps,     {0} },
	{ MODKEY|ShiftMask,             XK_a,      defaultgaps,    {0} },
//	{ MODKEY|Mod4Mask,              XK_i,      incrigaps,      {.i = +1 } },
//	{ MODKEY|Mod4Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
//	{ MODKEY|Mod4Mask,              XK_o,      incrogaps,      {.i = +1 } },
//	{ MODKEY|Mod4Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
//	{ MODKEY|Mod4Mask,              XK_6,      incrihgaps,     {.i = +1 } },
//	{ MODKEY|Mod4Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
//	{ MODKEY|Mod4Mask,              XK_7,      incrivgaps,     {.i = +1 } },
//	{ MODKEY|Mod4Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
//	{ MODKEY|Mod4Mask,              XK_8,      incrohgaps,     {.i = +1 } },
//	{ MODKEY|Mod4Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
//	{ MODKEY|Mod4Mask,              XK_9,      incrovgaps,     {.i = +1 } },
//	{ MODKEY|Mod4Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {1} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
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

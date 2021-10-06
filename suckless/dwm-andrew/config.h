/* appearance */
static const unsigned int borderpx = 5;   /* border pixel of windows */
static const unsigned int snap     = 32;
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const unsigned int gappx    = 1;   /* pixel gap between clients */
static const int showbar           = 1;   /* 0 means no bar */
static const int topbar            = 1;   /* 0 means bottom bar */
static const int horizpadbar       = 6;   /* horizontal padding for statusbar */
static const int vertpadbar        = 7;   /* vertical padding for statusbar */
/* Mononoki Nerd Font must be installed from AUR nerd-fonts-complete.
 * Otherwise, your default font will be Hack which is found in the standard
 * Arch repos and is listed as a dependency for this build. JoyPixels is also
 * a hard dependency and makes colored fonts and emojis possible.
 */
static const char *fonts[]     = {"Mononoki Nerd Font:size=10:4a4n4tialias=true:autohint=true",
                                  "Hack:size=14:antialias=true:autohint=true",
                                  "JoyPixels:size=14:antialias=true:autohint=true"
								  "ttf-font-awesome:size=14:antialias=true:autohint=true"
						     	};
static const char col_1[]  = "#000000"; /* background color of bar */
static const char col_2[]  = "#000000"; /* border color unfocused windows */
static const char col_3[]  = "#a82700";
static const char col_4[]  = "#3D0700"; /* border color focused windows and tags */
/* bar opacity
 * 0xff is no transparency.
 * 0xee adds wee bit of transparency.
 * 0xdd adds adds a bit more transparency.
 * Play with the value to get desired transparency.
 */
static const unsigned int baralpha    = 0xff;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]        = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_3, col_1, col_2 },
	[SchemeSel]  = { col_3, col_4, col_4 },
};
static const unsigned int alphas[][3] = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
/* static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" }; */
static const char *tags[] = { "", "", "", "", "", "", "", "", ""};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                instance    title       tags mask     isfloating   monitor */
	{ "discord",            NULL,       NULL,       1 << 4,            0,           -1 },
	{ "Brave",              NULL,       NULL,       1,                 0,           -1 },
	{ "Emacs",              NULL,       NULL,       1 << 3,            0,           -1 },
	{ "mpv",                NULL,       NULL,       1 << 1,            0,           -1 },
	{ "st",                 NULL,       NULL,       0,                 0,           -1 },
	{ "qbittorrent",        NULL,       NULL,       1 << 6,            0,           -1 },
	{ "virtualbox",         NULL,       NULL,       1 << 2,            0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include "layouts.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      tile },    /* first entry is default */
	{ "",      NULL },    /* no layout function means floating behavior */
	{ "",      monocle },
	{ "",      grid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(CHAIN,KEY,TAG) \
	{ MODKEY,                       CHAIN,    KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           CHAIN,    KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             CHAIN,    KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, CHAIN,    KEY,      toggletag,      {.ui = 1 << TAG} },
#define CMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* dmenu */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
/* If you are using the standard dmenu program, use the following. */
static const char *dmenucmd[]    = { "dmenu_run", "-p", "Run: ", "-c", "-bw", "2", "-l", "20", "-g", "2", NULL };
/* If you are using the dmenu-distrotube-git program, use the following for a cooler dmenu! */
/* static const char *dmenucmd[]    = { "dmenu_run", "-g", "10", "-l", "48", "-p", "Run: ", NULL }; */

/* the st terminal with tabbed */
static const char *termcmd[]     = { "alacritty", NULL };
/* An alternative way to launch st along with the fish shell */
/* static const char *termcmd[]     = { "st", "-e fish", NULL }; */
static const char *tabtermcmd[]  = { "tabbed", "-r", "2", "st", "-w", "''", NULL };

static Key keys[] = {
	/* modifier             chain key  key        function        argument */
	{ MODKEY|ShiftMask,     -1,        XK_Return, spawn,          {.v = dmenucmd } },
	{ MODKEY,               -1,        XK_Return, spawn,          {.v = termcmd } },
	{ Mod1Mask,             -1,        XK_Return, spawn,          {.v = tabtermcmd } },
	{ MODKEY,               -1,        XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,     -1,        XK_j,      rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,     -1,        XK_k,      rotatestack,    {.i = -1 } },
	{ Mod1Mask,             -1,        XK_Tab,    focusstack,     {.i = +1 } },
	{ MODKEY,               -1,        XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,               -1,        XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,               -1,        XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,               -1,        XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,               -1,        XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ControlMask,   -1,        XK_Return, zoom,           {0} },
	{ MODKEY|ShiftMask,     -1,        XK_c,      killclient,     {0} },

    /* Layout manipulation */
	{ MODKEY,               -1,        XK_Tab,    cyclelayout,    {.i = -1 } },
	{ MODKEY|ShiftMask,     -1,        XK_Tab,    cyclelayout,    {.i = +1 } },
	{ MODKEY,               -1,        XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,     -1,        XK_space,  togglefloating, {0} },

    /* Switch to specific layouts */
	{ MODKEY,               -1,        XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,               -1,        XK_x,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,               -1,        XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,               -1,        XK_g,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,               -1,        XK_u,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,               -1,        XK_o,      setlayout,      {.v = &layouts[5]} },

	{ MODKEY,               -1,        XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,     -1,        XK_0,      tag,            {.ui = ~0 } },

    /* Switching between monitors */
	{ MODKEY,               -1,        XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,               -1,        XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,     -1,        XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,     -1,        XK_period, tagmon,         {.i = +1 } },

	/* Bindings to programs with Only Modkey */
	{ MODKEY,               -1,        XK_q,      spawn,          CMD("kill -HUP dwm") },
	{ MODKEY,               -1,        XK_f,      spawn,          CMD("alacritty -e fish -c ~/.config/vifm/scripts/vifmrun") },
	{ MODKEY,               -1,        XK_Up,     spawn,          CMD("pamixer -i 5") },
	{ MODKEY,               -1,        XK_Down,   spawn,          CMD("pamixer -d 5") },

	/* Bindings to programs with shiftmask */
	{ MODKEY|ShiftMask,     -1,        XK_f,      spawn,          CMD("thunar") },
	{ MODKEY|ShiftMask,     -1,        XK_m,      spawn,          CMD("alacritty -e mocp") },
	{ MODKEY|ShiftMask,     -1,        XK_t,      spawn,          CMD("alacritty -e rtorrent") },
	{ MODKEY|ShiftMask,     -1,        XK_s,      spawn,          CMD("/home/andrew/.scripts/run-script") },

    /* Keybindings for programs using the format SUPER + ALT + "key" */
	{ MODKEY|Mod1Mask,      -1,        XK_b,      spawn,          CMD("brave") },
	{ MODKEY|Mod1Mask,      -1,        XK_Return, spawn,          CMD("run_command") },
	{ MODKEY|Mod1Mask,      XK_d,      XK_d,      spawn,          CMD("discord") },
	{ MODKEY|Mod1Mask,      XK_l,      XK_l,      spawn,          CMD("slock") },
	{ MODKEY|Mod1Mask,      XK_p,      XK_p,      spawn,          CMD("/home/andrew/.scripts/get-pass") },
	{ MODKEY|Mod1Mask,      XK_u,      XK_u,      spawn,          CMD("/home/andrew/.scripts/get-user") },
	{ MODKEY|Mod1Mask,      XK_c,      XK_c,      spawn,          CMD("/home/andrew/.scripts/get-configs") },
	{ MODKEY|Mod1Mask,      XK_r,      XK_m,      spawn,          CMD("/home/andrew/dmscripts/scripts/dm-man") },
	{ MODKEY|Mod1Mask,      -1,        XK_t,      spawn,          CMD("/home/andrew/.scripts/get-term-apps") },
	{ MODKEY|Mod1Mask,      -1,        XK_m,      spawn,          CMD("/home/andrew/.scripts/download-music") },
	{ MODKEY|Mod1Mask,      XK_e,      XK_f,      spawn,          CMD("emacs ~/.config/fish/config.fish") },
	{ MODKEY|Mod1Mask,      -1,        XK_y,      spawn,          CMD("ytfzf -D") },
	{ MODKEY|Mod1Mask,      -1,        XK_s,      spawn,          CMD("/home/andrew/.scripts/screenshot") },

	    /* Doom emacs keybindings use the keychord CTRL + e followed by "key" */
	{ ControlMask,          XK_e,      XK_e,      spawn,          CMD("emacsclient -c -a 'emacs'") },

	TAGKEYS(                -1,        XK_1,                      0)
	TAGKEYS(                -1,        XK_2,                      1)
	TAGKEYS(                -1,        XK_3,                      2)
	TAGKEYS(                -1,        XK_4,                      3)
	TAGKEYS(                -1,        XK_5,                      4)
	TAGKEYS(                -1,        XK_6,                      5)
	TAGKEYS(                -1,        XK_7,                      6)
	TAGKEYS(                -1,        XK_8,                      7)
	TAGKEYS(                -1,        XK_9,                      8)
	{ MODKEY|ShiftMask,     -1,        XK_q,	  quit,		      {0} },
    { MODKEY|ShiftMask,     -1,        XK_r,      quit,           {1} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click           event mask   button          function        argument */
	{ ClkLtSymbol,     0,           Button1,        setlayout,      {0} },
	{ ClkLtSymbol,     0,           Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,     0,           Button2,        zoom,           {0} },
	{ ClkStatusText,   0,           Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,    MODKEY,      Button1,        movemouse,      {0} },
	{ ClkClientWin,    MODKEY,      Button2,        togglefloating, {0} },
	{ ClkClientWin,    MODKEY,      Button3,        resizemouse,    {0} },
	{ ClkTagBar,       0,           Button1,        view,           {0} },
	{ ClkTagBar,       0,           Button3,        toggleview,     {0} },
	{ ClkTagBar,       MODKEY,      Button1,        tag,            {0} },
	{ ClkTagBar,       MODKEY,      Button3,        toggletag,      {0} },
};

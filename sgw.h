!===============================================================================!
! sgw.h - Simple Glulxe Wrapper for Inform
!===============================================================================!
! by Alessandro Schillaci, Vincenzo Scarpa, Paolo Maroncelli, Paolo Lucchesi
!
! WeB   : http://slade.altervista.org
! @mail : silver.slade@tiscalinet.it
!
! Version 1.6.3 2008-10-14
!===============================================================================!
!
! WHAT IS THIS FOR ?
! ==================
! "sgw.h" (this file) is a simple and small glulxe wrapper, created for a novice
! inform programming level.
! With this library it's possible to visualize an image or simply to play a sound
! (or a music) by using a small set of functions that wrap the glulx functions.
! There are also text styles ready to be used.
!
! It's possible to convert a z-code adventure to a glulx adventure with
! multimedia support, in few steps.
!
! You can use 3 audio channels:
!
! - music : for the music channel
! - chan1 : channel 1 for audio (sound effects)
! - chan2 : channel 2 for audio (sound effects)
!
!===============================================================================!
!
! HOW TO USE
! ==========
!
! Just follow these points:
!
! 1) Put in your main file the directive
!    include "sgw.h";
!    just after the Include "parser"; directive
!
! 2) Now you can play a sound or visualize an image simply using these functions into your Inform
!    code: viewImageLeft (or viewImageCenter or viewImageRight) and playSound()
!
! 3) You can customize colors settings or image window height, defining the following 
!    Constants before you include the "sgw.h" library (to override the default
!    setting):
!
!    SGWHEIGHT  Image window height, in pixels
!    SCBACK     Background color
!    SCTEXT     Main text color
!    SCSOFT     Soft text color
!    SCEMPH     Emphatized text color
!    SCHEAD     Headers color
!    SCINPU     Input line color
!
!    (you can use the $rrggbb format for specify hexadecimal rgb color codes)
!
!    For example
!       Constant SGWHEIGHT 250;
!    sets the image window height to 250 pixels, while
!       Constant SCBACK $440044;
!    sets the background to a dark violet 
!
! 4) If you want to use ONLY the sounds (no graphics) or ONLY the images you 
!    define one of these constants
!
!    Constant NOGRAPHICS;
!
!    Constant NOSOUND;
!
!    Before you Include the sgw.h library
!
! 5) If you want to use the text styles (examples):
!
!  with description [;
!             print "Text Style ", (s_emph) "Emphasized", "^";
!             print "Text Style ", (s_bold) "Bold", " (like Inform)^";
!             print "Text Style ", (s_pref) "Preformatted", "^";
!             print "Text Style ", (s_fixed) "Fixed", " (like Inform)^";
!             print "Text Style ", (s_head) "Header", "^";
!             print "Text Style ", (s_subhead) "Subheader", "^";
!             print "Text Style ", (s_alert) "Alert", "^";
!             print "Text Style ", (s_reverse) "Reverse", " (like Inform)^";
!             print "Text Style ", (s_note) "Note", "^";
!             print "Text Style ", (s_underline) "Underline/Italic", " (like Inform)^";
!             print "Text Style ", (s_block) "BlockQuote", "^";
!             print "Text Style ", (s_input) "Input", "^";
!       ],
!
!  These are also valid in z-code
!
!  (you can still use the classic "style bold", "style roman", etc. inform directives)
!
!
! 6) You can use these new simple functions in your game, also :
!
! GRAPHIC FUNCTIONS
! =================
! clearMainWindow()                     = clears the main window
! closeAllWindows()                     = closes all graphic windows
! initializeSGW(h)                      = graphic window dimension is set to h=height
! viewImageLeft(image)                  = shows the "image" in the graphic window on the Left
! viewImageCenter(image, image_width)   = shows the "image" in the graphic window (Centered)
! viewImageRight(image, image_width)    = shows the "image" in the graphic window on the Right
!
!
! AUDIO FUNCTIONS
! ===============
! playSound(channel,sound,length,volume)    = plays a sound/music
! setplayMusic(sound,length,volume)         = enque a music to be played (not working)
! fadeoutMusic()                            = fades out current music
! fadetoMusic(sound,length,volume)          = 
! silenceAll()                              = silences all audio channels
! silenceChannel(channel)                   = silences the audio "channel"
! setVolume(val, channel)                   = set "val" for volume of the channel
!
! length is the no. of times that the sound/music will be played (-1 to play continuously)
!
! 7) SGW automatically handles the HandleGlkEvent, InitGlkWindow and IdentifyGlkObject
!    entry points. If you need to define your own version of one or more of these 
!    entry points, you can define one or more of the following constants:
!
!        CUSTOM_HANDLEGLKEVENT
!        CUSTOM_INITGLKWINDOW
!        CUSTOM_IDENTIFYGLKOBJECT
!
!    before including sgw.h
!    In your entry points, you can invoke the appropriate the SGW related functions 
!    calling the following routines:
!
!        SGWHandleGlkEvent(event)
!        SGWInitGlkWindow(winrock)
!        SGWIdentifyGlkObject(phase,type,ref,rock)
!
!    Finally, from your InitGlkWindow entry point, you can call the
!    SGWDefineWindowColors() routine to set the defined colors for every
!    other window
!
!===============================================================================!
! LICENSE
! =======
!
! This file is free software, it can be freely used, copied, distribuited and
! modified. Any modified or unmodified copy of this file distribuited as source
! code must acknoledge the original author and must be freely usable, copyable,
! distributable and modifiable.
! There's absolutely no condition or binding on the distribution as compiled
! binary file.
! This software is distribuited as-is, with NO WARRANTY. The author cannot be
! held as responsable for any damage due directly or indirectly to this file.
!
!===============================================================================!

System_file;

message "Using the SGW 1.6.2 (Simple Glulxe Wrapper) library by Alessandro Schillaci";

#Ifdef NOGRAPHICS;
    message "[SGW] Using ONLY sounds";
#Endif;

Default SGWHEIGHT 200;

Global music                    = 0;            ! Music Channel
Global chan1                    = 0;            ! Channel 1 sound effects
Global chan2                    = 0;            ! Channel 2 sound effects

Constant VOLUME_HIGH            4;
Constant VOLUME_NORMAL          3;
Constant VOLUME_LOW             2;

#IfDef TARGET_GLULX;

Global ggraphic = true;
Global gsound = true;
Global gvolume = true;
Global gnotify = true;
Global gtimer = true;

Global current_music            = 0;
Global current_loops            = 0;
Global current_volume           = 0;
Global fading                   = 0;
Global volume_value             = 0;
Global next_music               = 0;
Global next_loops               = 0;
Global next_volume              = 0;
!Global gg_VolumeSupport            = false;        ! Change Volume supported?
Global gg_statuswin;
Global gg_mainwin;                                ! Text window
Global gg_bigwin;                                ! Image Location window
Global curr_pic;
Global curr_pic_pos;
Global curr_pic_width;
Global curr_height;

Constant GG_MUSICCHAN_ROCK          410;
Constant GG_MUSICCHANSOUND1_ROCK    411;
Constant GG_MUSICCHANSOUND2_ROCK    412;
Constant GG_BIGWIN_ROCK             210;        ! Image Location window

! Position constants - added by Paolo Maroncelli
Constant POS_GG_LEFT                1;
Constant POS_GG_CENTER              2;
Constant POS_GG_RIGHT               3;

! Colors constants - added by Vincenzo Scarpa
Default CLR_GG_AZURE                 $30ffff;
Default CLR_GG_BLACK                 $000000;
Default CLR_GG_BLUE                  $0000a0;
Default CLR_GG_BROWN                 $7f3f00;
Default CLR_GG_CYAN                  $30ffff;
Default CLR_GG_GREEN                 $30ff30;
Default CLR_GG_GREY                  $bfbfbf;
Default CLR_GG_MAGENTA               $ff30ff;
Default CLR_GG_ORANGE                $ff7f00;
Default CLR_GG_PINK                  $ff7fff;
Default CLR_GG_PURPLE                $ff30ff;
Default CLR_GG_RED                   $ff3030;
Default CLR_GG_YELLOW                $ffff30;
Default CLR_GG_WHITE                 $ffffff;
Default CLR_GG_PERSBACK              $110101;
Default CLR_GG_PERSTEXT              $DDBB99;
Default CLR_GG_PERSSOFT              $665544;
Default CLR_GG_PERSEMPH              $FFFFDD;
Default CLR_GG_PERSHEAD              $EEDDAA;
Default CLR_GG_PERSINPU              $DDEEAA;

! Colors settings
Default SCBACK                       CLR_GG_PERSBACK;
Default SCTEXT                       CLR_GG_PERSTEXT;
Default SCSOFT                       CLR_GG_PERSSOFT;
Default SCEMPH                       CLR_GG_PERSEMPH;
Default SCHEAD                       CLR_GG_PERSHEAD;
Default SCINPU                       CLR_GG_PERSINPU;

! Legacy
[ initializeSGW h; SGWreset(h); ]; 

[ SGWreset h;
        if (h == 0) h = SGWHEIGHT;
        if (music == 0) {music = glk_schannel_create(GG_MUSICCHAN_ROCK);          }
        if (chan1 == 0) {chan1 = glk_schannel_create(GG_MUSICCHANSOUND1_ROCK);    }
        if (chan2 == 0) {chan2 = glk_schannel_create(GG_MUSICCHANSOUND2_ROCK);    }
        if (music) setVolume(VOLUME_NORMAL, music);
        if (chan1) setVolume(VOLUME_NORMAL, chan1);
        if (chan2) setVolume(VOLUME_NORMAL, chan2);
        testGlulx();        ! Test about Interpreter's performances
        closeAllWindows();  ! Closing all window
        silenceAll();       ! Silence all audio channels
        inizializeGlulx(h); ! Inizialize the glulx system
];

#EndIf;

Stub initializeSGW 1;
Stub SGWreset 1;

Object "(sgw)" LibraryExtensions
  with ext_initialise [; SGWreset(); ];

Default CLR_GG_AZURE                 CLR_AZURE;
Default CLR_GG_BLACK                 CLR_BLACK;
Default CLR_GG_BLUE                  CLR_BLUE;
Default CLR_GG_BROWN                 CLR_PURPLE;
Default CLR_GG_CYAN                  CLR_CYAN;
Default CLR_GG_GREEN                 CLR_GREEN;
Default CLR_GG_GREY                  CLR_BLACK;
Default CLR_GG_MAGENTA               CLR_MAGENTA;
Default CLR_GG_ORANGE                CLR_RED;
Default CLR_GG_PINK                  CLR_RED;
Default CLR_GG_PURPLE                CLR_PURPLE;
Default CLR_GG_RED                   CLR_RED;
Default CLR_GG_YELLOW                CLR_YELLOW;
Default CLR_GG_WHITE                 CLR_WHITE;

! --- Texts functions - added by Vincenzo Scarpa -------------------------------------

! Mostly left for legacy reasons

! Text in Emphasized style
[ s_emph text;
       style underline; ! style_Emphasized
       print (string) text;
       style roman;
];

! Text in Underline/Italic style (like z-code)
[ s_underline text;
       print (s_note) text;
];

! Text in Preformatted style
[ s_pref text;
       style fixed; ! style_Preformatted
       print (string) text;
       style roman;
];

! Text in Fixed style (like z-code)
[ s_fixed text;
       print (s_pref) text;
];

! Text in Header style
[ s_head text;
    #IfDef TARGET_GLULX;
       glk_set_style(style_Header);
       print (string) text;
       glk_set_style(style_Normal);
    #IfNot;
       style bold;
       print (string) text;
       style roman;
    #EndIf;
];

! Text in Subheader style
[ s_subhead text;
       style bold; ! style_Subheader
       print (string) text;
       style roman;
];

! Text in Bold style (like z-code)
[ s_bold text;
       print (s_subhead) text;
];

! Text in Alert style
[ s_alert text;
       style reverse; ! style_Alert
       print (string) text;
       style roman;
];

! Text in Reverse style (like z-code)
[ s_reverse text;
       print (s_alert) text;
];

! Text in Note style
[ s_note text;
    #IfDef TARGET_GLULX;
       glk_set_style(style_Note);
       print (string) text;
       glk_set_style(style_Normal);
    #IfNot;
       style underline;
       print (string) text;
       style roman;
    #EndIf;
];

! Text in BlockQuote style
[ s_block text;
    #IfDef TARGET_GLULX;
       glk_set_style(style_BlockQuote);
       print (string) text;
       glk_set_style(style_Normal);
    #IfNot;
       style bold;
       print (string) text;
       style roman;
    #EndIf;       
];

! Text in Input style
[ s_input text;
    #IfDef TARGET_GLULX;
       glk_set_style(style_Input);
       print (string) text;
       glk_set_style(style_Normal);
    #IfNot;
       print (string) text;
    #EndIf;       
];

! --- Graphics functions -------------------------------------------------------------

#IfDef TARGET_GLULX;
#IfnDef NOGRAPHICS;    

! Centralized visualization routine - added by Paolo Maroncelli

[ viewImageSGW finestra_larghezza x_pos;
    glk_window_clear(gg_bigwin);
    glk_window_get_size(gg_bigwin, gg_arguments, gg_arguments+WORDSIZE);
    finestra_larghezza = gg_arguments-->0;
    switch (curr_pic_pos) {
        POS_GG_LEFT:     x_pos = 0;
        POS_GG_CENTER:   x_pos = (finestra_larghezza/2)-(curr_pic_width/2);
        POS_GG_RIGHT:    x_pos = (finestra_larghezza)-(curr_pic_width);
    }
    if (gg_bigwin && glk_gestalt(gestalt_Graphics, 0)) {
        glk_image_draw(gg_bigwin, curr_pic, x_pos, 0);
    }
];

! View an image on the left of the main graphic window
[ viewImageLeft image;
    curr_pic = image;
    curr_pic_pos = POS_GG_LEFT;
    curr_pic_width = 0;
    viewImageSGW();
];

! View an image on the center of the main graphic window
[ viewImageCenter image image_width;
    curr_pic = image;
    curr_pic_pos = POS_GG_CENTER;
    curr_pic_width = image_width;
    viewImageSGW();
];

! View an image on the right of the main graphic window
[ viewImageRight image image_width;
    curr_pic = image;
    curr_pic_pos = POS_GG_RIGHT;
    curr_pic_width = image_width;
    viewImageSGW();    
];

! Clean the main window
[ clearMainWindow;
    glk_window_set_background_color(gg_mainwin,SCBACK);
    glk_window_clear(gg_mainwin);
    glk_window_set_background_color(gg_bigwin,SCBACK);
    glk_window_clear(gg_bigwin);
];

! Close all windows
[ closeAllWindows;
    if (gg_bigwin) {
        glk_window_close(gg_bigwin,0);
        gg_bigwin = 0;
    }
];

! Redraws an image
[ MyRedrawGraphicsWindows ;
    viewImageSGW();
];

! Reopen window, redraws the image
[ SGWOpenWindow;
   if (gg_bigwin == 0) {
       gg_bigwin = glk_window_open(gg_mainwin,(winmethod_Above+winmethod_Fixed), curr_height , wintype_Graphics, GG_BIGWIN_ROCK);
    }
    glk_window_set_background_color(gg_bigwin,SCBACK);
    glk_window_clear(gg_bigwin);    
    viewImageSGW();
];

[ SGWCloseWindow;
    if (gg_bigwin) {
        glk_window_close(gg_bigwin,0);
        gg_bigwin = 0;
    }
];

#EndIf;
#EndIf;

Stub viewImageSGW 2;
Stub viewImageLeft 1;
Stub viewImageCenter 2;
Stub viewImageRight 2;
Stub clearMainWindow 0;
Stub closeAllWindows 0;
Stub MyRedrawGraphicsWindows 0;
Stub SGWOpenWindow 0;
Stub SGWCloseWindow 0;

![ MyRedrawGraphicsWindows finestra_larghezza;
!    #Ifdef TARGET_GLULX;
!        #Ifndef NOGRAPHICS;
!            ! WIDTH for center image
!            glk_window_set_background_color(gg_bigwin,SCBACK);
!            #Ifdef SGW_WIDTH;
!                glk_window_get_size(gg_bigwin, gg_arguments, gg_arguments+WORDSIZE);
!                finestra_larghezza = gg_arguments-->0;
!                glk_window_clear(gg_bigwin);
!                if (gg_bigwin && glk_gestalt(gestalt_Graphics, 0)) {
!                    glk_image_draw(gg_bigwin, curr_pic, ((finestra_larghezza/2)-(SGW_WIDTH/2)), 0);
!                }
!            #Ifnot;
!                if (gg_bigwin && glk_gestalt(gestalt_Graphics, 0)) {
!                    glk_image_draw(gg_bigwin, curr_pic, 0, 0);
!                }
!            #endif;
!        #endif;
!    #endif;
!];

! --- Audio functions -------------------------------------------------------------

#IfDef TARGET_GLULX;
#IfNDef NOSOUND;

! Plays the sound "sound" for the channel "channel" , with "length" and "volume"
[ playSound channel sound length volume evid;
    if (~~gsound) rfalse;
    evid = 0;
    if (channel == chan1) evid = 1;
    if (channel == chan2) evid = 2;
    if (channel == music) { evid = 5; current_music = sound; }
    if (length == 0) length = 1;
    glk_schannel_stop(channel);
    SetVolume(volume,channel);
    glk_schannel_play_ext(channel, sound, length, 0); 
      ! L'ultimo parametro era evid, ma mandava in crash Gargoyle
];

[ setplayMusic sound length volume;
    if (~~gsound) rfalse;
    if (length == 0) length = 1;
    if (~~gnotify) { playSound(music, sound, length, volume); rtrue; }
    playSound(music, sound, length, volume); rtrue;  ! Per i problemi di Gargoyle
!    if (current_music == 0) {
!        next_music = 0;
!        current_loops = length;
!        playSound(music, sound, 1, volume);
!    } else {
!        next_music = sound;
!        next_volume = volume;
!        next_loops = length;
!    }
];

[ fadeoutMusic;
    if ((~~gtimer) || (~~gvolume)) rfalse;
    if (current_music == 0) rfalse;
    fading = 1;
    glk_request_timer_events(25);
];

[ fadetoMusic sound length volume;
    if (current_music == 0) {
        next_music = 0;
        current_loops = length;
        playSound(music, sound, 1, volume);
    } else {
        next_music = sound;
        next_volume = volume;
        next_loops = length;
        fading = 2;
        glk_request_timer_events(25);        
    }        
];

! Sileces all the audio channels
[ silenceAll;
    if (chan1) glk_schannel_stop(chan1);
    if (chan2) glk_schannel_stop(chan2);
    if (music) glk_schannel_stop(music);
];

! Silences the channel "channel"
[ silenceChannel channel;
    if (channel) glk_schannel_stop(channel);
];

! Reset all audio channels
[ resetMusicChannel;
    glk_schannel_stop(music);
    glk_schannel_stop(chan1);
    glk_schannel_stop(chan2);
];

! Set a volume for the channel
[ setVolume val chan;
    if (~~gvolume) return;
    if (val > 0) {
      glk_schannel_set_volume(chan, val * 16384);
      if (chan == music) { current_volume = val; volume_value = val * 16384; }
    }
];

#EndIf;
#EndIf;

#IfnDef playSound; [playSound x1 x2 x3 x4; x1=x2; x3=x4; ]; #EndIf;
Stub setplayMusic 3;
Stub fadeoutMusic 0;
Stub fadetoMusic 3;
Stub silenceAll 0;
Stub silenceChannel 1;
Stub resetMusicChannel 0;
Stub setVolume 2;

! --- GLULX functions ------------------------------------------------------------- !

#IfDef TARGET_GLULX;

#IfnDef CUSTOM_HANDLEGLKEVENT;
[ HandleGlkEvent event; SGWHandleGlkEvent(event); ];
#EndIf;

[ SGWHandleGlkEvent event ;
    switch (event-->0) {
            evtype_Redraw, evtype_Arrange  :    MyRedrawGraphicsWindows();
                    !evtype_SoundNotify:            glk_schannel_play_ext(music, current_music, 1, 1);
          #IfnDef NOSOUND;
    		evtype_SoundNotify:
              if ((event-->3) == 5) { ! channel == music (bloccato)
                  if (next_music) {
                    current_loops = next_loops;
                    playSound(music, next_music, 1, next_volume);
                  } else {
                    if (current_loops > 0) current_loops--;
                    if (current_loops == 0) current_music = 0;
                    if (current_music) playSound(music, current_music, 1, 0);
                    };
                    
              }
            evtype_Timer:
              if (fading) {
                volume_value = volume_value - 256;
                if (volume_value > 32768) volume_value = volume_value - 256;
                if (volume_value < 0) volume_value = 0;
                glk_schannel_set_volume(music, volume_value);
                if (volume_value == 0) {
                    glk_schannel_stop(music);
                    setVolume(current_volume, music);
                    glk_request_timer_events(0);
                    if (fading == 2 && next_music) playSound(music, next_music, next_loops, next_volume);
                    fading = false;
                }
              }
		  #EndIf;
        4:                ! mouse
        5, 6:            ! arrange/redraw
    }
];

! Glk window initialization entry point.
#IfnDef CUSTOM_INITGLKWINDOW;
[ InitGlkWindow winrock; SGWInitGlkWindow(winrock); rfalse; ];
#EndIf;

[ SGWInitGlkWindow winrock;
    switch (winrock) {
         GG_MAINWIN_ROCK, GG_STATUSWIN_ROCK, GG_BIGWIN_ROCK: SGWDefineWindowColors();
    }
    rfalse;
];

[ SGWDefineWindowColors;
            glk_stylehint_set(wintype_AllTypes, style_Normal, stylehint_TextColor, SCTEXT);
            glk_stylehint_set(wintype_AllTypes, style_Normal, stylehint_BackColor, SCBACK);
            glk_stylehint_set(wintype_AllTypes, style_Normal, stylehint_Justification, stylehint_just_LeftRight);
            glk_stylehint_set(wintype_AllTypes, style_Emphasized, stylehint_TextColor, SCEMPH);
            glk_stylehint_set(wintype_AllTypes, style_Emphasized, stylehint_BackColor, SCBACK);
            glk_stylehint_set(wintype_AllTypes, style_Header, stylehint_TextColor, SCEMPH);
            glk_stylehint_set(wintype_AllTypes, style_Header, stylehint_BackColor, SCBACK);
            glk_stylehint_set(wintype_AllTypes, style_Subheader, stylehint_TextColor, SCHEAD);
            glk_stylehint_set(wintype_AllTypes, style_Subheader, stylehint_BackColor, SCBACK);
            glk_stylehint_set(wintype_AllTypes, style_Alert, stylehint_TextColor, SCBACK);
            glk_stylehint_set(wintype_AllTypes, style_Alert, stylehint_BackColor, SCTEXT);
            glk_stylehint_set(wintype_AllTypes, style_Note, stylehint_TextColor, SCINPU);
            glk_stylehint_set(wintype_AllTypes, style_Note, stylehint_BackColor, SCBACK);
            glk_stylehint_set(wintype_AllTypes, style_Blockquote, stylehint_TextColor, SCINPU);
            glk_stylehint_set(wintype_AllTypes, style_Blockquote, stylehint_BackColor, SCBACK);
            glk_stylehint_set(wintype_AllTypes, style_Input, stylehint_TextColor, SCINPU);
            glk_stylehint_set(wintype_AllTypes, style_Input, stylehint_BackColor, SCBACK);
            glk_stylehint_set(wintype_AllTypes, style_Preformatted, stylehint_TextColor, SCINPU);
            glk_stylehint_set(wintype_AllTypes, style_Preformatted, stylehint_BackColor, SCBACK);
            glk_stylehint_set(wintype_AllTypes, style_User1, stylehint_TextColor, SCSOFT);
            glk_stylehint_set(wintype_AllTypes, style_User1, stylehint_BackColor, SCBACK);    
];

! Glk object identification entry point.
#IfnDef CUSTOM_IDENTIFYGLKOBJECT;
[ IdentifyGlkObject phase type ref rock; SGWIdentifyGlkObject(phase,type,ref,rock); ];
#EndIf;

[ SGWIdentifyGlkObject phase type ref rock id;
    id = id;
    switch (phase) {
    0:  
		! start
        gg_bigwin            = 0;
        gg_statuswin         = 0;
        music                = 0;
        chan1                = 0;
        chan2                = 0;
        return;
    1:    
		! pass ref
        switch (type) {
        0:    ! window ref
            switch (rock) {
                GG_BIGWIN_ROCK    :    gg_bigwin    = ref;
            }
        }
        return;
    2:  
		! Update objects
		#IfnDef NOSOUND;
    	id = glk_schannel_iterate(0, gg_arguments);
         while (id) {
            switch (gg_arguments-->0) {
               GG_MUSICCHAN_ROCK          : music    = id;
               GG_MUSICCHANSOUND1_ROCK    : chan1    = id;
               GG_MUSICCHANSOUND2_ROCK    : chan2    = id;
           }
           id = glk_schannel_iterate(id, gg_arguments);
         }
         ResetMusicChannel();
         fading = 0;
         if (next_music) {
             current_loops = next_loops;
             playSound(music, next_music, 1, next_volume);
         } else {
             if (current_music) playSound(music, current_music, 1, 0);
         }
		#EndIf;
        MyRedrawGraphicsWindows();
        return;
    }
    return;
];

! Test the Glulx Interpreter's performances
[ testGlulx verbose;
    #Ifndef NOGRAPHICS;
        ggraphic = glk_gestalt(gestalt_Graphics, 0);
        if ((~~ggraphic) && verbose) 
            print "^[This Interpreter doesn't support graphics.]^";
    #IfNot;
        ggraphic = false;
    #EndIf;

#IfDef NOSOUND;
    gsound = false;
	gvolume = false;
	gnotify = false;
#IfNot;
    gsound = glk_gestalt(gestalt_Sound, 0);
    gvolume = glk_gestalt(gestalt_SoundVolume, 0);
    gnotify = glk_gestalt(gestalt_SoundNotify, 0);
    gtimer = glk_gestalt(gestalt_Timer, 0);
#EndIf;

    if (~~verbose) rfalse;
    
#IfnDef NOSOUND;
    if (~~glk_gestalt(gestalt_Sound, 0)) 
        print "^[This Interpreter doesn't support sound.]^";

    if (~~glk_gestalt(gestalt_SoundVolume, 0)) 
        print "^[This Interpreter doesn't support sound volume.]^";

    if (~~glk_gestalt(gestalt_SoundMusic, 0)) 
        print "^[This Interpreter doesn't support mod music.]^";

    if (~~glk_gestalt(gestalt_SoundNotify, 0)) 
        print "^[This Interpreter doesn't support sound notify.]^";
#EndIf;
    if (~~glk_gestalt(gestalt_Timer, 0)) 
        if (verbose) print "^[This Interpreter doesn't support timer.]^";

    if (~~glk_gestalt(gestalt_Hyperlinks, 0)) 
        if (verbose) print "^[This Interpreter doesn't support hyperlinks.]^";

    if (~~glk_gestalt(gestalt_GraphicsTransparency, 0))
        if (verbose) print "^[This Interpreter doesn't support transparency.]^";

    if (~~glk_gestalt(gestalt_Version, 0)) 
        if (verbose) print "^[This Interpreter doesn't support this version.]^";
];


! Glulx Inizialize function
[ inizializeGlulx h;
    curr_height = h;
        if (gg_statuswin == 0) {
            gg_statuswin = glk_window_open(gg_mainwin,(winmethod_Above+winmethod_Fixed), 2, wintype_TextGrid, GG_STATUSWIN_ROCK);
        }
        
    #Ifndef NOGRAPHICS;
        ! Graphics
        if (gg_bigwin == 0) {
            gg_bigwin = glk_window_open(gg_mainwin,(winmethod_Above+winmethod_Fixed), curr_height , wintype_Graphics, GG_BIGWIN_ROCK);
        }

        ! Set black as background colour for all windows
        glk_window_set_background_color(gg_bigwin,SCBACK);
        glk_window_clear(gg_bigwin);
        glk_window_set_background_color(gg_mainwin,SCBACK);
        glk_window_clear(gg_mainwin);
    #endif;
];

#Endif;

! --- Warning squasher, not needed sfor system file

![ __SGW_warningsquasher x;
!    x=SGWHEIGHT;
!    x = music+chan1+chan2;
!    x = VOLUME_HIGH+VOLUME_NORMAL+VOLUME_LOW;
!    x = CLR_GG_AZURE+CLR_GG_BLACK+CLR_GG_BLUE+CLR_GG_BROWN;
!    x = CLR_GG_CYAN+CLR_GG_GREEN+CLR_GG_GREY+CLR_GG_MAGENTA;
!    x = CLR_GG_ORANGE+CLR_GG_PINK+CLR_GG_PURPLE+CLR_GG_RED;
!    x = CLR_GG_YELLOW+CLR_GG_WHITE;
    
!    SGWreset();
!    s_emph(); s_underline(); s_fixed(); s_head(); s_bold(); s_reverse(); s_block(); s_input();
!    viewImageSGW(); viewImageLeft(); viewImageRight();
!    clearMainWindow(); closeAllWindows(); MyRedrawGraphicsWindows();
!    playSound(); silenceAll(); silenceChannel(); resetMusicChannel(); setVolume();
!    __SGW_warningsquasher();
!];

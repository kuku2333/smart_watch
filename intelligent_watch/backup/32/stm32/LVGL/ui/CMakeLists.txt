SET(SOURCES screens/ui_Start.c
    screens/ui_LockScreen.c
    screens/ui_ShowTime.c
    screens/ui_Screen4.c
    screens/ui_Screen5.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    ui_events.c
    images/ui_img_1670719189.c
    images/ui_img_1886717116.c)

add_library(ui ${SOURCES})

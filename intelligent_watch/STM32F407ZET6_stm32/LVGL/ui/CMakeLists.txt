SET(SOURCES screens/ui_MainScreen.c
    screens/ui_ScreenTime.c
    screens/ui_ScreenBloodHeart.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    ui_events.c)

add_library(ui ${SOURCES})

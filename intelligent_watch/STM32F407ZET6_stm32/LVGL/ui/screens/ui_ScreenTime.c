// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.11
// Project name: SquareLine_Project3

#include "../ui.h"

void ui_ScreenTime_screen_init(void)
{
    ui_ScreenTime = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenTime, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_ArcTimeSeconds = lv_arc_create(ui_ScreenTime);
    lv_obj_set_width(ui_ArcTimeSeconds, 150);
    lv_obj_set_height(ui_ArcTimeSeconds, 150);
    lv_obj_set_x(ui_ArcTimeSeconds, 4);
    lv_obj_set_y(ui_ArcTimeSeconds, -22);
    lv_obj_set_align(ui_ArcTimeSeconds, LV_ALIGN_CENTER);
    lv_arc_set_range(ui_ArcTimeSeconds, 0, 59);
    lv_arc_set_value(ui_ArcTimeSeconds, 0);
    lv_arc_set_bg_angles(ui_ArcTimeSeconds, 0, 360);
    lv_arc_set_rotation(ui_ArcTimeSeconds, 270);


    ui_LabelTimes = lv_label_create(ui_ScreenTime);
    lv_obj_set_width(ui_LabelTimes, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelTimes, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LabelTimes, 4);
    lv_obj_set_y(ui_LabelTimes, -22);
    lv_obj_set_align(ui_LabelTimes, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelTimes, "10:20:00");

    lv_obj_add_event_cb(ui_ScreenTime, ui_event_ScreenTime, LV_EVENT_ALL, NULL);

}

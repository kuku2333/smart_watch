// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.11
// Project name: SquareLine_Project3

#include "../ui.h"

void ui_Screen2_screen_init(void)
{
    ui_Screen2 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Arc1 = lv_arc_create(ui_Screen2);
    lv_obj_set_width(ui_Arc1, 150);
    lv_obj_set_height(ui_Arc1, 150);
    lv_obj_set_x(ui_Arc1, 4);
    lv_obj_set_y(ui_Arc1, -22);
    lv_obj_set_align(ui_Arc1, LV_ALIGN_CENTER);
    lv_arc_set_range(ui_Arc1, 0, 59);
    lv_arc_set_value(ui_Arc1, 0);
    lv_arc_set_bg_angles(ui_Arc1, 0, 360);
    lv_arc_set_rotation(ui_Arc1, 270);


    ui_Label1 = lv_label_create(ui_Screen2);
    lv_obj_set_width(ui_Label1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label1, 4);
    lv_obj_set_y(ui_Label1, -22);
    lv_obj_set_align(ui_Label1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label1, "10:20");

}

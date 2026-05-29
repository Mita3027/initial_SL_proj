#include <Arduino.h>
#include <lvgl.h>
#include "PanelLan.h"
#include "ui.h"


extern bool fwdbtnpress;
extern bool loginButtonPressed;
extern bool switchpressed;
extern bool bckbtnpressed;
extern bool sliderValueChanged;
int generateRandomNumber();
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data);
void Display_Init();
void Display_Timer();
void Display_loop();
int my_map(int x, int in_min, int in_max, int ut_min, int out_max);

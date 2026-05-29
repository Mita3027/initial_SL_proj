#include <Arduino.h>
#include <lvgl.h>
#include "PanelLan.h"
#include "ui.h"
// #include <string.h>
#include "display.h"
// #include <stdio.h>

bool fwdbtnpress = false;
bool bckbtnpressed = false;
bool loginButtonPressed = false;
bool switchpressed = false;
bool sliderValueChanged = false;

// BOARD_SC01_PLUS, BOARD_SC02, BOARD_SC05, BOARD_KC01, BOARD_BC02, BOARD_SC07
static PanelLan tft(BOARD_SC05);

/*Change to your screen resolution*/
static const uint16_t screenWidth = 800;
static const uint16_t screenHeight = 480;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[2][screenWidth * 10];

int i = 0;

// void login_event(lv_event_t *e)
// {
//   // LOGIN BTN
//   const char *pswd = "3728";
//   const char *entered_pswd = lv_textarea_get_text(ui_pswdtext);
// if (loginButtonPressed == true)
// {
//   if (strcmp(entered_pswd, pswd) == 0)
//   {
//     lv_label_set_text(ui_pswdlabel, "VALID PSWD");
//   }
//   else
//   {
//     lv_label_set_text(ui_pswdlabel, "INVALID PSWD");
//   }
//  }
// }

// int generateRandomNumber()
// {
//   int i = 0;
//   i = (i < 100) ? i++ : i = 0;

//   return i;
// }

void Display_loop()
{

  // SWITCH
  if (true == switchpressed)
  {
    (i < 100) ? i++ : i = 0;
    char text[10];
    sprintf(text, "%d", i);
    lv_label_set_text(ui_rndmtxt, text);
    switchpressed = false;
  }

  // LOGIN BTN
  if (true == loginButtonPressed)
  {
    const char *pswd = "3728";
    const char *entered_pswd = lv_textarea_get_text(ui_pswdtext);
    if (strcmp(entered_pswd, pswd) == 0)
    {
      lv_label_set_text(ui_pswdlabel, "VALID PSWD");
    }
    else
    {
      lv_label_set_text(ui_pswdlabel, "INVALID PSWD");
    }
    loginButtonPressed = false;
  }

  // SLIDER
  //if (true == sliderValueChanged)
  {
    int temp = lv_slider_get_value(ui_slider);
    int value = map(temp, 0, 100, 100, 200);
    tft.setBrightness(value);
    sliderValueChanged = false;
  }
  
}
  

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  if (tft.getStartCount() == 0)
  { // Processing if not yet started
    tft.startWrite();
  }
  tft.pushImageDMA(area->x1, area->y1, area->x2 - area->x1 + 1, area->y2 - area->y1 + 1, (lgfx::swap565_t *)&color_p->full);
  lv_disp_flush_ready(disp);
}

/*Read the touchpad*/
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
  uint16_t touchX, touchY;

  data->state = LV_INDEV_STATE_REL;

  if (tft.getTouch(&touchX, &touchY))
  {
    data->state = LV_INDEV_STATE_PR;

    /*Set the coordinates*/
    data->point.x = touchX;
    data->point.y = touchY;
  }
}

// void login_event(lv_event_t *e);
void Display_Init()
{
  tft.begin();
  tft.setBrightness(255);
  lv_init();
  lv_disp_draw_buf_init(&draw_buf, buf[0], buf[1], screenWidth * 10);

  /*Initialize the display*/
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  /*Change the following line to your display resolution*/
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  /*Initialize the input device driver*/
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register(&indev_drv);

  ui_init();
}

void Display_Timer()
{
  lv_timer_handler(); /* let the GUI do its work */
  delay(5);
}

// int x = 19;
// int in_min = 0;
// int in_max = 100;
// int out_min = 100;
// int out_max = 200;

// int my_map(int x, int in_min, int in_max, int ut_min, int out_max)
// {
//   return ((x - in_min) * (out_max - out_min) / (in_max - in_min)) + out_min;
// }
// int main()
// {
//   int result = my_map(x, in_min, in_max, out_min, out_max);
//   printf("Mapped value: %d\n", result);

//   return 0;
// }
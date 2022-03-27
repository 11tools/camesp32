/*
 * This file is part of the OpenMV project.
 * Copyright (c) 2013/2014 Ibrahim Abdelkader <i.abdalkader@gmail.com>
 * This work is licensed under the MIT license, see the file LICENSE for details.
 *
 * tvp5150 driver.
 *
 */
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "sccb.h"
#include "tvp5150.h"
#include "tvp5150_regs.h"
#include "tvp5150_settings.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#if defined(ARDUINO_ARCH_ESP32) && defined(CONFIG_ARDUHAL_ESP_LOG)
#include "esp32-hal-log.h"
#else
#include "esp_log.h"
static const char* TAG = "tvp5150";
#endif

static volatile tvp5150_bank_t reg_bank = BANK_MAX;
static int set_bank(sensor_t *sensor, tvp5150_bank_t bank)
{
    int res = 0;

    return res;
}

static int write_regs(sensor_t *sensor, const uint8_t (*regs)[2])
{
    int i=0, res = 0;

    return res;
}

static int write_reg(sensor_t *sensor, tvp5150_bank_t bank, uint8_t reg, uint8_t value)
{
    int ret = 0;
    return ret;
}

static int set_reg_bits(sensor_t *sensor, uint8_t bank, uint8_t reg, uint8_t offset, uint8_t mask, uint8_t value)
{
    int ret = 0;
    return ret;
}

static int read_reg(sensor_t *sensor, tvp5150_bank_t bank, uint8_t reg)
{

    return 0;
}

static uint8_t get_reg_bits(sensor_t *sensor, uint8_t bank, uint8_t reg, uint8_t offset, uint8_t mask)
{
    return (read_reg(sensor, bank, reg) >> offset) & mask;
}

static int write_reg_bits(sensor_t *sensor, uint8_t bank, uint8_t reg, uint8_t mask, int enable)
{
    return set_reg_bits(sensor, bank, reg, 0, mask, enable?mask:0);
}

#define WRITE_REGS_OR_RETURN(regs) ret = write_regs(sensor, regs); if(ret){return ret;}
#define WRITE_REG_OR_RETURN(bank, reg, val) ret = write_reg(sensor, bank, reg, val); if(ret){return ret;}
#define SET_REG_BITS_OR_RETURN(bank, reg, offset, mask, val) ret = set_reg_bits(sensor, bank, reg, offset, mask, val); if(ret){return ret;}

static int reset(sensor_t *sensor)
{
    int ret = 0;
    return ret;
}

static int set_pixformat(sensor_t *sensor, pixformat_t pixformat)
{
    int ret = 0;

    return ret;
}

static int set_window(sensor_t *sensor, tvp5150_sensor_mode_t mode, int offset_x, int offset_y, int max_x, int max_y, int w, int h){
    int ret = 0;
    return ret;
}

static int set_framesize(sensor_t *sensor, framesize_t framesize)
{
    int ret = 0;

    return ret;
}

static int set_contrast(sensor_t *sensor, int level)
{
    int ret=0;

    return ret;
}

static int set_brightness(sensor_t *sensor, int level)
{
    int ret=0;

    return ret;
}

static int set_saturation(sensor_t *sensor, int level)
{
    int ret=0;

    return ret;
}

static int set_special_effect(sensor_t *sensor, int effect)
{
    int ret=0;

    return ret;
}

static int set_wb_mode(sensor_t *sensor, int mode)
{
    int ret=0;

    return ret;
}

static int set_ae_level(sensor_t *sensor, int level)
{
    int ret=0;

    return ret;
}

static int set_quality(sensor_t *sensor, int quality)
{

    return 0;
}

static int set_agc_gain(sensor_t *sensor, int gain)
{

    return 0;
}

static int set_gainceiling_sensor(sensor_t *sensor, gainceiling_t gainceiling)
{
    return 0;
}

static int set_aec_value(sensor_t *sensor, int value)
{
    return 0;
}

static int set_aec2(sensor_t *sensor, int enable)
{
    return 0;
}

static int set_colorbar(sensor_t *sensor, int enable)
{
    return 0;
}

static int set_agc_sensor(sensor_t *sensor, int enable)
{
    return 0;
}

static int set_aec_sensor(sensor_t *sensor, int enable)
{
    sensor->status.aec = enable;
    return 0;
}

static int set_hmirror_sensor(sensor_t *sensor, int enable)
{
    sensor->status.hmirror = enable;
    return 0;
}

static int set_vflip_sensor(sensor_t *sensor, int enable)
{
    int ret = 0;
    return 0;
}

static int set_raw_gma_dsp(sensor_t *sensor, int enable)
{
    return 0;
}

static int set_awb_dsp(sensor_t *sensor, int enable)
{
    sensor->status.awb = enable;
    return 0;
}

static int set_awb_gain_dsp(sensor_t *sensor, int enable)
{
    sensor->status.awb_gain = enable;
    return 0;
}

static int set_lenc_dsp(sensor_t *sensor, int enable)
{
    sensor->status.lenc = enable;
    return 0;
}

static int set_dcw_dsp(sensor_t *sensor, int enable)
{
    sensor->status.dcw = enable;
    return 0;
}

static int set_bpc_dsp(sensor_t *sensor, int enable)
{
    sensor->status.bpc = enable;
    return 0;
}

static int set_wpc_dsp(sensor_t *sensor, int enable)
{
    sensor->status.wpc = enable;
    return 0;
}

//unsupported
static int set_sharpness(sensor_t *sensor, int level)
{
   return -1;
}

static int set_denoise(sensor_t *sensor, int level)
{
   return -1;
}

static int get_reg(sensor_t *sensor, int reg, int mask)
{
    int ret = read_reg(sensor, (reg >> 8) & 0x01, reg & 0xFF);
    if(ret > 0){
        ret &= mask;
    }
    return ret;
}

static int set_reg(sensor_t *sensor, int reg, int mask, int value)
{
    int ret = 0;
    ret = read_reg(sensor, (reg >> 8) & 0x01, reg & 0xFF);
    if(ret < 0){
        return ret;
    }
    value = (ret & ~mask) | (value & mask);
    ret = write_reg(sensor, (reg >> 8) & 0x01, reg & 0xFF, value);
    return ret;
}

static int set_res_raw(sensor_t *sensor, int startX, int startY, int endX, int endY, int offsetX, int offsetY, int totalX, int totalY, int outputX, int outputY, bool scale, bool binning)
{
    return set_window(sensor, (tvp5150_sensor_mode_t)startX, offsetX, offsetY, totalX, totalY, outputX, outputY);
}

static int _set_pll(sensor_t *sensor, int bypass, int multiplier, int sys_div, int root_2x, int pre_div, int seld5, int pclk_manual, int pclk_div)
{
    return -1;
}

esp_err_t xclk_timer_conf(int ledc_timer, int xclk_freq_hz);
static int set_xclk(sensor_t *sensor, int timer, int xclk)
{
    int ret = 0;
    return ret;
}

static int init_status(sensor_t *sensor){

    return 0;
}

unsigned char cmd5150[][3] = 
{

  {0x00, 0x00},

  {0x03, 0x0d},
 
  {0x0D, 0x40}, 
  
};


void init_tvp5150()
{
  int a;
  for( a = 0 ; a < sizeof(cmd5150)/2;a++)
  {
    SCCB_Write(0x5c, cmd5150[a][0], cmd5150[a][1]);
  }
}

void set_crop(int x1, int y1, int x2, int y2 ){
   SCCB_Write(0x5c, 0x11, x1);
   SCCB_Write(0x5c, 0x12, 0);

   SCCB_Write(0x5c, 0x13, x2);
   SCCB_Write(0x5c, 0x14, 0);
   
}


int tvp5150_init(sensor_t *sensor)
{
    sensor->reset = reset;
    sensor->init_status = init_status;
    sensor->set_pixformat = set_pixformat;
    sensor->set_framesize = set_framesize;
    sensor->set_contrast  = set_contrast;
    sensor->set_brightness= set_brightness;
    sensor->set_saturation= set_saturation;

    sensor->set_quality = set_quality;
    sensor->set_colorbar = set_colorbar;

    sensor->set_gainceiling = set_gainceiling_sensor;
    sensor->set_gain_ctrl = set_agc_sensor;
    sensor->set_exposure_ctrl = set_aec_sensor;
    sensor->set_hmirror = set_hmirror_sensor;
    sensor->set_vflip = set_vflip_sensor;

    sensor->set_whitebal = set_awb_dsp;
    sensor->set_aec2 = set_aec2;
    sensor->set_aec_value = set_aec_value;
    sensor->set_special_effect = set_special_effect;
    sensor->set_wb_mode = set_wb_mode;
    sensor->set_ae_level = set_ae_level;

    sensor->set_dcw = set_dcw_dsp;
    sensor->set_bpc = set_bpc_dsp;
    sensor->set_wpc = set_wpc_dsp;
    sensor->set_awb_gain = set_awb_gain_dsp;
    sensor->set_agc_gain = set_agc_gain;

    sensor->set_raw_gma = set_raw_gma_dsp;
    sensor->set_lenc = set_lenc_dsp;

    //not supported
    sensor->set_sharpness = set_sharpness;
    sensor->set_denoise = set_denoise;

    sensor->get_reg = get_reg;
    sensor->set_reg = set_reg;
    sensor->set_res_raw = set_res_raw;
    sensor->set_pll = _set_pll;
    sensor->set_xclk = set_xclk;
    init_tvp5150();
    ESP_LOGD(TAG, "tvp5150 Attached");
    return 0;
}

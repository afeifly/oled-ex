
#ifndef INCLUDE_EPSON_EPDC_H
#define INCLUDE_EPSON_EPDC_H 1


#include <Arduino.h>
#include <SPI.h>
#include "inidata.h" 
#include "PIC.H"

#define S1D13541_PROD_CODE                0x0053
//#define S1D13541_STATUS_HRDY          (1 << 13)
#define S1D13541_INTERNAL_CLOCK_ENABLE  (1 << 7)
#define S1D13541_I2C_CLOCK_DIV          7 /* 100 kHz */
#define S1D13541_PROT_KEY_1             0x5678 /* ToDo: add to s1d135xx_data */
#define S1D13541_PROT_KEY_2             0x1234
#define S1D13541_TEMP_SENSOR_CONTROL    (1 << 14)
#define S1D13541_TEMP_SENSOR_EXTERNAL   (1 << 6)
#define S1D13541_AUTO_TEMP_JUDGE_EN     (1 << 2)
#define S1D13541_GENERIC_TEMP_EN        (1 << 15)
#define S1D13541_GENERIC_TEMP_JUDGE_EN  (1 << 14)
#define S1D13541_GENERIC_TEMP_MASK      0x01FF
#define S1D13541_INT_RAW_WF_UPDATE      (1 << 14)
#define S1D13541_INT_RAW_OUT_OF_RANGE   (1 << 10)
#define S1D13541_LD_IMG_1BPP            (0 << 4)
#define S1D13541_LD_IMG_2BPP            (1 << 4)
#define S1D13541_LD_IMG_4BPP            (2 << 4)
#define S1D13541_LD_IMG_8BPP            (3 << 4)
#define S1D13541_WF_ADDR                0x00080000L

#define S1D13541_PROM_STATUS             0x0500
#define S1D13541_PROM_CTRL               0x0502
#define S1D13541_PROM_ADR_PGR_DATA       0x0504
#define S1D13541_PROM_READ_DATA          0x0506

#define S1D13541_PROM_STATUS_IDLE               0x0
#define S1D13541_PROM_STATUS_READ_BUSY          (1 << 8)
#define S1D13541_PROM_STATUS_PGM_BUSY           (1 << 9)
#define S1D13541_PROM_STATUS_ERASE_BUSY (1 << 10)
#define S1D13541_PROM_STATUS_READ_MODE          (1 << 12)
#define S1D13541_PROM_STATUS_PGM_MODE           (1 << 13)
#define S1D13541_PROM_STATUS_ERASE_ALL_MODE     (1 << 14)

#define S1D13541_PROM_READ_START                (1 << 0)
#define S1D13541_PROM_READ_STOP                 (1 << 1)
#define S1D13541_PROM_VCOM_READ                 (1 << 2)
#define S1D13541_PROM_PGM_MODE_START            (1 << 4)
#define S1D13541_PROM_PGM_OP_START                     (1 << 5)
#define S1D13541_PROM_PGM_OP_STOP               (1 << 6)
#define S1D13541_PROM_PGM_MODE_STOP             (1 << 7)
#define S1D13541_PROM_ERASE_ALL_MODE_START      (1 << 8)
#define S1D13541_PROM_ERASE_ALL_OP_START        (1 << 9)
#define S1D13541_PROM_ERASE_ALL_OP_STOP (1 << 10)
#define S1D13541_PROM_ERASE_ALL_MODE_STOP       (1 << 11)



/* Set to 1 to enable verbose update and EPD power on/off log messages */
#define VERBOSE 0

#define DATA_BUFFER_LENGTH              2048 // must be above maximum xres value for any supported display

#define S1D135XX_WF_MODE(_wf)           (((_wf) << 8) & 0x0F00)
#define S1D135XX_XMASK                  0x0FFF
#define S1D135XX_YMASK                  0x0FFF
#define S1D135XX_INIT_CODE_CHECKSUM_OK  (1 << 15)
#define S1D135XX_PWR_CTRL_UP            0x8001
#define S1D135XX_PWR_CTRL_DOWN          0x8002
#define S1D135XX_PWR_CTRL_BUSY          0x0080
#define S1D135XX_PWR_CTRL_CHECK_ON      0x2200

#define SPICS_Pin   15
#define EN3P3_Pin   18
#define NRST_Pin    4
#define WKUP_Pin    19
#define SHDN_Pin    32
#define HVEN_Pin    5
#define HDC_Pin     2
#define HIRQ_Pin    32    //NOT USE

/* Set to 1 to enable verbose temperature log messages */
#define VERBOSE_TEMPERATURE                  0
#define S1D135XX_TEMP_MASK                   0x00FF


/* Set to 1 to enable stub EPDC implementation */
#define PL_EPDC_STUB 0

/* Use this macro to convert a 16-greyscale value to 8 bits */
#define PL_GL16(_g) ({      \
  uint8_t g16 = (_g) & 0xF; \
  g16 | g16 << 4;     \
})

#define PL_WHITE PL_GL16(15)
#define PL_BLACK PL_GL16(0)

enum pl_epdc_power_state {
  PL_EPDC_RUN = 0,
  PL_EPDC_STANDBY,
  PL_EPDC_SLEEP,
  PL_EPDC_OFF,
};

enum pl_epdc_temp_mode {
  PL_EPDC_TEMP_MANUAL,
  PL_EPDC_TEMP_EXTERNAL,
  PL_EPDC_TEMP_INTERNAL,
};

enum pl_update_mode {
  UPDATE_FULL        = 0, //0x33,
  UPDATE_FULL_AREA   = 1, //0x34,
  UPDATE_PARTIAL      = 2, //0x35,
  UPDATE_PARTIAL_AREA = 3, //0x36,
};


enum s1d135xx_cmd {
  S1D135XX_CMD_INIT_SET            = 0x00, /* to load init code */
  S1D135XX_CMD_RUN                 = 0x02,
  S1D135XX_CMD_STBY                = 0x04,
  S1D135XX_CMD_SLEEP               = 0x05,
  S1D135XX_CMD_INIT_STBY           = 0x06, /* init then standby */
  S1D135XX_CMD_INIT_ROT_MODE       = 0x0B,
  S1D135XX_CMD_READ_REG            = 0x10,
  S1D135XX_CMD_WRITE_REG           = 0x11,
  S1D135XX_CMD_BST_RD_SDR          = 0x1C,
  S1D135XX_CMD_BST_WR_SDR          = 0x1D,
  S1D135XX_CMD_BST_END_SDR         = 0x1E,
  S1D135XX_CMD_LD_IMG              = 0x20,
  S1D135XX_CMD_LD_IMG_AREA         = 0x22,
  S1D135XX_CMD_LD_IMG_END          = 0x23,
  S1D135XX_CMD_WAIT_DSPE_TRG       = 0x28,
  S1D135XX_CMD_WAIT_DSPE_FREND     = 0x29,
  S1D135XX_CMD_UPD_INIT            = 0x32,
  S1D135XX_CMD_UPDATE_FULL         = 0x33,
  S1D135XX_CMD_UPDATE_FULL_AREA    = 0x34,
  S1D135XX_CMD_UPDATE_PARTIAL      = 0x35,
  S1D135XX_CMD_UPDATE_PARTIAL_AREA = 0x36,
  S1D135XX_CMD_EPD_GDRV_CLR        = 0x37,
};

enum s1d13541_reg {
  S1D13541_REG_CLOCK_CONFIG          = 0x0010,
  S1D13541_REG_PROT_KEY_1            = 0x042C,
  S1D13541_REG_PROT_KEY_2            = 0x042E,
  S1D13541_REG_FRAME_DATA_LENGTH     = 0x0400,
  S1D13541_REG_LINE_DATA_LENGTH      = 0x0406,
  S1D13541_REG_WF_DECODER_BYPASS     = 0x0420,
  S1D13541_REG_TEMP_SENSOR_VALUE     = 0x0576,
  S1D13541_REG_GENERIC_TEMP_CONFIG   = 0x057E,
};

enum s1d13541_cmd {
  S1D13541_CMD_RD_TEMP               = 0x12,
};

enum s1d135xx_reg {
  S1D135XX_REG_REV_CODE              = 0x0002,
  S1D135XX_REG_SOFTWARE_RESET        = 0x0008,
  S1D135XX_REG_SYSTEM_STATUS         = 0x000A,
  S1D135XX_REG_I2C_CLOCK             = 0x001A,
  S1D135XX_REG_PERIPH_CONFIG         = 0x0020,
  S1D135XX_REG_HOST_MEM_PORT         = 0x0154,
  S1D135XX_REG_I2C_TEMP_SENSOR_VALUE = 0x0216,
  S1D135XX_REG_I2C_STATUS            = 0x0218,
  S1D135XX_REG_PWR_CTRL              = 0x0230,
  S1D135XX_REG_SEQ_AUTOBOOT_CMD      = 0x02A8,
  S1D135XX_REG_DISPLAY_BUSY          = 0x0338,
  S1D135XX_REG_INT_RAW_STAT          = 0x033A,
};

enum s1d135xx_rot_mode {
  S1D135XX_ROT_MODE_0   = 0,
  S1D135XX_ROT_MODE_90  = 1,
  S1D135XX_ROT_MODE_180 = 2,
  S1D135XX_ROT_MODE_270 = 3,
};

enum epson_epdc_ref {
  EPSON_EPDC_S1D13524,
  EPSON_EPDC_S1D13541,
};

struct s1d135xx_data {
  unsigned reset;
  unsigned cs0;
  unsigned hirq;
  unsigned hrdy;
  unsigned hdc;
  unsigned clk_en;
  unsigned vcc_en;
};

struct pl_area {
 unsigned left;
 unsigned top;
 unsigned width;
 unsigned height;
};

  struct s1d135xx {
  const struct s1d135xx_data *data;
  struct pl_gpio *gpio;
  struct pl_interface *interface;
  uint16_t scrambling;
  uint16_t source_offset;
  uint16_t hrdy_mask;
  uint16_t hrdy_result;
  int measured_temp;
  unsigned xres;
  unsigned yres;
  struct {
    uint8_t needs_update:1;
  } flags;
};
  

struct pl_wfid {
  int id_from;
  int id_to;
//  const char *path;
//  int id;
};




struct pl_gpio;
struct pl_wflib;




struct pl_area;
struct pl_dispinfo;
struct pl_epdpsu;


int Epd_Port_init( uint8_t port);
int Epd_Power_up( void);
int Epd_Power_down( void);

static int epson_epdc_clear_init();
static int epson_epdc_wait_update_end();

static int epson_epdc_set_power(enum pl_epdc_power_state state);

static int epson_epdc_set_epd_power(int on);
int epson_epdc_init();
int epson_epdc_early_init();

void s1d135xx_hard_reset();
int s1d135xx_check_prod_code(uint16_t ref_code);
int s1d135xx_load_init_code();
int s1d135xx_load_wflib(uint32_t size, uint32_t addr);
int s1d135xx_init_gate_drv();
int s1d135xx_wait_dspe_trig();

int s1d135xx_clear_init();

int s1d135xx_fill(uint16_t mode, unsigned bpp, const struct pl_area *a, uint8_t grey);
int s1d135xx_pattern_check(uint16_t height, uint16_t width, uint16_t checker_size, uint16_t mode);
int s1d135xx_pattern_check_test_part(uint16_t height, uint16_t width, uint16_t checker_size, uint16_t mode,const struct pl_area *area);

int s1d135xx_update(int wfid, enum pl_update_mode mode,  const struct pl_area *area);

int s1d135xx_wait_update_end();
int s1d135xx_wait_idle();

int s1d135xx_set_power_state(enum pl_epdc_power_state state);

int s1d135xx_set_epd_power(int on);

void s1d135xx_cmd(uint16_t cmd, uint16_t *params, size_t n);

uint16_t s1d135xx_read_reg(uint16_t reg);
void s1d135xx_write_reg(uint16_t reg, uint16_t val);
static int get_hrdy();

static int do_fill(const struct pl_area *area, unsigned bpp, uint8_t g);

static int wflib_wr(const uint8_t *data, size_t n);

static void transfer_data(const uint8_t *data, size_t n);

static void send_cmd_area(uint16_t cmd, uint16_t mode,
        const struct pl_area *area);
static void send_cmd_cs(uint16_t cmd);

static void send_cmd(uint16_t cmd);

static void send_params(uint16_t *params, size_t n);
static void send_param(uint16_t param);
static void set_cs(int state);

static void set_hdc(int state);
int set_init_rot_mode();
int s1d13541_load_wflib();

int s1d13541_set_temp_mode(enum pl_epdc_temp_mode mode);

int s1d13541_update_temp(enum pl_epdc_temp_mode temp_mode);

int s1d13541_fill(const struct pl_area *area, uint8_t grey);
int s1d13541_pattern_check(uint16_t size);

int s1d13541_pattern_check_test_part(uint16_t size,const struct pl_area *area);

int epson_epdc_early_init_s1d13541();

int epson_epdc_init_s1d13541();

static int s1d13541_init_clocks();
static void update_temp(uint16_t reg);

static int update_temp_auto(uint16_t temp_reg);
int s1d13541_read_prom(uint8_t * blob);
static int wait_for_ack (uint16_t status, uint16_t mask);

int pl_epdc_single_update(int wfid, enum pl_update_mode mode, const struct pl_area *area);
 
SPIClass *hspi = NULL;
static const int spiClk = 15000000; // 15 MHz
//port  0 HSPI 1 VSPI
int Epd_Port_init( uint8_t port)
{ int i;
  if (port == 0)
  {
    hspi = new SPIClass(HSPI);
    //initialise hspi with default pins
    //SCLK = 14, MISO = 12, MOSI = 13, SS = 15
     hspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
    hspi->begin();
    hspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
    Serial.println("HSPI Init OK");   
    //alternatively route through GPIO pins
    //hspi->begin(25, 26, 27, 32); //SCLK, MISO, MOSI, SS
    pinMode(SPICS_Pin, OUTPUT); //HSPI SS
    pinMode(EN3P3_Pin, OUTPUT); //HSPI SS
    pinMode(NRST_Pin, OUTPUT); //HSPI SS
    pinMode(WKUP_Pin, OUTPUT); //HSPI SS
    pinMode(SHDN_Pin, OUTPUT); //HSPI SS
    pinMode(HVEN_Pin, OUTPUT); //HSPI SS
    pinMode(HDC_Pin, OUTPUT); //HSPI SS
 
  
  digitalWrite(EN3P3_Pin, LOW);
  digitalWrite(NRST_Pin, LOW);
  digitalWrite(WKUP_Pin, LOW);
  digitalWrite(SHDN_Pin, LOW);
  digitalWrite(HVEN_Pin, LOW);   
  digitalWrite(SPICS_Pin, 1);    

  ledcSetup(0, 80000000, 1);
  ledcAttachPin(17, 0);  //GPIO 17 配置为20MHz输出
  ledcWrite(0, 1);


  for(i=0;i<100;i++)
  {  digitalWrite(SPICS_Pin, 1); 
      digitalWrite(SPICS_Pin, 0); 
      }
    return 0;
  }
  else
    return -1;
}
int Epd_Power_up( void)
{
  digitalWrite(EN3P3_Pin, HIGH);
  digitalWrite(NRST_Pin, LOW);
  digitalWrite(WKUP_Pin, HIGH);
  digitalWrite(SHDN_Pin, HIGH);
  digitalWrite(HVEN_Pin, HIGH);
}
int Epd_Power_down( void)
{
  digitalWrite(EN3P3_Pin, LOW);
  digitalWrite(NRST_Pin, LOW);
  digitalWrite(WKUP_Pin, LOW);
  digitalWrite(SHDN_Pin, LOW);
  digitalWrite(HVEN_Pin, LOW);
}

static int epson_epdc_clear_init()
{
  return s1d135xx_clear_init();
}

//static int epson_epdc_update(struct pl_epdc *epdc, int wfid, enum pl_update_mode mode, const struct pl_area *area)
//{
//  struct s1d135xx *p = epdc->data;
//  return s1d135xx_update(p, wfid, mode, area);
//}

static int epson_epdc_wait_update_end()
{
  return s1d135xx_wait_update_end();
}

static int epson_epdc_set_power(enum pl_epdc_power_state state)
{
  if (s1d135xx_set_power_state(state))
    return -1;
  return 0;
}

static int epson_epdc_set_epd_power(int on)
{
  return s1d135xx_set_epd_power(on);
}

int epson_epdc_init()
{
 
  if (epson_epdc_init_s1d13541())
    return -1;

  if (s1d13541_load_wflib())
    return -1;
  return 0;
}

int epson_epdc_early_init()
{
  return epson_epdc_early_init_s1d13541();
}

 

void s1d135xx_hard_reset()
{
  digitalWrite(NRST_Pin, LOW);
  delay(4);
  digitalWrite(NRST_Pin, HIGH);
  delay(10);
}

int s1d135xx_soft_reset()
{
  s1d135xx_write_reg(S1D135XX_REG_SOFTWARE_RESET, 0xFF);
  return 0;
}

int s1d135xx_check_prod_code(uint16_t ref_code)
{
  uint16_t prod_code;

  prod_code = s1d135xx_read_reg(S1D135XX_REG_REV_CODE);

  do{
     prod_code = s1d135xx_read_reg(S1D135XX_REG_REV_CODE);
      Serial.println("prod_code:0x");
      Serial.print(prod_code,HEX);
    }while(prod_code!=ref_code);
 

  if (prod_code != ref_code) {
    return -1;
  }

  return 0;
}

uint16_t initdata2[sizeof(initdata1)/2];
int s1d135xx_load_init_code()
{
  uint16_t checksum;
  int stat;
  if (s1d135xx_wait_idle())
    return -1;
  set_cs(0);
  send_cmd(S1D135XX_CMD_INIT_SET);
//  stat = transfer_file();
  transfer_data(initdata1, sizeof(initdata1));
  set_cs(1);
  if (s1d135xx_wait_idle())
    return -1;
  set_cs(0);
  send_cmd(S1D135XX_CMD_INIT_STBY);
  send_param(0x0500);
  set_cs(1);
  delay(100);
  if (s1d135xx_wait_idle())
    return -1;
  checksum = s1d135xx_read_reg(S1D135XX_REG_SEQ_AUTOBOOT_CMD);

  if (!(checksum & (uint16_t)S1D135XX_INIT_CODE_CHECKSUM_OK)) {
    return -1;
  }

  return 0;
}

int s1d135xx_load_wflib(uint32_t size, uint32_t addr)
{
  uint16_t params[4];
  uint32_t size2 = sizeof(waveform) / 2;
  if (s1d135xx_wait_idle())
    return -1;
  params[0] = addr & 0xFFFF;
  params[1] = (addr >> 16) & 0xFFFF;
  params[2] = size2 & 0xFFFF;
  params[3] = (size2 >> 16) & 0xFFFF;
  set_cs(0);
  send_cmd(S1D135XX_CMD_BST_WR_SDR);
  send_params(params, 4);
  set_cs(1);
  wflib_wr(waveform, sizeof(waveform));
  if (s1d135xx_wait_idle())
    return -1;
  send_cmd_cs(S1D135XX_CMD_BST_END_SDR);

  return s1d135xx_wait_idle();
}

int s1d135xx_init_gate_drv()
{
  send_cmd_cs(S1D135XX_CMD_EPD_GDRV_CLR);

  return s1d135xx_wait_idle();
}

int s1d135xx_wait_dspe_trig()
{
  send_cmd_cs(S1D135XX_CMD_WAIT_DSPE_TRG);

  return 0;
}

int s1d135xx_clear_init()
{
  send_cmd_cs(S1D135XX_CMD_UPD_INIT);

  return s1d135xx_wait_dspe_trig();
}

int s1d135xx_fill(uint16_t mode, unsigned bpp, const struct pl_area *a, uint8_t grey)
{
  struct pl_area full_area;
  const struct pl_area *fill_area;

  set_cs(0);

  if (a != NULL) {
    send_cmd_area(S1D135XX_CMD_LD_IMG_AREA, mode, a);
    fill_area = a;
  } else {
    send_cmd(S1D135XX_CMD_LD_IMG);
    send_param(mode);
    full_area.top = 0;
    full_area.left = 0;
    full_area.width = 399;
    full_area.height = 239;
    fill_area = &full_area;
  }

  set_cs(1);

  return do_fill(fill_area, bpp, grey);
}

int s1d135xx_pattern_check(uint16_t height, uint16_t width, uint16_t checker_size, uint16_t mode)
{
  uint16_t i = 0, j = 0, k = 0;
  uint16_t val = 0;

  set_cs(0);
  send_cmd(S1D135XX_CMD_LD_IMG);
  send_param(mode);
  set_cs(1);
  if (s1d135xx_wait_idle())
    return -1;

  set_cs(0);
  send_cmd(S1D135XX_CMD_WRITE_REG);
  send_param(S1D135XX_REG_HOST_MEM_PORT);

  transfer_data(gImage_PIC,48000);

  set_cs(1);
  if (s1d135xx_wait_idle())
    return -1;
  send_cmd_cs(S1D135XX_CMD_LD_IMG_END);

  return 0;
}

int   usercde=0;
int s1d135xx_pattern_check_test_part(uint16_t height, uint16_t width, uint16_t checker_size, uint16_t mode,const struct pl_area *area)
{
  uint16_t i = 0, j = 0, k = 0;
  uint16_t val = 0;

  set_cs(0);
  send_cmd_area( S1D135XX_CMD_LD_IMG_AREA, mode, area);
  send_cmd(S1D135XX_CMD_LD_IMG);
  send_param(mode);
  set_cs(1);
  if (s1d135xx_wait_idle())
    return -1;

  set_cs(0);
  send_cmd(S1D135XX_CMD_WRITE_REG);
  send_param(S1D135XX_REG_HOST_MEM_PORT);

  
  
 
 
  if(usercde%2==0)
      transfer_data(gImage_part, height*width);
  else 
      transfer_data(gImage_tt, height*width);
  usercde++;
  
  set_cs(1);
  if (s1d135xx_wait_idle())
    return -1;
  send_cmd_cs(S1D135XX_CMD_LD_IMG_END);

  return 0;
}

int s1d135xx_update(int wfid, enum pl_update_mode mode,  const struct pl_area *area)
{
//  struct pl_area area_scrambled;
  uint8_t command = S1D135XX_CMD_UPDATE_FULL + mode;
  set_cs(0);

  /* wfid = S1D135XX_WF_MODE(wfid); */

  if (area != NULL) {
    if(!(command % 2 == 0))
      command++;

      send_cmd_area(command, S1D135XX_WF_MODE(wfid), area);

  } else {
    send_cmd(command);
    send_param(S1D135XX_WF_MODE(wfid));
  }

  set_cs(1);
 
  if (s1d135xx_wait_idle())
    return -1;

  return s1d135xx_wait_dspe_trig();
}

int s1d135xx_wait_update_end()
{
  send_cmd_cs(S1D135XX_CMD_WAIT_DSPE_FREND);

  return s1d135xx_wait_idle();
}

int s1d135xx_wait_idle()
{
  unsigned long timeout = 100000;

  while (!get_hrdy() && --timeout);

  if (!timeout) {
    
    return -1;
  }

  return 0;
}


int s1d135xx_set_power_state(enum pl_epdc_power_state state)
{
  int stat;

  set_cs(1);
  set_hdc(1);
//  HAL_GPIO_WritePin(GPIOB, EN3P3_Pin, GPIO_PIN_SET);
//  HAL_GPIO_WritePin(GPIOB, WKUP_Pin, GPIO_PIN_SET);

  switch (state) {
  case PL_EPDC_RUN:
    send_cmd_cs(S1D135XX_CMD_RUN);
    stat = s1d135xx_wait_idle();
    break;

  case PL_EPDC_STANDBY:
    send_cmd_cs(S1D135XX_CMD_STBY);
    stat = s1d135xx_wait_idle();
    break;

  case PL_EPDC_SLEEP:
    send_cmd_cs(S1D135XX_CMD_STBY);
    stat = s1d135xx_wait_idle();

    break;

  case PL_EPDC_OFF:
    send_cmd_cs(S1D135XX_CMD_SLEEP);
    stat = s1d135xx_wait_idle();

    set_hdc(0);
    set_cs(0);
    break;
  }

  return stat;
}

int s1d135xx_set_epd_power(int on)
{
  uint16_t arg = on ? S1D135XX_PWR_CTRL_UP : S1D135XX_PWR_CTRL_DOWN;
  uint16_t tmp;

  s1d135xx_write_reg(S1D135XX_REG_PWR_CTRL, arg);

  do {
    tmp = s1d135xx_read_reg(S1D135XX_REG_PWR_CTRL);
  } while (tmp & S1D135XX_PWR_CTRL_BUSY);

  if (on && ((tmp & S1D135XX_PWR_CTRL_CHECK_ON) !=
       S1D135XX_PWR_CTRL_CHECK_ON)) {
    return -1;
  }
  return 0;
}

void s1d135xx_cmd(uint16_t cmd, uint16_t *params, size_t n)
{
  set_cs(0);
  send_cmd(cmd);
  send_params(params, n);
  set_cs(1);
}

uint16_t s1d135xx_read_reg(uint16_t reg)
{
  uint16_t val;

  set_cs(0);
  send_cmd(S1D135XX_CMD_READ_REG);
  send_param(reg);
  
 
  val= hspi->transfer16(0xffff); 
  val= hspi->transfer16(0xffff);   
  set_cs(1);

  return val;  // swap bytes after read
//  return ((val<<8)&0xFF00) | ((val>>8)&0xFF);
}

void s1d135xx_write_reg(uint16_t reg, uint16_t val)
{
  uint16_t params[] = { reg, val };

  set_cs(0);
  send_cmd(S1D135XX_CMD_WRITE_REG);
  send_params(params, 2);
  set_cs(1);
}


/* ----------------------------------------------------------------------------
 * private functions
 */
#define S1D13541_STATUS_HRDY            (1 << 13)

static int get_hrdy()
{
  uint16_t status;
  status = s1d135xx_read_reg(S1D135XX_REG_SYSTEM_STATUS);

  return ((status & S1D13541_STATUS_HRDY) == S1D13541_STATUS_HRDY);
}

static int do_fill(const struct pl_area *area, unsigned bpp, uint8_t g)
{
  uint16_t val16;
  uint16_t lines;
  uint16_t pixels;

  /* Only 16-bit transfers for now... */
//  assert(!(area->width % 2));

  switch (bpp) {
  case 1:
  case 2:
//    LOG("Unsupported bpp");
    return -1;
  case 4:
    val16 = g & 0xF0;
    val16 |= val16 >> 4;
    val16 |= val16 << 8;
    pixels = area->width / 4;
    break;
  case 8:
    val16 = g | (g << 8);
    pixels = area->width / 2;
    break;
  default:;
//    assert_fail("Invalid bpp");
  }

  lines = area->height;

  if (s1d135xx_wait_idle())
    return -1;

  set_cs(0);
  send_cmd(S1D135XX_CMD_WRITE_REG);
  send_param(S1D135XX_REG_HOST_MEM_PORT);

  while (lines--) {
    uint16_t x = pixels;

    while (x--)
      send_param(val16);
  }

  set_cs(1);

  if (s1d135xx_wait_idle())
    return -1;

  send_cmd_cs(S1D135XX_CMD_LD_IMG_END);

  return s1d135xx_wait_idle();
}

static int wflib_wr(const uint8_t *data, size_t n)
{
  set_cs(0);
  send_cmd(S1D135XX_CMD_WRITE_REG);
  send_param(S1D135XX_REG_HOST_MEM_PORT);
  transfer_data(data, n);
  set_cs(1);

  return 0;
}


static void transfer_data(const uint8_t *data, size_t n)
{
  uint16_t *data16 = (uint16_t *)data;

  n /= 2;

  while (n--)
    send_param(*data16++);
}

static void send_cmd_area(uint16_t cmd, uint16_t mode,
        const struct pl_area *area)
{
  uint16_t args[] = {
    mode,
    (area->left & S1D135XX_XMASK),
    (area->top & S1D135XX_YMASK),
    (area->width & S1D135XX_XMASK),
    (area->height & S1D135XX_YMASK),
  };
#if VERBOSE
  LOG("%s: Command: 0x%04X", __func__, cmd);
#endif
  send_cmd(cmd);
  send_params(args, 5);
}

static void send_cmd_cs(uint16_t cmd)
{
  set_cs(0);
  send_cmd(cmd);
  set_cs(1);
}

static void send_cmd(uint16_t cmd)
{
//  uint16_t cmd2 = ((cmd<<8)&0xFF00) | ((cmd>>8)&0xFF);
//  cmd = htobe16(cmd); // swap bytes before writing
  set_hdc(0);
//  p->interface->write((uint8_t *)&cmd, sizeof(uint16_t));
//  HAL_SPI_Transmit(&hspi1, (uint8_t*)&cmd, 1, 0xff);
//  hspi->transfer((char)(cmd>>8));
//  hspi->transfer((char)(cmd&0xff00));  

  hspi->transfer16(cmd);
  set_hdc(1);
}

static void send_params(uint16_t *params, size_t n)
{
  size_t i;

  for (i = 0; i < n; ++i)
    send_param(params[i]);
}

static void send_param(uint16_t param)
{
 
 
  hspi->transfer16(param);
//  HAL_SPI_Transmit(&hspi1, (uint8_t*)&param, 1, 0xff);
}

static void set_cs(int state)
{
  if(state)  digitalWrite(SPICS_Pin, HIGH);
  if(!state) digitalWrite(SPICS_Pin, LOW);

}

static void set_hdc(int state)
{
  if(state) digitalWrite(HDC_Pin, HIGH);
  if(!state)digitalWrite(HDC_Pin, LOW);

}

int set_init_rot_mode()
{
  set_cs(0);
  send_cmd(S1D135XX_CMD_INIT_ROT_MODE);
  send_param(0x0400);
  set_cs(1);
  delay(100);
  return s1d135xx_wait_idle();
}


int s1d13541_load_wflib()
{
//  struct s1d135xx *p = epdc->data;

  return s1d135xx_load_wflib(2, S1D13541_WF_ADDR);
}

int s1d13541_set_temp_mode(enum pl_epdc_temp_mode mode)
{
//  struct s1d135xx *p = epdc->data;
  uint16_t reg;

//  if (mode == epdc->temp_mode)
//    return 0;

  reg = s1d135xx_read_reg(S1D135XX_REG_PERIPH_CONFIG);
  /* ToDo: when do we set this bit back? */
  reg &= S1D13541_TEMP_SENSOR_CONTROL;

  switch (mode) {
  case PL_EPDC_TEMP_MANUAL:
    break;
  case PL_EPDC_TEMP_EXTERNAL:
    reg &= ~S1D13541_TEMP_SENSOR_EXTERNAL;
    break;
  case PL_EPDC_TEMP_INTERNAL:
    reg |= S1D13541_TEMP_SENSOR_EXTERNAL;
    break;
  default:;
//    assert_fail("Invalid temperature mode");
  }

  s1d135xx_write_reg(S1D135XX_REG_PERIPH_CONFIG, reg);

  /* Configure the controller to automatically update the waveform table
   * after each temperature measurement.  */
  reg = s1d135xx_read_reg(S1D13541_REG_WF_DECODER_BYPASS);
  reg |= S1D13541_AUTO_TEMP_JUDGE_EN;
  s1d135xx_write_reg(reg, S1D13541_REG_WF_DECODER_BYPASS);

//  epdc->temp_mode = mode;

  return 0;
}

int s1d13541_update_temp(enum pl_epdc_temp_mode temp_mode)
{
//  struct s1d135xx *p = epdc->data;
  int stat;

  switch (temp_mode) {
  case PL_EPDC_TEMP_MANUAL:
//    stat = update_temp_manual(epdc->manual_temp);
    break;
  case PL_EPDC_TEMP_EXTERNAL:
    stat = update_temp_auto(S1D135XX_REG_I2C_TEMP_SENSOR_VALUE);
    break;
  case PL_EPDC_TEMP_INTERNAL:
    stat = update_temp_auto(S1D13541_REG_TEMP_SENSOR_VALUE);
    break;
  }

  if (stat)
    return -1;
  

  return 0;
}

int s1d13541_fill(const struct pl_area *area, uint8_t grey)
{
  return s1d135xx_fill(S1D13541_LD_IMG_8BPP, 8, area, grey);
}

int s1d13541_pattern_check(uint16_t size)
{
//return s1d135xx_pattern_check(240, 400, size, S1D13541_LD_IMG_8BPP);
  return s1d135xx_pattern_check(240, 400, size, S1D13541_LD_IMG_4BPP);  
}


int s1d13541_pattern_check_test_part(uint16_t size,const struct pl_area *area)
{
  return s1d135xx_pattern_check_test_part(10, 25, size, S1D13541_LD_IMG_1BPP,area);

}



/* -- initialisation -- */

int epson_epdc_early_init_s1d13541()
{
  int16_t measured_temp = -127;
  s1d135xx_hard_reset();
  
  if (s1d135xx_soft_reset())
    return -1;
  Serial.println("Check EPD ... ");   
  if (s1d135xx_check_prod_code(S1D13541_PROD_CODE))
    return -1;

  return s1d13541_init_clocks();
}

int epson_epdc_init_s1d13541()
{
//  struct s1d135xx *p = epdc->data;

  if (epson_epdc_early_init_s1d13541())
    return -1;

  if (s1d135xx_load_init_code()) {
    return -1;
  }



  // mg033 & mg034
  //s1d135xx_write_reg(p, 0x0140, 0);

  s1d135xx_write_reg(S1D13541_REG_PROT_KEY_1, S1D13541_PROT_KEY_1);
  s1d135xx_write_reg(S1D13541_REG_PROT_KEY_2, S1D13541_PROT_KEY_2);

  if (s1d135xx_wait_idle())
    return -1;
  
  if (s1d135xx_set_power_state(PL_EPDC_RUN))
    return -1;

  if (s1d135xx_init_gate_drv())
    return -1;

  if (s1d135xx_wait_dspe_trig())
    return -1;


  return s1d13541_set_temp_mode(PL_EPDC_TEMP_INTERNAL);
}

/* ----------------------------------------------------------------------------
 * private functions
 */

static int s1d13541_init_clocks()
{
  s1d135xx_write_reg(S1D135XX_REG_I2C_CLOCK, S1D13541_I2C_CLOCK_DIV);
  s1d135xx_write_reg(S1D13541_REG_CLOCK_CONFIG, S1D13541_INTERNAL_CLOCK_ENABLE);
  return s1d135xx_wait_idle();
}

static void update_temp(uint16_t reg)
{
  uint16_t regval;

  regval = s1d135xx_read_reg(S1D135XX_REG_INT_RAW_STAT);
//  p->flags.needs_update = (regval & S1D13541_INT_RAW_WF_UPDATE) ? 1 : 0;
  s1d135xx_write_reg(S1D135XX_REG_INT_RAW_STAT,
         (S1D13541_INT_RAW_WF_UPDATE |
          S1D13541_INT_RAW_OUT_OF_RANGE));
  regval = s1d135xx_read_reg(reg) & S1D135XX_TEMP_MASK;

}


static int update_temp_auto(uint16_t temp_reg)
{
  if (s1d135xx_set_power_state(PL_EPDC_STANDBY))
    return -1;

  s1d135xx_cmd(S1D13541_CMD_RD_TEMP, NULL, 0);

  if (s1d135xx_wait_idle())
    return -1;

  if (s1d135xx_set_power_state( PL_EPDC_RUN))
    return -1;

  update_temp(temp_reg);

  return 0;
}

int s1d13541_read_prom(uint8_t * blob)
{
       int i = 0, j = 0;
       uint16_t data = 0;
       uint16_t addr_ = 0;

       // wait for status: idle
       if(wait_for_ack(S1D13541_PROM_STATUS_IDLE, 0xffff))
              return -1;

       for(i=0; i<8; i++)
       {
              for(j=0; j<2; j++)
              {
                     // set read address
                     addr_ = ((i*2+j) << 8) & 0x0f00;
                     s1d135xx_write_reg(S1D13541_PROM_ADR_PGR_DATA, addr_);

                     // set read operation start trigger
                     s1d135xx_write_reg(S1D13541_PROM_CTRL, S1D13541_PROM_READ_START);

                     //wait for status: read mode start
                     if(wait_for_ack(S1D13541_PROM_STATUS_READ_MODE, S1D13541_PROM_STATUS_READ_MODE))
                           return -1;

                     //wait for status: read operation finished
                     if(wait_for_ack(0x0000, S1D13541_PROM_STATUS_READ_BUSY))
                           return -1;

                     // set read operation start trigger
                     data = s1d135xx_read_reg(S1D13541_PROM_READ_DATA);
                     if(j)
                           blob[i] |= data & 0x0f;
                     else
                           blob[i] = data << 4 & 0xf0;

              }
       }

       // set read mode stop trigger
       s1d135xx_write_reg(S1D13541_PROM_CTRL, S1D13541_PROM_READ_STOP);

       //wait for status: read mode stop
       if(wait_for_ack(0x0000, S1D13541_PROM_STATUS_READ_MODE))
              return -1;

       return 0;
}


static int wait_for_ack (uint16_t status, uint16_t mask)
{
       unsigned long timeout = 50000;
       uint16_t v;
       while ((v = s1d135xx_read_reg(S1D13541_PROM_STATUS) & mask) != status){
              --timeout;
              v=v;
              if (timeout == 0){
//                     LOG("PROM acknowledge timeout");
                     return -1;
              }
       }

       return 0;
}


int pl_epdc_single_update(int wfid, enum pl_update_mode mode, const struct pl_area *area)
{
  if (s1d13541_update_temp(PL_EPDC_TEMP_INTERNAL))
    return -1;

  s1d135xx_set_epd_power(1);
//  if (psu->on(psu))
//    return -1;

  if (s1d135xx_update(wfid, mode, area))
    return -1;

  if (s1d135xx_wait_update_end())
    return -1;
  
  s1d135xx_set_epd_power(0);
//  return psu->off(psu);
  return 0;
}



#endif /* INCLUDE_EPSON_EPDC_H */

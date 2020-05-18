/***************************************************************************
                          disphw32.h  -  description
                             -------------------
    begin                : Mon Jan 8 2001
    copyright            : (C) 2001 by Sven Fischer
    email                : fischer@deutaeit.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is copyrighted by DEUTA Werke GmbH, Germany.             *
 *   All rights reserved. Redistribution is not permitted.                 *
 *                                                                         *
 ***************************************************************************/

/**********************************************************/
/*    Interface for the Environment controller            */
/**********************************************************/
/*  Copyright (c) 1998 by Siemens AG.                     */
/*  Autor:    Roedel-Krainz                               */
/*  Version:  2.0 from 12.3.98                            */
/*                                                        */
/*                                                        */
/**********************************************************/
/* Changes                                                */
/* 23.3.98 JRK  added "msec" comments to time parameters  */
/*              minor beautifying: tabulator positions,   */
/*              changed comments: from // to c-like       */
/* 25.3.98 JRK  changes from Mr. Meischke concerning      */
/*                                a lot of const          */
/*              replaced tabs with spaces                 */
/*              BUFFER_TOO_SMALL instaed of _TO_SMALL     */
/* 26.3.98 JRK  removed BrightnessSensorType_t            */
/*              introduced fixed array size for keys      */
/**********************************************************/

# ifndef __DISPCNTL_H
# define __DISPCNTL_H


# define MAX_NUM_KEYS 128


/*
   states  after               cold start      reset

   watchdog                    off             off
   beeper                      off             off
   LED                         on              on
   auto brightness             off             off
   auto stop                   off             off
   callbacks                   off             off
   LCD                         off             remains
   keyboard                    off             remains
   key click                   off             off
   key mapping                 standard        remains
   critical temp.              remains         remains
   ventilators                 automatic       automatic
   heaters                     automatic       automatic
   brightness                  1/2 maximum     1/2 maximum
   brightness curve            remains         remains
*/

/* the whole file is C-code */
#ifdef __cplusplus
extern "C" {
#endif

  /**********************************************************/
  /*        include files                                   */
  /**********************************************************/
#ifdef _WINDOWS

# if !defined(__WINDOWS_H) && !defined(_INC_WINDOWS)
# include <windows.h>
# endif

  /* Assume byte packing throughout */
#ifdef _MSC_VER
#pragma pack(1)
#else
# if defined(__BCPLUSPLUS__) || defined (__BORLANDC__)
#  pragma option -a-
# else
#  include <pshpack1.h>
# endif
#endif

#else // _WINDOWS
#include <sys/types.h>
//#include <wchar.h>
#include "windefs.h"
#endif // _WINDOWS

#define EXPORT

  /**********************************************************/
  /* enumeration and structure type definition              */
  /**********************************************************/

  /* the sequence of enumerations is expected to be constant
     new elements must be inserted before _DO_NOT_USE_... */

  /* modes */
  typedef enum env_end_mode_ {
    ENV_MANUAL_MODE,
    ENV_AUTOMATIC_MODE,
    ENV_DO_NOT_USE_ENV_END_MODE_ = 0x7FFF
  } ENV_EndMode_t, FAR * LP_ENV_EndMode_t;

  /* general return values */
  typedef enum env_status_{
    ENV_OK,
    ENV_NOT_YET_IMPLEMENTED,
    ENV_OVERFLOW,
    ENV_UNDERFLOW,
    ENV_INVALID_PARAMETER,
    ENV_CONTROLLER_ERROR,
    ENV_CONTROLLER_TIMEOUT,
    ENV_BUSY,
    ENV_NO_ACCESS,
    ENV_BUFFER_TOO_SMALL,
    ENV_MEMORY_ERROR,
    ENV_ERROR_1,                            /* these are producer specific */
    ENV_ERROR_2,
    ENV_ERROR_3,
    ENV_ERROR_4,
    ENV_ERROR_5,
    ENV_ERROR_6,
    ENV_ERROR_7,
    ENV_ERROR_8,
    ENV_ERROR_9,
    ENV_ERROR_10,
    ENV_ERROR_11,
    ENV_ERROR_12,
    ENV_ERROR_13,
    ENV_ERROR_14,
    ENV_ERROR_15,
    ENV_ERROR_16,
    ENV_ERROR_17,
    ENV_ERROR_19,
    ENV_ERROR_20,
    ENV_FAILURE        = ENV_ERROR_1,
    ENV_THREAD_NOT_REGISTERED  = ENV_ERROR_2,
    ENV_DO_NOT_USE_ENV_STATUS_ = 0x7FFF
  }ENV_Status_t, FAR * LP_ENV_Status_t;


  /* sensor types */
  typedef struct env_sensors_{
    BYTE          bNumSensors;
    long          lValues[3];               /* open array */
  } ENV_Sensors_t, FAR * LP_ENV_Sensors_t;


  /* brightness device */
  typedef enum env_brightness_device_{
    ENV_DISPLAY,
    ENV_KEYBOARD,
    ENV_DO_NOT_USE_ENV_BRIGHTNESS_DEVICE_ = 0x7FFF
  }ENV_BrightnessDevice_t, FAR * LP_ENV_BrightnessDevice_t;

  /* boundary limits */
  typedef struct env_Limits_{
    long          lLower;
    long          lUpper;
  } ENV_Limits_t, FAR * LP_ENV_Limits_t;

  /* brightness curve */
  typedef struct env_curve_{
    DWORD         dwDelay;                  /* in msec */
    WORD          wHysteresis;              /* absolute in Candela */
    BYTE          bNumPoints;               /* see config, must be set  */
    long          lPoints[6];               /* open array */
  } ENV_Curve_t, FAR * LP_ENV_Curve_t;

  /* state of controls  */
  typedef enum env_autoSwitch_ {
    ENV_OFF,
    ENV_ON,
    ENV_AUTOMATIC,
    ENV_DEFECT,
    ENV_DO_NOT_USE_ENV_AUTOSWITCH_ = 0x7FFF
  }ENV_Autoswitch_t, FAR * LP_ENV_Autoswitch_t;


  /* temperature sensor types */
  typedef enum env_tempSensor_{
    ENV_PROCESSOR_TEMP_SENSOR,
    ENV_DISPLAY_TEMP_SENSOR,
    ENV_DEVICE_TEMP_SENSOR,
    ENV_FRONT_TEMP_SENSOR,
    ENV_STECKER_TEMP_SENSOR,
    ENV_BASE_TEMP_SENSOR,
    ENV_DO_NOT_USE_ENV_TEMP_SENSOR = 0x7FFF
  }ENV_TempSensorType_t, FAR * LP_ENV_TempSensorType_t;



  /* ventilator types */
  typedef enum env_ventilatorType_{
    ENV_PROCESSOR_VENTILATOR,
    ENV_HEATER_VENTILATOR,
    ENV_INT_VENTILATOR,
    ENV_EXT_VENTILATOR,
    ENV_DO_NOT_USE_ENV_VENTILATOR = 0x7FFF
  }ENV_VentilatorType_t, FAR * LP_ENV_VentilatorType_t;


  /* heater state */
  typedef struct env_heaterState_{
    long                  lTemperatureOn;   /* Temperature switching on Celsius */
    long                  lTemperatureOff;  /* Temperature switching off */
    BOOL                  bOn;              /* TRUE, if on */
    ENV_Autoswitch_t      eState;           /* ON, OFF, AUTOMATIC */
  } ENV_HeaterState_t, FAR * LP_ENV_HeaterState_t;

  /* ventilator state */
  typedef struct env_ventState_{
    ENV_Autoswitch_t      eSwitched;        /* ON, OFF or AUTO */
    WORD                  wRpm;             /* revolutions per minute */
  } ENV_VentState_t, FAR * LP_ENV_VentState_t;


  /* key types */

  /*
     The first call to getKeyboardMapping delivers the keys that are available.
     Keys, that are not available have code and modifier set to 0.
     The enum describes the label of the keys, it has to used as an index into
     the array of keys used by the following funktions
     - getKeyboardState
     - getKeyboardMapping and
     - setKeyboardMapping

  */

  typedef enum env_keyNumber_ {
    ENV_F1,                               /* 1 */
    ENV_F2,                               /* 2 */
    ENV_F3,                               /* 3 */
    ENV_F4,                               /* 4 */
    ENV_F5,                               /* 5 */
    ENV_F6,                               /* 6 */
    ENV_F7,                               /* 7 */
    ENV_F8,                               /* 8 */
    ENV_F9,                               /* 9 */
    ENV_F10,                              /* 0 */
    ENV_ESC,                              /* C */
    ENV_RETURN,                           /* OK, Q */
    ENV_PAGE_UP,                          /* Pfeil oben */
    ENV_PAGE_DOWN,                        /* Pfeil unten */
    ENV_SUN_OUT,                          /* Sonne aus */
    ENV_S,                                /* S */
    ENV_I,                                /* i */
    ENV_ST,                               /* St */
    ENV_V_GREATER_ZERO,                   /* V>0 */
    ENV_V_EQUAL_ZERO,                     /* V=0 */
    ENV_DIM,                              /* Stern (Sonne) */
    ENV_WHITE_BLACK,            /* Kreis, halb wei� halb schwarz (Kontrast) */
    ENV_UD,                               /* UD */
    ENV_LEFT,                             /* Pfeil links */
    ENV_RIGHT,                            /* Pfeil rechts */
    /* --- begin DEUTA specific extensions for MFD15 --- */
    ENV_POWER,                 /* on/off*/
    ENV_SPLIT_LEFT,                       /* Blatttr. Links*/
    ENV_SPLIT_RIGHT,                      /* Blatttr. Rechts*/
    ENV_COPY,                 /* Blaetter*/
    /* --- end DEUTA specific extensions for MFD15 --- */
    /* --- begin DEUTA specific extensions for MFT1 --- */
    ENV_QUESTION_MARK,                    /* ? */
    ENV_MONITOR,                          /* Monitor */
    /* --- end DEUTA specific extensions for MFT1 --- */
    ENV_DO_NOT_USE_ENV_KEYNUMBER_ = 0x7FFF
  } ENV_KeyNumber_t, FAR * LP_ENV_KeyNumber_t;


  /* state of complete keyboard */
  typedef struct env_keyboardstate_{
    DWORD         dwStartDelay;             /* in msec */
    DWORD         dwRepeatDelay;            /* in msec */
    BOOL          bSwitchedOn;
    WORD          wDownClick;               /* in msec */
    WORD          wUpClick;                 /* in msec */
    BYTE          bKeys[MAX_NUM_KEYS];     /* true if pressed */
  } ENV_Keyboardstate_t, FAR * LP_ENV_Keyboardstate_t;


  /* key modifier */
  typedef enum env_keyModifier_{
    ENV_MOD_L_SHIFT       =  (1 << 0),
    ENV_MOD_R_SHIFT       =  (1 << 1),
    ENV_MOD_L_CNTRL       =  (1 << 2),
    ENV_MOD_R_CNTRL       =  (1 << 3),
    ENV_MOD_L_ALT         =  (1 << 4),
    ENV_MOD_R_ALT         =  (1 << 5),
    ENV_DO_NOT_USE_ENV_KEY_MODIFIER_ = 0x7FFF
  }ENV_KeyModifier_t, FAR * LP_ENV_KeyModifier_t;


  /* one sound or color */
  typedef struct env_sound_{
    DWORD         dwTime;                   /* duration of one sound msec */
    DWORD         dwFrequence;              /* color: rgb, sound: Hz */
    /* monochrom: on if != 0 */
  } ENV_Sound_t, FAR * LP_ENV_Sound_t;


  /* sound or led state */
  typedef struct env_beeperState_{
    /* for get... function */
    DWORD         dwFrequence;              /* actual sound or color */
    DWORD         dwDuration;               /* rest of duration: msec */
    /* for set... function */
    BOOL          bKeyStops;                /* any pressed key stops sound */
    DWORD         dwNum;                    /* number of sounds */
    ENV_Sound_t   stSound[2];               /* open array */
  } ENV_BeeperState_t, FAR * LP_ENV_BeeperState_t;

  /* irda pulse */
  typedef enum env_Pulse_  {
    ENV_PULSE_3_16,
    ENV_PULSE_1U6,
    ENV_DO_NOT_USE_ENV_PULSE_ = 0x7FFF
  } ENV_Pulse_t, FAR * LP_ENV_Pulse_t;

  /* serial line baud rate */
  typedef enum env_Baud_  {
    ENV_BAUD_600,
    ENV_BAUD_1200,
    ENV_BAUD_1800,
    ENV_BAUD_2400,
    ENV_BAUD_3600,
    ENV_BAUD_4800,
    ENV_BAUD_7200,
    ENV_BAUD_9600,
    ENV_BAUD_12800,
    ENV_BAUD_14400,
    ENV_BAUD_19200,
    ENV_BAUD_38400,
    ENV_BAUD_57600,
    ENV_BAUD_115200,
    ENV_DO_NOT_USE_ENV_BAUD_ = 0x7FFF
  } ENV_Baud_t, FAR * LP_ENV_Baud_t;

  /* producer type */
  typedef enum  env_producer_{
    ENV_PROD_NONE,
    ENV_PROD_SIEMENS,
    ENV_PROD_DEUTA,
    ENV_PROD_BACHLEITNER_HEUGEL,
    ENV_DO_NOT_USE_ENV_PRODUCER_ = 0x7FFF
  }ENV_Producer_t, FAR * LP_ENV_Producer_t;

  /* hard disc type */
  typedef enum env_hdType_{
    ENV_HD_TYPE_NONE,
    ENV_HD_TYPE_HD,
    ENV_HD_TYPE_FLASH,
    ENV_HD_TYPE_CD_ROM,
    ENV_HD_TYPE_DVD,
    ENV_DO_NOT_USE_ENV_HDTYPE_ = 0x7FFF
  }ENV_HdType_t, FAR * LP_ENV_HdType_t;

  /* display type */
  typedef enum env_dispType_{
    ENV_DISP_TYPE_EL,
    ENV_DISP_TYPE_TFT,
    ENV_DISP_TYPE_LCD,
    ENV_DO_NOT_USE_ENV_DISPTYPE_ = 0x7FFF
  }ENV_DispType_t, FAR * LP_ENV_DispType_t;

  /* keyboard type */
  typedef enum env_keyboardType_{
    ENV_KBD_TYPE_NONE,
    ENV_KBD_TYPE_MECHANIC,
    ENV_KBD_TYPE_FOIL,
    ENV_KBD_TYPE_PIEZO,
    ENV_KBD_TYPE_TOUCH_PANEL,
    ENV_DO_NOT_USE_ENV_KEYBOARDTYPE_ = 0x7FFF
  }ENV_KeyboardType_t, FAR * LP_ENV_KeyboardType_t;

  /* interfacetypes */
  typedef enum env_interfaceType_{
    ENV_IF_LPT_1,
    ENV_IF_LPT_2,
    ENV_IF_COM_1,
    ENV_IF_COM_2,
    ENV_IF_COM_3,
    ENV_IF_COM_4,
    ENV_IF_COM_5,
    ENV_IF_COM_6,
    ENV_IF_COM_7,
    ENV_IF_COM_8,
    ENV_IF_FD,
    ENV_IF_IrDA,
    ENV_IF_IBIS,
    ENV_IF_TRAIN_BUS,
    ENV_IF_ETHERNET,
    ENV_IF_RADIO_CLOCK,
    ENV_IF_SOUND_CARD,
    ENV_IF_VIDEO_CARD,
    ENV_IF_HD_IDE,
    ENV_IF_KEYB_PC,
    ENV_DO_NOT_USE_ENV_INTERFACE_TYPE_ = 0x7FFF
  }ENV_InterfaceType_t, FAR * LP_ENV_InterfaceType_t;

  /* touchscreen type */
  typedef enum env_TouchscreenType_{
    ENV_TOUCH_TYPE_NONE,
    ENV_TOUCH_TYPE_IR,
    ENV_TOUCH_TYPE_AW,
    ENV_TOUCH_TYPE_RES,                      // @SW 14.12.01
    ENV_TOUCH_TYPE_RES_SCHURTER,
    ENV_DO_NOT_USE_ENV_TOUCHSCREEN_TYPE_ = 0x7FFF
  }ENV_TouchscreenType_t, FAR * LP_ENV_TouchscreenType_t;

  /* max possible display resolution */
  typedef enum env_displayResolution_{
    ENV_EGA,
    ENV_VGA_640_480,
    ENV_VGA_800_600,
    ENV_VGA_1024_768,
    ENV_VGA_1280_1024,
    ENV_DO_NOT_USE_ENV_DISPLAY_RESOLUTION_ = 0x7FFF
  }ENV_DisplayResolution_t, FAR * LP_ENV_DisplayResolution_t;

  /* communication protocol */
  typedef enum env_networkType_{
    ENV_COMM_DIN,
    ENV_COMM_TCN,
    ENV_COMM_MVBPC104,
    ENV_DO_NOT_USE_ENV_NETWORK_TYPE = 0x7FFF
  }ENV_NetworkType_t, FAR * LP_ENV_NetworkType_t;

  typedef enum env_busType_{
    ENV_MVB_SIEMENS_TRAFO = 0x11,
    ENV_MVB_SIEMENS_OPTO = 0x12,
    ENV_MVB_BOMBARDIER_TRAFO = 0x21,
    ENV_MVB_BOMBARDIER_OPTO = 0x22,
    ENV_DO_NOT_USE_ENV_BUS_TYPE = 0x7FFF
  }ENV_BusType_t;

  typedef enum env_ethernetType_{
    ENV_ETHERNET10B2PC104 = 0x01,
    ENV_ETHERNET10BTRTLTNC = 0x02,
    ENV_ETHERNET10BTRTLRJ45 = 0x04,
    ENV_ETHERNET100BTX = 0x08
  }ENV_EthernetType_t;

  /*typedef enum env_ColorBits_{
    ENV_MONOCHROM,
    ENV_4BIT,
    ENV_8BIT,
    ENV_16BIT,
    ENV_24BIT,
    ENV_DO_NOT_USE_COLORBIT = 0x7FFF
    }ENV_ColorBits_t, FAR * LP_ENV_ColorBits_t;
  */

  /* type of callback message */
  typedef enum env_CallbackMessageType_{
    ENV_CRITICAL_TEMP,
    ENV_WATCHDOG_HALFTIME,
    ENV_BRIGHTNESS_CHANGED,
    ENV_BEEP_LED_CHANGED,
    ENV_ADDRESS_CHANGED,
    ENV_POWER_ON_CHANGED,
    ENV_KEY_PRESSED,
    MAXCALLBACKS,
    ENV_DO_NOT_USE_ENV_CALLBACK_MESSAGE_TYPE_ = 0x7FFF
  }ENV_CallbackMessageType_t, FAR * LP_ENV_CallbackMessageType_t;


  /* configuration of display */
  typedef struct env_config_{
    WORD                          wStructSize;
    ENV_Producer_t                eProducer;
    BYTE                          bDeviceType[128];      /* c-string */
    DWORD                         dwSerialNumber;
    DWORD                         dwFwVersion;
    DWORD                         dwFwVersion2;
#ifdef _WINDOWS
    DWORD                         dwDllVersion;
#else
    BYTE                          bLibVersion[5];
#endif
    char                          sHwVersion[4];
    WORD                          wRAMSize;               /* in MB */
    ENV_DispType_t                eDispType;              /* TFT, ... */
    ENV_TouchscreenType_t         eTouchType;
    WORD                          wDispSize;              /* 1/10 Zoll */
    ENV_DisplayResolution_t       eDispResolution;        /* maximum */
    BYTE                          bColorBits;            /* bits per color */
    ENV_NetworkType_t             eNetworkType;           /* DIN, TCN */
    ENV_KeyboardType_t            eKeyboardType;          /* Folie, ... */
    ENV_BusType_t                 eBusType;
    ENV_EthernetType_t            eEthernetType;
    BYTE                          bSound;
    BYTE                          bVideo;
    BYTE                          bMinNumBrightCurvePoints;
    BYTE                          bMaxNumBrightCurvePoints;
    BYTE                          bNumHeaters;    // @SW 14.12.01
    BYTE                          bNumVentilators;
    ENV_VentilatorType_t    FAR * lpeVentilatorTypes;
    BYTE                          bNumSensorsBrightness;
    ENV_BrightnessDevice_t  FAR * lpeBrightnessSensorTypes;
    BYTE                          bNumSensorsTemperature;
    ENV_TempSensorType_t    FAR * lpeTemperatureSensorTypes;
    BYTE                          bNumHds;
    ENV_HdType_t            FAR * lpeHdTypes;
    DWORD                   FAR * lpdwHdSize;   /* MB */
    BYTE                          bNumLEDs;
    DWORD                   FAR * lpdwColorLED; /* RGB */
    BYTE                          bNumBeepers;
    DWORD                   FAR * lpdwBeeperFreq;
    BYTE                          bNumInterfaces;
    ENV_InterfaceType_t     FAR * lpeInterfaceType;
  } ENV_Config_t, FAR * LP_ENV_Config_t;

  typedef struct env_time_{
    WORD h;
    BYTE m;
    BYTE s;
  } ENV_Time_t;

  typedef struct env_diagnose_{
    ENV_Time_t                    sSystemTime;
    ENV_Time_t                    sMaintenanceTime[2];
    ENV_Time_t                    sVentilatorTime[3];
    ENV_Time_t                    sCCFLTime;
    ENV_Time_t                    sTooColdTime;
    ENV_Time_t                    sTooHotTime;
    WORD                          sOnCount;
    WORD                          sOffCount;
    WORD                          sExtendedTempCount;
    BYTE                          sSwitchOffReason[6];
    BYTE                          sSwitchOffIndex;
  } ENV_Diagnose_t, FAR * LP_ENV_Diagnose_t;


  /* for callbacks */

#ifdef _WINDOWS
  typedef void (CALLBACK * ENV_CB_Func_t) (const DWORD dwParam);
#else
#if 0 // def __QNXNTO__
  typedef  int ENV_CB_Func_t;
#else // __QNXNTO__
//#ifdef __cplusplus
#if 1
  class ENV_CB_Interface
  {
  public:
    virtual ~ENV_CB_Interface() {}
    virtual void callback( unsigned char type, unsigned short data ) = 0;
  };
    typedef ENV_CB_Interface* ENV_CB_Func_t;
#else
    typedef void (CALLBACK * ENV_CB_Func_t) (unsigned char type, unsigned short data);
#endif
#endif // __QNXNTO__
#endif // _WINDOWS


  /**********************************************************/
  /*        function declarations                           */
  /**********************************************************/

  /* delivers english c-string  */
  /* up to 128 Bytes incuding trailing 0  */

  ENV_Status_t WINAPI
  ENV_getErrorText              (const ENV_Status_t       eError,
                                 wchar_t FAR              * const lpcwText);


  ENV_Status_t WINAPI
  ENV_rebootPC                  (void);

  ENV_Status_t WINAPI
  ENV_switchVentilators         (const BOOL               bOn);

  ENV_Status_t WINAPI
  ENV_shutdownSystem            (const DWORD              dwDelay);  /* msec */

  ENV_Status_t WINAPI
  ENV_getPowerOnCommand         (BOOL FAR                 * const lpbOn);

  ENV_Status_t WINAPI
  ENV_setSwitchOffMode          (const ENV_EndMode_t      eMode,
                                 const DWORD              dwDelay); /* msec */

  ENV_Status_t WINAPI
  ENV_getBrightness             (ENV_Sensors_t FAR        * const lpstBrightness);

  ENV_Status_t WINAPI
  ENV_getBrightnessRelative     (const ENV_BrightnessDevice_t eType,
                                 WORD                     * const lpwBrightness);

  ENV_Status_t WINAPI
  ENV_getSensorBrightnessRelative (ENV_Sensors_t          * const lpstBrightness);

  ENV_Status_t WINAPI
  ENV_setBrightnessCurve        (const ENV_BrightnessDevice_t eType,
                                 const ENV_Curve_t FAR    * const lpstCurve);

  ENV_Status_t WINAPI
  ENV_getBrightnessCurve        (const ENV_BrightnessDevice_t eType,
                                 ENV_Curve_t FAR          * const lpstCurve);

  ENV_Status_t WINAPI
  ENV_setBrightnessOffset       (const ENV_BrightnessDevice_t eType,
                                 const short                  sBrightness);

  ENV_Status_t WINAPI
  ENV_setBrightnessDelay        (const ENV_BrightnessDevice_t eType,
                                 const short                  sDelay);

  ENV_Status_t WINAPI
  ENV_calibrateBrightness       (ENV_Sensors_t FAR        * const lpstBrightness);

  ENV_Status_t WINAPI
  ENV_setBrightnessFreshUp      (const DWORD              dwTime); /* msec */

  /* slope: 0 invalid
     if slope not implemented: only 0xFFFF valid */
  ENV_Status_t WINAPI
  ENV_activateAutomaticBrightness  (const BOOL            bOn,
                                    const WORD            wSlope); /* Candela per ...*/

  ENV_Status_t WINAPI
  ENV_setBrightnessAbsolute     (const ENV_BrightnessDevice_t eType,
                                 const WORD                   wBrightness);

  ENV_Status_t WINAPI
  ENV_setBrightnessRelative     (const ENV_BrightnessDevice_t eType,
                                 const WORD                   wBrightness);

  ENV_Status_t WINAPI
  ENV_setDisplayLight           (const ENV_BrightnessDevice_t eType,
                                 const BOOL                   bOn);

  ENV_Status_t WINAPI
  ENV_getOperatingTemperature   (ENV_Limits_t FAR         * const lpstLimits);

  ENV_Status_t WINAPI
  ENV_simulateTemperature       (const short              sOffset); /* Celsius */

  ENV_Status_t WINAPI
  ENV_setCriticalTemperature    (const ENV_Limits_t FAR   * const lpstLimits);

  ENV_Status_t WINAPI
  ENV_getCriticalTemperature    (ENV_Limits_t FAR         * const lpstLimits);

  ENV_Status_t WINAPI
  ENV_setTemperatureManagement  (const BOOL               bOn);

  ENV_Status_t WINAPI
  ENV_getTemperature            (ENV_Sensors_t FAR        * const lpstTemp,
                                 DWORD FAR                * const lpdwCritTime); /* msec */

  ENV_Status_t WINAPI
  ENV_setHeatingState           (const ENV_Autoswitch_t   eState);

  ENV_Status_t WINAPI
  ENV_getHeatingState           (ENV_HeaterState_t FAR    * const lpstHeaterState);

  ENV_Status_t WINAPI
  ENV_setVentilatorState        (const ENV_Autoswitch_t   eState);

  ENV_Status_t WINAPI
  ENV_getVentilatorState        (const BYTE               byIndex,
                                 ENV_VentState_t FAR      * const lpstState);

  ENV_Status_t WINAPI
  ENV_setWatchdog               (const DWORD              dwTime); /* msec */

  ENV_Status_t WINAPI
  ENV_getWatchdogCounter        (DWORD FAR                * const lpdwCount);

  ENV_Status_t WINAPI
  ENV_resetWatchdogEventCounter (void);

  ENV_Status_t WINAPI
  ENV_getWatchdogEventCounter   (DWORD FAR                * const lpdwCount);

  ENV_Status_t WINAPI
  ENV_activateKeyboard          (const BOOL               bOn);

  ENV_Status_t WINAPI
  ENV_setKeyboardRepeat         (const DWORD              dwStartDelay,
                                 const DWORD              dwRepeatDelay);

  ENV_Status_t WINAPI
  ENV_setKeyboardClick          (const DWORD              dwDown,
                                 const DWORD              dwUp);

  ENV_Status_t WINAPI EXPORT
  ENV_setKeyboardLED            (const DWORD              dwDown,
                                 const DWORD              dwUp,
                                 const BYTE               byIndex);

  ENV_Status_t WINAPI
  ENV_getKeyboardState          (ENV_Keyboardstate_t  FAR * const lpstState);

  /* pointer to arrays with size MAX_KEY_NUM */
  ENV_Status_t WINAPI
  ENV_setKeyboardMapping        (const BYTE FAR           * const lpbCode,
                                 const BYTE FAR           * const lpbModifier);

  /* if a key is not available then the first call
     delivers values 0 for Code and Modifier */
  ENV_Status_t WINAPI
  ENV_getKeyboardMapping        (BYTE FAR                 * const lpbCode,
                                 BYTE FAR                 * const lpbModifier);

  ENV_Status_t WINAPI
  ENV_activateBeeper            (const BYTE               byIndex,
                                 const BOOL               bOn);

  ENV_Status_t WINAPI
  ENV_activateLED               (const BYTE               byIndex,
                                 const BOOL               bOn);

  ENV_Status_t WINAPI
  ENV_synchronizeLEDToBeeper    (const BYTE               byIndexLED,
                                 const BYTE               byIndexBeeper);

  ENV_Status_t WINAPI
  ENV_synchronizeBeeperToLED    (const BYTE               byIndexBeeper,
                                 const BYTE               byIndexLED);

  ENV_Status_t WINAPI
  ENV_setBeeper                 (const BYTE               byIndex,
                                 const ENV_BeeperState_t FAR    * const lpstState);

  ENV_Status_t WINAPI
  ENV_setLED                    (const BYTE               byIndex,
                                 const ENV_BeeperState_t FAR    * const lpstState);

  ENV_Status_t WINAPI
  ENV_getBeeperState            (const BYTE               byIndex,
                                 ENV_BeeperState_t FAR    * const lpstState);

  ENV_Status_t WINAPI
  ENV_setSchnarre               (const BYTE               byOn);

  ENV_Status_t WINAPI
  ENV_writeSerialNumber         (long lSerNo);

  ENV_Status_t WINAPI
  ENV_getLEDState               (const BYTE               byIndex,
                                 ENV_BeeperState_t FAR    * const lpstState);

  ENV_Status_t WINAPI
  ENV_getAddress                (BYTE FAR                 * const lpbAddr);

  ENV_Status_t WINAPI
  ENV_getInputState             (BYTE FAR                 * const lpbState);

  ENV_Status_t WINAPI
  ENV_getOutputState            (BYTE FAR                 * const lpbState);

  ENV_Status_t WINAPI
  ENV_setOutputState            (const BYTE               byState);

  ENV_Status_t WINAPI
  ENV_setIrDAState              (const ENV_Baud_t         eBaud,
                                 const ENV_Pulse_t        ePulse);

  ENV_Status_t WINAPI
  ENV_getIrDAState              (ENV_Baud_t FAR           * const lpeBaud,
                                 ENV_Pulse_t FAR          * const lpePulse);

  ENV_Status_t WINAPI
  ENV_setRegister               (UINT                     iRegister,
                                 UINT                     iValue,
                                 UINT                     iService);

  ENV_Status_t WINAPI
  ENV_getRegister               (UINT                     iRegister,
                                 UINT                     * pValue);

  ENV_Status_t WINAPI
  ENV_init                      (void);

  void WINAPI
  ENV_exit                      (void);

  ENV_Status_t WINAPI
  ENV_resetController           (void);

  ENV_Status_t WINAPI
  ENV_loadDefaults              (const BOOL               bUser);

  ENV_Status_t WINAPI
  ENV_getConfig                 (ENV_Config_t FAR * FAR * lplpstConfig);

  ENV_Status_t WINAPI
  ENV_getDiagnose               (ENV_Diagnose_t FAR * FAR * lplpstConfig);

  ENV_Status_t WINAPI
  ENV_ioctrl                    (const short int            iFd,
                                 const short int            iReq,
                                 void FAR                 * const lpArg);

  ENV_Status_t WINAPI
  ENV_setCallback               (const ENV_CallbackMessageType_t                eEvent,
                                 ENV_CB_Func_t            lpFunc);

  ENV_Status_t WINAPI
  ENV_setHeaters                (int HeaterNum);

  ENV_Status_t WINAPI
  ENV_setAccessCode             (WORD wCode);

#ifdef __WATCOMC__
  int activateTrigger();
  void readTrigger();
  void getCallback( int* ev, int* data );
#endif // __WATCOMC__

  /**********************************************************/
  /*        prototypes for callbacks                        */
  /**********************************************************/

# if 0
  void CALLBACK
  ENV_msgCriticalTemp           (const DWORD    dwTooHot);
  /* 1 upper, 2 lower, 0 normal */

  void CALLBACK
  ENV_msgWatchdog               (const DWORD    dwTime); /* msec */

  void  CALLBACK
  ENV_msgBrightnessChanged      (const DWORD    dwBrightness);

  /* lowest Byte: new state (1 ON, 0 OFF)
     next       : index
     next        : type (LED: 1, Beeper 0)
  */

  void  CALLBACK
  ENV_msgBeeperLEDChanged       (const DWORD    dwBeeperLED);

  void  CALLBACK
  ENV_msgAddressChanged         (const DWORD    dwAddr);

  void  CALLBACK
  ENV_msgPowerOnChanged         (const DWORD    dwOn);
# endif

  /* Revert to default packing */
#ifdef _WINDOWS

#ifdef _MSC_VER
#pragma pack()
#else
# if defined(__BCPLUSPLUS__) || defined (__BORLANDC__)
# else
#  include <poppack.h>
# endif
#endif

#endif // _WINDOWS


#ifdef __cplusplus
}
#endif


# endif /* __DISPCNTL_H */




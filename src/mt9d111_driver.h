/*
 * mt9d111_driver.h
 * 
 * Copyright (C) 2018, Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * This file is part of MT9D111-Driver.
 * 
 * MT9D111-Driver is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * MT9D111-Driver is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with MT9D111-Driver. If not, see <http://www.gnu.org/licenses/>.
 * 
 */

/**
 * \brief MT9D111 firmware driver variables.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0-dev
 * 
 * \date 06/07/2018
 * 
 * \defgroup driver Driver
 * \ingroup mt9d111
 * \{
 */

#ifndef MT9D111_DRIVER_H_
#define MT9D111_DRIVER_H_

// Drivers IDs (Table 9: Drivers IDs)
#define MT9D111_DRIVER_ID_MONITOR                                       (0 << 8)    /**< Var name = mon. */
#define MT9D111_DRIVER_ID_SEQUENCER                                     (1 << 8)    /**< Var name = seq. */
#define MT9D111_DRIVER_ID_AUTO_EXPOSURE                                 (2 << 8)    /**< Var name = ae. */
#define MT9D111_DRIVER_ID_AUTO_WHITE_BALANCE                            (3 << 8)    /**< Var name = awb. */
#define MT9D111_DRIVER_ID_FLICKER_DETECTION                             (4 << 8)    /**< Var name = fd. */
#define MT9D111_DRIVER_ID_AUTO_FOCUS                                    (5 << 8)    /**< Var name = af. */
#define MT9D111_DRIVER_ID_AUTO_FOCUS_MECHANICS                          (6 << 8)    /**< Var name = afm. */
#define MT9D111_DRIVER_ID_MODE                                          (7 << 8)    /**< Var name = mode. */
#define MT9D111_DRIVER_ID_JPEG                                          (9 << 8)    /**< Var name = jpeg. */
#define MT9D111_DRIVER_ID_HISTOGRAM                                     (11 << 8)   /**< Var name = hg. */

// Driver Variables

// Monitor Driver (Table 10: Driver Variables-Monitor Driver (ID = 0))
#define MT9D111_DRIVER_VAR_MONITOR_CMD                                  2           /**< . */
#define MT9D111_DRIVER_VAR_MONITOR_ARG1                                 3           /**< . */
#define MT9D111_DRIVER_VAR_MONITOR_ARG2                                 5           /**< . */
#define MT9D111_DRIVER_VAR_MONITOR_MSG_COUNT                            7           /**< . */
#define MT9D111_DRIVER_VAR_MONITOR_MSG                                  8           /**< . */
#define MT9D111_DRIVER_VAR_MONITOR_VER                                  12          /**< . */

// Sequence Driver (Table 11: Driver Variables-Sequence Driver (ID = 1))
#define MT9D111_DRIVER_VAR_SEQUENCER_MODE                               2           /**< Name = mode. */
#define MT9D111_DRIVER_VAR_SEQUENCER_CMD                                3           /**< Name = cmd. */
#define MT9D111_DRIVER_VAR_SEQUENCER_STATE                              4           /**< Name = state. */
#define MT9D111_DRIVER_VAR_SEQUENCER_STEP_MODE                          5           /**< Name = setMode. */
#define MT9D111_DRIVER_VAR_SEQUENCER_SHARED_PARAMS_FLASH_TYPE           6           /**< Name = . */
#define MT9D111_DRIVER_VAR_SEQUENCER_SHARED_PARAMS_AE_CONT_BUFF         7           /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_SHARED_PARAMS_AE_CONT_STEP         8           /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_SHARED_PARAMS_AE_FAST_BUFF         9           /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_SHARED_PARAMS_AE_FAST_STEP         10          /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_SHARED_PARAMS_AWB_CONT_BUFF        11          /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_SHARED_PARAMS_AWB_CONT_STEP        12          /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_SHARED_PARAMS_AWB_FAST_BUF         13          /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_SHARED_PARAMS_AWB_FAST_STEP        14          /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_SHARED_PARAMS_TOTAL_MAX_FRAMES     18          /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_SHARED_PARAMS_FLASH_TH             19          /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_SHARED_PARAMS_OUTDOOR_TH           20          /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_SHARED_PARAMS_LL_MODE              21          /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_SHARED_PARAMS_LL_VIRT_GAIN_1       22          /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_SHARED_PARAMS_LL_VIRT_GAIN_2       23          /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_SHARED_PARAMS_LL_SAT_1             24          /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_SHARED_PARAMS_LL_SAT_2             25          /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_SHARED_PARAMS_LL_INTERP_THRESH_1   26          /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_SHARED_PARAMS_LL_INTERP_THRESH_2   27          /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_SHARED_PARAMS_LL_AP_CORR_1         28          /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_SHARED_PARAMS_LL_AP_CORR_2         29          /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_SHARED_PARAMS_LL_AP_THRESH_1       30          /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_SHARED_PARAMS_LL_AP_THRESH_2       31          /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_CAPTURE_PARAMS_MODE                32          /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_CAPTURE_PARAMS_NUM_FRAMES          33          /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_PREVIEW_PARAMS_0_AE                34          /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_PREVIEW_PARAMS_0_FD                35          /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_PREVIEW_PARAMS_0_AWB               36          /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_PREVIEW_PARAMS_0_AF                37          /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_PREVIEW_PARAMS_0_HG                38          /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_PREVIEW_PARAMS_0_FLASH             39          /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_PREVIEW_PARAMS_0_SKIP_FRAME        40          /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_PREVIEW_PARAMS_1_AE                41          /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_PREVIEW_PARAMS_1_FD                42          /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_PREVIEW_PARAMS_1_AWB               43          /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_PREVIEW_PARAMS_1_AF                44          /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_PREVIEW_PARAMS_1_HG                45          /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_PREVIEW_PARAMS_1_FLASH             46          /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_PREVIEW_PARAMS_1_SKIP_FRAME        47          /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_PREVIEW_PARAMS_2_AE                48          /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_PREVIEW_PARAMS_2_FD                49          /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_PREVIEW_PARAMS_2_AWB               50          /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_PREVIEW_PARAMS_2_AF                51          /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_PREVIEW_PARAMS_2_HG                52          /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_PREVIEW_PARAMS_2_FLASH             53          /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_PREVIEW_PARAMS_2_SKIP_FRAME        54          /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_PREVIEW_PARAMS_3_AE                55          /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_PREVIEW_PARAMS_3_FD                56          /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_PREVIEW_PARAMS_3_AWB               57          /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_PREVIEW_PARAMS_3_AF                58          /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_PREVIEW_PARAMS_3_HG                59          /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_PREVIEW_PARAMS_3_FLASH             60          /**< . */
#define MT9D111_DRIVER_VAR_SEQUENCER_PREVIEW_PARAMS_3_SKIP_FRAME        61          /**< . */

// Auto Exposure (Table 12: Driver Variables-Auto Exposure Driver (ID = 2))
#define MT9D111_DRIVER_VAR_AUTO_EXPOSURE_WINDOW_POS                     2           /**< . */
#define MT9D111_DRIVER_VAR_AUTO_EXPOSURE_WINDOW_SIZE                    3           /**< . */
#define MT9D111_DRIVER_VAR_AUTO_EXPOSURE_WAKE_UP_LINE                   4           /**< . */
#define MT9D111_DRIVER_VAR_AUTO_EXPOSURE_TARGET                         6           /**< . */
#define MT9D111_DRIVER_VAR_AUTO_EXPOSURE_GATE                           7           /**< . */
#define MT9D111_DRIVER_VAR_AUTO_EXPOSURE_SKIP_FRAMES                    8           /**< . */
#define MT9D111_DRIVER_VAR_AUTO_EXPOSURE_JUMP_DIVISOR                   9           /**< . */
#define MT9D111_DRIVER_VAR_AUTO_EXPOSURE_LUMA_BUFFER_SPEED              10          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_EXPOSURE_MAX_R12                        11          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_EXPOSURE_MIN_INDEX                      13          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_EXPOSURE_MAX_INDEX                      14          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_EXPOSURE_MIN_VIRT_GAIN                  15          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_EXPOSURE_MAX_VIRT_GAIN                  16          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_EXPOSURE_MAX_ADC_HI                     17          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_EXPOSURE_MIN_ADC_HI                     18          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_EXPOSURE_MIN_ADC_LO                     19          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_EXPOSURE_MAX_D_GAIN_AE1                 20          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_EXPOSURE_MAX_D_GAIN_AE2                 22          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_EXPOSURE_INDEX_TH23                     23          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_EXPOSURE_MAX_GAIN_23                    24          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_EXPOSURE_WEIGHTS                        25          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_EXPOSURE_STATUS                         26          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_EXPOSURE_CURRENT_Y                      27          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_EXPOSURE_R12                            28          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_EXPOSURE_INDEX                          30          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_EXPOSURE_VIRT_GAIN                      31          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_EXPOSURE_ADC_HI                         32          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_EXPOSURE_ADC_LO                         33          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_EXPOSURE_D_GAIN_AE1                     34          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_EXPOSURE_D_GAIN_AE2                     36          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_EXPOSURE_R9                             37          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_EXPOSURE_R65                            39          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_EXPOSURE_ROW_TIME                       40          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_EXPOSURE_GAIN_R12                       42          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_EXPOSURE_SKIP_FRAMES_CNT                43          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_EXPOSURE_BUFFERED_LUMA                  44          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_EXPOSURE_DIR_AE_PREV                    46          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_EXPOSURE_R9_STEP                        47          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_EXPOSURE_MAX_ADC_LO                     50          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_EXPOSURE_PHYS_GAIN_R                    51          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_EXPOSURE_PHYS_GAIN_G                    53          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_EXPOSURE_PHYS_GAIN_B                    55          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_EXPOSURE_MM_EV_ZONE_1                   82          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_EXPOSURE_MM_EV_ZONE_2                   83          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_EXPOSURE_MM_EV_ZONE_3                   84          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_EXPOSURE_MM_EV_ZONE_4                   85          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_EXPOSURE_MM_SHIFT_EV                    86          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_EXPOSURE_NUM_OE                         87          /**< . */

// Auto White Balance (Table 13: Driver Variables-Auto White Balance (ID = 3))
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_WINDOW_POS                2           /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_WINDOW_SIZE               3           /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_WAKEUP_LINE               4           /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_CCM_L_0                   6           /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_CCM_L_1                   8           /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_CCM_L_2                   10          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_CCM_L_3                   12          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_CCM_L_4                   14          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_CCM_L_5                   16          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_CCM_L_6                   18          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_CCM_L_7                   20          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_CCM_L_8                   22          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_CCM_L_9                   24          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_CCM_L_10                  26          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_CCM_RL_0                  28          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_CCM_RL_1                  30          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_CCM_RL_2                  32          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_CCM_RL_3                  34          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_CCM_RL_4                  36          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_CCM_RL_5                  38          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_CCM_RL_6                  40          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_CCM_RL_7                  42          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_CCM_RL_8                  44          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_CCM_RL_9                  46          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_CCM_RL_10                 48          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_CCM_0                     50          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_CCM_1                     52          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_CCM_2                     54          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_CCM_3                     56          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_CCM_4                     58          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_CCM_5                     60          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_CCM_6                     62          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_CCM_7                     64          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_CCM_8                     66          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_CCM_9                     68          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_CCM_10                    70          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_GAIN_BUFFER_SPEED         72          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_JUMP_DIVISOR              73          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_GAIN_MIN                  74          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_GAIN_MAX                  75          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_GAIN_R                    76          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_GAIN_G                    77          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_GAIN_B                    78          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_CCM_POSITION_MIN          79          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_CCM_POSITION_MAX          80          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_CCM_POSITION              81          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_SATURATION                82          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_MODE                      83          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_GAIN_R_BUF                84          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_GAIN_B_BUF                86          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_SUM_R                     88          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_SUM_Y                     89          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_SUM_B                     90          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_STEADY_B_GAIN_OUT_MIN     91          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_STEADY_B_GAIN_OUT_MAX     92          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_STEADY_B_GAIN_IN_MIN      93          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_STEADY_B_GAIN_IN_MAX      94          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_CNT_PX_ITH                95          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_TG_MIN_0                  97          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_TG_MAX_0                  98          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_X0                        99          /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_K_R_L                     100         /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_K_G_L                     101         /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_K_B_L                     102         /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_K_R_R                     103         /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_K_G_R                     104         /**< . */
#define MT9D111_DRIVER_VAR_AUTO_WHITE_BALANCE_K_B_R                     105         /**< . */

// Flicker Detection (Table 14: Driver Variables-Flicker Detection Driver (ID = 4))
#define MT9D111_DRIVER_VAR_FLICKER_DETECTION_WINDOW_POS_H               2           /**< . */
#define MT9D111_DRIVER_VAR_FLICKER_DETECTION_WINDOW_HEIGHT              3           /**< . */
#define MT9D111_DRIVER_VAR_FLICKER_DETECTION_MODE                       4           /**< . */
#define MT9D111_DRIVER_VAR_FLICKER_DETECTION_WAKEUP_LINE                5           /**< . */
#define MT9D111_DRIVER_VAR_FLICKER_DETECTION_SMOOTH_CNT                 7           /**< . */
#define MT9D111_DRIVER_VAR_FLICKER_DETECTION_SEARCH_F1_50               8           /**< . */
#define MT9D111_DRIVER_VAR_FLICKER_DETECTION_SEARCH_F2_50               9           /**< . */
#define MT9D111_DRIVER_VAR_FLICKER_DETECTION_SEARCH_F1_60               10          /**< . */
#define MT9D111_DRIVER_VAR_FLICKER_DETECTION_SEARCH_F2_60               11          /**< . */
#define MT9D111_DRIVER_VAR_FLICKER_DETECTION_SKIP_FRAME                 12          /**< . */
#define MT9D111_DRIVER_VAR_FLICKER_DETECTION_STAT_MIN                   13          /**< . */
#define MT9D111_DRIVER_VAR_FLICKER_DETECTION_STAT_MAX                   14          /**< . */
#define MT9D111_DRIVER_VAR_FLICKER_DETECTION_STAT                       15          /**< . */
#define MT9D111_DRIVER_VAR_FLICKER_DETECTION_MIN_AMPLITUDE              16          /**< . */
#define MT9D111_DRIVER_VAR_FLICKER_DETECTION_R9_STEP_60                 17          /**< . */
#define MT9D111_DRIVER_VAR_FLICKER_DETECTION_R9_STEP_50                 19          /**< . */
#define MT9D111_DRIVER_VAR_FLICKER_DETECTION_BUFFER                     21          /**< . */

// Auto Focus

// Auto Focus Mechanics

// Mode (Table 17: Driver Variables-Mode/Context Driver (ID = 7))
#define MT9D111_DRIVER_VAR_MODE_VMT_POINTER                             0           /**< . */
#define MT9D111_DRIVER_VAR_MODE_CONTEXT                                 2           /**< . */
#define MT9D111_DRIVER_VAR_MODE_OUTPUT_WIDTH_A                          3           /**< . */
#define MT9D111_DRIVER_VAR_MODE_OUTPUT_HEIGHT_A                         5           /**< . */
#define MT9D111_DRIVER_VAR_MODE_OUTPUT_WIDTH_B                          7           /**< . */
#define MT9D111_DRIVER_VAR_MODE_OUTPUT_HEIGHT_B                         9           /**< . */
#define MT9D111_DRIVER_VAR_MODE_MODE_CONFIG                             11          /**< . */
#define MT9D111_DRIVER_VAR_MODE_PLL_LOCL_DELAY                          13          /**< . */
#define MT9D111_DRIVER_VAR_MODE_S_ROW_START_A                           15          /**< . */
#define MT9D111_DRIVER_VAR_MODE_S_COL_START_A                           17          /**< . */
#define MT9D111_DRIVER_VAR_MODE_S_ROW_HEIGHT_A                          19          /**< . */
#define MT9D111_DRIVER_VAR_MODE_S_COL_WIDTH_A                           21          /**< . */
#define MT9D111_DRIVER_VAR_MODE_S_EXT_DELAY_A                           23          /**< . */
#define MT9D111_DRIVER_VAR_MODE_S_ROW_SPEED_A                           25          /**< . */
#define MT9D111_DRIVER_VAR_MODE_S_ROW_START_B                           27          /**< . */
#define MT9D111_DRIVER_VAR_MODE_S_COL_START_B                           29          /**< . */
#define MT9D111_DRIVER_VAR_MODE_S_ROW_HEIGHT_B                          31          /**< . */
#define MT9D111_DRIVER_VAR_MODE_S_COL_WIDTH_B                           33          /**< . */
#define MT9D111_DRIVER_VAR_MODE_S_EXT_DELAY_B                           35          /**< . */
#define MT9D111_DRIVER_VAR_MODE_S_ROW_SPEED_B                           37          /**< . */
#define MT9D111_DRIVER_VAR_MODE_CROP_X0_A                               39          /**< . */
#define MT9D111_DRIVER_VAR_MODE_CROP_X1_A                               41          /**< . */
#define MT9D111_DRIVER_VAR_MODE_CROP_Y0_A                               43          /**< . */
#define MT9D111_DRIVER_VAR_MODE_CROP_Y1_A                               45          /**< . */
#define MT9D111_DRIVER_VAR_MODE_DEC_CTRL_A                              47          /**< . */
#define MT9D111_DRIVER_VAR_MODE_CROP_X0_B                               53          /**< . */
#define MT9D111_DRIVER_VAR_MODE_CROP_X1_B                               55          /**< . */
#define MT9D111_DRIVER_VAR_MODE_CROP_Y0_B                               57          /**< . */
#define MT9D111_DRIVER_VAR_MODE_CROP_Y1_B                               59          /**< . */
#define MT9D111_DRIVER_VAR_MODE_DEC_CTRL_B                              61          /**< . */
#define MT9D111_DRIVER_VAR_MODE_GAM_CONT_A                              67          /**< . */
#define MT9D111_DRIVER_VAR_MODE_GAM_CONT_B                              68          /**< . */
#define MT9D111_DRIVER_VAR_MODE_GAMMA_TABLE_A_0                         69          /**< . */
#define MT9D111_DRIVER_VAR_MODE_GAMMA_TABLE_A_1                         70          /**< . */
#define MT9D111_DRIVER_VAR_MODE_GAMMA_TABLE_A_2                         71          /**< . */
#define MT9D111_DRIVER_VAR_MODE_GAMMA_TABLE_A_3                         72          /**< . */
#define MT9D111_DRIVER_VAR_MODE_GAMMA_TABLE_A_4                         73          /**< . */
#define MT9D111_DRIVER_VAR_MODE_GAMMA_TABLE_A_5                         74          /**< . */
#define MT9D111_DRIVER_VAR_MODE_GAMMA_TABLE_A_6                         75          /**< . */
#define MT9D111_DRIVER_VAR_MODE_GAMMA_TABLE_A_7                         76          /**< . */
#define MT9D111_DRIVER_VAR_MODE_GAMMA_TABLE_A_8                         77          /**< . */
#define MT9D111_DRIVER_VAR_MODE_GAMMA_TABLE_A_9                         78          /**< . */
#define MT9D111_DRIVER_VAR_MODE_GAMMA_TABLE_A_10                        79          /**< . */
#define MT9D111_DRIVER_VAR_MODE_GAMMA_TABLE_A_11                        80          /**< . */
#define MT9D111_DRIVER_VAR_MODE_GAMMA_TABLE_A_12                        81          /**< . */
#define MT9D111_DRIVER_VAR_MODE_GAMMA_TABLE_A_13                        82          /**< . */
#define MT9D111_DRIVER_VAR_MODE_GAMMA_TABLE_A_14                        83          /**< . */
#define MT9D111_DRIVER_VAR_MODE_GAMMA_TABLE_A_15                        84          /**< . */
#define MT9D111_DRIVER_VAR_MODE_GAMMA_TABLE_A_16                        85          /**< . */
#define MT9D111_DRIVER_VAR_MODE_GAMMA_TABLE_A_17                        86          /**< . */
#define MT9D111_DRIVER_VAR_MODE_GAMMA_TABLE_A_18                        87          /**< . */
#define MT9D111_DRIVER_VAR_MODE_GAMMA_TABLE_B_0                         88          /**< . */
#define MT9D111_DRIVER_VAR_MODE_GAMMA_TABLE_B_1                         89          /**< . */
#define MT9D111_DRIVER_VAR_MODE_GAMMA_TABLE_B_2                         90          /**< . */
#define MT9D111_DRIVER_VAR_MODE_GAMMA_TABLE_B_3                         91          /**< . */
#define MT9D111_DRIVER_VAR_MODE_GAMMA_TABLE_B_4                         92          /**< . */
#define MT9D111_DRIVER_VAR_MODE_GAMMA_TABLE_B_5                         93          /**< . */
#define MT9D111_DRIVER_VAR_MODE_GAMMA_TABLE_B_6                         94          /**< . */
#define MT9D111_DRIVER_VAR_MODE_GAMMA_TABLE_B_7                         95          /**< . */
#define MT9D111_DRIVER_VAR_MODE_GAMMA_TABLE_B_8                         96          /**< . */
#define MT9D111_DRIVER_VAR_MODE_GAMMA_TABLE_B_9                         97          /**< . */
#define MT9D111_DRIVER_VAR_MODE_GAMMA_TABLE_B_10                        98          /**< . */
#define MT9D111_DRIVER_VAR_MODE_GAMMA_TABLE_B_11                        99          /**< . */
#define MT9D111_DRIVER_VAR_MODE_GAMMA_TABLE_B_12                        100         /**< . */
#define MT9D111_DRIVER_VAR_MODE_GAMMA_TABLE_B_13                        101         /**< . */
#define MT9D111_DRIVER_VAR_MODE_GAMMA_TABLE_B_14                        102         /**< . */
#define MT9D111_DRIVER_VAR_MODE_GAMMA_TABLE_B_15                        103         /**< . */
#define MT9D111_DRIVER_VAR_MODE_GAMMA_TABLE_B_16                        104         /**< . */
#define MT9D111_DRIVER_VAR_MODE_GAMMA_TABLE_B_17                        105         /**< . */
#define MT9D111_DRIVER_VAR_MODE_GAMMA_TABLE_B_18                        106         /**< . */
#define MT9D111_DRIVER_VAR_MODE_FIFO_CONFIG0_A                          107         /**< . */
#define MT9D111_DRIVER_VAR_MODE_FIFO_CONFIG1_A                          109         /**< . */
#define MT9D111_DRIVER_VAR_MODE_FIFO_CONFIG2_A                          111         /**< . */
#define MT9D111_DRIVER_VAR_MODE_FIFO_LEN_TIMING_A                       112         /**< . */
#define MT9D111_DRIVER_VAR_MODE_FIFO_CONFIG0_B                          114         /**< . */
#define MT9D111_DRIVER_VAR_MODE_FIFO_CONFIG1_B                          116         /**< . */
#define MT9D111_DRIVER_VAR_MODE_FIFO_CONFIG2_B                          118         /**< . */
#define MT9D111_DRIVER_VAR_MODE_FIFO_LEN_TIMING_B                       119         /**< . */
#define MT9D111_DRIVER_VAR_MODE_SPOOF_WIDTH_B                           121         /**< . */
#define MT9D111_DRIVER_VAR_MODE_SPOOF_HEIGHT_B                          123         /**< . */
#define MT9D111_DRIVER_VAR_MODE_OUT_FORMAT_A                            125         /**< . */
#define MT9D111_DRIVER_VAR_MODE_OUT_FORMAT_B                            126         /**< . */
#define MT9D111_DRIVER_VAR_MODE_SPEC_EFFECTS_A                          127         /**< . */
#define MT9D111_DRIVER_VAR_MODE_SPEC_EFFECTS_B                          129         /**< . */
#define MT9D111_DRIVER_VAR_MODE_Y_RGB_OFFSET_A                          131         /**< . */
#define MT9D111_DRIVER_VAR_MODE_Y_RGB_OFFSET_B                          132         /**< . */

// JPEG


// Histogram (Table 19: Driver Variables-Histogram Driver (ID = 11))
#define MT9D111_DRIVER_VAR_HISTOGRAM_D_LEVEL_BUFFER_SPEED               2           /**< . */
#define MT9D111_DRIVER_VAR_HISTOGRAM_SCALE_G_FACTOR                     3           /**< . */
#define MT9D111_DRIVER_VAR_HISTOGRAM_MAX_D_LEVEL                        4           /**< . */
#define MT9D111_DRIVER_VAR_HISTOGRAM_PERCENT                            5           /**< . */
#define MT9D111_DRIVER_VAR_HISTOGRAM_LOWER_LIMIT_1                      6           /**< . */
#define MT9D111_DRIVER_VAR_HISTOGRAM_BIN_SIZE_1                         7           /**< . */
#define MT9D111_DRIVER_VAR_HISTOGRAM_LOWER_LIMIT_2                      8           /**< . */
#define MT9D111_DRIVER_VAR_HISTOGRAM_BIN_SIZE_2                         9           /**< . */
#define MT9D111_DRIVER_VAR_HISTOGRAM_D_LEVEL                            10          /**< . */
#define MT9D111_DRIVER_VAR_HISTOGRAM_D_LEVEL_BUF                        11          /**< . */
#define MT9D111_DRIVER_VAR_HISTOGRAM_FACTOR_HI                          13          /**< . */
#define MT9D111_DRIVER_VAR_HISTOGRAM_PERCENT_HI                         14          /**< . */

/**
 * \brief Monitor driver variables.
 */
struct Monitor
{
    uint16_t vmt;                       /**< Reserved. */
    char cmd;                           /**< Monitor command. */
    uint16_t arg1;                      /**< First argument for monitor command. */
    uint16_t arg2;                      /**< Second argument for minitor command. */
    char msgCount;                      /**< Number of posted messages. */
    uint32_t msg;                       /**< First message (unused). */
    uint8_t ver;                        /**< Firmware version. */
};

/**
 * \brief Shared (between capture and preview modes) parameters.
 */
struct SharedParams
{
    uint8_t flashType;                  /**< Type of flash to be used. */
    uint8_t aeContBuff;                 /**< . */
    uint8_t aeContStep;                 /**< . */
    uint8_t aeFastBuff;                 /**< . */
    uint8_t aeFastStep;                 /**< . */
    uint8_t awbContBuff;                /**< . */
    uint8_t awbContStep;                /**< . */
    uint8_t awbFastBuff;                /**< . */
    uint8_t awbFastStep;                /**< . */
    uint8_t totalMaxFrames;             /**< . */
    uint8_t flashTH;                    /**< . */
    uint8_t outdoorTH;                  /**< . */
    uint8_t LLmode;                     /**< . */
    uint8_t LLvirtGain1;                /**< . */
    uint8_t LLvirtGain2;                /**< . */
    uint8_t LLSat1;                     /**< . */
    uint8_t LLSat2;                     /**< . */
    uint8_t LLInterpThresh1;            /**< . */
    uint8_t LLInterpThresh2;            /**< . */
    uint8_t LLApCorr1;                  /**< . */
    uint8_t LLApCorr2;                  /**< . */
    uint8_t LLApThresh1;                /**< . */
    uint8_t LLApThresh2;                /**< . */
};

/**
 * \brief Capture mode parameters.
 */
struct CaptureParams
{
    uint8_t mode;                       /**< Capture mode. */
    uint8_t numFrames;                  /**< Number of frames captured in still capture mode. */
};

/**
 * \brief Preview mode parameters.
 */
struct PreviewParams
{
    uint8_t ae;                         /**< Auto exposure configuration in PreviewEnter state. */
    uint8_t fd;                         /**< . */
    uint8_t awb;                        /**< . */
    uint8_t af;                         /**< . */
    uint8_t hg;                         /**< . */
    uint8_t flash;                      /**< . */
    uint8_t skipFrame;                  /**< . */
};

/**
 * \brief .
 */
struct Sequencer
{
    uint16_t vmt;                       /**< Reserved. */
    uint8_t mode;                       /**< . */
    uint8_t cmd;                        /**< Command or program to execute. */
    uint8_t state;                      /**< Current state of sequencer. */
    uint8_t stepMode;                   /**< Step-by-step mode for sequencer. */
    SharedParams sharedParams;          /**< . */
    CaptureParams captureParams;        /**< . */
    PreviewParams previewParams[4];     /**< . */
};

/**
 * \brief Auto Exposure driver variables.
 */
struct AutoExposure
{
    uint16_t vmt;                       /**< Reserved. */
    uint8_t windowPos;                  /**< Position of upper left corner of first AE window. */
    uint8_t windowSize;                 /**< . */
    uint16_t wakeUpLine;                /**< . */
    uint8_t Target;                     /**< . */
    uint8_t Gate;                       /**< . */
    uint8_t SkipFrames;                 /**< . */
    uint8_t JumpDivisor;                /**< . */
    uint8_t lumaBufferSpeed;            /**< . */
    uint16_t masR12;                    /**< . */
    uint8_t minIndex;                   /**< . */
    uint8_t maxIndex;                   /**< . */
    uint8_t minVirtGain;                /**< . */
    uint8_t maxVirtGain;                /**< . */
    uint8_t maxADChi;                   /**< . */
    uint8_t minADClo;                   /**< . */
    uint8_t maxDGainAE1;                /**< . */
    uint8_t maxDGainAE2;                /**< . */
    uint8_t IndexTH23;                  /**< . */
    uint8_t maxGain23;                  /**< . */
    uint8_t weights;                    /**< . */
    uint8_t status;                     /**< . */
    uint8_t CurrentY;                   /**< . */
    uint16_t R12;                       /**< . */
    uint8_t Index;                      /**< . */
    uint8_t VirtGain;                   /**< . */
    uint8_t ADC_hi;                     /**< . */
    uint8_t ADC_lo;                     /**< . */
    uint8_t DGainAE1;                   /**< . */
    uint8_t DGainAE2;                   /**< . */
    uint8_t R9;                         /**< . */
    uint8_t R65;                        /**< . */
    uint8_t rowTime;                    /**< . */
    uint8_t gainR12;                    /**< . */
    uint8_t SkipFrames_cnt;             /**< . */
    uint8_t BufferedLuma;               /**< . */
    uint8_t dirAE_prev;                 /**< . */
    uint16_t R9_step;                   /**< . */
    uint8_t maxADClo;                   /**< . */
    uint16_t physGainR;                 /**< . */
    uint16_t physGainG;                 /**< . */
    uint16_t physGainB;                 /**< . */
    uint8_t mmEVZone1;                  /**< . */
    uint8_t mmEVZone2;                  /**< . */
    uint8_t mmEVZone3;                  /**< . */
    uint8_t mmEVZone4;                  /**< . */
    uint8_t mmShiftEV;                  /**< . */
    uint8_t numOE;                      /**< . */
};

/**
 * \brief Auto White Balance driver variables.
 */
struct AutoWhiteBalance
{
    uint16_t vmt;                       /**< Reserved. */
    uint8_t windowPos;                  /**< . */
    uint8_t windowSize;                 /**< . */
    uint16_t wakeUpLine;                /**< . */
    int16_t ccmL[11];                   /**< . */
    int16_t ccmRL[11];                  /**< . */
    int16_t ccm[11];                    /**< . */
    uint8_t GainBufferSpeed;            /**< . */
    uint8_t JumpDivisor;                /**< . */
    uint8_t GainMin;                    /**< . */
    uint8_t GainMax;                    /**< . */
    uint8_t GainR;                      /**< . */
    uint8_t GainG;                      /**< . */
    uint8_t GainB;                      /**< . */
    uint8_t CCMpositionMin;             /**< . */
    uint8_t CCMpositionMax;             /**< . */
    uint8_t CCMposition;                /**< . */
    uint8_t saturation;                 /**< . */
    uint8_t mode;                       /**< . */
    uint16_t GainR_buf;                 /**< . */
    uint16_t GainB_buf;                 /**< . */
    uint8_t sumR;                       /**< . */
    uint8_t sumY;                       /**< . */
    uint8_t sumB;                       /**< . */
    uint8_t steadyBGainOutMin;          /**< . */
    uint8_t steadyBGainOutMax;          /**< . */
    uint8_t steadyBGainInMin;           /**< . */
    uint8_t steadyBGainInMax;           /**< . */
    uint8_t cntPxITH;                   /**< . */
    uint8_t TG_min0;                    /**< . */
    uint8_t TG_max0;                    /**< . */
    uint8_t X0;                         /**< . */
    uint8_t kR_L;                       /**< . */
    uint8_t kG_L;                       /**< . */
    uint8_t kB_L;                       /**< . */
    uint8_t kR_R;                       /**< . */
    uint8_t kG_R;                       /**< . */
    uint8_t kB_R;                       /**< . */
};

/**
 * \brief Flicker Detection driver variables.
 */
struct FlickerDetection
{
    uint16_t vmt;                       /**< Reserved. */
    uint8_t windowPosH;                 /**< . */
    uint8_t windowHieght;               /**< . */
    uint8_t mode;                       /**< . */
};

/**
 * \brief Auto Focus driver variables.
 */
struct AutoFocus
{
    uint16_t Vmt;                       /**< Reserved. */
    uint8_t windowPos;                  /**< . */
    uint8_t windowSize;                 /**< . */
};

/**
 * \brief .
 */
struct AutoFocusMechanics
{
    uint16_t vmt;                       /**< Pointer to the driver’s virtual method table (VMT). */
};

/**
 * \brief Mode/Context driver variables.
 */
struct Mode
{
    uint16_t VMT_pointer;               /**< . */
    uint8_t context;                    /**< . */
    uint16_t output_width_A;            /**< . */
    uint16_t output_height_A;           /**< . */
    uint16_t output_width_B;            /**< . */
    uint16_t output_height_B;           /**< . */
    uint16_t mode_config;               /**< . */
    uint16_t PLL_lock_delay;            /**< . */
    uint16_t s_row_start_A;             /**< . */
    uint16_t s_col_start_A;             /**< . */
    uint16_t s_row_height_A;            /**< . */
    uint16_t s_col_width_A;             /**< . */
    uint16_t s_ext_delay_A;             /**< . */
    uint16_t s_row_speed_A;             /**< . */
    uint16_t s_row_start_B;             /**< . */
    uint16_t s_col_start_B;             /**< . */
    uint16_t s_row_height_B;            /**< . */
    uint16_t s_col_width_B;             /**< . */
    uint16_t s_ext_delay_B;             /**< . */
    uint16_t s_row_speed_B;             /**< . */
    uint16_t crop_X0_A;                 /**< . */
    uint16_t crop_X1_A;                 /**< . */
    uint16_t crop_Y0_A;                 /**< . */
    uint16_t crop_Y1_A;                 /**< . */
    uint16_t dec_ctrl_A;                /**< . */
    uint16_t crop_X0_B;                 /**< . */
    uint16_t crop_X1_B;                 /**< . */
    uint16_t crop_Y0_B;                 /**< . */
    uint16_t crop_Y1_B;                 /**< . */
    uint16_t dec_ctrl_B;                /**< . */
    uint8_t gam_cont_A;                 /**< . */
    uint8_t gam_cont_B;                 /**< . */
    uint8_t gamma_table_A_0;            /**< . */
    uint8_t gamma_table_A_1;            /**< . */
    uint8_t gamma_table_A_2;            /**< . */
    uint8_t gamma_table_A_3;            /**< . */
    uint8_t gamma_table_A_4;            /**< . */
    uint8_t gamma_table_A_5;            /**< . */
    uint8_t gamma_table_A_6;            /**< . */
    uint8_t gamma_table_A_7;            /**< . */
    uint8_t gamma_table_A_8;            /**< . */
    uint8_t gamma_table_A_9;            /**< . */
    uint8_t gamma_table_A_10;           /**< . */
    uint8_t gamma_table_A_11;           /**< . */
    uint8_t gamma_table_A_12;           /**< . */
    uint8_t gamma_table_A_13;           /**< . */
    uint8_t gamma_table_A_14;           /**< . */
    uint8_t gamma_table_A_15;           /**< . */
    uint8_t gamma_table_A_16;           /**< . */
    uint8_t gamma_table_A_17;           /**< . */
    uint8_t gamma_table_A_18;           /**< . */
    uint8_t gamma_table_B_0;            /**< . */
    uint8_t gamma_table_B_1;            /**< . */
    uint8_t gamma_table_B_2;            /**< . */
    uint8_t gamma_table_B_3;            /**< . */
    uint8_t gamma_table_B_4;            /**< . */
    uint8_t gamma_table_B_5;            /**< . */
    uint8_t gamma_table_B_6;            /**< . */
    uint8_t gamma_table_B_7;            /**< . */
    uint8_t gamma_table_B_8;            /**< . */
    uint8_t gamma_table_B_9;            /**< . */
    uint8_t gamma_table_B_10;           /**< . */
    uint8_t gamma_table_B_11;           /**< . */
    uint8_t gamma_table_B_12;           /**< . */
    uint8_t gamma_table_B_13;           /**< . */
    uint8_t gamma_table_B_14;           /**< . */
    uint8_t gamma_table_B_15;           /**< . */
    uint8_t gamma_table_B_16;           /**< . */
    uint8_t gamma_table_B_17;           /**< . */
    uint8_t gamma_table_B_18;           /**< . */
    uint16_t FIFO_config0_A;            /**< . */
    uint16_t FIFO_config1_A;            /**< . */
    uint8_t FIFO_config2_A;             /**< . */
    uint16_t FIFO_len_timing_A;         /**< . */
    uint16_t FIFO_config0_B;            /**< . */
    uint16_t FIFO_config1_B;            /**< . */
    uint8_t FIFO_config2_B;             /**< . */
    uint16_t FIFO_len_timing_B;         /**< . */
    uint16_t spoof_width_B;             /**< . */
    uint16_t spoof_height_B;            /**< . */
    uint8_t out_format_A;               /**< . */
    uint8_t out_format_B;               /**< . */
    uint16_t spec_effects_A;            /**< . */
    uint16_t spec_effects_B;            /**< . */
    uint8_t y_rgb_offset_A;             /**< . */
    uint8_t y_rgb_offset_B;             /**< . */
};

/**
 * \brief JPEG driver variables.
 */
struct JPEG
{
    uint16_t vmt;                       /**< . */
    uint16_t width;                     /**< . */
    uint16_t height;                    /**< . */
    uint8_t format;                     /**< . */
    uint8_t config;                     /**< . */
    uint16_t restartInt;                /**< . */
    uint8_t qscale1;                    /**< . */
    uint8_t qscale2;                    /**< . */
    uint8_t qscale3;                    /**< . */
    uint8_t timeoutFrames;              /**< . */
    uint8_t state;                      /**< . */
    uint8_t dataLengthMSB;              /**< . */
    uint16_t dataLengthLSBs;            /**< . */
};

/**
 * \brief Histogram driver variables.
 */
struct Histogram
{
    uint8_t DlevelBufferSpeed;          /**< Responde speed, 1-32; 32-maximum speed. */
    uint8_t scaleGFactor;               /**< . */
    uint8_t maxDLevel;                  /**< . */
    uint8_t percent;                    /**< . */
    uint8_t lowerLimit1;                /**< . */
    uint8_t binSize1;                   /**< . */
    uint8_t lowerLimit2;                /**< . */
    uint8_t binSize2;                   /**< . */
    uint8_t Dlevel;                     /**< . */
    uint16_t DLevel_buf;                /**< . */
    uint8_t factorHi;                   /**< . */
    uint8_t percentHi;                  /**< . */
};

/**
 * \brief Driver virables.
 */
struct Driver
{
    Monitor mon;                        /**< . */
    Sequencer seq;                      /**< . */
    AutoExposure ae;                    /**< . */
    AutoWhiteBalance awb;               /**< . */
    FlickerDetection fd;                /**< . */
    AutoFocus af;                       /**< . */
    AutoFocusMechanics afm;             /**< . */
    Mode mode;                          /**< . */
    JPEG jpeg;                          /**< . */
    Histogram hg;                       /**< . */
};

#endif // MT9D111_DRIVER_H_

//! \} End of driver group
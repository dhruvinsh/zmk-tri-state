# ZMK-SWAPPER

Currently not working, build fails with this error:

```
2024-02-03T23:50:51.3027191Z [16/337] Building C object CMakeFiles/app.dir/tmp/tmp.nHv8Kh3tgM/zmk-swapper/behaviors/behavior_tri_state.c.obj
2024-02-03T23:50:51.3029134Z FAILED: CMakeFiles/app.dir/tmp/tmp.nHv8Kh3tgM/zmk-swapper/behaviors/behavior_tri_state.c.obj
2024-02-03T23:50:51.3053828Z ccache /opt/zephyr-sdk-0.16.3/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc -DKERNEL -DNRF52840_XXAA -D_FORTIFY_SOURCE=2 -D__PROGRAM_START -D__ZEPHYR__=1 -I/tmp/tmp.nHv8Kh3tgM/zmk/app/include -I/tmp/tmp.nHv8Kh3tgM/zephyr/include -I/tmp/tmp.6FiFYZGtKh/zephyr/include/generated -I/tmp/tmp.nHv8Kh3tgM/zephyr/soc/arm/nordic_nrf/nrf52 -I/tmp/tmp.nHv8Kh3tgM/zephyr/soc/arm/nordic_nrf/common/. -I/tmp/tmp.nHv8Kh3tgM/zephyr/subsys/bluetooth/controller/ll_sw/nordic/hal/nrf5/nrfx_glue -I/tmp/tmp.nHv8Kh3tgM/zephyr/subsys/bluetooth -I/tmp/tmp.nHv8Kh3tgM/zephyr/subsys/usb/device -I/tmp/tmp.nHv8Kh3tgM/zephyr/subsys/settings/include -I/tmp/tmp.nHv8Kh3tgM/modules/hal/cmsis/CMSIS/Core/Include -I/tmp/tmp.nHv8Kh3tgM/modules/hal/nordic/nrfx -I/tmp/tmp.nHv8Kh3tgM/modules/hal/nordic/nrfx/drivers/include -I/tmp/tmp.nHv8Kh3tgM/modules/hal/nordic/nrfx/mdk -I/tmp/tmp.nHv8Kh3tgM/zephyr/modules/hal_nordic/nrfx/. -I/tmp/tmp.nHv8Kh3tgM/modules/crypto/tinycrypt/lib/include -I/tmp/tmp.nHv8Kh3tgM/zmk/app/module/include -I/tmp/tmp.nHv8Kh3tgM/zmk/app/module/drivers/sensor/battery/. -isystem /tmp/tmp.nHv8Kh3tgM/zephyr/lib/libc/minimal/include -isystem /opt/zephyr-sdk-0.16.3/arm-zephyr-eabi/bin/../lib/gcc/arm-zephyr-eabi/12.2.0/include -isystem /opt/zephyr-sdk-0.16.3/arm-zephyr-eabi/bin/../lib/gcc/arm-zephyr-eabi/12.2.0/include-fixed -fno-strict-aliasing -Os -imacros /tmp/tmp.6FiFYZGtKh/zephyr/include/generated/autoconf.h -ffreestanding -fno-common -g -gdwarf-4 -fdiagnostics-color=always -mcpu=cortex-m4 -mthumb -mabi=aapcs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mfp16-format=ieee --sysroot=/opt/zephyr-sdk-0.16.3/arm-zephyr-eabi/arm-zephyr-eabi -imacros /tmp/tmp.nHv8Kh3tgM/zephyr/include/zephyr/toolchain/zephyr_stdint.h -Wall -Wformat -Wformat-security -Wno-format-zero-length -Wno-main -Wno-pointer-sign -Wpointer-arith -Wexpansion-to-defined -Wno-unused-but-set-variable -Werror=implicit-int -fno-pic -fno-pie -fno-asynchronous-unwind-tables -fno-reorder-functions --param=min-pagesize=0 -fno-defer-pop -fmacro-prefix-map=/tmp/tmp.nHv8Kh3tgM/zmk/app=CMAKE_SOURCE_DIR -fmacro-prefix-map=/tmp/tmp.nHv8Kh3tgM/zephyr=ZEPHYR_BASE -fmacro-prefix-map=/tmp/tmp.nHv8Kh3tgM=WEST_TOPDIR -ffunction-sections -fdata-sections -std=c99 -nostdinc -Wfatal-errors -MD -MT CMakeFiles/app.dir/tmp/tmp.nHv8Kh3tgM/zmk-swapper/behaviors/behavior_tri_state.c.obj -MF CMakeFiles/app.dir/tmp/tmp.nHv8Kh3tgM/zmk-swapper/behaviors/behavior_tri_state.c.obj.d -o CMakeFiles/app.dir/tmp/tmp.nHv8Kh3tgM/zmk-swapper/behaviors/behavior_tri_state.c.obj -c /tmp/tmp.nHv8Kh3tgM/zmk-swapper/behaviors/behavior_tri_state.c
2024-02-03T23:50:51.3076405Z /tmp/tmp.nHv8Kh3tgM/zmk-swapper/behaviors/behavior_tri_state.c:301:13: warning: Macro is deprecated
2024-02-03T23:50:51.3077618Z   301 | DT_INST_FOREACH_STATUS_OKAY(TRI_STATE_INST)
2024-02-03T23:50:51.3078292Z       |             ^~~~~~~~~~~~~~~~~~~~~
2024-02-03T23:50:51.3079238Z In file included from /tmp/tmp.nHv8Kh3tgM/zephyr/include/zephyr/sys/util_macro.h:34,
2024-02-03T23:50:51.3080460Z                  from /tmp/tmp.nHv8Kh3tgM/zephyr/include/zephyr/sys/util.h:17,
2024-02-03T23:50:51.3081492Z                  from /tmp/tmp.nHv8Kh3tgM/zephyr/include/zephyr/devicetree.h:21,
2024-02-03T23:50:51.3082473Z                  from /tmp/tmp.nHv8Kh3tgM/zephyr/include/zephyr/device.h:38,
2024-02-03T23:50:51.3083683Z                  from /tmp/tmp.nHv8Kh3tgM/zmk-swapper/behaviors/behavior_tri_state.c:9:
2024-02-03T23:50:51.3086164Z /tmp/tmp.6FiFYZGtKh/zephyr/include/generated/devicetree_generated.h:6382:56: error: 'DT_N_S_behaviors_S_key_press_P_label' undeclared here (not in a function); did you mean 'DT_N_S_behaviors_S_key_press_PATH'?
2024-02-03T23:50:51.3088453Z  6382 | #define DT_N_S_behaviors_S_swapper_P_bindings_IDX_0_PH DT_N_S_behaviors_S_key_press
2024-02-03T23:50:51.3089463Z       |                                                        ^~~~~~~~~~~~~~~~~~~~~~~~~~~~
2024-02-03T23:50:51.3090932Z /tmp/tmp.nHv8Kh3tgM/zephyr/include/zephyr/sys/util_internal.h:72:26: note: in definition of macro '__DEBRACKET'
2024-02-03T23:50:51.3092188Z    72 | #define __DEBRACKET(...) __VA_ARGS__
2024-02-03T23:50:51.3092798Z       |                          ^~~~~~~~~~~
2024-02-03T23:50:51.3094226Z /tmp/tmp.nHv8Kh3tgM/zephyr/include/zephyr/sys/util_internal.h:64:9: note: in expansion of macro '__GET_ARG2_DEBRACKET'
2024-02-03T23:50:51.3095630Z    64 |         __GET_ARG2_DEBRACKET(one_or_two_args _if_code, _else_code)
2024-02-03T23:50:51.3096363Z       |         ^~~~~~~~~~~~~~~~~~~~
2024-02-03T23:50:51.3097669Z /tmp/tmp.nHv8Kh3tgM/zephyr/include/zephyr/sys/util_internal.h:59:9: note: in expansion of macro '__COND_CODE'
2024-02-03T23:50:51.3098973Z    59 |         __COND_CODE(_XXXX##_flag, _if_1_code, _else_code)
2024-02-03T23:50:51.3099617Z       |         ^~~~~~~~~~~
2024-02-03T23:50:51.3100822Z /tmp/tmp.nHv8Kh3tgM/zephyr/include/zephyr/sys/util_macro.h:157:9: note: in expansion of macro 'Z_COND_CODE_1'
2024-02-03T23:50:51.3102366Z   157 |         Z_COND_CODE_1(_flag, _if_1_code, _else_code)
2024-02-03T23:50:51.3103027Z       |         ^~~~~~~~~~~~~
2024-02-03T23:50:51.3104224Z /tmp/tmp.nHv8Kh3tgM/zephyr/include/zephyr/devicetree.h:3560:9: note: in expansion of macro 'COND_CODE_1'
2024-02-03T23:50:51.3105558Z  3560 |         COND_CODE_1(DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT),   \
2024-02-03T23:50:51.3106321Z       |         ^~~~~~~~~~~
2024-02-03T23:50:51.3107726Z /tmp/tmp.nHv8Kh3tgM/zephyr/include/zephyr/devicetree.h:614:32: note: in expansion of macro 'DT_CAT3'
2024-02-03T23:50:51.3109051Z   614 | #define DT_PROP(node_id, prop) DT_CAT3(node_id, _P_, prop)
2024-02-03T23:50:51.3109856Z       |                                ^~~~~~~
2024-02-03T23:50:51.3111206Z /tmp/tmp.nHv8Kh3tgM/zephyr/include/zephyr/devicetree.h:773:27: note: in expansion of macro 'DT_PROP'
2024-02-03T23:50:51.3112594Z   773 | #define DT_LABEL(node_id) DT_PROP(node_id, label) __DEPRECATED_MACRO
2024-02-03T23:50:51.3113441Z       |                           ^~~~~~~
2024-02-03T23:50:51.3114795Z /tmp/tmp.nHv8Kh3tgM/zmk-swapper/behaviors/behavior_tri_state.c:277:25: note: in expansion of macro 'DT_LABEL'
2024-02-03T23:50:51.3116358Z   277 |         .behavior_dev = DT_LABEL(DT_INST_PHANDLE_BY_IDX(node, bindings, idx)),                     \
2024-02-03T23:50:51.3117324Z       |                         ^~~~~~~~
2024-02-03T23:50:51.3118956Z /tmp/tmp.nHv8Kh3tgM/zephyr/include/zephyr/devicetree.h:3722:41: note: in expansion of macro 'DT_N_S_behaviors_S_swapper_P_bindings_IDX_0_PH'
2024-02-03T23:50:51.3120611Z  3722 | #define DT_CAT6(a1, a2, a3, a4, a5, a6) a1 ## a2 ## a3 ## a4 ## a5 ## a6
2024-02-03T23:50:51.3121791Z       |                                         ^~
2024-02-03T23:50:51.3123109Z /tmp/tmp.nHv8Kh3tgM/zephyr/include/zephyr/devicetree.h:1460:9: note: in expansion of macro 'DT_CAT6'
2024-02-03T23:50:51.3124369Z  1460 |         DT_CAT6(node_id, _P_, prop, _IDX_, idx, _PH)
2024-02-03T23:50:51.3125003Z       |         ^~~~~~~
2024-02-03T23:50:51.3126212Z /tmp/tmp.nHv8Kh3tgM/zephyr/include/zephyr/devicetree.h:3305:9: note: in expansion of macro 'DT_PHANDLE_BY_IDX'
2024-02-03T23:50:51.3127473Z  3305 |         DT_PHANDLE_BY_IDX(DT_DRV_INST(inst), prop, idx)
2024-02-03T23:50:51.3128126Z       |         ^~~~~~~~~~~~~~~~~
2024-02-03T23:50:51.3129539Z /tmp/tmp.nHv8Kh3tgM/zephyr/include/zephyr/sys/util_internal.h:105:36: note: in expansion of macro 'DT_N_INST_0_zmk_behavior_tri_state'
2024-02-03T23:50:51.3130954Z   105 | #define UTIL_PRIMITIVE_CAT(a, ...) a##__VA_ARGS__
2024-02-03T23:50:51.3131609Z       |                                    ^
2024-02-03T23:50:51.3132963Z /tmp/tmp.nHv8Kh3tgM/zephyr/include/zephyr/sys/util_internal.h:104:26: note: in expansion of macro 'UTIL_PRIMITIVE_CAT'
2024-02-03T23:50:51.3134334Z   104 | #define UTIL_CAT(a, ...) UTIL_PRIMITIVE_CAT(a, __VA_ARGS__)
2024-02-03T23:50:51.3135059Z       |                          ^~~~~~~~~~~~~~~~~~
2024-02-03T23:50:51.3136269Z /tmp/tmp.nHv8Kh3tgM/zephyr/include/zephyr/devicetree.h:326:31: note: in expansion of macro 'UTIL_CAT'
2024-02-03T23:50:51.3137561Z   326 | #define DT_INST(inst, compat) UTIL_CAT(DT_N_INST, DT_DASH(inst, compat))
2024-02-03T23:50:51.3138373Z       |                               ^~~~~~~~
2024-02-03T23:50:51.3139550Z /tmp/tmp.nHv8Kh3tgM/zephyr/include/zephyr/devicetree.h:2915:27: note: in expansion of macro 'DT_INST'
2024-02-03T23:50:51.3140748Z  2915 | #define DT_DRV_INST(inst) DT_INST(inst, DT_DRV_COMPAT)
2024-02-03T23:50:51.3141416Z       |                           ^~~~~~~
2024-02-03T23:50:51.3142596Z /tmp/tmp.nHv8Kh3tgM/zephyr/include/zephyr/devicetree.h:3305:27: note: in expansion of macro 'DT_DRV_INST'
2024-02-03T23:50:51.3143798Z  3305 |         DT_PHANDLE_BY_IDX(DT_DRV_INST(inst), prop, idx)
2024-02-03T23:50:51.3144451Z       |                           ^~~~~~~~~~~
2024-02-03T23:50:51.3145793Z /tmp/tmp.nHv8Kh3tgM/zmk-swapper/behaviors/behavior_tri_state.c:277:34: note: in expansion of macro 'DT_INST_PHANDLE_BY_IDX'
2024-02-03T23:50:51.3147799Z   277 |         .behavior_dev = DT_LABEL(DT_INST_PHANDLE_BY_IDX(node, bindings, idx)),                     \
2024-02-03T23:50:51.3148799Z       |                                  ^~~~~~~~~~~~~~~~~~~~~~
2024-02-03T23:50:51.3150255Z /tmp/tmp.nHv8Kh3tgM/zmk-swapper/behaviors/behavior_tri_state.c:294:27: note: in expansion of macro '_TRANSFORM_ENTRY'
2024-02-03T23:50:51.3151791Z   294 |         .start_behavior = _TRANSFORM_ENTRY(0, n),                                                  \
2024-02-03T23:50:51.3152667Z       |                           ^~~~~~~~~~~~~~~~
2024-02-03T23:50:51.3154100Z /tmp/tmp.6FiFYZGtKh/zephyr/include/generated/devicetree_generated.h:15530:57: note: in expansion of macro 'TRI_STATE_INST'
2024-02-03T23:50:51.3155498Z 15530 | #define DT_FOREACH_OKAY_INST_zmk_behavior_tri_state(fn) fn(0)
2024-02-03T23:50:51.3156249Z       |                                                         ^~
2024-02-03T23:50:51.3157818Z /tmp/tmp.nHv8Kh3tgM/zephyr/include/zephyr/sys/util_internal.h:105:36: note: in expansion of macro 'DT_FOREACH_OKAY_INST_zmk_behavior_tri_state'
2024-02-03T23:50:51.3159259Z   105 | #define UTIL_PRIMITIVE_CAT(a, ...) a##__VA_ARGS__
2024-02-03T23:50:51.3159889Z       |                                    ^
2024-02-03T23:50:51.3161264Z /tmp/tmp.nHv8Kh3tgM/zmk-swapper/behaviors/behavior_tri_state.c:301:1: note: in expansion of macro 'DT_INST_FOREACH_STATUS_OKAY'
2024-02-03T23:50:51.3162562Z   301 | DT_INST_FOREACH_STATUS_OKAY(TRI_STATE_INST)
2024-02-03T23:50:51.3163150Z       | ^~~~~~~~~~~~~~~~~~~~~~~~~~~
2024-02-03T23:50:51.3163797Z compilation terminated due to -Wfatal-errors.
2024-02-03T23:50:51.3233417Z [17/337] Building C object CMakeFiles/app.dir/src/events/sensor_event.c.obj
2024-02-03T23:50:51.3543106Z [18/337] Building C object CMakeFiles/app.dir/src/events/activity_state_changed.c.obj
2024-02-03T23:50:51.3911137Z [19/337] Building C object CMakeFiles/app.dir/src/events/position_state_changed.c.obj
2024-02-03T23:50:51.4735716Z [20/337] Building C object CMakeFiles/app.dir/src/event_manager.c.obj
2024-02-03T23:50:51.5246561Z [21/337] Building C object CMakeFiles/app.dir/src/ext_power_generic.c.obj
2024-02-03T23:50:51.5247612Z ninja: build stopped: subcommand failed.
2024-02-03T23:50:51.5294956Z FATAL ERROR: command exited with status 1: /usr/local/bin/cmake --build /tmp/tmp.6FiFYZGtKh
```

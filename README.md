# ZMK-TRI-STATE

Implement [Nick Conways's](https://github.com/nickconway) tri-state behavior for [ZMK](https://github.com/zmkfirmware/zmk).

This is proof of concept that shows that without maintaining fork, new behavior can
be implemented.

This implementation supports latest Zephyr 3.5 release with ZMK.

## How to use this module?

Under `config/west.yml` add `remotes` and `projects`, here is an example of
full file. Feel free to visit my config located [here](https://github.com/dhruvinsh/zmk-config/blob/0e4919ba45f08714bf1cc053c103ae1977bacd76/config/west.yml).

```yaml
manifest:
  remotes:
    - name: zmkfirmware
      url-base: https://github.com/zmkfirmware
    - name: dhruvinsh
      url-base: https://github.com/dhruvinsh
  projects:
    - name: zmk
      remote: zmkfirmware
      revision: main
      import: app/west.yml
    - name: zmk-tri-state
      remote: dhruvinsh
      revision: main
  self:
    path: config
```

**NOTE: [common use-case](https://zmk.dev/docs/development/new-behavior#defining-common-use-cases-for-the-behavior-dtsi-optional) hasn't be define for this behavior.**

To use,

```devicetree
#include <dt-bindings/zmk/keys.h>

/ {
  behaviors {
    swapper: swapper {
      compatible = "zmk,behavior-tri-state";
      #binding-cells = <0>;
      bindings = <&kp A>, <&kp B>, <&kt C>;
    };
  };
};
```

Once this define, `&swapper` can be use wherever it require. See below
documentation for further details. Working example can be find [here.](https://github.com/dhruvinsh/zmk-config/blob/0ed6b525a5834dc423eb600b4552b9afb9c621ee/config/include/behaviors.dtsi#L52-L61)

## Summary: Tri-State

Tri-States are a way to have something persist while other behaviors occur.

The tri-state key will fire the 'start' behavior when the key is pressed for
the first time. Subsequent presses of the same key will output the second,
'continue' behavior, and any key position or layer state change that is not
specified (see below) will trigger the 'interrupt behavior'.

### Basic Usage

The following is a basic definition of a tri-state:

```devicetree
/ {
    behaviors {
        tri-state: tri-state {
            compatible = "zmk,behavior-tri-state";
            label = "TRI-STATE";
            #binding-cells = <0>;
            bindings = <&kp A>, <&kp B>, <&kt C>;
        };
    };

    keymap {
        compatible = "zmk,keymap";
        label ="Default keymap";

        default_layer {
            bindings = <
                &tri-state  &kp D
                &kp E       &kp F>;
        };
    };
};
```

Pressing `tri-state` will fire the first behavior, and output `A`, as well as
the second behavior, outputting `B`. Subsequent presses of `tri-state` will
output `B`. When another key is pressed or a layer change occurs, the third,
'interrupt' behavior will fire.

### Advanced Configuration

#### `timeout-ms`

Setting `timeout-ms` will cause the deactivation behavior to fire when the time
has elapsed after releasing the Tri-State or a ignored key.

#### `ignored-key-positions`

- Including `ignored-key-positions` in your tri-state definition will let the
  key positions specified NOT trigger the interrupt behavior when a tri-state
  is active.
- Pressing any key **NOT** listed in `ignored-key-positions` will cause the
  interrupt behavior to fire.
- Note that `ignored-key-positions` is an array of key position indexes. Key
  positions are numbered according to your keymap, starting with 0. So if the
  first key in your keymap is Q, this key is in position 0. The next key
  (probably W) will be in position 1, et cetera.
- See the following example, which is an implementation of the popular [Swapper](https://github.com/callum-oakley/qmk_firmware/tree/master/users/callum)
  from Callum Oakley:

```devicetree
/ {
    behaviors {
        swap: swapper {
            compatible = "zmk,behavior-tri-state";
            label = "SWAPPER";
            #binding-cells = <0>;
            bindings = <&kt LALT>, <&kp TAB>, <&kt LALT>;
            ignored-key-positions = <1>;
        };
    };

    keymap {
        compatible = "zmk,keymap";
        label ="Default keymap";

        default_layer {
            bindings = <
                &swap    &kp LS(TAB)
                &kp B    &kp C>;
        };
    };
};
```

- The sequence `(swap, swap, LS(TAB))` produces `(LA(TAB), LA(TAB), LA(LS(TAB)))`.
  The LS(TAB) behavior does not fire the interrupt behavior, because it is
  included in `ignored-key-positions`.
- The sequence `(swap, swap, B)` produces `(LA(TAB), LA(TAB), B)`. The B
  behavior **does** fire the interrupt behavior, because it is **not** included
  in `ignored-key-positions`.

#### `ignored-layers`

- By default, any layer change will trigger the end behavior.
- Including `ignored-layers` in your tri-state definition will let the specified
  layers NOT trigger the end behavior when they become active (include the
  layer the behavior is on to accommodate for layer toggling).
- Activating any layer **NOT** listed in `ignored-layers` will cause the
  interrupt behavior to fire.
- Note that `ignored-layers` is an array of layer indexes. Layers are numbered
  according to your keymap, starting with 0. The first layer in your keymap is
  layer 0. The next layer will be layer 1, et cetera.
- Looking back at the swapper implementation, we can see how `ignored-layers`
  can affect things

```devicetree
/ {
    behaviors {
        swap: swapper {
            compatible = "zmk,behavior-tri-state";
            label = "SWAPPER";
            #binding-cells = <0>;
            bindings = <&kt LALT>, <&kp TAB>, <&kt LALT>;
            ignored-key-positions = <1 2 3>;
            ignored-layers = <1>;
        };
    };

    keymap {
        compatible = "zmk,keymap";
        label ="Default keymap";

        default_layer {
            bindings = <
                &swap    &kp LS(TAB)
                &kp B    &tog 1>;
        };

        layer2 {
            bindings = <
                &kp DOWN    &kp B
                &tog 2    &trans>;
        };

        layer3 {
            bindings = <
                &kp LEFT  &kp N2
                &trans    &kp N3>;
        };
    };
};
```

- The sequence `(swap, tog 1, DOWN)` produces `(LA(TAB), LA(DOWN))`. The change
  to layer 1 does not fire the interrupt behavior, because it is included in
  `ignored-layers`, and DOWN is in the same position as the tri-state, also not
  firing the interrupt behavior.
- The sequence `(swap, tog 1, tog 2, LEFT)` produces `(LA(TAB), LEFT`. The
  change to layer 2 **does** fire the interrupt behavior, because it is not
  included in `ignored-layers`.

## Credits

- [Pete Johanson](https://github.com/petejohanson)
- [Nick Conway](https://github.com/nickconway)
- [Cem Aksoylar](https://github.com/caksoylar)
- ZMK and Zephyr

## Other Project

- [ZMK-NUM-WORD](https://github.com/dhruvinsh/zmk-num-word)

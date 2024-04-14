# SDL2 Development Notes
SDL3 已经发布，然而SDL2仍然是`stable`版本。
先用SDL2避免麻烦。

+ SDL_image有点问题，似乎用不了
    + 建议使用stb_image等替代
    + 渲染时方向调整可以使用`SDL_RenderCopyEx`

跨平台实验需要使用宏

## Input Devices
```c
 if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = 0;
                    break;
                case SDL_CONTROLLERDEVICEADDED:
                    SDL_GameControllerOpen(event.cdevice.which);
                    break;
                case SDL_CONTROLLERBUTTONDOWN:
                    if(event.cbutton.button == SDL_CONTROLLER_BUTTON_START)
                        running = 0;
                    break;
            }
        }
```

SDL_CONTROLLER_BUTTON_INVALID

-1

SDL_CONTROLLER_BUTTON_A

0

SDL_CONTROLLER_BUTTON_B

1

SDL_CONTROLLER_BUTTON_X

2

SDL_CONTROLLER_BUTTON_Y

3

SDL_CONTROLLER_BUTTON_BACK

4

SDL_CONTROLLER_BUTTON_GUIDE

5

SDL_CONTROLLER_BUTTON_START

6

SDL_CONTROLLER_BUTTON_LEFTSTICK

7

SDL_CONTROLLER_BUTTON_RIGHTSTICK

8

SDL_CONTROLLER_BUTTON_LEFTSHOULDER

9

SDL_CONTROLLER_BUTTON_RIGHTSHOULDER

10

SDL_CONTROLLER_BUTTON_DPAD_UP

11

SDL_CONTROLLER_BUTTON_DPAD_DOWN

12

SDL_CONTROLLER_BUTTON_DPAD_LEFT

13

SDL_CONTROLLER_BUTTON_DPAD_RIGHT

14

SDL_CONTROLLER_BUTTON_MISC1

15

SDL_CONTROLLER_BUTTON_PADDLE1

16

SDL_CONTROLLER_BUTTON_PADDLE2

17

SDL_CONTROLLER_BUTTON_PADDLE3

18

SDL_CONTROLLER_BUTTON_PADDLE4

19

SDL_CONTROLLER_BUTTON_TOUCHPAD

20

SDL_CONTROLLER_BUTTON_MAX


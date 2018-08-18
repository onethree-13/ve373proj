# Ve373 project Battle of Tanks
### Demo Link

https://youtu.be/_B45H0vAMCo

### Tree Structure

```bash
├─debug
│  ├─joystick
│  ├─LCD
│  ├─LED
│  ├─motor
│  └─src
└─main
    └─src

```

+ `./main/` is the workspace for main program.
+ + `./main/src/` is for main.c and all *.h files.
  + Please include all files in `./main/src/`
+ `./debug/xxx/` are the workspace for different kinds of independent debug program.
+ + `./debug/src` is for *.c files for debugging.
  + Please include relevant *.h file in `./main/src/`.
  + Please include relevant xxx.c file in `./debug/src/`.

### Work Division

Tianhong Shen

- LCD debug & test program (deadline July 29th)

Qianyong Tang

- joystick debug & test program (deadline July 29th)
- motor debug & test program (deadline July 29th)

Yiming WU

- game design (deadline July 29th)


### Game Rules

+ Every turn, tanks move first, then the bullets.
+ The damage range of each bullet is two grids forward.
+ The tank shoots every two turns. 


### Schematics

#### pic32mx796m512l

|  Element  | Function | Port | Expansion Port |
| :-------: | :------: | :--: | :------------: |
| JoyStick1 |   AN0    | RB0  |     J11 34     |
|           |   AN1    | RB1  |     J11 33     |
| JoyStick2 |   AN2    | RB3  |     J11 32     |
|           |   AN3    | RB4  |     J11 31     |
| JoyStick3 |   AN8    | RB8  |     J10 33     |
|           |   AN9    | RB9  |     J10 34     |
| JoyStick4 |   AN14   | RB14 |     J10 59     |
|           |   AN15   | RB15 |     J10 60     |
|  motor1   |   OC1    | RD0  |     J11 19     |
|  motor2   |   OC2    | RD1  |     J11 20     |
|  motor3   |   OC3    | RD2  |     J11 17     |
|  motor4   |   OC4    | RD3  |     J11 18     |
|    LCD    |   U1TX   | RF3  |     J11 43     |
|           |   U1RX   | RF2  |     J11 41     |

#### map

| byte | unit        |
| ---- | ----------- |
| 0x30 | empty       |
| 0x31 | bullet      |
| 0x32 | wall        |
| 0x33 | tank1 up    |
| 0x34 | tank1 down  |
| 0x35 | tank1 left  |
| 0x36 | tank1 right |
| 0x37 | start stat  |
| 0x38 | start map   |
| 0x39 | end map     |
| 0x3A | tank1 win   |
| 0x3B | tank2 win   |
| 0x3C | draw        |
| 0x41 | tank2 up    |
| 0x42 | tank2 down  |
| 0x43 | tank2 left  |
| 0x44 | tank2 right |
# Ve373 project Battle of Tanks
### Tree Structure

```bash
├─debug
│  ├─joystick
│  ├─LCD
│  ├─LED
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
- LED debug & test program (deadline July 29th)

Yiming WU

- game design (deadline July 29th)


### Game Rules

+ Every turn, tanks move first, then the bullets.
+ The damage range of each bullet is forward two grids.
+ The tank shoots every two turns. 



### Demo

#### Legends

| item   | legend                             |
| ------ | :--------------------------------- |
| tank   | $\top$, $\bot$, $\dashv$, $\vdash$ |
| bullet | $\bullet$                          |
| danger | $\star$                            |

#### Shooting

| turn 0 | $\vdash$ |           |         |           |         |           |         |         |
| ------ | -------- | --------- | ------- | --------- | ------- | --------- | ------- | ------- |
| turn 1 | $\vdash$ | $\bullet$ | $\star$ | $\star$   |         |           |         |         |
| turn 2 | $\vdash$ |           |         | $\bullet$ | $\star$ | $\star$   |         |         |
| turn 3 | $\vdash$ | $\bullet$ | $\star$ | $\star$   |         | $\bullet$ | $\star$ | $\star$ |


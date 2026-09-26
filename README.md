# LED Dino Run

My first game: a Chrome T-Rex / dinosaur runner, built on Arduino and an 8×8 LED matrix.

You play as a small character on the left. Obstacles (trees) scroll toward you from the right. Jump to clear them. The game speeds up after each obstacle you survive. Hit one and the matrix fills with a lose animation, then the round restarts.

## Hardware

- Arduino (any board with the pins below)
- 8×8 LED matrix
- Shift register driving the matrix rows
- Two buttons

### Pin map

| Function | Pin |
| --- | --- |
| Matrix columns / grounds | D3–D10 (`g1`–`g8`) |
| Shift register data | A0 |
| Register clock (`Rclock`) | A1 |
| Shift clock (`SRclock`) | A2 |
| Move button | A4 |
| Jump button | A5 |

## How to play

- **A5** — jump (only from the ground)
- **A4** — move the character one column to the right (wraps around the matrix)
- Clear trees to keep going; speed increases each time a tree leaves the screen
- Collision ends the round

## Run it

1. Open `game1.ino` in the Arduino IDE.
2. Select your board and port.
3. Upload the sketch.
4. Press jump when a tree reaches you.

## Controls in code

Gameplay lives in `loop()`: draw the player and tree, check collision, scroll the obstacle, then read buttons. Jump physics are in `jump()`. Collision is a simple bounding-box test in `collusion()`.

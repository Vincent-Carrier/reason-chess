type sq = (int, int);
type vec = sq;
type color = White | Black;
type piece = { sq: sq, color: color };

module Color {
  let opposite = (clr) => clr == White ? Black : White;
  let homeRow = (clr) => clr == White ? 7 : 0;
  let pawnRow = (clr) => clr == White ? 6 : 1;
  let forward = (clr) => clr == White ? -1 : 1;
}

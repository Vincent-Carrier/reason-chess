open Base;

module Sq = {
  type t = sq;
  let compare = ((x1,y1), (x2,y2)) =>
    switch (Pervasives.compare(x1, x2)) {
      | 0 => Pervasives.compare(y1, y2);
      | c => c;
    }
}

module SqMap = Map.Make(Sq)

type t = {
  allPieces: SqMap.t(piece),
};

let at = (sq, ~board: t) => SqMap.find_opt(sq, board.allPieces);

let inside = ((x, y)) => 0 <= x && x < 8 && 0 <= y && y < 8;

let empty = () => { allPieces: SqMap.empty }

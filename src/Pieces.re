open Base; 
open List;
open Movement;

module type Piece = {
  let moves: (piece, Board.t) => list(sq);
}

let four_ways = (v, fn) => 
  four_directions(v)
  |> map(ve => fn(~towards=ve))
  |> flatten

module Bishop: Piece {
  let moves = (piece, board) => four_ways((1,1), slide(piece, board, ()));
}

module Rook: Piece {
  let moves = (piece, board) => four_ways((0,1), slide(piece, board, ()));
}

module Queen: Piece {
  let moves = (p, b) => Bishop.moves(p, b) @ Rook.moves(p, b);
}

module King: Piece {
  let moves = (p, b) => { 
    let diagonal = four_ways((1,1), slide(p, b, ~take=1, ()));
    let lateral = four_ways((0,1), slide(p, b, ~take=1, ()));
    diagonal @ lateral
  }
}

module Knight: Piece {
  let moves = (p, b) => { 
    let lShape = four_ways((1,2), slide(p, b, ~take=1, ()));
    let flippedL = four_ways((2,1), slide(p, b, ~take=1, ()));
    lShape @ flippedL
  }
}

module Pawn: Piece {
  let moves = (p, b) => { 
    let fwd = Color.forward(p.color);
    let straight = (0, fwd);
    let range = (snd(p.sq) == Color.pawnRow(p.color)) ? 2 : 1;
    let straightMoves = slide(p, b, ~towards=straight, 
                              ~take=range, ~canCapture=false, ());
    let captures = 
      List.map((n) => slide(p, b, ~take=1, ~towards=(n, fwd), ()), [-1, 1])
      |> List.flatten;
    straightMoves @ captures
  }
}

type t = Pawn | Knight | Bishop | Rook | Queen | King



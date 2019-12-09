open Base;

let translate = ((x,y), (i,j)) => (x+i, y+j);
let scale = ((i,j), n) => (i*n, j*n);
let rotate = ((i,j)) => (-j, i);

let slide = ({sq, color}: piece, ~towards: vec,
             board: Board.t, ~canCapture=true, ~take as max=8, ()): list((int, int)) => {
  let rec slide = (currentSq, moves) => {
    let sqContent = Board.at(currentSq, ~board);
    switch (sqContent) {
      | None when !(Board.inside(currentSq)) => moves;
      | None when max == List.length(moves) => moves;
      | Some(piece) when piece.color == color => moves;
      | None when (Board.inside(currentSq)) => 
        slide(translate(currentSq, towards), [currentSq, ...moves]);
      | Some(piece) when piece.color == Color.opposite(color) && canCapture => 
        [currentSq, ...moves];
    }
  }
  slide(translate(sq, towards), []);
}

let four_directions = v => {
  let rec rotated = directions => {
    switch (List.length(directions)) {
      | 4 => directions;
      | _ => rotated([rotate(List.hd(directions)), ...directions]);
    }
  };
  rotated([v]);
}

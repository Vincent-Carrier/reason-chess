open Jest;
open Movement;
open Expect;

describe("Sliding", () => {
  test("diagonally", () => {
    let expected = [(7,4), (6,3), (5,2)];
    let actual = slide({sq: (4,1), color: White}, ~towards=(1,1),
                      ~board=Board.empty(), ~canCapture=true);
    expect(actual) |> toEqual(expected);
  });
});

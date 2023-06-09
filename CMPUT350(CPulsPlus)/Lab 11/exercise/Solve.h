#pragma once

#include <vector>

using Matrix = std::vector<std::vector<double>>;
using Vector = std::vector<double>;

// payoffs in A below are in view of the row player
// p1 refers to the row player

// solve matrix game, print MiniMax strategies and value for p1 to stdout
extern void solve(Matrix &A);

// write best response to row strategy and value for p1 to stdout
extern void best_response_to_row(const Matrix &A, const Vector &strat1);

// write best response to col strategy and value for p1 to stdout
extern void best_response_to_col(const Matrix &A, const Vector &strat2);

// write expected value of game for the row player for given row and col
// strategies to stdout
extern void expected_value(const Matrix &A, const Vector &strat1, const Vector &strat2);

#ifndef _HEX_H_
#define _HEX_H_
struct Hex { // Cube storage, axial constructor
    const int q, r, s;
    Hex(int q_, int r_): q(q_), r(r_), s(-q_ - r_) {}
};
#endif
#include "Characters.h"

std::map<char, const char *> Characters::GetCharactersMap()
{
    static std::map<char, const char *> charMap;
    static bool hasBeenCalled = false;

    if (!hasBeenCalled)
    {
        hasBeenCalled = true;
        charMap['A'] = A;
        charMap['B'] = B;
        charMap['C'] = C;
        charMap['D'] = D;
        charMap['E'] = E;
        charMap['F'] = F;
        charMap['G'] = G;
        charMap['H'] = H;
        charMap['I'] = I;
        charMap['J'] = J;
        charMap['K'] = K;
        charMap['L'] = L;
        charMap['M'] = M;
        charMap['N'] = N;
        charMap['O'] = O;
        charMap['P'] = P;
        charMap['Q'] = Q;
        charMap['R'] = R;
        charMap['S'] = S;
        charMap['T'] = T;
        charMap['U'] = U;
        charMap['V'] = V;
        charMap['W'] = W;
        charMap['X'] = X;
        charMap['Y'] = Y;
        charMap['Z'] = Z;
        charMap['!'] = exclamation;
        charMap['?'] = interrogation;
        charMap['\''] = apostrophe;
        charMap[','] = comma;
        charMap['.'] = period;
        charMap['('] = openParenthesis;
        charMap[')'] = closeParenthesis;
        charMap['/'] = slash;
        charMap['0'] = _0;
        charMap['1'] = _1;
        charMap['2'] = _2;
        charMap['3'] = _3;
        charMap['4'] = _4;
        charMap['5'] = _5;
        charMap['6'] = _6;
        charMap['7'] = _7;
        charMap['8'] = _8;
        charMap['9'] = _9;
    }

    return charMap;
}

const char *Characters::A{
    " 333 "
    "3   3"
    "33333"
    "3   3"
    "3   3"};

const char *Characters::B{
    "3333 "
    "3   3"
    "3333 "
    "3   3"
    "3333"};

const char *Characters::C{
    " 3333"
    "3    "
    "3    "
    "3    "
    " 3333"};

const char *Characters::D{
    "333  "
    "3  3 "
    "3   3"
    "3  3 "
    "333  "};

const char *Characters::E{
    " 3333"
    "3    "
    "33333"
    "3    "
    " 3333"};

const char *Characters::F{
    "33333"
    "3    "
    "333  "
    "3    "
    "3    "};

const char *Characters::G{
    " 3333"
    "3    "
    "3  33"
    "3   3"
    " 3333"};

const char *Characters::H{
    "3   3"
    "3   3"
    "33333"
    "3   3"
    "3   3"};

const char *Characters::I{
    " 333 "
    "  3  "
    "  3  "
    "  3  "
    " 333 "};

const char *Characters::J{
    "33333"
    "    3"
    "    3"
    "3   3"
    " 333"};

const char *Characters::K{
    "3   3"
    "3  3 "
    "333  "
    "3  3 "
    "3   3"};

const char *Characters::L{
    "3    "
    "3    "
    "3    "
    "3    "
    "33333"};

const char *Characters::M{
    "3   3"
    "33 33"
    "3 3 3"
    "3   3"
    "3   3"};

const char *Characters::N{
    "3   3"
    "33  3"
    "3 3 3"
    "3  33"
    "3   3"};

const char *Characters::O{
    " 333 "
    "3   3"
    "3   3"
    "3   3"
    " 333 "};

const char *Characters::P{
    "3333 "
    "3   3"
    "3333 "
    "3    "
    "3    "};

const char *Characters::Q{
    " 33  "
    "3  3 "
    "3  3 "
    "3  3 "
    " 3333"};

const char *Characters::R{
    "3333 "
    "3   3"
    "3333 "
    "3  3 "
    "3   3"};

const char *Characters::S{
    " 3333"
    "3    "
    " 333 "
    "    3"
    "3333 "};

const char *Characters::T{
    "33333"
    "  3  "
    "  3  "
    "  3  "
    "  3  "};

const char *Characters::U{
    "3   3"
    "3   3"
    "3   3"
    "3   3"
    " 333 "};

const char *Characters::V{
    "3   3"
    "3   3"
    "3   3"
    " 3 3 "
    "  3  "};

const char *Characters::W{
    "3   3"
    "3   3"
    "3 3 3"
    "33 33"
    "3   3"};

const char *Characters::X{
    "3   3"
    " 3 3 "
    "  3  "
    " 3 3 "
    "3   3"};

const char *Characters::Y{
    "3   3"
    " 3 3 "
    "  3  "
    "  3  "
    "  3  "};

const char *Characters::Z{
    "33333"
    "   3 "
    "  3  "
    " 3   "
    "33333"};

const char *Characters::exclamation{
    "  3  "
    "  3  "
    "  3  "
    "     "
    "  3  "};

const char *Characters::interrogation{
    " 33  "
    "   3 "
    "  3  "
    "     "
    "  3  "};

const char *Characters::apostrophe{
    "  3  "
    "  3  "
    "     "
    "     "
    "     "};

const char *Characters::comma{
    "     "
    "     "
    "     "
    " 3   "
    "3    "};

const char *Characters::period{
    "     "
    "     "
    "     "
    "     "
    "3    "};

const char *Characters::openParenthesis{
    "    3"
    "   3 "
    "   3 "
    "   3 "
    "    3"};

const char *Characters::closeParenthesis{
    "3    "
    " 3   "
    " 3   "
    " 3   "
    "3    "};

const char *Characters::slash{
    "    3"
    "   3 "
    "  3  "
    " 3   "
    "3    "};

const char *Characters::_0{
    " 333 "
    "3   3"
    "3 3 3"
    "3   3"
    " 333 "};

const char *Characters::_1{
    "   3 "
    "  33 "
    " 3 3 "
    "   3 "
    " 3333"};

const char *Characters::_2{
    "  33 "
    " 3  3"
    "   3 "
    "  3  "
    " 3333"};

const char *Characters::_3{
    "3333 "
    "    3"
    " 333 "
    "    3"
    "3333 "};

const char *Characters::_4{
    "  33 "
    " 3 3 "
    "3333 "
    "   3 "
    "  333"};

const char *Characters::_5{
    "33333"
    "3    "
    "3333 "
    "    3"
    "3333 "};

const char *Characters::_6{
    " 333 "
    "3    "
    "3333 "
    "3   3"
    "3333 "};

const char *Characters::_7{
    "33333"
    "   3 "
    "  3  "
    " 3   "
    "3    "};

const char *Characters::_8{
    " 333 "
    "3   3"
    " 333 "
    "3   3"
    " 333 "};

const char *Characters::_9{
    " 333 "
    "3   3"
    " 3333"
    "    3"
    " 333 "};
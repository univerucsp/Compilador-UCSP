#pragma once
#include "all.hpp"


// Macro para definir una enumeracion de tipos de token utilizando enum.h
BETTER_ENUM(TokenType, int,
            // Terminales
            DOUBLE_NEWLINE = 0, NEWLINE, WORD, STRONG_OPEN, STRONG_CLOSE,
            EMPH_OPEN, EMPH_CLOSE, LINK_OPEN, LINK_CLOSE, LINK_MID, HEAD1,
            HEAD2, HEAD3, IMAGE_CAP, ULIST_SYMB, OLIST_SYMB, TABLE_CAP,
            TITLE_CAP, AUTHOR_CAP, DATE_CAP, TABLE_SEP, END_OF_FILE,

            // No terminales
            Doc, DocTitle, FDocTitle, Ftitle_cap, FText, Fauthor_cap, FText1, DocBlocks,
            FBlock, Block, Par, FStrongPar, FEmphPar, FLink, LineText, Fword, Text, FLineText,
            StrongPar, EmphPar, Link, Flink_open, Fword1, UList,
            Fulist_symb, FPar, OList, Folist_symb, FPar1, Image, TableItem,
            Ftable_sep, FLineText1, TableBody, FTableItem, TableCap, Table, Header);


// Estructura para almacenar un token
struct Token {
  TokenType type;
  string value;
  int line_number;
  Token(TokenType _type = TokenType::WORD, const string &_value = "", int _line_number = 0)
      : type(_type), value(_value), line_number(_line_number) {}

  bool terminal() const {
    return type._to_integral() < (+TokenType::Doc)._to_integral();
  }

  bool newline() const {
    return type._to_integral() == TokenType::NEWLINE ||
           type._to_integral() == TokenType::DOUBLE_NEWLINE;
  }

  bool eof() const { return type._to_integral() == TokenType::END_OF_FILE; }

  void print() const {
    if (type._to_integral() == TokenType::WORD) {
      printf("Token(%s, %s)", type._to_string(), value.c_str());
    } else {
      printf("Token(%s)", type._to_string());
    }
  }
};
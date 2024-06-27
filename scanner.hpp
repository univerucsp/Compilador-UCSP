#pragma once
#include "all.hpp"
#include "token.hpp"

// Para obtener la palabra evitando simbolos como:
// {* *} {_ _} |: [[ ][ ]] /*
void next_word(ifstream &input, Token &token) {
  token.type = TokenType::WORD;
  while (true) {
    switch (input.peek()) {
    case '{':
      token.value.push_back(input.get());
      if (input.peek() == '*' || input.peek() == '_') {
        token.value.pop_back();
        input.unget();
        return;
      }
      break;
    case '*':
    case '_':
      token.value.push_back(input.get());
      if (input.peek() == '}') {
        token.value.pop_back();
        input.unget();
        return;
      }
      break;
    case '|':
      token.value.push_back(input.get());
      if (input.peek() == ':') {
        token.value.pop_back();
        input.unget();
        return;
      }
      break;
    case '[':
      token.value.push_back(input.get());
      if (input.peek() == '[') {
        token.value.pop_back();
        input.unget();
        return;
      }
      break;
    case ']':
      token.value.push_back(input.get());
      if (input.peek() == '[' || input.peek() == ']') {
        token.value.pop_back();
        input.unget();
        return;
      }
      break;
    case '/':
      token.value.push_back(input.get());
      if (input.peek() == '*') {
        token.value.pop_back();
        input.unget();
        return;
      }
      break;
    case ' ':
    case '\t':
    case '\n':
    case EOF:
      return;
    default:
      token.value.push_back(input.get());
      break;
    }
  }
}

// Función principal del scanner
Token next_token(ifstream &input, bool start_of_line = false, int line_number = 1) {
  Token token;
  char current_char;

  // Saltar separadores
  do {
    current_char = input.get();
  } while (current_char == ' ' || current_char == '\t');

  // Chequear si se llegó al final del archivo
  if (input.eof()) {
    return Token(TokenType::END_OF_FILE);
  }

  token.value.push_back(current_char);

  if (current_char == '\n') {
    while (input.peek() == '\n') {
      token.value.push_back(input.get());
    }
    if (token.value.size() == 1) {
      token.type = TokenType::NEWLINE;
    } else {
      token.type = TokenType::DOUBLE_NEWLINE;
    }
  } else if (current_char == '{') {
    if (input.peek() == '*') {
      token.value.push_back(input.get());
      token.type = TokenType::STRONG_OPEN;
    } else if (input.peek() == '_') {
      token.value.push_back(input.get());
      token.type = TokenType::EMPH_OPEN;
    } else {
      next_word(input, token);
    }
  } else if (current_char == '*') {
    if (input.peek() == '}') {
      token.value.push_back(input.get());
      token.type = TokenType::STRONG_CLOSE;
    } else {
      next_word(input, token);
    }
  } else if (current_char == '_') {
    if (input.peek() == '}') {
      token.value.push_back(input.get());
      token.type = TokenType::EMPH_CLOSE;
    } else {
      next_word(input, token);
    }
  } else if (current_char == '|') {
    if (input.peek() == ':') {
      token.value.push_back(input.get());
      token.type = TokenType::TABLE_SEP;
    } else {
      next_word(input, token);
    }
  } else if (current_char == '[') {
    if (input.peek() == '[') {
      token.value.push_back(input.get());
      token.type = TokenType::LINK_OPEN;
    } else {
      next_word(input, token);
    }
  } else if (current_char == ']') {
    if (input.peek() == '[') {
      token.value.push_back(input.get());
      token.type = TokenType::LINK_MID;
    } else if (input.peek() == ']') {
      token.value.push_back(input.get());
      token.type = TokenType::LINK_CLOSE;
    } else {
      next_word(input, token);
    }
  } else if (start_of_line && current_char == '#') { // HEAD
    if (input.peek() == '#') {                       // consume el segundo '#'
      token.value.push_back(input.get());
      if (input.peek() == '#') { // consume el tercer '#'
        token.value.push_back(input.get());
        token.type = TokenType::HEAD3;
      } else {
        token.type = TokenType::HEAD2;
      }
    } else {
      token.type = TokenType::HEAD1;
    }
  } else if (start_of_line && current_char == '-') {
    token.type = TokenType::ULIST_SYMB;
  } else if (start_of_line && isdigit(current_char)) {
    while (isdigit(input.peek())) {
      token.value.push_back(input.get());
    }
    if (input.peek() == '.') {
      token.value.push_back(input.get());
      token.type = TokenType::OLIST_SYMB;
    } else {
      next_word(input, token);
    }
  } else {
    next_word(input, token);
  }

  assert(!token.value.empty() && "Token está vacío");

  if (start_of_line && token.type._to_integral() == TokenType::WORD) {
    if (token.value == "TITLE:") {
      token.type = TokenType::TITLE_CAP;
    } else if (token.value == "AUTHOR:") {
      token.type = TokenType::AUTHOR_CAP;
    } else if (token.value == "DATE:") {
      token.type = TokenType::DATE_CAP;
    } else if (token.value == "IMAGE:") {
      token.type = TokenType::IMAGE_CAP;
    } else if (token.value == "TABLE:") {
      token.type = TokenType::TABLE_CAP;
    }
  }

  token.line_number = line_number;
  return token;
}
#include "all.hpp"
#include "parser.hpp"
#include "scanner.hpp"
#include "token.hpp"

int main(int argc, char **argv) {
  ifstream input("ejemplo.txt");
  list<Token> tokens;
  int line_number = 1;

  while (tokens.empty() || !tokens.back().eof()) {
    // ignorar comentarios y espacios
    while (input.peek() == ' ' || input.peek() == '\t')
      input.get();

    while (input.peek() == '/') {
      input.get();
      if (input.peek() == '*') {
        input.get();
        while (true) {
          if (input.peek() == '*') {
            input.get();
            if (input.peek() == '/') {
              input.get();
              break;
            }
          } else {
            input.get();
          }
        }
      } else {
        input.unget();
        break;
      }
    }

    auto ntoken = next_token(input, tokens.empty() || tokens.back().newline(),
                             line_number);

    if (!tokens.empty() && tokens.back().newline() && ntoken.newline()) {
      tokens.back().type = TokenType::DOUBLE_NEWLINE;
    } else {
      tokens.push_back(ntoken);
    }

    if (ntoken.type._to_integral() == TokenType::DOUBLE_NEWLINE) {
      line_number += 2;
    } else if (ntoken.type._to_integral() == TokenType::NEWLINE) {
      line_number++;
    }
  }
  for (auto it = tokens.begin(); it != tokens.end(); ++it) {
    if (it == tokens.begin() ||
        prev(it)->type._to_integral() != TokenType::NEWLINE)
      continue;
    switch (it->type) {
    case TokenType::TITLE_CAP:
    case TokenType::AUTHOR_CAP:
    case TokenType::DATE_CAP:
    case TokenType::ULIST_SYMB:
    case TokenType::OLIST_SYMB:
    case TokenType::IMAGE_CAP:
    case TokenType::TABLE_CAP:
      tokens.erase(prev(it));
      break;
    default:
      break;
    }
  }

  puts("SCANNER:");
  for (const auto &token : tokens) {
    token.print();
    puts("");
  }

  ParseTreeNode* parseTree = nullptr;

  // Archivo que tendra la salida del parser
  std::string nombreArchivo = "documento.tex";
  std::ofstream archivo(nombreArchivo);
  
  puts("\nPARSER:");
  
  // Si el parser encuentra algun error solo muestra el error
  if (parse(tokens, parseTree)) {
    puts("Parseo exitoso. Árbol de parseo:\n");
    std::string latex = translateToLatex(parseTree);
    std::cout << "Traducción a LaTeX Terminada;\n" << std::endl;
    archivo << latex;
  } else {
    puts("Error en el parseo.\n");
  }

  deleteParseTree(parseTree);
  return 0;
}
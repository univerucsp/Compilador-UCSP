#pragma once
#include "all.hpp"
#include "token.hpp"

using T = TokenType;


//Gramatica ................................................
vector<pair<TokenType, vector<TokenType>>> grammar = {
  {T::Doc,         {T::DocTitle, T::FDocTitle}}, //........................................(0)
  {T::FDocTitle,   {T::DOUBLE_NEWLINE, T::DocBlocks, T::END_OF_FILE}}, //..................(1)
  {T::FDocTitle,   {T::END_OF_FILE}}, //...................................................(2)
  {T::DocTitle,    {T::TITLE_CAP, T::Ftitle_cap}}, //......................................(3)
  {T::Ftitle_cap,  {T::Text, T::FText}}, //................................................(4)
  {T::FText,       {}}, //.................................................................(5)
  {T::FText,       {T::AUTHOR_CAP, T::Fauthor_cap}}, //....................................(6)
  {T::Fauthor_cap, {T::Text, T::FText1}}, //...............................................(7)
  {T::FText1,      {}}, //...... .........................................................(8)
  {T::FText1,      {T::DATE_CAP, T::Text}}, //.............................................(9)
  {T::DocBlocks,   {T::Block, T::FBlock}}, //..............................................(10)
  {T::FBlock,      {}}, //................................................................(11)
  {T::FBlock,      {T::DOUBLE_NEWLINE, T::DocBlocks}}, //..................................(12)
  {T::Block,       {T::Par}}, //...........................................................(13)
  {T::Block,       {T::Header}}, //........................................................(14)
  {T::Block,       {T::UList}}, //.........................................................(15)
  {T::Block,       {T::OList}}, //.........................................................(16)
  {T::Block,       {T::Image}}, //.........................................................(17)
  {T::Block,       {T::Table}}, //.........................................................(18)
  {T::Par,         {T::Text}}, //..........................................................(19)
  {T::Par,         {T::StrongPar, T::FStrongPar}}, //......................................(20)
  {T::Par,         {T::EmphPar, T::FEmphPar}}, //..........................................(21)
  {T::Par,         {T::Link, T::FLink}}, //................................................(22)
  {T::FStrongPar,  {}}, //................................................................(23)
  {T::FStrongPar,  {T::Par}}, //...........................................................(24)
  {T::FEmphPar,    {}}, //................................................................(25)
  {T::FEmphPar,    {T::Par}}, //...........................................................(26)
  {T::FLink,       {}}, //................................................................(27)
  {T::FLink,       {T::Par}}, //...........................................................(28)
  {T::LineText,    {T::WORD, T::Fword}}, //................................................(29)
  {T::Fword,       {}}, //................................................................(30)
  {T::Fword,       {T::LineText}}, //......................................................(31)
  {T::Text,        {T::LineText, T::FLineText}}, //........................................(32)
  {T::FLineText,   {}}, //....... ........................................................(33)
  {T::FLineText,   {T::NEWLINE, T::Text}}, //..............................................(34)
  {T::StrongPar,   {T::STRONG_OPEN, T::Par, T::STRONG_CLOSE}}, //..........................(35)
  {T::EmphPar,     {T::EMPH_OPEN, T::Par, T::EMPH_CLOSE}}, //..............................(36)
  {T::Link,        {T::LINK_OPEN, T::Flink_open}}, //......................................(37)
  {T::Flink_open,  {T::WORD, T::Fword1}}, //...............................................(38)
  {T::Fword1,      {T::LINK_CLOSE}}, //....................................................(39)
  {T::Fword1,      {T::LINK_MID, T::Par, T::LINK_CLOSE}}, //...............................(40)
  {T::UList,       {T::ULIST_SYMB, T::Fulist_symb}}, //....................................(41)
  {T::Fulist_symb, {T::Par, T::FPar}}, //..................................................(42)
  {T::FPar,        {}}, //........ .......................................................(43)
  {T::FPar,        {T::UList}}, //.........................................................(44)
  {T::OList,       {T::OLIST_SYMB, T::Folist_symb}}, //....................................(45)
  {T::Folist_symb, {T::Par, T::FPar1}}, //.................................................(46)
  {T::FPar1,       {}}, //........ .......................................................(47)
  {T::FPar1,       {T::OList}}, //.........................................................(48)
  {T::Image,       {T::IMAGE_CAP, T::Link}}, //............................................(49)
  {T::TableItem,   {T::TABLE_SEP, T::Ftable_sep}}, //......................................(50)
  {T::Ftable_sep,  {T::LineText, T::FLineText1}}, //.......................................(51)
  {T::FLineText1,  {}}, //........ .......................................................(52)
  {T::FLineText1,  {T::TableItem}}, //.....................................................(53)
  {T::TableBody,   {T::TableItem, T::FTableItem}}, //......................................(54)
  {T::FTableItem,  {}}, //... .............................................................(55)
  {T::FTableItem,  {T::NEWLINE, T::TableBody}}, //.........................................(56)
  {T::TableCap,    {T::TABLE_CAP, T::Text}}, //. ..........................................(57)
  {T::Table,       {T::TableBody, T::TableCap}}, //.. .....................................(58)
  {T::Header,      {T::HEAD1, T::Text}}, //................................................(59)
  {T::Header,      {T::HEAD2, T::Text}}, //................................................(60)
  {T::Header,      {T::HEAD3, T::Text}} //.................................................(61)

  // COMPLETADO
};


// Tabla de transiciones
map<pair<TokenType, TokenType>, int> table = {
    {{T::Doc, T::TITLE_CAP}, 0},
    {{T::FDocTitle, T::DOUBLE_NEWLINE}, 1},
    {{T::FDocTitle, T::END_OF_FILE}, 2},
    {{T::DocTitle, T::TITLE_CAP}, 3},
    {{T::Ftitle_cap, T::WORD}, 4},
    {{T::FText, T::AUTHOR_CAP}, 6},
    {{T::FText, T::DOUBLE_NEWLINE}, 5},
    {{T::FText, T::END_OF_FILE}, 5},
    {{T::Fauthor_cap, T::WORD}, 7},
    {{T::FText1, T::DATE_CAP}, 9},
    {{T::FText1, T::DOUBLE_NEWLINE}, 8},
    {{T::FText1, T::END_OF_FILE}, 8},
    {{T::DocBlocks, T::HEAD3}, 10},
    {{T::DocBlocks, T::HEAD2}, 10},
    {{T::DocBlocks, T::HEAD1}, 10},
    {{T::DocBlocks, T::TABLE_SEP}, 10},
    {{T::DocBlocks, T::IMAGE_CAP}, 10},
    {{T::DocBlocks, T::OLIST_SYMB}, 10},
    {{T::DocBlocks, T::ULIST_SYMB}, 10},
    {{T::DocBlocks, T::WORD}, 10},
    {{T::DocBlocks, T::LINK_OPEN}, 10},
    {{T::DocBlocks, T::EMPH_OPEN}, 10},
    {{T::DocBlocks, T::STRONG_OPEN}, 10},
    {{T::FBlock, T::END_OF_FILE}, 11},
    {{T::FBlock, T::DOUBLE_NEWLINE}, 12},
    {{T::Block, T::HEAD3}, 14},
    {{T::Block, T::HEAD2}, 14},
    {{T::Block, T::HEAD1}, 14},
    {{T::Block, T::TABLE_SEP}, 18},
    {{T::Block, T::IMAGE_CAP}, 17},
    {{T::Block, T::OLIST_SYMB}, 16},
    {{T::Block, T::ULIST_SYMB}, 15},
    {{T::Block, T::WORD}, 13},
    {{T::Block, T::LINK_OPEN}, 13},
    {{T::Block, T::EMPH_OPEN}, 13},
    {{T::Block, T::STRONG_OPEN}, 13},
    {{T::Par, T::WORD}, 19},
    {{T::Par, T::LINK_OPEN}, 22},
    {{T::Par, T::EMPH_OPEN}, 21},
    {{T::Par, T::STRONG_OPEN}, 20},
    {{T::FStrongPar, T::END_OF_FILE}, 23},
    {{T::FStrongPar, T::OLIST_SYMB}, 23},
    {{T::FStrongPar, T::ULIST_SYMB}, 23},
    {{T::FStrongPar, T::LINK_CLOSE}, 23},
    {{T::FStrongPar, T::WORD}, 24},
    {{T::FStrongPar, T::LINK_OPEN}, 24},
    {{T::FStrongPar, T::EMPH_CLOSE}, 23},
    {{T::FStrongPar, T::EMPH_OPEN}, 24},
    {{T::FStrongPar, T::STRONG_CLOSE}, 23},
    {{T::FStrongPar, T::STRONG_OPEN}, 24},
    {{T::FStrongPar, T::DOUBLE_NEWLINE}, 23},
    {{T::FEmphPar, T::END_OF_FILE}, 25},
    {{T::FEmphPar, T::OLIST_SYMB}, 25},
    {{T::FEmphPar, T::ULIST_SYMB}, 25},
    {{T::FEmphPar, T::LINK_CLOSE}, 25},
    {{T::FEmphPar, T::WORD}, 26},
    {{T::FEmphPar, T::LINK_OPEN}, 26},
    {{T::FEmphPar, T::EMPH_CLOSE}, 25},
    {{T::FEmphPar, T::EMPH_OPEN}, 26},
    {{T::FEmphPar, T::STRONG_CLOSE}, 25},
    {{T::FEmphPar, T::STRONG_OPEN}, 26},
    {{T::FEmphPar, T::DOUBLE_NEWLINE}, 25},
    {{T::FLink, T::END_OF_FILE}, 27},
    {{T::FLink, T::OLIST_SYMB}, 27},
    {{T::FLink, T::ULIST_SYMB}, 27},
    {{T::FLink, T::LINK_CLOSE}, 27},
    {{T::FLink, T::WORD}, 28},
    {{T::FLink, T::LINK_OPEN}, 28},
    {{T::FLink, T::EMPH_CLOSE}, 27},
    {{T::FLink, T::EMPH_OPEN}, 28},
    {{T::FLink, T::STRONG_CLOSE}, 27},
    {{T::FLink, T::STRONG_OPEN}, 28},
    {{T::FLink, T::DOUBLE_NEWLINE}, 27}, 
    {{T::LineText, T::WORD}, 29},
    {{T::Fword, T::END_OF_FILE}, 30},
    {{T::Fword, T::TABLE_CAP}, 30},
    {{T::Fword, T::NEWLINE}, 30},
    {{T::Fword, T::TABLE_SEP}, 30},
    {{T::Fword, T::OLIST_SYMB}, 30},
    {{T::Fword, T::ULIST_SYMB}, 30},
    {{T::Fword, T::LINK_CLOSE}, 30},
    {{T::Fword, T::WORD}, 31}, 
    {{T::Fword, T::EMPH_CLOSE}, 30},
    {{T::Fword, T::STRONG_CLOSE}, 30},
    {{T::Fword, T::DOUBLE_NEWLINE}, 30},
    {{T::Fword, T::DATE_CAP}, 30},
    {{T::Fword, T::AUTHOR_CAP}, 30},
    {{T::Text, T::WORD}, 32},
    {{T::FLineText, T::END_OF_FILE}, 33},
    {{T::FLineText, T::NEWLINE}, 34},
    {{T::FLineText, T::OLIST_SYMB}, 33},
    {{T::FLineText, T::ULIST_SYMB}, 33},
    {{T::FLineText, T::LINK_CLOSE}, 33},
    {{T::FLineText, T::EMPH_CLOSE}, 33},
    {{T::FLineText, T::STRONG_CLOSE}, 33},
    {{T::FLineText, T::DOUBLE_NEWLINE}, 33},
    {{T::FLineText, T::DATE_CAP}, 33},
    {{T::FLineText, T::AUTHOR_CAP}, 33},
    {{T::StrongPar, T::STRONG_OPEN}, 35},
    {{T::EmphPar, T::EMPH_OPEN}, 36},
    {{T::Link, T::LINK_OPEN}, 37},
    {{T::Flink_open, T::WORD}, 38},
    {{T::Fword1, T::LINK_CLOSE}, 39},
    {{T::Fword1, T::LINK_MID}, 40},
    {{T::UList, T::ULIST_SYMB}, 41},
    {{T::Fulist_symb, T::WORD}, 42},
    {{T::Fulist_symb, T::LINK_OPEN}, 42},
    {{T::Fulist_symb, T::EMPH_OPEN}, 42},
    {{T::Fulist_symb, T::STRONG_OPEN}, 42},
    {{T::FPar, T::END_OF_FILE}, 43}, 
    {{T::FPar, T::ULIST_SYMB}, 44},
    {{T::FPar, T::DOUBLE_NEWLINE}, 43},
    {{T::OList, T::OLIST_SYMB}, 45},
    {{T::Folist_symb, T::WORD}, 46},
    {{T::Folist_symb, T::LINK_OPEN}, 46},
    {{T::Folist_symb, T::EMPH_OPEN}, 46},
    {{T::Folist_symb, T::STRONG_OPEN}, 46},
    {{T::FPar1, T::END_OF_FILE}, 47},
    {{T::FPar1, T::OLIST_SYMB}, 48},
    {{T::FPar1, T::DOUBLE_NEWLINE}, 47},
    {{T::Image, T::IMAGE_CAP}, 49},
    {{T::TableItem, T::TABLE_SEP}, 50},
    {{T::Ftable_sep, T::WORD}, 51},
    {{T::FLineText1, T::TABLE_CAP}, 52},
    {{T::FLineText1, T::NEWLINE}, 52},
    {{T::FLineText1, T::TABLE_SEP}, 53},
    {{T::TableBody, T::TABLE_SEP}, 54},
    {{T::FTableItem, T::TABLE_CAP}, 55},
    {{T::FTableItem, T::NEWLINE}, 56},      
    {{T::TableCap, T::TABLE_CAP}, 57},
    {{T::Table, T::TABLE_SEP}, 58},
    {{T::Header, T::HEAD3}, 61},
    {{T::Header, T::HEAD2}, 60},
    {{T::Header, T::HEAD1}, 59}
    // COMPLETADO
};


// Estructura para los nodos del arbol de parseo
struct ParseTreeNode {
    TokenType type;
    std::string value; // Solo si es un nodo terminal
    std::vector<ParseTreeNode*> children;

    ParseTreeNode(TokenType type) : type(type), value("") {}
    ParseTreeNode(TokenType type, const std::string &value) : type(type), value(value) {}
};

// Función para imprimir el arbol de parseo
void printParseTree(ParseTreeNode* node, int indent = 0) {
    for (int i = 0; i < indent; ++i) {
        std::cout << "  ";
    }
    std::cout << node->type._to_string();
    if (!node->value.empty()) {
        std::cout << ": " << node->value;
    }
    std::cout << std::endl;
    for (ParseTreeNode* child : node->children) {
        printParseTree(child, indent + 1);
    }
}

// Función para liberar memoria del arbol de parseo
void deleteParseTree(ParseTreeNode* node) {
    for (ParseTreeNode* child : node->children) {
        deleteParseTree(child);
    }
    delete node;
}


// Parser que implementa la correcion de errores y crea el arbol de parseo
bool parse(list<Token> tokens, ParseTreeNode*& root) {
    bool ans = true;
    vector<TokenType> st;
    vector<ParseTreeNode*> nodeStack;
    st.push_back(TokenType::Doc);
    root = new ParseTreeNode(TokenType::Doc);
    nodeStack.push_back(root);

    auto it = tokens.begin();
    while (!st.empty() && it != tokens.end()) {
        if (st.back() < (+TokenType::Doc)._to_integral()) {
            if (st.back() != it->type) {
                cerr << "ERROR: símbolos terminales no corresponden en la línea " << it->line_number << endl;
                cerr << "Se esperaba: " << st.back()._to_string() << " y se encontró: " << it->type._to_string() << endl;
                ans = false;
                while (it != tokens.end() && st.back() != it->type) {
                    ++it;
                }
                if (it != tokens.end()) {
                    cerr << "Recuperación de pánico: Se encontró el símbolo de sincronización " << it->type._to_string() << endl;
                    ++it;
                }
            } else {
                nodeStack.back()->children.push_back(new ParseTreeNode(it->type, it->value));
                nodeStack.pop_back();
                st.pop_back();
                ++it;
            }
        } else {
            if (!table.count(make_pair(st.back(), it->type))) {
                cerr << "ERROR: No existe la producción en la línea: " << it->line_number << endl;
                cerr << "Tokens son: " << st.back()._to_string() << " y " << it->type._to_string() << endl;
                ans = false;
                while (it != tokens.end() && !table.count(make_pair(st.back(), it->type))) {
                    ++it;
                }
                if (it != tokens.end()) {
                    cerr << "Recuperación de pánico: Se encontró el símbolo de sincronización " << it->type._to_string() << endl;
                }
            } else {
                auto prod = grammar[table[make_pair(st.back(), it->type)]].second;
                ParseTreeNode* parentNode = nodeStack.back();
                nodeStack.pop_back();
                st.pop_back();

                for (int i = prod.size() - 1; i >= 0; --i) {
                    st.push_back(prod[i]);
                    ParseTreeNode* childNode = new ParseTreeNode(prod[i]);
                    parentNode->children.push_back(childNode);
                    nodeStack.push_back(childNode);
                }
            }
        }
    }

    if (!st.empty()) {
        cerr << "ERROR: stack no se vació después de procesado el texto" << endl;
        ans = false;
        exit(1);
    }
    return ans;
}


// Funcion encargad de la traduccion a Latex ...............................................
std::string translateToLatex(ParseTreeNode* root) {
    std::ostringstream latex;
    std::stack<ParseTreeNode*> nodeStack;
    std::stack<int> childIndexStack;


    bool enumerate = true;
    bool itemize = true;
    bool tabla = true;
    int tabla_count = 0;
    nodeStack.push(root);
    childIndexStack.push(0);

    while (!nodeStack.empty()) {
        ParseTreeNode* currentNode = nodeStack.top();
        int& childIndex = childIndexStack.top();

        if (childIndex == 0) { // Node processing before children
            switch (currentNode->type) {
                case TokenType::Doc:
                    latex << "\\documentclass{article}\n\\usepackage{graphicx}\n";
                    break;
                case TokenType::DocTitle:
                    latex << "\\title{";
                    break;
                case TokenType::FDocTitle:
                    if (currentNode->children.size() == 3) {
                        latex << "\\begin{document}\n\\maketitle\n";
                    } else {
                        latex << "\\begin{document}\n\\end{document}\n";
                    }
                    break;

                case TokenType::FText:
                    if (currentNode->children[0]->type._to_integral() == TokenType::AUTHOR_CAP) {
                        latex << "";
                    } else {
                        latex << "}\n\\author{";
                    }
                    break;
                case TokenType::FText1:
                    if (currentNode->children[0]->type._to_integral() == TokenType::AUTHOR_CAP) {
                        latex << "";
                    } else {
                        latex << "}\n\\date{";
                    }
                    break;
                case TokenType::HEAD1:
                    if (currentNode->value == "#") {
                        latex << "";
                    } else {
                        latex << "\\section{";
                    }
                    break;

                case TokenType::HEAD2:
                    if (currentNode->value == "##") {
                        latex << "";
                    } else {
                        latex << "\\subsection{";
                    }
                    break;

                case TokenType::HEAD3:
                    if (currentNode->value == "###") {
                        latex << "";
                    } else {
                        latex << "\\subsubsection{";
                    }
                    break;

                case TokenType::OList:
                    if (enumerate) {
                        latex << "\\begin{enumerate}\n";
                        enumerate = false;
                    }
                    break;
                case TokenType::Folist_symb:
                    latex << "\\item ";
                    break;

                case TokenType::UList:
                    if (itemize) {
                        latex << "\\begin{itemize}\n";
                        itemize = false;
                    }
                    break;
                case TokenType::Fulist_symb:
                    latex << "\\item ";
                    break;

                case TokenType::Image:
                    latex << "\\begin{figure}[h]\n\\centering\n\\includegraphics[width=0.5\\textwidth]{";
                    break;

                case TokenType::Fword1:
                    latex << " }\n\\caption{";
                    break;
                case TokenType::Table:
                  latex << "\n\\begin{table}[h]\n\\centering\n\\begin{tabular}{|c|c|c|c|c|c|c|c|c|}\n\\hline\n";
                  break;
                case TokenType::TableCap:
                  latex << "\n\\end{tabular}\n\\caption{";
                  break;
                case TokenType::TableItem:
                    if (tabla) {
                        latex << "\\textbf{";
                        tabla_count++;
                    } else {
                        latex << " ";
                    }
                    break;
                case TokenType::FLineText1:
                    if (tabla) {
                        latex << "} & ";
                    } else {
                        latex << " & ";
                    }
                    break;
                
                case TokenType::FTableItem:
                    
                    if (tabla) {
                      std::string str = latex.str();
                      str.erase(str.size() - 2);
                      latex.str("");
                      latex << str;
                      latex << " \\\\ \\hline\n";
                      tabla = false;
                    } else {
                      std::string str = latex.str();
                      str.erase(str.size() - 2);
                      latex.str("");
                      latex << str;
                      latex << " \\\\ \\hline\n";
                    }
                    break;
                case TokenType::STRONG_OPEN:
                    if (currentNode->value == "{*") {
                        latex << "";
                    } else {
                        latex << "\\textbf{";
                    }
                    break;
                case TokenType::STRONG_CLOSE:
                    if (currentNode->value == "*}") {
                        latex << "";
                    } else {
                        latex << "}";
                    }
                    break;
                case TokenType::EMPH_OPEN:
                    if (currentNode->value == "{_") {
                        latex << "";
                    } else {
                        latex << "\\textit{";
                    }
                    break;
                case TokenType::EMPH_CLOSE:
                    if (currentNode->value == "_}") {
                        latex << "";
                    } else {
                        latex << "}";
                    }
                    break;
                case TokenType::DOUBLE_NEWLINE:
                    latex << "\n";
                    break;
                case TokenType::WORD:
                    latex << currentNode->value << " ";
                    break;
                default:
                    break;
            }
        }

        if (childIndex < currentNode->children.size()) {
            int reverseIndex = currentNode->children.size() - 1 - childIndex;
            nodeStack.push(currentNode->children[reverseIndex]);
            childIndexStack.push(0);
            childIndex++;
        } else {
            // Node processing after children
            switch (currentNode->type) {
                case TokenType::DocTitle:
                    latex << "}\n";
                    break;
                case TokenType::FDocTitle:
                    if (currentNode->children.size() == 3) {
                        latex << "\n\\end{document}\n";
                    }
                    break;
                case TokenType::FText:
                    if (!currentNode->children[0]->value.empty()) {
                        latex << "}\n";
                    }
                    break;
                case TokenType::Header:
                    latex << "}\n";
                    break;
                case TokenType::FPar:
                    if (!itemize) {
                        latex << "\n\\end{itemize}\n";
                        itemize = true;
                    }
                    break;
                case TokenType::FPar1:
                    if (!enumerate) {
                        latex << "\n\\end{enumerate}\n";
                        enumerate = true;
                    }
                    break;

                case TokenType::LINK_CLOSE:
                    if (currentNode->value == "]]") {
                        latex << "";
                    } else {
                        latex << " }\n\\end{figure}";
                    }
                    break;
                case TokenType::TableCap:
                    latex << "}\n\\end{table}";
                    break;

                

                default:
                    break;
            }
            nodeStack.pop();
            childIndexStack.pop();
        }
    }

    return latex.str();
}





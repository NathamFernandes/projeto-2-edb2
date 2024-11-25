#ifndef HANDLERS_H
#define HANDLERS_H

#include "book.h"

Node *handle_new_book(Node *library);
void handle_book_search(Node *library);
Node *handle_books_import(Node *library);
void handle_books_show(Node *library);

#endif
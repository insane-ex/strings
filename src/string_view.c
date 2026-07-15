#include "string_view.h"

#include <ctype.h>

StringView string_view_from_literal(const char *source) {
    StringView view = {0};

    if (source != NULL) {
        view.data = source;
        view.length = strlen(source);
    }

    return view;
}

StringView string_view_from_parts(const char *source, size_t length) {
    StringView view = {0};

    if (source != NULL) {
        view.data = source;
        view.length = length;
    }

    return view;
}

void string_view_chop_left(StringView *view) {
    if (view->data == NULL || view->length == 0) {
        return;
    }

    view->data += 1;
    view->length -= 1;
}

void string_view_chop_right(StringView *view) {
    if (view->data == NULL || view->length == 0) {
        return;
    }

    view->length -= 1;
}

void string_view_trim_left(StringView *view) {
    if (view->data == NULL || view->length == 0) {
        return;
    }

    while (view->length > 0 && isspace((unsigned char)view->data[0])) {
        string_view_chop_left(view);
    }
}

void string_view_trim_right(StringView *view) {
    if (view->data == NULL || view->length == 0) {
        return;
    }

    while (view->length > 0 && isspace((unsigned char)view->data[view->length - 1])) {
        string_view_chop_right(view);
    }
}

void string_view_trim(StringView *view) {
    if (view->data == NULL || view->length == 0) {
        return;
    }

    string_view_trim_left(view);
    string_view_trim_right(view);
}

bool string_view_is_empty(const StringView *view) {
    if (view == NULL || view->data == NULL) {
        return false;
    }

    return view->length == 0;
}

bool string_view_is_blank(const StringView *view) {
    if (view == NULL || view->data == NULL) {
        return false;
    }

    if (view->length == 0) {
        return true;
    }

    for (size_t i = 0; i < view->length; i++) {
        if (!isspace((unsigned char)view->data[i])) {
            return false;
        }
    }

    return true;
}

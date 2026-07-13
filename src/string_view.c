#include "string_view.h"

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

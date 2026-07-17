#ifndef STRING_VIEW_H
#define STRING_VIEW_H

#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

typedef struct {
    const char *data;
    size_t length;
} StringView;

#define STRING_VIEW_FORMAT "%.*s"
#define STRING_VIEW_ARGS(view) (int)((view).length), (view).data

#if defined(__GNUC__) || defined(__clang__)
#define STRING_VIEW_UNUSED __attribute__((unused))
#else
#define STRING_VIEW_UNUSED
#endif

static inline StringView string_view_from_literal(const char *source) {
    StringView view = {0};

    if (source == NULL) {
        return view;
    }

    view.data = source;
    view.length = strlen(source);

    return view;
}

static inline StringView string_view_from_parts(const char *source, size_t length) {
    StringView view = {0};

    if (source == NULL) {
        return view;
    }

    view.data = source;
    view.length = length;

    return view;
}

STRING_VIEW_UNUSED static void string_view_chop_left(StringView *view) {
    if (view->data == NULL || view->length == 0) {
        return;
    }

    view->data += 1;
    view->length -= 1;
}

STRING_VIEW_UNUSED static void string_view_chop_right(StringView *view) {
    if (view->data == NULL || view->length == 0) {
        return;
    }

    view->length -= 1;
}

STRING_VIEW_UNUSED static void string_view_trim_left(StringView *view) {
    if (view->data == NULL || view->length == 0) {
        return;
    }

    while (view->length > 0 && isspace((unsigned char)view->data[0])) {
        string_view_chop_left(view);
    }
}

STRING_VIEW_UNUSED static void string_view_trim_right(StringView *view) {
    if (view->data == NULL || view->length == 0) {
        return;
    }

    while (view->length > 0 && isspace((unsigned char)view->data[view->length - 1])) {
        string_view_chop_right(view);
    }
}

STRING_VIEW_UNUSED static void string_view_trim(StringView *view) {
    if (view->data == NULL || view->length == 0) {
        return;
    }

    string_view_trim_left(view);
    string_view_trim_right(view);
}

static inline bool string_view_is_initialized(const StringView *view) { return view != NULL && view->data != NULL; }

static inline bool string_view_is_empty(const StringView *view) {
    if (view == NULL || view->data == NULL) {
        return false;
    }

    return view->length == 0;
}

static inline bool string_view_is_blank(const StringView *view) {
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

STRING_VIEW_UNUSED static bool string_view_equals(const StringView *left, const StringView *right) {
    if (left == NULL || left->data == NULL) {
        return false;
    }

    if (right == NULL || right->data == NULL) {
        return false;
    }

    if (left->length != right->length) {
        return false;
    }

    return memcmp(left->data, right->data, left->length) == 0;
}

STRING_VIEW_UNUSED static bool string_view_equals_ignore_case(const StringView *left, const StringView *right) {
    if (left == NULL || left->data == NULL) {
        return false;
    }

    if (right == NULL || right->data == NULL) {
        return false;
    }

    if (left->length != right->length) {
        return false;
    }

    for (size_t i = 0; i < left->length; i++) {
        if (tolower(left->data[i]) != tolower(right->data[i])) {
            return false;
        }
    }

    return true;
}

STRING_VIEW_UNUSED static bool string_view_starts_with(const StringView *view, const StringView *prefix) {
    if (view == NULL || view->data == NULL) {
        return false;
    }

    if (prefix == NULL || prefix->data == NULL) {
        return false;
    }

    if (prefix->length > view->length) {
        return false;
    }

    return memcmp(view->data, prefix->data, prefix->length) == 0;
}

STRING_VIEW_UNUSED static bool string_view_ends_with(const StringView *view, const StringView *suffix) {
    if (view == NULL || view->data == NULL) {
        return false;
    }

    if (suffix == NULL || suffix->data == NULL) {
        return false;
    }

    if (suffix->length > view->length) {
        return false;
    }

    return memcmp(view->data + (view->length - suffix->length), suffix->data, suffix->length) == 0;
}

#endif

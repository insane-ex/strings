#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#define STRING_VIEW_FORMAT "%.*s"
#define STRING_VIEW_ARGS(view) (int)((view).length), (view).data

typedef struct {
    const char *data;
    size_t length;
} StringView;

StringView string_view_from_literal(const char *source);
StringView string_view_from_parts(const char *source, size_t length);

void string_view_chop_left(StringView *view);
void string_view_chop_right(StringView *view);
void string_view_trim_left(StringView *view);
void string_view_trim_right(StringView *view);
void string_view_trim(StringView *view);

bool string_view_is_empty(const StringView *view);
bool string_view_is_blank(const StringView *view);

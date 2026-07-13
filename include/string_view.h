#pragma once

#include <stddef.h>
#include <string.h>

typedef struct {
    const char *data;
    size_t length;
} StringView;

StringView string_view_from_literal(const char *source);
StringView string_view_from_parts(const char *source, size_t length);

void string_view_chop_left(StringView *view);
void string_view_chop_right(StringView *view);

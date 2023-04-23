#!/usr/bin/env python3

from jinja2 import Environment

limit = 255
prefix = ""

result = (
    Environment()
    .from_string(
        """
// clang-format off
#define {{prefix}}EVAL(...) __VA_ARGS__

#define {{prefix}}VARCOUNT_IMPL(_,{% for i in range(limit, 1, -1) -%}
_{{ i }},
{%- endfor %}result, ...) result
#define {{prefix}}VARCOUNT(...) {{prefix}}EVAL({{prefix}}VARCOUNT_IMPL(__VA_ARGS__,{{range(limit, 0, -1)|join(',')}},))

#define {{prefix}}GLUE_IMPL(x, y) x##y
#define {{prefix}}GLUE(x, y) {{prefix}}GLUE_IMPL(x, y)

#define {{prefix}}HEAD_IMPL(x, ...) x
#define {{prefix}}HEAD(...) {{prefix}}EVAL({{prefix}}HEAD_IMPL(__VA_ARGS__))

#define {{prefix}}TAIL_IMPL(x, ...) (__VA_ARGS__)
#define {{prefix}}TAIL(...) {{prefix}}EVAL({{prefix}}TAIL_IMPL(__VA_ARGS__))

#define {{prefix}}TRANSFORM(name, args) {{prefix}}GLUE({{prefix}}TRANSFORM_, {{prefix}}VARCOUNT args)(name, args)
#define {{prefix}}TRANSFORM_1(name, args) name args

{% for i in range(2, limit +1) -%}
#define {{prefix}}TRANSFORM_{{ i }}(name, args) name({{prefix}}HEAD args) {{prefix}}TRANSFORM_{{ i-1 }}(name, {{prefix}}TAIL args)
{% endfor -%}
// clang-format on
"""
    )
    .render(limit=limit, prefix=prefix)
)

print(result)

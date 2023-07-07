#!/usr/bin/env python3

# pylint: disable=missing-module-docstring,invalid-name,missing-function-docstring

from argparse import ArgumentParser
from os.path import exists
from jinja2 import Environment


def generate(output_path: str, **kwargs):
    template = """
#pragma once

// clang-format off
#define {{prefix}}THIRD_ARG(a, b, c, ...) c
#define {{prefix}}VA_OPT_SUPPORTED_IMPL(...) {{prefix}}THIRD_ARG(__VA_OPT__(,), 1, 0)
#define {{prefix}}VA_OPT_SUPPORTED {{prefix}}VA_OPT_SUPPORTED_IMPL(?)

#if !{{prefix}}VA_OPT_SUPPORTED
  #error "__VA_OPT__ is not supported, this library is not usable"
#endif

#define {{prefix}}EVAL(...) __VA_ARGS__

#define {{prefix}}VARCOUNT_IMPL(_,{% for i in range(limit, 0, -1) -%}
_{{ i }},
{%- endfor %}result, ...) result
#define {{prefix}}VARCOUNT(...) {{prefix}}EVAL({{prefix}}VARCOUNT_IMPL(__VA_OPT__(,) __VA_ARGS__,{{range(limit, -1, -1)|join(',')}},))

#define {{prefix}}GLUE_IMPL(x, y) x##y
#define {{prefix}}GLUE(x, y) {{prefix}}GLUE_IMPL(x, y)

#define {{prefix}}HEAD_IMPL(x, ...) x
#define {{prefix}}HEAD(...) {{prefix}}EVAL({{prefix}}HEAD_IMPL(__VA_ARGS__))

#define {{prefix}}TAIL_IMPL(x, ...) (__VA_ARGS__)
#define {{prefix}}TAIL(...) {{prefix}}EVAL({{prefix}}TAIL_IMPL(__VA_ARGS__))

#define {{prefix}}TRANSFORM(name, args) {{prefix}}GLUE({{prefix}}TRANSFORM_, {{prefix}}VARCOUNT args)(name, args)

#define {{prefix}}TRANSFORM_0(...)
#define {{prefix}}TRANSFORM_1(name, args) name args

{% for i in range(2, limit +1) -%}
#define {{prefix}}TRANSFORM_{{ i }}(name, args) name({{prefix}}HEAD args) {{prefix}}TRANSFORM_{{ i-1 }}(name, {{prefix}}TAIL args)
{% endfor -%}
// clang-format on
"""  # noqa: E501
    contents = Environment().from_string(template).render(**kwargs)

    if exists(output_path):
        # Open in read mode and check if the file already has the same contents,
        # this is done to avoid unnecessary recompilation
        with open(output_path, encoding="utf8") as f:
            if f.read() == contents:
                return

    with open(output_path, "w", encoding="utf8") as f:
        f.write(contents)


def main():
    parser = ArgumentParser(
        description="Render a jinja2 file with the full and short git hash"
    )
    parser.add_argument("--limit", type=int, default=255)
    parser.add_argument("--prefix", type=str, default="")
    parser.add_argument("output_path", type=str)

    args = parser.parse_args()

    generate(args.output_path, limit=args.limit, prefix=args.prefix)


if __name__ == "__main__":
    main()

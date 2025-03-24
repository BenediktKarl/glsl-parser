#include <nanobind/nanobind.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/string.h>

#include <iostream>

#include "parser.h"
#include "ast.h"

using namespace nanobind::literals;

std::vector<std::string> get_glsl_function_names(const std::string& glsl_source) {
    glsl::parser glsl_parser(glsl_source.c_str(), "shader.glsl");
    glsl::astTU* tu = glsl_parser.parse(glsl::astTU::kCompute);

    if (tu == nullptr) {
        std::cerr << glsl_parser.error() << std::endl;
        return {};
    }

    std::vector<std::string> result;
    for (const auto& function : tu->functions) {
        result.push_back(function->name);
    }

    return result;
}

NB_MODULE(glsl_parser, m) {
    m.def("get_glsl_function_names", get_glsl_function_names, "glsl_source"_a);
}
